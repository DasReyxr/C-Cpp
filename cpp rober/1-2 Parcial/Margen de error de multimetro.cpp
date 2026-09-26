#include<iostream>
#include <cmath>
using namespace std;
int main()
{
    int C = 6;
    int F = 11;
    float MarError = 0.0005; //0.0005
    float array[F][C] = {
        {4.2, 0.5, 0.07, 4.9, 4.9, 0.2},
        {4.4, 1.2, 0.1, 0.23, 0.23, 6.8},
        {5.5, 5.8, 0.2, 0.17, 0.17, 0.12},
        {4.2, 5.9, 0.14, 0.04, 0.04, 0.19},
        {4.7, 6.7, 0.3, 0.11, 0.11, 0.5},
        {3.5, 9.1, 0.13, 0.09, 0.09, 0.15},
        {4.0, 3.5, 0.31, 0.14, 0.14, 0.1},
        {2.5, 7.5, 0.15, 0.1, 0.1, 0.14},
        {4.7, 7.2, 0.2, 0.3, 0.3, 0.21},
        {5.4, 7.9, 0.5, 0.12, 0.12, 0.65},
        {4.0, 7.0, 1.6, 0.26, 0.26, 0.82}
    };
    float Error[F][C];
    float ErrorArr[F][C];
    for(int j = 0; j < F;j++){
    for(int i= 0; i < C;i++){
    Error[j][i] = array[j][i] -  (MarError*array[j][i]);
    ErrorArr[j][i] = array[j][i] +  (MarError*array[j][i]);
    }}
    for(int j = 0; j < F;j++){
    for (int i = 0; i < C;i++){
    cout <<"(" << round(Error[j][i]*10000)/10000 ;
    cout << " - " << round(ErrorArr[j][i]*10000)/10000 << ")";
    }
    cout << endl;
    }
}