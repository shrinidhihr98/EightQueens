#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#include<time.h>

int done = 0; 
float t = 0;

int body_1_position[2] = { 100, 100 };
int body_2_position[2] = { 300, 300 };

int body_1_position_initial[2] = { 100, 100 };
int body_2_position_initial[2] = { 500, 300 };


int body_1_velocity[3] = { 0, 0, 0 }; //x,y,z components.
int body_2_velocity[3] = { 0, 0, 0 }; //x,y,z components.

int body_1_velocity_initial[3] = { 0, 0, 0 }; //x,y,z components.
int body_2_velocity_initial[3] = { 0, 0, 0 }; //x,y,z components.


float body_1_acceleration = 0.5;
float body_2_acceleration = -0.5;
GLfloat RED[3] = { 1, 0, 0 };

void updatePosition(){

	/*
	Put in the equations of motion for 
	*/

	/*
	if (body_1_x_pos < final_1_x_pos){
		body_1_x_pos++;
	}
	*/



	body_1_position[0] = body_1_position_initial[0] + (int)((body_1_velocity_initial[0] * t) + (0.5 * body_1_acceleration * t * t));
	body_2_position[0] = body_2_position_initial[0] + (int)((body_2_velocity_initial[0] * t) + (0.5 * body_2_acceleration * t * t));

	t+=0.1;
	
}

void drawCircle(float xc, float yc, float radius, GLfloat* color){
	float x, y;
	glColor3fv(color);
	glBegin(GL_POLYGON);
	for (float angle = 0; angle < 360; angle+=1){
		x = xc + (radius * cos(angle));
		y = yc + (radius * sin(angle));
		glVertex2f(x, y);
	}
	glEnd();
	
}

void translateBody(){
	if (1){
		updatePosition();
		drawCircle(body_1_position[0], body_1_position[1], 50, RED);
		drawCircle(body_2_position[0], body_2_position[1], 5, RED);
		glFlush();
	}
	else{
		done = 1;
	}
		
}

void timerfunc(int value)    // handle animation 
{
	
	if(done == 0)          // as in your originial loop 
		glutTimerFunc(10, timerfunc, 100);  // plan next occurence
	glutPostRedisplay();     // redraw the window
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);
	translateBody();
}

/*
Module 3 and module 4 upto classes and functions.
Write a definition for a class circle with attributes center and radius where center is a point object and radius is a number.
Instantiate a circle with center 150,100 and radius 75. Write a function with name point_in_circle that takes a circle and point
and returns true if point lies in or on boundary of the circle. Write a function name rect_in circle that takes circle and a rectangle
and returns true if rectangle lies in boundary of a circle.
*/
void main(){
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Collsions");
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 800, 0, 800);
	glutDisplayFunc(display);
	glutTimerFunc(10, timerfunc, 100);       // call a timer function 
	glutMainLoop();
}