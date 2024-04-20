#include "EnemyLevelHandler.h"

EnemyLevelHandler::EnemyLevelHandler()
{
    //ctor
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

void EnemyLevelHandler::initEnemies(int n)
{

    n_enemies = n;

    for (int i=0;i<n_enemies;i++) {

        enemyList[i] = new enemy((i%4)+1);
        enemyList[i]->initEnemy();

    }
}
