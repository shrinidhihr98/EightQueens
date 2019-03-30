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

int target_position_x = 0, target_position_y = 0;

int current_cell[2] = { 0, 0 };
int newi = 0;
int newj = 0;

int conflictArray[3] = { 0, 0, 0 };

int move_right = 1;
int move_up = 0;

int solutions[92][8][2] = { { { 0, 1 }, { 1, 3 }, { 2, 5 }, { 3, 7 }, { 4, 2 }, { 5, 0 }, { 6, 6 }, { 7, 4 } }, { { 0, 2 }, { 1, 7 }, { 2, 3 }, { 3, 6 }, { 4, 0 }, { 5, 5 }, { 6, 1 }, { 7, 4 } }, { { 0, 3 }, { 1, 1 }, { 2, 7 }, { 3, 5 }, { 4, 0 }, { 5, 2 }, { 6, 4 }, { 7, 6 } }, { { 0, 3 }, { 1, 6 }, { 2, 2 }, { 3, 7 }, { 4, 1 }, { 5, 4 }, { 6, 0 }, { 7, 5 } }, { { 0, 5 }, { 1, 0 }, { 2, 4 }, { 3, 1 }, { 4, 7 }, { 5, 2 }, { 6, 6 }, { 7, 3 } }, { { 0, 4 }, { 1, 6 }, { 2, 0 }, { 3, 2 }, { 4, 7 }, { 5, 5 }, { 6, 3 }, { 7, 1 } }, { { 0, 4 }, { 1, 1 }, { 2, 5 }, { 3, 0 }, { 4, 6 }, { 5, 3 }, { 6, 7 }, { 7, 2 } }, { { 0, 6 }, { 1, 4 }, { 2, 2 }, { 3, 0 }, { 4, 5 }, { 5, 7 }, { 6, 1 }, { 7, 3 } }, { { 0, 0 }, { 1, 6 }, { 2, 3 }, { 3, 5 }, { 4, 7 }, { 5, 1 }, { 6, 4 }, { 7, 2 } }, { { 0, 7 }, { 1, 2 }, { 2, 0 }, { 3, 5 }, { 4, 1 }, { 5, 4 }, { 6, 6 }, { 7, 3 } }, { { 0, 5 }, { 1, 3 }, { 2, 6 }, { 3, 0 }, { 4, 2 }, { 5, 4 }, { 6, 1 }, { 7, 7 } }, { { 0, 4 }, { 1, 1 }, { 2, 3 }, { 3, 6 }, { 4, 2 }, { 5, 7 }, { 6, 5 }, { 7, 0 } }, { { 0, 0 }, { 1, 5 }, { 2, 7 }, { 3, 2 }, { 4, 6 }, { 5, 3 }, { 6, 1 }, { 7, 4 } }, { { 0, 2 }, { 1, 4 }, { 2, 1 }, { 3, 7 }, { 4, 5 }, { 5, 3 }, { 6, 6 }, { 7, 0 } }, { { 0, 3 }, { 1, 6 }, { 2, 4 }, { 3, 1 }, { 4, 5 }, { 5, 0 }, { 6, 2 }, { 7, 7 } }, { { 0, 7 }, { 1, 1 }, { 2, 4 }, { 3, 2 }, { 4, 0 }, { 5, 6 }, { 6, 3 }, { 7, 5 } }, { { 0, 0 }, { 1, 6 }, { 2, 4 }, { 3, 7 }, { 4, 1 }, { 5, 3 }, { 6, 5 }, { 7, 2 } }, { { 0, 7 }, { 1, 3 }, { 2, 0 }, { 3, 2 }, { 4, 5 }, { 5, 1 }, { 6, 6 }, { 7, 4 } }, { { 0, 5 }, { 1, 2 }, { 2, 4 }, { 3, 6 }, { 4, 0 }, { 5, 3 }, { 6, 1 }, { 7, 7 } }, { { 0, 3 }, { 1, 1 }, { 2, 6 }, { 3, 2 }, { 4, 5 }, { 5, 7 }, { 6, 4 }, { 7, 0 } }, { { 0, 0 }, { 1, 4 }, { 2, 7 }, { 3, 5 }, { 4, 2 }, { 5, 6 }, { 6, 1 }, { 7, 3 } }, { { 0, 2 }, { 1, 5 }, { 2, 3 }, { 3, 1 }, { 4, 7 }, { 5, 4 }, { 6, 6 }, { 7, 0 } }, { { 0, 4 }, { 1, 6 }, { 2, 1 }, { 3, 5 }, { 4, 2 }, { 5, 0 }, { 6, 3 }, { 7, 7 } }, { { 0, 7 }, { 1, 1 }, { 2, 3 }, { 3, 0 }, { 4, 6 }, { 5, 4 }, { 6, 2 }, { 7, 5 } }, { { 0, 3 }, { 1, 0 }, { 2, 4 }, { 3, 7 }, { 4, 1 }, { 5, 6 }, { 6, 2 }, { 7, 5 } }, { { 0, 6 }, { 1, 3 }, { 2, 1 }, { 3, 7 }, { 4, 5 }, { 5, 0 }, { 6, 2 }, { 7, 4 } }, { { 0, 2 }, { 1, 5 }, { 2, 1 }, { 3, 6 }, { 4, 0 }, { 5, 3 }, { 6, 7 }, { 7, 4 } }, { { 0, 3 }, { 1, 5 }, { 2, 7 }, { 3, 2 }, { 4, 0 }, { 5, 6 }, { 6, 4 }, { 7, 1 } }, { { 0, 1 }, { 1, 4 }, { 2, 6 }, { 3, 0 }, { 4, 2 }, { 5, 7 }, { 6, 5 }, { 7, 3 } }, { { 0, 5 }, { 1, 2 }, { 2, 6 }, { 3, 1 }, { 4, 7 }, { 5, 4 }, { 6, 0 }, { 7, 3 } }, { { 0, 4 }, { 1, 2 }, { 2, 0 }, { 3, 5 }, { 4, 7 }, { 5, 1 }, { 6, 3 }, { 7, 6 } }, { { 0, 4 }, { 1, 7 }, { 2, 3 }, { 3, 0 }, { 4, 6 }, { 5, 1 }, { 6, 5 }, { 7, 2 } }, { { 0, 4 }, { 1, 0 }, { 2, 7 }, { 3, 3 }, { 4, 1 }, { 5, 6 }, { 6, 2 }, { 7, 5 } }, { { 0, 6 }, { 1, 3 }, { 2, 1 }, { 3, 4 }, { 4, 7 }, { 5, 0 }, { 6, 2 }, { 7, 5 } }, { { 0, 2 }, { 1, 5 }, { 2, 1 }, { 3, 6 }, { 4, 4 }, { 5, 0 }, { 6, 7 }, { 7, 3 } }, { { 0, 2 }, { 1, 5 }, { 2, 7 }, { 3, 0 }, { 4, 3 }, { 5, 6 }, { 6, 4 }, { 7, 1 } }, { { 0, 1 }, { 1, 4 }, { 2, 6 }, { 3, 3 }, { 4, 0 }, { 5, 7 }, { 6, 5 }, { 7, 2 } }, { { 0, 5 }, { 1, 2 }, { 2, 6 }, { 3, 1 }, { 4, 3 }, { 5, 7 }, { 6, 0 }, { 7, 4 } }, { { 0, 5 }, { 1, 2 }, { 2, 0 }, { 3, 7 }, { 4, 4 }, { 5, 1 }, { 6, 3 }, { 7, 6 } }, { { 0, 3 }, { 1, 7 }, { 2, 0 }, { 3, 4 }, { 4, 6 }, { 5, 1 }, { 6, 5 }, { 7, 2 } }, { { 0, 2 }, { 1, 0 }, { 2, 6 }, { 3, 4 }, { 4, 7 }, { 5, 1 }, { 6, 3 }, { 7, 5 } }, { { 0, 6 }, { 1, 2 }, { 2, 7 }, { 3, 1 }, { 4, 4 }, { 5, 0 }, { 6, 5 }, { 7, 3 } }, { { 0, 2 }, { 1, 4 }, { 2, 6 }, { 3, 0 }, { 4, 3 }, { 5, 1 }, { 6, 7 }, { 7, 5 } }, { { 0, 4 }, { 1, 2 }, { 2, 7 }, { 3, 3 }, { 4, 6 }, { 5, 0 }, { 6, 5 }, { 7, 1 } }, { { 0, 1 }, { 1, 5 }, { 2, 0 }, { 3, 6 }, { 4, 3 }, { 5, 7 }, { 6, 2 }, { 7, 4 } }, { { 0, 5 }, { 1, 3 }, { 2, 1 }, { 3, 7 }, { 4, 4 }, { 5, 6 }, { 6, 0 }, { 7, 2 } }, { { 0, 3 }, { 1, 5 }, { 2, 0 }, { 3, 4 }, { 4, 1 }, { 5, 7 }, { 6, 2 }, { 7, 6 } }, { { 0, 5 }, { 1, 7 }, { 2, 1 }, { 3, 3 }, { 4, 0 }, { 5, 6 }, { 6, 4 }, { 7, 2 } }, { { 0, 4 }, { 1, 0 }, { 2, 3 }, { 3, 5 }, { 4, 7 }, { 5, 1 }, { 6, 6 }, { 7, 2 } }, { { 0, 6 }, { 1, 2 }, { 2, 0 }, { 3, 5 }, { 4, 7 }, { 5, 4 }, { 6, 1 }, { 7, 3 } }, { { 0, 5 }, { 1, 1 }, { 2, 6 }, { 3, 0 }, { 4, 2 }, { 5, 4 }, { 6, 7 }, { 7, 3 } }, { { 0, 4 }, { 1, 6 }, { 2, 3 }, { 3, 0 }, { 4, 2 }, { 5, 7 }, { 6, 5 }, { 7, 1 } }, { { 0, 1 }, { 1, 5 }, { 2, 7 }, { 3, 2 }, { 4, 0 }, { 5, 3 }, { 6, 6 }, { 7, 4 } }, { { 0, 2 }, { 1, 6 }, { 2, 1 }, { 3, 7 }, { 4, 5 }, { 5, 3 }, { 6, 0 }, { 7, 4 } }, { { 0, 3 }, { 1, 1 }, { 2, 4 }, { 3, 7 }, { 4, 5 }, { 5, 0 }, { 6, 2 }, { 7, 6 } }, { { 0, 3 }, { 1, 7 }, { 2, 4 }, { 3, 2 }, { 4, 0 }, { 5, 6 }, { 6, 1 }, { 7, 5 } }, { { 0, 6 }, { 1, 0 }, { 2, 2 }, { 3, 7 }, { 4, 5 }, { 5, 3 }, { 6, 1 }, { 7, 4 } }, { { 0, 6 }, { 1, 1 }, { 2, 5 }, { 3, 2 }, { 4, 0 }, { 5, 3 }, { 6, 7 }, { 7, 4 } }, { { 0, 3 }, { 1, 6 }, { 2, 4 }, { 3, 2 }, { 4, 0 }, { 5, 5 }, { 6, 7 }, { 7, 1 } }, { { 0, 3 }, { 1, 0 }, { 2, 4 }, { 3, 7 }, { 4, 5 }, { 5, 2 }, { 6, 6 }, { 7, 1 } }, { { 0, 1 }, { 1, 6 }, { 2, 2 }, { 3, 5 }, { 4, 7 }, { 5, 4 }, { 6, 0 }, { 7, 3 } }, { { 0, 4 }, { 1, 1 }, { 2, 3 }, { 3, 5 }, { 4, 7 }, { 5, 2 }, { 6, 0 }, { 7, 6 } }, { { 0, 4 }, { 1, 7 }, { 2, 3 }, { 3, 0 }, { 4, 2 }, { 5, 5 }, { 6, 1 }, { 7, 6 } }, { { 0, 1 }, { 1, 7 }, { 2, 5 }, { 3, 0 }, { 4, 2 }, { 5, 4 }, { 6, 6 }, { 7, 3 } }, { { 0, 4 }, { 1, 0 }, { 2, 7 }, { 3, 5 }, { 4, 2 }, { 5, 6 }, { 6, 1 }, { 7, 3 } }, { { 0, 6 }, { 1, 1 }, { 2, 3 }, { 3, 0 }, { 4, 7 }, { 5, 4 }, { 6, 2 }, { 7, 5 } }, { { 0, 4 }, { 1, 6 }, { 2, 1 }, { 3, 5 }, { 4, 2 }, { 5, 0 }, { 6, 7 }, { 7, 3 } }, { { 0, 2 }, { 1, 5 }, { 2, 3 }, { 3, 0 }, { 4, 7 }, { 5, 4 }, { 6, 6 }, { 7, 1 } }, { { 0, 1 }, { 1, 6 }, { 2, 4 }, { 3, 7 }, { 4, 0 }, { 5, 3 }, { 6, 5 }, { 7, 2 } }, { { 0, 3 }, { 1, 1 }, { 2, 6 }, { 3, 2 }, { 4, 5 }, { 5, 7 }, { 6, 0 }, { 7, 4 } }, { { 0, 5 }, { 1, 2 }, { 2, 4 }, { 3, 7 }, { 4, 0 }, { 5, 3 }, { 6, 1 }, { 7, 6 } }, { { 0, 3 }, { 1, 7 }, { 2, 0 }, { 3, 2 }, { 4, 5 }, { 5, 1 }, { 6, 6 }, { 7, 4 } }, { { 0, 4 }, { 1, 6 }, { 2, 0 }, { 3, 3 }, { 4, 1 }, { 5, 7 }, { 6, 5 }, { 7, 2 } }, { { 0, 5 }, { 1, 3 }, { 2, 0 }, { 3, 4 }, { 4, 7 }, { 5, 1 }, { 6, 6 }, { 7, 2 } }, { { 0, 5 }, { 1, 2 }, { 2, 0 }, { 3, 6 }, { 4, 4 }, { 5, 7 }, { 6, 1 }, { 7, 3 } }, { { 0, 5 }, { 1, 1 }, { 2, 6 }, { 3, 0 }, { 4, 3 }, { 5, 7 }, { 6, 4 }, { 7, 2 } }, { { 0, 2 }, { 1, 4 }, { 2, 7 }, { 3, 3 }, { 4, 0 }, { 5, 6 }, { 6, 1 }, { 7, 5 } }, { { 0, 2 }, { 1, 5 }, { 2, 7 }, { 3, 1 }, { 4, 3 }, { 5, 0 }, { 6, 6 }, { 7, 4 } }, { { 0, 2 }, { 1, 6 }, { 2, 1 }, { 3, 7 }, { 4, 4 }, { 5, 0 }, { 6, 3 }, { 7, 5 } }, { { 0, 3 }, { 1, 1 }, { 2, 7 }, { 3, 4 }, { 4, 6 }, { 5, 0 }, { 6, 2 }, { 7, 5 } }, { { 0, 5 }, { 1, 2 }, { 2, 0 }, { 3, 7 }, { 4, 3 }, { 5, 1 }, { 6, 6 }, { 7, 4 } }, { { 0, 5 }, { 1, 2 }, { 2, 6 }, { 3, 3 }, { 4, 0 }, { 5, 7 }, { 6, 1 }, { 7, 4 } }, { { 0, 3 }, { 1, 1 }, { 2, 6 }, { 3, 4 }, { 4, 0 }, { 5, 7 }, { 6, 5 }, { 7, 2 } }, { { 0, 3 }, { 1, 6 }, { 2, 0 }, { 3, 7 }, { 4, 4 }, { 5, 1 }, { 6, 5 }, { 7, 2 } }, { { 0, 2 }, { 1, 5 }, { 2, 1 }, { 3, 4 }, { 4, 7 }, { 5, 0 }, { 6, 6 }, { 7, 3 } }, { { 0, 4 }, { 1, 6 }, { 2, 1 }, { 3, 3 }, { 4, 7 }, { 5, 0 }, { 6, 2 }, { 7, 5 } }, { { 0, 4 }, { 1, 1 }, { 2, 7 }, { 3, 0 }, { 4, 3 }, { 5, 6 }, { 6, 2 }, { 7, 5 } }, { { 0, 2 }, { 1, 5 }, { 2, 7 }, { 3, 0 }, { 4, 4 }, { 5, 6 }, { 6, 1 }, { 7, 3 } }, { { 0, 4 }, { 1, 0 }, { 2, 7 }, { 3, 5 }, { 4, 2 }, { 5, 6 }, { 6, 1 }, { 7, 3 } }, { { 0, 6 }, { 1, 1 }, { 2, 3 }, { 3, 0 }, { 4, 7 }, { 5, 4 }, { 6, 2 }, { 7, 5 } }, { { 0, 4 }, { 1, 6 }, { 2, 1 }, { 3, 5 }, { 4, 2 }, { 5, 0 }, { 6, 7 }, { 7, 3 } }, { { 0, 2 }, { 1, 5 }, { 2, 3 }, { 3, 0 }, { 4, 7 }, { 5, 4 }, { 6, 6 }, { 7, 1 } } };

