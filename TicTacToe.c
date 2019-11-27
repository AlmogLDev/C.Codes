/*-------------------------------------------------------------------------
    Include files:
-------------------------------------------------------------------------*/
#include <stdio.h>

/*-------------------------------------------------------------------------
    Constants and definitions:
-------------------------------------------------------------------------*/
#define N 11
#define PLAYER_ONE 1
#define PLAYER_TWO 2
#define LEGAL 0
#define ILLEGAL 1
#define FAIL 1
#define GAME_OVER 0
#define MIN_COL 1
#define MIN_ROW 1
#define YES 0
#define NO 3
#define UNDO -2
#define NO_MOVES 0
#define TIE -2
#define EMPTY 0
/*-------------------------------------------------------------------------
    Function declaration
-------------------------------------------------------------------------*/
void print_welcome();
void print_enter_board_size();
void print_board(char board[N][N], int n);
void print_player_turn(int player_index);
void print_error();
void print_winner(int player_index);
void print_tie();

/*-------------------------------------------------------------------------
    Implementation
-------------------------------------------------------------------------*/
int ticTacToeGame(char board[N][N]);
void initializeBoard(char board[N][N], int BoardSize);
int nextMove(char board[N][N], int BoardSize, int moves[], int* CountMoves);
int validateUndo(int Row, int* CountMoves);
void saveMove(int Row, int Col, int moves[], int *CountMoves);
int checkEndGame(char board[N][N], int BoardSize);
int checkFullBoard(char board[N][N], int BoardSize);
int checkDiagonalLToR(char board[N][N], int BoardSize);
int checkDiagonalRToL(char board[N][N], int BoardSize);
int checkColumnSequence(char board[N][N], int BoardSize);
int checkRowSequence(char board[N][N], int BoardSize);
void putXorO(char board[N][N], int moves[], int *CountMoves, int *ChoosePlayer);
void checkWinner(int Winner);
void doUndo(int *CountMoves, int CheckUndo, int moves[], char board[N][N], int BoardSize, int *ChoosePlayer);
void switchPlayer(int *ChoosePlayer);
void prepareTheGame(int *BoardSizeP, char board[N][N]);
void endPlayerTurn(char board[N][N], int BoardSize, int *ChoosePlayer,int moves[], int *CountMoves, int *WinnerP);
int calculatesGameResult(int FullBoard, int DiagLR, int DiagRL, int ColSeq, int RowSeq);
void firstTry(int FirstTime);


//The main game function which connect all of the game functions.
//13 lines.
int ticTacToeGame(char board[N][N]){
    int BoardSize = 0, Player = PLAYER_ONE , MovesCounter = 0, Winner = NO, CheckUndo = 0;
    int *CountMoves = &MovesCounter, *ChoosePlayer = &Player;
    int moves[N*N*2] = {0};
    
    prepareTheGame(&BoardSize, board);
    
    while (Winner == NO) {//while we dont have winner/tie the game continues.
        print_player_turn(Player);
        
        CheckUndo = nextMove(board, BoardSize, moves, CountMoves);
        if (CheckUndo<0) {//Cheks if the player chose the undo option(going backwards).
            doUndo(CountMoves, CheckUndo, moves, board, BoardSize, ChoosePlayer);
            continue;
        }
        
        endPlayerTurn(board, BoardSize, ChoosePlayer, moves, CountMoves, &Winner);
    }
    checkWinner(Winner);
    
    return GAME_OVER;
}

/*Put the player sign in the right place on the board, prints the board, switch to the other player and checks by the checkEndGame function if we have a winner/tie or not*/
//4 lines.
void endPlayerTurn(char board[N][N], int BoardSize, int *ChoosePlayer,int moves[], int *CountMoves, int *WinnerP){
    
    putXorO(board, moves, CountMoves, ChoosePlayer);
    print_board(board, BoardSize);
    switchPlayer(ChoosePlayer);
    *WinnerP = checkEndGame(board, BoardSize);
}

//Get the board size from the user, initialized the board and prints the empty board.
//6 lines.
void prepareTheGame(int *BoardSizeP, char board[N][N]){
    print_welcome();
    print_enter_board_size();
    scanf("%d", BoardSizeP);// we can assume the size is legal.
    
    initializeBoard(board,*BoardSizeP);
    print_board(board, *BoardSizeP);
    
    return;
}

//Switch between player1 and player2.
//5 lines.
void switchPlayer(int *ChoosePlayer){
    if (*ChoosePlayer == PLAYER_ONE) {
        *ChoosePlayer = PLAYER_TWO;
    }else{
        *ChoosePlayer = PLAYER_ONE;
    }
    
    return;
}

