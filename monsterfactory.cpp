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
        for (int i = 0; i < 5; i ++) {
            AttackPattern p = {current_delay, x1_start + i * 100, y1_start, Direction::S};
            AttackPattern p2 = {current_delay, x2_start - i * 100, y2_start, Direction::N};
            pattern_1.push_back(p);
            pattern_1.push_back(p2);
        }

         current_delay += 1000;
        for (int i = 0; i < 5; i ++) {
            AttackPattern p = {current_delay, x1_start, y1_start + i * 100, Direction::E};
            AttackPattern p2 = {current_delay, x2_start, y2_start - i * 100, Direction::W};
            pattern_1.push_back(p);
            pattern_1.push_back(p2);
        }
        current_delay += 1000;
        for (int i = 0; i < 5; i ++) {
            AttackPattern p = {current_delay, x1_start + i * 100, y1_start, Direction::S};
            AttackPattern p2 = {current_delay, x2_start - i * 100, y2_start, Direction::N};
            pattern_1.push_back(p);
            pattern_1.push_back(p2);
        }

        current_delay += 1000;
       for (int i = 0; i < 5; i ++) {
           AttackPattern p = {current_delay, x1_start, y1_start + i * 100, Direction::E};
           AttackPattern p2 = {current_delay, x2_start, y2_start - i * 100, Direction::W};
           pattern_1.push_back(p);
           pattern_1.push_back(p2);
       }

        patterns.push_back(pattern_1);

        //Pattern 2
        std::vector<AttackPattern> pattern_2;

        current_delay = 0;
        for (int i = 0; i < 10; i ++) {
            AttackPattern p = {current_delay, x_center, y1_start, Direction::S};
            current_delay += 50;
            AttackPattern p2 = {current_delay, x_center + i * 10, y1_start, Direction::S};
            current_delay += 50;
            AttackPattern p3 = {current_delay, x_center - i * 10, y1_start, Direction::S};

            pattern_2.push_back(p);
            pattern_2.push_back(p2);
            pattern_2.push_back(p3);

        }
        current_delay += 150;
        pattern_2.push_back({current_delay, x1_start + 20, y1_start, Direction::S});
        pattern_2.push_back({current_delay, x2_start - 20, y1_start, Direction::S});

        for (int i = 0; i < 10; i ++) {
            AttackPattern p = {current_delay, x_center, y2_start, Direction::N};
            current_delay += 50;
            AttackPattern p2 = {current_delay, x_center + i * 10, y2_start, Direction::N};
            current_delay += 50;
            AttackPattern p3 = {current_delay, x_center - i * 10, y2_start, Direction::N};

            pattern_2.push_back(p);
            pattern_2.push_back(p2);
            pattern_2.push_back(p3);

        }
        current_delay += 150;
        pattern_2.push_back({current_delay, x1_start + 20, y2_start, Direction::N});
        pattern_2.push_back({current_delay, x2_start - 20, y2_start, Direction::N});

        patterns.push_back(pattern_2);





        Gun * g = new Gun();
        return new Enemy(enemy_sprite, 5, 2, bound, patterns, "Lesser Dog", 10, g, "qrc:/sounds/glame.mp3");
    }

    else if (e == DweebFish) {
        QPixmap enemy_sprite = QPixmap(":/images/Dweebfish.png");
        enemy_sprite = enemy_sprite.scaled(300, 300, Qt::KeepAspectRatio);
        Bounds bound = {0, 0, 10000, 10000};
        std::vector<std::vector<AttackPattern>> a;
        int current_delay = 0;

        //Pattern 1
        std::vector<AttackPattern> pattern_1;


        for (int k = 0; k < 2; k ++) {

            for (int i = 0; i < 17; i ++) {
                current_delay += 80;
                pattern_1.push_back({current_delay, x1_start + 6 * i, y1_start, Direction::S });
                pattern_1.push_back({current_delay, x2_start - 6 * i, y1_start, Direction::S });

            }

            for (int i = 0; i < 17; i ++) {
                current_delay += 80;
                pattern_1.push_back({current_delay, x_center + 6 * i, y2_start, Direction::N });
                pattern_1.push_back({current_delay, x_center - 6 * i, y2_start, Direction::N });

            }

        }

        for (int i = 0; i < current_delay; i += 100) {
            pattern_1.push_back({i, x_center, y2_start, Direction::N});
        }

        a.push_back(pattern_1);

        //Pattern 2

       std::vector<AttackPattern> pattern_2;

        current_delay = 0;
        for (int i = 0; i < 50; i ++) {
            if (rand() % 2 == 0) {
                current_delay += 100;
                int pos = rand() % 300;
                pattern_2.push_back({current_delay, x1_start + pos, y1_start, Direction::S});
            }
        }

        current_delay = 0;
        for (int i = 0; i < 50; i ++) {
            if (rand() % 2 == 0) {
                current_delay += 100;
                int pos = rand() % 275;
                pattern_2.push_back({current_delay, x1_start, y1_start + pos, Direction::W});
            }
        }

        current_delay = 0;
        for (int i = 0; i < 50; i ++) {
            if (rand() % 2 == 0) {
                current_delay += 100;
                int pos = rand() % 275;
                pattern_2.push_back({current_delay, x2_start , y1_start + pos, Direction::E});
            }
        }

        current_delay = 0;
        for (int i = 0; i < 50; i ++) {
            if (rand() % 2 == 0) {
                current_delay += 100;
                int pos = rand() % 300;
                pattern_2.push_back({current_delay, x1_start + pos, y2_start, Direction::N});
            }
        }

        a.push_back(pattern_2);


        return new Enemy(enemy_sprite, 5, 1, bound, a, "Dweeb Fish", 10, nullptr, "qrc:/sounds/thunder.mp3");
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
            return new Enemy(enemy_sprite, 5, 1, bound, patterns, "Can-ary", 10, g, "qrc:/sounds/can.mp3");
    }

    if (e == Helix) {
        QPixmap enemy_sprite = QPixmap(":/images/helix.png");
        enemy_sprite = enemy_sprite.scaled(300, 300, Qt::KeepAspectRatio);
        std::vector<std::vector<AttackPattern>> patterns;
        int current_delay = 0;
        Bounds bound = {0, 0, 10000, 10000};

        std::vector<AttackPattern> pattern_1;
        for (int i = 0; i < 5; i ++) {
            for (int i = 0; i < 10; i ++) {
                current_delay += 100;
                pattern_1.push_back({current_delay, x_center - 100 + (i * 20), y2_start, Direction::N});
                pattern_1.push_back({current_delay, x_center + 100 - (i * 20), y2_start, Direction::N});
            }
            pattern_1.push_back({current_delay, x1_start + 20, y1_start, Direction::S});
            pattern_1.push_back({current_delay, x2_start - 20, y1_start, Direction::S});
        }


//        patterns.push_back(pattern_1);

        std::vector<AttackPattern> pattern_2;
        current_delay = 0;
        for (int i = 0; i < 5; i ++) {
            for (int i = 0; i < 10; i ++) {
                current_delay += 150;
                pattern_2.push_back({current_delay, x1_start, y_center + 125 - (i * 8), Direction::E});
                pattern_2.push_back({current_delay, x1_start, y_center - 100 - (i * 8), Direction::E});
                pattern_2.push_back({current_delay, x1_start, y_center - (i * 8), Direction::E});

            }
        }
        patterns.push_back(pattern_2);



        Gun * g = new Gun();
        return new Enemy(enemy_sprite, 5, 2, bound, patterns, "Helix Muzny", 10, g, "qrc:/sounds/glame.mp3");
    }


}
