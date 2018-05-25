#ifndef SAVER_H_INCLUDED
#define SAVER_H_INCLUDED
#include <fstream>
#include <vector>
#include "globals.h"
using namespace std;

class Saver
{
    vector<pair<int,int>> savedChunks;
    unsigned counter=1;
    string name="save";
public:
    Saver();
    void add(string number,string number2,string content);
    void replace(fstream& save,int counter,string to);
};

#endif // SAVER_H_INCLUDED
