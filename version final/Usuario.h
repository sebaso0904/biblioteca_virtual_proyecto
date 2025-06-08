#ifndef USUARIO_H
#define USUARIO_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <conio.h>
#include <string>
using namespace std;

class Usuario
{
protected:
	char Cc[15];
	char Nombre[20];
	char correo[30];
	char contrasena[30];
	char tipo[20];
	Usuario* sig;
public:
	Usuario(const char* cc, const char* nombre, const char* correoUsuario, 
			const char* pass, const char* tip)
	{
		strcpy(Cc, cc);
		strcpy(Nombre, nombre);
		strcpy(correo, correoUsuario);
		strcpy(contrasena, pass);
		strcpy(tipo, tip);
		sig = nullptr;
	}
	virtual void registroUsuario() = 0;
	virtual void actualizarUsuario() = 0;
	virtual void verAndIdentificarUsuario() = 0;
	virtual void guardarUsuario() = 0;
	virtual void abrirUsuario() = 0;
	virtual char* getTipo() = 0; 
	
	const char* getCc() const {
		return Cc;
	}
	
	const char* getNombre() const {
		return Nombre;
	}
	
	const char* getCorreo() const {
		return correo;
	}
	
	const char* getContrasena() const {
		return contrasena;
	}
	
	Usuario* getSig() const {
		return sig;
	}
	
	void setSig(Usuario* siguiente) { 
		sig = siguiente; 
	}
	
	void setNombre(const char* nuevoNombre) { 
		strcpy(Nombre, nuevoNombre); 
	}
	
	void setCorreo(const char* nuevoCorreo) { 
		strcpy(correo, nuevoCorreo); 
	}
	
	void setContrasena(const char* nuevaContrasena) { 
		strcpy(contrasena, nuevaContrasena); 
	}
	
	virtual ~Usuario() {}
};

class Estudiante : public Usuario {
private: 
	static Estudiante* cab;	
public:
	static void inicializar() {
		cab = nullptr; 
	}
	
	static void setCabeza(Estudiante* nuevaCabeza) {
		cab = nuevaCabeza;
	}
	
	static Estudiante* obtenerCabeza() {
		return cab;
	}
	
	Estudiante(const char* cc, const char* nombre, const char* correoUsuario, const char* pass,
			   const char* tip)
		: Usuario(cc, nombre, correoUsuario, pass, tip) {}
	
	char* getTipo() override {
		return (char*)"Estudiante";
	}
	
	void registroUsuario() override {
		char cc[15], nom[20], correoUsuario[30], pass[30];
		
		cout << "=== REGISTRO DE ESTUDIANTE ===\n";
		cout << "Digite la cedula: "; cin >> cc;
		cout << "Digite el nombre: "; cin >> nom;
		cout << "Digite el correo: "; cin >> correoUsuario;
		cout << "Digite la contraseña: "; cin >> pass;
		
		Estudiante* nuevo = new Estudiante(cc, nom, correoUsuario, pass, "Estudiante");
		
		if (cab == nullptr) {
			cab = nuevo;
		} else {
			Estudiante* temp = cab;
			while (temp->getSig() != nullptr) {
				temp = (Estudiante*)temp->getSig();
			}
			temp->setSig(nuevo);
		}
		
		cout << "\nEstudiante registrado exitosamente.\n";
		cout << "Cedula: " << nuevo->getCc() << "\n";
		cout << "Nombre: " << nuevo->getNombre() << "\n";
		cout << "Correo: " << nuevo->getCorreo() << "\n";
		guardarUsuario();
		getch();
	}
	
