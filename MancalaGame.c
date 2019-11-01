/*-------------------------------------------------------------------------
 Include files:
 --------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/*=========================================================================
 Constants and definitions:
 ==========================================================================*/

/* put your #defines and typedefs here*/
#define PLAYER1 1
#define PLAYER2 2
#define NOBODY -1
#define HOME1 6
#define HOME2 13
#define WIDTH 2
#define NUM_OF_HOLES 14
#define LAST_HOLE_P1 6
#define LAST_HOLE_P2 13
#define FIRST_HOLE_P1 0
#define FIRST_HOLE_P2 7
#define INITIAL_NUM_STONES 6
#define END 0
#define STILL_PLAYING 0
#define EMPTY 0
#define ERROR 1
#define INVALID -1
#define LAST_STONE 1
#define INITIALIZED 0
#define PROBLEM 2
#define VALID 1
#define END_OF_GAME 1
#define ONE 1
#define TWO 2

/* PRINTING FUNCTIONS DECLARATIONS*/
void PrintWelcomeMessage();
void PrintBoard(int board[]);
void PrintTurn(int player);
void PrintChooseCell();
void PrintScanfFailure();
void PrintInvalidValue();
void PrintEmptyCell();
void PrintWinningMessage(int winner);
void InitializeGameBoard(int gameBoard[NUM_OF_HOLES]);
int CheckInput (bool Empty, bool CurPlayerInd, int gameBoard[NUM_OF_HOLES]
                ,int Player);
bool MoveStones (int Stones, int gameBoard[NUM_OF_HOLES], int Counter,
                 int Player);
int CalcPlayerStones (int gameBoard[NUM_OF_HOLES], int Player);
bool CheckExtraTurn (int Stones, int Player, int Counter);
int CheckNextJump (int Counter, int Player);
int CheckWinner (int gameBoard[NUM_OF_HOLES]);
int FinalBoardStat (int SumP1, int SumP2, int gameBoard[NUM_OF_HOLES]);
int CheckNextTurn (int Player, bool ExtraTurn);
int GameProcess (int gameBoard[NUM_OF_HOLES]);
void PrintPlayerAndCell(int Player);


