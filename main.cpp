//richard prado
#include <iostream>
#include <vector>
#include <string>
#include "state.h"
using namespace std;

class Libro {
private:
    string titulo;
    string autor;
    int cantidad;
    Estado* estado;

public:
    Libro(string t, string a, int c) : titulo(t), autor(a), cantidad(c) {
        if (cantidad > 0) {
            estado = new Disponible();
        } else {
            estado = new Agotado();
        }
    }

    ~Libro() {
        delete estado;
    }

    string getTitulo() const { return titulo; }
    string getAutor() const { return autor; }
    int getCantidad() const { return cantidad; }

    void incrementarCantidad() {
        cantidad++;
        if (cantidad > 0) {
            cambiarEstado(new Disponible());
        }
    }

    void decrementarCantidad() {
        if (cantidad > 0) {
            cantidad--;
        }
        if (cantidad == 0) {
            cambiarEstado(new Agotado());
        }
    }

    void cambiarEstado(Estado* nuevoEstado) {
        delete estado;
        estado = nuevoEstado;
    }

    void devolverLibro() {
        estado->devolver(this);
    }
};

void Disponible::devolver(Libro* libro) {
    cout << "Libro devuelto correctamente: " << libro->getTitulo() << endl;
    libro->incrementarCantidad();
}

void Agotado::devolver(Libro* libro) {
    cout << "Libro devuelto. Ya está disponible nuevamente: " << libro->getTitulo() << endl;
    libro->incrementarCantidad();
}

class SistemaBiblioteca {
private:
    vector<Libro*> libros;

public:
    void agregarLibro(Libro* libro) {
        libros.push_back(libro);
    }

    void devolverLibro() {
        string titulo;
        cout << "Ingrese el titulo del libro a devolver: ";
        getline(cin, titulo);
        for (auto& libro : libros) {
            if (libro->getTitulo() == titulo) {
                libro->devolverLibro();
                return;
            }
        }
        cout << "Libro no encontrado." << endl;
    }

    void listarLibros() {
        for (auto& libro : libros) {
            cout << "Titulo: " << libro->getTitulo()
                 << ", Autor: " << libro->getAutor()
                 << ", Cantidad: " << libro->getCantidad() << endl;
        }
    }

    ~SistemaBiblioteca() {
        for (auto& libro : libros) {
            delete libro;
        }
    }
};

int main() {
    SistemaBiblioteca sistema;
    sistema.agregarLibro(new Libro("1984", "George Orwell", 0));
    sistema.agregarLibro(new Libro("El Principito", "Antoine de Saint-Exupéry", 2));

    int opcion;
    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Listar libros\n";
        cout << "2. Devolver libro\n";
        cout << "0. Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                sistema.listarLibros();
                break;
            case 2:
                sistema.devolverLibro();
                break;
            case 0:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion invalida\n";
        }
    } while (opcion != 0);

    return 0;
}
