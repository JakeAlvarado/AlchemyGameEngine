#include "GLSounds.h"



GLSounds::GLSounds()
{
    //ctor
}

GLSounds::~GLSounds()
{
    //dtor
    engine->drop();
}

void GLSounds::playMusic(char* File)
{
    engine->play2D(File, true);
}

void GLSounds::playSound(char* File)
{
    if(!engine->isCurrentlyPlaying(File))
    engine->play2D(File, false,false);
}

void GLSounds::pauseSound(char* File)
{
    engine->play2D(File,true,false);
}

int GLSounds::initSounds()
{
    if(!engine){cout<<" ERROR: *** The Sound Engine Could Not Star"<<endl;
    return 0;}
    return 1;
}