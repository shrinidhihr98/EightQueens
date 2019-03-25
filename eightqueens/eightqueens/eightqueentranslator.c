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

int move_right = 1;
int move_up = 0;

int selected_cells[8][2] = { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } };
int wait[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int selected_cells_count = 0;


/******************************************************** DRAWING SECTION *************************************************************/
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

	printf("HighlightCell(): Highlighted cell wrt window: %d,%d\n", i, j);

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
		highlightCell(selected_cells[i][0], selected_cells[i][1]);
	}
}

void translatequeen(int i, int j){

	int grid_right = grid_left + (8 * grid_increment);
	int grid_top = grid_bottom + (8 * grid_increment);


	int target_position_x = indexToCoordinate(i, j)[0];
	int target_position_y = indexToCoordinate(i, j)[1];


	//The following code moves the queen on click.
	if (queen_position_x < target_position_x){
		queen_position_x += 1;
		move_right = 1;

	}
	else{
		printf("Move right set to zero!\n");
		move_right = 0;
	}
	if (queen_position_y < target_position_y && move_right == 0){
		queen_position_y += 1;
		move_up = 1;
	}
	else {
		move_up = 0;
	}

	if ((move_right == 1) | (move_up == 1)){
		glutPostRedisplay();
	}

	drawcell(queen_position_x, queen_position_y);

	printf("\tStarting queenposition: x,y: %d,%d\n\tEnding queen position: x,y, %d,%d\n", queen_position_x, queen_position_y, target_position_x, target_position_y);
	glPushMatrix();
	glLoadIdentity();
	drawgrid();
	glTranslatef(move_right, move_up, 0);

	glPopMatrix();

	if ((move_right == 0) && (move_up == 0)){
		selected_cells[selected_cells_count][0] = i;
		selected_cells[selected_cells_count][1] = j;

		queen_position_x = 0;
		queen_position_y = 0;
		selected_cells_count++;
	}

}


/******************************************************** DISPLAY SECTION *************************************************************/
void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);

	glColor3f(0, 1, 0);

	drawgrid();

	//Only  eight queens can be placed on the grid.
	if (selected_cells_count <= 8){
		translatequeen(coordinateToIndex(mouse_x, mouse_y)[0], coordinateToIndex(mouse_x, mouse_y)[1]);
	}

	showCurrentCells();
	//translatequeen(3,3);
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