	void actualizarUsuario() override {
		if (cab == nullptr) {
			cout << "No hay registros para modificar.\n";
			getch();
			return;
		}
		
		char ccBuscado[15];
		cout << "Ingrese la cedula del Estudiante que desea modificar: ";
		cin >> ccBuscado;
		char TipoEstu[20] = "Estudiante";
		Estudiante* temp = cab;
		bool encontrado = false;
		
		while (temp != nullptr) {
			if (strcmp(temp->getCc(), ccBuscado) == 0 && strcmp(temp->getTipo(), TipoEstu) == 0) {
				cout << "\nRegistro encontrado:\n";
				cout << "Cedula: " << temp->getCc() << "\n";
				cout << "Nombre actual: " << temp->getNombre() << "\n";
				cout << "Correo actual: " << temp->getCorreo() << "\n";
				cout << "contrasena actual: " << temp->getContrasena() << "\n";
				
				char nuevoCorreo[30], nuevaContrasena[30];
				cout << "Ingrese el nuevo correo: ";
				cin >> nuevoCorreo;
				cout << "Ingrese la nueva contraseña: ";
				cin >> nuevaContrasena;
				
				temp->setCorreo(nuevoCorreo);
				temp->setContrasena(nuevaContrasena);
				
				cout << "\nRegistro del estudiante actualizado correctamente.\n";
				guardarUsuario();
				encontrado = true;
				break;
			}
			temp = (Estudiante*)temp->getSig();
		}
		
		if (!encontrado) {
			cout << "\nNo se encontro el registro.\n";
		}
		
		getch();
	}
	
	void verAndIdentificarUsuario() override {
		char ccBuscado[15];
		cout << "Ingrese la cedula del Estudiante que deseas ver: ";
		cin >> ccBuscado;
		char TipoEstu[20] = "Estudiante";
		Estudiante* temp = cab;
		bool encontrado = false;
		
		while (temp != nullptr) {
			if (strcmp(temp->getCc(), ccBuscado) == 0 && strcmp(temp->getTipo(), TipoEstu) == 0) {
				cout << "\nRegistro encontrado:\n";
				cout << "Cedula: " << temp->getCc() << "\n";
				cout << "Nombre actual: " << temp->getNombre() << "\n";
				cout << "Correo actual: " << temp->getCorreo() << "\n";
				cout << "contrasena actual: " << temp->getContrasena() << "\n";
				encontrado = true;
				break;
			}
			temp = (Estudiante*)temp->getSig();
		}
		
		if (!encontrado) {
			cout << "\nNo se encontró el registro.\n";
		}
		getch();
	}
	
	void abrirUsuario() override {
		ifstream archivo("ESTUDIANTES.txt");
		if (!archivo.is_open()) {
			cout << "No se pudo abrir el archivo de estudiantes.\n";
			getch();
			return;
		}
		
		// Limpiar lista existente
		while (cab != nullptr) {
			Estudiante* temp = cab;
			cab = (Estudiante*)cab->getSig();
			delete temp;
		}
		
		string linea;
		while (getline(archivo, linea)) {
			if (linea.empty()) continue;
			size_t pos = 0;
			string campos[5];
			int campo = 0;
			
			// Parsear línea separada por '|'
			string temp_linea = linea;
			while ((pos = temp_linea.find('|')) != string::npos && campo < 4) {
				campos[campo++] = temp_linea.substr(0, pos);
				temp_linea.erase(0, pos + 1);
			}
			campos[campo] = temp_linea;
			
			// Verificar que tenemos 5 campos y es estudiante
			if (campo == 4 && campos[4] == "Estudiante") {
				Estudiante* nuevo = new Estudiante(campos[0].c_str(), campos[1].c_str(), 
												   campos[2].c_str(), campos[3].c_str(), 
												   campos[4].c_str());
				if (cab == nullptr) {
					cab = nuevo;
				} else {
					Estudiante* aux = cab;
					while (aux->getSig() != nullptr) {
						aux = (Estudiante*)aux->getSig();
					}
					aux->setSig(nuevo);
				}
			}
		}
		archivo.close();
		cout << "Estudiantes cargados exitosamente desde ESTUDIANTES.txt.\n";
		getch();
	}
	
	void guardarUsuario() override {
		// Reescribir todo el archivo con los datos actuales
		ofstream archivo("ESTUDIANTES.txt");
		if (!archivo.is_open()) {
			cout << "Error al abrir archivo ESTUDIANTES.txt para guardar.\n";
			return;
		}
		
		Estudiante* temp = cab;
		while (temp != nullptr) {
			archivo << temp->getCc() << "|" << temp->getNombre() << "|" 
				<< temp->getCorreo() << "|" << temp->getContrasena() << "|" 
				<< temp->getTipo() << endl;
			temp = (Estudiante*)temp->getSig();
		}
		
		archivo.close();
		cout << "Estudiantes guardados exitosamente en ESTUDIANTES.txt.\n";
	}
};

class Profesor : public Usuario {
private: 
	static Profesor* cab;	
public:
	static void inicializar() {
		cab = nullptr;
	}
	
