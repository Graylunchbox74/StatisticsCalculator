#include "findingValuesMenu.hpp"


vector<float> outcome, probability;
queue<int> inputQueueProbabilityDistribution;
int row, column;


void findingValuesGivenList::setupBorders(){
    attron(COLOR_PAIR(1));
    mvprintw(2,0, "+-----------------------------+--------------------------------+");
    mvprintw(3,0, "|                             |                                |");
    mvprintw(4,0, "|                             |                                |");
    mvprintw(5,0, "|                             |                                |");
    mvprintw(6,0, "|                             |                                |");
    mvprintw(7,0, "|                             |                                |");
    mvprintw(8,0, "|                             |                                |");
    mvprintw(9,0, "|                             |                                |");
    mvprintw(10,0,"|                             |                                |");
    mvprintw(11,0,"+-----------------------------+--------------------------------+");
    mvprintw(12,0,"|                             |                                |");
    mvprintw(13,0,"|                             |                                |");
    mvprintw(14,0,"|                             |                                |");
    mvprintw(15,0,"|                             |                                |");
    mvprintw(16,0,"+-----------------------------+                                |");
    mvprintw(17,0,"|                             |                                |");
    mvprintw(18,0,"|                             |                                |");
    mvprintw(19,0,"|                             |                                |");
    mvprintw(20,0,"|                             |                                |");
    mvprintw(21,0,"|                             |                                |");
    mvprintw(22,0,"+-----------------------------+--------------------------------+");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(4));
    mvprintw(0, 0, "list: ");
    mvprintw(3,2,"Sample:");
    mvprintw(5,2,"Standard Deviation:");
    mvprintw(8,2,"Variance:");



    mvprintw(3,32,"Population:");
    mvprintw(5,32,"Standard Deviation:");
    mvprintw(8,32,"Variance:");

    mvprintw(12, 2, "Mean:");
    mvprintw(13, 2, "Median:");
    mvprintw(14, 2, "Mode:");
    mvprintw(15, 2, "Range:");

    mvprintw(17,2,"Low:");
    mvprintw(18,2,"Q1:");
    mvprintw(19,2,"Median:");
    mvprintw(20,2,"Q3:");
    mvprintw(21,2,"High:");

    mvprintw(12,32,"Instructions");
    attroff(COLOR_PAIR(4));

    attron(COLOR_PAIR(5));
    mvprintw(13,32,"Type in list, space seperated");
    mvprintw(14,32,"Type 'c' to clear list");
    mvprintw(15,32,"Type 'q' to quit");
    mvprintw(16,32,"Type 'f' to toggle float view");

    attroff(COLOR_PAIR(6));


}

void computeStatistics(){
}

void findingValuesGivenList::input(){
    int x;
    timeout(2);
    x = getch();
    if(x != -1){
        inputQueueProbabilityDistribution.push(x);
    }
}

void findingValuesGivenList::setup(){
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

void findingValuesGivenList::runMenu(){
    int decimalPos = -1;
    float inputNum = INT_MAX;
    setup();
    setupBorders();
    while(1){
        input();
        while(!inputQueueProbabilityDistribution.empty()){
            int key = inputQueueProbabilityDistribution.front();
            inputQueueProbabilityDistribution.pop();
            
            if(key == 'c'){
                clearList();
                setupBorders();
                inputNum = INT_MAX;
                decimalPos = -1;
                outcome = {};
                probability = {};
                continue;
            }


            else if(key == 'q'){
                endwin();
                werase(stdscr);
                return;
            }

            else if(key == '.'){
                decimalPos = 1;
            }

            else if(key >= '0' && key <= '9'){
                if(inputNum == INT_MAX && decimalPos != -1){
                    outcome.push_back((float)(key-'0')/10);
                    decimalPos++;
                }
                else if(inputNum == INT_MAX){
                    inputNum = key - '0';
                    outcome.push_back(inputNum);
                }
                else if(decimalPos != -1){
                    inputNum = inputNum + ((float)(key-'0')/pow(10,decimalPos));
                    outcome[outcome.size() -1] = inputNum;
                    decimalPos++;
                }
                else{
                    inputNum = (inputNum*10) + (key - '0');
                    outcome[outcome.size() - 1] = inputNum;
                }
            }
            else if(key == ' '){
                inputNum = INT_MAX;
                decimalPos = -1;
            }
            else{
                continue;
            }

            if(!outcome.empty())
                computeStatistics();
            printList(outcome);
        }
    }

    return ;
}
