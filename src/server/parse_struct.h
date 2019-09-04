#ifndef __COMPILER_H__
#define __COMPILER_H__

#include <string.h>
#include <iostream>
#include <errno.h>
#include <error.h>

enum cmd_types
{
    ACCOP,
    ACCCL,
    ACCBAL,
    CR,
    DB,
    MINI,
    ALLACC,
    BBAL,
    ACTIVE,
    SHUT,
    NONE
};

struct parseCommand
{
    int acc_no;
    float amt;
    char *name;
    enum cmd_types cmd_type;
};

#endif