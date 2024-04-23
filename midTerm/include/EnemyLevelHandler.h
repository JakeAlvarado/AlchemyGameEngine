#ifndef ENEMYLEVELHANDLER_H
#define ENEMYLEVELHANDLER_H

#include <enemy.h>
#include <common.h>
#include <projectile.h>



class EnemyLevelHandler
{
    public:
        EnemyLevelHandler();
        EnemyLevelHandler(int level);
        virtual ~EnemyLevelHandler();

        vec3 target;
        enemy *enemyList[MAX_N_ENEMIES];

        int n_enemies;

        void meleAttack(vec3 playPos);

        void setTarget(vec3 t);
        void drawEnemies();
        void initEnemies(int n, projectile *proj);

        void killAllEnemies();

        void getEnempyPositions();



    protected:

    private:
};

#endif // ENEMYLEVELHANDLER_H
