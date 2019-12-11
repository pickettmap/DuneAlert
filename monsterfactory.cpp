#include "monsterfactory.h"
#include "gun.h"

MonsterFactory::MonsterFactory()
{

}

Enemy * MonsterFactory::GetEnemy(EnemyType e) {
    int x1 = 800;
    int y1 = 500;
    int x2 = x1 + 300;
    int y2 = y1 + 275;

    if (e == LesserDog) {
        QPixmap enemy_sprite = QPixmap(":/images/Gr8.png");
        enemy_sprite = enemy_sprite.scaled(300, 300, Qt::KeepAspectRatio);
        int current_delay = 0;
        Bounds bound = {0, 0, 10000, 10000};
        std::vector<AttackPattern> a;
        for (int i = 0; i < 5; i ++) {
            current_delay += 200;
            AttackPattern p = {current_delay, x1, y1 - 10, Direction::SE};
            AttackPattern p2 = {current_delay, x2, y2 - 10, Direction::NW};
            AttackPattern p3 = {current_delay, x1, y2 - 10, Direction::NE};
            AttackPattern p4 = {current_delay, x2, y1 - 10, Direction::SW};
            a.push_back(p);
            a.push_back(p2);
            a.push_back(p3);
            a.push_back(p4);
        }
        current_delay += 100;
        for (int i = 0; i < 10; i ++) {
            AttackPattern p = {current_delay, x1 - 10 + i * 150, y1, Direction::S};
            a.push_back(p);
        }

        Gun * g = new Gun();
        return new Enemy(enemy_sprite, 5, 1, bound, a, "Lesser Dog", 10, g);
    }

    else if (e == DweebFish) {
        QPixmap enemy_sprite = QPixmap(":/images/Dweebfish.png");
        enemy_sprite = enemy_sprite.scaled(300, 300, Qt::KeepAspectRatio);
        Bounds bound = {0, 0, 10000, 10000};
        std::vector<AttackPattern> a;
        int current_delay = 0;
        for (int i = 0; i < 11; i ++) {
            current_delay += 100;
            AttackPattern p = {current_delay, (x2 + x1) / 2 + i * 10, y2 - 10, Direction::N}; // 162 (362)
            AttackPattern p1 = {current_delay, (x2 + x1) / 2, y2 + 20, Direction::N}; // 162
            AttackPattern p2 = {current_delay, (x2 + x1) / 2 - i * 10, y2 - 10, Direction::N}; // 162 (362)
            a.push_back(p);
            a.push_back(p1);
            a.push_back(p2);
        }

        current_delay += 500;
        for (int i = 0; i < 11; i ++) {
            current_delay += 100;
            AttackPattern p = {current_delay, x2 + 20 + i * 10, y1 - 10, Direction::S}; // 162 (362)
            AttackPattern p1 = {current_delay, (x2 + x1) / 2, y1 - 10, Direction::S}; // 162
            AttackPattern p2 = {current_delay, x1 - 20 + i * 10, y1 - 10, Direction::S}; // 162 (362)
            a.push_back(p);
            a.push_back(p1);
            a.push_back(p2);
        }

        for (int i = 0; i < 11; i ++) {
            current_delay += 100;
            AttackPattern p = {current_delay, (x2 + x1) / 2 + i * 10, y2 - 10, Direction::N}; // 162 (362)
            AttackPattern p1 = {current_delay, (x2 + x1) / 2, y2 - 10, Direction::N}; // 162
            AttackPattern p2 = {current_delay, (x2 + x1) / 2 - i * 10, y2 - 10, Direction::N}; // 162 (362)
            a.push_back(p);
            a.push_back(p1);
            a.push_back(p2);
        }

        current_delay += 500;
        for (int i = 0; i < 11; i ++) {
            current_delay += 100;
            AttackPattern p = {current_delay, x2 + 20 - i * 10, y1 - 10, Direction::S}; // 162 (362)
            AttackPattern p1 = {current_delay, (x2 + x1) / 2, y1 - 10, Direction::S}; // 162
            AttackPattern p2 = {current_delay, x1 - 20 + i * 10, y1 - 10, Direction::S}; // 162 (362)
            a.push_back(p);
            a.push_back(p1);
            a.push_back(p2);
        }

        return new Enemy(enemy_sprite, 2, 1, bound, a, "Dweeb Fish", 10, nullptr);
    }

    else if (e == Canary) {
            QPixmap enemy_sprite = QPixmap(":/images/Canary.png");
            enemy_sprite = enemy_sprite.scaled(300, 300, Qt::KeepAspectRatio);
            int current_delay = 0;
            Bounds bound = {0, 0, 10000, 10000};
            std::vector<AttackPattern> a;
            for (int i = 0; i < 24; i ++) {
                current_delay += 200;
                AttackPattern p = {current_delay, x1 + 20+ i * 10, y2+ 10, Direction::N};
                AttackPattern p2 = {current_delay, x2 + 10, y1 + 10 + i * 10, Direction::W};
                a.push_back(p);
                a.push_back(p2);
            }

            for (int i = 0; i < 24; i ++) {
                current_delay += 200;
                AttackPattern p = {current_delay, x2 - i * 10, y2 - 20, Direction::N};
                AttackPattern p2 = {current_delay, x2 - 10, y2 - i * 10, Direction::W};
                a.push_back(p);
                a.push_back(p2);
            }



            Gun * g = new Gun();
            return new Enemy(enemy_sprite, 10, 1, bound, a, "Can-ary", 10, g);
    }



}
