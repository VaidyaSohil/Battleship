#include<iostream>
#include<iomanip>
#include<windows.h>
#include<conio.h>
#include<string>
#include<ctime>
#include<cstdlib>

using namespace std;
class Grid {
protected:
    int opening_entry;
    bool valid_opening_entry = false;
    char horizontal_vertical[10];
    char player_ship_coordinates[10];
    char player_attack_coordinates[10];
    char player_attack_radar[11][13] =
            {
                    {'|','-','-','-','-','-','-','-','-','-','-','|'},
                    {'|','-','-','-','-','-','-','-','-','-','-','|'},
                    {'|','-','-','-','-','-','-','-','-','-','-','|'},
                    {'|','-','-','-','-','-','-','-','-','-','-','|'},
                    {'|','-','-','-','-','-','-','-','-','-','-','|'},
                    {'|','-','-','-','-','-','-','-','-','-','-','|'},
                    {'|','-','-','-','-','-','-','-','-','-','-','|'},
                    {'|','-','-','-','-','-','-','-','-','-','-','|'},
                    {'|','-','-','-','-','-','-','-','-','-','-','|'},
                    {'|','-','-','-','-','-','-','-','-','-','-','|'},
            };

    char player_board[11][13] =
            {
                    {'|','-','-','-','-','-','-','-','-','-','-','|'},
                    {'|','-','-','-','-','-','-','-','-','-','-','|'},
                    {'|','-','-','-','-','-','-','-','-','-','-','|'},
                    {'|','-','-','-','-','-','-','-','-','-','-','|'},
                    {'|','-','-','-','-','-','-','-','-','-','-','|'},
                    {'|','-','-','-','-','-','-','-','-','-','-','|'},
                    {'|','-','-','-','-','-','-','-','-','-','-','|'},
                    {'|','-','-','-','-','-','-','-','-','-','-','|'},
                    {'|','-','-','-','-','-','-','-','-','-','-','|'},
                    {'|','-','-','-','-','-','-','-','-','-','-','|'},
            };

    char computer_board[11][13] =
            {
                    {'|','-','-','-','-','-','-','-','-','-','-','|'},
                    {'|','-','-','-','-','-','-','-','-','-','-','|'},
                    {'|','-','-','-','-','-','-','-','-','-','-','|'},
                    {'|','-','-','-','-','-','-','-','-','-','-','|'},
                    {'|','-','-','-','-','-','-','-','-','-','-','|'},
                    {'|','-','-','-','-','-','-','-','-','-','-','|'},
                    {'|','-','-','-','-','-','-','-','-','-','-','|'},
                    {'|','-','-','-','-','-','-','-','-','-','-','|'},
                    {'|','-','-','-','-','-','-','-','-','-','-','|'},
                    {'|','-','-','-','-','-','-','-','-','-','-','|'},
            };

public:

    void battleship_instructions() {
        system("CLS");
        for (int j = 0; j < 2; j++) {
            cout << endl;
        }
        system("Color 74");
        cout << setw(80) << "INSTRUCTION ABOUT THE BATTLESHIP GAME" << endl;
        cout << endl;
        cout << setw(20) << "  0. This is a battleship game. In this game, you will be given 5 different ships. " << endl <<endl;
        cout << setw(20) << "  1. Each ship has its own dynamics." <<endl <<endl;
        cout << setw(20) << "  2. You will also be provided with the battlefield, where your opponent (COMPUTER) as well as you, place your ships." << endl <<endl;
        cout << setw(20) << "  3. However, you will not be able to see your enemy's ship position." << endl << endl;
        cout << setw(20) << "  4. And neither will your opponent will be able to see yours." << endl << endl;
        cout << setw(20) << "  5. After placing your ships correctly (as instructed during the ship placement)." << endl <<endl;
        cout << setw(20) << "  6. You will enter a head on challenge with your enemy." << endl <<endl;
        cout << setw(20) << "  7. Here, you will use the coordinates provided in the grid to attack." << endl << endl;
        cout << setw(20) << "  8. Guess the coordinate and sink your opponent's ships." << endl << endl;
        cout << setw(20) << "  9. The one who destroys all 5 ships of their opponent's grid WINS the game" << endl <<endl << endl <<endl;
        cout << setw(25) << "         PS : You can also forfeit the battle and end the game right before placing your ships or after." << endl;
        cout << setw(30) << "                            Although this won't look good on ya CAPTAIN!!";

    }

};

class Battleship : public Grid {		//class battleship derived from parent grid class
private:		//private member variables



    int board_title = 65, board_title_next = 65;	// for the letters A-J at he side of the board
    int computer_ship_space_on_board = 17; //total ship space accumulated : 5+4+3+3+2 = 17
    int player_ship_space_on_board = 17;	//total ship space accumulated : 5+4+3+3+2 = 17

    // ship sizes declared accordingly
    int destroyer_size = 2, player_destroyer_size = 2;
    int submarine_size = 3, player_submarine_size = 3;
    int cruiser_size = 3, player_cruiser_size = 3;
    int battleship_size = 4, player_battleship_size = 4;
    int carrier_size = 5, player_carrier_size = 5;

    // to locate the positions on the grid for corresponding actions
    int row, col;		//player's coordinate
    int attack_row, attack_col;		//player's attack coordinate
    int computer_row, computer_col;		//computer's coordinate
    int computer_attack_row, computer_attack_col;		//computer's attack coordinate
    int computer_horizontal_vertical;	//numbering for computer coordinate
    char first_computer_coordinate;		//letter location (rows) for the computer

