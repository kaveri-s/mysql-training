<<<<<<< HEAD
// #include "parser.tab.hh"
#include "controller.hpp"

using namespace std;


int main()
{
    cout << "Hi\n";
    yyin = fopen("../test/lex", "r");
    yyparse();
    cout << "Bye\n";
=======
#include <iostream>
#include <cstring>
#include <cstdlib>
#include "y.tab.h"
#include "parser.h"

using namespace std;

int main()
{
    parse();
    return 0;
>>>>>>> 43d06b8a21b7adf1d22008a70f5bc894bc3a7793
}