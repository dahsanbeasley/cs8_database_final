#include "table.h"

//serial num used to build select tables
int serial_num = 0;

Table::Table(){
    
}

Table::Table(const string name, vectorstr s){
    fstream f;
    filename = name;
    field_names = s;
    table_num = 0;
    empty = true;
    last_recno = 0;

    FileRecord record;
    string temp = name + ".bin"; 
    open_fileW(f, temp.c_str());
    f.close();
    temp = name + "_fields.txt";
    open_fileW(f, temp.c_str());
    record = FileRecord(s);
    record.write(f);
    f.close();
    set_fields(field_names);
    serial_num++;
}

Table::Table(const string name){
    fstream f;
    filename = name;
    table_num = 0;
    last_recno = 0;
    string inp;

    string temp = name+"_fields.txt";
    open_fileRW(f, temp.c_str());
    records.read(f, 0);
    for (int i = 0; records._record[i][0] != '\0'; i++){
        field_names.push_back(records._record[i]);
    }
    set_fields(field_names);
    f.close();
    temp = filename+".bin";
    open_fileRW(f, temp.c_str());
    records.read(f, 0);
    for (long i = 0; records._record[0][0] != '\0'; i++){
        for (long j = 0; records._record[j][0] != '\0'; j++){
            inp = records._record[j];
            index[field_names[j]][inp] += i;
        }
        table_num++;
        records.read(f, i+1);
    }
    serial_num++;
}

void Table::insert_into(vectorstr s){
    fstream f;
    string temp = filename+".bin";
    open_fileRW(f, temp.c_str());
    records = FileRecord(s);
    last_recno = records.write(f);
    for (int i = 0; i < s.size(); i++){
        index[field_names[i]][s[i]] += last_recno;
    }
    table_num++;
    
}

Table Table::select(vectorstr fields, 
        const char f_cond[], const char s_cond[], const char t_cond[]){
    string temp = "_select_table_" + to_string(serial_num);
    Table s_t(temp, fields);
    temp = f_cond;
    if (index.contains(temp)){
        string temp2 = t_cond;
        vector<long> recnos;
        if (index[temp].contains(temp2)){
            mmap_sl::Iterator first;
            mmap_sl::Iterator second;
            if (!strcmp(s_cond, "=")){
                first = index[temp].lower_bound(temp2);
                second = index[temp].upper_bound(temp2);
            }
            else if (!strcmp(s_cond, ">")){
                first = index[temp].upper_bound(temp2);
                second = index[temp].end();
            }
            else if (!strcmp(s_cond, "<")){
                first = index[temp].begin();
                second = index[temp].lower_bound(temp2);
            }
            else if (!strcmp(s_cond, "<=")){
                first = index[temp].begin();
                second = index[temp].upper_bound(temp2);
            }
            else if (!strcmp(s_cond, ">=")){
                first = index[temp].lower_bound(temp2);
                second = index[temp].end();
            } 
            else return s_t;
            for (; first != second; first++){
                MPair<string, long> temp3 = *first;
                for (int i = 0; i < temp3.value_list.size(); i++){
                    recnos.push_back(temp3.value_list[i]);
                }
            }
            select_recs = recnos;
            fstream f;
            vectorstr inp;
            temp = filename +".bin";
            open_fileRW(f, temp.c_str());
            for (int i = 0; i < recnos.size(); i++){
                records.read(f, recnos[i]);
                inp.resize(s_t.field_names.size());
                for (long j = 0; records._record[j][0] != '\0'; j++){
                    if (s_t.names.contains(field_names[j]))
                        inp[s_t.names[field_names[j]]] = (records._record[j]);
                }
                s_t.insert_into(inp);
                inp.clear();
            }
            f.close();
        }
    }
    serial_num++;
    return s_t;
}

Table Table::select(vectorstr fields, Queue<Token*> cond){
    string temp = "_select_table_" + to_string(serial_num);
    Table s_t(temp, fields);
    RPN nums(cond);
    select_recs = nums.eval(index);
    fstream f;
    vectorstr inp;
    temp = filename +".bin";
    open_fileRW(f, temp.c_str());
    for (int i = 0; i < select_recs.size(); i++){
        records.read(f, select_recs[i]);
        inp.resize(s_t.field_names.size());
        for (long j = 0; records._record[j][0] != '\0'; j++){
            if (s_t.names.contains(field_names[j]))
                inp[s_t.names[field_names[j]]] = (records._record[j]);
        }
        s_t.insert_into(inp);
        inp.clear();
    }
    f.close();
    serial_num++;
    return s_t;
}

Table Table::select(vectorstr fields, vectorstr cond){
    Queue<Token*> post;
    ShuntingYard shunt(cond);
    post = shunt.convert();
    if (fields[0] == "*"|| fields[0] == "star"){
        return select(field_names, post);
    }
    return select(fields, post);
}

vectorlong Table::select_recnos(){
    return select_recs;
}


Table Table::select_all(){
    string temp = "_select_table_" + to_string(serial_num);
    Table t_all(temp, field_names);
    fstream f;
    vectorstr inp;
    temp = filename +".bin";
    open_fileRW(f, temp.c_str());
    int i = 0;
    vectorlong recnos;
    t_all.records.read(f, 0);
    while (!f.eof()){
        t_all.records.read(f, i);
        inp.resize(field_names.size());
        for (long j = 0; t_all.records._record[j][0] != '\0'; j++){
            inp[t_all.names[field_names[j]]] = (t_all.records._record[j]);
        }
        t_all.insert_into(inp);
        inp.clear();
        recnos.push_back(i);
        i++;
        t_all.records.read(f, i);
    }
    f.close();
    select_recs = recnos;
    serial_num++;
    return t_all;
}

Table Table::select_all(vectorstr fields){
    string temp = "_select_table_" + to_string(serial_num);
    Table t_all(temp, fields);
    fstream f;
    vectorstr inp;
    temp = filename +".bin";
    open_fileRW(f, temp.c_str());
    int i = 0;
    vectorlong recnos;
    t_all.records.read(f, 0);
    while (!f.eof()){
        inp.resize(t_all.field_names.size());
        for (long j = 0; t_all.records._record[j][0] != '\0'; j++){
            //cout << t_all.names[field_names[j]] << ": " << field_names[j] << endl;
            if(t_all.names.contains(field_names[j]))
                inp[t_all.names[field_names[j]]] = (t_all.records._record[j]);
        }
        t_all.insert_into(inp);
        //cout << inp << endl;
        inp.clear();
        recnos.push_back(i);
        i++;
        t_all.records.read(f, i);
    }
    f.close();
    select_recs = recnos;
    serial_num++;
    return t_all;
}

ostream& operator<<(ostream& outs, const Table& print_me){
        outs << "\nTable name: " << print_me.filename 
            << ", records: " << print_me.table_num << endl;
        outs << setw(25) << "record";
        fstream f;
        string temp = print_me.filename + "_fields.txt";
        FileRecord r;
        open_fileRW(f, temp.c_str());
        r.read(f, 0);
        outs << r << endl << endl;
        f.close();
        temp = print_me.filename+".bin";
        open_fileRW(f, temp.c_str());
        for (long i = 0; i < print_me.table_num; i++){
            r.read(f, i);
            outs << setw(25) << i << r << endl;
            
        }
        outs << endl;
        f.close();
        return outs;
    }

void Table::set_fields(vectorstr s){
    for (long i = 0; i < s.size(); i++){
        names.insert(s[i], i);
        index.insert(s[i], mmap_sl());
    }
}

vectorstr Table::get_fields(){
    return field_names;
}