/*-------------------------------------------------------------------------
 The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
int main()
{
    int gameBoard[NUM_OF_HOLES] = { INITIALIZED };
    InitializeGameBoard(gameBoard);
    PrintWelcomeMessage();
    PrintBoard(gameBoard);
    if (GameProcess(gameBoard)) {
        return ERROR;
    }
    return END;
}

// print the player who play and to choose cell.
void PrintPlayerAndCell (int Player){
    PrintTurn(Player);
    PrintChooseCell();
}

// the process of the game from the beginnig until the end (23).
int GameProcess(int gameBoard[NUM_OF_HOLES]){
    int Player=PLAYER1, ChosenCell=INITIALIZED, Stones=INITIALIZED,
    Counter=INITIALIZED, SumP1=INITIALIZED, SumP2=INITIALIZED,
    Winner=INITIALIZED;
    bool ExtraTurn = false, Empty=true, CurPlayerInd=false;
    
    while (Winner == STILL_PLAYING) {
        PrintPlayerAndCell(Player);
        ChosenCell = CheckInput(Empty, CurPlayerInd, gameBoard, Player);
        if (ChosenCell==INVALID) {
            return ERROR;
        }
        
        Stones = gameBoard[ChosenCell];
        gameBoard[ChosenCell] = EMPTY;
        Counter = ChosenCell+ONE;
        
        ExtraTurn = MoveStones(Stones, gameBoard, Counter, Player);
        
        SumP1 = CalcPlayerStones(gameBoard, PLAYER1);
        SumP2 = CalcPlayerStones(gameBoard, PLAYER2);
        
        if (FinalBoardStat(SumP1, SumP2, gameBoard)) {
            Winner = CheckWinner(gameBoard);
            return END;
        }else{
            PrintBoard(gameBoard);
        }
        SumP1 = INITIALIZED;
        SumP2 = INITIALIZED;
        
        Player = CheckNextTurn(Player, ExtraTurn);
        ExtraTurn = false;
    }
    return PROBLEM;
}

// Prepare the board to the start status (4).
void InitializeGameBoard(int gameBoard[NUM_OF_HOLES]){
    for (int i = FIRST_HOLE_P1; i<LAST_HOLE_P1; i++) {
        gameBoard[i] = INITIAL_NUM_STONES;
    }
    for (int j = FIRST_HOLE_P2; j<LAST_HOLE_P2; j++) {
        gameBoard[j] = INITIAL_NUM_STONES;
    }
}

int CheckInput (bool Empty, bool CurPlayerInd, int gameBoard[NUM_OF_HOLES]
                , int Player){//Validate that the input is valid. (16)
    int ChosenCell=INITIALIZED;
    while (Empty==true || CurPlayerInd==false) {
        
        if (scanf("%d", &ChosenCell)!= VALID) {
            PrintScanfFailure();
            return INVALID;
        }
        if (((ChosenCell>=LAST_HOLE_P1 || ChosenCell<FIRST_HOLE_P1) &&
             Player==PLAYER1) || ((ChosenCell<FIRST_HOLE_P2 ||
                                   ChosenCell>=LAST_HOLE_P2) &&
                                  Player==PLAYER2)) {
            PrintInvalidValue();
            continue;
        }else
            CurPlayerInd=true;
        
        if (gameBoard[ChosenCell]==EMPTY) {
            PrintEmptyCell();
            continue;
        }else
            Empty=false;
        
    }
    
    return ChosenCell;
}

// move the stones from the chosen cell.(16)
bool MoveStones (int Stones, int gameBoard[NUM_OF_HOLES],
                 int Counter, int Player){
    bool ExtraTurn = false;
    while (Stones > EMPTY) {
        gameBoard[Counter]++;
        if (Stones == LAST_STONE && gameBoard[Counter]==LAST_STONE &&
            Counter>=FIRST_HOLE_P1 && Counter<=(LAST_HOLE_P1-1) &&
            Player==PLAYER1) {
            gameBoard[Counter]--;
            gameBoard[LAST_HOLE_P1] += gameBoard[Counter+
                                TWO*(LAST_HOLE_P1-Counter)]+ONE;
            gameBoard[Counter+TWO*(LAST_HOLE_P1-Counter)]=INITIALIZED;
        }else{
            if (Stones == LAST_STONE && gameBoard[Counter]==FIRST_HOLE_P1+
                ONE&& Counter>=FIRST_HOLE_P2 && Counter<=LAST_HOLE_P2-ONE
                && Player==PLAYER2) {
                gameBoard[Counter]--;
                gameBoard[LAST_HOLE_P2] += gameBoard[Counter-
                                    TWO*(Counter-LAST_HOLE_P1)]+ONE;
                gameBoard[Counter-TWO*(Counter-LAST_HOLE_P1)]=INITIALIZED;
            }
        }
        
        ExtraTurn = CheckExtraTurn(Stones, Player, Counter);
        Counter=CheckNextJump(Counter, Player);
        Stones--;
    }
    return ExtraTurn;
}

// check if the player earn the next turn too.(3)
bool CheckExtraTurn (int Stones, int Player, int Counter){
    if ((Stones==LAST_STONE && Player==PLAYER1 && Counter==LAST_HOLE_P1)||
        (Stones==LAST_STONE && Player==PLAYER2 && Counter==LAST_HOLE_P2))
        return true;
    return false;
}
//calculate the num of stones the player has without the home cell. (8)
int CalcPlayerStones (int gameBoard[NUM_OF_HOLES], int Player){
    int Sum=INITIALIZED;
    if (Player==PLAYER1) {
        for (int i=FIRST_HOLE_P1; i<LAST_HOLE_P1; i++) {
            Sum+=gameBoard[i];
        }
    }else{
        for (int i=FIRST_HOLE_P2; i<LAST_HOLE_P2; i++) {
            Sum+=gameBoard[i];
        }
    }
    return Sum;
}

// Calculate the next cell to put stone. (7)
int CheckNextJump (int Counter, int Player){
    if (Player==PLAYER2 && Counter==LAST_HOLE_P1-ONE)
        return (Counter+TWO);
    else {
        if ((Counter==LAST_HOLE_P2) || (Player==PLAYER1 &&
                                    Counter==LAST_HOLE_P2-ONE))
            return FIRST_HOLE_P1;
        else
            return (Counter+ONE);
    }
}

// Checkes who wins the game or if it is a tie. (17)
int CheckWinner (int gameBoard[NUM_OF_HOLES]){
    int Winner = INITIALIZED;
    if (gameBoard[LAST_HOLE_P1]>gameBoard[LAST_HOLE_P2]) {
        Winner = PLAYER1;
        PrintBoard(gameBoard);
        PrintWinningMessage(Winner);
    }else{
        if (gameBoard[LAST_HOLE_P1]<gameBoard[LAST_HOLE_P2]) {
            Winner = PLAYER2;
            PrintBoard(gameBoard);
            PrintWinningMessage(Winner);
        }else{
            Winner = NOBODY;
            PrintBoard(gameBoard);
            PrintWinningMessage(Winner);
        }
    }
    return Winner;
}

//change the board to the final status.(15)
int FinalBoardStat (int SumP1, int SumP2, int gameBoard[NUM_OF_HOLES]){
    
    if (SumP1==EMPTY && SumP2>EMPTY) {
        
        gameBoard[LAST_HOLE_P1]+= SumP2;
        for (int j=FIRST_HOLE_P2; j<LAST_HOLE_P2; j++)
            gameBoard[j]=INITIALIZED;
        return END_OF_GAME;
    }else{
        if (SumP2==EMPTY && SumP1>EMPTY) {
            gameBoard[LAST_HOLE_P2]+= SumP1;
            for (int i=FIRST_HOLE_P1; i<LAST_HOLE_P1; i++)
                gameBoard[i]=INITIALIZED;
            return END_OF_GAME;
        }else{
            if (SumP1==EMPTY && SumP2==EMPTY) {
                return END_OF_GAME;
            }
        }
    }
    return STILL_PLAYING;
}

//Check who play the next turn.(6)
int CheckNextTurn (int Player, bool ExtraTurn){
    if (Player==PLAYER1 && ExtraTurn==false)
        return PLAYER2;
    else{
        if (Player==PLAYER2 && ExtraTurn==false)
            return PLAYER1;
    }
    return Player;
}

/* PRINTING FUNCTIONS */
void PrintWelcomeMessage()
{
    printf("Welcome to the game Mankala!\n");
}

