#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <time.h>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

private:
    Board board;
    Side color;
    Side oppColor;
    int heur[8][8];

public:
    Player(Side side);
    ~Player();

    Move *getAIWork();
    Move *getRandom();
    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
