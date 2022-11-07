#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../dependencies/string-number/include/string_function.h"
#include "../dependencies/string-number/include/string_def.h"

#ifndef __CUSTOM_ROW_DEF_H__
#define __CUSTOM_ROW_DEF_H__

typedef char* RowString;
typedef char* ColumnString;
typedef struct Row {
 char **columns;
 size_t length;
} Row;

struct Row *__PARSE_ROW_FROM_STRING__(char *row_string);

#endif