    // individual ship number later assigned to each ships, with appropriate sizes
    int count_player_ship = 0;	//set to zero initially, later used to appoint ships
    int count_computer_ship = 0;

    //booleans to check valid/invalide. If valid then it is proceeded with a certain function
    bool valid_ship_position;
    bool valid_computer_ship_position;
    bool valid_attack_coordinates;
    bool valid_computer_attack_coordinates;
    bool quit = false;
    bool hit = false;

    //all ships false to initialize, as it will be true if hit, and corresponding message will be displayed out of true
    bool destroyer_hit = false;
    bool submarine_hit = false;
    bool cruiser_hit = false;
    bool battleship_hit = false;
    bool carrier_hit = false;


public:		//public member functions

    void opening_menu() {		//initial menu with options 1 or 2
        do {
            mainmenu:
            system("color 0F");
            cout << endl;
            cout << "Choose of the below options (1 or 2):" << endl;
            cout << setw(20) << "1. Begin the game" << endl;
            cout << setw(18) << "2. Instructions" << endl;
            cin >> opening_entry;
            if (opening_entry == 1) {	//begin the game function
                valid_opening_entry = true;
                begin_game();
            }
            else if (opening_entry == 2) {		//instruction page function
                valid_opening_entry = true;
                system("CLS");
                battleship_instructions();
                for (int k = 0; k < 3; k++) {
                    cout << endl;
                }
                cout << "           WILL GUIDE YOU BACK TO THE MAIN MENU SHORTLY (30 sec)" << endl;
                Sleep(32000);
                system("CLS");
                goto mainmenu	//jump to mainmenu after few seconds
                        ;
            }
            else {
                goto mainmenu;		//invalid entry means it loops back to main menu
            }
        } while (valid_opening_entry == false);	//loops until true (until 1 or 2 is pressed)
    }
    void begin_game() {		//the main function to begin the game, all other functions are sub functions to this function
        while (1) {
            system("CLS");		//clear console screen
            take_computer_input();		//set up board for the computer
            player_grid_print_and_player_attack_grid_print();	//print two boards, one board that shows player's ship, where computer attacks and other board for player to attack
            take_player_input();	//receives coordinates from the user to position ships
            player_sets_attack();	//player sets attack on the computer's board
        }
    }


    void player_grid_print_and_player_attack_grid_print() {	//this function is used over and over again, literally after every user entry
        print_quit_option();	//function to let user know they can quit by pressing Q

        system("Color 0F");		//color
        for (int i = 0; i < 5; i++) {	//below codes are all decorations, making a nice box shape , with titles with appropriate coordinates
            cout << endl;
        }
        cout << setw(52) << "0 1 2 3 4 5 6 7 8 9" << setw(41) << "0 1 2 3 4 5 6 7 8 9" << endl;		//column title 0,1,2...

        cout << setw(32) << (char)218;
        for (int j = 0; j < 21; j++) {
            cout << (char)196;
        }cout << (char)191 << setw(19) << (char)218;
        for (int n = 0; n < 21; n++) {
            cout << (char)196;
        }cout << (char)191 << endl;
        for (int k = 0; k < 10; k++) {
            cout << setw(30) << (char)board_title++ << " ";			//row title A,B,C...
            for (int l = 0; l < 12; l++) {					//compares with the array of char initialized at the beginning
                if (player_board[k][l] == '-') {
                    cout << (char)196 << " ";			//lower bar character
                }
                else if (player_board[k][l] == '|') {		//side bar character
                    cout << (char)179 << " ";
                }
                else if (player_board[k][l] == 'D') {		//for destroyer
                    cout << (char)68 << " ";
                }
                else if (player_board[k][l] == 'S') {		//for submarine
                    cout << (char)83 << " ";
                }
                else if (player_board[k][l] == 'R') {		//for cruiser
                    cout << (char)82 << " ";
                }
                else if (player_board[k][l] == 'B') {		//for battleship
                    cout << (char)66 << " ";
                }
                else if (player_board[k][l] == 'C') {		//for carrier
                    cout << (char)67 << " ";
                }
                else if (player_board[k][l] == '*') {		//for hits --> 0

                    cout << (char)48 << " ";
                }
                else if (player_board[k][l] == '?') {		//for misses --> X
                    cout << (char)88 << " ";
                }
            }
            //now the printing board
            cout << setw(17) << (char)board_title_next++;		//letters A,B,C...
            for (int m = 0; m < 12; m++) {
                if (player_attack_radar[k][m] == '-') {		//lower bar character
                    cout << (char)196 << " ";
                }
                else if (player_attack_radar[k][m] == '|') {		//side bar character
                    cout << (char)179 << " ";
                }
                else if (player_attack_radar[k][m] == '*') {		//for hits
                    cout << (char)48 << " ";
                }
                else if (player_attack_radar[k][m] == '?') {		//for misses
                    cout << (char)88 << " ";
                }
            }
            cout << endl;
        }
        board_title = 65;		//reset to A(char = 65) for the next function call
        board_title_next = 65;		//reset to A for the next function call
        cout << setw(32) << (char)192; //corner bar character
        for (int o = 0; o < 21; o++) {
            cout << (char)196;		//lower bar character
        }cout << (char)217 << setw(19) << (char)192;	//corner bar characters
        for (int p = 0; p < 21; p++) {
            cout << (char)196;			//lower bar
        }cout << (char)217 << endl << endl; //corner bar charcter
    }

