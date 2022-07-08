#include <iostream>
#include <stdlib.h> 
#include <math.h>

using namespace std;

double urand(){
    return ((double) rand() / (double) RAND_MAX);
}

double KahanSumAlghoritm(double array[] , int size){

    double sum = 0;
    double c = (double) 0;

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
    int half_size = size / 2;

    for (int i = 0 ; i < size ; i++){
        
        if(go_random){
            a = (int) 2 * urand();
        }

        sign = -1 + 2 * a;  // a=0 -> -1 (->c++) || a=1 -> +1 (->b++)

        b += 1 - a;

        c += a;

        if(go_random){
            // wynik z prawej bedzie 0 gdy b lub c beda rowne polowie size
            // dlatego sprawdzamy wieksza z nich
            // Ponizsze jest rownowazne z: zwroc reszte z dzielenia wiekszej
            // z b i c przez pol rozmiaru tablicy. Jezeli b lub c beda rowne
            // polowie tablicy wynik bedzie 0 (Uwaga, wynik rozniez moze byc
            // 0 gdy b i c sa rowne zero, dlatego ten test trzeba przeprowadzic
            // gdy ktoras z nich jest juz niezerowa)
            go_random = ((b <= c) ? c : b) % half_size;
            // nastepnie trzeba przerzucic a na przeciwna wartosc, bo od tej
            // pory go_random jest 0 i ten kod, ani urand, juz sie nie wykonaja
            a = (a > 0) ? 0 : 1;
        }
        
        array[i] = MEAN + sign * STD_DEV;
//        cout << "i=" << i << " gr=" << go_random << " a=" << a << " b=" << b << " c=" << c << " s=" << sign << " ar(i)=" << array[i] << endl;
    }
//     cout << " b=" << b << " c=" << c << endl;
}

int InputSize(){

    int size;

    cout << "pass the size of an array" << endl;
    cin >> size;

    return size;
}

double Mean(double sum , int size){
    return sum / (double) size;
    // dzielenie double przez int czasem potrafi zrobic psikusa
}

double StandardDeviation(double array[] , int size , double mean){

    for (int i = 0 ; i < size ; i++){

        array[i] = (array[i] - mean)*(array[i] - mean);
    }
    
    return sqrt(KahanSumAlghoritm(array , size)/size);
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

    cout.precision(30);
    cout << fixed << sum << endl;
    cout << fixed << mean << endl;
    cout << fixed << standard_deviation << endl;

    return 0;
}
