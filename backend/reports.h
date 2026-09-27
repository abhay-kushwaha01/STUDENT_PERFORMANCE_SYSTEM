#ifndef REPORTS_H
#include <stddef.h>
#define REPORTS_H
int report_student(int student_id,char*filename,size_t fsz);
int report_class(char*filename,size_t fsz);
int report_subject(const char*subject,char*filename,size_t fsz);
#endif
