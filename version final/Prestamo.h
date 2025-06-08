#ifndef PRESTAMO_H
#define PRESTAMO_H
#include "Libro.h"
#include "Usuario.h"
#include <fstream>
#include <string>
using namespace std;

extern Estudiante* obtenerCabezaEstudiantes();
extern Profesor* obtenerCabezaProfesores();
extern Admin* obtenerCabezaAdmins();
extern LibroDigital* obtenerCabezaLibrosDigitales();
extern LibroFisico* obtenerCabezaLibrosFisicos();

class Prestamo
{
private:
	static Prestamo* cab;
protected:
	char Titulo[50];        
	char Cc[15];
	char EstadoPrestamo[20];
	char tipoLibro[20];
	char tipoUsuario[20];
	Prestamo* sig;
public:
	static void inicializar() {
		cab = nullptr; 
	}
	
	static Prestamo* obtenerCabeza() {
		return cab;
	}
	
	static void setCabeza(Prestamo* nuevaCabeza) {
		cab = nuevaCabeza;
	}
	
	Prestamo(const char* titulo, const char* cc, const char* estado,
			 const char* tipolibro, const char* tipousuario)
	{
		strcpy(Titulo, titulo);
		strcpy(Cc, cc);
		strcpy(EstadoPrestamo, estado);
		strcpy(tipoLibro, tipolibro);
		strcpy(tipoUsuario, tipousuario);
		sig = nullptr;
	}
	
	const char* getTitulo() const {
		return Titulo;
	}
	
	const char* getCc() const {
		return Cc;
	}
	
	const char* getEstadoPrestamo() const {
		return EstadoPrestamo;
	}
	
	const char* getTipoLibro() const {
		return tipoLibro;
	}
	
	const char* getTipoUsuario() const {
		return tipoUsuario;
	}
	
	Prestamo* getSig() const {
		return sig;
	}
	
	void setSig(Prestamo* siguiente) { 
		sig = siguiente; 
	}
	
	void setTitulo(const char* nuevoTitulo) { 
		strcpy(Titulo, nuevoTitulo); 
	}
	
	void setCc(const char* nuevoCc) { 
		strcpy(Cc, nuevoCc); 
	}
	
	void setEstadoPrestamo(const char* nuevoEstado) {
		strcpy(EstadoPrestamo, nuevoEstado);
	}
	
	void setTipoLibro(const char* nuevoTipoLibro) {
		strcpy(tipoLibro, nuevoTipoLibro);
	}
	
	void setTipoUsuario(const char* nuevoTipoUsuario) {
		strcpy(tipoUsuario, nuevoTipoUsuario);
	}
	
	bool validarUsuario(const char* cedula, char* tipoUsuarioEncontrado) {
		// Verificar si las funciones están disponibles antes de usarlas
		Estudiante* tempEst = obtenerCabezaEstudiantes();
		if (tempEst != nullptr) {
			while (tempEst != nullptr) {
				if (strcmp(tempEst->getCc(), cedula) == 0) {
					strcpy(tipoUsuarioEncontrado, "Estudiante");
					return true;
				}
				tempEst = (Estudiante*)tempEst->getSig();
			}
		}
		
		Profesor* tempProf = obtenerCabezaProfesores();
		if (tempProf != nullptr) {
			while (tempProf != nullptr) {
				if (strcmp(tempProf->getCc(), cedula) == 0) {
					strcpy(tipoUsuarioEncontrado, "Profesor");
					return true;
				}
				tempProf = (Profesor*)tempProf->getSig();
			}
		}
		
		Admin* tempAdmi = obtenerCabezaAdmins();
		if (tempAdmi != nullptr) {
			while (tempAdmi != nullptr) {
				if (strcmp(tempAdmi->getCc(), cedula) == 0) {
					strcpy(tipoUsuarioEncontrado, "Admin");
					return true;
				}
				tempAdmi = (Admin*)tempAdmi->getSig();
			}
		}
		return false;
	}
	
	bool validarLibro(const char* titulo, char* tipoLibroEncontrado) {
		LibroDigital* tempDig = obtenerCabezaLibrosDigitales();
		if (tempDig != nullptr) {
			while (tempDig != nullptr) {
				if (strcmp(tempDig->getTitulo(), titulo) == 0) {
					strcpy(tipoLibroEncontrado, "Digital");
					return true;
				}
				tempDig = (LibroDigital*)tempDig->getSig();
			}
		}
		
		LibroFisico* tempFis = obtenerCabezaLibrosFisicos();
		if (tempFis != nullptr) {
			while (tempFis != nullptr) {
				if (strcmp(tempFis->getTitulo(), titulo) == 0) {
					strcpy(tipoLibroEncontrado, "Fisico");
					return true;
				}
				tempFis = (LibroFisico*)tempFis->getSig();
			}
		}
		
		return false;
	}
	
