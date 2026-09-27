#ifndef ATTENDANCE_H
#include <stddef.h>
#define ATTENDANCE_H
#define MAX_ATTENDANCE 3000
typedef struct { int id; int student_id; char subject[80]; int total_classes; int classes_attended; int classes_absent; double percentage; } Attendance;
void calculate_attendance(Attendance *a); int attendance_add_from_json(const char*json,char*msg,size_t sz); int attendance_update_from_json(const char*json,char*msg,size_t sz); int attendance_delete(int id,char*msg,size_t sz); int attendance_json(char*out,size_t sz,int student_id);
#endif
