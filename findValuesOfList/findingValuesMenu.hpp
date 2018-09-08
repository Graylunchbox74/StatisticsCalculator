#ifdef findingValuesMenu
#define findingValuesMenu
#include <string>
#include <iostream>
#include <queue>
#include <math.h>
#include <algorithm>
#include <vector>
#include <ncurses.h>
#include <climits>
#include "findingValuesOfList.hpp"

vector<float> list;
queue<int> inputQueue;
int row, column;
bool wantFloats;

void printList(vector<float> list);

void clearList();

void setupBorders();

void computeStatistics();

int runMenu();

#endif