    void take_player_input() {		//function that takes the coordinates of the ships to be placed on the grid
        do {
            valid_ship_position = true;
            if (count_player_ship == 0) {
                cout << setw(90) << "Enter The Coordinate For Your DESTROYER (2 spots): ";
            }
            else if (count_player_ship == 1) {
                cout << setw(89) << "Enter The Coordinate For Your SUBMARINE (3 spots): ";
            }
            else if (count_player_ship == 2) {
                cout << setw(88) << "Enter The Coordinate For Your BATTLESHIP (4 spots): ";
            }
            else if (count_player_ship == 3) {
                cout << setw(91) << "Enter The Coordinate For Your CARRIER (5 spots): ";
            }
            else if (count_player_ship == 4) {
                cout << setw(92) << "Enter The Coordinate For Your CRUISER (3 spots): ";
            }
            cin.getline(player_ship_coordinates, 11, '\n');
            cout << endl << endl;
            check_for_correct_coordinates();
            player_grid_print_and_player_attack_grid_print();
            if (valid_ship_position == true) {
                count_player_ship++;
            }
        } while (!valid_ship_position || count_player_ship < 5);		//loops until either is false, if ship count exceeds 4, we only have 5 ships
    }

    void check_for_correct_coordinates() {		//checks the coordinate is valid or not
        if(player_ship_coordinates[0] == 'q' || player_ship_coordinates[0] == 'Q'){
            print_computer_board();
            quit = true;
            system("CLS");

            for (int i = 0; i < 2; i++) {
                cout << endl;
                cout << setw(40) << "You chose to exit out of the game. Bye" << endl;
                Sleep(1000);
                system("CLS");
            }
            exit(0);
        }
        if (player_ship_coordinates[0] < 'a' || player_ship_coordinates[0] > 'j' ||
            player_ship_coordinates[1] < '0' || player_ship_coordinates[1] > '9')
        {
            valid_ship_position = false;		// if not then, send invalid entry message
            player_grid_print_and_player_attack_grid_print();
            cout << setw(91) << "Invalid coordinates. Please try again. Alphabet followed by a number. eg: h1" << endl;
            Sleep(2500);
        }
        else {
            assign_values_of_row_column();		// user enters the coordinates
            check_for_valid_cell();			//checks if the entry is valid or not
        }
    }

    void check_for_valid_cell() {

        if (player_board[row][col] == '-') {		//check if the spot is free
            if (count_player_ship == 0) {
                player_board[row][col] = 'D';
            }
            else if (count_player_ship == 1) {
                player_board[row][col] = 'S';
            }
            else if (count_player_ship == 2) {
                player_board[row][col] = 'B';
            }
            else if (count_player_ship == 3) {
                player_board[row][col] = 'C';
            }
            else if (count_player_ship == 4) {
                player_board[row][col] = 'R';
            }
            ask_player_for_horizontal_or_vertical();		//if all set, then proceed to choosing h/v
        }
        else {
            player_grid_print_and_player_attack_grid_print();		// if not, then go back to the grid, and send a message saying the spot is not available
            cout << setw(92) << "Spot already taken. Choose another coordinate." << endl << endl;
            Sleep(2000);
            valid_ship_position = false;		//set flag to false, as it is an invalid entry
        }

    }

    void ask_player_for_horizontal_or_vertical() {	//user chooses horizontal or vertical

        player_grid_print_and_player_attack_grid_print();		//print the grid before letting the user enter h/v
        cout << setw(28) << player_ship_coordinates[0] << player_ship_coordinates[1] << " Press (h) to set your ship horzontally and (v) to set vertically: ";
        cin.getline(horizontal_vertical, 10, '\n');
        if (horizontal_vertical[0] == 'h') {	// if h, then set the ships horizontally
            if (count_player_ship == 0 && player_board[row][col + 1] == '-') {	//check if the horizontal space right is available or not
                player_board[row][col + 1] = 'D';
            }
            else if (count_player_ship == 1 && player_board[row][col + 1] == '-' && player_board[row][col + 2] == '-') {
                player_board[row][col + 1] = 'S';
                player_board[row][col + 2] = 'S';
            }
            else if (count_player_ship == 2 && player_board[row][col + 1] == '-' && player_board[row][col + 2] == '-' &&  player_board[row][col + 3] == '-') {
                player_board[row][col + 1] = 'B';
                player_board[row][col + 2] = 'B';
                player_board[row][col + 3] = 'B';
            }
            else if (count_player_ship == 3 && player_board[row][col + 1] == '-' && player_board[row][col + 2] == '-' &&  player_board[row][col + 3] == '-' && player_board[row][col + 4] == '-') {
                player_board[row][col + 1] = 'C';
                player_board[row][col + 2] = 'C';
                player_board[row][col + 3] = 'C';
                player_board[row][col + 4] = 'C';
            }
            else if (count_player_ship == 4 && player_board[row][col + 1] == '-' && player_board[row][col + 2] == '-') {
                player_board[row][col + 1] = 'R';
                player_board[row][col + 2] = 'R';
            }
            else {									//if not, then inform the user that the horizontal placement is not possible
                player_grid_print_and_player_attack_grid_print();
                cout << setw(85) << "Sorry, not enough for horizontal placement." << endl << endl;
                Sleep(2000);
                player_board[row][col] = '-';		//free the marked spot
                valid_ship_position = false;		// set the flag to false, as it is an invalid instruction
            }
        }
        else if (horizontal_vertical[0] == 'v') {		// same as horizontal, but it first checks the vertical spot and see if the spots below is available or not for each ships. If not then sends the appropriate message saying that the vertical placement is not possible
            if (count_player_ship == 0 && player_board[row + 1][col] == '-') {
                player_board[row + 1][col] = 'D';
            }
            else if (count_player_ship == 1 && player_board[row + 1][col] == '-' && player_board[row + 2][col] == '-') {
                player_board[row + 1][col] = 'S';
                player_board[row + 2][col] = 'S';
            }
            else if (count_player_ship == 2 && player_board[row + 1][col] == '-' && player_board[row + 2][col] == '-' &&  player_board[row + 3][col] == '-') {
                player_board[row + 1][col] = 'B';
                player_board[row + 2][col] = 'B';
                player_board[row + 3][col] = 'B';
            }
            else if (count_player_ship == 3 && player_board[row + 1][col] == '-' && player_board[row + 2][col] == '-' &&  player_board[row + 3][col] == '-' && player_board[row + 4][col] == '-') {
                player_board[row + 1][col] = 'C';
                player_board[row + 2][col] = 'C';
                player_board[row + 3][col] = 'C';
                player_board[row + 4][col] = 'C';
            }
            else if (count_player_ship == 1 && player_board[row + 1][col] == '-' && player_board[row + 2][col] == '-') {
                player_board[row + 1][col] = 'R';
                player_board[row + 2][col] = 'R';
            }
            else {
                player_grid_print_and_player_attack_grid_print();
                cout << setw(85) << "Sorry, not enough for vertical placement." << endl << endl;
                Sleep(2000);
                player_board[row][col] = '-';
                valid_ship_position = false;
            }
        }
        else {
            player_grid_print_and_player_attack_grid_print();
            cout << setw(105) << "Press (h) to set your ship horzontally and (v) to set vertically: " << endl << endl;
            player_board[row][col] = '-';
            Sleep(2000);
            valid_ship_position = false;
        }

    }


