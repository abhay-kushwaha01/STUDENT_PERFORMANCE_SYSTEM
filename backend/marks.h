#ifndef MARKS_H
#include <stddef.h>
#define MARKS_H
#define MAX_MARKS 3000
typedef struct { int id; int student_id; char subject[80]; double internal_marks; double external_marks; double practical_marks; double total_marks; double max_marks; double percentage; char grade[4]; } Mark;
void calculate_mark(Mark *m); int mark_add_from_json(const char *json,char *msg,size_t sz); int mark_update_from_json(const char*json,char*msg,size_t sz); int mark_delete(int id,char*msg,size_t sz); int marks_json(char*out,size_t sz,int student_id);
#endif
