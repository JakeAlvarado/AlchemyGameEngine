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
void enemy::initEnemy(float x_init, float y_init, int t)
{
    type = t;
    spriteShape.x = 1;
    spriteShape.y = 4;

    pos.x = x_init;
    pos.y = y_init;

    switch(type){

    case 1:
        enemyTex->loadTexture(earth_image_path);
        enemySpeed=0.0004;
        break;
    case 2:
        enemyTex->loadTexture(fire_image_path);
        enemySpeed=0.0005
        ;
        break;
    case 3:
        enemyTex->loadTexture(water_image_path);
        enemySpeed=0.0025;
        break;
    case 4:
        enemyTex->loadTexture(air_image_path);
        enemySpeed=0.002;
        break;
    }


    myTime->startTime = clock();
    moveTime->startTime = clock();

    myTimeC->set_timer();
    moveTimeC->set_timer();

    attackTimer=clock();

    pos.z = -1.0;
    frame = 0;
    n_frames = spriteShape.x*spriteShape.y;
    isLive=true;
    melleCounter=0;

}

void enemy::drawEnemy()
{
    if(!isLive)return;

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


    if(!isLive)return;

    //if(clock() - myTime->startTime > 200){
    if(myTimeC->get_delta_time() > 200){

        if(melleCounter>2) {
            killEnemy();
        }

        // inc frame
        if (clock() - attackTimer > 2500) {
            bool shot = false;
            if(rand()%2==1){
                gameProjectiles->shoot_projectile(1,Target.x,Target.y,pos.x,pos.y);
                shot = true;

            }
            if (shot) attackTimer = clock();
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

        //myTime->startTime=clock();
        myTimeC->set_timer();

    }
}

void enemy::setTarget(vec3 t)
{
    if(!isLive)return;
    Target.x=t.x;
    Target.y=t.y;

}

void enemy::updatePos() {

    if(!isLive) {
        return;
    }


    //if(clock() - moveTime->startTime < 600) return;
    if(moveTimeC->get_delta_time() < 10) return;


    float dx = Target.x-pos.x;
    float dy = Target.y-pos.y;

    if( dx>-.5 && dx<0.5 && dy>-.5 && dy<0.5 ) {
        return;
    }
    if (dx>0){
        pos.x+=enemySpeed;
        dir = true;
    }
    if(dx<0) {
        pos.x-=enemySpeed;
        dir = false;
    }
    if(dy>0) {
        pos.y+=enemySpeed;
    }
    if(dy<0) {
        pos.y-=enemySpeed
        ;
    }
    moveTimeC->set_timer();
}


void enemy::killEnemy()
{
    pos.x = 100;
    isLive=false;
}

bool enemy::hit_check(projectile* projList) {
    bool hitDetected = false;

    for (int i = 0; i < N_PROJ; i++) {
        if (!projList->projArr[i].isLive) {
            continue;
        }

        float dx = pos.x - projList->projArr[i].pos.x;
        float dy = pos.y - projList->projArr[i].pos.y;
        float d = sqrt((dx * dx) + (dy * dy));

        if (d < 0.1) {
            //cout << "ENEMY TOOK A HIT" << endl;
            projList->projArr[i].isLive = false;
            hitDetected = true;
            break;
        }
    }

    return hitDetected;
}
