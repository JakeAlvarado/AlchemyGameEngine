#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED


#include<windows.h>
#include<iostream>
#include<gl/gl.h>
#include<GL/glut.h>
#include<time.h>
#include<math.h>
#include <vector>
#include <unordered_map>
#include <chrono>

#include<SOIL.h>
#include<SNDS/irrKlang.h>

#define N_PROJ 10
#define MAX_N_ENEMIES 10


using namespace std;
using namespace irrklang;
using namespace chrono;



typedef struct{   // shader positions in 3D
    float x;
    float y;
    float z;
    float w;
}vec4;


typedef struct{  //  positions in 3D graphics
    float x;
    float y;
    float z;
}vec3;

typedef struct{  //  positions in 3D graphics
    float x;
    float y;
}vec2;

enum element
{
  AIR,
  EARTH,
  WATER,
  FIRE
};

#endif // COMMON_H_INCLUDED
