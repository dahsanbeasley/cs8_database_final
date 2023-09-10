#ifndef FILE_RECORD_H
#define FILE_RECORD_H

#include <iostream>
#include <iomanip>
#include <string.h>
#include <vector>
#include "utilities.h"

using namespace std;

struct FileRecord{
    //when you construct a FileRecord, it's either empty or it
    //  contains a word
    FileRecord(){
        _record[0][0] = '\0';
        recno = -1;
        //['\0'|  | G | a | r | b | a   |  g  |  e |    ]
    }

    FileRecord(char str[]){
        strncpy(_record[0], str, MAX);
        _record[1][0] = '\0';
    }
    
    FileRecord(string s){
        strncpy(_record[0], s.c_str(), MAX);
        _record[1][0] = '\0';
    }

    FileRecord(vector<string> s){
        int i = 0;
        for(; i < s.size(); i++){
            strncpy(_record[i], s[i].c_str(), MAX);
        }
        _record[i][0] = '\0';
        
    }

    long write(fstream& outs);              //returns the record number
    long read(fstream& ins, long recno);    //returns the number of bytes
                                            //      read = MAX, or zero if
                                            //      read passed the end of file


    friend ostream& operator<<(ostream& outs, const FileRecord& r);

    static const int MAX = 100;
    int recno;
    char _record[MAX+1][MAX+1];
};

#endif