int wait[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

int selected_cells_array[8][3] = { { 0, 0, 1 }, { 0, 0, 1 }, { 0, 0, 1 }, { 0, 0, 1 }, { 0, 0, 1 }, { 0, 0, 1 }, { 0, 0, 1 }, { 0, 0, 1 } };
int selected_cells_count = 0;

int hint_cells_count = 0;

typedef enum { ToBeStarted, Started, MoveNewRight, MoveNewUp, CheckConflict, MoveConflictHorizontal, MoveConflictVertical, Killed, MoveConflictHorizontalBack, MoveConflictVerticalBack, FindHints, Done } status;
enum status state = ToBeStarted;

/*Colors*/
GLfloat RED[3] = { 1, 0, 0 };
GLfloat GREEN[3] = { 0, 1, 0 };
GLfloat BLUE[3] = { 0, 0, 1 };
GLfloat LIGHT_BLUE[3] = { 0, 1, 1 };
GLfloat ORANGE[3] = { 1, 0.5, 0 };

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
void drawcell(int x, int y, GLfloat* color){
	//printf("Drawcell: Drawing cell at x,y: %d,%d\n", x, y);
	glColor3fv(color);
	glBegin(GL_QUADS);
	glVertex2i(x, y);
	glVertex2i(x + grid_increment, y);
	glVertex2i(x + grid_increment, y + grid_increment);
	glVertex2i(x, y + grid_increment);
	glEnd();
	glColor3fv(GREEN);

}

//Highlights cell i,j on the grid. WORKS.
void highlightCell(int i, int j,GLfloat* color){
	int grid_right = grid_left + (8 * grid_increment);
	int grid_top = grid_bottom + (8 * grid_increment);

	//printf("HighlightCell(): Highlighted cell wrt window: %d,%d\n", i, j);

	int x = indexToCoordinate(i, j)[0];
	int y = indexToCoordinate(i, j)[1];

	if (x >= grid_left && x < grid_right && y >= grid_bottom && y < grid_top){
		drawcell(x, y,color);
	}
	else{
		printf("Grid left, bottom, top, right: %d, %d, %d, %d\n", grid_left, grid_bottom, grid_top, grid_right);
		printf("Cannot highlight: Mouse at %d,%d clicked outside grid!\n", x, y);
	}
}

//Draws already placed cells. Works.
void showSelectedCells(){

	for (int i = 0; i < selected_cells_count; i++){
		//printf("Selected cell: %d,%d,%d\n", selected_cells_array[i][0], selected_cells_array[i][1], selected_cells_array[i][2]);
		//printf("Highlighting selected cells:\n");
		if (selected_cells_array[i][2] == 1){
			
			highlightCell(selected_cells_array[i][0], selected_cells_array[i][1],GREEN);
		}

	}
}


/******************************************************** CIRCULAR LINKED LIST SECTION *************************************************************/
typedef struct hints_node
{
	int cell_i;
	int cell_j;
	struct hints_node* next;
} hints_node;
int solutionNodesCount = 0;
int hintsNodesCount = 0;

void hints_printList(struct hints_node** headRef){
	struct hints_node* cursor = *headRef;
	if (cursor == NULL){
		printf("Hints List is empty!\n");
	}
	else{
		printf("Printing hints list:\n");
		do{
			printf("(%d,%d) ", cursor->cell_i, cursor->cell_j);
			cursor = cursor->next;
		} while (cursor != *headRef);
		printf("\n-----------------\n");
	}
}


struct hints_node* hints_append(struct hints_node** headRef, int i, int j){
	struct hints_node* new = NULL;
	new = malloc(sizeof(struct hints_node));
	new->cell_i = i;
	new->cell_j = j;
	new->next = *headRef;
	struct hints_node* cursor = *headRef;

	//Repeated code
	if (cursor->cell_i == i && cursor->cell_j == j){
		//printf("Data already in list head. Cannot insert duplicates!\n");
		return *headRef;
	}
	while (cursor->next != *headRef){
		if (cursor->cell_i == i && cursor->cell_j == j){
			//printf("Data already in list. Cannot insert duplicates!\n");
			return *headRef;
		}
		cursor = cursor->next;
	}
	cursor->next = new;
	//printf("Hints Append succesful!\n");
	hintsNodesCount++;
	return *headRef;
}


/******************************************************** MATCHING SOLUTIONS *************************************************************/

void highlightHints(struct hints_node** headRef){
	struct hints_node* cursor = *headRef;
	
	glPushMatrix();
	glLoadIdentity();
	printf("Highlighting hints:\n");
	do{
		highlightCell(cursor->cell_i, cursor->cell_j,LIGHT_BLUE);
		cursor = cursor->next;
	} while (cursor != *headRef);
	glPopMatrix();


	
}

//Validates cell
int validCell(){
	if (current_cell[0] >= 0 && current_cell[0] < 8 && current_cell[1] >= 0 && current_cell[1] < 8){
		return 1;
	}
	else{
		return 0;
	}
}

int CellinSelectedCells(int cell_i, int cell_j){
	for (int i = 0; i < selected_cells_count; i++){
		if (selected_cells_array[i][0] == cell_i && selected_cells_array[i][1] == cell_j){
			return 1;
		}
	}
	return 0;
}

int arrayContains(int arr[8][2], int cell_i, int cell_j){
	for (int k = 0; k < 8; k++){
		if (arr[k][0] == cell_i && arr[k][1] == cell_j){
			return 1;
		}
	}
	return 0;
}


int solutionContainsSelected(int k){
	for (int i = 0; i < selected_cells_count; i++){
		if (arrayContains(solutions[k], selected_cells_array[i][0], selected_cells_array[i][1]) == 0){
			return 0;
		}
	}
	return 1;
}

int isSolutionPossible(){

	for (int k = 0; k < 92; k++){
		if (solutionContainsSelected(k)){
			return 1;
		}
	}
	return 0;
}
void findHints(){
	struct hints_node* hintsList = NULL;
	hintsList = malloc(sizeof(struct hints_node));
	if (hintsList == NULL){
		printf("Unable to allocate memory!\n");
	}
	//Initializing.
	hintsList->cell_i = 10;
	hintsList->cell_j = 10;
	hintsList->next = hintsList;
	hintsNodesCount = 1;


	if (validCell() && !CellinSelectedCells(current_cell[0], current_cell[1])){
		printf("\nNew cell found! %d,%d\n", current_cell[0], current_cell[1]);
		if (selected_cells_count < 8){
			//TODO: Find a better place to put these following 3 lines.
			selected_cells_array[selected_cells_count][0] = current_cell[0];
			selected_cells_array[selected_cells_count][1] = current_cell[1];
			selected_cells_array[selected_cells_count][2] = 1;
			selected_cells_count++;
		}
		else{
			printf("no new cell.\n");
		}
	}

	if (!isSolutionPossible()){
		printf("NO SOLUTION EXISTS!!!!!!!!!!!!!!\n");
	}
	/*Finding hints.*/
	if (selected_cells_count > 0){
		for (int k = 0; k < 92; k++){
			if (solutionContainsSelected(k)){
				printf("The solution number %d contains currently selected.\n", k);
				for (int i = 0; i < 8; i++){
					if (!CellinSelectedCells(solutions[k][i][0], solutions[k][i][1])){
						if (hintsList->cell_i == 10){
							//Replace the initialization parameters.
							hintsList->cell_i = solutions[k][i][0];
							hintsList->cell_j = solutions[k][i][1];
						}
						else{
							hintsList = hints_append(&hintsList, solutions[k][i][0], solutions[k][i][1]);
						}
					}
				}
			}
		}

		//hints_printList(&hintsList);
		if (selected_cells_count < 8){
			highlightHints(&hintsList);
		}
	}
}
/*************************TRANSLATE QUEENS********************************/

int* detectConflict(int conflict[], int newi, int newj){

	int A = 0, B = 0;
	for (int s = 0; s < selected_cells_count; s++){
		A = selected_cells_array[s][0];
		B = selected_cells_array[s][1];
		printf("A is%d. B is %d.\n", A, B);
		printf("newi is %d. newj is %d.\n", newi, newj);
		/*Handle row or column conflicts.*/
		if (A == newi || B == newj){
			conflict[0] = 1;
			conflict[1] = A;
			conflict[2] = B;
			return conflict;
		}

		/*Handle diagonal conflict along north east.*/
		for (int i = 1; i < (8 - ((A>B) ? A : B)); i++){
			if ((newi == (A + i)) && (newj == (B + i))){
				conflict[0] = 1;
				conflict[1] = A;
				conflict[2] = B;
				return conflict;
			}
		}

		/*Handle diagonal conflict along south west.*/
		for (int i = 1; i <= ((A<B) ? A : B); i++){
			if ((newi == (A - i)) && (newj == (B - i))){
				conflict[0] = 1;
				conflict[1] = A;
				conflict[2] = B;
				return conflict;
			}
		}

		/*Handle conflicts along other diagonals.*/


		if (A > B){
			for (int i = 1; i < 8 - A; i++){
				if ((newi == (A + i)) && (newj == (B - i))){
					conflict[0] = 1;
					conflict[1] = A;
					conflict[2] = B;
					return conflict;
				}
			}

			for (int i = 1; i <= A; i++){
				if ((newi == (A - i)) && (newj == (B + i))){
					conflict[0] = 1;
					conflict[1] = A;
					conflict[2] = B;
					return conflict;
				}
			}
		}
		if (A < B){
			for (int i = 1; i <= B; i++){
				if ((newi == (A + i)) && (newj == (B - i))){
					conflict[0] = 1;
					conflict[1] = A;
					conflict[2] = B;
					return conflict;
				}
			}
			for (int i = 1; i < 8 - B; i++){
				if ((newi == (A - i)) && (newj == (B + i))){
					conflict[0] = 1;
					conflict[1] = A;
					conflict[2] = B;
					return conflict;
				}
			}
		}


	}
	conflict[0] = 0;
	conflict[1] = 0;
	conflict[2] = 0;
	return conflict;
}

void translatequeen(int i, int j){
	for (int it = 0; it < 1000; it++){
		for (int jt = 0; jt < 100; jt++);
	}
	int array[3] = { 0, 0, 0 };
	int* c = detectConflict(array, i, j);
	printf("Conflict array: %d,%d,%d\n", c[0], c[1], c[2]);
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

	drawcell(queen_position_x, queen_position_y,GREEN);

	glPushMatrix();
	glLoadIdentity();
	drawgrid();
	showSelectedCells();
	glTranslatef(move_right, move_up, 0);

	glPopMatrix();

	if ((move_right == 0) && (move_up == 0)){
		findHints();
		queen_position_x = 0;
		queen_position_y = 0;
	}

}

void setSelected(int newi, int newj, int value){
	for (int i = 0; i < selected_cells_count; i++){
		if (selected_cells_array[i][0] == newi && selected_cells_array[i][1] == newj){
			selected_cells_array[i][2] = value;
		}
	}
}

void drawBackground(void){
	glPushMatrix();
	glLoadIdentity();
	drawgrid();
	showSelectedCells();
	glTranslatef(move_right, move_up, 0);
	glPopMatrix();

}

void displaySolution(){
	//{ ToBeStarted, Started, MoveNewRight, MoveNewUp, CheckConflict,
	//	MoveConflictHorizontal, MoveConflictVertical, Killed, MoveConflictHorizontalBack,
	//	MoveConflictVerticalBack, FindHints, Done }
	for (int it = 0; it < 1000; it++){
		for (int jt = 0; jt < 1000; jt++);
	}

	int array[3] = { 0, 0, 0 };
	int* c = NULL;
	switch (state){
	case ToBeStarted:
		if (validCell())
		{
			state = Started;
			glutPostRedisplay();
		}
		drawBackground();
		break;
	case Started:
		if (!CellinSelectedCells(current_cell[0], current_cell[1]))
		{
			newi = current_cell[0];
			newj = current_cell[1];
			queen_position_x = 0;//Is this redundant?
			queen_position_y = 0;
			target_position_x = indexToCoordinate(newi, newj)[0];
			target_position_y = indexToCoordinate(newi, newj)[1];
			printf("\nNew cell found! %d,%d\n", newi, newj);
			state = MoveNewRight;
		}
		else{
			printf("No new cell.\n");
		}
		drawcell(queen_position_x, queen_position_y,GREEN);
		drawBackground();
		break;
	case MoveNewRight:
		if (queen_position_x < target_position_x){
			queen_position_x++;
			glutPostRedisplay();
		}
		if (queen_position_x == target_position_x){
			state = MoveNewUp;
			glutPostRedisplay();
		}
		drawcell(queen_position_x, queen_position_y,GREEN);
		drawBackground();
		break;
	case MoveNewUp:
		if (queen_position_y < target_position_y){
			queen_position_y++;
			glutPostRedisplay();
		}
		if (queen_position_y == target_position_y){
			state = CheckConflict;
			glutPostRedisplay();
		}
		drawcell(queen_position_x, queen_position_y,GREEN);
		drawBackground();
		break;
	case CheckConflict:

		c = detectConflict(array, newi, newj);
		conflictArray[0] = c[0];
		conflictArray[1] = c[1];
		conflictArray[2] = c[2];

		if (conflictArray[0] == 0){
			printf("No conflict found.\n");
			state = FindHints;
			glutPostRedisplay();
		}
		else{
			printf("CONFLICT EXISTS!\n");
			state = MoveConflictHorizontal;
			queen_position_x = indexToCoordinate(conflictArray[1], conflictArray[2])[0];			
			queen_position_y = indexToCoordinate(conflictArray[1], conflictArray[2])[1];
			glutPostRedisplay();
		}
		drawcell(queen_position_x, queen_position_y,RED);
		drawBackground();
		break;
	case MoveConflictHorizontal:
		printf("Moving conflict horizontal.\n");

		setSelected(newi, newj, 0);
		if (queen_position_x < target_position_x){
			queen_position_x++;
		}
		if (queen_position_x > target_position_x){
			queen_position_x--;
		}
		if (queen_position_x == target_position_x){
			state = MoveConflictVertical;
		}

		glutPostRedisplay();
		drawcell(target_position_x, target_position_y,ORANGE);
		drawcell(queen_position_x, queen_position_y,RED);
		drawBackground();
		break;
	case MoveConflictVertical:
		if (queen_position_y < target_position_y){
			queen_position_y++;
		}
		if (queen_position_y > target_position_y){
			queen_position_y--;
		}
		if (queen_position_y == target_position_y){
			state = Killed;
		}
		glutPostRedisplay();
		drawcell(target_position_x, target_position_y,ORANGE);
		drawcell(queen_position_x, queen_position_y,RED);
		drawBackground();
		break;
	case Killed:
		target_position_x = indexToCoordinate(conflictArray[1], conflictArray[2])[0];
		target_position_y = indexToCoordinate(conflictArray[1], conflictArray[2])[1];
		queen_position_x = indexToCoordinate(newi, newj)[0];
		queen_position_y = indexToCoordinate(newi, newj)[1];
		state = MoveConflictVerticalBack;
		glutPostRedisplay();
		drawcell(queen_position_x, queen_position_y,GREEN);
		drawBackground();
		break;
	case MoveConflictVerticalBack:
		printf("queen positiony is:%d and targetpositiony is %d\n", queen_position_y, target_position_y);
		printf("moving conflict vertical back\n");
		if (queen_position_y < target_position_y){
			queen_position_y++;
		}
		if (queen_position_y > target_position_y){
			queen_position_y--;
		}
		if (queen_position_y == target_position_y){
			state = MoveConflictHorizontalBack;
		}
		glutPostRedisplay();
		drawcell(queen_position_x, queen_position_y,GREEN);
		drawBackground();
		break;
	case MoveConflictHorizontalBack:
		printf("Moving conflict horizontal back\n");
		if (queen_position_x < target_position_x){
			queen_position_x++;
		}
		if (queen_position_x > target_position_x){
			queen_position_x--;
		}
		if (queen_position_x == target_position_x){
			setSelected(newi, newj, 1);
			state = FindHints;
		}
		glutPostRedisplay();
		drawcell(queen_position_x, queen_position_y,GREEN);
		drawBackground();
		
		break;
	case FindHints:
		findHints();
		if (selected_cells_count < 8){
			state = Done;//IS THIS CORRECT?
			queen_position_x = 0;
			queen_position_y = 0;
		}
		else{
			state = Done;
		}
		glutPostRedisplay();
		//drawcell(queen_position_x, queen_position_y); ?NOT necessary
		drawBackground();
		break;
	case Done: break;
	default:
		break;
	}
}

/******************************************************** DISPLAY SECTION *************************************************************/
void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);

	glColor3f(0, 1, 0);


	current_cell[0] = coordinateToIndex(mouse_x, mouse_y)[0];
	current_cell[1] = coordinateToIndex(mouse_x, mouse_y)[1];
	//	printf(".........................................................\n");
	if ((selected_cells_count < 8) && !CellinSelectedCells(current_cell[0], current_cell[1]))
	{ if (state == Done){
		state = ToBeStarted;
		printf("Set state to started. State is:%d", state);
		}
		//printf("Calling display solution!State is %d.\n", state);
		//translatequeen(current_cell[0], current_cell[1]);
		displaySolution();
	}
	glFlush();

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

#Program does not handle window resizing.

#First stage:
Order:
Place first queen immediately as user clicks on a valid cell. Overlap remaining 7 queens at window origin. Move the queens one by one,
(remember to skip the currently placed ones), and final queen should not leave any trace. Queens first move along x, then along y.

STAGE 1 COMPLETED!!!!!!!!!

#Second stage:
User places a queen in the first selection. On cell selection, queens move from the origin to the cell. DONE.

All cells which can be a possible solution are highlighted. DONE.

When conflicting queens are added, the current queen turns red, and translates, along x, and then along y (is diagonal, or z possible?),
moves over to the conflicting queen and kills it, and translates back to original position. After no more choices are left, the computer
automatically places the remaining queens.

The program will be sufficiently complex after the second is implemented.

*/

