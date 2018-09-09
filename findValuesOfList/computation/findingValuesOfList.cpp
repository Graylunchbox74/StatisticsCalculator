#include "findingValuesOfList.hpp"

float findMean(vector<float> list){
    float sum = 0;
    for(int i = 0; i < list.size(); i++){
        sum += list[i];
    }

    return sum / list.size();
}


float findStandardDeviationSample(vector<float> list){
    if(list.empty())
        return 0;

    float sum = 0;

    float mean = findMean(list);

    for(int i = 0; i < list.size(); i++){
        sum += pow(list[i] - mean,2);
    }

    float newMean = sum / (list.size() - 1);

    return sqrt(newMean);
}


float findStandardDeviationPopulation(vector<float> list){
    if(list.empty())
        return 0;

    float sum = 0;

    float mean = findMean(list);

    for(int i = 0; i < list.size(); i++){
        list[i] = pow(list[i] - mean,2);
        sum += list[i];
    }
    float newMean = sum / list.size();

    return sqrt(newMean);
}

float findVarianceSample(vector<float> list){
    if(list.empty())
        return 0;

    return pow(findStandardDeviationSample(list),2);
}

float findMode(vector<float> list){
    if(list.empty())
        return 0;

    int currentMode = list[0];
    int currentModeAmount = 1;

    int tmpMode = list[0];
    int tmpModeAmount = 1;
    
    for(int i = 1; i < list.size(); i++){
        if(list[i] == tmpMode){
            tmpModeAmount++;
        }
        else{
            if(tmpModeAmount > currentModeAmount){
                currentMode = tmpMode;
                currentModeAmount = tmpModeAmount;
            }
            tmpMode = list[i];
            tmpModeAmount = 1;
        }
    }

    if(tmpModeAmount > currentModeAmount){
        currentMode = tmpMode;
        currentModeAmount = tmpModeAmount;
    }


    return currentMode;
}

float findVariancePopulation(vector<float> list){
    if(list.empty())
        return 0;

    return pow(findStandardDeviationPopulation(list),2);
}

float findMedian(vector<float> list){
    if(list.empty())
        return 0;

    if(list.size() % 2 == 1){
        return list[list.size() / 2];
    }
    else{
        return (list[list.size()/2 - 1] + list[list.size()/2]) / 2;
    }
}

float findRange(vector<float> list){
    return list[list.size()-1] - list[0];
}

float findLow(vector<float> list){
    if(list.empty())
        return 0;
    else
        return list[0];
}

float findMax(vector<float> list){
    if(list.empty())
        return 0;
    else
        return list[list.size()-1];
}

float findQ1(vector<float> list){
    vector<float> tmp;
    if(list.size()%2==1)
        for(int i = 0; i <= list.size()/2; i++)
            tmp.push_back(list[i]);
    else
        for(int i = 0; i <= list.size()/2-1; i++)
            tmp.push_back(list[i]);

    return findMedian(tmp);
}

float findQ3(vector<float> list){
    vector<float> tmp;
    for(int i = list.size()/2; i < list.size(); i++)
        tmp.push_back(list[i]);
    return findMedian(tmp);
}