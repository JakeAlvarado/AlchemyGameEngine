#include "EnemyLevelHandler.h"

EnemyLevelHandler::EnemyLevelHandler()
{
    //ctor


}

EnemyLevelHandler::EnemyLevelHandler(int level)
{

}

EnemyLevelHandler::~EnemyLevelHandler()
{
    for(int i=0;i<n_enemies;i++) {
        delete[] enemyList;
    }
}
void EnemyLevelHandler::setTarget(vec3 t)
{
    if(!safe_to_draw) {
        return;
    }

    for (int i=0; i<n_enemies; i++) {
        enemyList[i]->setTarget(t);
    }
}

void EnemyLevelHandler::drawEnemies()
{
    if(!safe_to_draw) {
        return;
    }

    for (int i=0; i<n_enemies; i++) {
        enemyList[i]->drawEnemy();

    }
}

void EnemyLevelHandler::initEnemies(int n, projectile *proj)
{
    n_enemies = MAX_N_ENEMIES;
    for (int i=0;i<n_enemies;i++) {
        enemyList[i] = new enemy(4, proj);
        enemyList[i]->initEnemy(-1,.2, WATER);
    }
    safe_to_draw = true;
}


void EnemyLevelHandler::meleAttack(vec3 playPos)
{
    if(!safe_to_draw) {
        return;
    }


    int live_counter = 0;

    for (int i=0; i<n_enemies; i++) {
        if(!enemyList[i]->isLive){continue;}

        live_counter+=1;

        float dx = enemyList[i]->pos.x - playPos.x;
        float dy = enemyList[i]->pos.y - playPos.y;

        float d = sqrt((dx*dx+dy*dy));

        if (d<0.2){
            enemyList[i]->melleCounter+=1;

        }

    }
    int live_counter_after = 0;
    for (int i=0; i<n_enemies; i++) {
        if(!enemyList[i]->isLive){continue;}
        live_counter_after+=1;
    }

    if (live_counter!=live_counter_after && live_counter>live_counter_after) {
        kill_counter+=live_counter>live_counter_after;
        n_alive-=live_counter;
    }
}


void EnemyLevelHandler::getEnempyPositions()
{

}

void EnemyLevelHandler::killAllEnemies()
{
    for(int i=0; i<n_enemies; i++) {

        enemyList[i]->killEnemy();
    }
}

void EnemyLevelHandler::resetEnemyHandler()
{

}

void EnemyLevelHandler::startLevel(int l)
{
    level_timer = clock();
    killAllEnemies();
    level = l;


    switch(level){

        case 1:


            break;
        case 2:

            kill_counter=0;
            n_alive=0;
            max_enemies_spawned = 3;
            win_number=8;
            initial_spawn();
            break;
        case 3:
            kill_counter=0;
            n_alive=0;
            max_enemies_spawned = 4;
            win_number=8;
            initial_spawn();

            break;
        case 4:
            kill_counter=0;
            n_alive=0;
            max_enemies_spawned = 5;
            win_number=8;
            initial_spawn();
            break;

    }
}

void EnemyLevelHandler::initial_spawn()
{


    switch (level) {
        case 2:


            enemyList[0]->initEnemy(-1,.2,AIR);
            enemyList[1]->initEnemy(0,-.3,FIRE);

            break;

        case 3:
            enemyList[0]->initEnemy(-1,.2,FIRE);
            enemyList[1]->initEnemy(0,-.3,EARTH);
            enemyList[2]->initEnemy(.2,.3,EARTH);
            break;

        case 4:

            enemyList[0]->initEnemy(1,-.28,EARTH);
            enemyList[1]->initEnemy(1,.25,EARTH);
            enemyList[2]->initEnemy(-1,.3,FIRE);
            enemyList[3]->initEnemy(-1,-.2,FIRE);
            enemyList[4]->initEnemy(0,-.3,WATER);
            enemyList[5]->initEnemy(.2,-.2,AIR);
            break;



    }


    safe_to_draw=true;



}



