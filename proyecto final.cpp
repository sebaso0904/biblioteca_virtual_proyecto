#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Usuario {
private:
    string usuario;
    string contrasena;
    string rol;

public:
    Usuario(string user, string pass, string r) : usuario(user), contrasena(pass), rol(r) {}

    string getUsuario() const {
        return usuario;
    }

    string getContrasena() const {
        return contrasena;
    }

    string getRol() const {
        return rol;
    }

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
        ofstream archivo(archivoUsuarios, ios::app); // modo append
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

int main() {
    SistemaLogin sistema("usuarios.txt");

    int opcion;
    do {
        cout << "\n--- MENU ---\n";
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
