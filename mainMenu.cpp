#include <iostream>
#include <vector>
#include <ncurses.h>
#include <queue>

using namespace std;

queue<int> inputQueue;
vector<string> options;

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
    init_pair(6, COLOR_BLACK, COLOR_WHITE); //normal color
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

    attron(COLOR_PAIR(5));
        mvprintw(1,1,"Use arrow keys to navigate");
        mvprintw(2,1,"Press enter to select option");
    attroff(COLOR_PAIR(5));

    attron(COLOR_PAIR(6));
        mvprintw(3,1, options[0].c_str());
    attroff(COLOR_PAIR(6));

    attron(COLOR_PAIR(2));
    for(int i = 1; i <= options.size(); i++)
        mvprintw(i + 3,1,options[i].c_str());
    attroff(COLOR_PAIR(2));
    
    int currentSelected = 0;
    attron(A_REVERSE);
    while(1){
        input();
        while(!inputQueue.empty()){
            int key = inputQueue.front();
            inputQueue.pop();
            if(key == KEY_UP){
                if(currentSelected > 0){
                    mvprintw(currentSelected + 3, 1, options[currentSelected].c_str());
                    currentSelected--;
                    mvprintw(currentSelected + 3, 1, options[currentSelected].c_str());
                    
                }
            }
            else if(key == KEY_DOWN){
                if(currentSelected < options.size() - 1){
                    mvprintw(currentSelected + 3, 1, options[currentSelected].c_str());
                    currentSelected++;
                    mvprintw(currentSelected + 3, 1, options[currentSelected].c_str());
                }
            }
            else if(key == 10){
                //go to menu selected
            }
            else if(key == 'q'){
                return;
            }
            cout << currentSelected << endl;
            // attron(COLOR_PAIR(2));
            // mvprintw(15,0,itoa(currentSelected));
            // attroff(COLOR_PAIR(2));
        }
    }
    attroff(A_REVERSE);


}



int main(){
    options.push_back("Find Values Given List");
    options.push_back("Test1");
    options.push_back("Testing2");

    MainMenu();
    endwin();
    return 0;
}