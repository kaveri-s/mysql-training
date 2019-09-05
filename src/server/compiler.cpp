#include "data_structs.h"

//Initialise members of re-entrant parser, parse command and cleanup
struct parseCommand *Compiler::getParams(const char *buffer)
{
    struct parseCommand *expression = (struct parseCommand *)malloc(sizeof(struct parseCommand));

    expression->acc_no = 0;
    expression->amt = 0;
    expression->cmd_type = NONE;
    expression->name = NULL;
    
    yyscan_t scanner;
    YY_BUFFER_STATE state;

    if (yylex_init(&scanner))
    {
        /* could not initialize */
        return NULL;
    }

    state = yy_scan_string(buffer, scanner);

    if (yyparse(expression, scanner))
    {
        return NULL;
    }

    yy_delete_buffer(state, scanner);
    yylex_destroy(scanner);

    return expression;
}

//Wrapper to direct input and output between thread and compiler
int Compiler::parse()
{
    char buff[this->buffer.size() + 1];
    strncpy(buff, this->buffer.c_str(), this->buffer.size());
    buff[this->buffer.size()]='\0';
    command = getParams((const char *)buff);
    
    if (command == NULL)
    {
        return 1;
    }

    return 0;
}