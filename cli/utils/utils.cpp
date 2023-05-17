#include <iostream>
#include <ctime>
#include "colors.h"

using namespace std;

char questionDBPath[] = "questions.bin";

typedef struct __Question
{
    string question;
    string answer;
    string subject;
    time_t timeStamp;
} Question;

void add_question()
{
    cout << CYAN_COLOR << "Add a Question" << WHITE_COLOR << endl;
    cout << YELLOW_COLOR << "Note: Questions and answers support multiline input. So Write [END] to end question/answer" << WHITE_COLOR << endl;
    // Open a file from certain directory (/home/shakib/Dev/build-semTracker-Desktop-Debug/questions.db)
    FILE *file = fopen(questionDBPath, "ab");

    if (file == NULL)
    {
        cout << RED_COLOR << "Error: Could not open the file." << WHITE_COLOR << endl;
        return;
    }
    Question question;

    cout << "question: ";

    string input = "";
    // Question
    while (input != "[END]")
    {
        cin >> input;
        if (input == "[END]")
            break;
        question.question.append("\n");
        question.question.append(input);
    }
    // Answer
    cout << "answer: ";
    input = "";

    while (input != "[END]")
    {
        cin >> input;
        if (input == "[END]")
            break;
        question.answer.append("\n");
        question.answer.append(input);
    }
    // Subject
    cout << "subject: ";
    cin >> question.subject;
    // TimeStamp
    question.timeStamp = time(NULL);
    // Write the question to the file
    fwrite(&question, sizeof(question), 1, file);

    cout << GREEN_COLOR << "Question added successfully." << WHITE_COLOR << endl;

    fclose(file);
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

void get_question()
{
    FILE *file;
    file = fopen(questionDBPath, "rb");

    if (file == NULL)
    {
        cout << RED_COLOR << "Error: Could not open the file." << WHITE_COLOR << endl;
        return;
    }
    Question question;
    //Read all the Questions from the file
    while (fread(&question, sizeof(Question), 1, file))
    {
        cout << question.question<< endl;
        cout << question.answer<< endl;
    }
    
    fclose(file);
}