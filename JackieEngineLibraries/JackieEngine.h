#pragma once

#include <math.h>

/*
** Define Trigonometric Functions that use Degrees instead of Radians
*/
#define cosd(x)  cos(x*0.017453293)
#define sind(x)  sin(x*0.017453293)
#define tand(x)  tan(x*0.017453293)
#define acosd(x) acos(x*0.017453293)
#define asind(x) asin(x*0.017453293)
#define atand(x) atan(x*0.017453293)


/*
** Define a Cube
*/
float CubeMesh[12 * 3 * 3] = {
  1.0f, 1.0f, 1.0f,  4.0f, 1.0f, 1.0f,  1.0f, 4.0f, 1.0f,  //near
  1.0f, 4.0f, 1.0f,  4.0f, 4.0f, 1.0f,  4.0f, 1.0f, 1.0f,  //near
  1.0f, 1.0f, 4.0f,  4.0f, 1.0f, 4.0f,  1.0f, 4.0f, 4.0f,  //far
  1.0f, 4.0f, 4.0f,  4.0f, 4.0f, 4.0f,  4.0f, 1.0f, 4.0f,  //far
  1.0f, 4.0f, 4.0f,  1.0f, 1.0f, 4.0f,  1.0f, 1.0f, 1.0f,  //left
  1.0f, 4.0f, 4.0f,  1.0f, 4.0f, 1.0f,  1.0f, 1.0f, 1.0f,  //left
  4.0f, 4.0f, 4.0f,  4.0f, 1.0f, 4.0f,  4.0f, 1.0f, 1.0f,  //right
  4.0f, 4.0f, 4.0f,  4.0f, 4.0f, 1.0f,  4.0f, 1.0f, 1.0f,  //right
  1.0f, 4.0f, 1.0f,  1.0f, 4.0f, 4.0f,  4.0f, 4.0f, 4.0f,  //up
  1.0f, 4.0f, 1.0f,  4.0f, 4.0f, 1.0f,  4.0f, 4.0f, 4.0f,  //up
  1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 4.0f,  4.0f, 1.0f, 4.0f,  //down
  1.0f, 1.0f, 1.0f,  4.0f, 1.0f, 1.0f,  4.0f, 1.0f, 4.0f   //down
};
