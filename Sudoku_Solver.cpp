#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

bool isSafe(int row, int col, vector<vector<int>> &board, int val) {
    
    for(int i=0; i<9; i++){
        if(board[row][i] == val) 
            return false;
        
        if(board[i][col] == val) 
         return false;
    }
   
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            if(board[3*(row/3) + i][3*(col/3) + j] == val) 
            return false;
        }
    }
    return true;
}

bool solve(vector<vector<int>> & board){
    for(int row=0; row<9; row++) {
        for(int column=0; column<9; column++) {
            if(board[row][column] == 0){
                for(int val=1; val<=9; val++){
                    if(isSafe(row, column, board, val)){
                        board[row][column] = val;
                        if(solve(board)) return true;
                        board[row][column] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;  
}

void DisplayBoard(vector<vector<int>>& board) {
    cout << "Current sudoku board: " << endl;
    for(const auto &row : board) {
        for(int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void userSolve(vector<vector<int>>& board) {
    int row, col, value;
    int invalidAttempts = 0;  
    cout << "Enter your moves in the format: row col value: " << endl;
    cout << "Enter -1 -1 -1 to finish solving" << endl;

    while(true) {
        DisplayBoard(board);
        cout << "Your move: ";
        cin >> row >> col >> value;

        if(row == -1 && col == -1 && value == -1) {
            break;  
        }

        if(row < 1 || row > 9 || col < 1 || col > 9 || value < 1 || value > 9) {
            cout << "Invalid input! " << endl;
            invalidAttempts++;
            if(invalidAttempts >= 3) {
                cout << "Too many invalid attempts! " << endl;
                break;
            }
            continue;
        }

        row--;
         col--;  

        if(board[row][col] != 0) {
            cout << "Cell already filled! " << endl;
            continue;
        }

        if(isSafe(row, col, board, value)) {
            board[row][col] = value;
        } else {
            cout << "Invalid move. The value " << value << " cannot be placed at (" << row + 1 << "," << col + 1 << ")." << endl;
        }
    }
}

int main() {
    vector<vector<int>> sudoku = {
        { 5, 3, 0, 0, 7, 0, 0, 0, 0 },
        { 6, 0, 0, 1, 9, 5, 0, 0, 0 },
        { 0, 9, 8, 0, 0, 0, 0, 6, 0 },
        { 8, 0, 0, 0, 6, 0, 0, 0, 3 },
        { 4, 0, 0, 8, 0, 3, 0, 0, 1 },
        { 7, 0, 0, 0, 2, 0, 0, 0, 6 },
        { 0, 6, 0, 0, 0, 0, 2, 8, 0 },
        { 0, 0, 0, 4, 1, 9, 0, 0, 5 },
        { 0, 0, 0, 0, 8, 0, 0, 7, 9 }
    };

    cout << "Welcome to Sudoku Solver" << endl;
    cout << "Initial Board: " << endl;
    DisplayBoard(sudoku);

    userSolve(sudoku);

    if(solve(sudoku)) {
        cout << "Solved Solution" << endl;
        DisplayBoard(sudoku);
    } else {
        cout << "Cannot be solved" << endl;
    }

    return 0;
}