    void take_computer_input() {

        do {		//set computer's ship
            system("CLS");
            for (int i = 0; i < 2; i++) {
                cout << endl;
            }
            system("color 07");
            cout << setw(62) << "Wait a few seconds, Computer is placing its ships....";
            valid_computer_ship_position = true;
            srand(time(0));
            computer_row = rand() % 11;		//randomly generated number used as the location of placement of the ships of the computer
            computer_col = rand() % 11;
            check_if_computer_move_is_valid();		//then check if the location is valid
            if (valid_computer_ship_position == true) {		//if valid, then increment the ship counter, which means get on to the next ship placement, we have a total of 5 ships
                count_computer_ship++;
            }
        } while (count_computer_ship < 5 || !valid_computer_ship_position);		//loops until all the ships are placed

        system("CLS");
        for (int i = 0; i < 3; i++) {
            cout << endl;
        }
        cout << setw(0) << "  ...";
        Sleep(750);
        cout << setw(0) << "...";
        Sleep(750);
        cout << setw(0) << "....";
        Sleep(750);
        cout << setw(0) << "....LOADING COMPLETE!!! ";
        Sleep(1700);
        system("CLS");
        cout << endl;
        cout << "   Now, it's your turn to place the ships";
        Sleep(1700);
        system("CLS");
    }

    void check_if_computer_move_is_valid() {		// function to check if the computer placed it correctly

        if (computer_board[computer_row][computer_col] == '-') {
            if (count_computer_ship == 0) {
                computer_board[computer_row][computer_col] = 'D';
            }
            else if (count_computer_ship == 1) {
                computer_board[computer_row][computer_col] = 'S';
            }
            else if (count_computer_ship == 2) {
                computer_board[computer_row][computer_col] = 'B';
            }
            else if (count_computer_ship == 3) {
                computer_board[computer_row][computer_col] = 'C';
            }
            else if (count_computer_ship == 4) {
                computer_board[computer_row][computer_col] = 'R';
            }
            computer_chooses_horizontal_or_vertical();		// if correct, then proceed to choose between h/v
        }
        else {
            valid_computer_ship_position = false;		//if not correct, then set flag to false
        }

    }


