
#ifndef SPORTSLAYOUT_H
#define	SPORTSLAYOUT_H

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
using namespace std;

class SportsLayout{

    private:
    int z,l;
    int** T;
    int **N;
    int time;
    int *mapping;
    // long long cost;

    public:
    SportsLayout(string inputfilename);

    bool check_output_format();

    // void readOutputFile(string output_filename);
    
    long long cost_fn();

    long long next_cost_fn(int i, int j,long long cost);

    void write_to_file(string outputfilename);

    void readInInputFile(string inputfilename);

    void compute_allocation();


};


#endif