	static Profesor* obtenerCabeza() {
		return cab;
	}
	
	static void setCabeza(Profesor* nuevaCabeza) {
		cab = nuevaCabeza;
	}
	
	Profesor(const char* cc, const char* nombre, const char* correoUsuario, const char* pass,
			 const char* tip)
		: Usuario(cc, nombre, correoUsuario, pass, tip) {}
	
	char* getTipo() override {
		return (char*)"Profesor";
	}
	
	void registroUsuario() override {
		char cc[15], nom[20], correoUsuario[30], pass[30];
		
		cout << "=== REGISTRO DE PROFESOR ===\n";
		cout << "Digite la cedula: "; cin >> cc;
		cout << "Digite el nombre: "; cin >> nom;
		cout << "Digite el correo: "; cin >> correoUsuario;
		cout << "Digite la contraseña: "; cin >> pass;
		
		Profesor* nuevo = new Profesor(cc, nom, correoUsuario, pass, "Profesor");
		
		if (cab == nullptr) {
			cab = nuevo;
		} else {
			Profesor* temp = cab;
			while (temp->getSig() != nullptr) {
				temp = (Profesor*)temp->getSig();
			}
			temp->setSig(nuevo);
		}
		
		cout << "\nProfesor registrado exitosamente.\n";
		cout << "Cedula: " << nuevo->getCc() << "\n";
		cout << "Nombre: " << nuevo->getNombre() << "\n";
		cout << "Correo: " << nuevo->getCorreo() << "\n";
		guardarUsuario();
		getch();
	}
	
	void actualizarUsuario() override {
		if (cab == nullptr) {
			cout << "No hay registros para modificar.\n";
			getch();
			return;
		}
		
		char ccBuscado[15];
		cout << "Ingrese la cedula del Profesor que desea modificar: ";
		cin >> ccBuscado;
		char TipoPro[20] = "Profesor";
		Profesor* temp = cab;
		bool encontrado = false;
		
		while (temp != nullptr) {
			if (strcmp(temp->getCc(), ccBuscado) == 0 && strcmp(temp->getTipo(), TipoPro) == 0) {
				cout << "\nRegistro encontrado:\n";
				cout << "Cedula: " << temp->getCc() << "\n";
				cout << "Nombre actual: " << temp->getNombre() << "\n";
				cout << "Correo actual: " << temp->getCorreo() << "\n";
				cout << "contrasena actual: " << temp->getContrasena() << "\n";
				
				char nuevoCorreo[30], nuevaContrasena[30];
				cout << "Ingrese el nuevo correo: ";
				cin >> nuevoCorreo;
				cout << "Ingrese la nueva contraseña: ";
				cin >> nuevaContrasena;
				
				temp->setCorreo(nuevoCorreo);
				temp->setContrasena(nuevaContrasena);
				
				cout << "\nRegistro del profesor actualizado correctamente.\n";
				guardarUsuario();
				encontrado = true;
				break;
			}
			temp = (Profesor*)temp->getSig();
		}
		
		if (!encontrado) {
			cout << "\nNo se encontró el registro.\n";
		}
		
		getch();
	}
	
	void verAndIdentificarUsuario() override {
		char ccBuscado[15];
		cout << "Ingrese la cedula del Profesor que desea ver: ";
		cin >> ccBuscado;
		char TipoPro[20] = "Profesor";
		Profesor* temp = cab;
		bool encontrado = false;
		
		while (temp != nullptr) {
			if (strcmp(temp->getCc(), ccBuscado) == 0 && strcmp(temp->getTipo(), TipoPro) == 0) {
				cout << "\nRegistro encontrado:\n";
				cout << "Cedula: " << temp->getCc() << "\n";
				cout << "Nombre actual: " << temp->getNombre() << "\n";
				cout << "Correo actual: " << temp->getCorreo() << "\n";
				cout << "contrasena actual: " << temp->getContrasena() << "\n";
				encontrado = true;
				break;
			}
			temp = (Profesor*)temp->getSig();
		}
		
		if (!encontrado) {
			cout << "\nNo se encontró el registro.\n";
		}
		getch();
	}
	