    void computer_chooses_horizontal_or_vertical() {		// two random numbers generated that decides horizontal or vertical

        computer_horizontal_vertical = 1 + rand() % 2;
        if (computer_horizontal_vertical == 1) {		// if 1 is the generated output, then horizontal placement
            if (count_computer_ship == 0 && computer_board[computer_row][computer_col + 1] == '-') {
                computer_board[computer_row][computer_col + 1] = 'D';
            }
            else if (count_computer_ship == 1 && computer_board[computer_row][computer_col + 1] == '-' && computer_board[computer_row][computer_col + 2] == '-') {
                computer_board[computer_row][computer_col + 1] = 'S';
                computer_board[computer_row][computer_col + 2] = 'S';
            }
            else if (count_computer_ship == 4 && computer_board[computer_row][computer_col + 1] == '-' && computer_board[computer_row][computer_col + 2] == '-') {
                computer_board[computer_row][computer_col + 1] = 'R';
                computer_board[computer_row][computer_col + 2] = 'R';
            }
            else if (count_computer_ship == 2 && computer_board[computer_row][computer_col + 1] == '-' && computer_board[computer_row][computer_col + 2] == '-' && computer_board[computer_row][computer_col + 3] == '-') {
                computer_board[computer_row][computer_col + 1] = 'B';
                computer_board[computer_row][computer_col + 2] = 'B';
                computer_board[computer_row][computer_col + 3] = 'B';
            }
            else if (count_computer_ship == 3 && computer_board[computer_row][computer_col + 1] == '-' && computer_board[computer_row][computer_col + 2] == '-' && computer_board[computer_row][computer_col + 3] == '-' && computer_board[computer_row][computer_col + 4] == '-') {
                computer_board[computer_row][computer_col + 1] = 'C';
                computer_board[computer_row][computer_col + 2] = 'C';
                computer_board[computer_row][computer_col + 3] = 'C';
                computer_board[computer_row][computer_col + 4] = 'C';
            }

            else {
                computer_board[computer_row][computer_col] = '-';		//if not then free the spot, and set booleann to false
                valid_computer_ship_position = false;
            }
        }
        else if (computer_horizontal_vertical == 2) {
            if (count_computer_ship == 0 && computer_board[computer_row + 1][computer_col] == '-') {
                computer_board[computer_row + 1][computer_col] = 'D';
            }
            else if (count_computer_ship == 1 && computer_board[computer_row + 1][computer_col] == '-' && computer_board[computer_row + 2][computer_col] == '-') {
                computer_board[computer_row + 1][computer_col] = 'S';
                computer_board[computer_row + 2][computer_col] = 'S';
            }
            else if (count_computer_ship == 1 && computer_board[computer_row + 1][computer_col] == '-' && computer_board[computer_row + 2][computer_col] == '-') {
                computer_board[computer_row + 1][computer_col] = 'R';
                computer_board[computer_row + 2][computer_col] = 'R';
            }
            else if (count_computer_ship == 2 && computer_board[computer_row + 1][computer_col] == '-' && computer_board[computer_row + 2][computer_col] == '-' && computer_board[computer_row + 3][computer_col] == '-') {
                computer_board[computer_row + 1][computer_col] = 'B';
                computer_board[computer_row + 2][computer_col] = 'B';
                computer_board[computer_row + 3][computer_col] = 'B';
            }
            else if (count_computer_ship == 3 && computer_board[computer_row + 1][computer_col] == '-' && computer_board[computer_row + 2][computer_col] == '-' && computer_board[computer_row + 3][computer_col] == '-' && computer_board[computer_row + 4][computer_col] == '-') {
                computer_board[computer_row + 1][computer_col] = 'C';
                computer_board[computer_row + 2][computer_col] = 'C';
                computer_board[computer_row + 3][computer_col] = 'C';
                computer_board[computer_row + 4][computer_col] = 'C';
            }
            else {
                computer_board[computer_row][computer_col] = '-';		//if not, then not a valid position, free that spot
                valid_computer_ship_position = false;
            }
        }
        system("CLS");

    }

    void player_sets_attack() {		//function to let the user attack entering the coordinates rows,columns
        do {
            valid_attack_coordinates = true;
            player_grid_print_and_player_attack_grid_print();
            cout << setw(76) << "Where should we target? CAPTAIN: ";
            cin.getline(player_attack_coordinates, 10, '\n');	//store the user entry

            check_for_correct_attack_coordinates();		//checks if coordinate entered is in the correct format, then proceeds to the horzontal or vertical placement. After that checks if v/h is available or not. If not, then returns back here to let the user enter the coordinates again
            if (computer_ship_space_on_board == 0) {		//successfull condition, which prints that the user has won the battle
                for (int i = 0; i < 6; i++) {
                    system("CLS");
                    system("Color 4E");
                    for (int i = 0; i < 19; i++) {
                        cout << endl;
                    }
                    Sleep(500);
                    cout << setw(60) <<"Captain!! Mission Accomplised. Victory is ours!!" << endl;
                    Sleep(1500);
                }
                exit(0);		//end program
            }
            else if (valid_attack_coordinates == true) {		//if the ship_space of computer not zero, then repeat
                Sleep(1500);
                player_grid_print_and_player_attack_grid_print();		//print grids
                computer_sets_attack();		//let the computer take turn
            }
        } while (!valid_attack_coordinates || computer_ship_space_on_board > 0);
    }

    void check_for_correct_attack_coordinates() {	//checks if the user entered correct format
        if (player_attack_coordinates[0] == 'q' || player_ship_coordinates[0] == 'Q') {	// if user presses Q after the ship is set, then they are allowed to quit the program with a goodbye message on display
            quit = true;
            print_computer_board();
            system("CLS");
            for (int i = 0; i < 3; i++) {
                for (int i = 0; i < 6; i++) {
                    cout << endl;
                }
                cout << setw(52) << "You chose to exit out of the game. Bye" << endl;
                Sleep(2000);
                system("CLS");
            }
            exit(0);
        }
        if (player_attack_coordinates[0] < 'a' || player_attack_coordinates[0] > 'j' ||		//checking for incorrect format
            player_attack_coordinates[1] < '0' || player_attack_coordinates[1] > '9') {
            valid_attack_coordinates = false;		//set it false, as it is not a valid entry
            system("CLS");
            player_grid_print_and_player_attack_grid_print();	//print the grid
            cout << setw(91) << "Invalid coordinates. Please try again. Alphabet followed by a number. eg: h1" << endl;	//along with the message
            Sleep(2000);	//let the user read the message, 2 sec
        }
        else {
            assign_values_of_attack_row_column();
            player_sets_attack_on_board();
        }
    }

