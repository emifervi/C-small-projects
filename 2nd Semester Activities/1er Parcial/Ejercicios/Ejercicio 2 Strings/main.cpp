//Descripci�n: Analiza una lista de puntos para encontrar los m�s cercanos.
//Autor: Jos� Guilllermo Salda�a C�rdenas
//Fecha:11 enero 2018
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string frase,siglas="";
    cout << "Teclea la frase" << endl;
    getline(cin, frase);

    for(int i=0; i<frase.length();i++){
        if( i==0 || frase[i-1]==' ')
            siglas+=toupper(frase[i]);
    }
    cout<<"Las siglas son: "<<siglas;

    return 0;
}