	void abrirUsuario() override {
		ifstream archivo("PROFESORES.txt");
		if (!archivo.is_open()) {
			cout << "No se pudo abrir el archivo de profesores.\n";
			getch();
			return;
		}
		
		// Limpiar lista existente
		while (cab != nullptr) {
			Profesor* temp = cab;
			cab = (Profesor*)cab->getSig();
			delete temp;
		}
		
		string linea;
		while (getline(archivo, linea)) {
			if (linea.empty()) continue;
			size_t pos = 0;
			string campos[5];
			int campo = 0;
			
			string temp_linea = linea;
			while ((pos = temp_linea.find('|')) != string::npos && campo < 4) {
				campos[campo++] = temp_linea.substr(0, pos);
				temp_linea.erase(0, pos + 1);
			}
			campos[campo] = temp_linea;
			
			// Verificar que tenemos 5 campos y es profesor
			if (campo == 4 && campos[4] == "Profesor") {
				Profesor* nuevo = new Profesor(campos[0].c_str(), campos[1].c_str(), 
											   campos[2].c_str(), campos[3].c_str(), 
											   campos[4].c_str());
				if (cab == nullptr) {
					cab = nuevo;
				} else {
					Profesor* aux = cab;
					while (aux->getSig() != nullptr) {
						aux = (Profesor*)aux->getSig();
					}
					aux->setSig(nuevo);
				}
			}
		}
		archivo.close();
		cout << "Profesores cargados exitosamente desde PROFESORES.txt.\n";
		getch();
	}
	
	void guardarUsuario() override {
		// Reescribir todo el archivo con los datos actuales
		ofstream archivo("PROFESORES.txt");
		if (!archivo.is_open()) {
			cout << "Error al abrir archivo PROFESORES.txt para guardar.\n";
			return;
		}
		
		Profesor* temp = cab;
		while (temp != nullptr) {
			archivo << temp->getCc() << "|" << temp->getNombre() << "|" 
				<< temp->getCorreo() << "|" << temp->getContrasena() << "|" 
				<< temp->getTipo() << endl;
			temp = (Profesor*)temp->getSig();
		}
		
		archivo.close();
		cout << "Profesores guardados exitosamente en PROFESORES.txt.\n";
	}
};

class Admin : public Usuario {
private: 
	static Admin* cab;
	int tipoUsuario;	
public:
	static void inicializar() {
		cab = nullptr; 
	}
	
	static Admin* obtenerCabeza() {
		return cab;
	}
	
	static void setCabeza(Admin* nuevaCabeza) {
		cab = nuevaCabeza;
	}
	
	Admin(const char* cc, const char* nombre, const char* correoUsuario, const char* pass,
		  const char* tip)
		: Usuario(cc, nombre, correoUsuario, pass, tip) {}
	
	char* getTipo() override {
		return (char*)"Admin";
	}
	
