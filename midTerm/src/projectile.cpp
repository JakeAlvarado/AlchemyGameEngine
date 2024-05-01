#include "projectile.h"

projectile::projectile()
{

}

projectile::~projectile()
{
    //dtor
}
void projectile::initProj()
{
    projTex->loadTexture("images/cannon_ball.png");
    charProjTex->loadTexture("images/cannon_ball.png");
    enemProjTex->loadTexture("images/fire_ball.png");
    hit_check_clock = chrono::steady_clock::now();

}

void projectile::shoot_projectile(int type, float tx, float ty, float sx, float sy)
{


    projArr[idx].isLive=true;
    projArr[idx].stTime=clock();
    projArr[idx].sPos.x=sx;
    projArr[idx].sPos.y=sy;
    projArr[idx].pos.x=sx;
    projArr[idx].pos.y=sy;
    projArr[idx].tPos.x=tx;
    projArr[idx].tPos.y=ty;
    projArr[idx].type=type;


    float delta_x = tx - sx;
    float delta_y = ty - sy;

    float magnitude = sqrt((delta_x*delta_x + delta_y*delta_y));

    projArr[idx].v.x = (delta_x/magnitude)*projArr[idx].speed;
    projArr[idx].v.y = (delta_y/magnitude)*projArr[idx].speed;

    idx+=1;
    idx=idx%N_PROJ;
}

void projectile::draw_projectiles()
{
    for(int i=0;i<N_PROJ;i++) {

        if(!projArr[i].isLive) {continue;}

        if(clock()-projArr[i].stTime>5000){
            projArr[i].isLive=false;
        }

        move_projectiles(i);

        if(projArr[i].type == 0 )projTex->bindTexture();
        if(projArr[i].type != 0 )enemProjTex->bindTexture();
        glPushMatrix();

        glTranslatef(projArr[i].pos.x*2,projArr[i].pos.y*2,0);
        glPushMatrix();
        glScalef(0.1,0.1,1);
        glBegin(GL_POLYGON);

            glTexCoord2f(0,0);
            glVertex3f(-1,-1,-8.0);

            glTexCoord2f(1,0);
            glVertex3f( 1,-1,-8.0);

            glTexCoord2f(1,1);
            glVertex3f( 1,1,-8.0);

            glTexCoord2f(0,1);
            glVertex3f(-1,1,-8.0);


        glEnd();
        glPopMatrix();
        glPopMatrix();

    }
}
void projectile::move_projectiles(int i)
{
    projArr[i].pos.x+=projArr[i].v.x;
    projArr[i].pos.y+=projArr[i].v.y;
}
void projectile::reset()
{
    for(int i=0;i<N_PROJ;i++) {

        projArr[i].isLive=false;

    }
}

bool projectile::check_colision(vec3 plPosition)
{
    chrono::steady_clock::time_point rn = steady_clock::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(rn - hit_check_clock);

    if (elapsed.count()<100) {
        return false;
    };

    hit_check_clock = steady_clock::now();

    for(int i=0; i<N_PROJ; i++) {

        if(!projArr[i].isLive) {
            continue;
        }

        float dx = plPosition.x- projArr[i].pos.x;
        float dy = plPosition.y- projArr[i].pos.y;

        float d = sqrt((dx*dx)+(dy*dy));

        cout << d << endl;

        if (d<0.1) {

            projArr[i].isLive = false;
            return true;
            }
        else {
            continue;
        }
    }




    return false;
}



