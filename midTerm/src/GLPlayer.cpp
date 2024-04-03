#include "GLPlayer.h"

GLPlayer::GLPlayer()
{
    //ctor
    vert[0].x =-0.5; vert[0].y = -0.5; vert[0].z =-1.0;
    vert[1].x = 0.5; vert[1].y = -0.5; vert[1].z =-1.0;
    vert[2].x = 0.5; vert[2].y =  0.5; vert[2].z =-1.0;
    vert[3].x =-0.5; vert[3].y =  0.5; vert[3].z =-1.0;

}

GLPlayer::~GLPlayer()
{
    //dtor
}
void GLPlayer::initPlayer(int x, int y, char* fileName)
{
    plPosition.x =0.0;         // initialize positions
    plPosition.y =-0.2;
    plPosition.z = -1.0;

    plScale.x = 0.5;           // initialize scale
    plScale.y = 0.5;
    plScale.z = 1.0;

    framesX = x;               // record number of frames
    framesY = y;

    texture->loadTexture(fileName); //loading my background

    xMin =0;
    yMax =2.0/(float)framesY;
    xMax =1.0/(float)framesX;
    yMin =yMax-1.0/(float)framesY;

    actionTrigger=0;
    myTime->startTime = clock();
}

void GLPlayer::drawPlayer()
{

    glTranslatef(plPosition.x,plPosition.y,plPosition.z);
    glScalef(plScale.x,plScale.y,plScale.z);

    glColor3f(1.0,1.0,1.0);    //white rectangle
    texture->bindTexture();    //binding my background


    glBegin(GL_QUADS);
      glTexCoord2f(xMin,yMax);
      glVertex3f(vert[0].x,vert[0].y,vert[0].z);

      glTexCoord2f(xMax,yMax);
      glVertex3f(vert[1].x,vert[1].y,vert[1].z);

      glTexCoord2f(xMax,yMin);
      glVertex3f(vert[2].x,vert[2].y,vert[2].z);

      glTexCoord2f(xMin,yMin);
      glVertex3f(vert[3].x,vert[3].y,vert[3].z);

    glEnd();
}

void GLPlayer::actions()
{


   switch(actionTrigger)
   {
   case STAND:

       xMin =0;
       xMax = 1.0/(float)framesX;
       yMax =1.0/(float)framesY;
       yMin =yMax-1.0/(float)framesY;

       break;

   case WALKLEFT:

    if(clock() - myTime->startTime > 60)
    {
        if(xMin < 1)
        {
            xMin += 1.0/(float)framesX;
            xMax += 1.0/(float)framesX;
        }
        else
        {
            xMax = 0.0;
            xMin = 1.0/(float)framesX;
            yMax = 5.0/(float)framesY;
            yMin = yMax - 1.0/(float)framesY;
        }
        this->plPosition.x -= 0.05;




        myTime->startTime =clock();
    }

       /*xMax =0;
       xMin = 1.0/(float)framesX;

       yMax =1.0/(float)framesY;
       yMin =yMax-1.0/(float)framesY;

       xMax += 1.0/(float)framesX;
       xMin += 1.0/(float)framesX;*/
       break;

   case WALKRIGHT:

    if(clock() - myTime->startTime > 60)
    {
        if(xMax < 1)
        {
            xMin += 1.0/(float)framesX;
            xMax += 1.0/(float)framesX;
        }
        else
        {
            xMin = 0.0;
            xMax = 1.0/(float)framesX;
            yMax = 5.0/(float)framesY;
            yMin = yMax - 1.0/(float)framesY;
        }
        this->plPosition.x += 0.05;

        myTime->startTime =clock();
    }
    break;
       /*if(xMax <1) {
       xMin += 1.0/(float)framesX;
       xMax += 1.0/(float)framesX;
       }
       else
       {
        xMin = 0;
        xMax = 1.0/(float)framesX;

         if(yMax <1)
         {
             yMax +=1.0/(float)framesY;
             yMin +=1.0/(float)framesY;
         }
         else
         {
             yMin =0.0/(float)framesY;
             yMax =1.0/(float)framesY;
         }

       }*/

   case WALKUP:

    if(clock() - myTime->startTime>60)
   {
       yMax = 6.0/(float)framesY;
       yMin = yMax - 1.0/(float)framesY;

       xMin += 1.0/(float)framesX;
       xMax += 1.0/(float)framesX;

       this->plPosition.y += 0.05;

    myTime->startTime =clock();
   }
    break;

   case WALKDOWN:

     if(clock() - myTime->startTime>60)
   {
       yMax = 4.0/(float)framesY;
       yMin = yMax - 1.0/(float)framesY;

       xMin += 1.0/(float)framesX;
       xMax += 1.0/(float)framesX;

       this->plPosition.y -= 0.05;

    myTime->startTime =clock();
   }
    break;

   case RUN: break;
   case JUMP: break;
   case ATTACK: break;
   default: break;
   }
}
void GLPlayer::update()
{
    if (keyStates[VK_LEFT] || keyStates['A'])
    {
        this->actionTrigger = WALKLEFT;
    }
    else if (keyStates[VK_UP] || keyStates['W'])
    {
        this->actionTrigger = WALKUP;
    }
    else if (keyStates[VK_DOWN] || keyStates['S'])
    {
        this->actionTrigger = WALKDOWN;
    }
    else if (keyStates[VK_RIGHT] || keyStates['D'])
    {
        this->actionTrigger = WALKRIGHT;
    }
    else
    {
        this->actionTrigger = STAND;
    }

    this->actions();
}