	void registroUsuario() override {
		char continuar = 's';
		while (continuar == 's' || continuar == 'S') {
			system("cls");
			cout << "=== REGISTRO DE USUARIOS (ADMIN) ===\n";
			cout << "1. Registrar Estudiante\n";
			cout << "2. Registrar Profesor\n";
			cout << "3. Registrar Admin\n";
			cout << "4. Volver al menu\n";
			cout << "Seleccione el tipo de usuario a registrar: ";
			cin >> tipoUsuario;
			
			char cc[15], nom[20], correoUsuario[30], pass[30];
			switch(tipoUsuario) {
			case 1: {
				cout << "=== REGISTRO DE ESTUDIANTE (POR ADMIN) ===\n";
				cout << "Digite la cedula: "; cin >> cc;
				cout << "Digite el nombre: "; cin >> nom;
				cout << "Digite el correo: "; cin >> correoUsuario;
				cout << "Digite la contraseña: "; cin >> pass;
				Estudiante* nuevo = new Estudiante(cc, nom, correoUsuario, pass, "Estudiante");
				Estudiante* cabEst = Estudiante::obtenerCabeza();
				
				if (cabEst == nullptr) {
					Estudiante::setCabeza(nuevo);
				} else {
					Estudiante* temp = cabEst;
					while (temp->getSig() != nullptr) {
						temp = (Estudiante*)temp->getSig();
					}
					temp->setSig(nuevo);
				}
				cout << "\nEstudiante registrado exitosamente por Admin.\n";
				cout << "Cedula: " << nuevo->getCc() << "\n";
				cout << "Nombre: " << nuevo->getNombre() << "\n";
				cout << "Correo: " << nuevo->getCorreo() << "\n";
				cout << "contrasena: " << nuevo->getContrasena() << "\n";
				nuevo->guardarUsuario(); // Guarda en ESTUDIANTES.txt
				
				cout << "\n¿Desea continuar con otro registro Admin? <s/n>: ";
				cin >> continuar;
				break;
			}
			case 2: {
				cout << "=== REGISTRO DE PROFESOR (POR ADMIN) ===\n";
				cout << "Digite la cedula: "; cin >> cc;
				cout << "Digite el nombre: "; cin >> nom;
				cout << "Digite el correo: "; cin >> correoUsuario;
				cout << "Digite la contraseña: "; cin >> pass;
				Profesor* nuevo = new Profesor(cc, nom, correoUsuario, pass, "Profesor");
				Profesor* cabProf = Profesor::obtenerCabeza();
				
				if (cabProf == nullptr) {
					Profesor::setCabeza(nuevo);
				} else {
					Profesor* temp = cabProf;
					while (temp->getSig() != nullptr) {
						temp = (Profesor*)temp->getSig();
					}
					temp->setSig(nuevo);
				}
				cout << "\nProfesor registrado exitosamente por Admin.\n";
				cout << "Cedula: " << nuevo->getCc() << "\n";
				cout << "Nombre: " << nuevo->getNombre() << "\n";
				cout << "Correo: " << nuevo->getCorreo() << "\n";
				cout << "contrasena: " << nuevo->getContrasena() << "\n";
				nuevo->guardarUsuario(); // Guarda en PROFESORES.txt
				
				cout << "\n¿Desea continuar con otro registro Admin? <s/n>: ";
				cin >> continuar;
				break;
			}
			case 3: {
				cout << "=== REGISTRO DE ADMIN (POR ADMIN) ===\n";
				cout << "Digite la cedula: "; cin >> cc;
				cout << "Digite el nombre: "; cin >> nom;
				cout << "Digite el correo: "; cin >> correoUsuario;
				cout << "Digite la contraseña: "; cin >> pass;
				
				Admin* nuevo = new Admin(cc, nom, correoUsuario, pass, "Admin");
				
				if (cab == nullptr) {
					cab = nuevo;
				} else {
					Admin* temp = cab;
					while (temp->getSig() != nullptr) {
						temp = (Admin*)temp->getSig();
					}
					temp->setSig(nuevo);
				}
				
				cout << "\nAdmin registrado exitosamente.\n";
				cout << "Cedula: " << nuevo->getCc() << "\n";
				cout << "Nombre: " << nuevo->getNombre() << "\n";
				cout << "Correo: " << nuevo->getCorreo() << "\n";
				cout << "contrasena: " << nuevo->getContrasena() << "\n";
				guardarUsuario(); // Guarda en ADMINS.txt
				
				cout << "\n¿Desea continuar con otro registro Admin? <s/n>: ";
				cin >> continuar;
				break;
			}
			case 4:{
				return;
			}
			default:
					cout << "Opción inválida.\n";
					continue;
			}
		}
	}
	
	void actualizarUsuario() override {
		while(true) {
			cout << "=== ACTUALIZAR USUARIOS (ADMIN) ===\n";
			cout << "1. Actualizar Estudiante\n";
			cout << "2. Actualizar Profesor\n";
			cout << "3. Actualizar Admin\n";
			cout << "4. Devolver al menu\n";
			cout << "Seleccione opción: ";
			int opcion;
			cin >> opcion;
			
			switch(opcion) {
			case 1: {
				Estudiante temp("", "", "", "", "Estudiante");
				temp.actualizarUsuario();
				break;
			}
			case 2: {
				Profesor temp("", "", "", "", "Profesor");
				temp.actualizarUsuario();
				break;
			}
			case 3: {
				if (cab == nullptr) {
					cout << "No hay administradores registrados para modificar.\n";
					getch();
					break;
				}
				
				char ccBuscado[15];
				cout << "Ingrese la cedula del Admin que desea modificar: ";
				cin >> ccBuscado;
				char TipoAdmin[20] = "Admin";
				Admin* temp = cab;
				bool encontrado = false;
				
				while (temp != nullptr) {
					if (strcmp(temp->getCc(), ccBuscado) == 0 && strcmp(temp->getTipo(), TipoAdmin) == 0) {
						cout << "\nRegistro encontrado:\n";
						cout << "Cedula: " << temp->getCc() << "\n";
						cout << "Nombre actual: " << temp->getNombre() << "\n";
						cout << "Correo actual: " << temp->getCorreo() << "\n";
						cout << "contrasena actual: " << temp->getContrasena() << "\n";
						
						char nuevoCorreo[30], nuevaContrasena[30];
						cout << "Ingrese el nuevo correo: ";
						cin >> nuevoCorreo;
						cout << "Ingrese la nueva contraseña: ";
						cin >> nuevaContrasena;
						
						temp->setCorreo(nuevoCorreo);
						temp->setContrasena(nuevaContrasena);
						
						cout << "\nRegistro del admin actualizado correctamente.\n";
						guardarUsuario();
						encontrado = true;
						break;
					}
					temp = (Admin*)temp->getSig();
				}
				
				if (!encontrado) {
					cout << "\nNo se encontró el registro del admin.\n";
				}
				getch();
				break;
			}
			case 4: {
				return;
			}
			default:
				cout << "Opción inválida.\n";
				break;
			}	
		}
	}
	
