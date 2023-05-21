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

typedef struct __CourseStates
{
    char courseTitle[20];
    float quizMarks;
    int totalDays;
    int present;
    int courseCredit;
} CourseStates;

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

string get_multiline_input()
{
    string input = "", output = "";

    while (input != "[END]")
    {
        getline(cin, input);

        if (input == "[END]")
            break;
        output += input + "\n";
    }

    return output;
}

string get_current_time_in_HM_format()
{
    // Get the current time
    std::time_t currentTime = std::time(nullptr);

    // Convert the current time to a struct tm
    std::tm *timeInfo = std::localtime(&currentTime);

    // Add one minute to the time
    timeInfo->tm_min += 1;

    // Handle overflow of minutes
    if (timeInfo->tm_min >= 60)
    {
        timeInfo->tm_hour += 1;
        timeInfo->tm_min -= 60;
    }

    // Format the time as "hour:minute" in 24-hour format
    char formattedTime[6];
    std::strftime(formattedTime, sizeof(formattedTime), "%H:%M", timeInfo);
    return string(formattedTime);
}

void show_homepage()
{
    cout << CYAN_COLOR << BOLD_COLOR << " _______  _______  _______ _________ _______  _______  _______  _        _______  _______ \n"
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
    int option, optionCount = 0;
    cout << "Choose what do you want to do?\n"
         << endl;
    cout << ++optionCount << ". Add a question. 🖊️" << endl;
    cout << ++optionCount << ". View questions. 👁️" << endl;
    cout << ++optionCount << ". Remove a question.✏️" << endl;
    cout << ++optionCount << ". Test yourself. 💯" << endl;
    cout << ++optionCount << ". Calculate CGPA. 🧮" << endl;
    cout << ++optionCount << ". Attendence and quiz marks status. ✋" << endl;
    // cout << ++optionCount << ". Add quiz marks. ✔️" << endl;
    cout << ++optionCount << ". Open app on GUI. 💡" << endl;
    cout << ++optionCount << ". Schedule a reminder. ⏰" << endl;
    cout << "99. Exit." << endl;
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

void remove_question()
{
    vector<string> fileNames;
    long long questionCount = 0;
    long long qNum;
    char confirm;
    for (const auto &entry : fs::directory_iterator(questionsDirectory))
    {
        if (entry.is_regular_file())
        {
            fileNames.push_back(entry.path().filename());
            Question question = get_question_from_file(entry.path().filename().string());
            cout << ++questionCount << ". " << endl;
            cout << GREEN_COLOR << "Question: " << DEFAULT_COLOR << question.question;
        }
    }
    cout << CYAN_COLOR << "Please enter the number of the question to remove:" << DEFAULT_COLOR;
    cin >> qNum;

    if (qNum > questionCount)
    {
        cout << RED_COLOR << "Invalid question number." << DEFAULT_COLOR << endl;
        return;
    }
    cout << "Confirm deletation [Y/N]:";
    cin >> confirm;
    if (confirm == 'Y' || confirm == 'y')
    {
        // cout << questionsDirectory + "/" + fileNames[qNum-1] << endl;
        fs::remove(questionsDirectory + "/" + fileNames[qNum - 1]);
        fs::remove(answersDirectory + "/" + fileNames[qNum - 1]);
        fs::remove(subjectsDirectory + "/" + fileNames[qNum - 1]);

        cout << GREEN_COLOR << "Question no. " << qNum << " has been deleted." << DEFAULT_COLOR << endl;
    }
}

void open_in_gui()
{
    system("/home/shakib/Dev/semTracker/build-semTracker-gui-Desktop-Debug/semTracker-gui");
}

void test_yourself()
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
    cout << CYAN_COLOR << " There are " << fileNames.size() << " questions. How many questions would you like to answer?" << DEFAULT_COLOR << endl;
    long long numOfQuestiontoAnswer = fileNames.size();

    cin >> numOfQuestiontoAnswer;

    while (numOfQuestiontoAnswer > fileNames.size())
    {
        cout << RED_COLOR << "You provided invalid number of question. Try again" << DEFAULT_COLOR << endl;
        cin >> numOfQuestiontoAnswer;
    }
    random_device rd;
    mt19937 generator(rd());
    shuffle(fileNames.begin(), fileNames.end(), generator);

    vector<string> userAnswer;
    vector<Question> questions;
    questions.resize(numOfQuestiontoAnswer);
    userAnswer.resize(numOfQuestiontoAnswer);

    for (long long i = 0; i < numOfQuestiontoAnswer; i++)
    {
        Question question = get_question_from_file(fileNames[i]);

        questions[i] = question;

        cout << i + 1 << ". " << question.question;

        userAnswer[i] = get_multiline_input();
    }

    for (long long i = 0; i < numOfQuestiontoAnswer; i++)
    {
        if (userAnswer[i].length() > 2)
        {
            cout << "Question: " << questions[i].question;
            cout << YELLOW_COLOR << "Your answer: " << userAnswer[i] << DEFAULT_COLOR << endl;
            cout << CYAN_COLOR << "Correct answer: " << questions[i].answer << DEFAULT_COLOR << endl;

            string command = "python3 check_answer.py " + string("\"") + questions[i].answer + string("\" ") + string("\"") + userAnswer[i] + string("\"");
            system(command.c_str());
        }
    }
}
// Fateen's part
void scehdule_notifier()
{
    string current_time = get_current_time_in_HM_format();
    string command = "echo 'notify-send \"Wake up to reality.\nNothing is remembered. Everything is forgotten. \"' -t 3000 | at " + current_time;
    system(command.c_str());
}

