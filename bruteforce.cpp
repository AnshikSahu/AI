#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>

using namespace std;

void shuffle(vector<int> &arr, int n) {
    for (int i = n - 1; i >= 1; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

vector<vector<int>> transposed( vector<vector<int>> &vec){
    int rows = vec.size();
    int cols = vec[0].size();
    vector<vector<int>> transposed(cols, vector<int>(rows));
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            transposed[j][i] = vec[i][j];
        }
    }
    return transposed;
}

vector<vector<int>> matrix_mul( vector<vector<int>> &vec ,  vector<vector<int>> &vec2){
    int r1 = vec.size();
    int c1 = vec[0].size();
    int r2 = vec2.size();
    int c2 = vec2[0].size();
    assert(c1==r2);
    vector<vector<int>> res(r1, vector<int>(c2,0));
    for(int i=0;i<r1;i++){
        for(int j=0;j<c2;j++){
            for(int k=0;k<c1;k++){
                res[i][j] += vec[i][k] * vec2[k][j];
            }
        }
    }
    return res;
}

// pair<vector<vector<int>>,vector<vector<int>>> mat_map(vector<int> &mapping,int z){
//     int r = mapping.size();
//     vector<vector<int>> left(r, vector<int>(z,0));
//     vector<vector<int>> right(z, vector<int>(r,0));
//     for(int i=0;i<r;i++){
//         left[i][mapping[i]-1] = 1;
//         right[mapping[i]-1][i] = 1;
//     }
//     return {left,right};
// }

long long objective(vector<vector<int>> &locs, vector<vector<int>> &zones, vector<int> &mapping){
    int l = locs.size();
    int z = zones.size();
    vector<vector<int>> left(z, vector<int>(l,0));
    vector<vector<int>> right(l, vector<int>(z,0));
    for(int i=0;i<z;i++){
        right[mapping[i]-1][i] = 1;
        left[i][mapping[i]-1] = 1;
    }
    vector<vector<int>> res = matrix_mul(left,locs);
    res = matrix_mul(res,right);
    long long sum = 0;
    for(int i=0;i<z;i++){
        for(int j=0;j<z;j++){
            sum += res[i][j] * zones[i][j];
        }
    }
    return sum;
}

// void perm(vector<int> &a, int n, int k, int i,vector<vector<int>> &locs, vector<vector<int>> &zones)
// {
//     if(i == 0)
//     {
//         vector<int> temp;
//         for(int j=n; j<n+k; j++) temp.push_back(a[j]);
//         for(auto x  : temp){
//             cout<<x<<" ";
//         }
//         cout<<" : ";
//         cout<<objective(locs,zones,temp)<<endl;
//         return;
//     }

//     for(int j=0; j<n; j++)
//     {
//         swap(a[j], a[n-1]);
//         perm(a, n-1, k, i-1,locs,zones);
//         swap(a[j], a[n-1]);
//     }

// }

// void perm(vector<int> &a, int n, int k, int i)
// {
//     if(i == 0)
//     {
//         for(int j=n; j<n+k; j++) cout << a[j] << " ";
//         cout << endl;
//         return;
//     }

//     for(int j=0; j<n; j++)
//     {
//         swap(a[j], a[n-1]);
//         perm(a, n-1, k, i-1);
//         swap(a[j], a[n-1]);
//     }

// }

int main(){
    freopen("input.txt", "r", stdin);
    vector<vector<int>> zones;
    vector<vector<int>> locations;
    vector<int> mapping;
    int t,z,l;
    cin>>t>>z>>l;
    for(int i=0;i<z;i++){
        vector<int> temp;
        for(int j=0;j<z;j++){
            int x;
            cin>>x;
            temp.push_back(x);
        }
        zones.push_back(temp);
    }
    for(int i=0;i<l;i++){
        vector<int> temp;
        for(int j=0;j<l;j++){
            int x;
            cin>>x;
            temp.push_back(x);
        }
        locations.push_back(temp);
    }
    // vector<int> v1{1,3,5,4,2};
    // cout<<objective(locations,zones,v1)<<endl;
    for(int i=1;i<=l;i++){
        mapping.push_back(i);
    }
    // cout<<objective(locations,zones,mapping)<<endl;
    long long best = INT_MAX;
    vector<int> best_mapping;
    do{
        // for(auto x : mapping){
        //     cout<<x<<" ";
        // }
        // cout<<" : ";
        long long temp = objective(locations,zones,mapping);
        // cout<<temp<<endl;
        if(temp<best){
            best = temp;
            best_mapping = mapping;
        }
    }while(next_permutation(mapping.begin(),mapping.end()));
    for(auto x : best_mapping){
        cout<<x<<" ";
    }
    cout<<" : ";
    cout<<best<<endl;

}

