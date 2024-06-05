#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// Constructors
int displayMenu(int round);
void singlePlayer();
void multiPlayer();
void displayStats();
bool exitScript();

// Constants
const int ROWS = 3;
const int COLS = 3;

const string p1Move = "X";
const string p2Move = "O";

// Global Variables for Wins and Losses
int singlePWins = 0;
int singlePLose = 0;

int p1Win = 0;
int p1Lose = 0;

int p2Win = 0;
int p2Lose = 0;


// Main Method
int main()
{
    // Variable Declaration
    bool repeat = true;
    int rounds = 0;
    int choice;

    // Loop till 'repeat' == false
    while(repeat == true)
    {
        // Choice Assignment
        choice = displayMenu(rounds);

        //Single PLayer Initialization
        if(choice == 1)
        {
            singlePlayer();
            rounds += 1;
        }

        // Multi Player Initialization
        else if(choice == 2)
        {
            multiPlayer();
            rounds += 1;
        }

        // Shows the Game Stats
        else if(choice == 3)
        {
            displayStats();
        }

        // Break for Quit Game
        else if(choice == 4)
        {
            repeat = exitScript();
            break;
        }
    }

    return 0;
}

// Displays the Menu for the game every iteration and
int displayMenu(int round)
{
    // Variable Declaration
    int choice;

    // Starting Output
    cout << endl << endl << "Welcome to the Tic Tac Toe Game!" << endl;
    cout << "You have played " << round << " rounds." << endl << endl;

    // Do while function for valid choices
    do
    {
        cout << "Select the Game Type" << endl;
        cout << "1: Single Player" << endl;
        cout << "2: Multiplayer" << endl;
        cout << "3: Display Stats" << endl;
        cout << "4: Quit Game" << endl;

        cin >> choice;

        // Checks if choice is a valid option
        if (choice < 1 || choice > 4)
        {
            cout << "\nPLEASE SELECT A VALID OPTION FROM BELOW!" << endl << endl;
        }
    } while (choice < 1 || choice > 4); // Input validation

    return choice;
}

// Checks wins or losses after every move
bool checkWin(string board[ROWS][COLS], int row, int col, string move)
{

    // Check row
    bool win = true;
    for (int i = 0; i < COLS; ++i)
    {
        if (board[row][i] != move)
        {
            win = false;
            break;
        }
    }
    if (win) return true;

    // Check column
    win = true;
    for (int i = 0; i < ROWS; ++i)
    {
        if (board[i][col] != move)
        {
            win = false;
            break;
        }
    }
    if (win) return true;

    // Check main diagonal
    if (row == col)
    {
        win = true;
        for (int i = 0; i < ROWS; ++i)
        {
            if (board[i][i] != move)
            {
                win = false;
                break;
            }
        }
        if (win) return true;
    }

    // Check anti-diagonal
    if (row + col == ROWS - 1)
    {
        win = true;
        for (int i = 0; i < ROWS; ++i)
        {
            if (board[i][ROWS - 1 - i] != move)
            {
                win = false;
                break;
            }
        }
        if (win) return true;
    }

    return false;
}

