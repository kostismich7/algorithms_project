#include <stdlib.h>
#include <random>
#include <vector>
#include  <stdio.h>
#include "hash_func.h"
#include "Object.h"
#include "Point.h"
#include "utils.h"


using namespace std;

PointHasher::PointHasher(int amplificationSize,int numDimension) {
    //maybe we need  more or less
    this->amplificationSize = amplificationSize;
    this->numDimension = numDimension;
    gridPoolSize = amplificationSize * 10;
    if (gridPool == nullptr) {
        generateGrids();
    }
    random_device r;
    //do we need another engine?
    default_random_engine e1(r());
    uniform_int_distribution<int> uniform_dist(0,gridPoolSize-1);
    selectedGrids = (int *)malloc(gridPoolSize * sizeof(int));
    for (int i = 0; i<amplificationSize; i++){
        selectedGrids[i] = uniform_dist(e1);
    }
}

PointHasher::~PointHasher() {
    for (int i=0;i<gridPoolSize; i++)
        free(gridPool[i]);
    free(gridPool);
    free(selectedGrids);
}

void PointHasher::generateGrids() {
    random_device r;
    //do we need another engine?
    default_random_engine e1(r());
    uniform_real_distribution<float> uniform_dist(0,WINDOW_SIZE);
    gridPool = (double **)malloc(gridPoolSize * sizeof(double*));
    for(int i = 0; i < gridPoolSize;i++)  
        gridPool[i] = (double *)malloc(numDimension* sizeof(double));
    for (int i =0; i< gridPoolSize; i++) 
        for (int j =0; j < numDimension; j ++) 
            gridPool[i][j] = uniform_dist(e1);
}

int PointHasher::hash(Object* obj,int hashIndex) {
    Point *point = dynamic_cast<Point *>(obj);
    vector<double> coordinates = point->getCoordinates();
    //or select coefficient randomly?
    int coefficient = 0xffff;
    int sum = 0,i = 0,j = numDimension;
    int M = pow(2,32/amplificationSize);
    //sum can not overflow because we sum numDimension values
    //each of them is < M. So the max(sum) = numDimension * M  
    // = numDimension * 2^(32/numDimension) < 2^32. 
    for (auto c :coordinates) {
        int gridCell = int((c - gridPool[selectedGrids[hashIndex]][i])/WINDOW_SIZE); 
        sum+= ((gridCell%M)*(powModulo(coefficient,j,M)))%M;
        i++;
        j--;
    }
    return sum % M;
}

int PointHasher::hash(Object* obj) {
    Point *point = dynamic_cast<Point *>(obj);
    string amplified = "";
    for (int i =0; i < amplificationSize;i++) 
        amplified+= to_string(hash(obj,i));
    return stoi(amplified);
}