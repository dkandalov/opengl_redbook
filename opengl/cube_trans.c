#include <OpenGL/gl.h>
#include <GLUT/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);

    glLoadIdentity ();
    glTranslatef (0.0, 0.0, -5.0); /* viewing transformation */
    glScalef (1.0, 2.0, 1.0);	/* modeling transformation */
    glRotatef(5, 0, 0, 1);

    glutWireCube(1.0);

    glFlush();
}

void myReshape(GLsizei w, GLsizei h) {
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0); /* projection transformation */

    glMatrixMode (GL_MODELVIEW); /* back to modelview matrix */
    glViewport (0, 0, w, h);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("cube transformation");

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);

    glutDisplayFunc(display);
    glutReshapeFunc(myReshape);
    glutMainLoop();

    return 0;   /* ISO C requires main to return int. */
}