#include <iostream>
#include <ctime>
#include<fstream>
#include<string.h>
#include <filesystem>
#include<vector>
#include "colors.h"

namespace fs = std::filesystem;
using namespace std;

char questionDBPath[] = "questions.txt";
string questionsDirectory = "data/questions";
string answersDirectory = "data/answers";
string subjectsDirectory = "data/subjects";

typedef struct __Question
{
    string question;
    string answer;
    string subject;
    time_t timeStamp;
} Question;


void show_homepage()
{
    cout << CYAN_COLOR << " _______  _______  _______ _________ _______  _______  _______  _        _______  _______ \n"
         << "(  ____ \\(  ____ \\(       )\\__   __/(  ____ )(  ___  )(  ____ \\| \\    /\\(  ____ \\(  ____ )\n"
         << "| (    \\/| (    \\/| () () |   ) (   | (    )|| (   ) || (    \\/|  \\  / /| (    \\/| (    )|\n"
         << "| (_____ | (__    | || || |   | |   | (____)|| (___) || |      |  (_/ / | (__    | (____)|\n"
         << "(_____  )|  __)   | |(_)| |   | |   |     __)|  ___  || |      |   _ (  |  __)   |     __)\n"
         << "      ) || (      | |   | |   | |   | (\\ (   | (   ) || |      |  ( \\ \\ | (      | (\\ (   \n"
         << "/\\____) || (____/\\| )   ( |   | |   | ) \\ \\__| )   ( || (____/\\|  /  \\ \\| (____/\\| ) \\ \\__\n"
         << "\\_______)(_______/|/     \\|   )_(   |/   \\__/|/     \\|(_______/|_/    \\/(_______/|/   \\__/\n"
         << "                                                                                          \n"
         << WHITE_COLOR
         << endl;

    cout << "\nsemTracker is a CLI tool for studying that helps you memorize questions and track your progress. You can then put your memory to the test. Track your attendence. Lackings and Quiz marks. \n\n"
         << endl;
}

int get_menu()
{
    int option;
    cout << "Choose what do you want to do?\n"
         << endl;
    cout << " 1. Add a question." << endl;
    cout << " 2. Test yourself." << endl;
    cout << " 3. Score board." << endl;
    cout << " 4. View questions." << endl;
    cout << " 5. Add attendence." << endl;
    cout << " 6. Add quiz marks." << endl;
    cout << " 7. Check statistics." << endl;
    cout << " 8. Open app on GUI." << endl;
    cout << " 99. Exit." << endl;
    cout << " > ";
    cin >> option;
    return option;
}


void add_question()
{
    cout << CYAN_COLOR << "Add a Question" << WHITE_COLOR << endl;
    cout << YELLOW_COLOR << "Note: Questions and answers support multiline input. So Write [END] to end question/answer" << WHITE_COLOR << endl;
    // Open a file from certain directory (/home/shakib/Dev/build-semTracker-Desktop-Debug/questions.bin)
    
    // TimeStamp
    time_t timeStamp = time(NULL);
    string currentTime = ctime(&timeStamp);
    currentTime.erase(currentTime.length() - 1);
    string fileName = currentTime + ".txt";

    ofstream qfile(questionsDirectory + "/" + fileName, ios::app);
    ofstream afile(answersDirectory + "/" + fileName, ios::app);
    ofstream sfile(subjectsDirectory + "/" + fileName, ios::app);
    
    if (!qfile.is_open())
    {
        cout << RED_COLOR << "Error: Could not open the file." << WHITE_COLOR << endl;
        return;
    }

    cout << "question: ";

    string input = "";
    // Question
    while (input != "[END]")
    {
        getline(cin, input);

        if (input == "[END]")
            break;
        
        qfile << input << "\n";
    }
    // Answer
    cout << "answer: ";
    
    input = "";

    while (input != "[END]")
    {
        getline(cin, input);
        
        if (input == "[END]")
            break;

        afile << input << "\n";
    }
    // Subject
    cout << "subject: ";
    
    getline(cin, input);
    sfile << input << "\n";

    cout << GREEN_COLOR << "Question added successfully." << WHITE_COLOR << endl;

    qfile.close();
    afile.close();
    sfile.close();
}

void get_question()
{
    vector<string> fileNames;

    for (const auto& entry : fs::directory_iterator(questionsDirectory)) {
            if (entry.is_regular_file()) {
                fileNames.push_back(entry.path().filename());
            }
        }

    // if (file == NULL)
    // {
    //     cout << RED_COLOR << "Error: Could not open the file." << WHITE_COLOR << endl;
    //     return;
    // }
    // //Read all the Questions from the file
    // while (getline())
    // {
    //     printf("%s\n", question.question);
    //     printf("%s\n", question.answer);
    // }
    
    // fclose(file);
}
