
#ifndef UTILS_DOT_H_ALREADY_INCLUDED 
#define UTILS_DOT_H_ALREADY_INCLUDED 

#include<string>
using namespace std;

extern string questionsDirectory;
extern string answersDirectory;
extern string subjectsDirectory;

typedef struct __Question
{
    string question;
    string answer;
    string subject;
    string timeStamp;
} Question;

// List prototypes of all functions in utils.cpp here: 
void add_question (void);
void remove_question (void);
void show_homepage(void);
void get_question(void);
void open_in_gui(void);
void test_yourself(void);
float calculate_cgpa(void);
void scehdule_notifier(void);
void attendence_quiz_status(void);
string get_current_time_in_HM_format();


Question get_question_from_file(string fileName);

int get_menu(void);

// End include guard: 
#endif