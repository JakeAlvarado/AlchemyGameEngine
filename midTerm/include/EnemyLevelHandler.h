#ifndef ENEMYLEVELHANDLER_H
#define ENEMYLEVELHANDLER_H

#include <enemy.h>
#include <common.h>
#include <projectile.h>
#include <vector>



class EnemyLevelHandler
{
    public:
        EnemyLevelHandler();
        EnemyLevelHandler(int level);
        virtual ~EnemyLevelHandler();

        vec3 target;
        enemy *enemyList[MAX_N_ENEMIES];

        clock_t level_timer;
        vector<int> level_enemy_types;

        int max_enemies_spawned;
        int win_number;
        int kill_counter;
        int n_alive;

        void initial_spawn();

        int n_enemies;
        bool safe_to_draw = false;

        void meleAttack(vec3 playPos);

        void setTarget(vec3 t);
        void drawEnemies();
        void initEnemies(int n, projectile *proj);

        void killAllEnemies();
        void resetEnemyHandler();
        void getEnempyPositions();
        void startLevel(int level);



    protected:

    private:
};

#endif // ENEMYLEVELHANDLER_H
