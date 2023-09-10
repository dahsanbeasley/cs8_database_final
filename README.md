
# Work Report

## Name: <ins> Dahsan Beasley </ins>

## Features:

- Not Implemented:
  - what features have been implemented

<br><br>

- Implemented:
  - SQL Class

<br><br>

- Partly implemented:
  - what features have not been implemented

<br><br>

- Bugs
  - Known bugs

<br><br>

# Reflections:

- Got weird redeclaration errors with Queue's friend operators on itself

# **output**
<pre>
<br/><br/><br/><br/>
## Delete this line and paste the output of your basic test and then testB here
</pre>


<br/><br/>

# basic_test.cpp output:
<pre>
<br/><br/><br/><br/>
----------running basic_test.cpp---------


[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from SQL_BASIC
[ RUN      ] SQL_BASIC.SQLBasic
>make table employee fields  last,       first,         dep,      salary, year
basic_test: table created.

>make table employee fields  last,       first,         dep,      salary, year
>insert into employee values Blow,       Joe,           CS,       100000, 2018
>insert into employee values Blow,       JoAnn,         Physics,  200000, 2016
>insert into employee values Johnson,    Jack,          HR,       150000, 2014
>insert into employee values Johnson,    "Jimmy",     Chemistry,140000, 2018
>make table student fields  fname,          lname,    major,    age
>insert into student values Flo,            Yao,        Art,    20
>insert into student values Bo,                      Yang,      CS,             28
>insert into student values "Sammuel L.", Jackson,      CS,             40
>insert into student values "Billy",         Jackson,   Math,   27
>insert into student values "Mary Ann",   Davis,        Math,   30



>select * from employee

Table name: employee_13, records: 4
                   record                     last                    first                      dep                   salary                     year

                        0                     Blow                      Joe                       CS                   100000                     2018
                        1                     Blow                    JoAnn                  Physics                   200000                     2016
                        2                  Johnson                     Jack                       HR                   150000                     2014
                        3                  Johnson                    Jimmy                Chemistry                   140000                     2018


basic_test: records selected: [0 1 2 3 ]

>select last, first, age from employee

Table name: employee_16, records: 4
                   record                     last                    first                      age

                        0                     2018                      Joe
                        1                     2016                    JoAnn
                        2                     2014                     Jack
                        3                     2018                    Jimmy


basic_test: records selected: [0 1 2 3 ]

>select last from employee

Table name: employee_19, records: 4
                   record                     last

                        0                     2018
                        1                     2016
                        2                     2014
                        3                     2018


basic_test: records selected: [0 1 2 3 ]

>select * from employee where last = Johnson

Table name: _select_table_22, records: 2
                   record                     last                    first                      dep                   salary                     year

                        0                  Johnson                     Jack                       HR                   150000                     2014
                        1                  Johnson                    Jimmy                Chemistry                   140000                     2018


basic_test: records selected: [2 3 ]

>select * from employee where last=Blow and major="JoAnn"

Table name: _select_table_25, records: 0
                   record                     last                    first                      dep                   salary                     year



basic_test: records selected: []

>select * from student

Table name: student_28, records: 5
                   record                    fname                    lname                    major                      age

                        0                      Flo                      Yao                      Art                       20
                        1                       Bo                     Yang                       CS                       28
                        2              Sammuel L .                  Jackson                       CS                       40
                        3                    Billy                  Jackson                     Math                       27
                        4                 Mary Ann                    Davis                     Math                       30


basic_test: records selected: [0 1 2 3 4 ]

>select * from student where (major=CS or major=Art)

Table name: _select_table_31, records: 3
                   record                    fname                    lname                    major                      age

                        0                      Flo                      Yao                      Art                       20
                        1                       Bo                     Yang                       CS                       28
                        2              Sammuel L .                  Jackson                       CS                       40


basic_test: records selected: [0 1 2 ]

>select * from student where lname>J

Table name: _select_table_34, records: 4
                   record                    fname                    lname                    major                      age

                        0              Sammuel L .                  Jackson                       CS                       40
                        1                    Billy                  Jackson                     Math                       27
                        2                       Bo                     Yang                       CS                       28


basic_test: records selected: [2 3 1 0 ]

>select * from student where lname>J and (major=CS or major=Art)

Table name: _select_table_37, records: 3
                   record                    fname                    lname                    major                      age

                        0                      Flo                      Yao                      Art                       20
                        1                       Bo                     Yang                       CS                       28
                        2              Sammuel L .                  Jackson                       CS                       40


basic_test: records selected: [0 1 2 ]
----- END TEST --------
[       OK ] SQL_BASIC.SQLBasic (256 ms)
[----------] 1 test from SQL_BASIC (257 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (257 ms total)
[  PASSED  ] 1 test.
</pre>
# testB.cpp output:
<pre>
<br/><br/><br/><br/>
----------running testB.cpp---------


[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from SQL_BASIC
[ RUN      ] SQL_BASIC.SmallFuncs

Table name: student, records: 7
                   record                    fname                    lname                      age

                        0                      Joe                    Gomez                       20
                        1                    Karen                   Orozco                       21
                        2                      Flo                      Yao                       29
                        3                     Jack                      Yao                       19
                        4                      Flo                  Jackson                       20
                        5                      Flo                    Gomez                       20
                        6                    Karen                  Jackson                       15


Existing Table Test


here is the student table:
Table name: student, records: 7
                   record                    fname                    lname                      age

                        0                      Joe                    Gomez                       20
                        1                    Karen                   Orozco                       21
                        2                      Flo                      Yao                       29
                        3                     Jack                      Yao                       19
                        4                      Flo                  Jackson                       20
                        5                      Flo                    Gomez                       20
                        6                    Karen                  Jackson                       15



Select all filtered test:

Table name: student_2, records: 7
                   record                     last                      age

                        0                    Gomez                       20
                        1                   Orozco                       21
                        2                      Yao                       29
                        3                      Yao                       19
                        4                  Jackson                       20
                        5                    Gomez                       20
                        6                  Jackson                       15


[       OK ] SQL_BASIC.SmallFuncs (109 ms)
[----------] 1 test from SQL_BASIC (110 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (111 ms total)
[  PASSED  ] 1 test.
</pre>


