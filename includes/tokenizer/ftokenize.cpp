#include "ftokenize.h"

//only constructor, calls in fname to open said file
FTokenizer::FTokenizer(char* fname){
    _f.open(fname);
    _pos = 0;
    _blockPos = 0;
    _more = true;   //sets more to true so it can process
}

//next token is taken in if there is more in stk
Token FTokenizer::next_token(){
    string add; 
    Token t;
    //only gets a new token if there is more tokens to get
    if (_stk.more()){
        _stk>>t;
    }
    add = t.token_str();
    //adjusts blockPos and pos to new values after token input
    _blockPos+= add.length();   //adds length of the new token
    _pos+= add.length();
    return t;
}
//returns private more variable
bool FTokenizer::more(){
    return _more;
} 

//returns private file position variable
int FTokenizer::pos(){
    return _pos;
}

//returns private block position variable
int FTokenizer::block_pos(){
    return _blockPos;
}  

//calls get new block if string tokenizer done, and gets token from next token
FTokenizer& operator >> (FTokenizer& f, Token& t){
    if (f._stk.done()){
        f.get_new_block();  //this also sets more to false if at end of file
    }
    t = f.next_token(); 
    return f;
}

//isnt called often but important to end the ftoken loop
bool FTokenizer::get_new_block(){
    char c;
    char n_block [MAX_BLOCK];
    int i = 0;
    _f.seekg(_pos, _f.end);
    int length = _f.tellg();
    _f.seekg(_pos, _f.beg);
    
    //cout << "Length: " << length << endl;
    //if length is less than 0, then there is nothing left to read
    if (length < 0){
        _more = false;
        return false;
    }

    //creates a block until char limit or end of file
    while ((i < MAX_BLOCK) && (_f.get(c))){
        n_block[i] = c;
        i++;
    }
    cout << "----- New Block ---------------------[" << i-1 << "] bytes\n";
    n_block[i] = '\0';
    _stk.set_string(n_block);
    _blockPos = 0;  //reset blockPos to 0 
    return true;
}    
