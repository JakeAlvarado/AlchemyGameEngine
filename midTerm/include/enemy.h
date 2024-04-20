#ifndef ENEMY_H
#define ENEMY_H
#include <common.h>
#include <GLTexture.h>
#include <GLTimer.h>

#include <random>

class enemy
{
    public:
        enemy(int t);
        virtual ~enemy();

        int type;



        char *water_image_path = "images/enemies/WaterElemental.png";
        char *earth_image_path = "images/enemies/EarthElemental.png";
        char *fire_image_path = "images/enemies/FireElemental.png";
        char *air_image_path = "images/enemies/AirElemental.png";

        vec3 spriteShape;

        GLTexture *enemyTex = new GLTexture();
        GLTimer   *myTime = new GLTimer();
        GLTimer   *moveTime = new GLTimer();

        vec3 pos;
        vec3 Target;

        vec3 vert[4];

        void setTarget(vec3 t);

        void initEnemy();
        void drawEnemy();
        void updateFrame();
        void updatePos();


        int n_frames;
        int frame;

        float xMin =0;
        float xMax =0.25;
        float yMin=0;
        float yMax=1;






    protected:

    private:
};

#endif // ENEMY_H
