#include "EnemyLevelHandler.h"

EnemyLevelHandler::EnemyLevelHandler()
{
    //ctor


}

EnemyLevelHandler::EnemyLevelHandler(int level)
{
    // use this to initialize enemy list and such for what level we are on
    switch(level){

        case 1:
            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            break;


    }

}

EnemyLevelHandler::~EnemyLevelHandler()
{
    for(int i=0;i<n_enemies;i++) {
        delete[] enemyList;
    }
}
void EnemyLevelHandler::setTarget(vec3 t)
{

    for (int i=0; i<n_enemies; i++) {
        enemyList[i]->setTarget(t);
    }


}

void EnemyLevelHandler::drawEnemies()
{

    for (int i=0; i<n_enemies; i++) {
        enemyList[i]->drawEnemy();

    }
}

void EnemyLevelHandler::initEnemies(int n, projectile *proj)
{

    n_enemies = MAX_N_ENEMIES;

    for (int i=0;i<n_enemies;i++) {

        enemyList[i] = new enemy(3, proj);



        enemyList[i]->initEnemy(1,.2);

    }
}


void EnemyLevelHandler::meleAttack(vec3 playPos)
{

    for (int i=0; i<n_enemies; i++) {
        if(!enemyList[i]->isLive){continue;}


        float dx = enemyList[i]->pos.x - playPos.x;
        float dy = enemyList[i]->pos.y - playPos.y;

        float d = sqrt((dx*dx+dy*dy));


        if (d<0.2){
            enemyList[i]->melleCounter+=1;
        }
    }


}

void EnemyLevelHandler::getEnempyPositions()
{

}

void EnemyLevelHandler::killAllEnemies()
{
    for(int i; i<n_enemies; i++) {

        enemyList[i]->killEnemy();

    }
}

