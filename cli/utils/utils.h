
#ifndef UTILS_DOT_H_ALREADY_INCLUDED 
#define UTILS_DOT_H_ALREADY_INCLUDED 

#include<string>
using namespace std;

extern string questionsDirectory;
extern string answersDirectory;
extern string subjectsDirectory;

// List prototypes of all functions in utils.cpp here: 
void add_question (void); 
void show_homepage(void);
void get_question(void);

int get_menu(void);

// End include guard: 
#endif