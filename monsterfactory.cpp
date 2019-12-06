#include "monsterfactory.h"

MonsterFactory::MonsterFactory()
{

}

Enemy * MonsterFactory::GetEnemy(EnemyType e) {

    if (e == LesserDog) {
        QPixmap enemy_sprite = QPixmap(":/images/Gr8.png");
        enemy_sprite = enemy_sprite.scaled(300, 300, Qt::KeepAspectRatio);
        int current_delay = 0;
        Bounds bound = {0, 0, 10000, 10000};
        std::vector<AttackPattern> a;
        for (int i = 0; i < 50; i ++) {
            current_delay += 50;
            AttackPattern p = {current_delay, 100, 100, Direction::SE};
            AttackPattern p2 = {current_delay, 400, 400, Direction::NW};
            a.push_back(p);
            a.push_back(p2);
        }
        return new Enemy(enemy_sprite, 5, 1, bound, a);
    }
}
