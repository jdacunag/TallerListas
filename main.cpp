#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Nodo{
    char dato[20];
    Nodo *siguiente;
};

Nodo *primero, *ultimo, *actual, *nuevo;
void menu();


//Insertar elementos en la lista
void insertarLista(){
    system("cls");
    char dato[20];
    char respuesta;

    do {
        nuevo = new Nodo;
        cout << "Ingrese la palabra... ";
        cin >> dato;

        ofstream archivo;
        archivo.open("palabras.txt",ios::app);
    
        if(archivo.fail()){
            cout<<"No se pudo abrir el archivo";
            exit(1);
        }
        archivo<<dato<<endl;
        archivo.close();

        if (primero == NULL) {
            primero = new (Nodo);
            strcpy(nuevo->dato, dato);
            ultimo = primero;
        } else {
            actual = new (Nodo);
            ultimo->siguiente = actual;
            strcpy(actual->dato, dato);
            ultimo = actual;
        }
        ultimo->siguiente = NULL;

        cout<<"¿Desea ingresar otro elemento? (s/n): "<<endl;
        respuesta = getchar();
    } while (respuesta == 's');
    cout<<"Presione ENTER para continuar..."<<endl;
    getchar();
    menu();;
}

//Mostrar elementos de la lista
void mostrarLista(){
    system("cls");
    actual = primero;
    int i = 1;
    while(actual != NULL){
        cout<<""<<endl;
        cout<<i<<": "<<actual->dato<<endl;
        actual = actual->siguiente;    
        i++;
    }
    cout<<"Presione ENTER para continuar..."<<endl;
    getchar();
    menu();
}

//Buscar un elemento en la lista
void buscarLista(){
system("cls");
    char dato[20];
    int esta = 0;

    cout<<"Ingrese la palabra para buscar: ";
    cin>>dato;
    actual = primero;

    while(actual != NULL){
        if(strcmp(actual->dato,dato) == 0){
            esta = 1;
        }
        actual = actual->siguiente;
    }
    if(esta == 1){
      cout<<""<<endl;
      cout<<"Palabra "<<dato<<" se encuentra en la lista"<<endl;
    }
    else{
      cout<<""<<endl;
      cout<<"La palabra no se encuentra en la lista..."<<endl;
    }
    cout<<"Presione ENTER para continuar..."<<endl;
    cout<<""<<endl;
    getchar();
    menu();
}

//Eliminar un elemento de la lista
void eliminarLista(){
    system("cls");
    char dato[20];
    int eliminador = 0;

    ifstream salida;
    salida.open("palabras.txt",ios::in);
    ofstream entrada;
    entrada.open("temp.txt",ios::out);

    cout<<"Ingrese la palabra que desea eliminar: ";
    cout<<""<<endl;
    cin>>dato;
    actual = primero;
    
    while(actual != NULL && eliminador == 0){
        if(strcmp(actual->dato,dato) == 0){
            if (actual == primero){
              primero = primero->siguiente;
            }
            else{
              ultimo->siguiente = actual->siguiente;
            }
            delete(actual);
            eliminador = 1;

            if (eliminador == 0){
                ultimo = actual;
                actual = actual->siguiente;
            }
        }
    }
    if(eliminador == 1){
        cout<<"¡¡La palabra "<<dato<<" fue eliminada con exito!!"<<endl;
    }else{
        cout<<"La palabra "<<dato<<" no se encuentra en la lista"<<endl;
    }
    cout<<"Presione enter para continuar..."<<endl;
    getchar();
    menu();
}

void carga_Archivo(){
    ifstream archivo;
    archivo.open("palabras.txt",ios::in);
    if (archivo.fail()){
        cout<<"No se ha podido abrir el archivo";
        exit(1);
    }

    char dato[20];
    while (!archivo.eof()){
        archivo>>dato;
        if (!archivo.eof()){
            nuevo = new Nodo;
            strcpy(nuevo->dato,dato);
            if (primero == NULL){
                primero = nuevo;
                primero->siguiente = NULL;
                ultimo = primero;
            }else{
                ultimo->siguiente = nuevo;
                nuevo->siguiente = NULL;
                ultimo = nuevo;
            }
        }
    }archivo.close();
}

//Menu para elegir una accion
void menu(){
    system("cls");
    cout<<"¡¡Bienvenido usuario!!"<<endl;
    int opcion;
    cout<<endl<<"Elige el número de lo que deseas hacer..."<<endl;
   cout<<""<<endl;
   cout<<"1. Insertar elementos a la lista"<<endl<<"2. Mostrar elementos de la lista"<<endl<<"3. Buscar elementos en la lista"<<endl<<"4. Eliminar elementos de la lista"<<endl<<"5. Salir"<<endl;
    cout<<""<<endl;
    cin>>opcion;

    switch(opcion){
        case 1:
            insertarLista();
            break;
        case 2:
            mostrarLista();
            break;
        case 3:
            buscarLista();
            break;
        case 4:
            eliminarLista();
            break;
        case 5:
            cout<<"¡¡Vuelva pronto!!"<<endl;
            getchar();
            exit(0);
            break;
    }
}

int main(){
    carga_Archivo();
    menu();
}