// Displays the Grid with everyone's moves
void displayGrid(string board[ROWS][COLS])
{
    cout << endl << "Row is side numbers, and column is top numbers" << endl;
    cout << "  ";

    // Top numbers for Columns
    for (int i = 1; i <= COLS; i++)
    {
        cout << i << " ";
    }

    cout << endl;

    // Creating grid as well as rows
    for (int i = 0; i < ROWS; i++)
    {
        cout << (i + 1) << " ";
        for (int j = 0; j < COLS; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Sets random variables so that AI can play against the player
void aiScript(string board[ROWS][COLS], int& row, int& col)
{
    // Random seed for generation
    srand(time(0));
    while (true)
    {
        // Chooses Random Row and Column
        row = rand() % ROWS + 1;
        col = rand() % COLS + 1;

        // Breaks through the loop if selected space is taken open
        if (board[row-1][col-1] == "*")
        {
            break;
        }
    }
}

// Initializes the Single Player Game Mode
void singlePlayer()
{
    // Variables
    string playerName;

    int row;
    int col;

    bool gameEnd = false;

    // Starting Script
    cout << endl << "Thank you for choosing Single Player!" << endl << endl;

    // Input Method and input clearing for name
    cout << "Enter your player name:";
    cin.ignore();
    getline(cin, playerName);

    cout << endl << endl;

    cout << "Welcome " << playerName << ", we are initializing the AI and the grid, sit tight." << endl << endl;

    cout << "Generating grid . . ." << endl << endl;

    // Grid Array
    string value = "*";
    string board[ROWS][COLS];

    // Creating Array
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            board[i][j] = value;
        }
    }

    // Displays the grid
    displayGrid(board);

    // While loop plays until game is ended and rerouted to main menu
    while(!gameEnd)
    {
        // Player One Move
        while(true)
        {
            // Player input variable
            cout << endl << "Input a move, row then column with a space." << endl;
            cout << "Example Move:\"1 1\"" << endl;    // \" Used to show quotations in script
            cout << playerName << " Move:" << endl;

            cin >> row >> col;

            // Checks if the row and column is within the said array
            if (row < 1 || row > 3 || col < 1 || col > 3)
            {
                cout << endl << "Invalid input. Please enter a row and column between 1 and 3." << endl;
            }

            // Checks if the spot said and given is available and open
            else if (board[row-1][col-1] == p1Move || board[row-1][col-1] == p2Move)
            {
                cout << endl << "Please enter a valid and open spot." << endl << endl;
            }

            // If Both Conditions are met, Input is accepted
            else
            {
                break;
            }
        }
        board[row-1][col-1] = p1Move;
        displayGrid(board);

        // Checks Win for Player 1
        if (checkWin(board, row-1, col-1, p1Move))
        {
            cout << playerName << " Wins!" << endl;
            singlePWins += 1;
            gameEnd = true;
            break;
        }

        // Checks For all spaces filled up for draw
        bool draw = true;     // Draw is only called for P1 since there is a odd number of spaces
        for (int i = 0; i < ROWS; ++i)
        {
            for (int j = 0; j < COLS; ++j)
            {
                if (board[i][j] == "*")
                {
                    draw = false;
                    break;
                }
            }
            if (!draw) break;
        }

        // Displays Draw if all spaces are filled up
        if (draw) {
            cout << "It's a draw!" << endl;
            gameEnd = true;
            break;
        }

        // Calls AI to place a move
        aiScript(board, row, col);
        board[row-1][col-1] = p2Move;
        displayGrid(board);

        // Checks if AI has won the game
        if (checkWin(board, row-1, col-1, p2Move))
        {
            cout << "AI Wins!" << endl;
            singlePLose += 1;
            gameEnd = true;
        }

    }
}

// Initializes the Multi Player Game Mode
void multiPlayer()
{
    // Variables
    string playerOneName;
    string playerTwoName;

    int row;
    int col;

    bool gameEnd = false;

    // Starting Script
    cout << endl << "Thank you for choosing Multi Player!" << endl << endl;

    // Input Method and Input Clearing for Name
    cout << "Enter player 1 name:";
    cin.ignore();
    getline(cin, playerOneName);

    cout << endl << "Enter player 2 name:";
    getline(cin, playerTwoName);

    cout << endl << endl;

    cout << "Generating grid . . ."  << endl << endl;

    // Grid Array
    string value = "*";
    string board[ROWS][COLS];

    // Creating the Grid
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            board[i][j] = value;
        }
    }

    // Displays the grid when called
    displayGrid(board);

    while(!gameEnd)
    {
        // Player One Move
        while(true)
        {
            // Player 1 Input
            cout << endl << "Input a move, row then column with a space." << endl;
            cout << "Example Move:\"1 1\"" << endl;
            cout << playerOneName << " Move:" << endl;

            cin >> row >> col;

            // Checks if the row and column is within the said array
            if (row < 1 || row > 3 || col < 1 || col > 3)
            {
                cout << endl << "Invalid input. Please enter a row and column between 1 and 3." << endl;
            }

                // Checks if the spot said and given is available and open
            else if (board[row-1][col-1] == p1Move || board[row-1][col-1] == p2Move)
            {
                cout << endl << "Please enter a valid and open spot." << endl << endl;
            }

                // If Both Conditions are met, Input is accepted
            else
            {
                break;
            }
        }

        // Adds Accepted Input into Board
        board[row-1][col-1] = p1Move;
        displayGrid(board);

        // Checks if Player One Wins the Game
        if (checkWin(board, row-1, col-1, p1Move))
        {
            cout << playerOneName << " Wins!" << endl;
            p1Win += 1;
            p2Lose += 1;
            gameEnd = true;
            break;
        }

        // Checks if the game is a draw
        bool draw = true;
        for (int i = 0; i < ROWS; ++i)
        {
            for (int j = 0; j < COLS; ++j)
            {
                if (board[i][j] == "*")
                {
                    draw = false;
                    break;
                }
            }
            if (!draw) break;
        }

        // Breaks the loop if the game is a draw
        if (draw)
        {
            cout << "It's a draw!" << endl;
            gameEnd = true;
            break;
        }

        // Player Two Move
        while(true)
        {
            // Player 2 Input
            cout << endl << "Input a move, row then column with a space." << endl;
            cout << "Example Move:\"1 1\"" << endl;
            cout << playerTwoName << " Move:" << endl;

            cin >> row >> col;

            // Checks if the row and column is within the said array
            if (row < 1 || row > 3 || col < 1 || col > 3)
            {
                cout << endl << "Invalid input. Please enter a row and column between 1 and 3." << endl;
            }

            // Checks if the spot said and given is available and open
            else if (board[row-1][col-1] == p1Move || board[row-1][col-1] == p2Move)
            {
                cout << endl << "Please enter a valid and open spot." << endl << endl;
            }

            // If Both Conditions are met, Input is accepted
            else
            {
                break;
            }
        }

        // Accepted input is added onto the board
        board[row-1][col-1] = p2Move;
        displayGrid(board);

        // Checks if Player 2 has won the game
        if (checkWin(board, row-1, col-1, p2Move))
        {
            cout << playerTwoName << " Wins!" << endl;
            p2Win += 1;
            p1Lose += 1;
            gameEnd = true;
        }
    }
}

void displayStats()
{
    // Single Player
    cout << endl << "Stats for Single Player" << endl;
    cout << "Single Player Wins:" << setw(40) << left << singlePWins << endl;
    cout << "Single Player Losses:" << setw(40) << left << singlePLose << endl << endl;

    // Multi Player P1
    cout << "Stats for Multi Player" << endl;
    cout << "Player 1 Wins:" << setw(40) << left << p1Win << endl;
    cout << "Player 1 Losses:" << setw(40) << left << p1Lose << endl << endl;

    // Multiplayer P2
    cout << "Player 2 Wins:" << setw(40) << left << p2Win << endl;
    cout << "Player 2 Losses:" << setw(40) << left << p2Lose << endl << endl;
}

bool exitScript()
{
    // Exit Lines
    cout << endl << "Thank you for Playing the Tic Tac Toe game." << endl;
    cout << "Enjoy the rest of your day!" << endl << endl;

    cout << "Exiting script . . . " << endl;

    // Returns False so Main Method Loop Can Break
    return false;
}