    void assign_values_of_row_column() {		//assigning values to the rows and columns as read from the value entered by the user. This assigns appropriate location for the char/num combination entered by the user

        if (player_ship_coordinates[0] == 'a') {
            row = 0;
        }
        else if (player_ship_coordinates[0] == 'b') {
            row = 1;
        }
        else if (player_ship_coordinates[0] == 'c') {
            row = 2;
        }
        else if (player_ship_coordinates[0] == 'd') {
            row = 3;
        }
        else if (player_ship_coordinates[0] == 'e') {
            row = 4;
        }
        else if (player_ship_coordinates[0] == 'f') {
            row = 5;
        }
        else if (player_ship_coordinates[0] == 'g') {
            row = 6;
        }
        else if (player_ship_coordinates[0] == 'h') {
            row = 7;
        }
        else if (player_ship_coordinates[0] == 'i') {
            row = 8;
        }
        else if (player_ship_coordinates[0] == 'j') {
            row = 9;
        }

        if (player_ship_coordinates[1] == '0') {
            col = 1;
        }
        else if (player_ship_coordinates[1] == '1') {
            col = 2;
        }
        else if (player_ship_coordinates[1] == '2') {
            col = 3;
        }
        else if (player_ship_coordinates[1] == '3') {
            col = 4;
        }
        else if (player_ship_coordinates[1] == '4') {
            col = 5;
        }
        else if (player_ship_coordinates[1] == '5') {
            col = 6;
        }
        else if (player_ship_coordinates[1] == '6') {
            col = 7;
        }
        else if (player_ship_coordinates[1] == '7') {
            col = 8;
        }
        else if (player_ship_coordinates[1] == '8') {
            col = 9;
        }
        else if (player_ship_coordinates[1] == '9') {
            col = 10;
        }
    }


    void assign_values_of_attack_row_column() {		//same thing as the above but for the grid that takes a hit (computer's)

        if (player_attack_coordinates[0] == 'a') {
            attack_row = 0;
        }
        else if (player_attack_coordinates[0] == 'b') {
            attack_row = 1;
        }
        else if (player_attack_coordinates[0] == 'c') {
            attack_row = 2;
        }
        else if (player_attack_coordinates[0] == 'd') {
            attack_row = 3;
        }
        else if (player_attack_coordinates[0] == 'e') {
            attack_row = 4;
        }
        else if (player_attack_coordinates[0] == 'f') {
            attack_row = 5;
        }
        else if (player_attack_coordinates[0] == 'g') {
            attack_row = 6;
        }
        else if (player_attack_coordinates[0] == 'h') {
            attack_row = 7;
        }
        else if (player_attack_coordinates[0] == 'i') {
            attack_row = 8;
        }
        else if (player_attack_coordinates[0] == 'j') {
            attack_row = 9;
        }

        if (player_attack_coordinates[1] == '0') {
            attack_col = 1;
        }
        else if (player_attack_coordinates[1] == '1') {
            attack_col = 2;
        }
        else if (player_attack_coordinates[1] == '2') {
            attack_col = 3;
        }
        else if (player_attack_coordinates[1] == '3') {
            attack_col = 4;
        }
        else if (player_attack_coordinates[1] == '4') {
            attack_col = 5;
        }
        else if (player_attack_coordinates[1] == '5') {
            attack_col = 6;
        }
        else if (player_attack_coordinates[1] == '6') {
            attack_col = 7;
        }
        else if (player_attack_coordinates[1] == '7') {
            attack_col = 8;
        }
        else if (player_attack_coordinates[1] == '8') {
            attack_col = 9;
        }
        else if (player_attack_coordinates[1] == '9') {
            attack_col = 10;
        }
    }

    void assigning_computer_coordinates_to_alphabets() {		//converting the computer generated coordinated to alphabets, so that both the user entered value and computer generated value matches , and it becomes easier to follow through with the same function later on
        if (computer_attack_row == 0) {
            first_computer_coordinate = 'a';
        }
        else if (computer_attack_row == 1) {
            first_computer_coordinate = 'b';
        }
        else if (computer_attack_row == 2) {
            first_computer_coordinate = 'c';
        }
        else if (computer_attack_row == 3) {
            first_computer_coordinate = 'd';
        }
        else if (computer_attack_row == 4) {
            first_computer_coordinate = 'e';
        }
        else if (computer_attack_row == 5) {
            first_computer_coordinate = 'f';
        }
        else if (computer_attack_row == 6) {
            first_computer_coordinate = 'g';
        }
        else if (computer_attack_row == 7) {
            first_computer_coordinate = 'h';
        }
        else if (computer_attack_row == 8) {
            first_computer_coordinate = 'i';
        }
        else if (computer_attack_row == 9) {
            first_computer_coordinate = 'j';
        }
    }



    void player_sets_attack_on_board() {			//function that sets attack on the grid where computer placed it's ships
        if (player_attack_radar[attack_row][attack_col] == '*' || player_attack_radar[attack_row][attack_col] == '?') {		//check if the spots that has already been marked
            player_grid_print_and_player_attack_grid_print();	//if so, print the grid and show below message, ready for the next round
            cout << setw(82) << "This position has already been attacked";
            Sleep(2000);
            valid_attack_coordinates = false;			//this is important as it is not valid attack, and it shouln't decrement the number of total_ship_space or the number of individual_ships
        }
        else if (computer_board[attack_row][attack_col] == 'D') {	//if destroyer ship located, then print the board and display the message, whilst reducing the computer_ship_space as well as Destroyer's life
            player_grid_print_and_player_attack_grid_print();
            cout << setw(84) << "Captain, we have been informed that we just struck the Destroyer of our opponent. SIR!! ";
            player_attack_radar[attack_row][attack_col] = '*';		//mark as hit
            destroyer_size--;
            computer_ship_space_on_board--;
        }	// repeat the process as for the destroyer ship for all other ships
        else if (computer_board[attack_row][attack_col] == 'S') {
            player_grid_print_and_player_attack_grid_print();
            cout << setw(84) << "Captain, we have been informed that we just struck the Submarine of our opponent. SIR!! ";
            player_attack_radar[attack_row][attack_col] = '*';
            submarine_size--;
            computer_ship_space_on_board--;
        }
        else if (computer_board[attack_row][attack_col] == 'B') {
            player_grid_print_and_player_attack_grid_print();
            cout << setw(84) << "Captain, we have been informed that we just struck the Battleship of our opponent. SIR!! ";
            player_attack_radar[attack_row][attack_col] = '*';
            battleship_size--;
            computer_ship_space_on_board--;
        }
        else if (computer_board[attack_row][attack_col] == 'C') {
            player_grid_print_and_player_attack_grid_print();
            cout << setw(84) << "Captain, we have been informed that we just struck the Carrier of our opponent. SIR!! ";
            player_attack_radar[attack_row][attack_col] = '*';
            carrier_size--;
            computer_ship_space_on_board--;
        }
        else if (computer_board[attack_row][attack_col] == 'R') {
            player_grid_print_and_player_attack_grid_print();
            cout << setw(84) << "Captain, we have been informed that we just struck the Cruiser of our opponent. SIR!! ";
            player_attack_radar[attack_row][attack_col] = '*';
            cruiser_size--;
            computer_ship_space_on_board--;
        }
        else {							//if not hit to the already hit location,nor it hits any ships, then display message that it missed
            player_grid_print_and_player_attack_grid_print();
            cout << setw(71) << "Missed the target." << endl << endl;
            player_attack_radar[attack_row][attack_col] = '?';		//mark that location as occupied

        }

    }

