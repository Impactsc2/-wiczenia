#include <iostream>
#include <stdlib.h> 
#include <math.h>


using namespace std;

double KahanSumAlghoritm(double array[] , int size){

    double sum = 0.0;
    double c = 0.0;

    for (int i = 0 ; i < size ; i++){
        
        double y = array[i] - c;
        double t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }

    return sum;
}

void ArrayDuplication(double array1[] , double array2[] , int size){

    for (int i = 0 ; i < size ; i++){

        array1[i] = array2[i];
    }
}

double * GeneratingArray(double array[] , int size){

    srand (time(NULL));

    const int mean_const = 1;
    const double standard_deviation_const = 0.1;
    int a = 0;
    int b = 0;
    int c = 0;
    int stop = 0;
    int sign = 0;

    for (int i = 0 ; i < size ; i++){
        
        if (stop == 0){
            
            a = rand()%2;
            
            if (b == 0.5*size){
                a = 1;
                stop = 1;
            }
            if (c == 0.5*size){
                a = 0;
                stop = 1;
            }
        }
        sign = (a == 0) ? 1 , c++ : -1 , b++;
        array[i] = mean_const + sign*standard_deviation_const;
    }

    return array;
}

int InputSize(){

    int size;

    cout << "pass the size of an array" << endl;
    cin >> size;

    return size;
}

double Mean(double sum , int size){

    double mean = 0.0;

    mean = sum/size;

    return mean;
}

double StandardDeviation(double array[] , int size , double mean){

    double standard_deviation = 0.0;

    for (int i = 0 ; i < size ; i++){

        array[i] = pow(array[i] - mean , 2);
    }
     standard_deviation = sqrt(KahanSumAlghoritm(array , size)/size);
    
    return standard_deviation;
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

    ArrayDuplication(array , GeneratingArray(array , size) , size);

    sum = KahanSumAlghoritm(array , size);
    mean = Mean(sum , size);
    standard_deviation = StandardDeviation(array , size , mean);

    cout.precision(30);
    cout << fixed << sum << endl;
    cout << fixed << mean << endl;
    cout << fixed << standard_deviation << endl;

    return 0;
}
