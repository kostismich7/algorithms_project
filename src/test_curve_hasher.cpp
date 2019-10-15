#define private public
#include <random>
#include <set>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "hasher.h"
#include "LSH.h"
#include "Point.h"
#include "Curve.h"


static FILE* temp_file = NULL;
LSH *lsh;
using namespace std;

struct point_compare {
   bool operator() (Point const point1,Point const point2) {
    if (point1.coordinates.size() !=  point2.coordinates.size())
        return true;
    for (int i =0; i<point2.coordinates.size(); i++) 
        if (point1.coordinates.at(i) == point2.coordinates.at(i))
            continue;
        else if (point1.coordinates.at(i) <point2.coordinates.at(i))
            return true;
        else 
            return false;
    return false;
   }
};

void test_CurveHasher() {
    auto chasher = new CurveHasher(2,10,10,0);
    for (int i =0; i < 2; i++)
        CU_ASSERT(chasher->shiftedGrid[i] < 2.0);
    chasher = new CurveHasher(7,10,10,0);
    for (int i =0; i < 7; i++)
        CU_ASSERT(chasher->shiftedGrid[i] < 7.0);
}

void test_snap() {
    auto chasher = new CurveHasher(2,3,3,0);    
    auto delta = 4 * 2 * 3 ;
    auto point = new Point("1");
    point->addCoordinateLast(90.4329482); point->addCoordinateLast(14.5342342);
    auto snaped = chasher->snap(point);
    //double precision may be inaccurate so 
    //ensure we are approximately near the expected results.
    CU_ASSERT(fabs(snaped[0] - 4.0 * double(delta)) < 2.0);
    CU_ASSERT(fabs(snaped[1] - 1.0 * double(delta)) < 2.0);
    //create four points that should lie on the same grid curve
    //but have different coordinates
    auto point2 = new Point("2");
    point2->addCoordinateLast(14.955); point2->addCoordinateLast(102.1344);
    auto point3 = new Point("3");
    point3->addCoordinateLast(28.0002); point3->addCoordinateLast(94.000772);
    auto point4 = new Point("4");
    point4->addCoordinateLast(34.9933); point4->addCoordinateLast(100.000772);
    auto point5 = new Point("5");
    point5->addCoordinateLast(24.94203482); point5->addCoordinateLast(96.432984);
    snaped = chasher->snap(point2);
    auto snaped2 = chasher->snap(point3);
    auto snaped3 = chasher->snap(point4);
    auto snaped4 = chasher->snap(point5);
    CU_ASSERT(snaped[0] == snaped2[0] && snaped3[0] == snaped4[0]);
    CU_ASSERT(snaped[0] == snaped3[0] && snaped2[0] == snaped4[0]);
    CU_ASSERT(snaped[1] == snaped2[1] && snaped3[1] == snaped4[1]);
    CU_ASSERT(snaped[1] == snaped3[1] && snaped2[1] == snaped4[1]);
    //create two points that should NOT lie on the same grid curve
    point = new Point("6");
    point->addCoordinateLast(14.955); point->addCoordinateLast(102.1344);
    point3 = new Point("7");
    point3->addCoordinateLast(5.0002); point3->addCoordinateLast(66.000772);
    snaped = chasher->snap(point);
    snaped2 = chasher->snap(point3);
    CU_ASSERT(snaped[0] != snaped2[0] && snaped[1] != snaped2[1]);
}

void test_Vectorize() {
   //create a curve with length == 7.
   //first three consecutive lie on the same grid curve so 
   //only the first one should exist after removing duplicates.
   //Same applies for points 4,5 and for points 6,7
   vector<Point> pointVec;
   pointVec.push_back(*(new Point(vector<double> {10.4324,100.4328})));
   pointVec.push_back(*(new Point(vector<double> {11.89,98.489})));
   pointVec.push_back(*(new Point(vector<double> {15.7668,96.603})));
   pointVec.push_back(*(new Point(vector<double> {87.883,63.432})));
   pointVec.push_back(*(new Point(vector<double> {88.883,62.432})));
   pointVec.push_back(*(new Point(vector<double> {44.883,46.432})));
   pointVec.push_back(*(new Point(vector<double> {49.883,43.432})));
   auto curve = new Curve(pointVec);
   //delta = 4 * 2 * 7 = 56.
   auto chasher = new CurveHasher(2,7,7,0);
   auto point = chasher->vectorize(chasher->snap(curve));
   CU_ASSERT(point->getCoordinates().size() == 3);
}

