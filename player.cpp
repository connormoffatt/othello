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

     color = side;
     if(side == BLACK) {
        oppColor = WHITE;
     }
     else {
        oppColor = BLACK;
     }
     // initialze the heuristic table
     initHeur();
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}


/*
* @brief This function returns the a move that it first encounters
* as valid.
*/
Move *Player::getAIWork() {
    // Loop through all squares on board
    for(int i = 0; i < BoardSize; i++) {
        for(int j = 0; j < BoardSize; j++) {
            Move *simpMove = new Move(i, j);
            // Check if move is valid
            if(board.checkMove(simpMove, color)) {
                // If so return the move
                return simpMove;
            }

        }
    }
    return nullptr;
}

/*
* @brief This function choose a random move based on a vector of all
* valid moves.
*/
Move *Player::getRandom() {
    srand (time(NULL));
    // Get all possible valid moves
    std::vector<Move *> valid = board.getMoves(color);
    // Pick random one and return it
    return valid[rand() % valid.size()];
}

/*
* @brief This function determins the players move based on heuristics.
* It figures out the best move based on the largest value.
*/
Move *Player::getHeuristic() {
    std::vector<Move *> valid = board.getMoves(color);

    int max_index = 0;
    int best_move = heur[valid[0]->getY()][valid[0]->getX()];
    int current_move;
    for(int i = 1; i < valid.size(); i++){
        current_move = heur[valid[i]->getY()][valid[i]->getX()];
        if(current_move > best_move){
            best_move = current_move;
            max_index = i;
        }
    }
    return valid[max_index];
}

Move *Player::getMinimax(){

    char boardData[64] = {
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', 'b', ' ', ' ', ' ', ' ', ' ', ' ',
        'b', 'w', 'b', 'b', 'b', 'b', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
    };

    if(testingMinimax == true)
    {
        board.setBoard(boardData);
    }
    // create two sets of vectors to represent valid moves for us and our
    // opponents
    std::vector<Move *> valid = board.getMoves(color);
    std::vector<Move *> validOpp;

    // create a vector that will contain the worst score at a depth of 2 for
    // us for each of our possible moves
    std::vector<int> small_score;


    // counters used to determine the min values at a depth of 2
    int worst_all, worst_curr;

    // counters when finding the max of all of the min values in small score
    int best_all,  best_return;


    // for loop that will itereate through all of our valid moves
    for(int i = 0; i < valid.size(); i++){
        // create temporary board and perform the current move in the for loop
        temp_board1 = board.copy();
        temp_board1->doMove(valid[i], color);

        // find the valid moves for the opponent for the move we just made
        validOpp = temp_board1->getMoves(oppColor);

        // check to see if our opponent has any valid moves. If our opponent
        // does not have any valid moves then we want to check to current 
        // board score
        if(validOpp.size() == 0){
            // calculate the current board score 
            worst_all = temp_board1->count(color) - \
                temp_board1->count(oppColor);
        }
        // If our opponent has valid moves, then we will iterate through them
        else{
            // initialize the value to be something greater than any possible
            // value. We will always find a board state smaller than this.
            worst_all = 100;

            // iterate through all of the opponents valid moves
            for(int j = 0; j < validOpp.size(); j++){
                // create temporary board at the depth of 2
                temp_board2 = temp_board1->copy();
                temp_board2->doMove(validOpp[j], oppColor);

                // find the current score of the current board
                worst_curr = temp_board2->count(color) - \
                    temp_board2->count(oppColor);

                // continually keep track of the worst total score for us in 
                // the set of our opponents move
                if(worst_curr < worst_all){
                    worst_all = worst_curr;
                }
            }
        }
        // after going through all of the opponenets move. Save the worst
        // board state that we can obtain for each of our moves and save into
        // a vector
        small_score.push_back(worst_all);

    }

    // set the initial index and high score to the first item in the small
    // score vector
    best_all = small_score[0];
    best_return = 0;

    // iterate through the rest of the small_score vector 
    for(int k = 1; k < valid.size(); k++){
        // check to see if our move has a higher minimum that previous
        if(small_score[k] > best_all)
        {
            // reset value and index to be returned
            best_all = small_score[k];
            best_return = k;

        }
    }
    // return the minimax move
    return valid[best_return];
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

    // Choose line of code below depening on which AI that needs to be run

    //Move *newMove = getAIWork();
    //Move *newMove = getRandom();
    //Move *newMove = getHeuristic();
    //Move *newMove = getMinimax();
    // *newMove = getMinimaxHeuristic();
    Move *newMove = getMinimaxHeuristic2();
    if(newMove != nullptr) {

        board.doMove(newMove, color);
    }
    
    return newMove;
}


