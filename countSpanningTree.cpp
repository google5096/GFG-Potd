#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

void printMatInt(vector<vector<int>> &mat, int n){
    for(auto row : mat){
        for(auto ele : row)
            cout<<ele<<"  ";
        cout<<endl;
    }
}
void printMatDoub(vector<vector<double>> &mat, int n){
    for(auto row : mat){
        for(auto ele : row)
            cout<<ele<<"  ";
        cout<<endl;
    }
}
double determinant(vector<vector<double>> &mat, int n){
    double det=1.0;
    // find pivot
    for(int i=0; i<n; i++){
        int pivot = i;
        
        for(int j=i+1; j<n; j++){
            if(fabs(mat[j][i] > mat[pivot][i]))
                pivot=j;
        }

        // swap rows
        if(i!=pivot){
            swap(mat[i], mat[pivot]);
            det *= -1;
        }
        // printMatDoub(mat, n);

        det *= mat[i][i];

        // eliminate below 
        for(int j=i+1; j<n; j++){
            double factor = mat[j][i] / mat[i][i];
            for(int k=i; k<n; k++){
                mat[j][k] = mat[j][k] - factor*mat[i][k];
            }
            // printMatDoub(mat, n);
        }
    }
    return det;
}

int countST(vector<vector<int>> &graph, int n){
    // create laplacian matrix
    vector<vector<int>> lap(n, vector<int>(n,0));
    
    for(int i=0; i<n; i++){
        int deg=0;
        for(int j=0; j<n; j++){
            if(graph[i][j]){
                deg++;
                if(i!=j)
                    lap[i][j] = -1;
            }
        }
        // assign deg to diagonal element
        lap[i][i]=deg;
    }
    // printMatInt(lap, n);
    // create minor matrix
    vector<vector<double>> minor(n-1, vector<double>(n-1));
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-1; j++){
            minor[i][j] = lap[i][j];
        }
    }
    // printMatDoub(minor, n-1);
    // Determinant 
    return (int)round(determinant(minor, n-1));
}

int main(){
    int v = 4;
     vector<vector<int>> graph = {
        {0, 1, 1, 1},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {1, 1, 1, 0}
    };

    int count = countST(graph, v);
    cout<<"counting of spanning tree  : "<<count;

    return 0;
}