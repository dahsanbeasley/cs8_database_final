#include "gtest/gtest.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>

//------------------------------------------------------------------------------------------
//Files we are testing:
#include "../../includes/sql/sql.h"


//------------------------------------------------------------------------------------------

using namespace std;

bool small_funcs(bool debug = false)
{
  vectorstr fields={"fname", "lname", "age"};
  Table t("student", fields);
  vectorstr row;
  row = {"Joe", "Gomez", "20"};
  t.insert_into(row);
  row = {"Karen", "Orozco", "21"};
  t.insert_into(row);
  row = {"Flo", "Yao", "29"};
  t.insert_into(row);
  row = {"Jack", "Yao", "19"};
  t.insert_into(row);
  row = {"Flo", "Jackson", "20"};
  t.insert_into(row);
  row = {"Flo", "Gomez", "20"};
  t.insert_into(row);
  row = {"Karen", "Jackson", "15"};
  t.insert_into(row);
  cout << t << endl;
  cout << "Existing Table Test\n";
  Table tbl_student("student");
  cout << "\n\nhere is the student table: " << tbl_student << endl;
  cout <<"\nSelect all filtered test:\n" << tbl_student.select_all({"last", "age"}) << endl;
  return true;
}

bool sql_batch(bool debug = false)
{
  SQL sql("_!select.txt");
  return true;
}

TEST(SQL_BASIC, SmallFuncs) {
  bool success = small_funcs();
  EXPECT_EQ(success, true);
}

TEST(SQL_BASIC, SQLBatch) {
  bool success = sql_batch();
  EXPECT_EQ(success, true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

