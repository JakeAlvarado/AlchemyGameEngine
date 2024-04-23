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

#include<SOIL.h>

#define N_PROJ 10
#define MAX_N_ENEMIES 10


using namespace std;




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
typedef struct{

    vec2 sPos;
    vec2 tPos;
    vec2 pos;

    float speed=0.01;
    int type; // this will determine which tex to use

    vec2 v;

    clock_t stTime;
    bool isLive = false;

} proj;

#endif // COMMON_H_INCLUDED
