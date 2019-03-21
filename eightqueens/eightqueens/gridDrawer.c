#include<Windows.h>
#include<GL/glut.h>
#include<stdio.h>

//Global Variables: Stay same throughout execution.
int bottom = 100;
int left = 100;
int increment = 50;
int size = 8;


void drawline(int x1, int y1, int x2, int y2){
	glBegin(GL_LINES);

	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEnd();

}

void drawcell(int x, int y, int increment){
	glBegin(GL_QUADS);
	glVertex2i(x, y);
	glVertex2i(x + increment, y);
	glVertex2i(x + increment, y + increment);
	glVertex2i(x, y + increment);
	glEnd();

}

void highlightCell(int cellx, int celly){
	int x = left + (cellx* increment);
	int y = bottom + (celly * increment);
	drawcell(x, y, increment);
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

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
	glColor3f(0, 1, 0);


	drawgrid(50);
	highlightCell(2, 2);

	glFlush();
}


void main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Sample");
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 800, 0, 800);
	glutDisplayFunc(display);
	glutMainLoop();
}

