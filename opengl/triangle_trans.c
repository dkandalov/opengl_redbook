#include <OpenGL/gl.h>
#include <GLUT/glut.h>

void draw_triangle() {
    glBegin(GL_LINE_STRIP);
    glVertex3f(-0.5, -0.5, 0);
    glVertex3f(0.5, -0.5, 0);
    glVertex3f(0.0, 0.5, 0);
    glVertex3f(-0.5, -0.5, 0);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    glLoadIdentity();
    draw_triangle();

    glEnable(GL_LINE_STIPPLE);

    glLineStipple(1, 0xF0F0);
    glLoadIdentity();
    glTranslatef(-0.1, 0.1, 0.0);
    draw_triangle();

    glLineStipple(1, 0xF00F);
    glLoadIdentity();
    glScalef(1.5, 0.5, 1.0);
    draw_triangle();

    glLineStipple(1, 0x8888);
    glLoadIdentity();
    glRotatef (30.0, 0.0, 0.0, 1.0);
    draw_triangle ();

    glDisable (GL_LINE_STIPPLE);

    glFlush();
}

void myReshape(GLsizei w, GLsizei h) {
//    glMatrixMode (GL_PROJECTION);
//    glLoadIdentity ();
//    glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0); /* transformation */
    glMatrixMode (GL_MODELVIEW); /* back to modelview matrix */
    glViewport (0, 0, w, h);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("triangle transformation");

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);

    glutDisplayFunc(display);
    glutReshapeFunc(myReshape);
    glutMainLoop();

    return 0;   /* ISO C requires main to return int. */
}