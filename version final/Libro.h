#ifndef LIBRO_H
#define LIBRO_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <conio.h>
#include <string>
using namespace std;

// Clase base abstracta para métodos de búsqueda digital
class BuscarDijitalMethod
{
public:
	virtual void buscar() const=0;
	virtual ~BuscarDijitalMethod()=default;
};

// Clase base abstracta para métodos de búsqueda física
class BuscarFisicaMethod
{
public:
	virtual void buscar() const=0;
	virtual ~BuscarFisicaMethod()=default;
};

// Clase base Libro
class Libro
{
protected:
	char Titulo[50];
	char Autor[50];
	char tipoLibro[20];
	Libro* sig;
public:
	Libro(const char* titulo, const char* autor, const char* tipolibro)
	{
		strcpy(Titulo, titulo);
		strcpy(Autor, autor);
		strcpy(tipoLibro, tipolibro);
		sig = nullptr;
	}
	virtual void registrarLibro() = 0;
	virtual void actualizarLibro() = 0;
	virtual void setbuscar() = 0;
	virtual void processBuscar() = 0;
	virtual void guardarLibro() = 0;  
	virtual void abrirLibro() = 0;
	virtual void verLibros()=0;
	virtual char* getTipoLibro() = 0; 
	
	const char* getTitulo() const {
		return Titulo;
	}
	
	const char* getAutor() const {
		return Autor;
	}
	
	Libro* getSig() const {
		return sig;
	}
	
	void setSig(Libro* siguiente) { 
		sig = siguiente; 
	}
	
	void setTitulo(const char* nuevoTitulo) { 
		strcpy(Titulo, nuevoTitulo); 
	}
	
	void setAutor(const char* nuevoAutor) { 
		strcpy(Autor, nuevoAutor); 
	}
	
	virtual ~Libro() {}
};

// Clase LibroDigital
class LibroDigital : public Libro {
private: 
	static LibroDigital* cab;
	BuscarDijitalMethod* buscarMethod;
	static const char* ARCHIVO_DIGITAL;  // Archivo específico para libros digitales
public:
	static void inicializar() {
		cab = nullptr; 
	}
	
	static LibroDigital* obtenerCabeza() {
		return cab;
	}
	
	static void setCabeza(LibroDigital* nuevaCabeza) {
		cab = nuevaCabeza;
	}
	
	LibroDigital(const char* titulo, const char* autor, const char* tipolibro)
		: Libro(titulo, autor, tipolibro), buscarMethod(nullptr) {}
	
	char* getTipoLibro() override {
		return (char*)"Digital";
	}
	
	void registrarLibro() override {
		char continuar = 's';
		while (continuar == 's' || continuar == 'S') {
			system("cls");
			
			char titulo[50], autor[50];
			
			cout << "=== REGISTRO DE LIBRO DIGITAL ===\n";
			cout << "Digite el titulo: "; cin.ignore(); cin.getline(titulo, 50);
			cout << "Digite el autor: "; cin.getline(autor, 50);
			
			LibroDigital* nuevoLibro = new LibroDigital(titulo, autor, "Digital");
			
			if (cab == nullptr) {
				cab = nuevoLibro;
			} else {
				LibroDigital* temp = cab;
				while (temp->getSig() != nullptr) {
					temp = (LibroDigital*)temp->getSig();
				}
				temp->setSig(nuevoLibro);
			}
			
			cout << "\nLibro Digital registrado exitosamente:\n";
			cout << "Titulo: " << nuevoLibro->getTitulo() << "\n";
			cout << "Autor: " << nuevoLibro->getAutor() << "\n";
			guardarLibro();
			cout << "\n¿Desea continuar con otro registro Libro Digital? <s/n>: ";
			cin >> continuar;
		}
	}
	
