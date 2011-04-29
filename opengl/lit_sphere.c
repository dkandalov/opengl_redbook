#include <stdio.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

static GLfloat spin = 0.0;
static int counter = 0;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        glNormal3f(1,1,1);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 2);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 2, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(2, 0, 0);
    glEnd();

    glPushMatrix();

        glRotatef(spin, 1,1,0);
        glTranslatef(0.5, 0.5 ,-1);
        glutSolidSphere(0.5, 200, 200);
//        glRectf(-1.0, -1.0, 1.0, 1.0);

    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void init() {
//    return;
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat light_ambient[] = { 0.0, 0.0, 1.0, 1.0};

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glEnable(GL_LIGHT0);

    GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light1_diffuse[] = { 1.0, 0.0, 1.0, 1.0 };
    GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light1_position[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat spot_direction[] = { -1.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
//    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
//    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);
//    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
//    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
//    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);
    glEnable(GL_LIGHT1);

    glEnable(GL_LIGHTING);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
}

void myReshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glRotatef(-25, 1,1,0);

    if (w <= h)
        glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w, 1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
    else
        glOrtho (-1.5*(GLfloat)w/(GLfloat)h, 1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void onIdle() {
    counter++;
    spin = counter * 0.5;
    if (spin > 360) {
        spin = spin - 360;
        counter = 0;
    }
    display();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(400, 400);
    glutInitWindowSize(300, 300);
    glutCreateWindow("lit sphere");

    init();
    glutReshapeFunc(myReshape);
    glutIdleFunc(onIdle);
    glutDisplayFunc(display);

    glutMainLoop();

    printf("Is this line never reached?\n");
    return 0;
}