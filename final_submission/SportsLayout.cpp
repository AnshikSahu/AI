#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <random>
// #include <boost/random.hpp>
// #include <boost/random/normal_distribution.hpp>
#include <ctime>
#include <cmath>
#include <time.h>
#include <algorithm>
#include <climits>

using namespace std;

#include "SportsLayout.h"

    SportsLayout::SportsLayout(string inputfilename)
    {
          
        readInInputFile(inputfilename);
        mapping= vector<int> (l,0);

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
                new_cost-=(long long)N[i][k]*(long long)T[mapping[i]-1][mapping[k]-1]+(long long)N[k][i]*(long long)T[mapping[k]-1][mapping[i]-1];
                if(k==i){continue;}
                new_cost-=(long long)N[j][k]*(long long)T[mapping[j]-1][mapping[k]-1]+(long long)N[k][j]*(long long)T[mapping[k]-1][mapping[j]-1];
            }
            swap(mapping[i],mapping[j]);
            for(int k=0;k<z;k++){
                new_cost+=(long long)N[i][k]*(long long)T[mapping[i]-1][mapping[k]-1]+(long long)N[k][i]*(long long)T[mapping[k]-1][mapping[i]-1];
                if(k==i){continue;}
                new_cost+=(long long)N[j][k]*(long long)T[mapping[j]-1][mapping[k]-1]+(long long)N[k][j]*(long long)T[mapping[k]-1][mapping[j]-1];
            }
            swap(mapping[i],mapping[j]);
            return new_cost;
        }
        else{
            for(int k=0;k<z;k++){
                new_cost-=(long long)N[i][k]*(long long)T[mapping[i]-1][mapping[k]-1]+(long long)N[k][i]*(long long)T[mapping[k]-1][mapping[i]-1];
            }
            swap(mapping[i],mapping[j]);
            for(int k=0;k<z;k++){
                new_cost+=(long long)N[i][k]*(long long)T[mapping[i]-1][mapping[k]-1]+(long long)N[k][i]*(long long)T[mapping[k]-1][mapping[i]-1];
            }
            swap(mapping[i],mapping[j]);
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
        for(int i=0;i<z;i++){
            N[i][i]=0;
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

    for(int i=0;i<z;i++){
    outputFile<<mapping[i]<<" ";
    // cout<<mapping[i]<<" ";
    }
    // cout<<endl;
    cout<<c1<<endl;
    // Close the file
    outputFile.close();

    cout << "Allocation written to the file successfully." << endl;

    }

    void shuffle(int *a, int z, int l) {
        std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
        std::normal_distribution<> nd(static_cast<double>(z) / 6, std::sqrt(3 * l));

        double k = nd(rng);
        k = std::abs(k);
        int j2 = static_cast<int>(k);
        j2 = j2 % l;
        j2 += 3;

        for (int i = 0; i < j2; i++) {
            int j = std::rand() % z;
            int j1 = (j + std::rand()) % l;
            std::swap(a[j], a[j1]);
        }
    }
    void shuffle2(int *a, int z, int l){
        int i,j;
        for( i=l-1 ; i >0; i-- ){
            // cout<<"Hello"<<endl;
            j = rand() % (i+1);
            // k = rand() %10;
            // if(k<4){
                swap(a[i],a[j]);
            // }
        }
    }

    void SportsLayout::compute_allocation()
    {
        // vector<int> greedy_sample(l,0);
        vector<pair<int,int> > rand_nbrs;
        int nbr = z*l-z;
        if(nbr >= 4000 ){
            for(int x11=0;x11<z;x11++){
                for(int x12=x11+1;x12<l;x12++){
                    rand_nbrs.push_back(make_pair(x11,x12));
                }
            }
        }
        time_t start_time, end_time;
        float time_limit;
        if(z*l <= 40000){
            time_limit = time * 60 - 1;
        }
        else{
            time_limit = time * 60 - 2.5;
        }
        start_time = std::time(&start_time);
        //you can write your code here 
        //comment out following dummy code
        int curr_sample[l],i,a,b,j,size;
        long long cost,best=INT64_MAX,next_cost,temp;
        int best_mapping[l];
        vector<pair<int,int> > swap_list;
        bool flag;
        for(i=0;i<l;i++){
            curr_sample[i]=i+1;
        }
        if(time_limit >= 10){
        for(i=5;i<z-1;i++){
            int idx = i;
            long long sum = 0;
            for(int x1 = 0;x1<z;x1++){
                sum += (long long)(N[x1][i] + N[i][x1] )* (long long)T[curr_sample[x1]-1][curr_sample[idx]-1];
            }
            for(int x2 = i+1;x2<l;x2++){
                int temp_sum = 0;
                for(int x1 = 0;x1<z;x1++){
                    temp_sum += (long long)(N[x1][i] + N[i][x1] )* (long long)T[curr_sample[x1]-1][curr_sample[x2]-1];
                }
                if(temp_sum < sum){
                    idx = x2;
                    sum = temp_sum;
                }
            }
            swap(curr_sample[i],curr_sample[idx]);
        }}
        for(int i=0;i<l;i++){
            best_mapping[i] = curr_sample[i];
        }
        // cout << "Greedy done" << endl;
        // cout<<" "<<cost_fn()<<endl;
        int iter = 0;
        while (std::time(&end_time) - start_time < time_limit) {
            // cout<<iter<<" Hill "<<endl;
            iter++;
        // for(int i=0;i<1000;i++){
            // cout<<"Iteration "<<iter<<endl;
            if(iter%7==1 or iter%7==2 or iter%7==3){
            for(int i=0;i<l;i++){
                curr_sample[i]=best_mapping[i];
            }
            shuffle(curr_sample,z,l);
            }
            else{
            shuffle2(curr_sample,z,l);
            }            
            for(j=0;j<l;j++){
                mapping[j]=curr_sample[j];
            }
            // cout<<endl;
            cost=cost_fn();
            if(cost<best){
                for(j=0;j<l;j++){
                    best_mapping[j]=curr_sample[j];
                }
                best=cost;
                // cout<<"cost: "<<cost<<endl;
            }
            flag=false;
            while(!flag && std::time(&end_time) - start_time < time_limit){
                swap_list.clear();
                next_cost=cost;
                int rise = 0;
                int i2 = 0;
                if(nbr < 6000){
                for(a=0;a<z;a++){
                    for(b=a+1;b<l;b++){
                            // swap(mapping[a],mapping[b]);
                            temp=next_cost_fn(a,b,cost);
                            // swap(mapping[a],mapping[b]);
                            if(temp<next_cost){
                                next_cost=temp;
                                swap_list.clear();
                                swap_list.push_back(make_pair(a,b));
                                rise++;
                            }
                            else if(temp==next_cost){
                                swap_list.push_back(make_pair(a,b));
                            }
                    }
                }
                }
                else{
                    int sz = rand_nbrs.size();
                    for(int i=sz-1;i>0;i--){
                        int j = rand()%(i+1);
                        swap(rand_nbrs[i],rand_nbrs[j]);
                    }
                    for(int y = 0; y < sz; y++){
                        if((rise && y>300) || (y>3000)) break;
                        a = rand_nbrs[y].first;
                        b = rand_nbrs[y].second;
                        temp=next_cost_fn(a,b,cost);
                        if(temp<next_cost){
                            next_cost=temp;
                            swap_list.clear();
                            swap_list.push_back(make_pair(a,b));
                            rise++;
                        }
                        else if(temp==next_cost){
                            swap_list.push_back(make_pair(a,b));
                        }
                    }
                }

                if(next_cost==cost){
                    flag=true;
                }
                else{
                    size=swap_list.size();
                    j=rand()%size;
                    swap(mapping[swap_list[j].first],mapping[swap_list[j].second]);
                    // cout<<"Swapped "<<swap_list[j].first<<" "<<swap_list[j].second<<endl;
                    cost=next_cost;
                    if(cost<best){
                        for(j=0;j<l;j++){
                            best_mapping[j]=mapping[j];
                        }
                        best=cost;
                        // cout<<best<<endl;
                    }                        
                }
            }
            end_time = std::time(&end_time);
            c1 = best;
        }
        
        for(int i=0;i<l;i++){
            mapping[i]=best_mapping[i];
        }
    }