	void actualizarLibro() override {
		if (cab == nullptr) {
			cout << "No hay registros para modificar.\n";
			getch();
			return;
		}
		
		char tituloBuscado[50];
		char autorBuscado[50];
		cout << "Ingrese el titulo del Libro Digital que desea modificar: ";
		cin.ignore(); cin.getline(tituloBuscado, 50);
		cout << "Ingrese el autor del Libro Digital que desea modificar: ";
		cin.getline(autorBuscado, 50);
		
		char TipoDigi[20] = "Digital";
		LibroDigital* temp = cab;
		bool encontrado = false;
		
		while (temp != nullptr) {
			if (strcmp(temp->getTitulo(), tituloBuscado) == 0 && 
				strcmp(temp->getAutor(), autorBuscado) == 0 && 
				strcmp(temp->getTipoLibro(), TipoDigi) == 0) {
				cout << "\nRegistro encontrado:\n";
				cout << "Titulo actual: " << temp->getTitulo() << "\n";
				cout << "Autor actual: " << temp->getAutor() << "\n";
				
				char nuevoTitulo[50], nuevoAutor[50];
				cout << "Ingrese el nuevo titulo: ";
				cin.getline(nuevoTitulo, 50);
				cout << "Ingrese el nuevo autor: ";
				cin.getline(nuevoAutor, 50);
				
				temp->setTitulo(nuevoTitulo);
				temp->setAutor(nuevoAutor);
				
				cout << "\nRegistro del libro digital actualizado correctamente.\n";
				guardarLibro();
				encontrado = true;
				break;
			}
			temp = (LibroDigital*)temp->getSig();
		}
		
		if (!encontrado) {
			cout << "\nNo se encontró el registro.\n";
		}
		
		getch();
	}
	
	void setbuscar() override;  // Declaración - implementación después
	void processBuscar() override {
		if (buscarMethod != nullptr) {
			buscarMethod->buscar();
		} else {
			cout << "No se ha establecido un método de búsqueda.\n";
		}
	}
	
	void verLibros()override{
		char TipoDigi[20] = "Digital";
		LibroDigital* temp = cab;
		bool encontrado = false;
		
		while (temp != nullptr) {
			if (strcmp(temp->getTipoLibro(), TipoDigi) == 0) {
				cout << "\nRegistro o registros encontrados:\n";
				cout << "Titulo: " << temp->getTitulo() << "\n";
				cout << "Autor: " << temp->getAutor() << "\n";
				cout << "Tipo: " << temp->getTipoLibro() << "\n";
				encontrado = true;
			}
			temp = (LibroDigital*)temp->getSig();
		}
		
		if (!encontrado) {
			cout << "\nNo se encontró ningun registro.\n";
		}
		getch();
	}
	
	void guardarLibro() override {
		// Reescribir completamente el archivo con todos los libros digitales
		ofstream archivo(ARCHIVO_DIGITAL);
		if (!archivo.is_open()) {
			cout << "Error al abrir archivo para guardar libros digitales.\n";
			return;
		}
		
		LibroDigital* temp = cab;
		while (temp != nullptr) {
			archivo << temp->getTitulo() << "|" << temp->getAutor() << "|" 
				<< temp->getTipoLibro() << "|LIBRO" << endl;
			temp = (LibroDigital*)temp->getSig();
		}
		
		archivo.close();
		cout << "Libros digitales guardados exitosamente en " << ARCHIVO_DIGITAL << ".\n";
		getch();
	}
	
	void abrirLibro() override {
		ifstream archivo(ARCHIVO_DIGITAL);
		if (!archivo.is_open()) {
			cout << "No se pudo abrir el archivo " << ARCHIVO_DIGITAL << ".\n";
			getch();
			return;
		}
		
		// Limpiar lista existente
		while (cab != nullptr) {
			LibroDigital* temp = cab;
			cab = (LibroDigital*)cab->getSig();
			delete temp;
		}
		
		string linea;
		while (getline(archivo, linea)) {
			if (linea.empty()) continue;
			
			size_t pos = 0;
			string campos[4];
			int campo = 0;
			
			// Parsear línea separada por '|'
			string temp_linea = linea;
			while ((pos = temp_linea.find('|')) != string::npos && campo < 3) {
				campos[campo++] = temp_linea.substr(0, pos);
				temp_linea.erase(0, pos + 1);
			}
			campos[campo] = temp_linea;
			
			// Verificar que es un libro digital
			if (campo == 3 && campos[3] == "LIBRO" && campos[2] == "Digital") {
				LibroDigital* nuevo = new LibroDigital(campos[0].c_str(), campos[1].c_str(), 
													   campos[2].c_str());
				if (cab == nullptr) {
					cab = nuevo;
				} else {
					LibroDigital* aux = cab;
					while (aux->getSig() != nullptr) {
						aux = (LibroDigital*)aux->getSig();
					}
					aux->setSig(nuevo);
				}
			}
		}
		archivo.close();
		cout << "Libros digitales cargados desde " << ARCHIVO_DIGITAL << ".\n";
	}
	
	~LibroDigital() {
		delete buscarMethod;
	}
};

