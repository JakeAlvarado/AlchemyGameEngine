#include "GLHUD.h"

GLHUD::GLHUD()
{
    //ctor    

    vert[0].x =-0.5; vert[0].y = -0.5; vert[0].z =-1.0;
    vert[1].x = 0.5; vert[1].y = -0.5; vert[1].z =-1.0;
    vert[2].x = 0.5; vert[2].y =  0.5; vert[2].z =-1.0;
    vert[3].x =-0.5; vert[3].y =  0.5; vert[3].z =-1.0;
}

GLHUD::~GLHUD()
{
    //dtor
    delete heart1;
    delete heart2;
    delete heart3;
    delete heart4;
    delete equipment1;
    delete equipment2;
    delete equipment3;
    delete equipment4;
}

void GLHUD::initHUD() {
    initHealth(5, 1, "images/hud/player_health.png"); // loading player hud health texture
    initEquipment(2, 1, "images/hud/player_equipment.png"); // loading player hud equipment texture
    air->loadTexture("images/elements/air.png"); // loading air icon
    water->loadTexture("images/elements/water.png"); // loading water icon
    earth->loadTexture("images/elements/earth.png"); // loading earth icon
    fire->loadTexture("images/elements/fire.png"); // loading fire icon
}

void GLHUD::initHealth(int x,int y, char* fileName)
{
    heart1->loadTexture(fileName); //loading player hud health texture
    heart2->loadTexture(fileName); //loading player hud health texture
    heart3->loadTexture(fileName); //loading player hud health texture
    heart4->loadTexture(fileName); //loading player hud health texture

    // Init Health Variables
    hearts = 4;

    framesXHealth = x;
    framesYHealth = y;

    xMinHealth = 0.8;
    xMaxHealth = 1.0;
    yMaxHealth = 1.0/(float)framesYHealth;
    yMinHealth = 0.0;

}

void GLHUD::initEquipment(int x, int y, char* fileName)
{
    equipment1->loadTexture(fileName); //loading player hud equipment texture
    equipment2->loadTexture(fileName); //loading player hud equipment texture
    equipment3->loadTexture(fileName); //loading player hud equipment texture
    equipment4->loadTexture(fileName); //loading player hud equipment texture

    // Init equipment variables
    framesXEquipment = x;
    framesYEquipment = y;

    xMinEquipment =0;
    yMaxEquipment =1.0/(float)framesYEquipment;
    xMaxEquipment =2.0/(float)framesXEquipment;
    yMinEquipment =yMaxEquipment-1.0/(float)framesYEquipment;
}

void GLHUD::hudDraw()
{
    healthDraw();
    equipmentDraw();
}

void GLHUD::drawGraphicAtOGLPos(float xPos, float yPos, GLTexture *graphic, float xMin, float xMax, float yMin, float yMax, float scale)
{
    // GLint viewport[4];
    // GLdouble modelview[16];
    // GLdouble projection[16];
    // GLfloat winX, winY, winZ;
    // GLdouble posX, posY, posZ;

    // glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    // glGetDoublev(GL_PROJECTION_MATRIX, projection);
    // glGetIntegerv(GL_VIEWPORT, viewport);

    // winX = static_cast<float>(xPos);
    // winY = static_cast<float>(viewport[3] - yPos);
    // glReadPixels(xPos, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

    // gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
    // xPos =(int) (posX *M->getGridSize()/2 +M->getGridSize()/2); // update graphic position X
    // yPos =(int) (posY *M->getGridSize()/2 +M->getGridSize()/2);

    // Draw the graphic at the unprojected world position    

    glPushMatrix();

    glTranslatef(xPos, yPos, -1.0);
    glScalef(scale, scale, scale);
    glColor3f(1.0, 1.0, 1.0);
    graphic->bindTexture();
    
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
    glPopMatrix();

}

