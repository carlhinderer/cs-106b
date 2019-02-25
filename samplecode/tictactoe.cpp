/* 
 * File: tictactoe.cpp 
 * ------------------- 
 * This program plays a game of tic-tac-toe with the user.  The 
 * code is designed to make it easy to adapt the general structure 
 * to other games. 
 */

#include "genlib.h"
#include "simpio.h"
#include "vector.h"
#include "grid.h"
#include <iostream>

/* 
 * Constants: WINNING_POSITION, NEUTRAL_POSITION, LOSING_POSITION 
 * -------------------------------------------------------------- 
 * These constants define a rating system for game positions.  A 
 * rating is an integer centered at 0 as the neutral score: ratings 
 * greater than 0 are good for the current player, ratings less than 
 * 0 are good for the opponent.  The constants WINNING_POSITION and 
 * LOSING_POSITION are opposite in value and indicate a position that 
 * is a forced win or loss, respectively.  In a game in which the 
 * analysis is complete, no intermediate values ever arise.  If the 
 * full tree is too large to analyze, the EvaluatePosition function 
 * returns integers that fall between the two extremes. 
 */

const int WINNING_POSITION  = 1000;
const int NEUTRAL_POSITION  = 0;
const int LOSING_POSITION   = -WINNING_POSITION;

/* 
 * Type: playerT 
 * ------------- 
 * This type is used to distinguish the human and computer 
 * players and keep track of who has the current turn. 
 */

enum playerT { Human, Computer };

/* 
 * Type: moveT 
 * ----------- 
 * For any particular game, the moveT type must keep track of the 
 * information necessary to describe a move.  For tic-tac-toe, 
 * a moveT is simply an integer identifying the number of one of 
 * the nine squares, as follows: 
 * 
 *        1 | 2 | 3 
 *       ---+---+--- 
 *        4 | 5 | 6 
 *       ---+---+--- 
 *        7 | 8 | 9 
 */

typedef int moveT;

/* 
 * Type: stateT 
 * ------------ 
 * For any game, the stateT structure records the current state of 
 * the game.  As in Chapter 4, the tic-tac-toe board is represented 
 * using a Grid<char>; the elements must be either 'X', 'O', or ' '. 
 * In addition to the board array, the code stores a playerT value 
 * to indicate whose turn it is.  In this game, the stateT structure 
 * also contains the total number of moves so that functions can 
 * find this value without counting the number of occupied squares. 
 */

struct stateT {Grid<char> board;playerT whoseTurn;int turnsTaken;};

/* 
 * Constant: MAX_DEPTH 
 * ------------------- 
 * This constant indicates the maximum depth to which the recursive 
 * search for the best move is allowed to proceed. 
 */

const int MAX_DEPTH = 10000;

/* 
 * Constant: FIRST_PLAYER 
 * ---------------------- 
 * This constant indicates which player goes first. 
 */

const playerT FIRST_PLAYER = Computer;

/* Private function prototypes */
void GiveInstructions();
moveT FindBestMove(stateT state, int depth, int & pRating);
int EvaluatePosition(stateT state, int depth);
stateT NewGame();
void DisplayGame(stateT state);
void DisplayMove(moveT move);
char PlayerMark(playerT player);
moveT GetUserMove(stateT state);
moveT ChooseComputerMove(stateT state);
void GenerateMoveList(stateT state, Vector<moveT> & moveList);
bool MoveIsLegal(moveT move, stateT state);
void MakeMove(stateT & state, moveT move);
void RetractMove(stateT & state, moveT move);
bool GameIsOver(stateT state);
void AnnounceResult(stateT state);
playerT WhoseTurn(stateT state);
playerT Opponent(playerT player);
int EvaluateStaticPosition(stateT state);
bool CheckForWin(stateT state, playerT player);
bool CheckForWin(Grid<char> & board, char mark);
bool CheckLine(Grid<char> & board, char mark, int row, int col, int dRow, int dCol);

/* 
 * Main program 
 * ------------ 
 * The main program, along with the functions FindBestMove and 
 * EvaluatePosition, are general in their design and can be 
 * used with most two-player games.  The specific details of 
 * tic-tac-toe do not appear in these functions and are instead 
 * encapsulated in the stateT and moveT data structures and a 
 * a variety of subsidiary functions. 
 */

int main() {
    GiveInstructions();
    stateT state = NewGame();
    moveT move;
    while (!GameIsOver(state)) {
        DisplayGame(state);
        switch (WhoseTurn(state)) {  
            case Human:
                move = GetUserMove(state);
                break;
            case Computer:
                move = ChooseComputerMove(state);
                DisplayMove(move);
                break;
        }
        MakeMove(state, move);
    }
    AnnounceResult(state);
    return 0;
}

