#ifndef ENEMYLEVELHANDLER_H
#define ENEMYLEVELHANDLER_H

#include <enemy.h>
#include <common.h>


class EnemyLevelHandler
{
    public:
        EnemyLevelHandler();
        virtual ~EnemyLevelHandler();

        vec3 target;
        enemy *enemyList[3];

        int n_enemies;

        void setTarget(vec3 t);
        void drawEnemies();
        void initEnemies(int n);



    protected:

    private:
};

#endif // ENEMYLEVELHANDLER_H