// Clase LibroFisico
class LibroFisico : public Libro {
private:
	static LibroFisico* cab;
	BuscarFisicaMethod* buscarMethod;
	static const char* ARCHIVO_FISICO;  // Archivo específico para libros físicos
public:
	static void inicializar() {
		cab = nullptr;
	}
	
	static LibroFisico* obtenerCabeza() {
		return cab;
	}
	
	static void setCabeza(LibroFisico* nuevaCabeza) {
		cab = nuevaCabeza;
	}
	
	LibroFisico(const char* titulo, const char* autor, const char* tipolibro)
		: Libro(titulo, autor, tipolibro), buscarMethod(nullptr) {}
	
	char* getTipoLibro() override {
		return (char*)"Fisico";
	}
	
	void registrarLibro() override {
		char continuar = 's';
		while (continuar == 's' || continuar == 'S') {
			system("cls");
			
			char titulo[50], autor[50];
			
			cout << "=== REGISTRO DE LIBRO FISICO ===\n";
			cout << "Digite el titulo: "; cin.ignore(); cin.getline(titulo, 50);
			cout << "Digite el autor: "; cin.getline(autor, 50);
			
			LibroFisico* nuevoLibro = new LibroFisico(titulo, autor, "Fisico");
			
			if (cab == nullptr) {
				cab = nuevoLibro;
			} else {
				LibroFisico* temp = cab;
				while (temp->getSig() != nullptr) {
					temp = (LibroFisico*)temp->getSig();
				}
				temp->setSig(nuevoLibro);
			}
			
			cout << "\nLibro Fisico registrado exitosamente:\n";
			cout << "Titulo: " << nuevoLibro->getTitulo() << "\n";
			cout << "Autor: " << nuevoLibro->getAutor() << "\n";
			guardarLibro();
			cout << "\n¿Desea continuar con otro registro Libro Fisico? <s/n>: ";
			cin >> continuar;
		}
	}
	
	void actualizarLibro() override {
		if (cab == nullptr) {
			cout << "No hay registros para modificar.\n";
			getch();
			return;
		}
		
		char tituloBuscado[50];
		char autorBuscado[50];
		cout << "Ingrese el titulo del Libro Fisico que desea modificar: ";
		cin.ignore(); cin.getline(tituloBuscado, 50);
		cout << "Ingrese el autor del Libro Fisico que desea modificar: ";
		cin.getline(autorBuscado, 50);
		
		char TipoFisi[20] = "Fisico";
		LibroFisico* temp = cab;
		bool encontrado = false;
		
		while (temp != nullptr) {
			if (strcmp(temp->getTitulo(), tituloBuscado) == 0 &&
				strcmp(temp->getAutor(), autorBuscado) == 0 &&
				strcmp(temp->getTipoLibro(), TipoFisi) == 0) {
				cout << "\nRegistro encontrado:\n";
				cout << "Titulo actual: " << temp->getTitulo() << "\n";
				cout << "Autor actual: " << temp->getAutor() << "\n";
				
				char nuevoTitulo[50], nuevoAutor[50];
				cout << "Ingrese el nuevo titulo: ";
				cin.getline(nuevoTitulo, 50);
				cout << "Ingrese el nuevo autor: ";
				cin.getline(nuevoAutor, 50);
				
				temp->setTitulo(nuevoTitulo);
				temp->setAutor(nuevoAutor);
				
				cout << "\nRegistro del libro fisico actualizado correctamente.\n";
				guardarLibro();
				encontrado = true;
				break;
			}
			temp = (LibroFisico*)temp->getSig();
		}
		
		if (!encontrado) {
			cout << "\nNo se encontró el registro.\n";
		}
		
		getch();
	}
	
	void setbuscar() override;  // Declaración - implementación después
	void processBuscar() override {
		if (buscarMethod != nullptr) {
			buscarMethod->buscar();
		} else {
			cout << "No se ha establecido un método de búsqueda.\n";
		}
	}
	
	void verLibros()override{
		char TipoFisi[20] = "Fisico";
		LibroFisico* temp = cab;
		bool encontrado = false;
		
		while (temp != nullptr) {
			if (strcmp(temp->getTipoLibro(), TipoFisi) == 0) {
				cout << "\nRegistro o registros encontrado:\n";
				cout << "Titulo: " << temp->getTitulo() << "\n";
				cout << "Autor: " << temp->getAutor() << "\n";
				cout << "Tipo: " << temp->getTipoLibro() << "\n";
				encontrado = true;
			}
			temp = (LibroFisico*)temp->getSig();
		}
		
		if (!encontrado) {
			cout << "\nNo se encontró el registro.\n";
		}
		getch();
	}
	
