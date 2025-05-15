#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Usuario {
private:
    string usuario;
    string contrasena;

public:
    Usuario(string user, string pass) : usuario(user), contrasena(pass) {}

    string getUsuario() const {
        return usuario;
    }

    string getContrasena() const {
        return contrasena;
    }
};

class SistemaLogin {
private:
    vector<Usuario> listaUsuarios;

    void cargarUsuariosDesdeArchivo(const string& nombreArchivo) {
        ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            cout << "No se pudo abrir el archivo de usuarios.\n";
            return;
        }

        string user, pass;
        while (archivo >> user >> pass) {
            listaUsuarios.push_back(Usuario(user, pass));
        }

        archivo.close();
    }

public:
    SistemaLogin(const string& archivoCredenciales) {
        cargarUsuariosDesdeArchivo(archivoCredenciales);
    }

    bool iniciarSesion(const string& user, const string& pass) {
        for (const Usuario& u : listaUsuarios) {
            if (u.getUsuario() == user && u.getContrasena() == pass) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    SistemaLogin login("usuarios.txt");

    string usuario, contrasena;
    cout << "Usuario: ";
    cin >> usuario;
    cout << "Contrasena: ";
    cin >> contrasena;

    if (login.iniciarSesion(usuario, contrasena)) {
        cout << "Inicio de sesion exitoso.\n";
    } else {
        cout << "Credenciales incorrectas.\n";
    }

    return 0;
}
