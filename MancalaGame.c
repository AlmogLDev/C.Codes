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


/*-------------------------------------------------------------------------
 The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
int main()
{
    int Player=1, ChosenCell=0, Stones=0, Counter=0, SumP1=0, SumP2=0, Winner=0;
    bool ExtraTurn = false, Empty=true, CurPlayerInd=false;
    int gameBoard[NUM_OF_HOLES] = { 0 };
    InitializeGameBoard(gameBoard);
    PrintWelcomeMessage();
    PrintBoard(gameBoard);
    
    while (Winner == 0) {
        PrintTurn(Player);
        if (Player == 1) {
            PrintChooseCell();

            while (Empty==true || CurPlayerInd==false) {
                
                if (scanf("%d", &ChosenCell)!=1) {
                    PrintScanfFailure();
                    return 1;
                }
                if (ChosenCell>=LAST_HOLE_P1 || ChosenCell<FIRST_HOLE_P1) {
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
            
        }else {
            PrintChooseCell();
            while (Empty==true || CurPlayerInd==false) {
                
                if (scanf("%d", &ChosenCell)!=1) {
                    PrintScanfFailure();
                    return 1;
                }
                if (ChosenCell<FIRST_HOLE_P2 || ChosenCell>=LAST_HOLE_P2) {
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
        }
        Empty = true;
        CurPlayerInd = false;
        
        Stones = gameBoard[ChosenCell];
        gameBoard[ChosenCell] = 0;
        Counter = ChosenCell+1;
        
        
        while (Stones > 0) {
            gameBoard[Counter]++;
            if (Stones == 1 && gameBoard[Counter]==1 && Counter>=0 && Counter<=5 && Player==1) {
                gameBoard[Counter]--;
                gameBoard[6] += gameBoard[Counter+2*(6-Counter)]+1;
                gameBoard[Counter+2*(6-Counter)] = 0;
            }else{
                if (Stones == 1 && gameBoard[Counter]==1 && Counter>=7 && Counter<=12 && Player==2) {
                    gameBoard[Counter]--;
                    gameBoard[13] += gameBoard[Counter-2*(Counter-6)]+1;
                    gameBoard[Counter-2*(Counter-6)] = 0;
                }
            }
            
            if ((Stones==1 && Player==1 && Counter==6)||(Stones==1 && Player==2 && Counter==13))
                ExtraTurn = true;
            
            
            
            if (Player==2 && Counter==5)
                Counter += 2;
            else {
                if ((Counter==13) || (Player==1 && Counter==12))
                    Counter = 0;
                else
                    Counter++;
            }
            Stones--;
        }
        Counter = 0;
        
        
        for (int i=0; i<6; i++) {
            SumP1+=gameBoard[i];
        }
        for (int j=7; j<13; j++) {
            SumP2+=gameBoard[j];
        }
        
        if (SumP1==0 && SumP2>0) {
            gameBoard[6]+= SumP2;
            for (int i=0; i<6; i++)
                gameBoard[i]=0;

            for (int j=7; j<13; j++)
                gameBoard[j]=0;

            
            if (gameBoard[6]>gameBoard[13]) {
                Winner = 1;
                PrintBoard(gameBoard);
                PrintWinningMessage(Winner);
                return END;
            }else{
                if (gameBoard[6]<gameBoard[13]) {
                    Winner = 2;
                    PrintBoard(gameBoard);
                    PrintWinningMessage(Winner);
                    return END;
                }else{
                    Winner = NOBODY;
                    PrintBoard(gameBoard);
                    PrintWinningMessage(Winner);
                    return END;
                }
            }
            
        }else{
            if (SumP2==0 && SumP1>0) {
                gameBoard[13]+= SumP1;
                for (int i=0; i<6; i++)
                    gameBoard[i]=0;
         
                for (int j=7; j<13; j++)
                    gameBoard[j]=0;
         
                
                if (gameBoard[6]>gameBoard[13]) {
                    Winner = 1;
                    PrintBoard(gameBoard);
                    PrintWinningMessage(Winner);
                    return END;
                }else{
                    if (gameBoard[6]<gameBoard[13]) {
                        Winner = 2;
                        PrintBoard(gameBoard);
                        PrintWinningMessage(Winner);
                        return END;
                    }else{
                        Winner = NOBODY;
                        PrintBoard(gameBoard);
                        PrintWinningMessage(Winner);
                        return END;
                    }
                }
                
            }else{
                if (SumP2==0 && SumP1==0){
                    
                    if (gameBoard[6]>gameBoard[13]) {
                        Winner = 1;
                        PrintBoard(gameBoard);
                        PrintWinningMessage(Winner);
                        return END;
                    }else{
                        if (gameBoard[6]<gameBoard[13]) {
                            Winner = 2;
                            PrintBoard(gameBoard);
                            PrintWinningMessage(Winner);
                            return END;
                        }else{
                            Winner = NOBODY;
                            PrintBoard(gameBoard);
                            PrintWinningMessage(Winner);
                            return END;
                        }
                    }
                    
                }else{
                    PrintBoard(gameBoard);
                }
            }
        }
        
        SumP1 = 0;
        SumP2 = 0;
        
         if (Player==1 && ExtraTurn==false)
            Player = 2;
         else{
            if (Player==2 && ExtraTurn==false)
                Player = 1;
         }
        
        ExtraTurn = false;
    }
    
    return END;
}

void InitializeGameBoard(int gameBoard[NUM_OF_HOLES]){
    for (int i = FIRST_HOLE_P1; i<LAST_HOLE_P1; i++) {
        gameBoard[i] = INITIAL_NUM_STONES;
    }
    for (int j = FIRST_HOLE_P2; j<LAST_HOLE_P2; j++) {
        gameBoard[j] = INITIAL_NUM_STONES;
    }
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
