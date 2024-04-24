#ifndef GLHUD_H
#define GLHUD_H

#include<common.h>
#include<GLTexture.h>
#include <GL/glut.h>

class GLHUD
{
    public:
        GLHUD();
        virtual ~GLHUD();

        GLTexture *heart1 = new GLTexture();
        GLTexture *heart2 = new GLTexture();
        GLTexture *heart3 = new GLTexture();
        GLTexture *heart4 = new GLTexture();


        GLTexture *equipment1 = new GLTexture();
        GLTexture *equipment2 = new GLTexture();
        GLTexture *equipment3 = new GLTexture();
        GLTexture *equipment4 = new GLTexture();

        void initHUD(); // init HUD files
        void initHealth(int,int,char* fileName); // load hud file
        void initEquipment(int,int,char* fileName); // load hud file
        void healthDraw(); // hearts
        void equipmentDraw();
        void hudDraw(); // width and height
        void drawGraphicAtOGLPos(float x, float y, GLTexture *, float, float, float, float); // Desired screen coordinates

        vec3 vert[4];

        // Health Variables
        int hearts;
        float xMaxHealth,xMinHealth,yMaxHealth,yMinHealth, xPosHealth, yPosHealth;
        int framesXHealth,framesYHealth;

        // Equipment Variables
        enum element {AIR, EARTH, WATER, FIRE};
        int inventory[4] = {};
        float xMaxEquipment,xMinEquipment,yMaxEquipment,yMinEquipment, xPosEquipment, yPosEquipment;
        int framesXEquipment,framesYEquipment;

    protected:

    private:
};

#endif // GLPARALLAX_H