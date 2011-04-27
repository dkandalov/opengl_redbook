#include <stdio.h>
#include <math.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#define X .525731112119133606
#define Z .850650808352039932

static GLfloat vdata[12][3] = { {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z}, {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X}, {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0}
};
static GLint tindices[20][3] = { {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1}, {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3}, {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6}, {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} };


void normalize(float v[3]) {
    GLfloat d = sqrt(v[1]*v[1]+v[2]*v[2]+v[3]*v[3]);
    if (d == 0.0) {
        printf("zero length vector");
        return;
    }
    v[1] /= d; v[2] /= d; v[3] /= d;
}

void normcrossprod(float v1[3], float v2[3], float out[3]) {
    GLint i, j;
    GLfloat length;
    out[0] = v1[1]*v2[2] - v1[2]*v2[1];
    out[1] = v1[2]*v2[0] - v1[0]*v2[2];
    out[2] = v1[0]*v2[1] - v1[1]*v2[0];
    normalize(out);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    int i, j;
    for (i = 0; i < 20; i++) {
//        glColor3f(i * 0.05, i * 0.05, 123);
        GLfloat d1[3], d2[3], norm[3];
        for (j = 0; j < 3; j++) {
            d1[j] = vdata[tindices[i][0]][j] - vdata[tindices[i][1]][j];
            d2[j] = vdata[tindices[i][1]][j] - vdata[tindices[i][2]][j];
        }
        normcrossprod(d1, d2, norm);
        glNormal3fv(norm);

        glBegin(GL_TRIANGLES);
        glVertex3fv(&vdata[tindices[i][0]][0]);
        glVertex3fv(&vdata[tindices[i][1]][0]);
        glVertex3fv(&vdata[tindices[i][2]][0]);
        glEnd();
    }

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(400, 400);
    glutInitWindowSize(300, 300);
    glutCreateWindow("icosahedron");

    init();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}