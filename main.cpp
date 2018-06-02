#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

void print_board(char [9]);
bool first_turn();
int ai_move(const int [8][3], char[9], char);
bool is_game_end(const int [8][3], char[9], char);
int get_human_move();

int main(int argc, char **argv)
{
    char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    char human;
    bool ai_turn =first_turn();
    if (ai_turn) human = 'O';
    else human = 'X';
    bool is_X = true;
    int move;
    int win_pos[8][3] = {
        {0,1,2},
        {3,4,5},
        {6,7,8},
        {0,3,6},
        {1,4,7},
        {2,5,8},
        {0,4,8},
        {2,4,6}
        };
    print_board(board);
    while(true){
        if (ai_turn){
            move = ai_move(win_pos, board, human);
            ai_turn = false;
        }
        else{
            move = get_human_move();
            ai_turn = true;
        }
        if(is_X){
            board[move] = 'X';
            is_X = false;
        }
        else{
            board[move] = 'O';
            is_X = true;
        }
        print_board(board);
        if(is_game_end(win_pos, board, human)){
            break;
        }
    }
	return 0;
}

void print_board(char board[9]){
    char digits[9] = {};
    for (int  i = 0; i < 9; i++){
        if (board[i] == ' ') digits[i] = char(i+49);
        else digits[i] = board[i];
    }
    printf("\n|-+-+-|\n");
    printf("|%c+%c+%c|\n", digits[0],  digits[1], digits[2]);
    printf("|-+-+-|\n");
    printf("|%c+%c+%c|\n", digits[3],  digits[4], digits[5]);
    printf("|-+-+-|\n");
    printf("|%c+%c+%c|\n", digits[6],  digits[7], digits[8]);
    printf("|-+-+-|\n\n");  
    
    COORD position;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    position.X = 0;
    position.Y = 1;
    SetConsoleCursorPosition(hConsole, position);
}

bool first_turn(){
    char answer;
    int button;
    puts("Do u want to make first move (y/n)?");
    while (true) {
        int button = getch();
        answer = char(button);
        if (answer == 'y') return false;
        if (answer == 'n') return true;
    }
}

int ai_move(const int a[8][3], char board[9], char human){
    const int best_moves[9] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
    int close_2_lose = 0;
    int close_2_win = 0;
    int blank_space;
    char ai;
    if (human == 'X') ai = 'O';
    else ai = 'X';
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 3; j++){
            if(board[a[i][j]] == human) close_2_lose++;
            if(board[a[i][j]] == ai) close_2_win++;
            if(board[a[i][j]] == ' ') blank_space = a[i][j];
        }
        if(close_2_lose == 2) {
            if (board[blank_space] != ' ') continue;
            else return blank_space;
        }
        if(close_2_win == 2){
            if (board[blank_space] != ' ') continue;
            else return blank_space;
        }
        close_2_lose = 0;
        close_2_win = 0;
    }
    for (int e = 0; e < 8; e++){
        if(board[best_moves[e]] == ' ') return best_moves[e];
    }
}

bool is_game_end(const int a[8][3], char board[9], char human){
    char ai;
    int human_win = 0;
    int ai_win = 0;
    if (human == 'X') ai = 'O';
    else ai = 'X';
    COORD position;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    position.X = 0;
    position.Y = 9;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 3; j++){
            if(board[a[i][j]] == human) human_win++;
            if(board[a[i][j]] == ai) ai_win++;
        }
        if(human_win == 3){
            SetConsoleCursorPosition(hConsole, position);
            puts("HUMAN WIN");
            return true;
        }
        if(ai_win == 3){
            SetConsoleCursorPosition(hConsole, position);
            puts("AI WIN");
            return true;
        }
        human_win = 0;
        ai_win = 0;
    }
    for(int e = 0; e < 9; e++){
        if (board[e] == ' ') break;
        if (e == 8) {
            SetConsoleCursorPosition(hConsole, position);
            puts("DRAW!");
            return true;
        }
    }
    return false;
}

int get_human_move(){
    int button = getch();
    button -= 49;
    return button;
}