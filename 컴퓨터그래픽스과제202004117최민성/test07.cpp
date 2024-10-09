#include <GL/freeglut.h>
#include <math.h>


int FlatShaded = 0;
int Wireframed = 0;


float camX = 0.0f, camY = 0.0f, camZ = -5.0f; 
float camDistance = 5.0f; 
float camAngleX = 0.0f; 
float camAngleY = 0.0f;

void InitLight() {
	GLfloat mat_diffuse[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_shininess[] = { 15.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light_position[] = { -3, 6, 3.0, 0.0 };
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void MyMouseMove(int button, int state, int x, int y) {
	glutPostRedisplay();
}

void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'q': case 'Q': case '\033':
		exit(0);
		break;
	case 's':
		if (FlatShaded) {
			FlatShaded = 0;
			glShadeModel(GL_SMOOTH);

		}
		else {
			FlatShaded = 1;
			glShadeModel(GL_FLAT);
		}
		glutPostRedisplay();
		break;
	}
}

void MySpecialKeyboard(int key, int x, int y) {
	
	switch (key) {
	case GLUT_KEY_UP:
		camAngleY += 0.1f; 
		camZ = camDistance * cos(camAngleY);
		camY = camDistance * sin(camAngleY);
		break;
	case GLUT_KEY_DOWN:
		camAngleY -= 0.1f;
		camZ = camDistance * cos(camAngleY);
		camY = camDistance * sin(camAngleY);
		break;
	case GLUT_KEY_LEFT:
		camAngleX -= 0.1f;
		break;
	case GLUT_KEY_RIGHT:
		camAngleX += 0.1f;
		break;
	}
	glutPostRedisplay(); 
}


void leg1()
{
	glPushMatrix();
	glTranslatef(1.5f, 0.4f, -0.5f);
	glScalef(0.1, 1.2, 0.1);
	glutSolidCube(1.0);
	glPopMatrix();
}
void leg2()
{
	glPushMatrix();
	glTranslatef(-1.5f,0.4f, 0.5f);
	glScalef(0.1, 1.2, 0.1);
	glutSolidCube(1.0);
	glPopMatrix();
}
void leg3()
{
	glPushMatrix();
	glTranslatef(-1.5f, 0.4f, -0.5f);

	glScalef(0.1, 1.2, 0.1);
	glutSolidCube(1.0);
	glPopMatrix();
}
void leg4()
{
	glPushMatrix();
	glTranslatef(1.5f, 0.4f, 0.5f);
	glScalef(0.1, 1.2, 0.1);
	glutSolidCube(1.0);
	glPopMatrix();
}
void floor1()
{
	glPushMatrix();
	glTranslatef(0, -0.2f, 0);
	glScalef(4, 0.1f, 2);
	glutSolidCube(1.0);
	glPopMatrix();
}
void surface()
{
	glPushMatrix();
	glTranslatef(0, 1.0f, 0);
	glScalef(3, 0.1f, 1);
	glutSolidCube(1.0);
	glPopMatrix();
}
void table()
{

	surface();
	leg1();
	leg2();
	leg3();
	leg4();
	floor1();
}



void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camX = camDistance * sin(camAngleX);
	camZ = camDistance * cos(camAngleX);

	

	gluLookAt(camX, camY, camZ,  
		0, 0, 0, 
		0.0, 1.0, 0.0);
	table();

	glPushMatrix();
	glTranslatef(1.1f, 1.12f, 0.0f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glutSolidTorus(0.09, 0.2,  10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.1f, 1.24f, 0.0f);
	glutSolidSphere(0.2, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 1.2f, 0.0f);
	glutSolidTeapot(0.2);
	glPopMatrix();

	glFlush();


}


void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-2.0, 2.0, -2.0, 2.0, -100.0, 100.0);
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("fff");
	glClearColor(0.4, 0.4, 0.4, 0.0);
	InitLight();
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutSpecialFunc(MySpecialKeyboard);
	glutMouseFunc(MyMouseMove);
	glutReshapeFunc(MyReshape);
	glutMainLoop();
}