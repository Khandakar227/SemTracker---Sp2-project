#include <iostream>
using namespace std;

void add_question()
{
    cout << "Add questions" << endl;
}

void show_homepage()
{
    cout << " _______  _______  _______ _________ _______  _______  _______  _        _______  _______ \n"
         << "(  ____ \\(  ____ \\(       )\\__   __/(  ____ )(  ___  )(  ____ \\| \\    /\\(  ____ \\(  ____ )\n"
         << "| (    \\/| (    \\/| () () |   ) (   | (    )|| (   ) || (    \\/|  \\  / /| (    \\/| (    )|\n"
         << "| (_____ | (__    | || || |   | |   | (____)|| (___) || |      |  (_/ / | (__    | (____)|\n"
         << "(_____  )|  __)   | |(_)| |   | |   |     __)|  ___  || |      |   _ (  |  __)   |     __)\n"
         << "      ) || (      | |   | |   | |   | (\\ (   | (   ) || |      |  ( \\ \\ | (      | (\\ (   \n"
         << "/\\____) || (____/\\| )   ( |   | |   | ) \\ \\__| )   ( || (____/\\|  /  \\ \\| (____/\\| ) \\ \\__\n"
         << "\\_______)(_______/|/     \\|   )_(   |/   \\__/|/     \\|(_______/|_/    \\/(_______/|/   \\__/\n"
         << "                                                                                          \n"
         << endl;
   
    cout << "\nsemTracker is a CLI tool for studying that helps you memorize questions and track your progress. You can then put your memory to the test. Track your attendence. Lackings and Quiz marks. \n\n\n\n"
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
    cout << " 4. View questions."<< endl;
    cout << " 5. Add attendence."<< endl;
    cout << " 6. Add quiz marks."<< endl;
    cout << " 7. Check statistics."<< endl;
    cout << " > ";
    cin >> option;
    return option;
}