    void print_computer_board() {		//function to print out the coordinates of ships that computer generated randomly
        system("CLS");
        system("Color F1");
        cout << endl << endl;
        cout << setw(84) << "Here is a sneak peek towards your enemy's base" << endl <<endl;
        cout << setw(73) << "0 1 2 3 4 5 6 7 8 9" << endl;		//column title 0,1,2...
        cout << setw(52) << " " << (char)218;		//corner bar character
        for (int i = 0; i < 21; i++) {
            cout << (char)196;			//bottom bar character
        }cout << (char)191 << endl;		//corner bar character
        for (int i = 0; i < 10; i++) {
            cout << setw(52) << (char)board_title++;	//row title A,B,C...
            for (int j = 0; j < 12; j++) {
                if (computer_board[i][j] == '|') {		//spots that are edges
                    cout << (char)179 << " ";
                }
                else if (computer_board[i][j] == '-') {		//spots that are free
                    cout << (char)196 << " ";
                }
                else if (computer_board[i][j] == 'D') {		//spots with destroyer
                    cout << (char)68 << " ";
                }
                else if (computer_board[i][j] == 'S') {		//spots with submarine
                    cout << (char)83 << " ";
                }
                else if (computer_board[i][j] == 'R') {		//spots with cruiser
                    cout << (char)82 << " ";
                }
                else if (computer_board[i][j] == 'B') {		//spots with battleship
                    cout << (char)66 << " ";
                }
                else if (computer_board[i][j] == 'C') {		//spots with carrier
                    cout << (char)67 << " ";
                }
            }cout << endl;
        }
        board_title = 65;		//char-->A, incremented later for next characters
        cout << setw(52) << " " << (char)192;	//corner bar character
        for (int i = 0; i < 21; i++) {
            cout << (char)196;			//bottom bar character
        }cout << (char)217 << endl << endl;		//corner bar character
        Sleep(3300);
    }


    void computer_sets_attack() {		//computer attack function. It generates a random number for computer_attack_row and computer_attack_column within the range to attack on the player board
        do {
            valid_computer_attack_coordinates = true;
            computer_attack_row = rand() % 11;
            computer_attack_col = rand() % 11;

            if (destroyer_hit == true) {	// if the boolean is set to true, and the coordinate is marked D, then proceed to the function computer's attack, which in turn decreases the destroyer's coordinate and marks as a hit
                if (player_board[computer_attack_row][computer_attack_col] == 'D') {
                    computer_sets_attack_on_board();
                }
                else {
                    valid_computer_attack_coordinates = false;		//checks valid move, if false then have to loop the do-while loop again
                }
            }
            else if (submarine_hit == true) {
                if (player_board[computer_attack_row][computer_attack_col] == 'S') {
                    computer_sets_attack_on_board();
                }
                else {
                    valid_computer_attack_coordinates = false;
                }
            }
            else if (cruiser_hit == true) {
                if (player_board[computer_attack_row][computer_attack_col] == 'R') {
                    computer_sets_attack_on_board();
                }
                else {
                    valid_computer_attack_coordinates = false;
                }
            }
            else if (battleship_hit == true) {
                if (player_board[computer_attack_row][computer_attack_col] == 'B') {
                    computer_sets_attack_on_board();
                }
                else {
                    valid_computer_attack_coordinates = false;
                }
            }
            else if (carrier_hit == true) {
                if (player_board[computer_attack_row][computer_attack_col] == 'C') {
                    computer_sets_attack_on_board();
                }
                else {
                    valid_computer_attack_coordinates = false;
                }
            }

            if (destroyer_hit == false && submarine_hit == false	//if not hit
                && battleship_hit == false && carrier_hit == false && cruiser_hit == false) {
                computer_sets_attack_on_board();
            }

        } while (!valid_computer_attack_coordinates || player_ship_space_on_board > 0);	//player_ship_space_on_board in on the decrement, thus when it hits zero, it breaks from the do-while loop
    }


