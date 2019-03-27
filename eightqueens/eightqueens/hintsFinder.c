#include<stdlib.h> //Has to be placed above glut.h line; otherwise raises error C2381:'exit':redefinition.
#include<GL/glut.h>
#include<stdio.h>

int window_height = 600;

int mouse_x = 0;
int mouse_y = 0;

int grid_bottom = 100;
int grid_left = 100;
int grid_increment = 50;

int queen_position_x = 0;
int queen_position_y = 0;

int current_cell[2] = { 0, 0 };

int move_right = 1;
int move_up = 0;

int solutions[92][8][8] = { { { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 } }, { { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 } }, { { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 } }, { { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 } }, { { 0, 0, 0, 0, 0, 1, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 } }, { { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 } }, { { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 1, 0, 0, 0, 0, 0 } }, { { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 } }, { { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 } }, { { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 } }, { { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 } }, { { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 } }, { { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 } }, { { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 } }, { { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 } }, { { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 } }, { { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 } }, { { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 } }, { { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 } }, { { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 } }, { { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 } }, { { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 } }, { { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 } }, { { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 } }, { { 0, 0, 0, 1, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 } }, { { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 } }, { { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 1, 0, 0, 0 } }, { { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 } }, { { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 } }, { { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 } }, { { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 } }, { { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 } }, { { 0, 0, 0, 0, 1, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 } }, { { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 } }, { { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 1, 0, 0, 0, 0 } }, { { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 } }, { { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 } }, { { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 } }, { { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 } }, { { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 } }, { { 0, 0, 1, 0, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 } }, { { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 } }, { { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 0, 1, 0, 0 } }, { { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 } }, { { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 } }, { { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 } }, { { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 } }, { { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 } }, { { 0, 0, 0, 0, 1, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 } }, { { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 } }, { { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 1, 0, 0, 0, 0 } }, { { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 } }, { { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 } }, { { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 } }, { { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 } }, { { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 } }, { { 0, 0, 0, 0, 0, 0, 1, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 } }, { { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 1, 0, 0, 0 } }, { { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 1, 0, 0, 0, 0, 0, 0 } }, { { 0, 0, 0, 1, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 } }, { { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 } }, { { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 } }, { { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 } }, { { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 } }, { { 0, 0, 0, 0, 1, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 } }, { { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 } }, { { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 1, 0, 0, 0, 0 } }, { { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 } }, { { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 } }, { { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 } }, { { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 } }, { { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 } }, { { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 } }, { { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 } }, { { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 } }, { { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 } }, { { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 } }, { { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 } }, { { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 } }, { { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 } }, { { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 } }, { { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 } }, { { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 } }, { { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 } }, { { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 } }, { { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 } }, { { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 } }, { { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 } }, { { 0, 0, 0, 0, 1, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 } }, { { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 } }, { { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 1, 0, 0, 0, 0 } }, { { 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 1, 0, 0, 0, 0, 0, 0 } } };

int wait[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

int selected_cells_array[8][2] = { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } };
int selected_cells_count = 0;

int hint_cells_array[3][2] = { { 0, 0 }, { 0, 0 }, { 0, 0 } };
int hint_cells_count = 0;

/******************************************************** DRAWING SECTION *************************************************************/
//Validates cell
int valid(){
	if (current_cell[0] >= 0 && current_cell[0] < 8 && current_cell[1] >= 0 && current_cell[1] < 8){
		return 1;
	}
	else{
		return 0;
	}
}

//Converts cell indexes into Window Coordinates. WORKS
int* indexToCoordinate(int i, int j){
	static int a[2]; //Static has to be use, as C does not advocate to return the address of a local variable to outside of the function.
	a[0] = (i + 2) * grid_increment; //Gets bottom left corner of cell. Using +2, because window size magic.
	a[1] = (j + 2) * grid_increment;
	return a;
}

