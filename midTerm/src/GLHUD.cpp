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
    delete health;
    delete equipment;
}

void GLHUD::initHUD() {
    initHealth(5, 1, "./images/hud/player_health.png"); // loading player hud health texture
    initEquipment(2, 1, "images/hud/player_equipment.png"); // loading player hud equipment texture
}

void GLHUD::initHealth(int x,int y, char* fileName)
{
    health->loadTexture(fileName); //loading player hud health texture

    // Init Health Variables
    hearts = 3;

    framesXHealth = x;
    framesYHealth = y;

    xMinHealth =0;
    yMaxHealth =2.0/(float)framesYHealth;
    xMaxHealth =1.0/(float)framesXHealth;
    yMinHealth =yMaxHealth-1.0/(float)framesYHealth;    
}

void GLHUD::initEquipment(int x, int y, char* fileName)
{
    equipment->loadTexture(fileName); //loading player hud equipment texture

    // Init equipment variables
    framesXEquipment = x;
    framesYEquipment = y;

    xMinEquipment =0;
    yMaxEquipment =2.0/(float)framesYEquipment;
    xMaxEquipment =1.0/(float)framesXEquipment;
    yMinEquipment =yMaxEquipment-1.0/(float)framesYEquipment;
}

void GLHUD::hudDraw()
{
    healthDraw();
    //equipmentDraw(equipment);
}

void GLHUD::drawGraphicAtOGLPos(int xPos, int yPos, GLTexture *graphic, int xMin, int xMax, int yMin, int yMax)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    winX = static_cast<float>(xPos);
    winY = static_cast<float>(viewport[3] - yPos);
    glReadPixels(xPos, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
    // xPos =(int) (posX *M->getGridSize()/2 +M->getGridSize()/2); // update graphic position X
    // yPos =(int) (posY *M->getGridSize()/2 +M->getGridSize()/2);

    // Draw the graphic at the unprojected world position
    glScalef(2.0f, 2.0f, 2.0f);
    glColor3f(1.0, 1.0, 1.0); // Assuming the graphic is white
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
}

void GLHUD::healthDraw() {
    // logic based on hearts
    drawGraphicAtOGLPos(-1, -10, health, xMinHealth, xMaxHealth, yMinHealth, yMaxHealth);
}

void GLHUD::equipmentDraw() {
    // logic based on inventory
    drawGraphicAtOGLPos(0, 0, equipment, xMinEquipment, xMaxEquipment, yMinEquipment, yMaxEquipment);
}
