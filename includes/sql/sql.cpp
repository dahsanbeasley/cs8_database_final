#include "sql.h"

SQL::SQL(){
    fstream f;
    int i = 0;
    open_fileRW(f, "table_names.txt");
    long bytes = access.read(f, i);
    while (bytes>0){
        table_names.push_back(access._record[i]);
        i++;
        bytes = access.read(f, i);
    }
    f.close();
}

SQL::SQL(string filename){
    fstream f;
    int i = 0;
    open_fileRW(f, "table_names.txt");
    long bytes = access.read(f, i);
    while (bytes>0){
        table_names.push_back(access._record[i]);
        i++;
        bytes = access.read(f, i);
    }
    f.close();

    ifstream batch(filename);
    int query = 0;
    string temp;
    while(getline(batch, temp)){
        //cout << temp << endl;
        if(temp[0] == '/'|| temp.size() == 0){
            cout << temp << endl;
        }
        else if(temp.size() != 0){
            cout << "[" << query << "] " << temp << endl; 
            cout << command(temp) << endl;
            query++;
        }
    }
    batch.close();
}

SQL::~SQL(){

}

SQL::SQL(const SQL& copyMe){
    c_parser = copyMe.c_parser;
    ptree = copyMe.ptree;
    table_names = copyMe.table_names;
    recnos = copyMe.recnos;
}

SQL& SQL::operator=(const SQL& rhs){
    c_parser = rhs.c_parser;
    ptree = rhs.ptree;
    table_names = rhs.table_names;
    recnos = rhs.recnos;
}

Table SQL::command(string str){ 
    c_parser.set_string(str);
    ptree = c_parser.parse_tree();
    
    string cmd = ptree["command"][0];
    if(cmd.compare("make") == 0){
        return make();
    }
    if(cmd.compare("insert") == 0){
        return insert();
    }
    if(cmd.compare("select") == 0){
        return select();
    }
    else{
        return Table();
    }
}

vector<long> SQL::select_recnos(){
    return recnos;
}

Table SQL::make(){
    vectorstr fields = ptree["col"];
    table_names.push_back(ptree["table_name"][0]);
    return Table(ptree["table_name"][0], fields);
}

Table SQL::insert(){
    Table t(ptree["table_name"][0]);
    t.insert_into(ptree["values"]);
    return t;
}

Table SQL::select(){
    Table t(ptree["table_name"][0]);
    if (ptree.contains("where")){
        cout << "Case 1: \n";
        vectorstr cond = ptree["condition"];
        Table selected = t.select(ptree["fields"], cond);
        recnos = t.select_recnos();
        return selected;

    }
    else if(ptree["fields"][0] == "*" || ptree["fields"][0] == "star"){
        cout << "Case 2: \n";
        Table selected =  t.select_all();
        recnos = t.select_recnos();
        return selected;
    }
    else {
        cout << "Case 3: \n";
        Table selected = t.select_all(ptree["fields"]);
        recnos = t.select_recnos();
        return selected;
    }

}