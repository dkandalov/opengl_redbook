#include <stdio.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

static GLfloat spin = 0.0;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT); 
    glPushMatrix();
    glRotatef(spin, 0.0, 0.0, 1.0); 
    glRectf(-25.0, -25.0, 25.0, 25.0);
    glBegin(GL_POINTS);
//        glColor3f(1.0, 1.0, 0.0);
        glVertex3f (25, 25, 0.0);
        glVertex3f (75, 25, 0.0);
        glVertex3f (75, 75, 0.0);
        glVertex3f (25, 75, 0.0);
    glEnd();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void spinDisplay(void) {
    spin = spin + 0.05;
    if (spin > 360.0) spin = spin - 360.0;
    display();
}

void myReshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h)
        glOrtho(-50.0, 50.0, -50.0 * (GLfloat)h / (GLfloat)w, 50.0 * (GLfloat)h / (GLfloat)w, -1.0, 1.0);
    else
        glOrtho(-50.0 * (GLfloat)w / (GLfloat)h, 50.0 * (GLfloat)w / (GLfloat)h, -50.0, 50.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glShadeModel(GL_FLAT);
    glPointSize(4.0);
}

void onMouseClick(int button, int state, int x, int y) {
    if (button == 0)
        glutIdleFunc(spinDisplay);
    else
        glutIdleFunc(0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(400, 400);
    glutInitWindowSize(300, 300);
    glutCreateWindow("square");

    init();
    glutReshapeFunc(myReshape);
//    glutIdleFunc(spinDisplay);
    glutMouseFunc(onMouseClick);

    glutDisplayFunc(display);
    glutMainLoop();

    printf("Is this line never reached?\n");
    return 0;
}