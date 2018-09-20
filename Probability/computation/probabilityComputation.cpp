#include "probabilityComputation.hpp"


float findSumOfList(vector<float> input){
    float sum = 0;
    for(int i = 0; i < input.size(); i++){
        sum += input[i];
    }
    return sum;
}

float findProbabilityOfListFromList(vector<float> input, vector<float> list){
    float inputSum, listSum;
    inputSum = findSumOfList(input);
    listSum = findSumOfList(list);

    return inputSum / listSum;
}