vector<Curve> generateDataset(int numCurves,int curveLen,int lower,int upper) {
    vector<Point> *pointVec;
    pointVec = new vector<Point>[numCurves];
    vector<Curve> curveVec;
    uniform_real_distribution<double> dist(lower,upper);
    default_random_engine re;
    for (int i=0; i < numCurves; i++) {
        for (int j=0; j < curveLen; j++) 
            pointVec[i].push_back(*(new Point(vector<double> {dist(re),dist(re)})));
        curveVec.push_back(*(new Curve(pointVec[i])));
    }
    return curveVec;
}

void runHasher(int numCurves,int curveLen,int window,vector<Curve> curveVec,int *bucketRes,int *vectoriseRes) {
    size_t bucket;
    auto chasher = new CurveHasher(2,curveLen,curveLen,window);
    set<size_t> buckets;
    set<Point,point_compare> pointSet;
    Point *prev = nullptr;
    Point *curr = nullptr;
    for (int i=0; i < numCurves; i++) {
        auto point = chasher->vectorize(chasher->snap(&curveVec.at(i)));
        pointSet.insert(*point);
        bucket = (*chasher)(&curveVec.at(i));
        buckets.insert(bucket);
    }
    *bucketRes = buckets.size();
    *vectoriseRes = pointSet.size();
}  

void test_Hash() {
   //test two curves that should lie on the same bucket.
   vector<Point> _pointVec;
   _pointVec.push_back(*(new Point(vector<double> (10.4324,100.4328))));
   _pointVec.push_back(*(new Point(vector<double> (49.89,22.489))));
   auto curve = new Curve(_pointVec);
   vector<Point> _pointVec2;
   _pointVec2.push_back(*(new Point(vector<double> (11.4324,98.2391))));
   _pointVec2.push_back(*(new Point(vector<double> (48.777,20.777))));
   auto curve2 = new Curve(_pointVec2);
   //delta = 4 * 2 * 2 = 16
   auto _chasher = new CurveHasher(2,2,2,20);
   auto point = _chasher->vectorize(_chasher->snap(curve));
   auto point2 = _chasher->vectorize(_chasher->snap(curve2));
   CU_ASSERT(*point == *point2);
   auto bucket = (*_chasher)(curve);
   auto bucket2 = (*_chasher)(curve2);
   CU_ASSERT(bucket == bucket2);
   //test multiple curves (numCurves) with length = curveLen.
   //the success of this test depends on window of PointHasher 
   //that is created in CurveHashre constructor.

   //delta = 4 * 2* 10 = 80
   auto curveVec = generateDataset(3000,10,0,50);
   int bucketRes, vectoriseRes;
   int window = 20;
   runHasher(3000,10,window,curveVec,&bucketRes,&vectoriseRes);
   printf("results: points = %d, buckets = %d\n",vectoriseRes,bucketRes);
}


int init_suite1(void)
{
   if (NULL == (temp_file = fopen("testPoinHasher.txt", "w+"))) {
      return -1;
   }
   else {
      return 0;
   }
}

int clean_suite1(void)
{
   if (0 != fclose(temp_file)) {
      return -1;
   }
   else {
      temp_file = NULL;
      return 0;
   }
}

int main(int argc,char *argv[]) {
   CU_pSuite pSuite = NULL;
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();
   pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }
   if ((NULL == CU_add_test(pSuite, "test of CurveHasher constructor", test_CurveHasher))||
       (NULL == CU_add_test(pSuite, "test of round Coordinate", test_snap)) || 
       (NULL == CU_add_test(pSuite,"test_Vectorize",test_Vectorize)) ||
       (NULL == CU_add_test(pSuite,"test_Hash",test_Hash)))
      {
      CU_cleanup_registry();
      return CU_get_error();
   }
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
