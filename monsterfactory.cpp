#include "monsterfactory.h"
#include "gun.h"
/*
Function: MonsterFactory Constructor
Params: none
Desc:
Returns: none
*/
MonsterFactory::MonsterFactory()
{

}

/*
Function: GetEnemy
Params: EnemyType, which enemy to get
Desc: Given an enemy type, will return a fully created Enemy class
Returns: Enemy, enemy requested
*/
Enemy * MonsterFactory::GetEnemy(EnemyType e) {
    int x1 = 700;
    int y1 = 400;
    int x2 = x1 + 300;
    int y2 = y1 + 275;

    int x1_start = x1 - 30;
    int y1_start = y1 - 20;
    int x2_start = x2;
    int y2_start = y2 + 20;

    int x_center = (x1_start + x2_start + 10) / 2;
    int y_center = (y1_start + y2_start + 10) / 2;

    if (e == LesserDog) {
        QPixmap enemy_sprite = QPixmap(":/images/Gr8.png");
        enemy_sprite = enemy_sprite.scaled(300, 300, Qt::KeepAspectRatio);
        std::vector<std::vector<AttackPattern>> patterns;
        int current_delay = 0;
        Bounds bound = {0, 0, 10000, 10000};

        std::vector<AttackPattern> pattern_1;
        pattern_1.push_back({0, x1_start, y1_start, Direction::SE});
        pattern_1.push_back({0, x2_start, y2_start, Direction::NW});
        for (int i = 0; i < 24; i ++) {
            current_delay += 100;
            AttackPattern p = {current_delay, x1_start + i * 10, y2_start, Direction::N};
            AttackPattern p2 = {current_delay, x2_start, y1_start + (i * 10), Direction::W};
            pattern_1.push_back(p);
            pattern_1.push_back(p2);
        }

        for (int i = 0; i < 24; i ++) {
            current_delay += 100;
            AttackPattern p = {current_delay, x2_start - i * 10, y2_start, Direction::N};
            AttackPattern p2 = {current_delay, x2_start, y2_start - i * 10, Direction::W};
            pattern_1.push_back(p);
            pattern_1.push_back(p2);
        }

        patterns.push_back(pattern_1);


        Gun * g = new Gun();
        return new Enemy(enemy_sprite, 5, 1, bound, patterns, "Lesser Dog", 10, g);
    }

    else if (e == DweebFish) {
        QPixmap enemy_sprite = QPixmap(":/images/Dweebfish.png");
        enemy_sprite = enemy_sprite.scaled(300, 300, Qt::KeepAspectRatio);
        Bounds bound = {0, 0, 10000, 10000};
        std::vector<std::vector<AttackPattern>> a;
        int current_delay = 0;


        return new Enemy(enemy_sprite, 2, 1, bound, a, "Dweeb Fish", 10, nullptr);
    }

    else if (e == Canary) {
            QPixmap enemy_sprite = QPixmap(":/images/Canary.png");
            enemy_sprite = enemy_sprite.scaled(300, 300, Qt::KeepAspectRatio);
            int current_delay = 0;
            Bounds bound = {0, 0, 10000, 10000};
            std::vector<std::vector<AttackPattern>> patterns;

//            Code for attack pattern 1
            std::vector<AttackPattern> pattern_1;
            pattern_1.push_back({0, x1_start, y1_start, Direction::SE});
            pattern_1.push_back({0, x2_start, y2_start, Direction::NW});
            for (int i = 0; i < 24; i ++) {
                current_delay += 100;
                AttackPattern p = {current_delay, x1_start + i * 10, y2_start, Direction::N};
                AttackPattern p2 = {current_delay, x2_start, y1_start + (i * 10), Direction::W};
                pattern_1.push_back(p);
                pattern_1.push_back(p2);
            }

            for (int i = 0; i < 24; i ++) {
                current_delay += 100;
                AttackPattern p = {current_delay, x2_start - i * 10, y2_start, Direction::N};
                AttackPattern p2 = {current_delay, x2_start, y2_start - i * 10, Direction::W};
                pattern_1.push_back(p);
                pattern_1.push_back(p2);
            }

            patterns.push_back(pattern_1);

            //Code for attack pattern 2
            current_delay = 0;
            std::vector<AttackPattern> pattern_2;
            for (int i = 0; i < 22; i ++) {
                current_delay += 200;
                AttackPattern p = {current_delay, x1_start + 20 + (i * 10), y2_start, Direction::NE};
                AttackPattern p2 = {current_delay, x2_start - 20 + (i * -10), y1_start, Direction::SW};
                pattern_2.push_back(p);
                pattern_2.push_back(p2);
            }
            current_delay += 200;
            for (int i = 0; i < 22; i ++) {
                current_delay += 200;
                AttackPattern p = {current_delay, x1_start + 10 + (i * 10), y1_start, Direction::SE};
                AttackPattern p2 = {current_delay, x2_start - 10 - (i * 10), y2_start, Direction::NW};
                pattern_2.push_back(p);
                pattern_2.push_back(p2);
            }

            patterns.push_back(pattern_2);



            Gun * g = new Gun();
            return new Enemy(enemy_sprite, 10, 1, bound, patterns, "Can-ary", 10, g);
    }



}
