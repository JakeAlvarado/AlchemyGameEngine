#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <GLTexture.h>
#include <common.h>

#define N_PROJ 10

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

class projectile
{
    public:
        projectile();
        virtual ~projectile();



        GLTexture *projTex = new GLTexture();
        GLTexture *charProjTex = new GLTexture();
        GLTexture *enemProjTex = new GLTexture();

        proj projArr[N_PROJ]; // increase this value to handle more projectiles


        int idx = 0;

        void initProj();

        void shoot_projectile(int type, float tx, float ty, float sx, float sy); // what type of projectile to draw and positions
        void draw_projectiles();

        void move_projectiles(int i);




    protected:

    private:
};

#endif // PROJECTILE_H
