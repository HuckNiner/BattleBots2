#include <iostream>
#include "simplebot.h"

enum class Direction { None, Right, Left };

SimpleBot::SimpleBot() {
    srand(time(nullptr));
}

// EntityType { TankA, TankB, TankC, TankD, WallNS, WallEW, WallN, WallS, WallE, WallW, Tower, CornerEN, CornerES, CornerWN, CornerWS, Tree, Rock1, Rock2, Exit };

bool turnNeeded = false;
Direction lastDir = Direction::Right;
int state = 1;

void SimpleBot::takeTurn() {
    EntityData info = nullptr;

    if (amOnExit()) {
        return;
    }

    switch (state) {
    case 1:
        if (frontIsClear()) {
            move();
        }
        else {
            state = 2;
        }
        break;

    case 2:
        info = scan();
        switch (info.getType()) {
        case Exit:
        case Tower:
        case Tree:
        case Rock1:
        case Rock2:
            std::cout << "Rock, tower, tree encountered" << std::endl;
            if (rightIsClear() && rand() % 2 == 0) {
                state = 5;
                turnRight();
                break;
            }
            else if (leftIsClear() && rand() % 2 == 1) {
                state = 5;
                turnLeft();
                break;
            }
            else {
                if (lastDir == Direction::Right) {
                    state = 3;
                    turnLeft();
                    lastDir = Direction::Left;
                }
                else {
                    turnRight();
                    state = 3;
                    lastDir = Direction::Right;
                }
            }
            break;

        default:
            if (lastDir == Direction::Right) {
                turnLeft();
                state = 3;
                lastDir = Direction::Left;
            }
            else {
                turnRight();
                state = 3;
                lastDir = Direction::Right;
            }
            break;
        }
        break;

    case 3:
        info = scan();
        if (info.getType() == Exit) {
            state = 1;
            break;
        }
        else if (!frontIsClear() && (info.getType() == Tower || info.getType() == Tree || info.getType() == Rock1 || info.getType() == Rock2)) {
            state = 2;
            cout << "2 triggered again because in front is an obstacle" << endl;
            break;
        }

        if (frontIsClear()) {
            move();
            std::cout << "Moving forward" << std::endl;
            state = 4;
            turnNeeded = true;
        }
        else {
            state = 4;
            turnNeeded = false;
        }
        break;

    case 4:
        if (turnNeeded) {
            if (lastDir == Direction::Left) {
                turnLeft();
                lastDir = Direction::Right;
            }
            else {
                turnRight();
                lastDir = Direction::Left;
            }
            turnNeeded = false;
        }
        if (lastDir == Direction::Left) {
            turnLeft();
            lastDir = Direction::Right;
        }
        else {
            turnRight();
            lastDir = Direction::Left;
        }
        state = 1;
        break;

    case 5:
        if (frontIsClear()) {
            state = 6;
            std::cout << state << std::endl;
            turnNeeded = true;
            move();
            std::cout << "case 5 triggered" << std::endl;
        }
        else {
            std::cout << "case 5 blocked" << std::endl;
            state = 6;
            turnNeeded = false;
        }
        break;

    case 6:
        if (turnNeeded) {
            if (lastDir == Direction::Left) {
                turnRight();
            }
            else {
                turnLeft();
                lastDir = Direction::Left;
            }
        }
        state = 1;
        break;
    }
}