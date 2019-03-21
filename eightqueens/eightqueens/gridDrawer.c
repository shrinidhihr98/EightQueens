#include<Windows.h>
#include<GL/glut.h>
#include<stdio.h>

//Global Variables: Stay same throughout execution.
int window_height = 600;


int bottom = 100;
int left = 100;
int increment = 50;
int size = 8;
int mouse_x = 0;
int mouse_y = 0;
int actualmousex = 0;
int actualmousey = 0;

void drawline(int x1, int y1, int x2, int y2){
	glBegin(GL_LINES);

	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEnd();

}

void drawcell(int x, int y, int increment){
	printf("Drawcell: Drawing cell at x,y: %d,%d\n", x, y);
	glBegin(GL_QUADS);
	glVertex2i(x, y);
	glVertex2i(x + increment, y);
	glVertex2i(x + increment, y + increment);
	glVertex2i(x, y + increment);
	glEnd();

}

void highlightCell(){
	int right = left + (size * increment);
	int top = bottom + (size * increment);

	int cellx = mouse_x / 50;
	int celly = mouse_y / 50;

	int cellxindex = cellx - 2; 
	int cellyindex = celly - 2;
	printf("HighlightCell():\n\tMouse_x, mouse_y: %d,%d\n\tHighlighted cell wrt window: %d,%d\n", mouse_x,mouse_y,cellxindex, cellyindex);

	int x =  (cellx* increment);
	int y =  (celly * increment);

	

	if (x >= left && x < right && y >= bottom && y < top){
		drawcell(x, y, increment);		
	}
	else{
		printf("Grid left, bottom, top, right: %d, %d, %d, %d\n", left, bottom, top, right);
		printf("Cannot highlight: Mouse at %d,%d clicked outside grid!\n",x,y);
	}
}

void drawgrid(int increment){
	int right = left + (size * increment);
	int top = bottom + (size * increment);


	for (int x = left; x <= right; x += increment){
		drawline(x, bottom, x, top);
		printf("Drawing lines along y: %d, %d ... %d, %d\n", x, bottom, x, top);

	}


	for (int y = bottom; y <= top; y += increment){
		drawline(left, y, right, y);
		printf("Drawing lines along x: %d, %d ... %d, %d\n", left, y, right, y);
	}


}


void mouse(int button, int state, int x, int y){
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		actualmousex = x;
		actualmousey = y;
		mouse_x = x;
		mouse_y = window_height - y;
		if (mouse_y < 0){
			mouse_y = mouse_y*-1;
		}
		printf("Left Mouse button clicked! x,y: %d,%d\n", mouse_x, mouse_y);
		printf("Mouse Coordinates are: %d,%d", x, y);
		
	}
	glutPostRedisplay();
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
	//glLoadIdentity();
	glColor3f(0, 1, 0);


	drawgrid(50);

	printf("Display():\n\tActual Mousex, ActualMousey: %d,%d\n", actualmousex, actualmousey);
	highlightCell();
	
	//glutSwapBuffers();
	glFlush();
	
	printf("=========================================================\n");
}


void main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(window_height, window_height);
	glutCreateWindow("Sample");
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, window_height, 0, window_height);
	glMatrixMode(GL_MODELVIEW);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMainLoop();
}

