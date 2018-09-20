#include <ncurses.h>
#include <iostream>
#include <queue>

#include "../computation/probabilityComputation.hpp"

using namespace std;

queue<int> inputQueueProbabilityMenu;
bool wantFloatsProbability;

void input(){
    int x;
    timeout(2);
    x = getch();
    if(x != -1){
        inputQueueProbabilityMenu.push(x);
    }
}

void setup(){
    wantFloatsProbability = false;
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
}

void printProbabilityMenu(){
    mvprintw(2,0,"Probability Of:");
    mvprintw(3,0,"Probability:");
//    instructions = 12
    int maxX, maxY;
    getmaxyx(stdscr, maxY, maxX);
    mvprintw(4,0,"+");

    for(int i = 1; i < maxX - 12; i++){
        mvprintw(4,i,"-");
    }

}