/* 
 * Function: GiveInstructions 
 * Usage: GiveInstructions(); 
 * -------------------------- 
 * This function gives the player instructions about how to 
 * play the game. 
 */

void GiveInstructions() {
    cout << "Welcome to tic-tac-toe.  The object of the game" << endl;
    cout << "is to line up three symbols in a row," << endl;
    cout << "vertically, horizontally, or diagonally." << endl;
    cout << "You'll be " << PlayerMark(Human) << " and I'll be "
         << PlayerMark(Computer) << "." << endl;
}

/* 
 * Function: NewGame 
 * Usage: state = NewGame(); 
 * ------------------------- 
 * This function starts a new game and returns a stateT that 
 * has been initialized to the defined starting configuration. 
 */

stateT NewGame() {
    stateT state;
    state.board.resize(3, 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            state.board[i][j] = ' ';
        }
    }
    state.whoseTurn = FIRST_PLAYER;
    state.turnsTaken = 0;
    return state;
}

/* 
 * Function: DisplayGame 
 * Usage: DisplayGame(state); 
 * -------------------------- 
 * This function displays the current state of the game. 
 */

void DisplayGame(stateT state) {
    if (GameIsOver(state)) {
        cout << "The final position looks like this:" << endl << endl;
    } else {
        cout << "The game now looks like this:" << endl << endl;
    }

    for (int i = 0; i < 3; i++) {
        if (i != 0) cout << "---+---+---" << endl;
        for (int j = 0; j < 3; j++) {
            if (j != 0) cout << "|";
            cout << " " << state.board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

/* 
 * Function: DisplayMove 
 * Usage: DisplayMove(move); 
 * ------------------------- 
 * This function displays the computer's move. 
 */

void DisplayMove(moveT move) {
    cout << "I'll move to " << move << endl;
}

/* 
 * Function: FindBestMove 
 * Usage: move = FindBestMove(state, depth, pRating); 
 * -------------------------------------------------- 
 * This function finds the best move for the current player, given 
 * the specified state of the game.  The depth parameter and the 
 * constant MAX_DEPTH are used to limit the depth of the search 
 * for games that are too difficult to analyze in full detail. 
 * The function returns the best move by storing an integer in 
 * the variable to which pRating points. 
 */

moveT FindBestMove(stateT state, int depth, int & rating) {
    Vector<moveT> moveList;
    GenerateMoveList(state, moveList);
    int nMoves = moveList.size();
    if (nMoves == 0) Error("No moves available");
    moveT bestMove;
    int minRating = WINNING_POSITION + 1;
    for (int i = 0; i < nMoves && minRating != LOSING_POSITION; i++) {
        moveT move = moveList[i];
        MakeMove(state, move);
        int curRating = EvaluatePosition(state, depth + 1);
        if (curRating < minRating) {
            bestMove = move;
            minRating = curRating;
        }
        RetractMove(state, move);
    }
    rating = -minRating;
    return bestMove;
}

/* 
 * Function: EvaluatePosition 
 * Usage: rating = EvaluatePosition(state, depth); 
 * ----------------------------------------------- 
 * This function evaluates a position by finding the rating of 
 * the best move in that position.  The depth parameter and the 
 * constant MAX_DEPTH are used to limit the depth of the search. 
 */

int EvaluatePosition(stateT state, int depth) {
    int rating;
    if (GameIsOver(state) || depth >= MAX_DEPTH) {
        return EvaluateStaticPosition(state);
    }
    FindBestMove(state, depth, rating);
    return rating;
}

/* 
 * Function: NewGame 
 * Usage: state = NewGame(); 
 * ------------------------- 
 * This function starts a new game and returns a stateT that 
 * has been initialized to the defined starting configuration. 
 */

stateT NewGame() {    
    stateT state;    
    for (int i = 1; i <= 9; i++) {
        state.board[i] = ' ';
    }
    state.whoseTurn = FIRST_PLAYER;
    state.turnsTaken = 0;
    return state;
}

/* 
 * Function: DisplayGame 
 * Usage: DisplayGame(state); 
 * -------------------------- 
 * This function displays the current state of the game. 
 */

void DisplayGame(stateT state) {    
    if (GameIsOver(state)) {
        cout << "The final position looks like this:" << endl << endl;
    } else {
        cout << "The game now looks like this:" << endl << endl;
    }

    for (int row = 0; row < 3; row++) {
        if (row != 0) cout << "---+---+---" << endl;
        for (int col = 0; col < 3; col++) {
            if (col != 0) cout << "|";
            cout << " " << state.board[row * 3 + col + 1] << " ";
        }
        cout << endl;    
    }
    cout << endl;
}

/* 
 * Function: DisplayMove 
 * Usage: DisplayMove(move); 
 * ------------------------- 
 * This function displays the computer's move. 
 */

void DisplayMove(moveT move) {
    cout << "I'll move to " << move << endl;
}