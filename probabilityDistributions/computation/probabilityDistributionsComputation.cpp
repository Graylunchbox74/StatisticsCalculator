#include "probabilityDistributionComputation.hpp"


float findMeanPD(vector<float> outcomes, vector<float> probability){
    float sum = 0;
    for(int i = 0; i < outcomes.size(); i++){
        sum += (outcomes[i] * probability[i]);
    }
    return sum;
}


float findVariancePD(vector<float> outcomes, vector<float> probability){
    float sum = 0;
    for(int i = 0; i < outcomes.size(); i++){
        sum += (pow(outcomes[i],2) * probability[i]);
    }

    return sum - pow(findMeanPD(outcomes,probability), 2);
}


float findStandardDeviationPD(vector<float> outcomes, vector<float> probability){
    return sqrt(findVariancePD(outcomes,probability));
}