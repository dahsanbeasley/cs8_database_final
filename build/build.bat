g++ -std=gnu++11 -o main       ../main.cpp                          ../includes/token/token.cpp ../includes/tokenizer/state_machine_functions.cpp ../includes/tokenizer/stokenize.cpp ../includes/tokenizer/ftokenize.cpp -Igoogletest/googletest/include -pthread -Lgoogletest/build/lib -lgtest
g++ -std=gnu++11 -o basic_test ../_tests/_test_files/basic_test.cpp ../includes/token/token.cpp ../includes/tokenizer/state_machine_functions.cpp ../includes/token/child_tokens.cpp ../includes/tokenizer/stokenize.cpp ../includes/binary_files/utilities.cpp ../includes/binary_files/file_record.cpp ../includes/table/table.cpp ../includes/shunting_yard/shunting_yard.cpp ../includes/rpn/rpn.cpp ../includes/parser/parser.cpp ../includes/sql/sql.cpp -Igoogletest/googletest/include -pthread -Lgoogletest/build/lib -lgtest
g++ -std=gnu++11 -o testB      ../_tests/_test_files/testB.cpp      ../includes/token/token.cpp ../includes/tokenizer/state_machine_functions.cpp ../includes/token/child_tokens.cpp ../includes/tokenizer/stokenize.cpp ../includes/binary_files/utilities.cpp ../includes/binary_files/file_record.cpp ../includes/table/table.cpp ../includes/shunting_yard/shunting_yard.cpp ../includes/rpn/rpn.cpp ../includes/parser/parser.cpp ../includes/sql/sql.cpp -Igoogletest/googletest/include -pthread -Lgoogletest/build/lib -lgtest



