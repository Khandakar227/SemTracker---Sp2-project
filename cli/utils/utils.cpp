#include <iostream>
#include <ctime>
#include <fstream>
#include <string.h>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <random>
#include "colors.h"

namespace fs = std::filesystem;
using namespace std;

string questionsDirectory = "data/questions";
string answersDirectory = "data/answers";
string subjectsDirectory = "data/subjects";

typedef struct __Question
{
    string question;
    string answer;
    string subject;
    string timeStamp;
    int status;
} Question;

Question get_question_from_file(string fileName)
{
    string qPath = questionsDirectory + "/" + fileName;
    string aPath = answersDirectory + "/" + fileName;
    string sPath = subjectsDirectory + "/" + fileName;

    Question question;
    question.question = "";
    question.answer = "";
    ifstream qfile(qPath);
    ifstream afile(aPath);
    ifstream sfile(sPath);

    string output;

    while (!qfile.eof())
    {
        getline(qfile, output);
        question.question.append(output + "\n");
    }

    output = "";
    while (!afile.eof())
    {
        getline(afile, output);
        question.answer.append(output + "\n");
    }

    output = "";
    while (!sfile.eof())
    {
        getline(sfile, output);
        question.subject.append(output + "\n");
    }

    question.timeStamp = fileName.substr(0, fileName.length() - 4);

    qfile.close();
    afile.close();
    sfile.close();

    return question;
}

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

    string input;
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

    cout << endl;
    cout << GREEN_COLOR << "Question added successfully." << WHITE_COLOR << endl;
    cout << endl;

    qfile.close();
    afile.close();
    sfile.close();
}

void get_question()
{
    vector<string> fileNames;
    long long questionCount = 0;
    for (const auto &entry : fs::directory_iterator(questionsDirectory))
    {
        if (entry.is_regular_file())
        {
            Question question = get_question_from_file(entry.path().filename().string());
            cout << ++questionCount << ". " << endl;
            cout << GREEN_COLOR << "Question: " << DEFAULT_COLOR << question.question;
            cout << GREEN_COLOR << "Answer: " << DEFAULT_COLOR << question.answer;
            cout << GREEN_COLOR << "Subject: " << DEFAULT_COLOR << question.subject;
            cout << GREEN_COLOR << "Created at: " << DEFAULT_COLOR << question.timeStamp;
            cout << endl;
            cout << endl;
        }
    }
}

void open_in_gui()
{
    system("/home/shakib/Dev/semTracker/build-semTracker-gui-Desktop-Debug/semTracker-gui");
}

void test_yourself(void)
{
    cout << CYAN_COLOR << "Test your memory" << DEFAULT_COLOR << endl;

    vector<string> fileNames;
    for (const auto &entry : fs::directory_iterator(questionsDirectory))
    {
        if (entry.is_regular_file())
        {
            fileNames.push_back(entry.path().filename());
        }
    }

    random_device rd;
    mt19937 generator(rd());
    shuffle(fileNames.begin(), fileNames.end(), generator);
}