void GLHUD::healthDraw() {
    // logic based on hearts
    switch(hearts) {
        case 0: // no hearts
            drawGraphicAtOGLPos(-4.0, -7.5, heart1, 0.0, 0.2, 0.0, 1.0, 1.0);
            drawGraphicAtOGLPos(-3.0, -7.5, heart2, 0.0, 0.2, 0.0, 1.0, 1.0);
            drawGraphicAtOGLPos(-2.0, -7.5, heart3, 0.0, 0.2, 0.0, 1.0, 1.0);
            drawGraphicAtOGLPos(-1.0, -7.5, heart4, 0.0, 0.2, 0.0, 1.0, 1.0);
            break;
        case 1: // 1 heart
            drawGraphicAtOGLPos(-4.0, -7.5, heart1, 0.8, 1.0, 0.0, 1.0, 1.0);
            drawGraphicAtOGLPos(-3.0, -7.5, heart2, 0.0, 0.2, 0.0, 1.0, 1.0);
            drawGraphicAtOGLPos(-2.0, -7.5, heart3, 0.0, 0.2, 0.0, 1.0, 1.0);
            drawGraphicAtOGLPos(-1.0, -7.5, heart4, 0.0, 0.2, 0.0, 1.0, 1.0);
            break;
        case 2: // 2 hearts
            drawGraphicAtOGLPos(-4.0, -7.5, heart1, 0.8, 1.0, 0.0, 1.0, 1.0);
            drawGraphicAtOGLPos(-3.0, -7.5, heart2, 0.8, 1.0, 0.0, 1.0, 1.0);
            drawGraphicAtOGLPos(-2.0, -7.5, heart3, 0.0, 0.2, 0.0, 1.0, 1.0);
            drawGraphicAtOGLPos(-1.0, -7.5, heart4, 0.0, 0.2, 0.0, 1.0, 1.0);
            break;
        case 3: // 3 hearts
            drawGraphicAtOGLPos(-4.0, -7.5, heart1, 0.8, 1.0, 0.0, 1.0, 1.0);
            drawGraphicAtOGLPos(-3.0, -7.5, heart2, 0.8, 1.0, 0.0, 1.0, 1.0);
            drawGraphicAtOGLPos(-2.0, -7.5, heart3, 0.8, 1.0, 0.0, 1.0, 1.0);
            drawGraphicAtOGLPos(-1.0, -7.5, heart4, 0.0, 0.2, 0.0, 1.0, 1.0);
            break;
        case 4: // 4 hearts
            drawGraphicAtOGLPos(-4.0, -7.5, heart1, 0.8, 1.0, 0.0, 1.0, 1.0);
            drawGraphicAtOGLPos(-3.0, -7.5, heart2, 0.8, 1.0, 0.0, 1.0, 1.0);
            drawGraphicAtOGLPos(-2.0, -7.5, heart3, 0.8, 1.0, 0.0, 1.0, 1.0);
            drawGraphicAtOGLPos(-1.0, -7.5, heart4, 0.8, 1.0, 0.0, 1.0, 1.0);
            break;
        default: // 4 hearts
            drawGraphicAtOGLPos(-4.0, -7.5, heart1, 0.8, 1.0, 0.0, 1.0, 1.0);
            drawGraphicAtOGLPos(-3.0, -7.5, heart2, 0.8, 1.0, 0.0, 1.0, 1.0);
            drawGraphicAtOGLPos(-2.0, -7.5, heart3, 0.8, 1.0, 0.0, 1.0, 1.0);
            drawGraphicAtOGLPos(-1.0, -7.5, heart4, 0.8, 1.0, 0.0, 1.0, 1.0);
            break;
    }
}

