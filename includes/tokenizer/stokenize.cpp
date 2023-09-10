#include "stokenize.h"

int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];

STokenizer::STokenizer(){
    //step 1: buffer set up to all null characters
    for (int j = 0; j < MAX_BUFFER; j++){
        _buffer[j] = 0;
    }
    //step 2: pos set to 0
    _pos = 0;
    //step 3: make the table
    make_table(_table);
}

STokenizer::STokenizer(char str[]){
    int i = 0;
    //need to initialize buffer before copying in str
    for (int j = 0; j < MAX_BUFFER; j++){
        _buffer[j] = 0;
    }
    _pos = 0;
    //copy str to buffer, pos at 0
    for (i; str[i] != '\0'; i++){
        _buffer[i] = str[i];
    }
    _buffer[i] = '\0'; 
    make_table(_table);
}

//if pos before _pos is null, entire token and up to first null was reached
//  and is therefore done.
bool STokenizer::done(){
    return (_pos > strlen(_buffer));
    //return (_buffer[_pos-1] == '\0'); alternate method used previously, works
    
}

//opposite of above but essentially works the same
bool STokenizer::more(){
    return (_pos <= strlen(_buffer));
    //return (_buffer[_pos-1] != '\0'); read comment above
}

//the real meat of the stokenizer, main call to string tokenize
//  heavy reliance on get_token
STokenizer& operator >> (STokenizer& s, Token& t){
    int type_start = -1;
    string token;
    if (s._buffer[s._pos] > 0){
        type_start = s._table[0][s._buffer[s._pos]];
    }
    //for case involving end of list
    if (s._buffer[s._pos] == '\0'){
        t = Token();
        s._pos++;
        return s;
    }
    if (s.get_token(type_start, token)){
        if (type_start == START_DOUBLE){
            t = Token(token, TOKEN_NUMBER);
        }
        if (type_start == START_SPACES){
            t = Token(token, TOKEN_SPACE);
        }
        if (type_start == START_ALPHA){
            t = Token(token, TOKEN_ALPHA);
        }
        if (type_start == START_OPERATOR || type_start == 31){
            t = Token(token, TOKEN_OPERATOR);
        }
        if (type_start == START_PUNC){
            t = Token(token, TOKEN_PUNC);
        }
    }
    else{
        t = Token(token, TOKEN_UNKNOWN);
        s._pos++;
    }

    return s;
}

void STokenizer::set_string(string str){
    int i = 0;
    for (int j = 0; j < MAX_BUFFER; j++){
        _buffer[j] = 0;
    }
    _pos = 0;
    for (i; str[i] != '\0'; i++){
        _buffer[i] = str[i];
    }
    _buffer[i] = '\0';
}

void STokenizer::make_table(int _table[][MAX_COLUMNS]){
    //initialize table to -1 values across the board to set for fails
    init_table(_table);

    //NUMBERS
    mark_fail(_table, 0);            //if something fails on first state fails
    mark_success(_table, 1);         //1st state is one or more numbers, success
    mark_fail(_table, 2);            //2nd state is period, must be followed by period or fails
    mark_success(_table, 3);         //3rd state is one or more numbers, success
    //one or more numbers, can be followed by a period if also ends with number
    mark_cells(0, _table, DIGITS, 1);    //state [0] --- DIGITS ---> [1]
    mark_cells(1, _table, DIGITS, 1);    //state [1] --- DIGITS ---> [1]
    mark_cell(1, _table, '.', 2);        //state [1] --- '.' ------> [2] 
    mark_cells(2, _table, DIGITS, 3);    //state [2] --- DIGITS ---> [3]
    mark_cells(3, _table, DIGITS, 3);    //state [3] --- DIGITS ---> [3]

    //SPACES
    mark_success(_table, 10);       //success state for space chars
    //one or more spaces, loops in 10 state until failure
    mark_cells(0, _table, SPACES, 10);   //state[0] --- SPACES ---> [10]
    mark_cells(10, _table, SPACES, 10);  //state[10] --- SPACES ---> [10]

    //ALPHABET
    mark_success(_table, 20);       //success state for alpha chars
    //one or more letters, loops in 20 state until failure
    mark_cells(0, _table, ALFA, 20);      //state[0] --- ALFA ---> [20]
    mark_cells(20, _table, ALFA, 20);     //state[20] --- ALFA ---> [20]

    //OPERATOR
    mark_success(_table, 30);       //success state for operator chars
    mark_success(_table, 31);       //success state for < and >
    mark_success(_table, 32);       //success state if = follows > or <
    //one operator, special case for two, no loops and all success states
    mark_cells(0, _table, OPERATORS, 30);//state [0] --- OPS ---> [30]
    //special case for "<=" and ">=", also accounts for standalone '<' and '>'
    mark_cell(0, _table, '>', 31);       //state [0] --- '>' ---> [31]
    mark_cell(0, _table, '<', 31);       //state [0] --- '<' ---> [31]
    mark_cell(31, _table, '=', 32);      //state [31] --- '=' ---> [32]

    //PUNCTUATIONS
    mark_success(_table, 40);       //success state for puncs
    //one punctuation mark per token
    mark_cells(0, _table, PUNC, 40);     //state [0] --- PUNC ---> [40]
}

bool STokenizer::get_token(int start_state, string& token){
    int i = _pos;
    int new_state = 0;
    int last_success = -1;
    int set = 0;
    char temp[200] = {0};
    
    if (_buffer[_pos] < 0 || _buffer[_pos] > 127){
        //cout << _buffer[_pos];
        token = _buffer[_pos];
        _pos++;
        return false;
    }

    //state machine process, runs until end of buffer or fail state
    while ((new_state != -1) && (_buffer[i] != '\0')){
        //cout << _buffer[i] <<": Input!\n";
        new_state = _table[new_state][_buffer[i]];
        if (is_success(_table, new_state)){
            //cout << "Success!\n";
            last_success = i;
        }
        i++;
    }
    //setting our token string to copy up to last success state
    for (_pos; _pos <= last_success; _pos++){
        temp[set] = _buffer[_pos];
        set++;
    }
    token = temp;

    //cout << token << "<-Token passed!\n";
    return (last_success != -1);
}