	void verAndIdentificarUsuario() override {
		int opcion;
		cout << "=== VER USUARIOS (ADMIN) ===\n";
		cout << "1. Ver todos los usuarios\n";
		cout << "2. Buscar usuario específico\n";
		cout << "Seleccione opción: ";
		cin >> opcion;
		
		switch(opcion) {
		case 1: {
			cout << "\n=== TODOS LOS USUARIOS ===\n";
			
			cout << "\n--- ESTUDIANTES ---\n";
			Estudiante* tempEst = Estudiante::obtenerCabeza();
			if (tempEst == nullptr) {
				cout << "No hay estudiantes registrados.\n";
			} else {
				while (tempEst != nullptr) {
					cout << "Cedula: " << tempEst->getCc() << " | ";
					cout << "Nombre: " << tempEst->getNombre() << " | ";
					cout << "Correo: " << tempEst->getCorreo() << " | ";
					cout << "Tipo: " << tempEst->getTipo() << "\n";
					tempEst = (Estudiante*)tempEst->getSig();
				}
			}
			
			cout << "\n--- PROFESORES ---\n";
			Profesor* tempProf = Profesor::obtenerCabeza();
			if (tempProf == nullptr) {
				cout << "No hay profesores registrados.\n";
			} else {
				while (tempProf != nullptr) {
					cout << "Cedula: " << tempProf->getCc() << " | ";
					cout << "Nombre: " << tempProf->getNombre() << " | ";
					cout << "Correo: " << tempProf->getCorreo() << " | ";
					cout << "Tipo: " << tempProf->getTipo() << "\n";
					tempProf = (Profesor*)tempProf->getSig();
				}
			}
			
			cout << "\n--- ADMINISTRADORES ---\n";
			Admin* tempAdmin = cab;
			if (tempAdmin == nullptr) {
				cout << "No hay administradores registrados.\n";
			} else {
				while (tempAdmin != nullptr) {
					cout << "Cedula: " << tempAdmin->getCc() << " | ";
					cout << "Nombre: " << tempAdmin->getNombre() << " | ";
					cout << "Correo: " << tempAdmin->getCorreo() << " | ";
					cout << "Tipo: " << tempAdmin->getTipo() << "\n";
					tempAdmin = (Admin*)tempAdmin->getSig();
				}
			}
			break;
		}
		case 2: {
			char ccBuscado[15];
			cout << "Ingrese la cedula del usuario que desea buscar: ";
			cin >> ccBuscado;
			bool encontrado = false;
			
			// Buscar en estudiantes
			Estudiante* tempEst = Estudiante::obtenerCabeza();
			while (tempEst != nullptr && !encontrado) {
				if (strcmp(tempEst->getCc(), ccBuscado) == 0) {
					cout << "\n=== USUARIO ENCONTRADO ===\n";
					cout << "Cedula: " << tempEst->getCc() << "\n";
					cout << "Nombre: " << tempEst->getNombre() << "\n";
					cout << "Correo: " << tempEst->getCorreo() << "\n";
					cout << "Tipo: " << tempEst->getTipo() << "\n";
					encontrado = true;
				}
				tempEst = (Estudiante*)tempEst->getSig();
			}
			
			// Buscar en profesores
			Profesor* tempProf = Profesor::obtenerCabeza();
			while (tempProf != nullptr && !encontrado) {
				if (strcmp(tempProf->getCc(), ccBuscado) == 0) {
					cout << "\n=== USUARIO ENCONTRADO ===\n";
					cout << "Cedula: " << tempProf->getCc() << "\n";
					cout << "Nombre: " << tempProf->getNombre() << "\n";
					cout << "Correo: " << tempProf->getCorreo() << "\n";
					cout << "Tipo: " << tempProf->getTipo() << "\n";
					encontrado = true;
				}
				tempProf = (Profesor*)tempProf->getSig();
			}
			
			// Buscar en admins
			Admin* tempAdmin = cab;
			while (tempAdmin != nullptr && !encontrado) {
				if (strcmp(tempAdmin->getCc(), ccBuscado) == 0) {
					cout << "\n=== USUARIO ENCONTRADO ===\n";
					cout << "Cedula: " << tempAdmin->getCc() << "\n";
					cout << "Nombre: " << tempAdmin->getNombre() << "\n";
					cout << "Correo: " << tempAdmin->getCorreo() << "\n";
					cout << "Tipo: " << tempAdmin->getTipo() << "\n";
					encontrado = true;
				}
				tempAdmin = (Admin*)tempAdmin->getSig();
			}
			
			if (!encontrado) {
				cout << "\nNo se encontró el usuario con cedula: " << ccBuscado << "\n";
			}
			break;
		}
		default:
			cout << "Opción inválida.\n";
			break;
		}
		getch();
	}
	
