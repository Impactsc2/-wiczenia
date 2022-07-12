#include <iostream>
#include <stdlib.h> 
#include <math.h>

using namespace std;


double urand(){
    return ((double) rand() / (double) RAND_MAX);
}

double KahanSumAlghoritm(double array[] , int size){

    double sum = 0;
    double c = (double)0;

    for (int i = 0 ; i < size ; i++){
        
        double y = array[i] - c;
        double t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }

    return sum;
}

void GeneratingArray(double array[] , int size){
    
    srand (780428172);

    const int MEAN = 1;
    const double STD_DEV = (double) 1 / (double) 10;
    int a, sign;
    int b = 0, c = 0, go_random = 1;
    int half_size = (double) size / (double) 2;

    for (int i = 0 ; i < size ; i++){
        
        if (go_random){           
            a = (int) 2 * urand();
        }
        
        sign = -1 + 2 * a; 

        b += 1 - a;

        c += a;

        if(go_random){

            go_random = ((b <= c) ? c : b) % half_size;

            a = (a > 0) ? 0 : 1;
        }

        array[i] = MEAN + sign * STD_DEV;
        
    }
}

int InputSize(){

    int size;

    cout << "pass the size of an array" << endl;
    cin >> size;

    return size;
}

double Mean(double sum , int size){

    double mean = 0.0;

    mean = sum / (double) size;

    return mean;
}

double StandardDeviation(double array[] , int size , double mean){

    double *local_array =  new double[size];

    double a;

    for (int i = 0 ; i < size ; i++){

        a = (array[i] - mean);
        local_array[i] = a*a;
    }
     
    
    return sqrt(KahanSumAlghoritm(local_array , size) / (double) size);
}

void CoutArray(double array[] , int size){

    for (int i = 0 ; i < size ; i++){
        cout.precision(30);
        cout << fixed << array[i] << endl;
    }
}



int main(){

    double *array;
    double sum;
    double mean;
    double standard_deviation;
    int size = InputSize();
    
    array = new double[size];

    GeneratingArray(array , size);

    sum = KahanSumAlghoritm(array , size);
    mean = Mean(sum , size);
    standard_deviation = StandardDeviation(array , size , mean);
    CoutArray(array, size);
    cout.precision(30);
    cout << fixed << sum << endl;
    cout << fixed << mean << endl;
    cout << fixed << standard_deviation << endl;

    return 0;
}
