#ifndef SQL_H
#define SQL_H

#include "../../includes/table/table.h"
#include "../../includes/parser/parser.h"

class SQL
{
public:
    SQL();
    SQL(string filename);
    
    ~SQL();
    SQL(const SQL& copyMe);
    SQL& operator=(const SQL& rhs);

    Table command(string str);
    vector<long> select_recnos();
private:
    FileRecord access;
    Parser c_parser;
    mmap_ss ptree;
    vectorstr table_names;
    vectorlong recnos;

    Table make();
    Table insert();
    Table select();
};

#endif