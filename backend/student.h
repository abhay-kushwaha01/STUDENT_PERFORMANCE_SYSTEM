#ifndef STUDENT_H
#include <stddef.h>
#define STUDENT_H
#define MAX_STUDENTS 500
#define MAX_NAME 100
#define MAX_FIELD 64
typedef struct { int student_id; char roll_no[30]; char name[MAX_NAME]; char email[100]; char phone[20]; char gender[16]; char dob[16]; char department[50]; char course[60]; int semester; char section[10]; int admission_year; } Student;
int student_exists_id(int id); int student_exists_roll(const char *roll,int except_id);
int student_add_from_json(const char *json,char *message,size_t msgsz);
int student_update_from_json(const char *json,char *message,size_t msgsz);
int student_delete(int id,char *message,size_t msgsz);
int student_get(int id,Student *out); int student_list_json(char *out,size_t outsz,const char *query);
#endif