	void guardarLibro() override {
		// Reescribir completamente el archivo con todos los libros físicos
		ofstream archivo(ARCHIVO_FISICO);
		if (!archivo.is_open()) {
			cout << "Error al abrir archivo para guardar libros físicos.\n";
			return;
		}
		
		LibroFisico* temp = cab;
		while (temp != nullptr) {
			archivo << temp->getTitulo() << "|" << temp->getAutor() << "|" 
				<< temp->getTipoLibro() << "|LIBRO" << endl;
			temp = (LibroFisico*)temp->getSig();
		}
		
		archivo.close();
		cout << "Libros fisicos guardados exitosamente en " << ARCHIVO_FISICO << ".\n";
		getch();
	}
	
	void abrirLibro() override {
		ifstream archivo(ARCHIVO_FISICO);
		if (!archivo.is_open()) {
			cout << "No se pudo abrir el archivo " << ARCHIVO_FISICO << ".\n";
			getch();
			return;
		}
		
		// Limpiar lista existente
		while (cab != nullptr) {
			LibroFisico* temp = cab;
			cab = (LibroFisico*)cab->getSig();
			delete temp;
		}
		
		string linea;
		while (getline(archivo, linea)) {
			if (linea.empty()) continue;
			
			size_t pos = 0;
			string campos[4];
			int campo = 0;
			
			// Parsear línea separada por '|'
			string temp_linea = linea;
			while ((pos = temp_linea.find('|')) != string::npos && campo < 3) {
				campos[campo++] = temp_linea.substr(0, pos);
				temp_linea.erase(0, pos + 1);
			}
			campos[campo] = temp_linea;
			
			// Verificar que es un libro físico
			if (campo == 3 && campos[3] == "LIBRO" && campos[2] == "Fisico") {
				LibroFisico* nuevo = new LibroFisico(campos[0].c_str(), campos[1].c_str(), 
													 campos[2].c_str());
				if (cab == nullptr) {
					cab = nuevo;
				} else {
					LibroFisico* aux = cab;
					while (aux->getSig() != nullptr) {
						aux = (LibroFisico*)aux->getSig();
					}
					aux->setSig(nuevo);
				}
			}
		}
		archivo.close();
		cout << "Libros físicos cargados desde " << ARCHIVO_FISICO << ".\n";
	}
	
	~LibroFisico() {
		delete buscarMethod;
	}
};

// Ahora que las clases están completamente definidas, podemos implementar las clases de búsqueda

class LibroVirtualPorTitulo: public BuscarDijitalMethod{
	void buscar() const override{
		char tituloBuscado[50];
		cout << "Ingrese el titulo del Libro Digital que desea buscar: ";
		cin.ignore(); cin.getline(tituloBuscado, 50);
		
		char TipoDigi[20] = "Digital";
		LibroDigital* temp = LibroDigital::obtenerCabeza();
		bool encontrado = false;
		
		while (temp != nullptr) {
			if (strcmp(temp->getTitulo(), tituloBuscado) == 0 && 
				strcmp(temp->getTipoLibro(), TipoDigi) == 0) {
				cout << "\nRegistro encontrado:\n";
				cout << "Titulo: " << temp->getTitulo() << "\n";
				cout << "Autor: " << temp->getAutor() << "\n";
				cout << "Tipo: " << temp->getTipoLibro() << "\n";
				encontrado = true;
			}
			temp = (LibroDigital*)temp->getSig();
		}
		
		if (!encontrado) {
			cout << "\nNo se encontró el registro.\n";
		}
		getch();
	}
};

class LibroFisicoPorTitulo: public BuscarFisicaMethod{
	void buscar() const override{
		char tituloBuscado[50];
		cout << "Ingrese el titulo del Libro Fisico que desea buscar: ";
		cin.ignore(); cin.getline(tituloBuscado, 50);
		
		char TipoFisi[20] = "Fisico";
		LibroFisico* temp = LibroFisico::obtenerCabeza();
		bool encontrado = false;
		
		while (temp != nullptr) {
			if (strcmp(temp->getTitulo(), tituloBuscado) == 0 && 
				strcmp(temp->getTipoLibro(), TipoFisi) == 0) {
				cout << "\nRegistro encontrado:\n";
				cout << "Titulo: " << temp->getTitulo() << "\n";
				cout << "Autor: " << temp->getAutor() << "\n";
				cout << "Tipo: " << temp->getTipoLibro() << "\n";
				encontrado = true;
			}
			temp = (LibroFisico*)temp->getSig();
		}
		
		if (!encontrado) {
			cout << "\nNo se encontró el registro.\n";
		}
		getch();
	}
};