	void guardarUsuario() override {
		// Reescribir todo el archivo con los datos actuales de admins
		ofstream archivo("ADMINS.txt");
		if (!archivo.is_open()) {
			cout << "Error al abrir archivo ADMINS.txt para guardar.\n";
			return;
		}
		
		Admin* temp = cab;
		while (temp != nullptr) {
			archivo << temp->getCc() << "|" << temp->getNombre() << "|" 
				<< temp->getCorreo() << "|" << temp->getContrasena() << "|" 
				<< temp->getTipo() << endl;
			temp = (Admin*)temp->getSig();
		}
		
		archivo.close();
		cout << "Administradores guardados exitosamente en ADMINS.txt.\n";
	}
	
	void abrirUsuario() override {
		cout << "=== CARGANDO TODOS LOS USUARIOS (ADMIN) ===\n";
		
		// Cargar estudiantes
		Estudiante tempEst("", "", "", "", "Estudiante");
		tempEst.abrirUsuario();
		
		// Cargar profesores  
		Profesor tempProf("", "", "", "", "Profesor");
		tempProf.abrirUsuario();
		
		// Cargar administradores
		ifstream archivo("ADMINS.txt");
		if (!archivo.is_open()) {
			cout << "No se pudo abrir el archivo de administradores (puede que no exista aún).\n";
		} else {
			// Limpiar lista existente de admins
			while (cab != nullptr) {
				Admin* temp = cab;
				cab = (Admin*)cab->getSig();
				delete temp;
			}
			
			string linea;
			while (getline(archivo, linea)) {
				if (linea.empty()) continue;
				size_t pos = 0;
				string campos[5];
				int campo = 0;
				
				string temp_linea = linea;
				while ((pos = temp_linea.find('|')) != string::npos && campo < 4) {
					campos[campo++] = temp_linea.substr(0, pos);
					temp_linea.erase(0, pos + 1);
				}
				campos[campo] = temp_linea;
				
				// Verificar que tenemos 5 campos y es admin
				if (campo == 4 && campos[4] == "Admin") {
					Admin* nuevo = new Admin(campos[0].c_str(), campos[1].c_str(), 
											 campos[2].c_str(), campos[3].c_str(), 
											 campos[4].c_str());
					if (cab == nullptr) {
						cab = nuevo;
					} else {
						Admin* aux = cab;
						while (aux->getSig() != nullptr) {
							aux = (Admin*)aux->getSig();
						}
						aux->setSig(nuevo);
					}
				}
			}
			archivo.close();
			cout << "Administradores cargados exitosamente desde ADMINS.txt.\n";
		}
		
		cout << "\nTodos los usuarios han sido cargados exitosamente.\n";
		getch();
	}
	
