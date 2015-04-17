/*
 * Simplifies including OpenGL headers.
 *
 *  Created on: Jan 3, 2011
 *      Author: marc.wren
 */

#ifndef SFOPENGL_H_
#define SFOPENGL_H_

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
  #include <windows.h>
#endif
#include <GL/gl.h>
#include "glu.h"
//#include <GL/glu.h>
//#include <GL/glut.h>
#endif

#endif /* SFOPENGL_H_ */
