#include "state_machine_functions.h"

void init_table(int _table[][MAX_COLUMNS]){
    for (int i = 0; i < MAX_ROWS; i++){
        for (int j = 0; j < MAX_COLUMNS; j++){
            _table[i][j] = -1;
        }
    }
}

void mark_success(int _table[][MAX_COLUMNS], int state){
    _table[state][0] = 1;
}

void mark_fail(int _table[][MAX_COLUMNS], int state){
    _table[state][0] = 0;
}

bool is_success(int _table[][MAX_COLUMNS], int state){
    if (state == -1)
        return false;
    return (_table[state][0] == 1);
}

void mark_cells(int row, int _table[][MAX_COLUMNS], int from, int to, int state){
    for (int i = from; i <= to; i++)
    {
        _table[row][i] = state;
    }
}

void mark_cells(int row, int _table[][MAX_COLUMNS], const char columns[], int state){
    for (int i = 0; columns[i] != '\0'; i++){
        _table[row][columns[i]] = state;
    }
}

void mark_cell(int row, int table[][MAX_COLUMNS], int column, int state){
    table[row][column] = state;
}

void print_table(int _table[][MAX_COLUMNS]){
    for (int i = 0; i < MAX_ROWS; i++){
        for (int j = 0; j < MAX_COLUMNS; j++){
            if (_table[i][j] != -1){
                cout << " |"; 
                if (j != 0){
                    cout << (char)j << ":"; 
                }
                cout << " " << _table[i][j] << " | ";
            }
        }
        if (_table[i][0] != -1){
            cout << endl;
        }
    }
}

void show_string(char s[], int _pos){
    for (int i = 0; s[i] != '\0'; i++){
        cout << s[i];
    }
    cout << " pos: " << _pos << endl;
    for (int i = 1; i < _pos; i++){
        cout << " ";
    }
    cout << "^\n";
}