void GLHUD::equipmentDraw() {
    // draw elements in each slot
    drawGraphicAtOGLPos(0.6, -5.1, air, 0.0, 1.0, 0.0, 1.0, 0.35); // slot 0 has air
    drawGraphicAtOGLPos(1.28, -5.1, water, 0.0, 1.0, 0.0, 1.0, 0.35); // slot 1 has water
    drawGraphicAtOGLPos(1.945, -5.1, earth, 0.0, 1.0, 0.0, 1.0, 0.35); // slot 2 has earth
    drawGraphicAtOGLPos(2.625, -5.1, fire, 0.0, 1.0, 0.0, 1.0, 0.35); // slot 3 has fire


    // render equipment hud based on what item is equipped
    switch(equipped) {
      case AIR:
        drawGraphicAtOGLPos(1.0, -7.5, equipment1, 0.5, 1.0, 0.0, 1.0, 1.0); // slot 0 equipped
        drawGraphicAtOGLPos(2.0, -7.5, equipment2, 0.0, 0.5, 0.0, 1.0, 1.0); // slot 1 not equipped
        drawGraphicAtOGLPos(3.0, -7.5, equipment3, 0.0, 0.5, 0.0, 1.0, 1.0); // slot 2 not equipped
        drawGraphicAtOGLPos(4.0, -7.5, equipment4, 0.0, 0.5, 0.0, 1.0, 1.0); // slot 3 not equipped
        drawGraphicAtOGLPos(0.6, -5.1, air, 0.0, 1.0, 0.0, 1.0, 0.35); // draw equipped element on top
        break;
      case WATER:
        drawGraphicAtOGLPos(1.0, -7.5, equipment1, 0.0, 0.5, 0.0, 1.0, 1.0); // slot 0 not equipped
        drawGraphicAtOGLPos(2.0, -7.5, equipment2, 0.5, 1.0, 0.0, 1.0, 1.0); // slot 1 equipped
        drawGraphicAtOGLPos(3.0, -7.5, equipment3, 0.0, 0.5, 0.0, 1.0, 1.0); // slot 2 not equipped
        drawGraphicAtOGLPos(4.0, -7.5, equipment4, 0.0, 0.5, 0.0, 1.0, 1.0); // slot 3 not equipped
        drawGraphicAtOGLPos(1.28, -5.1, water, 0.0, 1.0, 0.0, 1.0, 0.35); // draw equipped element on top
        break;
      case EARTH:
        drawGraphicAtOGLPos(1.0, -7.5, equipment1, 0.0, 0.5, 0.0, 1.0, 1.0); // slot 0 not equipped
        drawGraphicAtOGLPos(2.0, -7.5, equipment2, 0.0, 0.5, 0.0, 1.0, 1.0); // slot 1 not equipped
        drawGraphicAtOGLPos(3.0, -7.5, equipment3, 0.5, 1.0, 0.0, 1.0, 1.0); // slot 2 equipped
        drawGraphicAtOGLPos(4.0, -7.5, equipment4, 0.0, 0.5, 0.0, 1.0, 1.0); // slot 3 not equipped
        drawGraphicAtOGLPos(1.945, -5.1, earth, 0.0, 1.0, 0.0, 1.0, 0.35); // draw equipped element on top
        break;
      case FIRE:
        drawGraphicAtOGLPos(1.0, -7.5, equipment1, 0.0, 0.5, 0.0, 1.0, 1.0); // slot 0 not equipped
        drawGraphicAtOGLPos(2.0, -7.5, equipment2, 0.0, 0.5, 0.0, 1.0, 1.0); // slot 1 not equipped
        drawGraphicAtOGLPos(3.0, -7.5, equipment3, 0.0, 0.5, 0.0, 1.0, 1.0); // slot 2 not equipped
        drawGraphicAtOGLPos(4.0, -7.5, equipment4, 0.5, 1.0, 0.0, 1.0, 1.0); // slot 3 equipped
        drawGraphicAtOGLPos(2.625, -5.1, fire, 0.0, 1.0, 0.0, 1.0, 0.35); // draw equipped element on top
        break;
      default:
        drawGraphicAtOGLPos(1.0, -7.5, equipment1, 0.0, 0.5, 0.0, 1.0, 1.0); // slot 0 not equipped
        drawGraphicAtOGLPos(2.0, -7.5, equipment2, 0.0, 0.5, 0.0, 1.0, 1.0); // slot 1 not equipped
        drawGraphicAtOGLPos(3.0, -7.5, equipment3, 0.0, 0.5, 0.0, 1.0, 1.0); // slot 2 not equipped
        drawGraphicAtOGLPos(4.0, -7.5, equipment4, 0.0, 0.5, 0.0, 1.0, 1.0); // slot 3 not equipped
        break;
    }

    

    // // logic based on inventory array
    // if (inventory[AIR] > 0)
    //   // draw air icon on inventory slot 1
    // if (inventory[WATER] > 0)
    //   // draw water icon on inventory slot 2
    // if (inventory[EARTH] > 0)
    //   // draw earth icon on inventory slot 3
    // if (inventory[FIRE] > 0)
    //  // draw fire icon on inventory slot 4
}