	void registrarPrestamo() {
		char continuar = 's';
		while (continuar == 's' || continuar == 'S') {
			system("cls");
			
			char titulo[50], cc[15], tipoUsuarioEncontrado[20], tipoLibroEncontrado[20];
			bool usuarioValido = false;
			bool libroValido = false;
			
			cout << "=== REGISTRO DE PRESTAMO ===\n";
			
			cout << "Digite su cedula: ";
			cin >> cc;
			
			usuarioValido = validarUsuario(cc, tipoUsuarioEncontrado);
			
			if (!usuarioValido) {
				cout << "ERROR: La cedula " << cc << " no existe en el sistema." << endl;
				cout << "Por favor, registre primero el usuario o verifique la cedula." << endl;
				cout << "Presione cualquier tecla para volver al menu...";
				getch();
				return;
			}
			cout << "Usuario encontrado: Tipo " << tipoUsuarioEncontrado << endl;
			
			cout << "Digite el titulo del libro: ";
			cin.ignore();
			cin.getline(titulo, 50);
			
			libroValido = validarLibro(titulo, tipoLibroEncontrado);
			
			if (!libroValido) {
				cout << "ERROR: El libro '" << titulo << "' no existe en el sistema." << endl;
				cout << "Por favor, registre primero el libro o verifique el titulo." << endl;
				cout << "Presione cualquier tecla para para volver al menu...";
				getch();
				return;
			}
			cout << "Libro encontrado: Tipo " << tipoLibroEncontrado << endl;
			
			bool libroYaPrestado = false;
			Prestamo* bus = cab;
			
			while (bus != nullptr) {
				if (strcmp(bus->getTitulo(), titulo) == 0 && 
					strcmp(bus->getEstadoPrestamo(), "Activo") == 0) {
					libroYaPrestado = true;
					break;
				}
				bus = bus->getSig();
			}
			
			if (libroYaPrestado) {
				cout << "ERROR: El libro '" << titulo << "' ya esta prestado y activo." << endl;
				cout << "No se puede prestar un libro que ya esta en prestamo." << endl;
				cout << "Presione cualquier tecla para continuar...";
				getch();
				return;
			} else {
				Prestamo* nuevoPrestamo = new Prestamo(titulo, cc, "Activo", 
													   tipoLibroEncontrado, tipoUsuarioEncontrado);
				
				if (cab == nullptr) {
					cab = nuevoPrestamo;
				} else {
					Prestamo* temp = cab;
					while (temp->getSig() != nullptr) {
						temp = temp->getSig();
					}
					temp->setSig(nuevoPrestamo);
				}
				
				cout << "\nPrestamo registrado exitosamente:\n";
				cout << "Titulo: " << nuevoPrestamo->getTitulo() << "\n";
				cout << "Cedula: " << nuevoPrestamo->getCc() << "\n";
				cout << "Estado: " << nuevoPrestamo->getEstadoPrestamo() << "\n";
				cout << "Tipo de Libro: " << nuevoPrestamo->getTipoLibro() << "\n";
				cout << "Tipo de Usuario: " << nuevoPrestamo->getTipoUsuario() << "\n";
				guardarPrestamo();
			}
			
			cout << "\n¿Desea continuar con otro registro de Prestamo? <s/n>: ";
			cin >> continuar;
		}
	}
	
	void verPrestamo() {
		if (cab == nullptr) {
			cout << "No hay prestamos registrados.\n";
			getch();
			return;
		}
		
		char cedulaBuscada[15];
		cout << "Ingrese la cedula del usuario para ver sus prestamos: ";
		cin >> cedulaBuscada;
		
		Prestamo* temp = cab;
		bool encontrado = false;
		
		cout << "\n===== PRESTAMOS ENCONTRADOS =====\n";
		while (temp != nullptr) {
			if (strcmp(temp->getCc(), cedulaBuscada) == 0) {
				cout << "Titulo: " << temp->getTitulo() << "\n";
				cout << "Cedula: " << temp->getCc() << "\n";
				cout << "Estado: " << temp->getEstadoPrestamo() << "\n";
				cout << "Tipo de Libro: " << temp->getTipoLibro() << "\n";
				cout << "Tipo de Usuario: " << temp->getTipoUsuario() << "\n";
				cout << "----------------------------\n";
				encontrado = true;
			}
			temp = temp->getSig();
		}
		
		if (!encontrado) {
			cout << "No se encontraron prestamos para la cedula: " << cedulaBuscada << "\n";
		}
		getch();
	}
	
