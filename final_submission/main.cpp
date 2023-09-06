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

using namespace std;

int main(int argc, char** argv )
{

    // auto t1 = high_resolution_clock::now();
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
    // auto t2 = high_resolution_clock::now();
    s->compute_allocation();
    // auto t3 = high_resolution_clock::now();
    s->write_to_file(outputfilename);
    // auto t4 = high_resolution_clock::now();
    long long cost = s->cost_fn ();
    // cout<<" Time taken "<<duration_cast<milliseconds>(t4-t1).count()<<"seconds"<<endl;
    cout<< "cost:"<<cost<<endl;



    return 0;

}