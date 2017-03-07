#include "player.hpp"

#define BoardSize 8
/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
     color = side;
     if(side == BLACK) {
        oppColor = WHITE;
     }
     else {
        oppColor = BLACK;
     }
     initHeur();

}

/*
 * Destructor for the player.
 */
Player::~Player() {
}


Move *Player::getAIWork() {
    for(int i = 0; i < BoardSize; i++) {
        for(int j = 0; j < BoardSize; j++) {
            Move *simpMove = new Move(i, j);
            if(board.checkMove(simpMove, color)) {
                return simpMove;
            }

        }
    }
    return nullptr;
}

Move *Player::getRandom() {
    srand (time(NULL));
    std::vector<Move *> valid = board.getMoves(color);
    return valid[rand() % valid.size()];
}

Move *Player::getHeuristic() {
    std::vector<Move *> valid = board.getMoves(color);

    int max_index = 0;
    int best_move = heur[valid[0]->getY()][valid[0]->getX()];
    int current_move;
    //std::cerr<<"best move: "<< best_move <<std::endl;
    //std::cerr<<"max index: "<< max_index<<std::endl;
    for(int i = 1; i < valid.size(); i++){
        current_move = heur[valid[i]->getY()][valid[i]->getX()];
        if(current_move > best_move){
            best_move = current_move;
            max_index = i;
        }
    }
    return valid[max_index];
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    board.doMove(opponentsMove, oppColor);

    if(!board.hasMoves(color)) {
        return nullptr;
    }
    //Move *newMove = getAIWork();
    //Move *newMove = getRandom();
    Move *newMove = getHeuristic();

    if(newMove != nullptr) {

        board.doMove(newMove, color);
        //std::cerr<<"yes"<<std::endl;
    }
    
    return newMove;
}

/*
 * This function will initialize the heuristic table
 *
 */

void Player::initHeur(){
    // first row
    heur[0][0] = 10;
    heur[0][1] = -2;
    heur[0][2] = 5;
    heur[0][3] = 5;
    heur[0][4] = 5;
    heur[0][5] = 5;
    heur[0][6] = -2;
    heur[0][7] = 10;

    // second row
    heur[1][0] = -2;
    heur[1][1] = -5;
    heur[1][2] = -3;
    heur[1][3] = -1;
    heur[1][4] = -1;
    heur[1][5] = -3;
    heur[1][6] = -5;
    heur[1][7] = -2;

    // third row
    heur[2][0] = 5;
    heur[2][1] = -3;
    heur[2][2] = 3;
    heur[2][3] = 1;
    heur[2][4] = 1;
    heur[2][5] = 3;
    heur[2][6] = -3;
    heur[2][7] = 5;

    // fourth row
    heur[3][0] = 5;
    heur[3][1] = -1;
    heur[3][2] = 1;
    heur[3][3] = 0;
    heur[3][4] = 0;
    heur[3][5] = 1;
    heur[3][6] = -1;
    heur[3][7] = 5;

    // fifth row
    heur[4][0] = 5;
    heur[4][1] = -1;
    heur[4][2] = 1;
    heur[4][3] = 0;
    heur[4][4] = 0;
    heur[4][5] = 1;
    heur[4][6] = -1;
    heur[4][7] = 5;

    // sixth row
    heur[5][0] = 5;
    heur[5][1] = -3;
    heur[5][2] = 3;
    heur[5][3] = 1;
    heur[5][4] = 1;
    heur[5][5] = 3;
    heur[5][6] = -3;
    heur[5][7] = 5;

    // seventh row
    heur[6][0] = -2;
    heur[6][1] = -5;
    heur[6][2] = -3;
    heur[6][3] = -1;
    heur[6][4] = -1;
    heur[6][5] = -3;
    heur[6][6] = -5;
    heur[6][7] = -2;

    // eigth row
    heur[7][0] = 10;
    heur[7][1] = -2;
    heur[7][2] = 5;
    heur[7][3] = 5;
    heur[7][4] = 5;
    heur[7][5] = 5;
    heur[7][6] = -2;
    heur[7][7] = 10;

}
