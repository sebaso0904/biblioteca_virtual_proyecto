//richard prado
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <vector>
#include <algorithm>
using namespace std;

// -------------------- Usuario Login --------------------
class Usuario {
private:
    string usuario;
    string contrasena;
    string rol;

public:
    Usuario(string user, string pass, string r) : usuario(user), contrasena(pass), rol(r) {}

    string getUsuario() const { return usuario; }
    string getContrasena() const { return contrasena; }
    string getRol() const { return rol; }

    string toString() const {
        return usuario + " " + contrasena + " " + rol;
    }
};

class SistemaLogin {
private:
    vector<Usuario> listaUsuarios;
    string archivoUsuarios;

    void cargarUsuariosDesdeArchivo() {
        listaUsuarios.clear();
        ifstream archivo(archivoUsuarios);
        if (!archivo.is_open()) {
            cerr << "No se pudo abrir el archivo de usuarios.\n";
            return;
        }
        string user, pass, rol;
        while (archivo >> user >> pass >> rol) {
            listaUsuarios.push_back(Usuario(user, pass, rol));
        }
        archivo.close();
    }

    void guardarUsuarioEnArchivo(const Usuario& u) {
        ofstream archivo(archivoUsuarios, ios::app);
        if (archivo.is_open()) {
            archivo << u.toString() << endl;
            archivo.close();
        } else {
            cerr << "No se pudo escribir en el archivo.\n";
        }
    }

public:
    SistemaLogin(const string& archivo) : archivoUsuarios(archivo) {
        cargarUsuariosDesdeArchivo();
    }

    bool iniciarSesion(const string& user, const string& pass, string& rol) {
        for (const Usuario& u : listaUsuarios) {
            if (u.getUsuario() == user && u.getContrasena() == pass) {
                rol = u.getRol();
                return true;
            }
        }
        return false;
    }

    void crearUsuario() {
        system("cls");
        string user, pass, rol;
        int rol2;
        cout << "Ingrese nombre de usuario: ";
        cin >> user;
        cout << "Ingrese contrasena: ";
        cin >> pass;
        cout << "Ingrese rol (<1> administrador, <2> profesor, <3> estudiante): ";
        cin >> rol2;
        if(rol2==1){ 
        	rol = "administrador";
		}else if(rol2==2){
			rol = "profesor";
		}else{
			rol = "estudiante";
		}
        Usuario nuevo(user, pass, rol);
        listaUsuarios.push_back(nuevo);
        guardarUsuarioEnArchivo(nuevo);
        cout << "Usuario creado exitosamente.\n";
        getch();
    }
};

// -------------------- Biblioteca --------------------
class Libro {
public:
    string titulo;
    string estado;
    int cantidad;

    Libro(const string& t, const string& e, int c) : titulo(t), estado(e), cantidad(c) {}

    string toString() const {
        return titulo + "," + estado + "," + to_string(cantidad);
    }
};

class SistemaBiblioteca {
private:
    vector<Libro*> libros;

    void guardarLibrosEnArchivo() {
        ofstream archivo("libros.txt");
        if (archivo.is_open()) {
            for (Libro* libro : libros) {
                archivo << libro->toString() << endl;
            }
            archivo.close();
        } else {
            cerr << "No se pudo escribir en el archivo libros.txt\n";
        }
    }

    string minusculas(string texto) {
        transform(texto.begin(), texto.end(), texto.begin(), ::tolower);
        return texto;
    }

public:
    void cargarLibrosDesdeArchivo(const string& nombreArchivo) {
        ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            cerr << "No se pudo abrir el archivo de libros.\n";
            return;
        }

