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
    Move *newMove = getAIWork();
    if(newMove != nullptr) {
        board.doMove(newMove, color);
    }
    
    return newMove;
}