void PrintBoard(int board[])
{
    
    printf("\n");
    printf("Player %*d indices:    ", WIDTH, PLAYER1);
    for(int i = HOME1; i >= 0; i--)
    {
        printf(" %*d  ", WIDTH, i);
    }
    printf("      \n");
    
    printf("                    |-----------------------------------------|\n");
    printf("                    |-----------------------------------------|\n");
    
    printf("                    ||    |");
    for(int i = HOME1-1; i >= 0; i--)
    {
        printf(" %*d |", WIDTH, board[i]);
    }
    printf("    ||\n");
    
    printf("                    || %*d |-----------------------------| %*d ||\n",
           WIDTH, board[HOME1], WIDTH, board[HOME2]);
    
    printf("                    ||    |");
    for(int i = HOME1+1; i < HOME2; i++)
    {
        printf(" %*d |", WIDTH, board[i]);
    }
    printf("    ||\n");
    
    printf("                    |-----------------------------------------|\n");
    printf("                    |-----------------------------------------|\n");
    
    printf("Player %*d indices:         ", WIDTH, PLAYER2);
    for(int i = HOME1+1; i <= HOME2; i++)
    {
        printf(" %*d  ", WIDTH, i);
    }
    printf("      \n\n");
}

void PrintTurn(int player)
{
    printf("Player %d turn.\n", player);
}


void PrintChooseCell()
{
    printf("Please choose one of your non-empty cells:\n");
}

void PrintScanfFailure()
{
    printf("Error: fail to read input! Exiting.\n");
}

void PrintInvalidValue()
{
    printf("Error: invalid number of cell! please try again:\n");
}

void PrintEmptyCell()
{
    printf("Error: cell is empty! please try again:\n");
}

void PrintWinningMessage(int winner)
{
    if(winner == NOBODY)
    {
        printf("Draw!\n");
        return;
    }
    
    printf("The winner is player %d!\n", winner);
}

