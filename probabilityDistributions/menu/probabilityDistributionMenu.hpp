#ifndef findingValuesMenu
#define findingValuesMenu
#include <string>
#include <iostream>
#include <queue>
#include <math.h>
#include <algorithm>
#include <vector>
#include <ncurses.h>
#include <climits>
#include "../computation/findingValuesOfList.hpp"

using namespace std;

namespace findingValuesGivenList{
        void runMenu();
        void printList(vector<float> list);
        void clearList();
        void input();
        void setup();
        void setupBorders();
        void computeStatistics();
};

#endif