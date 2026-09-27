#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H
#include <stddef.h>
#include <stdio.h>
#include "student.h"
#include "marks.h"
#include "attendance.h"
void fm_init(void);
int fm_load_students(Student *out, int max);
int fm_save_students(const Student *items, int count);
int fm_load_marks(Mark *out, int max);
int fm_save_marks(const Mark *items, int count);
int fm_load_attendance(Attendance *out, int max);
int fm_save_attendance(const Attendance *items, int count);
int fm_append_student(const Student *s);
int fm_append_mark(const Mark *m);
int fm_append_attendance(const Attendance *a);
#endif
