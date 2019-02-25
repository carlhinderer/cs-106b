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