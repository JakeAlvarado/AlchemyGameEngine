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
        enemyList[i] = new enemy(3, proj);
        enemyList[i]->initEnemy(-1,.2, 3);
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

        cout<<d<<endl;
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

void EnemyLevelHandler::startLevel(int level)
{
    level_timer = clock();
    killAllEnemies();

    switch(level){

        case 1:


            break;
        case 2:
            initial_spawn();
            kill_counter=0;
            n_alive=0;
            max_enemies_spawned = 3;
            win_number=8;

            break;
        case 3:
            kill_counter=0;
            n_alive=0;
            max_enemies_spawned = 4;
            win_number=8;

            break;
        case 4:
            kill_counter=0;
            n_alive=0;
            max_enemies_spawned = 5;
            win_number=8;
            break;

    }
}

void EnemyLevelHandler::initial_spawn()
{

    enemyList[0]->initEnemy(-1,.2,3);

}



