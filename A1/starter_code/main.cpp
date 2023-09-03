#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <fstream>

#include "SportsLayout.h"

using namespace std::chrono;

int main(int argc, char** argv )
{

    auto start = high_resolution_clock::now();
     // Parse the input.
    if ( argc < 3 )
    {   
        cout<<"Missing arguments\n";
        cout<<"Correct format : \n";
        cout << "./main <input_filename> <output_filename>";
        exit ( 0 );
    }
    string inputfilename ( argv[1] );
    string outputfilename ( argv[2] );
    
    SportsLayout *s  = new SportsLayout( inputfilename );
    s->compute_allocation();
    s->write_to_file(outputfilename);

    long long cost = s->cost_fn ();
    cout<< "cost:"<<cost<<endl;
    auto stop = high_resolution_clock::now();
    cout<<"Time taken:"<<duration_cast<milliseconds>(stop - start).count()<<endl;


    return 0;

}