// Fateen's part
void calculate_cgpa()
{
    int subcount;
    cout << "Enter the number of your subject:";
    cin >> subcount;
    vector<float> grade, credit;
    float _grade_, _credit_, creditsum = 0, grademultiplier = 0;
    string order;
    char coursename[20];

    for (int i = 0; i < subcount; i++)
    {
        if (i + 1 == 1)
        {
            order = "st";
        }
        else if ((i + 1) == 2)
        {
            order = "nd";
        }
        else if ((i + 1) == 3)
        {
            order = "rd";
        }
        else
        {
            order = "th";
        }

        cout << "Enter the name of the " << i + 1 << order << " course name: ";

        scanf(" %[^\n]", coursename);

        cout << "Enter the grade of the " << i + 1 << order << " course: ";

        cin >> _grade_;
        cout << "Enter the credit of the " << i + 1 << order << " course: ";
        cin >> _credit_;
        creditsum += _credit_;
        grademultiplier += (_grade_ * _credit_);
        grade.push_back(_grade_);
        credit.push_back(_credit_);
    }
    printf("Your CGPA: %0.2f\n", grademultiplier / creditsum);
    cout << endl;
}
// Rihila's part
void attendence_quiz_status()
{
    cout << CYAN_COLOR << "Attendence status" << DEFAULT_COLOR << endl;
    int courseCount;
    cout << "Enter the number of your courses: ";
    cin >> courseCount;

    CourseStates courses[100000];
    for (int i = 0; i < courseCount; i++)
    {
        cout << "Enter the name of the "
             << " course no." << i + 1 << " :";
        scanf(" %[^\n]", courses[i].courseTitle);
        cout << "Enter the number of classes taken for the course: ";
        cin >> courses[i].totalDays;
        cout << "Enter the number of attended classes: ";
        cin >> courses[i].present;
        cout << "Enter the total number of course quiz: ";
        scanf("%f", &courses[i].quizMarks);
    }
    cout << endl;
    cout << CYAN_COLOR << BOLD_COLOR;
    printf("|%-20s %-10s %-10s %-15s %-10s|\n", "Course Title", "Total days", "Present", "Percentage(%)", "Quiz mark");
    cout << DEFAULT_COLOR << BOLD_COLOR;
    printf("|%-20s %-10s %-10s %-15s %-10s|\n", "", "", "", "", "");

    for (int i = 0; i < courseCount; i++)
    {
        float percentage = 100 * courses[i].present / courses[i].totalDays;
        printf("|%-20s %-10d %-10d %-15.2f %-10.1f|\n", courses[i].courseTitle, courses[i].totalDays, courses[i].present, percentage, courses[i].quizMarks);
    }
    cout << endl;
}
