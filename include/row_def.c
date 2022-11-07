#include "./row_def.h"

struct Row *__PARSE_ROW_FROM_STRING__(char *row_string){
struct Row *row = calloc(1,sizeof(struct Row));
char ** columns = 0x00;
size_t length = strlen_runtime(row_string);
size_t current_length = 0x00,current_string_length = 0x00;
char quote_mark = 0x00,comma_mark = 0x00;
char *quote_open = 0x00,*quote_close = 0x00;
char *comma_open = 0x00,*comma_close = 0x00;
char *current_start = 0x00,*current_end = 0x00,*current = 0x00,*current_string = 0x00,*current_string_start = 0x00,*current_string_end = 0x00;

__PARSE_ROW_LOOP_START__:
comma_mark = ',';
current = row_string;
current_start = current;
__PARSE_ROW_LOOP_REPEAT_START__:
current_end = __STRING_INDEX_OF__(current_start,comma_mark);
current_end = current_end ? current_end : (row_string + length);
(quote_mark = 0x00,quote_open = 0x00,quote_close = 0x00);
while(current && current < current_end){
 if((*current) == '\"'){ quote_mark = '\"'; quote_open = current; break; }
 if((*current) == '\''){ quote_mark = '\''; quote_open = current; break; }
 current++;
}
current_end = (row_string + length);
if(quote_open && quote_mark){
 current = quote_open + 1;
 while(current && current < current_end){
  if((*current) == quote_mark){ quote_close = current; break; }
  current++;
 }
}
if(quote_open && quote_close){
 current_string_start = quote_open + 1;
 current_string_end = quote_close - 1;
 current_string_length = current_string_end + 1 - current_string_start;

 current_string = calloc(current_string_length + __STRING_END_NULL_BYTE_SIZE__,sizeof(char));
 memcpy(current_string,current_string_start,current_string_length);

 columns = calloc(row->length + 1,sizeof(char*));
 if(row->columns && row->length) (
  memcpy(columns,row->columns,row->length * sizeof(char*)),
  free(row->columns)
 );
 *((char**)columns + (row->length)) = current_string;
 row->columns = columns;
 row->length = row->length + 1;

 current_start = __STRING_INDEX_OF__(quote_close + 1,comma_mark);
 if(current_start == 0x00) goto __PARSE_ROW_LOOP_END__;
 current = (current_start++);
 goto __PARSE_ROW_LOOP_REPEAT_START__;
} else if(current_start) {
 current_end = __STRING_INDEX_OF__(current_start,comma_mark);
 current_end = current_end ? current_end : row_string + length;
 current_string_start = current_start;
 current_string_end = current_end - 1;
 current_string_length = current_string_end + 1 - current_string_start;

 current_string = calloc(current_string_length + __STRING_END_NULL_BYTE_SIZE__,sizeof(char));
 memcpy(current_string,current_string_start,current_string_length);


 columns = calloc(row->length + 1,sizeof(char*));
 if(row->columns && row->length) (
  memcpy(columns,row->columns,row->length * sizeof(char*)),
  free(row->columns)
 );
 *((char**)columns + (row->length)) = current_string;
 row->columns = columns;
 row->length = row->length + 1;

 current_start = __STRING_INDEX_OF__(current_string_end + 1,comma_mark);
 if(current_start == 0x00) goto __PARSE_ROW_LOOP_END__;
 current = (current_start++);
 goto __PARSE_ROW_LOOP_REPEAT_START__;
}

__PARSE_ROW_LOOP_END__:
return row;
}

