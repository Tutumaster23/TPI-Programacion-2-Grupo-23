
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "rlutil.h"
#include "Menus.h"

#include "Autor.h"

using namespace std;
using namespace rlutil;

Autor::Autor(){


    _idAutor = 0;
    strcpy(_nombre, "");
    strcpy(_apellido, "");
    strcpy(_nacionalidad, "");
    _estado = true;
}


Autor::Autor(int idAutor, const char* nombre, const char* apellido, const char* nacionalidad, bool estado){

    _idAutor = idAutor;
    strcpy(_nombre, nombre);
    strcpy(_apellido, apellido);
    strcpy(_nacionalidad, nacionalidad);
    _estado = estado;
}


int Autor::getAutorID(){ return _idAutor; }
void Autor::setAutorID(int idAutor){ _idAutor = idAutor; }

const char* Autor::getNombre(){ return _nombre; }
void Autor::setNombre(const char* nombre){ strcpy(_nombre, nombre); }

const char* Autor::getApellido(){ return _apellido; }
void Autor::setApellido(const char* apellido){ strcpy(_apellido, apellido); }

const char* Autor::getNacionalidad(){ return _nacionalidad; }
void Autor::setNacionalidad(const char* nacionalidad){ strcpy(_nacionalidad, nacionalidad); }

bool Autor::getEstado(){ return _estado; }
void Autor::setEstado(bool estado){ _estado = estado; }

void Autor::mostrar(int fila){

    if(_estado){
        locate(30, fila + 1);cout << "ID: " << _idAutor << endl;
        locate(30, fila + 2);cout << "Nombre: " << _nombre << endl;
        locate(30, fila + 3);cout << "Apellido: " << _apellido << endl;
        locate(30, fila + 4);cout << "Nacionalidad: " << _nacionalidad << endl;
        locate(30, fila + 5);cout << "-----------------------------" << endl;
    }
}

bool Autor::guardar(){

    FILE* pArchivo = fopen("Autores.dat", "ab");

    if(pArchivo == NULL){
        return false;
    }
    bool ok = fwrite(this, sizeof(Autor), 1, pArchivo);

    fclose(pArchivo);

    return ok;
}

int Autor::contarRegistros(){

    FILE* pArchivo = fopen("Autores.dat", "rb");

    if(pArchivo == NULL){

        return 0;
    }

    fseek(pArchivo, 0, SEEK_END);

    int cantidad = ftell(pArchivo) / sizeof(Autor);

   fclose(pArchivo);

    return cantidad;
}

Autor Autor::leer(int posicion){

    Autor autor;

    FILE* pArchivo = fopen("Autores.dat", "rb");

    if(pArchivo == NULL){

        return autor;
    }
    fseek(pArchivo, posicion * sizeof(Autor), SEEK_SET);

    fread(&autor, sizeof(Autor), 1, pArchivo);

    fclose(pArchivo);

    return autor;
}

int Autor::generarNuevoID(){

    int cantidad = contarRegistros();
    int maximo = 0;

    for(int i = 0; i < cantidad; i++){

        Autor autor = leer(i);

        if(autor.getAutorID() > maximo){

            maximo = autor.getAutorID();
        }
    }

    return maximo + 1;
}

int Autor::buscarporID(int id){
    int cant = contarRegistros();

    for(int i=0; i<cant; i++){
        Autor autor = leer(i);
        if(autor.getAutorID() == id && autor.getEstado()){
            return i;
        }
    }
    return -1;
}

void Autor::listar(){

    system("cls");

    int cantidad = contarRegistros();

    for(int i = 0; i < cantidad; i++){

        Autor autor = leer(i);

        autor.mostrar(5);
    }

    system("pause");
}

void Autor::listarOrdenadoPorApellido(){

    system("cls");
    int cantidad = contarRegistros();

    int alto = 10 + cantidad * 5 + 1;
    pantalla("LISTAR AUTORES", alto);

    if(cantidad == 0){
        locate(30, 10);
        cout << "No hay autores cargados." << endl;
        pausar(16);
        return;
    }

    Autor* autores = new Autor[cantidad];

    for(int i = 0; i < cantidad; i++){
        autores[i] = leer(i);
    }
    int y = 0;

    for(int i = 0; i < cantidad - 1; i++){


        for(int j = 0; j < cantidad - 1 - i; j++){

           if(strcmp(autores[j].getApellido(), autores[j + 1].getApellido()) > 0){
                Autor aux = autores[j];
                autores[j] = autores[j + 1];
                autores[j + 1] = aux;
            }
        }
    }

    for(int i = 0; i < cantidad; i++){
        autores[i].mostrar(10 + y * 5);
        y++;
    }

    delete[] autores;

    pausar(alto + 2);
}
