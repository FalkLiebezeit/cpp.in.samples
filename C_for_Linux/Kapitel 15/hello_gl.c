/* hello_gl.c */
#include <GL/glut.h>
#include <stdlib.h>

static GLfloat spin = 0.0;
static GLfloat spin_tick = 0.5;
static GLint win;

void OpenGLInit(void) {
	glClearColor (1.0, 1.0, 1.0, 0.0);
	glShadeModel (GL_FLAT);
}

void OpenGLDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(spin, 0.0, 0.0, 1.0);
	glColor3f (1.0, 0.0, 0.0);
	glRectf(-25.0, -25.0, 25.0, 25.0);
	glPopMatrix();
	glutSwapBuffers();
}

void OpenGLSpinDisplay(void) {
	spin = spin + spin_tick;
	if (spin > 360.0)
		spin = spin - 360.0;
	glutPostRedisplay();
}

void OpenGLReshape(int w, int h) {
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Mausereignisse behandeln
void mouse(int button, int state, int x, int y) {
	switch (button) {
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN)
				glutIdleFunc(OpenGLSpinDisplay);
		break;
		case GLUT_RIGHT_BUTTON:
			if (state == GLUT_DOWN)
				glutIdleFunc(NULL);
		break;
		default: break;
	}
}

// Tastatur-Ereignisse behandeln
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case '+':
			if( spin_tick < 5.0 ) spin_tick += 0.5;
				glutIdleFunc(OpenGLSpinDisplay);
		break;
		case '-':
			if( spin_tick > -5.0 ) spin_tick -= 0.5;
				glutIdleFunc(OpenGLSpinDisplay);
		break;
		default: break;
	}
}

// Funktions-Tastatur-Ereignisse behandeln
void none_ascii_keyboard(int key, int x, int y) {
	switch (key) {
		case  GLUT_KEY_F1:
			glutDestroyWindow(win);
		break;
		default: break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (250, 250);
	glutInitWindowPosition (100, 100);
	win = glutCreateWindow ("Und es bewegt sich doch ...");
	OpenGLInit ();
	glutDisplayFunc(OpenGLDisplay);
	glutReshapeFunc(OpenGLReshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(none_ascii_keyboard);
	glutMainLoop();
	return 0;
}
