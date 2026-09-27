#include "file_manager.h"
#include "student.h"
#include "marks.h"
#include "attendance.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <direct.h>
#define MKDIR(x) _mkdir(x)
#else
#define MKDIR(x) mkdir(x,0755)
#endif
static const char *SF="data/students.dat",*MF="data/marks.dat",*AF="data/attendance.dat";
static int load_raw(const char*fn,void*out,size_t es,int max){FILE*f=fopen(fn,"rb");if(!f)return 0;int n=0;while(n<max&&fread((char*)out+n*es,es,1,f)==1)n++;fclose(f);return n;}
static int save_raw(const char*fn,const void*in,size_t es,int count){FILE*f=fopen(fn,"wb");if(!f)return 0;int ok=(fwrite(in,es,(size_t)count,f)==(size_t)count);fclose(f);return ok;}
int fm_load_students(Student*o,int m){return load_raw(SF,o,sizeof(Student),m);} int fm_save_students(const Student*o,int c){return save_raw(SF,o,sizeof(Student),c);} int fm_load_marks(Mark*o,int m){return load_raw(MF,o,sizeof(Mark),m);} int fm_save_marks(const Mark*o,int c){return save_raw(MF,o,sizeof(Mark),c);} int fm_load_attendance(Attendance*o,int m){return load_raw(AF,o,sizeof(Attendance),m);} int fm_save_attendance(const Attendance*o,int c){return save_raw(AF,o,sizeof(Attendance),c);} 
int fm_append_student(const Student*s){FILE*f=fopen(SF,"ab");if(!f)return 0;int ok=fwrite(s,sizeof(*s),1,f)==1;fclose(f);return ok;}int fm_append_mark(const Mark*m){FILE*f=fopen(MF,"ab");if(!f)return 0;int ok=fwrite(m,sizeof(*m),1,f)==1;fclose(f);return ok;}int fm_append_attendance(const Attendance*a){FILE*f=fopen(AF,"ab");if(!f)return 0;int ok=fwrite(a,sizeof(*a),1,f)==1;fclose(f);return ok;}
static void seed(void){
    enum { DEMO_STUDENTS = 40, DEMO_SUBJECTS = 8 };
    Student s[DEMO_STUDENTS];
    Mark m[DEMO_STUDENTS * DEMO_SUBJECTS];
    Attendance a[DEMO_STUDENTS * DEMO_SUBJECTS];
    memset(s,0,sizeof(s)); memset(m,0,sizeof(m)); memset(a,0,sizeof(a));
    const char*names[] = {
        "Aarav Sharma","Aditi Verma","Akshat Gupta","Ananya Singh","Arjun Bansal",
        "Avni Kapoor","Devansh Kumar","Diya Patel","Harsh Pandey","Ishita Jain",
        "Kabir Malhotra","Kavya Mishra","Krish Agarwal","Manav Jain","Meera Joshi",
        "Nandini Das","Neel Khanna","Nikhil Singh","Pooja Yadav","Pranav Roy",
        "Rahul Tiwari","Riya Kapoor","Rohan Agarwal","Sakshi Gupta","Samarth Saini",
        "Shivam Sharma","Shreya Mehta","Simran Kaur","Tanmay Saini","Tanya Arora",
        "Utkarsh Verma","Vaishnavi Rao","Vansh Kumar","Varun Chawla","Yash Malhotra",
        "Yuvraj Singh","Zara Khan","Ishaan Kumar","Karan Mehta","Sneha Jain"
    };
    const char*first_names[] = {
        "aarav","aditi","akshat","ananya","arjun","avni","devansh","diya","harsh","ishita",
        "kabir","kavya","krish","manav","meera","nandini","neel","nikhil","pooja","pranav",
        "rahul","riya","rohan","sakshi","samarth","shivam","shreya","simran","tanmay","tanya",
        "utkarsh","vaishnavi","vansh","varun","yash","yuvraj","zara","ishaan","karan","sneha"
    };
    const char*deps[] = {"Computer Science & Engineering","Information Technology","Electronics & Communication","Mechanical Engineering"};
    const char*subs[] = {"Data Structures","Computer Networks","DBMS","Operating Systems","Mathematics","Digital Logic","Computer Organization","Python Programming"};
    int mi=1, ai=1;
    for(int i=0;i<DEMO_STUDENTS;i++){
        s[i].student_id = 26001 + i;
        snprintf(s[i].roll_no,sizeof(s[i].roll_no),"ITS26%03d",i+1);
        safe_copy(s[i].name,sizeof(s[i].name),names[i]);
        snprintf(s[i].email,sizeof(s[i].email),"%s.%s@its.edu.in",first_names[i],(i%2==0)?"student":"btech");
        snprintf(s[i].phone,sizeof(s[i].phone),"98%08d",70124000+i*37);
        safe_copy(s[i].gender,sizeof(s[i].gender),(i%3==0)?"Female":((i%3==1)?"Male":"Other"));
        snprintf(s[i].dob,sizeof(s[i].dob),"2006-%02d-%02d",(i%12)+1,(i%25)+1);
        safe_copy(s[i].department,sizeof(s[i].department),deps[i%4]);
        safe_copy(s[i].course,sizeof(s[i].course),"B.Tech");
        s[i].semester = (i%3)+2;
        snprintf(s[i].section,sizeof(s[i].section),"%c",'A'+(i%3));
        s[i].admission_year = 2025;
        for(int j=0;j<DEMO_SUBJECTS;j++){
            double pct = 48.0 + ((i*9 + j*7 + (i%4)*3) % 45); /* 48..92 */
            if(i==2) pct += (j%2)*5;                    /* strong */
            if(i==7) pct -= (j<3)?12:5;                 /* needs improvement */
            if(i==15 && j==2) pct=33;                   /* failed subject */
            if(i==21) pct = 38 + ((j*4)%8);             /* critical student */
            if(i==30) pct = 84 + ((j*3)%8);             /* high performer */
            if(i==36 && j==5) pct=58;                   /* mixed performance */
            if(pct>96) pct=96;
            if(pct<30) pct=30;
            m[mi-1].id=mi; m[mi-1].student_id=s[i].student_id;
            safe_copy(m[mi-1].subject,sizeof(m[mi-1].subject),subs[j]);
            m[mi-1].max_marks=100;
            m[mi-1].internal_marks=pct*0.20;
            m[mi-1].external_marks=pct*0.65;
            m[mi-1].practical_marks=pct*0.15;
            calculate_mark(&m[mi-1]); mi++;
            a[ai-1].id=ai; a[ai-1].student_id=s[i].student_id;
            safe_copy(a[ai-1].subject,sizeof(a[ai-1].subject),subs[j]);
            a[ai-1].total_classes=38 + ((i+j)%4)*4;
            double attendance = 68.0 + ((i*5 + j*7)%31); /* 68..98 */
            if(i==7) attendance -= 8;
            if(i==21) attendance = 60 + (j%4)*3;
            if(i==31) attendance = 72 + (j%5)*2;
            if(attendance>99) attendance=99;
            a[ai-1].classes_attended=(int)(a[ai-1].total_classes*(attendance/100.0));
            calculate_attendance(&a[ai-1]); ai++;
        }
    }
    fm_save_students(s,DEMO_STUDENTS);
    fm_save_marks(m,mi-1);
    fm_save_attendance(a,ai-1);
}
void fm_init(void){MKDIR("data");MKDIR("reports");FILE*f=fopen(SF,"ab");if(f)fclose(f);f=fopen(MF,"ab");if(f)fclose(f);f=fopen(AF,"ab");if(f)fclose(f);Student s[1];if(fm_load_students(s,1)==0)seed();}
