#include "enemy.h"

enemy::enemy(int t, projectile *proj)
{
    type = t;
    vert[0].x =-0.5; vert[0].y = -0.5; vert[0].z =-1.0;
    vert[1].x = 0.5; vert[1].y = -0.5; vert[1].z =-1.0;
    vert[2].x = 0.5; vert[2].y =  0.5; vert[2].z =-1.0;
    vert[3].x =-0.5; vert[3].y =  0.5; vert[3].z =-1.0;

    gameProjectiles = proj;
}

enemy::~enemy()
{
    //dtor
}
void enemy::initEnemy()
{
    spriteShape.x = 1;
    spriteShape.y = 4;

    switch(type){

    case 1:
        enemyTex->loadTexture(earth_image_path);
        break;
    case 2:
        enemyTex->loadTexture(fire_image_path);
        break;
    case 3:
        enemyTex->loadTexture(water_image_path);
        break;
    case 4:
        enemyTex->loadTexture(water_image_path);
        break;
    }





    myTime->startTime = clock();
    moveTime->startTime = clock();

    pos.x =0.0;         // initialize positions
    pos.y =-0.2;
    pos.z = -1.0;

    frame = 0;
    n_frames = spriteShape.x*spriteShape.y;



}

void enemy::drawEnemy()
{

    updateFrame();
    updatePos();

    glPushMatrix();

    glTranslatef(pos.x,pos.y,pos.z);


    glColor3f(1.0,1.0,1.0);    //white rectangle
    enemyTex->bindTexture();    //binding my background
    glScalef(0.25,0.25,1.0);


    glBegin(GL_QUADS);
      if(!dir)glTexCoord2f(xMax,1);
      else glTexCoord2f(xMin,1);
      glVertex3f(vert[0].x,vert[0].y,vert[0].z);

      if(!dir)glTexCoord2f(xMin,1);
      else glTexCoord2f(xMax,1);
      glVertex3f(vert[1].x,vert[1].y,vert[1].z);

      if(!dir)glTexCoord2f(xMin,0);
      else glTexCoord2f(xMax,0);
      glVertex3f(vert[2].x,vert[2].y,vert[2].z);

      if(!dir)glTexCoord2f(xMax,0);
      else glTexCoord2f(xMin,0);
      glVertex3f(vert[3].x,vert[3].y,vert[3].z);

    glEnd();
    glPopMatrix();
}

void enemy::updateFrame() {

    if(clock() - myTime->startTime > 200){
        // inc frame
        if(rand()%10==1){
            gameProjectiles->shoot_projectile(1,Target.x,Target.y,pos.x,pos.y);
        }
        frame+=1;
        frame = frame%n_frames;


        // calculate frame yMin, yMax


        xMin+=1.0/(float)n_frames;
        xMax+=1.0/(float)n_frames;

        if(xMax==1){
            xMin=0;
            xMax=.25;
        }

        myTime->startTime=clock();


    }

}

void enemy::setTarget(vec3 t)
{
    Target.x=t.x;
    Target.y=t.y;

}

void enemy::updatePos() {

    if (type == 1 || type == 2) return;
    if(clock() - moveTime->startTime < 600) return;


    float dx = Target.x-pos.x;
    float dy = Target.y-pos.y;

    if( dx>-.5 && dx<0.5 && dy>-.5 && dy<0.5 ) {
        return;
    }
    if (dx>0){
        pos.x+=0.002;
        dir = true;
    }
    if(dx<0) {
        pos.x-=0.002;
        dir = false;
    }
    if(dy>0) {
        pos.y+=0.002;
    }
    if(dy<0) {
        pos.y-=0.002;
    }
}



