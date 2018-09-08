#include <iostream>
#include <vector>
#include <ncurses.h>
#include <queue>
#include <functional>
#include "findValuesOfList.hpp"

using namespace std;

queue<int> inputQueue;
struct option{
    string nameOnScreen;
    void (*functionForMenu)();
};

vector<option> options;

void input(){
    int x;
    timeout(2);
    x = getch();
    if(x != -1){
        inputQueue.push(x);
    }
}

int setup(){
    initscr();
    raw();
    curs_set(FALSE);
    noecho();
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK); //Border
    init_pair(2, COLOR_WHITE, COLOR_BLACK); //normal color
    init_pair(3, COLOR_RED, COLOR_BLACK); //list
    init_pair(4, COLOR_YELLOW, COLOR_BLACK); //label
    init_pair(5, COLOR_CYAN, COLOR_BLACK); // instructions
    init_pair(6, COLOR_BLACK, COLOR_YELLOW); //normal color
    init_pair(7, COLOR_BLACK, COLOR_CYAN);
}

void MainMenu(){
    if(options.empty()){
        cout << "Nothing to show in the menu" << endl;
        return;
    }

    setup();

    attron(COLOR_PAIR(1));
        mvprintw(0,0,"+------------------------------------+");
        for(int i = 1; i <= options.size() + 2; i++)
            mvprintw(i,0,"|                                    |");

        mvprintw(options.size() + 3,0,"+------------------------------------+");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(4));
        mvprintw(1,1,"Use arrow keys to navigate");
        mvprintw(2,1,"Press enter to select option");
    attroff(COLOR_PAIR(4));

    attron(COLOR_PAIR(7));
        mvprintw(3,1, options[0].c_str());
    attroff(COLOR_PAIR(7));

    attron(COLOR_PAIR(2));
    for(int i = 1; i < options.size(); i++){
        mvprintw(i + 3,1, options[i].c_str());
    }
    attroff(COLOR_PAIR(2));
    
    // attron(COLOR_PAIR(6));
    // mvprintw(16,0,"TESTING");
    // attroff(COLOR_PAIR(6));

    int currentSelected = 0;
    while(1){
        input();
        while(!inputQueue.empty()){
            int key = inputQueue.front();
            inputQueue.pop();
            if(key == KEY_UP){
                if(currentSelected > 0){
                    attron(COLOR_PAIR(2));
                    mvprintw(currentSelected + 3, 1, options[currentSelected].c_str());
                    attroff(COLOR_PAIR(2));
                    currentSelected--;
                    attron(COLOR_PAIR(7));
                    mvprintw(currentSelected + 3, 1, options[currentSelected].c_str());                    
                    attroff(COLOR_PAIR(7));
                }
            }
            else if(key == KEY_DOWN){
                if(currentSelected < options.size() - 1){
                    attron(COLOR_PAIR(2));
                    mvprintw(currentSelected + 3, 1, options[currentSelected].c_str());
                    attroff(COLOR_PAIR(2));
                    currentSelected++;
                    attron(COLOR_PAIR(7));
                    mvprintw(currentSelected + 3, 1, options[currentSelected].c_str());                    
                    attroff(COLOR_PAIR(7));
                }
            }
            else if(key == 10){

            }
            else if(key == 'q'){
                return;
            }

        }
    }


}

void helloWorld(){
    cout << "HEllo world" <<  endl;
}

int main(){

    MainMenu();
    endwin();
    return 0;
}