//Converts Window Coordinates to cell indexes.
int* coordinateToIndex(int i, int j){
	static int a[2]; //Static has to be use, as C does not advocate to return the address of a local variable to outside of the function.
	a[0] = (i / grid_increment) - 2; //Gets bottom left corner of cell. Using +2, because window size magic.
	a[1] = (j / grid_increment) - 2;
	return a;
}
//Takes in coordinate points, draws lines. WORKS
void drawline(int x1, int y1, int x2, int y2){
	glBegin(GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEnd();
}

//Draws 8 by 8 grid. WORKS
void drawgrid(){
	int grid_right = grid_left + (8 * grid_increment); //8 because of 8 x 8 grid.
	int grid_top = grid_bottom + (8 * grid_increment);

	for (int x = grid_left; x <= grid_right; x += grid_increment){
		drawline(x, grid_bottom, x, grid_top);
	}

	for (int y = grid_bottom; y <= grid_top; y += grid_increment){
		drawline(grid_left, y, grid_right, y);
	}
}

//Takes in coordinate point, draws cells placing point at left bottom. WORKS
void drawcell(int x, int y){
	//printf("Drawcell: Drawing cell at x,y: %d,%d\n", x, y);
	glBegin(GL_QUADS);
	glVertex2i(x, y);
	glVertex2i(x + grid_increment, y);
	glVertex2i(x + grid_increment, y + grid_increment);
	glVertex2i(x, y + grid_increment);
	glEnd();

}

//Highlights cell i,j on the grid. WORKS.
void highlightCell(int i, int j){
	int grid_right = grid_left + (8 * grid_increment);
	int grid_top = grid_bottom + (8 * grid_increment);

	//printf("HighlightCell(): Highlighted cell wrt window: %d,%d\n", i, j);

	int x = indexToCoordinate(i, j)[0];
	int y = indexToCoordinate(i, j)[1];

	if (x >= grid_left && x < grid_right && y >= grid_bottom && y < grid_top){
		drawcell(x, y);
	}
	else{
		printf("Grid left, bottom, top, right: %d, %d, %d, %d\n", grid_left, grid_bottom, grid_top, grid_right);
		printf("Cannot highlight: Mouse at %d,%d clicked outside grid!\n", x, y);
	}
}

//Draws already placed cells. Works.
void showCurrentCells(){

	for (int i = 0; i < selected_cells_count; i++){
		printf("Current cell:");
		highlightCell(selected_cells_array[i][0], selected_cells_array[i][1]);
	}
}

/******************************************************** CIRCULAR LINKED LIST SECTION *************************************************************/
/*
Properties of the following linked list:
It can contain only unique elements. delete() function returns a pointer to the head of the list.
*/
typedef struct solutions_node
{
	int solutionNumber;
	struct solutions_node* next;
} solutions_node;


typedef struct hints_node
{
	int cell_i;
	int cell_j;
	struct hints_node* next;
} hints_node;
int solutionNodesCount = 0;
int hintsNodesCount = 0;
//PERSISTENT LIST GETS OVERRIDDEN WITH EVERY NEW INPUT.
struct hints_node* persistentHintsList = NULL;
struct solutions_node* persistentsolutionsList = NULL;

void hints_printList(struct hints_node** headRef){
	struct hints_node* cursor = *headRef;
	if (cursor == NULL){
		printf("Hints List is empty!\n");
	}
	else{
		printf("Printing hints list:\n");
		do{
			printf("(%d,%d) ", cursor->cell_i,cursor->cell_j);
			cursor = cursor->next;
		} while (cursor != *headRef);
		printf("\n=============\n");
	}
}

void solutions_printList(struct solutions_node** headRef){
	struct solutions_node* cursor = *headRef;
	if (cursor == NULL){
		printf("Solutions List is empty!\n");
	}
	else{
		printf("Printing Solutions list:\n");
		do{
			printf("%d ", cursor->solutionNumber);
			cursor = cursor->next;
		} while (cursor != *headRef);
		printf("\n=============\n");
	}
}


struct hints_node* hints_append(struct hints_node** headRef, int i, int j){
	struct hints_node* new = NULL;
	new = malloc(sizeof(struct hints_node));
	new->cell_i = i;
	new->cell_j = j;
	new->next = *headRef;
	printf("*headRef is %p\n", *headRef);
	struct hints_node* cursor = *headRef;
	printf("cursor->next is %p\n", cursor->next);
	printf("Cursor has %d,%d.\n", cursor->cell_i, cursor->cell_j);

	//Repeated code
	if (cursor->cell_i == i && cursor->cell_j == j){
		printf("Data already in list head. Cannot insert duplicates!\n");
		return *headRef;
	}
	while (cursor->next != *headRef){
		printf("Cursor has %d,%d.\n", cursor->cell_i, cursor->cell_j);
		if (cursor->cell_i == i && cursor->cell_j == j){
			printf("Data already in list. Cannot insert duplicates!\n");
			return *headRef;
		}
		cursor = cursor->next;
	}
	cursor->next = new;
	printf("Append succesful!");
	hintsNodesCount++;
	return *headRef;
}

struct solutions_node* solutions_append(struct solutions_node** headRef, int data){
	struct solutions_node* new = NULL;
	new = malloc(sizeof(struct hints_node));
	new->solutionNumber = data;
	new->next = *headRef;

	struct solutions_node* cursor = *headRef;
	//Repeated code
	if (cursor->solutionNumber == data){
		printf("Data already in list. Cannot insert duplicates!\n");
		return *headRef;
	}
	while (cursor->next != *headRef){		
		if (cursor->solutionNumber == data){
			printf("Data already in list. Cannot insert duplicates!\n");
			return *headRef;
		}
		cursor = cursor->next;
	}
	cursor->next = new;
	printf("Append %d succesful!\n",data);
	solutionNodesCount++;
	return *headRef;
}

struct hints_node* hints_delete(struct hints_node** headRef, int i, int j){
	struct hints_node* cursor = *headRef;
	struct hints_node* pre_cursor = *headRef;

	if (*(&(*headRef)->cell_i) == i && *(&(*headRef)->cell_j) == j){
		printf("Deleting head!\n");
		printf("hintsNodesCount is %d\n", hintsNodesCount);
		if (hintsNodesCount == 1){
			hintsNodesCount--;
			printf("No other elements in list. Returning null.\n");
			return NULL;
		}

		while (pre_cursor->next != *headRef){
			pre_cursor = pre_cursor->next;
		}
		
		printf("Head is at: %p\n", *headRef);
		printf("pre_cursor->next is %p and head->next is %p", pre_cursor->next, *(&(*headRef)->next));
		pre_cursor->next = *(&(*headRef)->next);

		free(*headRef);
		*headRef = NULL;
		printf("Deleted data: %d,%d\n", i,j);
		hintsNodesCount--;
		return pre_cursor->next;
	}

	cursor = cursor->next;
	while (cursor != *headRef){
		if (cursor->cell_i == i && cursor->cell_j == j){
			while (pre_cursor->next != cursor){
				pre_cursor = pre_cursor->next;
			}
			pre_cursor->next = cursor->next;
			free(cursor);
			printf("Deleted data: %d,%d\n", i, j);
			hintsNodesCount--;
			return *headRef;
		}
		cursor = cursor->next;
	}
	printf("Data %d,%d not found. Unable to delete!\n", i, j);
	return *headRef;
}

struct solutions_node* solutions_delete(struct solutions_node** headRef, int data){
	struct solutions_node* cursor = *headRef;
	struct solutions_node* pre_cursor = *headRef;

	if (*(&(*headRef)->solutionNumber) == data){
		printf("Deleting head!\n");
		printf("solutionNodesCount is %d\n", solutionNodesCount);
		if (solutionNodesCount == 1){
			solutionNodesCount--;
			printf("No other elements in list. Returning null.\n");
			return NULL;
		}

		while (pre_cursor->next != *headRef){
			pre_cursor = pre_cursor->next;
		}

		printf("Head is at: %p\n", *headRef);
		printf("pre_cursor->next is %p and head->next is %p", pre_cursor->next, *(&(*headRef)->next));
		pre_cursor->next = *(&(*headRef)->next);

		free(*headRef);
		*headRef = NULL;
		printf("Deleted data: %d\n", data);
		solutionNodesCount--;
		return pre_cursor->next;
	}

	cursor = cursor->next;
	while (cursor != *headRef){
		if (cursor->solutionNumber == data){
			while (pre_cursor->next != cursor){
				pre_cursor = pre_cursor->next;
			}
			pre_cursor->next = cursor->next;
			free(cursor);
			printf("Deleted data: %d\n", data);
			solutionNodesCount--;
			return *headRef;
		}
		cursor = cursor->next;
	}
	printf("Data %d not found. Unable to delete!\n", data);
	return *headRef;
}


/******************************************************** MATCHING SOLUTIONS *************************************************************/

void highlightHints(struct hints_node** headRef){
	printf("HighlightHints called!\n");
	struct hints_node* cursor = *headRef;
	
	glColor3f(0, 1, 1);
	glPushMatrix();
	glLoadIdentity();
	printf("cursor i,j : %d,%d", cursor->cell_i, cursor->cell_j);
	while (cursor->next != *headRef){
		printf("Highlighting hint: %d,%d \n", cursor->cell_i, cursor->cell_j);
		highlightCell(cursor->cell_i, cursor->cell_j);
		cursor = cursor->next;
	}

	glPopMatrix();

	
	glColor3f(0, 1, 0);
}

/*
void highlightHints(){
	struct hints_node* cursor = persistentHintsList;
	glColor3f(0, 1, 1);
	glPushMatrix();
	glLoadIdentity();
	if (persistentHintsList != NULL){
		while (cursor->next != persistentHintsList){
			printf("Highlighting hint: %d,%d \n", cursor->cell_i, cursor->cell_j);
			highlightCell(cursor->cell_i, cursor->cell_j);
			cursor = cursor->next;
		}
	}

	glPopMatrix();


	glColor3f(0, 1, 0);
}
*/
int CellinSelectedCells(int i, int j){
	for (int i = 0; i < selected_cells_count; i++){
		if (selected_cells_array[i][0] == i && selected_cells_array[i][1] == j){
			return 1;
		}
	}
	return 0;
}

int arrayContains(int arr[8][2], int i, int j){
	for (int k = 0; k < 8; k++){
		if (arr[k][0] == i && arr[k][1] == j){
			return 1;
		}
	}
	return 0;
}

void findSolution(){
	struct hints_node* hintsList = NULL;
	hintsList = malloc(sizeof(struct hints_node));
	//You have to handle this.
	hintsList->cell_i = 1;
	hintsList->cell_j = 1;
	hintsList->next = hintsList;
	hintsNodesCount = 1;
	hints_printList(&hintsList);
	hintsList = hints_append(&hintsList, 1, 1);
	hints_printList(&hintsList);
	hintsList = hints_delete(&hintsList, 2, 1);
	hints_printList(&hintsList);
	
	struct solutions_node* solutionsList = NULL;
	solutionsList = malloc(sizeof(struct solutions_node));
	//You have to handle this.
	solutionsList->solutionNumber = 10;
	solutionsList->next = solutionsList;
	solutionNodesCount = 1;
	solutions_printList(&solutionsList);
	solutionsList = solutions_append(&solutionsList, 10);
	solutions_printList(&solutionsList);
	solutionsList = solutions_delete(&solutionsList, 12);
	solutions_printList(&solutionsList);


	
}




/******************************************************** DISPLAY SECTION *************************************************************/
void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);

	glColor3f(0, 1, 0);

	drawgrid();
	current_cell[0] = coordinateToIndex(mouse_x, mouse_y)[0];
	current_cell[1] = coordinateToIndex(mouse_x, mouse_y)[1];
	printf("Currentcell in display function: %d,%d\n", current_cell[0], current_cell[1]);
	//Only  eight queens can be placed on the grid.
	findSolution();
//	highlightHints();
	showCurrentCells();

	glFlush();

	printf("=========================================================\n");
}


void mouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		mouse_x = x;

		//		Subtraction and multiplication for mouse_y required
		//		because GL coordinates start at bottom left,
		//		and Windows Mouse Coordinates start at top left.

		mouse_y = window_height - y;

		if (mouse_y < 0){
			mouse_y = mouse_y*-1;
		}
	}
	
	glutPostRedisplay();
}

void main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(window_height, window_height);
	glutCreateWindow("Queens");
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, window_height, 0, window_height);
	glMatrixMode(GL_MODELVIEW);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMainLoop();
}


/*
Todo: Rename list related variables later.
*/