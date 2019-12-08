#include "monsterfactory.h"
#include "gun.h"

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
        for (int i = 0; i < 5; i ++) {
            current_delay += 200;
            AttackPattern p = {current_delay, 100, 100, Direction::SE};
            AttackPattern p2 = {current_delay, 400, 400, Direction::NW};
            AttackPattern p3 = {current_delay, 100, 400, Direction::NE};
            AttackPattern p4 = {current_delay, 400, 100, Direction::SW};
            a.push_back(p);
            a.push_back(p2);
            a.push_back(p3);
            a.push_back(p4);
        }
        current_delay += 100;
        for (int i = 0; i < 10; i ++) {
            AttackPattern p = {current_delay, 100 + i * 150, 100, Direction::S};
            a.push_back(p);
        }

        Gun * g = new Gun();
        return new Enemy(enemy_sprite, 5, 1, bound, a, "Lesser Dog", 10, g);
    }
}
