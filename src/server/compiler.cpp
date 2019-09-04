#include "data_structs.h"

//Initialise and free members of re-entrant parser as well as parse command
struct parseCommand *Compiler::getParams(const char * buffer)
{
    struct parseCommand *expression = (struct parseCommand *)malloc(sizeof(struct parseCommand));
    expression->acc_no = 0;
    expression->amt = 0;
    expression->cmd_type = NONE;
    expression->name = NULL;
    yyscan_t scanner;
    YY_BUFFER_STATE state;

    if (yylex_init(&scanner)) {
        /* could not initialize */
        return NULL;
    }

    state = yy_scan_string(buffer, scanner);

    if (yyparse(expression, scanner)) {
        return NULL;
    }

    yy_delete_buffer(state, scanner);

    yylex_destroy(scanner);

    return expression;
}

//Wrapper to set parser output
int Compiler::parse()
{
    char buff[this->buffer.size() + 1];
    strcpy(buff, this->buffer.c_str());
    this->command = this->getParams((const char *)buff);
    if(this->command == NULL ) {
        return 1;
    }

    return 0;
}