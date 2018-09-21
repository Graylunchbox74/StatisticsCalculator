#include <string>
#include <iostream>
#include <queue>
#include <math.h>
#include <algorithm>
#include <vector>
#include <ncurses.h>
#include <climits>

using namespace std;

vector<int> outcome;
vector<float> probability;
queue<int> inputQueueProbabilityDistribution;
int row, column;

void setup(){
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

void  input(){
    int x;
    timeout(2);
    x = getch();
    if(x != -1){
        inputQueueProbabilityDistribution.push(x);
    }
}

void setupBordersTable(){

    attron(COLOR_PAIR(1));          
        mvprintw(2,0,"+-----+------------------+");
        mvprintw(3,0,"|     |                  |");
        mvprintw(4,0,"+-----+------------------+");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(4));
        mvprintw(3,3,"X");
        mvprintw(3,8,"Probability of X");
    attroff(COLOR_PAIR(4));
}

void printTableContents(){
    for(int i = 0; i < outcome.size(); i++){
        attron(COLOR_PAIR(1));
            mvprintw(i+5,0,"|     |                  |");
        attroff(COLOR_PAIR(1));

        mvprintw(i+5,5,"%d", outcome[i]);
        if(i < probability.size()){
            mvprintw(i+5,8,"%.7f", probability[i]);
        }
    }
    attron(COLOR_PAIR(1));
        mvprintw(outcome.size()+5,0,"+-----+------------------+");
    attroff(COLOR_PAIR(1));
    return;
}


void getTable(){
    int inputNum = INT_MAX;
    float inputFloat = -1;
    int decimalPos = -1;
    bool outcomeVector = true;
    setupBordersTable();
    printTableContents();
    while(1){
        input();
        while(!inputQueueProbabilityDistribution.empty()){
            int key = inputQueueProbabilityDistribution.front();
            inputQueueProbabilityDistribution.pop();
            if(key == 'q'){
                return;
            }
            else if(key == '.'){
                if(decimalPos == -1 && outcomeVector == false)
                    decimalPos = 1;
            }
            else if(key >= '0' && key <= '9'){
                if(outcomeVector){
                    if(inputNum == INT_MAX)
                        inputNum = key - '0';
                        outcome.push_back(inputNum);
                    else{
                        inputNum *= 10;
                        inputNum += key - '0';
                        outcome[outcome.size()-1] = inputNum;
                    }
                }
                else{
                    if(decimalPos == -1){
                        if(inputFloat == -1){
                            inputFloat = key - '0';
                            probability.push_back(inputFloat);
                        }
                        else{
                            inputFloat *= 10;
                            inputFloat += key - '0';
                            probability[probability.size() - 1] = inputFloat;
                        }
                    }
                    else{
                        float addTo = key - '0';
                        for(int i = 0; i < decimalPos; i++){
                            addTo /= 10;
                        }
                        inputFloat += addTo;
                        decimalPos++;
                    }
                }
            }
            else if(key == ' ' || key == KEY_ENTER){
                if(outcomeVector && inputNum != INT_MAX){
                        inputNum = INT_MAX;
                        outcomeVector = !outcomeVector;
                }
                else{
                    if(inputFloat != -1){
                        inputFloat = -1;
                        outcomeVector = !outcomeVector;                        
                    }
                }
            }
            printTableContents();
        }
    }
}





void setupBordersStatistics(){
    attron(COLOR_PAIR(1));
//                 0         10        20        30        40        50        60        70        80
//                 0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567
    mvprintw(2,0, "+-------------------------------------------------------------+-----+------------------+");
    mvprintw(3,0, "|                                                             |     |                  |");
    mvprintw(4,0, "|                                                             |-----+------------------+");
    mvprintw(5,0, "|                                                             |");
    mvprintw(6,0, "|                                                             |");
    mvprintw(7,0, "|                                                             |");
    mvprintw(8,0, "|                                                             |");
    mvprintw(9,0, "|                                                             |");
    mvprintw(10,0,"|                                                             |");
    mvprintw(11,0,"+-------------------------------------------------------------+");
    mvprintw(12,0,"|                                                             |");
    mvprintw(13,0,"|                                                             |");
    mvprintw(14,0,"|                                                             |");
    mvprintw(15,0,"|                                                             |");
    mvprintw(16,0,"|                                                             |");
    mvprintw(17,0,"|                                                             |");
    mvprintw(18,0,"|                                                             |");
    mvprintw(19,0,"+-------------------------------------------------------------+");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(4));
    mvprintw(3, 65, "X");
    mvprintw(3, 70, "Probability of X");
    mvprintw(3,1,"Select X value:");
    mvprintw(4,1,"Probability of X:");
    mvprintw(5,1,"Probability of X and Greater:");
    mvprintw(6,1,"Probability of X and Less:");
    mvprintw(8,1,"Is X Significant:");
    mvprintw(9,1,"Is X and Greater Significant:");
    mvprintw(10,1,"Is X and Less Significant:");
    attroff(COLOR_PAIR(4));

    //instructions
    attron(COLOR_PAIR(5));
    attroff(COLOR_PAIR(5));

}

void computeStatistics(){
}

void runMenu(){
    int decimalPos = -1;
    float inputNum = INT_MAX;
    setup();
    //setupBorders();
    while(1){
        input();
        while(!inputQueueProbabilityDistribution.empty()){
            int key = inputQueueProbabilityDistribution.front();
            inputQueueProbabilityDistribution.pop();
            
            if(key == 'c'){
//                clearList();
                //setupBorders();
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
            //printList(outcome);
        }
    }

    return ;
}


int main(){
    setup();
    getTable();
    endwin();
    return 0;
}