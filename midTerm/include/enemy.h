#ifndef ENEMY_H
#define ENEMY_H
#include <common.h>
#include <GLTexture.h>
#include <GLTimer.h>
#include <projectile.h>
#include<random>
#include<time.h>
#include <GLChrono.h>

#include <GLTimer.h>

#include <random>

class enemy
{
    public:
        enemy(int t, projectile* proj);
        virtual ~enemy();

        int type;

        projectile *gameProjectiles;


        char *water_image_path = "images/enemies/WaterElemental.png";
        char *earth_image_path = "images/enemies/EarthElemental.png";
        char *fire_image_path = "images/enemies/FireElemental.png";
        char *air_image_path = "images/enemies/AirElemental.png";

        bool dir = true;

        clock_t attackTimer;

        vec3 spriteShape;

        GLTexture *enemyTex = new GLTexture();
        GLTimer   *myTime = new GLTimer();
        GLTimer   *moveTime = new GLTimer();

        GLChrono *myTimeC = new GLChrono();
        GLChrono *moveTimeC = new GLChrono();

        bool isLive=false;

        int melleCounter = 0;

        vec3 pos;
        vec3 Target;

        vec3 vert[4];

        void setTarget(vec3 t);

        void initEnemy(float x_init, float y_init, int t);
        void drawEnemy();
        void updateFrame();
        void updatePos();
        void killEnemy();
        bool hit_check(projectile *projList);

        int n_frames;
        int frame;

        float xMin =0;
        float xMax =0.25;
        float yMin=0;
        float yMax=1;

        float enemySpeed = 0.002;






    protected:

    private:
};

#endif // ENEMY_H
