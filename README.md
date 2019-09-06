# MySQL Training

This client-server applicaton was created as part of a practice test

## Dependecies
This code requires:
* readline C library
* make
* valgrind
* python3

## Folder Structure

The folder structure is as follows

```bash
.
├── README.md
├── src
│   ├── client
│   │   ├── client.cpp
│   │   ├── client.h
│   │   ├── client.h.gch
│   │   ├── Makefile
│   │   └── readline.supp
│   └── server
│       ├── account.cpp
│       ├── bank.cpp
│       ├── bank.h
│       ├── compiler.cpp
│       ├── connection.cpp
│       ├── data_structs.h
│       ├── lexer.l
│       ├── Makefile
│       ├── parser.y
│       ├── parse_struct.h
│       ├── server.cpp
│       └── thread.cpp
├── test
│   ├── lex
│   ├── loadtest.py
│   ├── testalldataop.txt
│   └── testgen.py
└── valgrind
    ├── callgrind
    ├── massif
    └── memcheck

```

### Server Files:
There are 3 header files:
* data_struct : Has declarations of classes Compiler, Thread and ConnectionManager as well as connection configuration macros
* parse_struct : Has declarations of structure shared by Compiler(Class), lexer and parser
* bank.h :  Has declarations of Bank and Account classes

There are 6 .cpp files:
* server.cpp : The entry point containing main and signal handler definition
* connection.cpp : definitions of member functions of ConnectionManager class
* thread.cpp : definitions of member functions of Thread class
* compiler.cpp : definitions of member functions of Compiler class
* bank.cpp : definitions of member functions of Bank class
* account.cpp : definitions of member functions of Account class

## Setup
To run the server, in the src/server folder run:
```bash
make
./server
```

To run the client, in a separate terminal in the src/client folder run:
```bash
make
./client
```

## Test
To run a load test, start the server and in a new terminal, in test folder run:
```bash
python3 loadtest.py
```

To check all edge cases on one client, in src/client folder run:
```bash
./client < ../../test/testalldataop.txt
```

To generate 1000 test cases and get a file run:
```bash
testgen.py > <out_file_name>
```
Can be used to generate many such files which are bound to have some common account number to check for concurrency