class LibroVirtualPorAutor: public BuscarDijitalMethod{
	void buscar() const override{
		char autorBuscado[50];
		cout << "Ingrese el Autor del Libro Digital que desea buscar: ";
		cin.ignore(); cin.getline(autorBuscado, 50);
		
		char TipoDigi[20] = "Digital";
		LibroDigital* temp = LibroDigital::obtenerCabeza();
		bool encontrado = false;
		
		while (temp != nullptr) {
			if (strcmp(temp->getAutor(), autorBuscado) == 0 && 
				strcmp(temp->getTipoLibro(), TipoDigi) == 0) {
				cout << "\nRegistro encontrado:\n";
				cout << "Titulo: " << temp->getTitulo() << "\n";
				cout << "Autor: " << temp->getAutor() << "\n";
				cout << "Tipo: " << temp->getTipoLibro() << "\n";
				encontrado = true;
			}
			temp = (LibroDigital*)temp->getSig();
		}
		
		if (!encontrado) {
			cout << "\nNo se encontró el registro.\n";
		}
		getch();
	}
};

class LibroFisicoPorAutor: public BuscarFisicaMethod{
	void buscar() const override{
		char autorBuscado[50];
		cout << "Ingrese el Autor del Libro Fisico que desea buscar: ";
		cin.ignore(); cin.getline(autorBuscado, 50);
		
		char TipoFisi[20] = "Fisico";
		LibroFisico* temp = LibroFisico::obtenerCabeza();
		bool encontrado = false;
		
		while (temp != nullptr) {
			if (strcmp(temp->getAutor(), autorBuscado) == 0 && 
				strcmp(temp->getTipoLibro(), TipoFisi) == 0) {
				cout << "\nRegistro encontrado:\n";
				cout << "Titulo: " << temp->getTitulo() << "\n";
				cout << "Autor: " << temp->getAutor() << "\n";
				cout << "Tipo: " << temp->getTipoLibro() << "\n";
				encontrado = true;
			}
			temp = (LibroFisico*)temp->getSig();
		}
		
		if (!encontrado) {
			cout << "\nNo se encontró el registro.\n";
		}
		getch();
	}
};

// Implementaciones de los métodos setbuscar que fueron declarados antes
void LibroDigital::setbuscar() {
	int opcion;
	cout << "Seleccione método de búsqueda:\n";
	cout << "1. Por título\n";
	cout << "2. Por autor\n";
	cout << "Opción: ";
	cin >> opcion;
	
	switch(opcion) {
	case 1:
		buscarMethod = new LibroVirtualPorTitulo();
		break;
	case 2:
		buscarMethod = new LibroVirtualPorAutor();
		break;
	default:
		buscarMethod = nullptr;
		cout << "Opción inválida.\n";
		break;
	}
}

void LibroFisico::setbuscar() {
	int opcion;
	cout << "Seleccione método de búsqueda:\n";
	cout << "1. Por título\n";
	cout << "2. Por autor\n";
	cout << "Opción: ";
	cin >> opcion;
	
	switch(opcion) {
	case 1:
		buscarMethod = new LibroFisicoPorTitulo();
		break;
	case 2:
		buscarMethod = new LibroFisicoPorAutor();
		break;
	default:
		buscarMethod = nullptr;
		cout << "Opción inválida.\n";
		break;
	}
}

// Clase Factory
class LibroFactory {
private:
	Libro* libro;
public:
	Libro* getLibro() {
		int opcion = 0;
		cout << "====Menu====\n";
		cout << "Digital 1\n";
		cout << "Fisico 2\n";
		cout << "Escoja un tipo: ";
		cin >> opcion;
		
		switch (opcion) {
		case 1:
			libro = new LibroDigital("", "", "Digital");
			break;
		case 2:
			libro = new LibroFisico("", "", "Fisico");
			break;
		default:
			libro = nullptr;
			break;
		}
		
		return libro;
	}
};

// Definición de variables estáticas
LibroDigital* LibroDigital::cab = nullptr;
LibroFisico* LibroFisico::cab = nullptr;

// Definición de nombres de archivos específicos
const char* LibroDigital::ARCHIVO_DIGITAL = "BIBLIOTECA_DIGITAL.txt";
const char* LibroFisico::ARCHIVO_FISICO = "BIBLIOTECA_FISICA.txt";

#endif
