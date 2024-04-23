#ifndef GLPLAYER_H
#define GLPLAYER_H

#include<common.h>
#include<GLTexture.h>
#include<GLTimer.h>
#include<map>
#include<projectile.h>

class GLPlayer
{
    public:
        GLPlayer();
        virtual ~GLPlayer();

        enum {STAND, WALKLEFT,WALKRIGHT, WALKDOWN, WALKUP, RUN, JUMP, ATTACK, ATTACKLEFT, ATTACKDOWN, ATTACKUP};
        vector<vector<float>> bounds;

        GLTexture *texture = new GLTexture();
        GLTimer   *myTime = new GLTimer();

        void initPlayer(int,int,char* fileName); // number of x, y frames
        void drawPlayer();
        void actions();
        void update();
        void boundsCheck(int);
        void performAttack();
        void performAttackLeft();
        void performAttackDown();
        void performAttackUp();

        bool hit_check(projectile *projList);

        vec3 getPos();

        vec3 plPosition;
        vec3 plScale;

        vec3 vert[4];
        float xMax,xMin,yMax,yMin;
        int framesX,framesY;

        int actionTrigger;  // for load actions

        std::map<int, bool> keyStates; // Hash map for O(1) lookup.

    protected:

    private:
};

#endif // GLPLAYER_H
