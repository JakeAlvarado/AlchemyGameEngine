#ifndef GLSOUNDS_H
#define GLSOUNDS_H

#include<common.h>

class GLSounds
{
    public:
        GLSounds();
        virtual ~GLSounds();

        ISoundEngine *engine = createIrrKlangDevice();
        void playMusic(char *);
        void playSound(char *);
        void pauseSound(char *);
        int initSounds();

    protected:

    private:
};

#endif // GLSOUNDS_H