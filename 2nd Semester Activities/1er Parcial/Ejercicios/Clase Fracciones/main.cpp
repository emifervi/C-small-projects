#include <iostream>
using namespace std;

#include "Fraccion.h"

int main()
{

    Fraccion fr1,fr2(3,4);
    cout<<"El valor de la fracci�n "<<fr1.getNum()<<"/"<<fr1.getDen()<<" es "<<fr1.CalcValorReal()<<endl;
    cout<<"El valor de la fracci�n "<<fr2.getNum()<<"/"<<fr2.getDen()<<" es "<<fr2.CalcValorReal()<<endl;

    return 0;
}
