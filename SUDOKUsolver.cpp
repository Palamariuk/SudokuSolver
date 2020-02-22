#include <iostream>
#include <fstream>

using namespace std;

void ReadFromFile(string name, int array[9][9]) {

    ifstream in;
    in.open("sudoku.in");
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            in >> array[i][j];
    in.close();

}

void PrintTable(int array[9][9]) {

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << array[i][j] << " ";
            if ((j + 1) % 3 == 0 && j != 8) cout << "| ";
        }
        if ((i+1) % 3 == 0 && i!=8) cout << "\n----------------------";
        cout << "\n";
    }
}

bool IsValid(int array[9][9], int num, int I, int J) {

    for (int j = 0; j < 9; j++) {
        if (array[I][j] == num) return false;
    }
    for (int i = 0; i < 9; i++) {
        if (array[i][J] == num) return false;
    }

    int boxI = 3 * (I / 3);
    int boxJ = 3 * (J / 3);

    for (int i = boxI; i < boxI + 3; i++) {
        for (int j = boxJ; j < boxJ + 3; j++)
            if (array[i][j] == num) return false;
    }

    return true;

}

bool IsEmpty(int array[9][9]) {

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (array[i][j] == 0) return false;
    return true;

}

bool SudokuSolver(int array[9][9]) {

    if (IsEmpty(array)) return true; //

    int emptyI, emptyJ;

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (array[i][j] == 0) {
                emptyI = i; 
                emptyJ = j;
                break;
            }

    for (int k = 1; k < 10; k++) {
        if (IsValid(array, k, emptyI, emptyJ)) {
            array[emptyI][emptyJ] = k;
            if (SudokuSolver(array)) return true;
            array[emptyI][emptyJ] = 0;
        }
    }

    return false;

}

int main()
{
    int sudoku[9][9];
    ReadFromFile("sudoku.in", sudoku);

    cout << "Before\n";
    PrintTable(sudoku);

    SudokuSolver(sudoku);

    cout << "After\n";
    PrintTable(sudoku);
}

