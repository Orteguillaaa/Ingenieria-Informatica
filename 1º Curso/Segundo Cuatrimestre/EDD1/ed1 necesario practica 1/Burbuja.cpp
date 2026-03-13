#include <iostream>

using namespace std;

int main()
{
    int datos [100];
    int ne; //contiene el número de datos que almacena el vector Datos

    cout<<"Introduce el número de datos a leer: ";
    cin>>ne;

    for (int i=0;i<ne;i++)
    {
        cout<<"Introduce el datos nº "<<i+1<<": ";
        cin>>datos[i];
    };

    cout<<endl;
    for (int i=0;i<ne;i++)
        cout<<datos[i]<<" ";
    cout<<endl;

    for(int i=0; i<ne; i++)
    {
        for(int j=i+1; j<ne; j++)
        {
            if (datos[i]>datos[j])
            {
                int tmp=datos[i];
                datos[i]=datos[j];
                datos[j]=tmp;
            }
        }

    }
    for (int i=0;i<ne;i++)
        cout<<datos[i]<<" ";
    cout<<endl;

    return 0;
}

