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

  /* Inicjowanie generatora liczb pseudolosowych czasem to bardzo zly pomysl.
   * To sie zapewne sprawdza w przypadku tworzenia gier itp. ale nie w przypadku
   * obliczen. 1. W takim przypadku nie jest Pan w stanie powtorzyc symulacji
   * danej symulacji drugi raz (bo nie zapamaientuje Pan wartosci seed).
   * 2. Uruchamiajac wiele symulacji jednoszesnie (w celu zebrania statystyki)
   * na klastrze np., wiele set osobnych runow zleconych do kolejki uruchomi sie
   * jednoczesnie z tym samym seedem generatora, wiec zamiast 100 roznych symulacji
   * ma Pan 100 razy te sama. A nawet jesli nie, to generator bedzie inicjowany
   * wartosciami bardzo bliskimi sobie.
   *
   * Generator inicjujemy duzym losowym int'em
   */
    srand (780428172);

    int srednia_dana = 1;
    long double odchylenie_standardowe_dane = 0.1;
    int a = 0;
    int b = 0;
    // Wysttarczy jeden licznik, c zawsze wynosi N-b. kiedy przestajemy
    // inkrementowac b, c zawsze bedzie rowne N/2
//     int c = 0;
    int znak = 1;

    for (int i = 0 ; i < N ; i++){
        // Ta instrukcja nic nie robi
//         a = rand()%2;

        a=0;
        if (b == N/2){
            a = 1;
        }//else{
//         if (c == N/2){
//             a = 0;
//         }

        // Powyzsze mozna jeszcze bardziej zwiezle zapisac jako (ternary operator)
//         a = (b == N/2) ? 1 : 0;

        /* jezli mamy tylko dwie opcje, warto uzyc domyslnie jednej a druga
         * wstawic blok 'if'. Instrukcja else jest wykonaniem skoku bezwarunkwego
         * jezeli test w 'if' jest false. Taka instrukcja sie nie optymalizuje
         * zbyt dobrze (czytaj: wcaje), wiec kod dzial szybciej bez bloku else.
         * Patrzac z punktu widzenia wydajnosci nalezy tak konstruowac bloki if/else,
         * aby ten kod ktory oczekujemy ze bedzie sie czesciej wykonywal byl w bloku 'if'
         */
        znak = 1;
        if ( a == 0){
            znak = -1;
            b++;
        }
//         else{
//             znak = 1;
//             c++;
//         }
        /* Nalezy unikac powtarzania sie kodu. Jezeli gdzies wystepuja
         * powtorzenia, to znak ze mozna tam zastosowac jaka optymalizacje
         * algorytmu albo wyodrebnic kod do funkcji. Kompilator zazwyczaj bedzie
         * w stanie lepiej zoptymalizowac kod przy kompilacji.
         */
        x[i] = srednia_dana + znak * odchylenie_standardowe_dane;
        y[i] = srednia_dana + znak * odchylenie_standardowe_dane;
        z[i] = srednia_dana + znak * odchylenie_standardowe_dane;
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

void Srednia(){

    srednia_x = suma_x/N;
    srednia_y = suma_y/N;
    srednia_z = suma_z/N;

}

void OdchylenieStandardowe(){
    float a = 0;
    // Wykonuje Pan 3*N - 3 niepotrzebnych operacji dzielenia
    float avg_x = suma_x/N;
    double avg_y = suma_y/N;
    long double avg_z = suma_z/N;

    for (int i = 0 ; i < N ; i++){
        odchylenie_standardowe_x += pow(x[i] - avg_x , 2);
        odchylenie_standardowe_y += pow(y[i] - avg_y , 2);
        // w przypadku kwadratow, jezeli wyrazenie nie jest zbyt rozwlekle
        // warto zrezygnowac z pow(), rowniez ze wzgledow wydajnosciowych.
        // Proste mnozenie bedzie szybsze
        odchylenie_standardowe_z += (z[i] - avg_z)*(z[i] - avg_z);
    }
    
    odchylenie_standardowe_x = sqrt(odchylenie_standardowe_x/N);
    odchylenie_standardowe_y = sqrt(odchylenie_standardowe_y/N);
    odchylenie_standardowe_z = sqrt(odchylenie_standardowe_z/N);

}

void Dane(){

    Suma();
    Srednia();
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
