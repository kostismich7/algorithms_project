#include <iostream>
#include <iomanip>
#include <limits>
#include "HashTableStruct.h"
#include "Dataset.h"
#include "ui.h"
#include "parse_files.h"
#include "utils.h"
#include "LSH.h"
#include "hasher.h"
#include "distance.h"
#include "search.h"

LSH *LoadInput(int argc, char* argv[]) {
    auto lsh = new LSH(new DTW());
    readArgumentsLSHCurves(lsh, argc, argv);
    if(!lsh->isInputFileGiven())
        lsh->setInputFilename(askInputFile());
    if(!lsh->isQueryFileGiven())
        lsh->setQueryFilename(askQueryFile());
    if(!lsh->isOutputFileGiven())
        lsh->setOutputFilename(askOutputFile());
    lsh->setData(parseQueryFileCurves(lsh->getInputFilename()));
    cout << lsh->getDataset()->getMean() << endl;
    //TODO:find formula for window and min
    auto dataset = lsh->getDataset();
    lsh->setHashTableStruct(new CurveHashTableStruct(lsh->getNumOfHashTables(),dataset->getSize(),lsh->getNumOfFunctions(),dataset->getDimension(),0.02,dataset->getMax(),4000));
    auto points = lsh->getDataset()->getData();
    for (auto & point : points)
        lsh->getHashTableStruct()->addToAllHashTables(point);
    lsh->setQueryData(parseQueryFileCurves(lsh->getQueryFilename()));
    return lsh;
}


int main(int argc, char* argv[]){
    auto lsh = LoadInput(argc,argv);
    DoQueries(lsh);
}
