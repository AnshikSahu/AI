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
        mapping=vector<int>(z,0);

    }

    bool SportsLayout::check_output_format()
    {
        int i=0,m=0;
        for(;i<10;i++)
        {
            if(costs[i]<costs[m]){
                m=i;
            }
        }
        mapping=mappings[m];
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


    long long SportsLayout::cost_fn(int n){

        long long cost=0;

        for(int i=0;i<z;i++)
        {
           for(int j=0;j<z;j++) 
           {
                cost+=(long long)N[i][j]*(long long)T[mappings[n][i]-1][mappings[n][j]-1];
           }
        }

        return cost;
    }

    long long SportsLayout::next_cost_fn(int i, int j,int n){
        long long new_cost=costs[n];
        if(j<z){
            for(int k=0;k<z;k++){
                new_cost-=N[i][k]*T[mappings[n][i]-1][mappings[n][k]-1]+N[k][i]*T[mappings[n][k]-1][mappings[n][i]-1];
                new_cost-=N[j][k]*T[mappings[n][j]-1][mappings[n][k]-1]+N[k][j]*T[mappings[n][k]-1][mappings[n][j]-1];
            }
            swap(mappings[n][i],mappings[n][j]);
            for(int k=0;k<z;k++){
                new_cost+=N[i][k]*T[mappings[n][i]-1][mappings[n][k]-1]+N[k][i]*T[mappings[n][k]-1][mappings[n][i]-1];
                new_cost+=N[j][k]*T[mappings[n][j]-1][mappings[n][k]-1]+N[k][j]*T[mappings[n][k]-1][mappings[n][j]-1];
            }
            swap(mappings[n][i],mappings[n][j]);
            return new_cost;
        }
        else{
            for(int k=0;k<z;k++){
                new_cost-=N[i][k]*T[mappings[n][i]-1][mappings[n][k]-1]+N[k][i]*T[mappings[n][k]-1][mappings[n][i]-1];
            }
            swap(mappings[n][i],mappings[n][j]);
            for(int k=0;k<z;k++){
                new_cost+=N[i][k]*T[mappings[n][i]-1][mappings[n][k]-1]+N[k][i]*T[mappings[n][k]-1][mappings[n][i]-1];
            }
            swap(mappings[n][i],mappings[n][j]);
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

    void SportsLayout::shuffle(int n, int z, int l){
        int i,j;
        for( i=0 ; i <z; i++ ){
            j = rand() % l;
            swap(mappings[n][i], mappings[n][j]);
        }
    }

    pair<pair<pair<int,int>,pair<int,int> >,pair<long long,long long> > SportsLayout::champions(int n){
        pair<int,int> swap1,swap2;
        long long cost1=LLONG_MAX,cost2=LLONG_MAX,temp;
        int i,j;
        for(i=0;i<z;i++){
            for(j=i+1;j<l;j++){
                temp=next_cost_fn(i,j,n);
                if(temp<cost1){
                    cost2=cost1;
                    swap2=swap1;
                    cost1=temp;
                    swap1=make_pair(i,j);
                }
                else if(temp<cost2 and temp!=cost1){
                    cost2=temp;
                    swap2=make_pair(i,j);
                }
            }
        }
        return make_pair(make_pair(swap1,swap2),make_pair(cost1,cost2));
    }


    void SportsLayout::compute_allocation()
    {
        //you can write your code here 
        //comment out following dummy code
        int i,a,b,j,size,k;
        vector<int> next_beam[20];
        long long next_costs[20],temp,best=LLONG_MAX;
        for(k=0;k<10000;k++){
            for(i=0;i<10;i++){
                mappings[i]=vector<int>();
                for(j=0;j<l;j++){
                    mappings[i].push_back(j+1);
                }
                shuffle(i,z,l);
                costs[i]=cost_fn(i);
            }
            for(i=0;i<2;i++){
                // cout<<i<<endl;
                for(j=0;j<10;j++){
                    pair<pair<pair<int,int>,pair<int,int> >,pair<long long,long long> > temp=champions(j);
                    swap(mappings[j][temp.first.first.first],mappings[j][temp.first.first.second]);
                    vector<int> copy;
                    for(a=0;a<l;a++){
                        copy.push_back(mappings[j][a]);
                    }
                    next_beam[2*j]=copy;
                    next_costs[2*j]=temp.second.first;
                    swap(mappings[j][temp.first.second.first],mappings[j][temp.first.second.second]);
                    next_beam[2*j+1]=mappings[j];
                    next_costs[2*j+1]=temp.second.second;
                }
                for(j=0;j<3;j++){
                    temp=LLONG_MAX;
                    b=-1;
                    for(a=j;a<20;a++){
                        if(next_costs[a]<temp){
                            temp=next_costs[a];
                            b=a;
                        }
                    }
                    swap(next_costs[j],next_costs[b]);
                    swap(next_beam[j],next_beam[b]);
                }
                for(j=0;j<3;j++){
                    mappings[j]=next_beam[j];
                    costs[j]=next_costs[j];
                }              
                j=3;
                while(j<7){
                    a=rand()%17+3;
                    if(next_costs[a]!=-1){
                        mappings[j]=next_beam[a];
                        costs[j]=next_costs[a];
                        next_costs[a]=-1;
                        j++;
                    }
                }
                shuffle(7,z,l);
                costs[7]=cost_fn(7);
                shuffle(8,z,l);
                costs[8]=cost_fn(8);
                shuffle(9,z,l);
                costs[9]=cost_fn(9);
            }
            for(i=0;i<10;i++){
                temp=LLONG_MAX;
                b=-1;
                for(j=i;j<10;j++){
                    if(costs[j]<temp){
                        temp=costs[j];
                        b=j;
                    }
                }
            }
            if(temp<best){
                best=temp;
                mapping=mappings[b];
            }
        }
    }
