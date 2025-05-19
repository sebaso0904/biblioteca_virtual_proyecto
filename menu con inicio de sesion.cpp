//richard prado
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <memory>
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
        string user, pass, rol;
        cout << "Ingrese nombre de usuario: ";
        cin >> user;
        cout << "Ingrese contrasena: ";
        cin >> pass;
        cout << "Ingrese rol (administrador, profesor, estudiante): ";
        cin >> rol;
        Usuario nuevo(user, pass, rol);
        listaUsuarios.push_back(nuevo);
        guardarUsuarioEnArchivo(nuevo);
        cout << "Usuario creado exitosamente.\n";
    }
};

// -------------------- Biblioteca --------------------
class Libro {
public:
    string titulo;
    Libro(const string& t) : titulo(t) {}
};

class SistemaBiblioteca {
private:
    vector<Libro*> libros;
public:
    void agregarLibro() {
        string titulo;
        cout << "Ingrese el titulo del libro: ";
        cin.ignore();
        getline(cin, titulo);
        libros.push_back(new Libro(titulo));
        cout << "Libro agregado exitosamente.\n";
    }

    void listarLibros() {
        if (libros.empty()) {
            cout << "No hay libros registrados.\n";
            return;
        }
        cout << "\n--- LISTA DE LIBROS ---\n";
        for (size_t i = 0; i < libros.size(); i++) {
            cout << i + 1 << ". " << libros[i]->titulo << endl;
        }
    }
};

// -------------------- Menú Principal --------------------
void menuBiblioteca(const string& rol) {
    SistemaBiblioteca biblioteca;
    int opcion;

    do {
        cout << "\n--- MENU BIBLIOTECA ---\n";
        cout << "1. Listar libros\n";
        if (rol == "administrador") {
            cout << "2. Agregar libro\n";
            cout << "3. Salir\n";
        } else {
            cout << "2. Salir\n";
        }

        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (rol == "administrador") {
            switch (opcion) {
                case 1: biblioteca.listarLibros(); break;
                case 2: biblioteca.agregarLibro(); break;
                case 3: cout << "Cerrando sesión...\n"; break;
                default: cout << "Opcion invalida.\n"; break;
            }
        } else {
            switch (opcion) {
                case 1: biblioteca.listarLibros(); break;
                case 2: cout << "Cerrando sesión...\n"; break;
                default: cout << "Opcion invalida.\n"; break;
            }
        }
    } while ((rol == "administrador" && opcion != 3) || (rol != "administrador" && opcion != 2));
}

// -------------------- main --------------------
int main() {
    SistemaLogin sistema("usuarios.txt");
    int opcion;

    do {
        cout << "\n--- MENU INICIAL ---\n";
        cout << "1. Iniciar sesion\n";
        cout << "2. Crear usuario\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                string usuario, contrasena, rol;
                cout << "Usuario: ";
                cin >> usuario;
                cout << "Contrasena: ";
                cin >> contrasena;

                if (sistema.iniciarSesion(usuario, contrasena, rol)) {
                    cout << "Sesion iniciada como " << rol << ".\n";
                    menuBiblioteca(rol);
                } else {
                    cout << "Credenciales incorrectas.\n";
                }
                break;
            }
            case 2:
                sistema.crearUsuario();
                break;
            case 3:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }
    } while (opcion != 3);

    return 0;
}
