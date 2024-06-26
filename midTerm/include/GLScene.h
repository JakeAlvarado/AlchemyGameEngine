#ifndef GLSCENE_H
#define GLSCENE_H

#include <common.h>


class GLScene
{
    public:
        GLScene();
        virtual ~GLScene();
        bool shouldExit() {return requestExit;}
        GLint initGL();
        GLint drawScene();
        GLint pauseGame();
        GLint needsHelp();
        GLint gameOver();
        GLint playerWins();
        GLvoid resizeScene(GLsizei, GLsizei);

        int windMsg(HWND,UINT,WPARAM,LPARAM);  // take windows inputs

        WPARAM wParam;                         // keyboard/Mouse msg

        float screenWidth;                     // get values from main window
        float screenHeight;                    // get Values from main window

    protected:

    private:
        bool requestExit = false;
};

#endif // GLSCENE_H
