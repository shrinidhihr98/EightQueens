/*

#include<Windows.h>
#include<GL/glut.h>

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

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	drawstring_font1("Computer Graphics", 200, 200);
	drawstring_font2("Computer Graphics", 200, 250);
	drawstring_font3("Computer Graphics", 200, 300);
	drawstring_font4("Computer Graphics", 200, 350);
	drawstring_font5("Computer Graphics", 200, 400);



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

*/