Move *Player::getMinimaxHeuristic(){


    // create two sets of vectors to represent valid moves for us and our
    // opponents
    std::vector<Move *> valid = board.getMoves(color);
    std::vector<Move *> validOpp;

    // create a vector that will contain the worst score at a depth of 2 for
    // us for each of our possible moves
    std::vector<int> small_score;


    // counters used to determine the min values at a depth of 2
    int worst_all, worst_curr;

    // counters when finding the max of all of the min values in small score
    int best_all,  best_return;


    // for loop that will itereate through all of our valid moves
    for(int i = 0; i < valid.size(); i++){
        // create temporary board and perform the current move in the for loop
        temp_board1 = board.copy();
        temp_board1->doMove(valid[i], color);

        // find the valid moves for the opponent for the move we just made
        validOpp = temp_board1->getMoves(oppColor);

        // check to see if our opponent has any valid moves. If our opponent
        // does not have any valid moves then we want to check to current 
        // board score
        if(validOpp.size() == 0){
            // calculate the current board score
            //std::cerr << "Before opponenent doesnt have valid move" << std::endl;
            //worst_all = getHeuristic2(temp_board1);
            //std::cerr << "Opponnent doesn't have valid move: " << worst_all;
            worst_all = 50;

        }
        // If our opponent has valid moves, then we will iterate through them
        else{
            // initialize the value to be something greater than any possible
            // value. We will always find a board state smaller than this.
            worst_all = 100;

            // iterate through all of the opponents valid moves
            for(int j = 0; j < validOpp.size(); j++){
                // create temporary board at the depth of 2
                temp_board2 = temp_board1->copy();
                temp_board2->doMove(validOpp[j], oppColor);

                // find the current score of the current board
                worst_curr = getHeuristic2(temp_board2);

                // continually keep track of the worst total score for us in 
                // the set of our opponents move
                if(worst_curr < worst_all){
                    worst_all = worst_curr;
                }
            }
        }
        // after going through all of the opponenets move. Save the worst
        // board state that we can obtain for each of our moves and save into
        // a vector
        small_score.push_back(worst_all);

    }

    // set the initial index and high score to the first item in the small
    // score vector
    best_all = small_score[0];
    best_return = 0;

    //if(valid.size() != 0){
        // iterate through the rest of the small_score vector 
        for(int k = 1; k < valid.size(); k++){
            // check to see if our move has a higher minimum that previous
            if(small_score[k] > best_all)
            {
                // reset value and index to be returned
                best_all = small_score[k];
                best_return = k;

            }
        }
    //}
    // return the minimax move
    return valid[best_return];
}


int Player::getHeuristic2(Board * b) {
    std::vector<Move *> valid = b->getMoves(color);
    if(valid.size() != 0){
        int best_move = heur[valid[0]->getY()][valid[0]->getX()];
        int current_move;
        
            for(int i = 1; i < valid.size(); i++){
                current_move = heur[valid[i]->getY()][valid[i]->getX()];
                if(current_move > best_move){
                    best_move = current_move;
                }
            }
        return best_move;
    }
    return 50;
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



Move *Player::getMinimaxHeuristic2(){


    // create two sets of vectors to represent valid moves for us and our
    // opponents
    std::vector<Move *> valid = board.getMoves(color);
    std::vector<Move *> validOpp;

    // create a vector that will contain the worst score at a depth of 2 for
    // us for each of our possible moves
    std::vector<int> small_score;


    // counters used to determine the min values at a depth of 2
    int worst_all, worst_curr;

    // counters when finding the max of all of the min values in small score
    int best_all,  best_return;

    int current_score;

    // for loop that will itereate through all of our valid moves
    for(int i = 0; i < valid.size(); i++){

        // calculate the current score

        current_score = heur[valid[i]->getY()][valid[i]->getX()];

        // create temporary board and perform the current move in the for loop
        temp_board1 = board.copy();
        temp_board1->doMove(valid[i], color);

        // find the valid moves for the opponent for the move we just made
        validOpp = temp_board1->getMoves(oppColor);

        // check to see if our opponent has any valid moves. If our opponent
        // does not have any valid moves then we want to check to current 
        // board score
        if(validOpp.size() == 0){
            // calculate the current board score
            //std::cerr << "Before opponenent doesnt have valid move" << std::endl;
            //worst_all = getHeuristic2(temp_board1);
            //std::cerr << "Opponnent doesn't have valid move: " << worst_all;
            worst_all = 50;

        }
        // If our opponent has valid moves, then we will iterate through them
        else{
            // initialize the value to be something greater than any possible
            // value. We will always find a board state smaller than this.
            worst_all = 100;

            // iterate through all of the opponents valid moves
            for(int j = 0; j < validOpp.size(); j++){
                // create temporary board at the depth of 2
                temp_board2 = temp_board1->copy();
                temp_board2->doMove(validOpp[j], oppColor);

                // find the current score of the current board
                worst_curr = getHeuristic2(temp_board2);

                // continually keep track of the worst total score for us in 
                // the set of our opponents move
                if(worst_curr < worst_all){
                    worst_all = worst_curr;
                }
            }
        }
        // after going through all of the opponenets move. Save the worst
        // board state that we can obtain for each of our moves and save into
        // a vector
        small_score.push_back(worst_all + current_score);

    }

    // set the initial index and high score to the first item in the small
    // score vector
    best_all = small_score[0];
    best_return = 0;

    //if(valid.size() != 0){
        // iterate through the rest of the small_score vector 
        for(int k = 1; k < valid.size(); k++){
            // check to see if our move has a higher minimum that previous
            if(small_score[k] > best_all)
            {
                // reset value and index to be returned
                best_all = small_score[k];
                best_return = k;

            }
        }
    //}
    // return the minimax move
    return valid[best_return];
}