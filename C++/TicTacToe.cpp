// Homework2 by Mohammed AJoor 
// Game: Tic-Tac-Toe

#include <iostream>
#include <string>
using  std::cout;
using std::endl;


// Constant values
int const NROW = 3;
int const NCOLUMN = 3;
int const TOTAL_MOVES = NROW * NCOLUMN;

// Important variable
char player_choices_log[TOTAL_MOVES];


//Function decleration 
void PrintGameBoard(char game[3][3], int n, int m);
void player_move(int case_selected, char game[3][3], char mark);
bool error_handler(int case_selected);
void game_result(char game[3][3]);
bool game_over(char game[3][3]);

int input() {
     int selected;

    while (true) {
        std::cin >> selected;
        if (std::cin.good() && (0 < selected && selected < 10)) { // user is only allowed to select a num between 1 and 9
            return selected; // return the selected number
        }
        else {
            cout << "Please enter a VALID selection: ";
            std::cin.clear();
            std::cin.ignore(256, '\n');
        }
    }
    return -1;
}

int main()
{   
    int player_one = true; // if it is not player one , the value would be false
    char mark; // either X or O
    int player_choice; // which cell the player selected
    char game_board[NROW][NCOLUMN] = { '1','2','3','4','5','6','7','8','9' };     // initializing cells 
    bool error; // true for error
    int player = 0;

    cout << "-----------------------------------\n"
        << "     This is Tic-Tac-Toe game \n"
        << "-----------------------------------\n\n\n";
    
    for (int i = 1; i <= TOTAL_MOVES; i++) { // Max number of moves is 9 , then the game ends automatically
        
        // Alternate between player one and two
        if (i % 2 == 0) {
            player_one = true;
            mark = 'O';
            player = 2;
        }
        else {
            player_one = false;
            mark = 'X';
            player =1;
        }

        // Game Introduction
        cout << "Turn " << i << " (" << "Player: " <<player << ")"<<": " << endl;
        cout << "Select one of the following unocupied cells to place an " << mark << " on:\n\n";
        PrintGameBoard(game_board, NROW, NCOLUMN);
        
        // Player Input 
        cout << "Player selection: ";
        do { // handles player secltion and Checks if player has entered a valid selection 
            player_choice = input(); // get player selection
            error = error_handler(player_choice); // check if selection is vaild
            if (error == true) { // Show error msg
                cout << "You cannot place a mark on an occupied cell!\n";
                cout << "Please select a cell that is NOT occupied: ";
            }
        } while (error == true); // repeat until the player has made a valid selection

        player_choices_log[i] = player_choice; // record the player move
        player_move(player_choice, game_board, mark); // apply the player move

        if (game_over(game_board) == true) { // check of game is over or not
            cout << endl;
            PrintGameBoard(game_board, NROW, NCOLUMN); // print the final game board 
            cout << "Game is Over!: " << endl; 
            game_result(game_board); // declears which player has won the game

            break;
        }
        else {
            cout << endl;
            cout << "--------------------------------------------------------------";
            cout << endl;
        }
    }
    return 0; // ends the program
}


bool error_handler(int case_selected) {

    bool rule_violation;
    // # A player cannot place a mark on an occupied cell 
    for (int i = 0; i < TOTAL_MOVES; i++) {
        if (case_selected == player_choices_log[i]) { // if the selected cell in play choice log ,  rule has been violated
            rule_violation = true;
            break;
        }
        else {
            rule_violation = false; // otherwise ,  rule has not been violated 
        }
    }
    return rule_violation; // return result
}

void player_move(int case_selected, char game[3][3], char mark) { // translate user input into action
    
    // each case represent a possible option to place a mark on
    switch (case_selected) { // there is no need for a default case because the error_handler function will handle all errors
    
    case 1:
        game[0][0] = mark;
        break;
    case 2:
        game[0][1] = mark;
        break;
    case 3:
        game[0][2] = mark;
        break;
    case 4:
        game[1][0] = mark;
        break;
    case 5:
        game[1][1] = mark;
        break;
    case 6:
        game[1][2] = mark;
        break;
    case 7:
        game[2][0] = mark;
        break;
    case 8:
        game[2][1] = mark;
        break;
    case 9:
        game[2][2] = mark;
        break;
    }
}

void game_result(char game[3][3]) { // returns who has won the game
    
    char mark = 'N'; // the winner mark will be assigned to this vairable
    bool result_known=false;

    for (int i = 0; i < NROW; i++) {

        if (game[i][0] == game[i][1] && game[i][1] == game[i][2]) {
            mark = game[i][0];
            result_known = true;
            break;
        }

        if (game[0][i] == game[1][i] && game[1][i] == game[2][i]) {
            mark = game[0][i];
            result_known = true;
            break;
        }
    }
    if (result_known == false) {

        if (game[0][0] == game[1][1] && game[1][1] == game[2][2]) { // special case I
            mark = game[0][0];
        }
        else if (game[2][0] == game[1][1] && game[1][1] == game[0][2]) { // special case II
            mark = game[2][0];
        }
    }

    if (mark == 'X') {
        cout << "Player one has WON the game!";
    }
    else if (mark == 'O') {
        cout << "Player two has WON the game!";
    }
    else {
        cout << "This game has ended in a DRAW!" << endl;
    }
}

bool game_over(char game[3][3]) {

    // cases in which the game ends

    if ((game[0][0] == game[0][1] && game[0][1] == game[0][2]) || (game[1][0] == game[1][1] && game[1][1] == game[1][2]) || (game[2][0] == game[2][1] && game[2][1] == game[2][2])
        || (game[0][0] == game[1][0] && game[1][0] == game[2][0]) || (game[0][1] == game[1][1] && game[1][1] == game[2][1]) || 
        (game[0][2] == game[1][2] && game[1][2] == game[2][2]) || (game[0][0] == game[1][1] && game[1][1] == game[2][2]) ||
        (game[2][0] == game[1][1] && game[1][1] == game[0][2])){
        return true;
    }
    else {
        return false;
    }
}

void PrintGameBoard(char game[3][3], int n, int m) { // prints the gameboard on screen

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << "| " << game[i][j] << " | ";
        }
        cout << endl << endl;
    }
}
