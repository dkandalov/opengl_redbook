#include <stdio.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

static GLfloat spin = 0;

void display() {
    glEnable(GL_DEPTH_TEST); // without this planet will always be visible (even when behind the sun)

    // adding light
    GLfloat sun_light_position[] = {1.0, 1.0, -1.0, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL); // without this line objects' color won't be used with lights

    glClearColor(0.1, 0.1, 0.13, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // sun
    glPushMatrix();
        glRotatef(spin, 0, 1, 0);
        glColor3f(1.0, 1.0, 0.0);
        glutWireSphere(0.2, 10, 10);
    glPopMatrix();

    // planet
    glPushMatrix();
        glRotatef(-10, 1, 0, 0); // incline for better view TODO should be in projection
        glRotatef(spin, 0, 1, 0);
        glTranslatef(0.9, 0, 0);
        glRotatef(spin * 3, 0, 1, 0);

        glColor3f(1.0, 1.0, 1.0);
        glutWireSphere(0.1, 10, 10);

        // moon
        glRotatef(spin, 0, 1, 0);
        glTranslatef(0.2, 0, 0);
        glRotatef(spin * 4, 0, 1, 0);
        glutWireSphere(0.02, 10, 10);

    glPopMatrix();

    glFlush();
}

void rotate() {
    spin = spin + 0.04;
    if (spin > 360) {
        spin = 0;
    }
    display();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH); //not sure if it's necessary for this example
    glutInitWindowPosition(400, 200);
    glutInitWindowSize(400, 400);
    glutCreateWindow("planet and sun");

    glutDisplayFunc(display);
    glutIdleFunc(rotate);
    glutMainLoop();

    return 0;
}