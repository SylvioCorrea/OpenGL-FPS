#ifndef PREVIOUSHEADERS_H_INCLUDED
#define PREVIOUSHEADERS_H_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <stdlib.h>


using namespace std;



//=====================================================
// Estruturas
//=====================================================

struct Point2d {
    int x;
    int y;
};

struct FrameData {
    Point2d* position;
    int frameNumber;
};

struct PersonData {
    int framesInVideo;
    vector<FrameData*> path;
};

struct VideoData {
    int pixelsPerMeter;
    int nOfFrames;
    vector<PersonData*> persons;
};
//=====================================================





//=====================================================
// "Construtores"
//=====================================================

PersonData* string2PersonData(string str);
PersonData* pdTest(string str);
VideoData* file2VideoData(string file);

//=====================================================





//=====================================================
//toStrings
//=====================================================

string toString(Point2d* p);
string toString(FrameData* fd);
string toString(PersonData* pd);
string toString(VideoData* vd);

//=====================================================




//=====================================================
//Conversores
//=====================================================

string int2string(int n);
string int2string(size_t n);
string float2String(float f);

//=====================================================





//=====================================================
//Algebra Linear
//=====================================================
void makeVetor(Point2d* p1, Point2d* p2, Point2d* res);
bool equals(Point2d* p1, Point2d* p2);
float module(float vx, float vy);
float dotProduct(float v1x, float v1y, float v2x, float v2y);
float angle2v(Point2d* v1, Point2d* v2);
float angle2v(float v1x, float v1y, float v2x, float v2y);



//=====================================================
//Auxiliares
//=====================================================
int ultimoFrameGrupo(int** matGrupo, int nPessoas, int nFrames);
void screenBound(VideoData* vd, Point2d* menores, Point2d* maiores);
void zeroFill(VideoData* vd);
void printMatrix(int** mat, int rows, int cols);
int getPixelData(string str);
int findNOfFrames(vector<PersonData*> vec);
//=====================================================


#endif // PREVIOUSHEADERS_H_INCLUDED
