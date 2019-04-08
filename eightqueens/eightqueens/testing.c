#include<Windows.h>
#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void drawstring_font1(char *a, int x, int y)
{
	glRasterPos2i(x, y);
	for (int i = 0; a[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, a[i]);
}
void drawstring_font2(char *a, int x, int y)
{
	glRasterPos2i(x, y);
	for (int i = 0; a[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, a[i]);
}
void drawstring_font3(char *a, int x, int y)
{
	glRasterPos2i(x, y);
	for (int i = 0; a[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, a[i]);
}
void drawstring_font4(char *a, int x, int y)
{
	glRasterPos2i(x, y);
	for (int i = 0; a[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, a[i]);
}

void drawstring_font5(char *a, int x, int y)
{
	glRasterPos2i(x, y);
	for (int i = 0; a[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, a[i]);
}

char* makePossilitiesString(char* buffer, int possibleSolutionsCount){
		char num[4] = "0";
		_itoa_s(possibleSolutionsCount,num,4,10);
		printf("Num char array is: %s\n", num);
		char stringpart[30] = "Possible solutions: ";
		printf("Size of stringpart is: %d\n", strlen(stringpart));
		//char buffer[100] ;
		//{ 'Possible solutions: ', num[0], '\0' }
		unsigned int i = 0;
		buffer = malloc(sizeof(char) * 100);
		for (i = 0; i < strlen(stringpart); i++){
			buffer[i] = stringpart[i];
		}
		printf("i is:%d\n", i);
		if (possibleSolutionsCount < 10){
			buffer[i] = num[0];
			buffer[i + 1] = '\0';
		}
		else{
			buffer[i] = num[0];
			buffer[i + 1] = num[1];
			buffer[i + 2] = '\0';
		}
		printf("%s\n", buffer);
		return buffer;
}
void try_text(){
	int possibleSolutionsCount = 4;

}

void drawCircle(float xc, float yc, float radius, GLfloat* color){
	printf("Drawing circle!");
	float angle = 0;
	float x, y = 0;
	glColor3fv(color);
	glBegin(GL_POLYGON);
	for (angle = 0; angle <= 100; angle += 0.2){
		x = xc + radius*cos(angle);
		y = yc + radius*sin(angle);
		glVertex2f(x, y);
	}
	printf("finished");
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	char* buffer = "";
	buffer = makePossilitiesString(buffer, 0);
	printf("Buffer is: \n%s\n",buffer);
	drawstring_font2(buffer, 50, 50);
	//drawstring_font1("Computer Graphics", 200, 200);
	//drawstring_font2("Computer Graphics", 200, 250);
	//drawstring_font3("Computer Graphics", 200, 300);
	//drawstring_font4("Computer Graphics", 200, 350);
	//drawstring_font5("Computer Graphics", 200, 400);

	/*
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 0, 0);
	glVertex2i(300, 100);
	//glColor3i(0, 1, 0);
	glVertex2i(350, 150);

	//glColor3f(0, 0, 1);
	glVertex2i(350, 100);

	//glColor3f(1, 0, 0);
	glVertex2i(350, 50);

	glEnd();
	*/
	GLfloat RED[3] = { 1, 0, 0 };
	drawCircle(300, 300, 50, RED);
//	drawButton(100,100,100,50);
	glFlush();
}

void main()
{
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Text_Display");
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 500, 0, 500);
	glutDisplayFunc(display);
	glutMainLoop();
}