	// Funciones adicionales específicas para el admin
	void eliminarUsuario() {
		cout << "=== ELIMINAR USUARIOS (ADMIN) ===\n";
		cout << "1. Eliminar Estudiante\n";
		cout << "2. Eliminar Profesor\n";
		cout << "3. Eliminar Admin\n";
		cout << "4. Volver al menu\n";
		cout << "Seleccione opción: ";
		int opcion;
		cin >> opcion;
		
		char ccBuscado[15];
		bool encontrado = false;
		
		switch(opcion) {
		case 1: {
			cout << "Ingrese la cedula del Estudiante a eliminar: ";
			cin >> ccBuscado;
			
			Estudiante* cabEst = Estudiante::obtenerCabeza();
			if (cabEst == nullptr) {
				cout << "No hay estudiantes registrados.\n";
				break;
			}
			
			// Si es el primer elemento
			if (strcmp(cabEst->getCc(), ccBuscado) == 0) {
				Estudiante::setCabeza((Estudiante*)cabEst->getSig());
				delete cabEst;
				encontrado = true;
				cout << "Estudiante eliminado exitosamente.\n";
			} else {
				Estudiante* anterior = cabEst;
				Estudiante* actual = (Estudiante*)cabEst->getSig();
				
				while (actual != nullptr) {
					if (strcmp(actual->getCc(), ccBuscado) == 0) {
						anterior->setSig(actual->getSig());
						delete actual;
						encontrado = true;
						cout << "Estudiante eliminado exitosamente.\n";
						break;
					}
					anterior = actual;
					actual = (Estudiante*)actual->getSig();
				}
			}
			
			if (encontrado) {
				Estudiante temp("", "", "", "", "Estudiante");
				temp.guardarUsuario();
			} else {
				cout << "No se encontró el estudiante con cedula: " << ccBuscado << "\n";
			}
			break;
		}
		case 2: {
			cout << "Ingrese la cedula del Profesor a eliminar: ";
			cin >> ccBuscado;
			
			Profesor* cabProf = Profesor::obtenerCabeza();
			if (cabProf == nullptr) {
				cout << "No hay profesores registrados.\n";
				break;
			}
			
			// Si es el primer elemento
			if (strcmp(cabProf->getCc(), ccBuscado) == 0) {
				Profesor::setCabeza((Profesor*)cabProf->getSig());
				delete cabProf;
				encontrado = true;
				cout << "Profesor eliminado exitosamente.\n";
			} else {
				Profesor* anterior = cabProf;
				Profesor* actual = (Profesor*)cabProf->getSig();
				
				while (actual != nullptr) {
					if (strcmp(actual->getCc(), ccBuscado) == 0) {
						anterior->setSig(actual->getSig());
						delete actual;
						encontrado = true;
						cout << "Profesor eliminado exitosamente.\n";
						break;
					}
					anterior = actual;
					actual = (Profesor*)actual->getSig();
				}
			}
			
			if (encontrado) {
				Profesor temp("", "", "", "", "Profesor");
				temp.guardarUsuario();
			} else {
				cout << "No se encontró el profesor con cedula: " << ccBuscado << "\n";
			}
			break;
		}
		case 3: {
			cout << "Ingrese la cedula del Admin a eliminar: ";
			cin >> ccBuscado;
			
			if (cab == nullptr) {
				cout << "No hay administradores registrados.\n";
				break;
			}
			
			// Si es el primer elemento
			if (strcmp(cab->getCc(), ccBuscado) == 0) {
				Admin* temp = cab;
				cab = (Admin*)cab->getSig();
				delete temp;
				encontrado = true;
				cout << "Administrador eliminado exitosamente.\n";
			} else {
				Admin* anterior = cab;
				Admin* actual = (Admin*)cab->getSig();
				
				while (actual != nullptr) {
					if (strcmp(actual->getCc(), ccBuscado) == 0) {
						anterior->setSig(actual->getSig());
						delete actual;
						encontrado = true;
						cout << "Administrador eliminado exitosamente.\n";
						break;
					}
					anterior = actual;
					actual = (Admin*)actual->getSig();
				}
			}
			
			if (encontrado) {
				guardarUsuario();
			} else {
				cout << "No se encontró el administrador con cedula: " << ccBuscado << "\n";
			}
			break;
		}
		case 4:
			return;
		default:
			cout << "Opción inválida.\n";
			break;
		}
		getch();
	}
};

Estudiante* Estudiante::cab = nullptr;
Profesor* Profesor::cab = nullptr;
Admin* Admin::cab = nullptr;

#endif
