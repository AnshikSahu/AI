#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <climits>

using namespace std;

#include "SportsLayout.h"

    SportsLayout::SportsLayout(string inputfilename)
    {
          
        readInInputFile(inputfilename);
        mapping= new int[z];

    }

    bool SportsLayout::check_output_format()
    {

        vector<bool> visited(l,false);
        for(int i=0;i<z;i++)
        {
            if((mapping[i]>=1 && mapping[i]<=l))
            {
                if(!visited[mapping[i]-1])
                visited[mapping[i]-1]=true;
                else
                {
                    cout<<"Repeated locations, check format\n";
                    return false;
                }
            }
            else
            {
                cout<<"Invalid location, check format\n";
                return false;
            }
        }

        return true;

    }

    // void SportsLayout::readOutputFile(string output_filename)
    // {
    //         fstream ipfile;
	//         ipfile.open(output_filename, ios::in);
    //         if (!ipfile) {
    //             cout << "No such file\n";
    //             exit( 0 );
    //         }
    //         else {
                
    //             vector<int> ip;

    //             while (1) {
    //                 int t;
    //                 ipfile >> t;
    //                 ip.push_back(t);
    //                 if (ipfile.eof())
    //                     break;
                    
    //             }
            
    //         if(ip.size()!=z)
    //         {
    //             cout<<"number of values not equal to number of N, check output format\n";
    //             exit(0);
    //         }
    //         for(int i=0;i<z;i++)
    //         mapping[i]=ip[i];
    //     ipfile.close();

    //     if(!check_output_format())
    //         exit(0);
    //     cout<<"Read output file, format OK"<<endl;

    //         }
        
    // }


    long long SportsLayout::cost_fn(){

        long long cost=0;

        for(int i=0;i<z;i++)
        {
           for(int j=0;j<z;j++) 
           {
                cost+=(long long)N[i][j]*(long long)T[mapping[i]-1][mapping[j]-1];
           }
        }

        return cost;
    }

    long long SportsLayout::next_cost_fn(int i, int j, long long cost){
        long long new_cost=cost;
        if(j<z){
            for(int k=0;k<z;k++){

                new_cost-=N[i][k]*T[mapping[i]-1][mapping[k]-1]+N[k][i]*T[mapping[k]-1][mapping[i]-1];
                new_cost+=N[i][k]*T[mapping[j]-1][mapping[k]-1]+N[k][i]*T[mapping[k]-1][mapping[j]-1];
            }
            for(int k=0;k<z;k++){

                new_cost-=N[j][k]*T[mapping[j]-1][mapping[k]-1]+N[k][j]*T[mapping[k]-1][mapping[j]-1];
                new_cost+=N[j][k]*T[mapping[i]-1][mapping[k]-1]+N[k][j]*T[mapping[k]-1][mapping[i]-1];
            }
            return new_cost;
        }
        else{
            for(int k=0;k<z;k++){

                new_cost-=N[i][k]*T[mapping[i]-1][mapping[k]-1]+N[k][i]*T[mapping[k]-1][mapping[i]-1];
                new_cost+=N[i][k]*T[mapping[j]-1][mapping[k]-1]+N[k][i]*T[mapping[k]-1][mapping[j]-1];
            }
            return new_cost;
        }
    }


    void SportsLayout::readInInputFile(string inputfilename)
    {
            fstream ipfile;
	        ipfile.open(inputfilename, ios::in);
            if (!ipfile) {
                cout << "No such file\n";
                exit( 0 );
            }
            else {
                

                ipfile>> time;
                ipfile >> z;
                ipfile >> l;

                if(z>l)
                {
                    cout<<"Number of N more than locations, check format of input file\n";
                    exit(0);
                }


            

            int **tempT;
            int **tempN;

          tempT = new int*[l];
         for (int i = 0; i < l; ++i)
            tempT[i] = new int[l];
        
        tempN = new int*[z];
        for (int i = 0; i < z; ++i)
            tempN[i] = new int[z];

        for(int i=0;i<z;i++)
        {
            for(int j=0;j<z;j++)
            ipfile>>tempN[i][j];
        }

        for(int i=0;i<l;i++)
        {
            for(int j=0;j<l;j++)
            ipfile>>tempT[i][j];
        }

        ipfile.close();

        T= tempT;
        N= tempN;
            }

    }

    void SportsLayout::write_to_file(string outputfilename){

         // Open the file for writing
    ofstream outputFile(outputfilename);

    // Check if the file is opened successfully
    if (!outputFile.is_open()) {
        cerr << "Failed to open the file for writing." << std::endl;
        exit(0);
    }

    for(int i=0;i<z;i++)
    outputFile<<mapping[i]<<" ";

    // Close the file
    outputFile.close();

    cout << "Allocation written to the file successfully." << endl;

    }

    void shuffle(int *a, int z, int l){
        int i,j;
        for( i=0 ; i <z; i++ ){
            j = rand() % l;
            swap(a[i], a[j]);
        }
    }

    void SportsLayout::compute_allocation()
    {
        //you can write your code here 
        //comment out following dummy code
        int curr_sample[l],i,a,b,j,size;
        long long cost,best=INT16_MAX,next_cost,temp;
        int best_mapping[l];
        vector<pair<int,int> > swap_list;
        bool flag;
        for(i=0;i<l;i++){
            curr_sample[i]=i+1;
        }
        for(i=0;i<1000;i++){
            shuffle(curr_sample, z, l);
            mapping=curr_sample;
            cost=cost_fn();
            if(cost<best){
                for(j=0;j<l;j++){
                    best_mapping[j]=curr_sample[j];
                }
                best=cost;
            }
            flag=false;
            while(!flag){
                printf("%lld\n",cost);
                swap_list.clear();
                next_cost=cost;
                for(a=0;a<z;a++){
                    for(b=0;b<l;b++){
                        if(a!=b){
                            temp=next_cost_fn(a,b,cost);
                            if(temp<next_cost){
                                next_cost=temp;
                                swap_list.clear();
                                swap_list.push_back(make_pair(a,b));
                            }
                            else if(temp==next_cost){
                                swap_list.push_back(make_pair(a,b));
                            }
                        }
                    }
                }
                if(next_cost==cost||swap_list.size()==0 ){
                    flag=true;
                }
                else{
                    size=swap_list.size();
                    j=rand()%size;
                    swap(mapping[swap_list[j].first],mapping[swap_list[j].second]);
                    cost=next_cost;
                    if(cost<best){
                        for(j=0;j<l;j++){
                            best_mapping[j]=mapping[j];
                        }
                        best=cost;
                    }                        
                }
            }
        }
    }


