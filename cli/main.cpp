#include <iostream>
#include <map>
#include <filesystem>
#include <cstdlib>
#include <thread>
#include <future>
#include "utils/utils.h"

namespace fs = std::filesystem;
using namespace std;

void pause()
{
    string x;
    cout << "Press any key to continue..." << endl;
    getline(cin, x);
    getline(cin, x);
}

int main()
{

    system("clear");

    int menu = 0;
    show_homepage();

    fs::create_directories(questionsDirectory);
    fs::create_directories(answersDirectory);
    fs::create_directories(subjectsDirectory);

    thread guiThread;

    while (menu != 99)
    {
        menu = get_menu();
        switch (menu)
        {
        case 1:
            /* add question */
            add_question();
            pause();
            break;
        case 2:
            /* Test yourself */
            break;
        case 3:
            /* Score board */
            break;
        case 4:
            /* View questions */
            get_question();
            pause();
            break;
        case 5:
            /* Add attendence */
            break;
        case 6:
            /* Add quiz marks */
            break;
        case 7:
            /* Check Statistics */
            break;
        case 8:
            guiThread = thread(open_in_gui);
            system("clear");
            cout << "Opening app in graphical interface" << endl;
            break;
        case 99:
            cout << "Bye..." << endl;
            break;
        default:
            cout << "\x1b[31mInvalid option\x1b[37m" << endl;
            break;
        }

        if (guiThread.joinable())
        {
            guiThread.join();
        }
    }
    return 0;
}