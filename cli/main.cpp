#include <iostream>
#include <map>
#include "utils/utils.h"
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

int main()
{
    int menu = 0;
    show_homepage();
    
    fs::create_directories(questionsDirectory);
    fs::create_directories(answersDirectory);
    fs::create_directories(subjectsDirectory);
    
    while (menu != 8)
    {
        menu = get_menu();
        switch (menu)
        {
        case 1:
            /* add question */
            add_question();
            break;
        case 2:
            /* Test yourself */
            break;
        case 3:
            /* Score board */
            break;
        case 4:
            get_question();
            /* View questions */
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
        case 99:
            cout << "Bye..." << endl;
            break;
        default:
            cout << "\x1b[31mInvalid option\x1b[37m" << endl;
            break;
        }
    }
    return 0;
}