//Performs the undo action: returns the game a few steps back(the player chose how much steps).
//8 lines.
void doUndo(int *CountMoves, int CheckUndo, int moves[], char board[N][N], int BoardSize, int *ChoosePlayer){
    
    //"delete" the last steps of the game from the "memory" and return the appropriate board.
    for (int i=*CountMoves; i>*CountMoves+CheckUndo; i--) {
        board[moves[i*2-2]-1][moves[i*2-1]-1] = '_';
        moves[i*2-1] = EMPTY;
        moves[i*2-2] = EMPTY;
    }
    *CountMoves += CheckUndo;
    
    print_board(board, BoardSize);
    switchPlayer(ChoosePlayer);
    
    return;
}

//Checks if we have winner/tie then print it.
//5 lines.
void checkWinner(int Winner){
    if (Winner == TIE) {
        print_tie();
    }else{
        print_winner(Winner);
    }
    
    
    return;
}

//checks if this is the first try at this turn of the player, else prints error.
//3 lines.
void firstTry(int FirstTime){
    
    if (FirstTime) {
        print_error();
    }
    
    return;
}

//Takes the next step in the game.
//13 lines.
int nextMove(char board[N][N], int BoardSize, int moves[], int *CountMoves){
    int Row = 0, Col = 0, FirstTime = YES, CheckUndo = 0;
    
    do{
        firstTry(FirstTime);
        
        scanf("%d", &Row);
        CheckUndo = validateUndo(Row, CountMoves);
        if(CheckUndo<0){
            return CheckUndo;
        }
        Row = CheckUndo;
        
        scanf("%d", &Col);
        FirstTime=NO;
    }
    while ((Row<0 && Row%2==0)||(!Row || Row>BoardSize)||(Col<MIN_COL || Col>BoardSize) || board[Row-1][Col-1]!='_');
    
    
    saveMove(Row, Col, moves, CountMoves);
    
    return LEGAL;
}


//Position the relevant sign(X or O) in the appropriate cell on the board.
//9 lines.
void putXorO(char board[N][N], int moves[], int *CountMoves, int *ChoosePlayer){
    int Row = 0, Col = 0;
    
    Row = moves[(*CountMoves)*2];
    Col = moves[(*CountMoves)*2+1];
    
    if (*ChoosePlayer == PLAYER_ONE) {//Select the sign of this player.
        board[Row-1][Col-1] = 'X';
    }else{
        board[Row-1][Col-1] = 'O';
    }
    
    *CountMoves += 1;
    
    
    return;
}

//Checks if we have a full row only with X or only with O.
//12 lines.
int checkRowSequence(char board[N][N], int BoardSize){
    int CheckRowSeq = YES;
    
    for (int i=0; i<BoardSize; i++) {
        for (int j=0; j<BoardSize-1; j++) {
            if (board[i][j]!=board[i][j+1]) {
                CheckRowSeq = NO;
            }
        }
        if (CheckRowSeq == YES) {
            if (board[i][0] == 'X') {
                return PLAYER_ONE;
                }
            if (board[i][0] == 'O') {
                return PLAYER_TWO;
                }
        }
        CheckRowSeq = YES;
        
    }
    
    return NO;
}

//Checks if we have a full column only with X or only with O.
//12 lines.
int checkColumnSequence(char board[N][N], int BoardSize){
    int CheckColSeq = YES;
    
    for (int i=0; i<BoardSize; i++) {
        for (int j=0; j<BoardSize-1; j++) {
            if (board[j][i]!=board[j+1][i]) {
                CheckColSeq = NO;
            }
        }
        if (!CheckColSeq) {
            if (board[0][i] == 'X') {
                return PLAYER_ONE;
                
            }
            if (board[0][i] == 'O') {
                return PLAYER_TWO;

                }
        }
        CheckColSeq = YES;
    }
    
    return NO;
}

//Checks the conditions and return the contemporary result of the game.
//12 lines.
int calculatesGameResult(int FullBoard, int DiagLR, int DiagRL, int ColSeq, int RowSeq){
    if (DiagLR == PLAYER_ONE || DiagRL == PLAYER_ONE || ColSeq == PLAYER_ONE || RowSeq == PLAYER_ONE) {
        return PLAYER_TWO;
    }else{
        if (DiagLR == PLAYER_TWO || DiagRL == PLAYER_TWO || ColSeq == PLAYER_TWO || RowSeq == PLAYER_TWO) {
            return PLAYER_ONE;
        }else{
            if (FullBoard == YES) {
                return TIE;
            }else{
                return NO;
            }
            
        }
    }
}

