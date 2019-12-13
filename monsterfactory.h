#ifndef MONSTERFACTORY_H
#define MONSTERFACTORY_H

#include "enemy.h"

enum EnemyType { LesserDog, DweebFish, Canary, Helix };

class MonsterFactory
{
public:
    static MonsterFactory& GetInstance() {
        static MonsterFactory instance;
        return instance;
    }

    static Enemy * GetEnemy(EnemyType e);


    MonsterFactory(MonsterFactory const&) = delete;
    void operator=(MonsterFactory const&) = delete;

private:
    MonsterFactory();
    std::vector<Enemy> enemies_;
};

#endif // MONSTERFACTORY_H
