#include <iostream>
#include <fstream>
#include <string>
#include <cctype> // For isalnum and isalpha functions

using namespace std;

const int ROW = 3; 
const int COL = 3; 

void boardPrint(string matrix[ROW][COL]);
bool isRightMove(int row, int col, bool occupied[ROW][COL]);
bool winningProbability(string MATRIX[ROW][COL], string player);
void registeredAccount();
unsigned int hashPassword(string &username, string &password);
bool login();
bool isValidInput(const string &input);

int main()
{
    while (true)
    {
        int option; 
        cout << " 1. Register \n 2. Log in\n 3. Quit the game \n Please choose the following options: ";
        cin >> option; 
        cin.ignore();

        switch(option)
        {
            case 1: 
                registeredAccount(); 
                break; 
            case 2: 
                if (!login())
                {
                    cout << "Invalid login credentials. Returning to the main menu.\n";
                    break;
                }

                // If login is successful, start the game
                {
                    string board[ROW][COL] = {""};  // Correctly initializing the board with empty strings
                    string player1 = "x";
                    string player2 = "o";
                    
                    int row, col; 
                    int steps = 0; 
                    bool occupied[ROW][COL] = {false}; // initializing occupied spots

                    while(steps < 9) 
                    {
                        cout << "Player " << (steps % 2 == 0 ? "1" : "2") << ": Please choose your move (row, col): ";
                        cin >> row >> col;
                        
                        while(!isRightMove(row, col, occupied))
                        {
                            if (occupied[row][col])
                            {
                                cout << "The position has already been chosen. Please choose another spot (row, col): ";
                            }
                            else
                            {
                                cout << "Invalid move. Please choose your move (row, col): ";
                            }
                            cin >> row >> col;
                        }
                    
                        string currentPlayer = (steps % 2 == 0) ? player1 : player2;
                        board[row][col] = currentPlayer; 
                        occupied[row][col] = true;  
                        boardPrint(board); // print the board
                        steps++;  // increment the step

                        if (winningProbability(board, currentPlayer))
                        {
                            cout << "Player " << (steps % 2 == 0 ? "2" : "1") << " wins!" << endl; 
                            break;
                        }

                        if (steps == 9)
                        {
                            cout << "The game is tied" << endl;
                            break;  
                        }
                    }
                }
                break; 
            case 3: 
                cout << "Exiting the program\n";
                return 0;
            default: 
                cout << "Invalid option. Please choose again\n";
                break;
        }
    }

    return 0;    
}

void boardPrint(string matrix[ROW][COL])
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            cout << (matrix[i][j] == "" ? "." : matrix[i][j]) << " ";
        }
        cout << endl;
    }
}

bool isRightMove(int row, int col, bool occupied[ROW][COL])
{
    if (row >= 0 && row < 3 && col >= 0 && col < 3 && !occupied[row][col])  // Check if the move is within bounds and not occupied
    {
        return true; 
    }
    return false; 
}

bool winningProbability(string MATRIX[ROW][COL], string player)
{
    // Check rows and columns
    for (int i = 0; i < ROW; i++)
    {
        if ((MATRIX[i][0] == player && MATRIX[i][1] == player && MATRIX[i][2] == player) ||
            (MATRIX[0][i] == player && MATRIX[1][i] == player && MATRIX[2][i] == player))
        {
            return true; 
        }
    }

    // Check diagonals
    if ((MATRIX[0][0] == player && MATRIX[1][1] == player && MATRIX[2][2] == player) ||
        (MATRIX[0][2] == player && MATRIX[1][1] == player && MATRIX[2][0] == player))
    {
        return true; 
    }
    
    return false; 
}

void registeredAccount()
{
    string username, password, checked_password; 
    cout << "Please enter your username: ";
    getline(cin, username);

    while (!isValidInput(username))
    {
        cout << "Username should contain only letters, numbers, and the characters @, #, $, %, ^, &, ! and must contain at least one letter. Please enter your username again: ";
        getline(cin, username);
    }

    do 
    {
        cout << "Please enter your password: ";
        getline(cin, password);

        while (!isValidInput(password))
        {
            cout << "Password should contain only letters, numbers, and the characters @, #, $, %, ^, &, ! and must contain at least one letter. Please enter your password again: ";
            getline(cin, password);
        }

        cout << "Please re-enter your password: ";
        getline(cin, checked_password);
        if (password != checked_password)
        {
            cout << "Password is not matching with the authenticated password" << endl;
        }
    } while(password != checked_password);

    unsigned int hash_password = hashPassword(username, password);
    ofstream outputFile; 
    outputFile.open("user_information.txt", ios::app);

    if(!outputFile.is_open())
    {
        cerr << "Unable to read the file." << endl; 
        exit(1);
    }

    outputFile << username << endl; 
    outputFile << hash_password << endl; 
    cout << "Your account is successfully created." << endl; 

    outputFile.close();
}

unsigned int hashPassword(string &username, string &password)
{
    unsigned int result = 0;

    for (unsigned int ch:username)
    {
        result = ch + (result << 4) + (result << 10) - result; 
    }

    for (unsigned int ch:password)
    {
        result = ch + (result << 4) + (result << 10) - result; 
    }

    return result; 
}

bool login()
{
    string username, password; 

    cout << "Please enter your username: ";
    cin >> username; 

    if (!isValidInput(username))
    {
        cout << "Username should contain only letters, numbers, and the characters @, #, $, %, ^, &, ! and must contain at least one letter.\n";
        return false;
    }

    cout << "Please enter your password: ";
    cin >> password; 

    if (!isValidInput(password))
    {
        cout << "Password should contain only letters, numbers, and the characters @, #, $, %, ^, &, ! and must contain at least one letter.\n";
        return false;
    }

    ifstream inputFile; 
    inputFile.open("user_information.txt");

    if(!inputFile.is_open())
    {
        cerr << "Unable to read the file." << endl;
        exit(1);
    }

    string valid_username; 
    unsigned int valid_password; 

    unsigned int hash_password = hashPassword(username, password);

    while (inputFile >> valid_username >> valid_password)
    {
        if (username == valid_username && valid_password == hash_password)
        {
            cout << "Login successful." << endl;
            inputFile.close();
            return true; 
        }
    }
    inputFile.close();
    return false; 
}

bool isValidInput(const string &input)
{
    bool hasLetter = false;
    for (char ch : input)
    {
        if (isalnum(ch) || ch == '@' || ch == '#' || ch == '$' || ch == '%' || ch == '^' || ch == '&' || ch == '!')
        {
            if (isalpha(ch))  // Check if there's at least one letter
            {
                hasLetter = true;
            }
        }
        else
        {
            return false;  // Invalid character found
        }
    }
    return hasLetter;  // Ensure there's at least one letter
}