//Checks if we have a winner/tie or the game must continue.
//8 lines.
int checkEndGame(char board[N][N], int BoardSize){
    int FullBoard = NO, DiagLR = NO, DiagRL = NO, ColSeq = NO, RowSeq = NO ,Result = NO;
    
    FullBoard = checkFullBoard(board, BoardSize);
    DiagRL = checkDiagonalRToL(board, BoardSize);
    DiagLR = checkDiagonalLToR(board, BoardSize);
    ColSeq = checkColumnSequence(board, BoardSize);
    RowSeq = checkRowSequence(board, BoardSize);
    
    Result=calculatesGameResult(FullBoard, DiagLR, DiagRL, ColSeq, RowSeq);
    
    return Result;

}

//Checks if we have a full diagonal from right to left only with X or only with O.
//11 lines.
int checkDiagonalRToL(char board[N][N], int BoardSize){
    
    for (int i=0; i<BoardSize-1; i++) {
        if (board[i][BoardSize-1-i]!=board[i+1][BoardSize-1-i-1]) {
            return NO;
        }
    }
    
    if (board[0][BoardSize-1] == 'X') {
        return PLAYER_ONE;
    }else{
        if (board[0][BoardSize-1] == 'O') {
            return PLAYER_TWO;
        }else{
            return NO;
        }
    }
}

//Checks if we have a full diagonal from left to right only with X or only with O.
//10 lines.
int checkDiagonalLToR(char board[N][N], int BoardSize){
    
    for (int i=0; i<BoardSize-1; i++) {
        if (board[i][i]!=board[i+1][i+1]) {
            return NO;
        }
    }
    
    if (board[0][0] == 'X') {
        return PLAYER_ONE;
    }else{
        if (board[0][0] == 'O') {
            return PLAYER_TWO;
        }else{
            return NO;
        }
    }
}

//Cheks if the board is full.
//5 lines.
int checkFullBoard(char board[N][N], int BoardSize){
    
    for (int i=0; i<BoardSize; i++) {
        for (int j=0; j<BoardSize; j++) {
            if (board[i][j] == '_') {
                return NO;
            }
        }
    }
    
    return YES;
}

//Saves all the moves int the game, the "memory" of the game.
//3 lines.
void saveMove(int Row, int Col, int moves[], int *CountMoves){
    
    moves[*CountMoves*2] = Row;
    moves[(*CountMoves*2)+1] = Col;
    
    
    return;
}

//Checks if the undo request is legal, else allow the user enter value again.
//6 lines.
int validateUndo(int Row, int *CountMoves){
    int NewRowVal = Row;
    
    if (NewRowVal<0) { //Checks the negative value is odd else allow the user enter again.
        while ((NewRowVal<0 && NewRowVal%2==0) || (*CountMoves<NewRowVal*(-1)&&NewRowVal<0)) {
            print_error();
            scanf("%d", &NewRowVal);
            }
    }
    
    return NewRowVal;
    
}

//Initialize the board to empty board.
//4 lines.
void initializeBoard(char board[N][N], int BoardSize){
    
    for (int i=0; i<BoardSize; i++) {
        for (int j=0; j<BoardSize; j++) {
            board[i][j] = '_';
        }
    }
    return;
}





//4 lines.
int main(){
    char board[N][N];
    
    if (ticTacToeGame(board)) {
        return FAIL;
    }
    return 0;
}





//print welcome message
//1 lines
void print_welcome()
{
    printf("*** Welcome to AVOIDANCE TIC-TAC-TOE game ***\n\n");
}

//print message to enter board size
//1 lines
void print_enter_board_size()
{
    printf("Please enter board size (1 to %d):\n", N);
}

//print the board
//7 lines
void print_board(char board[N][N], int n)
{
    printf("\nCurrent board:\n");
    for (int i = 0; i < n; i++)
    {
        printf("|");
        for (int j = 0; j < n; j++)
        {
            printf("%c|", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//print a request for player with index "player_index" to move
//1 lines
void print_player_turn(int player_index)
{
    printf("\nPlayer ** %d **, enter next move:\n", player_index);
}

//print error message
//1 lines
void print_error()
{
    printf("Illegal move!!!, please try again:\n");
}

//print the winner
//1 lines
void print_winner(int player_index)
{
    printf("Player %d Wins! Hooray!\n", player_index);
}

//print message to announce there is a tie (no one wins)
//1 lines
void print_tie()
{
    printf("It's a tie!\n");
}