    void computer_sets_attack_on_board() {		//computer sets attack in random coordinates, outputs a message saying that a certain ship has been hit, and takes out its (analogy as lives left in a game) out of total spots taken
        assigning_computer_coordinates_to_alphabets();
        if (player_board[computer_attack_row][computer_attack_col] == 'D') {
            cout << setw(82) << "Captain, we have been informed that our Destroyer has been struck by our opponent. SIR!! " << first_computer_coordinate << computer_attack_col - 1 << endl << endl;
            destroyer_hit = true;
            player_board[computer_attack_row][computer_attack_col] = '*';
            player_ship_space_on_board--;
            player_destroyer_size--;
        }
        else if (player_board[computer_attack_row][computer_attack_col] == 'S') {
            cout << setw(81) << "Captain, we have been informed that our Submarine has been struck by our opponent. SIR!! " << first_computer_coordinate << computer_attack_col - 1 << endl << endl;
            submarine_hit = true;
            player_board[computer_attack_row][computer_attack_col] = '*';
            player_ship_space_on_board--;
            player_submarine_size--;
        }
        else if (player_board[computer_attack_row][computer_attack_col] == 'B') {
            cout << setw(81) << "Captain, we have been informed that our Battleship has been struck by our opponent. SIR!! " << first_computer_coordinate << computer_attack_col - 1 << endl << endl;
            battleship_hit = true;
            player_board[computer_attack_row][computer_attack_col] = '*';
            player_ship_space_on_board--;
            player_battleship_size--;
        }
        else if (player_board[computer_attack_row][computer_attack_col] == 'C') {
            cout << setw(81) << "Captain, we have been informed that our Carrier has been struck by our opponent. SIR!! " << first_computer_coordinate << computer_attack_col - 1 << endl << endl;
            carrier_hit = true;
            player_board[computer_attack_row][computer_attack_col] = '*';
            player_ship_space_on_board--;
            player_carrier_size--;
        }
        else if (player_board[computer_attack_row][computer_attack_col] == 'R') {
            cout << setw(81) << "Captain, we have been informed that our Cruiser has been struck by our opponent. SIR!! " << first_computer_coordinate << computer_attack_col - 1 << endl << endl;
            cruiser_hit = true;
            player_board[computer_attack_row][computer_attack_col] = '*';
            player_ship_space_on_board--;
            player_cruiser_size--;
        }
        else if (player_board[computer_attack_row][computer_attack_col] == '-') {	//condition for misses, if these spots were hit, then mark it as X (for misses)
            cout << setw(73) << "Opponent missed the target: " << first_computer_coordinate << computer_attack_col - 1 << endl << endl;
            player_board[computer_attack_row][computer_attack_col] = '?';

        }
        else {
            valid_computer_attack_coordinates = false;
        }
        clear_hit();
        if (player_ship_space_on_board == 0) {	//opponent's winning condition, and message
            for (int i = 0; i < 6; i++) {
                system("CLS");
                system("Color F4");
                for (int i = 0; i < 19; i++) {
                    cout << endl;
                }
                Sleep(500);
                cout << setw(72) << "Mission Failed!! You lose the battle" << endl;
                Sleep(500);
            }
            print_computer_board();
            exit(0);
        }
        else if (valid_computer_attack_coordinates == true) {
            Sleep(1500);
            player_sets_attack();
        }
    }

    void clear_hit() {		//boolean check function
        if (player_carrier_size == 0) {
            carrier_hit = false;
        }
        if (player_submarine_size == 0) {
            submarine_hit = false;
        }
        if (player_cruiser_size == 0) {
            cruiser_hit = false;
        }
        if (player_destroyer_size == 0) {
            destroyer_hit = false;
        }
        if (player_battleship_size == 0) {
            battleship_hit = false;
        }

    }

    //function is not used, but it could be used if we want to restart the game. this functions RESETS everthing
    void board_clearer() {			//clear the grid every row, every column
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                if (player_board[i][j] == 'D' || computer_board[i][j] == 'D' ||
                    player_board[i][j] == 'S' || computer_board[i][j] == 'S' ||
                    player_board[i][j] == 'R' || computer_board[i][j] == 'R' ||
                    player_board[i][j] == 'B' || computer_board[i][j] == 'B' ||
                    player_board[i][j] == 'C' || computer_board[i][j] == 'C' ||
                    player_board[i][j] == '*' || player_attack_radar[i][j] == '*' ||
                    player_board[i][j] == '?' || player_attack_radar[i][j] == '?') {
                    player_board[i][j] = '-';	// reset player board
                    computer_board[i][j] = '-';		//reset computer board
                    player_attack_radar[i][j] = '-';
                }
            }
        }
        count_computer_ship = 0;		//reset to zero, b/c increment is used to keep within the range with the helpf of while loop
        count_player_ship = 0;			//reset to zero, b/c increment is used to keep within the range with the helpf of while loop
        computer_ship_space_on_board = 17;	//total ship spaces taken by 5 ships (Computer)
        player_ship_space_on_board = 17;	//total ship spaces taken by 5 ships (Player)
        destroyer_size = 2;				//reset the sizes of the ships
        player_destroyer_size = 2;
        submarine_size = 3;
        player_submarine_size = 3;
        cruiser_size = 3;
        player_cruiser_size = 3;
        battleship_size = 4;
        player_battleship_size = 4;
        carrier_size = 5;
        player_carrier_size = 5;
    }

    void print_quit_option() {		//prints evertime the grid is printed, letting user know the option available too quit pressing Q
        for (int i = 0; i < 10; i++) {
            cout << endl;
        }
        cout <<setw(92) << "Press Q if you want to exit out of the game" << endl;
    }

};




int main() {
    Grid g;
    Battleship b;	//b object of derived class Battleship from the base class Grid
    b.opening_menu();	//basic use of inheritance, as opening_menu() is inherited from the base class, which call all other necessary functions required

    //below function could be used to restart the game, by setting the above b.opening_menu() and below b.board_clearer() inside a while loop using boolean argument.
    //b.board_clearer();

}
