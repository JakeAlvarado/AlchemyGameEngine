#include "enemy.h"

enemy::enemy()
{
    vert[0].x =-0.5; vert[0].y = -0.5; vert[0].z =-1.0;
    vert[1].x = 0.5; vert[1].y = -0.5; vert[1].z =-1.0;
    vert[2].x = 0.5; vert[2].y =  0.5; vert[2].z =-1.0;
    vert[3].x =-0.5; vert[3].y =  0.5; vert[3].z =-1.0;
}

enemy::~enemy()
{
    //dtor
}
void enemy::initEnemy()
{
    type = 1;

    spriteShape.x = 1;
    spriteShape.y = 4;

    enemyTex->loadTexture(water_image_path);
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
    glTranslatef(pos.x,pos.y,pos.z);


    glColor3f(1.0,1.0,1.0);    //white rectangle
    enemyTex->bindTexture();    //binding my background
    glScalef(0.12,0.24,1.0);


    glBegin(GL_QUADS);
      glTexCoord2f(xMin,1);
      glVertex3f(vert[0].x,vert[0].y,vert[0].z);

      glTexCoord2f(xMax,1);
      glVertex3f(vert[1].x,vert[1].y,vert[1].z);

      glTexCoord2f(xMax,0);
      glVertex3f(vert[2].x,vert[2].y,vert[2].z);

      glTexCoord2f(xMin,0);
      glVertex3f(vert[3].x,vert[3].y,vert[3].z);

    glEnd();
}

void enemy::updateFrame() {

    if(clock() - myTime->startTime > 200){
        // inc frame

        frame+=1;
        frame = frame%n_frames;


        // calculate frame yMin, yMax


        xMin+=1.0/(float)n_frames;
        xMax+=1.0/(float)n_frames;

        if(xMax==1){
            xMin=0;
            xMax=.25;
        }

        cout<<"Xmin="<<xMin<<endl;
        cout<<"XMax="<<xMax<<endl;

        myTime->startTime=clock();


    }

}

void enemy::setTarget(vec3 t)
{
    Target.x=t.x;
    Target.y=t.y;

}

void enemy::updatePos() {


    if(clock() - moveTime->startTime < 60) return;


    float dx = Target.x-pos.x;
    float dy = Target.y-pos.y;

    if( dx>-.5 && dx<0.5 && dy>-.5 && dy<0.5 ) {
        return;
    }
    if (dx>0){
        pos.x+=0.005;
    }
    if(dx<0) {
        pos.x-=0.005;
    }
    if(dy>0) {
        pos.y+=0.005;
    }
    if(dy<0) {
        pos.y-=0.005;
    }
}



