/**
 * Anova IT Consulting 2011
 *
 * This file is licensed under the GPL version 3.
 * Please refer to the URL http://www.gnu.org/licenses/gpl-3.0.html for details.
 */

#include <stdlib.h>
#include <GLES/gl.h>

#define one 1.0f

typedef unsigned char byte;

extern void jni_printf(char *format, ...);

// Cube
static GLfloat vertices[24] = {
		-one, -one, -one,
		 one, -one, -one,
		 one,  one, -one,
		-one,  one, -one,
		-one, -one,  one,
		 one, -one,  one,
		 one,  one,  one,
		-one,  one,  one,
};

static GLfloat colors[] = {
		0,   0,   0,   one,
		one, 0,   0,   one,
		one, one, 0,   one,
		0,   one, 0,   one,
		0,   0,   one, one,
		one, 0,   one, one,
		one, one, one, one,
		0,   one, one, one,
};

static byte indices[] = {
		0, 4, 5,    0, 5, 1,
		1, 5, 6,    1, 6, 2,
		2, 6, 7,    2, 7, 3,
		3, 7, 4,    3, 4, 0,
		4, 7, 6,    4, 6, 5,
		3, 0, 1,    3, 1, 2
};

void Cube_draw() {
	glFrontFace(GL_CW);

	glVertexPointer(3, GL_FLOAT, 0, vertices); 
	glColorPointer(4, GL_FLOAT, 0 , colors); 

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);
}
