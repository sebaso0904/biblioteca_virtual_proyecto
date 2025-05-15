#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <conio.h>
using namespace std;

class Libro; // Declaracion adelantada

// Clase base Estado (interfaz)
class EstadoLibro {
public:
    virtual string getNombreEstado() const = 0;
    virtual void cambiarEstado(Libro& libro) = 0;
    virtual ~EstadoLibro() {}
};

// Clases concretas de estado
class Disponible : public EstadoLibro {
public:
    string getNombreEstado() const override {
        return "Disponible";
    }

    void cambiarEstado(Libro& libro) override;
};

class Prestado : public EstadoLibro {
public:
    string getNombreEstado() const override {
        return "Prestado";
    }

    void cambiarEstado(Libro& libro) override;
};

class Agotado : public EstadoLibro {
public:
    string getNombreEstado() const override {
        return "Agotado";
    }

    void cambiarEstado(Libro& libro) override {
        cout << "El libro ya esta agotado. No se puede cambiar su estado.\n";
    }
};

// Clase Libro
class Libro {
private:
    string titulo;
    EstadoLibro* estado;

public:
    Libro(string t, EstadoLibro* e) : titulo(t), estado(e) {}

    ~Libro() {
        delete estado;
    }

    string getTitulo() const {
        return titulo;
    }

    string getEstado() const {
        return estado->getNombreEstado();
    }

    void cambiarEstado() {
        estado->cambiarEstado(*this);
    }

    void setEstado(EstadoLibro* nuevoEstado) {
        delete estado;
        estado = nuevoEstado;
    }

    string serializar() const {
        return titulo + ";" + estado->getNombreEstado();
    }
};

// Implementacion de los cambios de estado
void Disponible::cambiarEstado(Libro& libro) {
    cout << "Cambiando de Disponible a Prestado...\n";
    libro.setEstado(new Prestado());
}

void Prestado::cambiarEstado(Libro& libro) {
    cout << "Cambiando de Prestado a Agotado...\n";
    libro.setEstado(new Agotado());
}

// Clase que maneja los libros
class GestorLibros {
private:
    vector<Libro*> libros;

    EstadoLibro* crearEstadoDesdeTexto(const string& estadoStr) {
        if (estadoStr == "Disponible") return new Disponible();
        if (estadoStr == "Prestado") return new Prestado();
        if (estadoStr == "Agotado") return new Agotado();
        return new Disponible(); // por defecto
    }

public:
    ~GestorLibros() {
        for (Libro* libro : libros) delete libro;
    }

    void inicializarLibros() {
        libros.push_back(new Libro("Cien Anios de Soledad", new Disponible()));
        libros.push_back(new Libro("El Principito", new Disponible()));
        libros.push_back(new Libro("1984", new Disponible()));
        libros.push_back(new Libro("Don Quijote", new Disponible()));
        libros.push_back(new Libro("Moby Dick", new Disponible()));
        libros.push_back(new Libro("Rayuela", new Disponible()));
        libros.push_back(new Libro("Hamlet", new Disponible()));
        libros.push_back(new Libro("La Odisea", new Disponible()));
        libros.push_back(new Libro("El Aleph", new Disponible()));
        libros.push_back(new Libro("La Metamorfosis", new Disponible()));
    }

    void mostrarLibros() {
        cout << "\n--- Lista de Libros ---\n";
        for (size_t i = 0; i < libros.size(); ++i) {
            cout << i + 1 << ". " << libros[i]->getTitulo()
                 << " - Estado: " << libros[i]->getEstado() << endl;
        }
    }

    void cambiarEstadoLibro(int indice) {
        if (indice < 1 || indice > libros.size()) {
            cout << "Indice invalido.\n";
            return;
        }
        libros[indice - 1]->cambiarEstado();
    }

    void guardarEnArchivo(const string& nombreArchivo) {
        ofstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            cerr << "No se pudo abrir el archivo para guardar.\n";
            return;
        }

        for (Libro* libro : libros) {
            archivo << libro->serializar() << endl;
        }

        archivo.close();
        cout << "Libros guardados en " << nombreArchivo << endl;
    }

    void cargarDesdeArchivo(const string& nombreArchivo) {
        ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            cerr << "No se pudo abrir el archivo para cargar.\n";
            return;
        }

        libros.clear();
        string linea;
        while (getline(archivo, linea)) {
            size_t pos = linea.find(';');
            if (pos != string::npos) {
                string titulo = linea.substr(0, pos);
                string estado = linea.substr(pos + 1);
                libros.push_back(new Libro(titulo, crearEstadoDesdeTexto(estado)));
            }
        }

        archivo.close();
        cout << "Libros cargados desde " << nombreArchivo << endl;
    }
};

// Programa principal
int main() {
    GestorLibros gestor;
    int opcion;

    cout << "Desea cargar libros desde archivo? (1=Si, 2=No): ";
    cin >> opcion;

    if (opcion == 1) {
        gestor.cargarDesdeArchivo("libros.txt");
    } else {
        gestor.inicializarLibros();
    }

    do {
        cout << "\n--- MENU LIBROS ---\n";
        cout << "1. Ver libros\n";
        cout << "2. Cambiar estado de un libro\n";
        cout << "3. Guardar en archivo\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
            	system("cls");
                gestor.mostrarLibros();
                getch();
                               
                break;
            case 2:
            	system("cls");
                int indice;
                gestor.mostrarLibros();
                cout << "Seleccione el libro a cambiar de estado: ";
                cin >> indice;
                gestor.cambiarEstadoLibro(indice);
                getch();
                break;
            case 3:
            	system("cls");
                gestor.guardarEnArchivo("libros.txt");
                getch();
                break;
            case 4:
                cout << "Saliendo...\n";
                
                break;
            default:
                cout << "Opcion invalida.\n";
                
        }
    } while (opcion != 4);

    return 0;
}