        string linea;
        while (getline(archivo, linea)) {
            if (!linea.empty()) {
                size_t p1 = linea.find(',');
                size_t p2 = linea.find(',', p1 + 1);
                if (p1 != string::npos && p2 != string::npos) {
                    string titulo = linea.substr(0, p1);
                    string estado = linea.substr(p1 + 1, p2 - p1 - 1);
                    int cantidad = stoi(linea.substr(p2 + 1));
                    libros.push_back(new Libro(titulo, estado, cantidad));
                }
            }
        }
        archivo.close();
        cout << "\nLibros cargados desde el archivo.\n";
    }

    void agregarLibro() {
        string titulo, estado;
        int cantidad;

        cin.ignore();
        cout << "Ingrese el titulo del libro: ";
        getline(cin, titulo);
        cout << "Ingrese el estado del libro (Disponible, Agotado): ";
        getline(cin, estado);
        cout << "Ingrese la cantidad: ";
        cin >> cantidad;

        libros.push_back(new Libro(titulo, estado, cantidad));

        ofstream archivo("libros.txt", ios::app);
        if (archivo.is_open()) {
            archivo << titulo << "," << estado << "," << cantidad << endl;
            archivo.close();
            cout << "Libro agregado y guardado exitosamente.\n";
        } else {
            cerr << "Error al abrir el archivo libros.txt.\n";
        }
    }

    void listarLibros() {
        if (libros.empty()) {
            cout << "No hay libros registrados.\n";
            return;
        }
        cout << "\n--- LISTA DE LIBROS ---\n";
        for (size_t i = 0; i < libros.size(); i++) {
            cout << i + 1 << ". " << libros[i]->titulo
                 << " | Estado: " << libros[i]->estado
                 << " | Cantidad: " << libros[i]->cantidad << endl;
        }
    }

    void prestarLibro() {
        if (libros.empty()) {
            cout << "No hay libros disponibles para prestar.\n";
            return;
        }

        listarLibros();

        int opcion;
        cout << "Seleccione el numero del libro a prestar: ";
        cin >> opcion;

        if (opcion < 1 || opcion > (int)libros.size()) {
            cout << "Opcion invalida.\n";
            return;
        }

        Libro* libro = libros[opcion - 1];

        if (libro->cantidad > 0) {
            libro->cantidad--;
            if (libro->cantidad == 0) {
                libro->estado = "Agotado";
            }
            guardarLibrosEnArchivo();
            cout << "Libro prestado exitosamente.\n";
        } else {
            cout << "No hay ejemplares disponibles de este libro.\n";
        }
    }

    void devolverLibro() {
        cin.ignore();
        string titulo;
        cout << "Ingrese el titulo del libro a devolver: ";
        getline(cin, titulo);
        string buscar = minusculas(titulo);

        bool encontrado = false;
        for (Libro* libro : libros) {
            if (minusculas(libro->titulo) == buscar) {
                libro->cantidad++;
                if (libro->estado == "Agotado") {
                    libro->estado = "Disponible";
                }
                guardarLibrosEnArchivo();
                cout << "Libro devuelto correctamente.\n";
                encontrado = true;
                break;
            }
        }

        if (!encontrado) {
            cout << "No se encontró un libro con ese titulo.\n";
        }
    }
};

// -------------------- Menú Principal --------------------
void menuBiblioteca(const string& rol, SistemaLogin& sistema) {
    SistemaBiblioteca biblioteca;
    biblioteca.cargarLibrosDesdeArchivo("libros.txt");

    int opcion;
    do {
        system("cls");
        cout << "\n--- MENU BIBLIOTECA ---\n";
        cout << "1. Listar libros\n";
        cout << "2. Prestar libro\n";
        cout << "3. Devolver libro\n";

        if (rol == "administrador") {
            cout << "4. Agregar libro\n";
            cout << "5. Crear usuario\n";
            cout << "6. Salir\n";
        } else {
            cout << "4. Salir\n";
        }

        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (rol == "administrador") {
            switch (opcion) {
                case 1: biblioteca.listarLibros(); break;
                case 2: biblioteca.prestarLibro(); break;
                case 3: biblioteca.devolverLibro(); break;
                case 4: biblioteca.agregarLibro(); break;
                case 5: sistema.crearUsuario(); break;
                case 6: cout << "Cerrando sesion...\n"; break;
                default: cout << "Opción inválida.\n"; break;
            }
        } else {
            switch (opcion) {
                case 1: biblioteca.listarLibros(); break;
                case 2: biblioteca.prestarLibro(); break;
                case 3: biblioteca.devolverLibro(); break;
                case 4: cout << "Cerrando sesion...\n"; break;
                default: cout << "Opción inválida.\n"; break;
            }
        }

        getch();

    } while ((rol == "administrador" && opcion != 6) || (rol != "administrador" && opcion != 4));
}

void inicioSesion(SistemaLogin& sistema) {
    string usuario, contrasena, rol;
    cout << "Usuario: ";
    cin >> usuario;
    cout << "Contrasena: ";
    cin >> contrasena;

    if (sistema.iniciarSesion(usuario, contrasena, rol)) {
        cout << "Sesion iniciada como " << rol << ".\n";
        getch();
        menuBiblioteca(rol, sistema);
    } else {
        cout << "Credenciales incorrectas.\n";
        getch();
    }
}

// -------------------- main --------------------
int main() {
    SistemaLogin sistema("usuarios.txt");
    int opcion;

    do {
        system("cls");
        cout << "\n--- MENU INICIAL ---\n";
        cout << "1. Iniciar sesion\n";
        cout << "2. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                system("cls");
                inicioSesion(sistema);
                break;
            case 2:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
                getch();
        }
    } while (opcion != 2);

    return 0;
}
