#include <iostream>
#include <stdlib.h> 
#include <time.h>
#include <math.h>


using namespace std;

float * x = NULL;
double * y = NULL;
long double * z = NULL;
int N = 0;

float suma_x = 0;
double suma_y = 0;
long double suma_z = 0;

float srednia_x = 0;
double srednia_y = 0;
long double srednia_z = 0;

float odchylenie_standardowe_x = 0;
double odchylenie_standardowe_y = 0;
long double odchylenie_standardowe_z = 0;


void CreatingArray(){
    
    cout << "podaj rozmiar tablicy (parzysta liczba)" << endl;
    cin >> N;
    x = new float[N];
    y = new double[N];
    z = new long double[N];
}

void GeneratingArray(){

    srand (time(NULL));

    int srednia_dana = 1;
    float odchylenie_standardowe_dane = 0.1;
    int a = 0;
    int b = 0;
    int c = 0;

    for (int i = 0 ; i < N ; i++){

        a = rand()%2;

        if (b == N/2){
            a = 1;
        }
        if (c == N/2){
            a = 0;
        }

        if ( a == 0){
            x[i] = srednia_dana - odchylenie_standardowe_dane;
            y[i] = srednia_dana - odchylenie_standardowe_dane;
            z[i] = srednia_dana - odchylenie_standardowe_dane;
            b++;
        }
        else{
            x[i] = srednia_dana + odchylenie_standardowe_dane;
            y[i] = srednia_dana + odchylenie_standardowe_dane;
            z[i] = srednia_dana + odchylenie_standardowe_dane;
            c++;
        }
    }
}

void CoutArray(){
    cout << "array:" << endl;
    cout.precision(25);
    for (int i = 0 ; i < N ; i++){
        cout << fixed << x[i] << endl;
    }
}



void Suma(){

    for (int i = 0 ; i < N ; i++){

        suma_x += x[i];
        suma_y += y[i];
        suma_z += z[i];
    }
}

void Średnia(){

    srednia_x = suma_x/N;
    srednia_y = suma_y/N;
    srednia_z = suma_z/N;

}

void OdchylenieStandardowe(){
    float a = 0;

    for (int i = 0 ; i < N ; i++){
        odchylenie_standardowe_x += pow(x[i] - suma_x/N , 2);
        odchylenie_standardowe_y += pow(y[i] - suma_y/N , 2);
        odchylenie_standardowe_z += pow(z[i] - suma_z/N , 2);

    }
    
    odchylenie_standardowe_x = sqrt(odchylenie_standardowe_x/N);
    odchylenie_standardowe_y = sqrt(odchylenie_standardowe_y/N);
    odchylenie_standardowe_z = sqrt(odchylenie_standardowe_z/N);

}

void Dane(){

    Suma();
    Średnia();
    OdchylenieStandardowe();

}

void Output(){

    cout.precision(25);
    cout << "float: " << endl;
    cout << fixed << "Suma: "  << suma_x << endl;
    cout << fixed << "Srednia: " << srednia_x << endl;
    cout << fixed << "Odchylenie standardowe: " << odchylenie_standardowe_x << endl;

    cout.precision(25);
    cout << "double: " << endl;
    cout << fixed << "Suma: "  << suma_y << endl;
    cout << fixed << "Srednia: " << srednia_y << endl;
    cout << fixed << "Odchylenie standardowe: " << odchylenie_standardowe_y << endl;

    cout.precision(25);
    cout << "float: " << endl;
    cout << fixed << "Suma: "  << suma_z << endl;
    cout << fixed << "Srednia: " << srednia_z << endl;
    cout << fixed << "Odchylenie standardowe: " << odchylenie_standardowe_z << endl;

}
int main(){

    CreatingArray();
    GeneratingArray();
    Dane();
    Output();

    return 0;
}
