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
       switch(facing) {
            case LEFT:
                xMin = 1.0/(float)framesX;
                xMax = 0;
                yMax = 2.0/(float)framesY;
                yMin = yMax-1.0/(float)framesY;
                break;
            case RIGHT:
                xMax = 1.0/(float)framesX;
                xMin = 0;
                yMax = 2.0/(float)framesY;
                yMin = yMax-1.0/(float)framesY;
                break;
            case UP:
                xMin =0;
                xMax = 1.0/(float)framesX;
                yMax =3.0/(float)framesY;
                yMin =yMax-1.0/(float)framesY;
                break;
            case DOWN:
                xMin =0;
                xMax = 1.0/(float)framesX;
                yMax =1.0/(float)framesY;
                yMin =yMax-1.0/(float)framesY;
                break;
            default:
                break;
        }

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
   case ATTACK:
    if(clock() - myTime->startTime>60)
    {
        yMax = 8.0/(float)framesY;
        yMin = yMax - 1.0/(float)framesY;

        xMin += 1.0/(float)framesX;
        xMax += 1.0/(float)framesX;

    myTime->startTime =clock();
    }
        break;
   case ATTACKLEFT:
       if(clock() - myTime->startTime>60)
    {
        yMax = 8.0/(float)framesY;
        yMin = yMax - 1.0/(float)framesY;

        xMax += 1.0/(float)framesX;
        xMin += 1.0/(float)framesX;


    myTime->startTime =clock();
    }
    break;
   case ATTACKUP:
    if(clock() - myTime->startTime>60)
    {
        yMax = 9.0/(float)framesY;
        yMin = yMax - 1.0/(float)framesY;

        xMax += 1.0/(float)framesX;
        xMin += 1.0/(float)framesX;


    myTime->startTime =clock();
    }

    break;
   case ATTACKDOWN:
    if(clock() - myTime->startTime>60)
    {
        yMax = 7.0/(float)framesY;
        yMin = yMax - 1.0/(float)framesY;

        xMax += 1.0/(float)framesX;
        xMin += 1.0/(float)framesX;


    myTime->startTime =clock();
    }

   default: break;
   }
}
void GLPlayer::update()
{
    bool isMoving = false;
    if (keyStates[VK_LEFT] || keyStates['A'])
    {
        this->actionTrigger = WALKLEFT;
        isMoving = true;
        facing = LEFT;
    }
    if (keyStates[VK_UP] || keyStates['W'])
    {
        this->actionTrigger = WALKUP;
        isMoving = true;
        facing = UP;
    }
    if (keyStates[VK_DOWN] || keyStates['S'])
    {
        this->actionTrigger = WALKDOWN;
        isMoving = true;
        facing = DOWN;
    }
    if (keyStates[VK_RIGHT] || keyStates['D'])
    {
        this->actionTrigger = WALKRIGHT;
        isMoving = true;
        facing = RIGHT;
    }
    if (keyStates[VK_SPACE])
    {

        if (keyStates['A'] || keyStates[VK_LEFT])
        {
            performAttackLeft();
        }
        else if (keyStates['W'] || keyStates[VK_UP])
        {
            performAttackUp();
        }
        else if (keyStates['S'] || keyStates[VK_DOWN])
        {
            performAttackDown();
        }
        else
        {
            performAttack();
        }
    }
    if (isMoving == false && !keyStates[VK_SPACE])
    {
        this->actionTrigger = STAND;
    }

    this->actions();
}

vec3 GLPlayer::getPos()
{
    return plPosition;
}
// follows pattern of left, up, right, down
void GLPlayer::boundsCheck(int level) {
    if (this->plPosition.x <= this->bounds[level][0]) this->plPosition.x = this->bounds[level][0];
    else if (this->plPosition.y >= this->bounds[level][1]) this->plPosition.y = this->bounds[level][1];
    else if (this->plPosition.x >= this->bounds[level][2]) this->plPosition.x = this->bounds[level][2];
    else if (this->plPosition.y <= this->bounds[level][3]) this->plPosition.y = this->bounds[level][3];
}
void GLPlayer::performAttack()
{
    this->actionTrigger = ATTACK;
}

void GLPlayer::performAttackLeft()
{
    this->actionTrigger = ATTACKLEFT;
}
void GLPlayer::performAttackDown()
{
    this->actionTrigger = ATTACKDOWN;
}

void GLPlayer::performAttackUp()
{
    this->actionTrigger = ATTACKUP;
}


bool GLPlayer::hit_check(projectile* projList)
{

    for(int i=0; i<N_PROJ; i++) {



        if(!projList->projArr[i].isLive) {
            continue;
        }

        float dx = plPosition.x- projList->projArr[i].pos.x;
        float dy = plPosition.y- projList->projArr[i].pos.y;

        float d = sqrt((dx*dx)+(dy*dy));


        if (d<0.2) {
            cout << "PLAYER TOOK A HIT"<<endl;
            return(true);
            }
        else {
            return(false);
        }

    }
}

