// #include "parser.tab.hh"
#include "controller.hpp"

using namespace std;


int main()
{
    cout << "Hi\n";
    yyin = fopen("../test/lex", "r");
    yyparse();
    cout << "Bye\n";
}