	void verTodosPrestamos() {
		if (cab == nullptr) {
			cout << "No hay prestamos registrados.\n";
			getch();
			return;
		}
		
		Prestamo* temp = cab;
		cout << "\n===== TODOS LOS PRESTAMOS =====\n";
		
		while (temp != nullptr) {
			cout << "Titulo: " << temp->getTitulo() << "\n";
			cout << "Cedula: " << temp->getCc() << "\n";
			cout << "Estado: " << temp->getEstadoPrestamo() << "\n";
			cout << "Tipo de Libro: " << temp->getTipoLibro() << "\n";
			cout << "Tipo de Usuario: " << temp->getTipoUsuario() << "\n";
			cout << "----------------------------\n";
			temp = temp->getSig();
		}
		getch();
	}
	
	void devolverLibro() {
		if (cab == nullptr) {
			cout << "No hay prestamos registrados para devolver.\n";
			getch();
			return;
		}
		
		char cedulaBuscada[15];
		char tituloBuscado[50];
		
		cout << "Ingrese la cedula del usuario: ";
		cin >> cedulaBuscada;
		cout << "Ingrese el titulo del libro a devolver: ";
		cin.ignore();
		cin.getline(tituloBuscado, 50);
		
		Prestamo* temp = cab;
		bool encontrado = false;
		
		while (temp != nullptr) {
			if (strcmp(temp->getCc(), cedulaBuscada) == 0 &&
				strcmp(temp->getTitulo(), tituloBuscado) == 0 &&
				strcmp(temp->getEstadoPrestamo(), "Activo") == 0) {
				
				cout << "\nPrestamo encontrado:\n";
				cout << "Titulo: " << temp->getTitulo() << "\n";
				cout << "Cedula: " << temp->getCc() << "\n";
				cout << "Estado actual: " << temp->getEstadoPrestamo() << "\n";
				cout << "Tipo de Libro: " << temp->getTipoLibro() << "\n";
				cout << "Tipo de Usuario: " << temp->getTipoUsuario() << "\n";
				
				char confirmacion;
				cout << "\n¿Confirma la devolucion de este libro? (s/n): ";
				cin >> confirmacion;
				
				if (confirmacion == 's' || confirmacion == 'S') {
					temp->setEstadoPrestamo("Devuelto");
					cout << "\nLibro devuelto correctamente.\n";
					cout << "Estado actualizado a: " << temp->getEstadoPrestamo() << "\n";
					guardarPrestamo();
				} else {
					cout << "\nDevolucion cancelada.\n";
				}
				
				encontrado = true;
				break;
			}
			temp = temp->getSig();
		}
		
		if (!encontrado) {
			cout << "\nNo se encontro un prestamo activo con esa cedula y titulo.\n";
			cout << "Verifique que:\n";
			cout << "- La cedula sea correcta\n";
			cout << "- El titulo del libro sea correcto\n";
			cout << "- El prestamo este en estado 'Activo'\n";
		}
		getch();
	}
	
	void guardarPrestamo() {
		ofstream archivo("BIBLIOTECA_PRESTAMO.txt");
		if (!archivo.is_open()) {
			cout << "Error al abrir archivo para guardar prestamos.\n";
			getch();
			return;
		}
		
		Prestamo* temp = cab;
		while (temp != nullptr) {
			archivo << temp->getTitulo() << "|" << temp->getCc() << "|" 
				<< temp->getEstadoPrestamo() << "|" << temp->getTipoLibro() << "|"
				<< temp->getTipoUsuario() << "|PRESTAMO" << endl;
			temp = temp->getSig();
		}
		
		archivo.close();
		cout << "Prestamos guardados exitosamente.\n";
		getch();
	}
	
	void abrirPrestamo() {
		ifstream archivo("BIBLIOTECA_PRESTAMO.txt");
		if (!archivo.is_open()) {
			cout << "No se pudo abrir el archivo.\n";
			getch();
			return;
		}
		
		while (cab != nullptr) {
			Prestamo* temp = cab;
			cab = cab->getSig();
			delete temp;
		}
		
		string linea;
		while (getline(archivo, linea)) {
			if (linea.empty()) continue;
			
			size_t pos = 0;
			string campos[6];
			int campo = 0;
			
			string temp_linea = linea;
			while ((pos = temp_linea.find('|')) != string::npos && campo < 5) {
				campos[campo++] = temp_linea.substr(0, pos);
				temp_linea.erase(0, pos + 1);
			}
			campos[campo] = temp_linea;
			
			if (campo == 5 && campos[5] == "PRESTAMO") {
				Prestamo* nuevo = new Prestamo(campos[0].c_str(), campos[1].c_str(), 
											   campos[2].c_str(), campos[3].c_str(), 
											   campos[4].c_str());
				if (cab == nullptr) {
					cab = nuevo;
				} else {
					Prestamo* aux = cab;
					while (aux->getSig() != nullptr) {
						aux = aux->getSig();
					}
					aux->setSig(nuevo);
				}
			}
		}
		archivo.close();
		cout << "Prestamos cargados exitosamente.\n";
		getch();
	}
	
	virtual ~Prestamo() {}
};

Prestamo* Prestamo::cab = nullptr;

#endif
