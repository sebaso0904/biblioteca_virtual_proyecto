#include "Usuario.h"    // Incluye las clases de usuario
#include "libro.h"      // Incluye las clases de libro
#include "Prestamo.h"   // Incluye la clase de prestamo
#include <iostream>
#include <conio.h>
#include <cstdlib>
using namespace std;

// Variables globales para autenticación de administrador
int administrador = 1234;
int pass_admin = 0;
bool esAdministrador = false; // Variable para mantener el estado de autenticación

// Funciones para obtener cabezas de listas
Estudiante* obtenerCabezaEstudiantes() {
	return Estudiante::obtenerCabeza();
}

Profesor* obtenerCabezaProfesores() {
	return Profesor::obtenerCabeza();
}

Admin* obtenerCabezaAdmins() {
	return Admin::obtenerCabeza();
}

LibroDigital* obtenerCabezaLibrosDigitales() {
	return LibroDigital::obtenerCabeza();
}

LibroFisico* obtenerCabezaLibrosFisicos() {
	return LibroFisico::obtenerCabeza();
}

void cargarDatosAutomaticamente();
// Declaraciones de funciones de menú
void mostrarMenuPrincipal();
void mostrarMenuUsuarios();
void mostrarMenuLibros();
void mostrarMenuPrestamos();

// Funciones de gestión de usuarios
void gestionarUsuarios();
void operacionesUsuario(Usuario* usuario);

// Funciones de gestión de libros
void gestionarLibros();

// Funciones de gestión de préstamos
void gestionarPrestamos();

// Función para limpiar pantalla y pausar
void limpiarPantalla();
void pausar();

// Función para verificar autenticación de administrador
bool verificarAdmin() {
	if (esAdministrador) {
		return true; // Ya está autenticado como admin
	}
	
	cout << "Para verificar que usted esta autorizado de usar esta funcion\n";
	cout << "Digite la contrasena: ";
	cin >> pass_admin;
	if (administrador == pass_admin) {
		return true;
	} else {
		cout << "Contrasena incorrecta\n";
		pausar();
		return false;
	}
}

int main() {
	// Inicializar todas las listas estáticas
	Estudiante::inicializar();
	Profesor::inicializar();
	Admin::inicializar();
	LibroDigital::inicializar();
	LibroFisico::inicializar();
	Prestamo::inicializar();
	
	int opcion = 0;
	
	cout << "=========================================\n";
	cout << "  BIENVENIDO AL SISTEMA DE BIBLIOTECA\n";
	cout << "=========================================\n";
	cout << "Sistema integral de gestion bibliotecaria\n";
	cout << "Presione cualquier tecla para continuar...";
	getch();
	
	cout << "\n=========================================\n";
	cout << "  CARGANDO DATOS DEL SISTEMA...\n";
	cout << "=========================================\n";
	cargarDatosAutomaticamente();
	
	do {
		limpiarPantalla();
		mostrarMenuPrincipal();
		cin >> opcion;
		
		switch(opcion) {
		case 1:
			gestionarUsuarios();
			break;
			
		case 2:
			gestionarLibros();
			break;
			
		case 3:
			gestionarPrestamos();
			break;
			
		case 4:
			cout << "\n=== CERRANDO SISTEMA ===\n";
			cout << "Gracias por usar el Sistema de Biblioteca!\n";
			cout << "Presione cualquier tecla para salir...";
			getch();
			break;
			
		default:
			cout << "Opcion invalida. Presione cualquier tecla para continuar...\n";
			getch();
			break;
		}
		
	} while(opcion != 4);
	
	return 0;
}

void cargarDatosAutomaticamente() {
	cout << "Cargando usuarios...\n";
	Admin* admin = new Admin("", "", "", "", "Admin");
	admin->abrirUsuario();
	delete admin;
	cout << "? Todos los usuarios han sido cargados.\n";
	
	cout << "\nCargando libros digitales...\n";
	LibroDigital* libroDigital = new LibroDigital("", "", "Digital");
	libroDigital->abrirLibro();
	delete libroDigital;
	cout << "? Libros digitales cargados.\n";
	
	cout << "\nCargando libros fisicos...\n";
	LibroFisico* libroFisico = new LibroFisico("", "", "Fisico");
	libroFisico->abrirLibro();
	delete libroFisico;
	cout << "? Libros fisicos cargados.\n";
	
	cout << "\nCargando prestamos...\n";
	Prestamo* prestamo = new Prestamo("", "", "Activo", "Digital", "Estudiante");
	prestamo->abrirPrestamo();
	delete prestamo;
	cout << "? Prestamos cargados.\n";
	pausar();
}

void mostrarMenuPrincipal() {
	cout << "\n==========================================\n";
	cout << "       SISTEMA DE BIBLIOTECA\n";
	if (esAdministrador) {
		cout << "     [MODO ADMINISTRADOR ACTIVO]\n";
	}
	cout << "==========================================\n";
	cout << "1. Gestion de Usuarios\n";
	cout << "2. Gestion de Libros\n";
	cout << "3. Gestion de Prestamos\n";
	cout << "4. Salir del Sistema\n";
	cout << "==========================================\n";
	cout << "Seleccione una opcion: ";
}

void gestionarUsuarios() {
	int opcionTipo = 0;
	Usuario* usuarioActual = nullptr;
	
	do {
		limpiarPantalla();
		cout << "=== GESTION DE USUARIOS ===\n";
		if (esAdministrador) {
			cout << "[MODO ADMINISTRADOR ACTIVO]\n";
		}
		cout << "1. Gestionar como Estudiante\n";
		cout << "2. Gestionar como Profesor\n";
		cout << "3. Gestionar como Administrador\n";
		cout << "4. Volver al Menu Principal\n";
		cout << "===============================\n";
		cout << "Seleccione el tipo de usuario: ";
		cin >> opcionTipo;
		
		switch(opcionTipo) {
		case 1:
			usuarioActual = new Estudiante("", "", "", "", "Estudiante");
			cout << "\nModo: ESTUDIANTE\n";
			break;
		case 2:
			usuarioActual = new Profesor("", "", "", "", "Profesor");
			cout << "\nModo: PROFESOR\n";
			break;
		case 3:
			if (!esAdministrador) {
				cout << "Verifique que usted sea el Admin\n";
				cout << "Digite la contrasena: ";
				cin >> pass_admin;
				if(pass_admin == administrador){
					esAdministrador = true; // Marcar como administrador autenticado
					usuarioActual = new Admin("", "", "", "", "Admin");
					cout << "\nModo: ADMINISTRADOR [AUTENTICADO]\n";
				} else {
					cout << "Contrasena incorrecta\n";
					pausar();
					continue;
				}
			} else {
				usuarioActual = new Admin("", "", "", "", "Admin");
				cout << "\nModo: ADMINISTRADOR [YA AUTENTICADO]\n";
			}
			break;
		case 4:
			cout << "Volviendo al menu principal...\n";
			return;
		default:
			cout << "Opcion invalida.\n";
			pausar();
			continue;
		}
		
		if (usuarioActual != nullptr) {
			operacionesUsuario(usuarioActual);
			delete usuarioActual;
			usuarioActual = nullptr;
		}
		
	} while(opcionTipo != 4);
}

void operacionesUsuario(Usuario* usuario) {
	int opcion = 0;
	
	do {
		limpiarPantalla();
		cout << "Modo actual: " << usuario->getTipo();
		if (esAdministrador && usuario->getTipo() == "Admin") {
			cout << " [AUTENTICADO]";
		}
		cout << "\n";
		mostrarMenuUsuarios();
		cin >> opcion;
		
		switch(opcion) {
		case 1:
			if (verificarAdmin()) {
				cout << "\n--- REGISTRAR USUARIO ---\n";
				try {
					usuario->registroUsuario();
				} catch(...) {
					cout << "Error durante el registro.\n";
				}
				pausar();
			}
			break;
			
		case 2:
			if (verificarAdmin()) {
				cout << "\n--- ACTUALIZAR USUARIO ---\n";
				try {
					usuario->actualizarUsuario();
				} catch(...) {
					cout << "Error durante la actualizacion.\n";
				}
				pausar();
			}
			break;
			
		case 3:
			cout << "\n--- VER USUARIO ---\n";
			try {
				usuario->verAndIdentificarUsuario();
			} catch(...) {
				cout << "Error al mostrar usuario.\n";
			}
			pausar();
			break;
			
		case 4:
			return;
			
		default:
			cout << "Opcion invalida.\n";
			pausar();
			break;
		}
		
	} while(opcion != 4);
}

void mostrarMenuUsuarios() {
	cout << "\n===============================\n";
	cout << "      OPERACIONES USUARIO\n";
	cout << "===============================\n";
	cout << "1. Registrar Usuario\n";
	cout << "2. Actualizar Usuario\n";
	cout << "3. Ver Usuario\n";
	cout << "4. Volver\n";
	cout << "===============================\n";
	cout << "Seleccione una opcion: ";
}

void gestionarLibros() {
	LibroFactory factory;
	Libro* libro = nullptr;
	int opcion = 0;
	
	do {
		limpiarPantalla();
		mostrarMenuLibros();
		cin >> opcion;
		
		switch(opcion) {
		case 1: {
			if (verificarAdmin()) {
				cout << "\n=== REGISTRAR NUEVO LIBRO ===\n";
				libro = factory.getLibro();
				if (libro != nullptr) {
					libro->registrarLibro();
					delete libro;
					libro = nullptr;
				} else {
					cout << "Opcion invalida seleccionada.\n";
				}
				pausar();
			}
			break;
		}
		
		case 2: {
			if (verificarAdmin()) {
				cout << "\n=== ACTUALIZAR LIBRO EXISTENTE ===\n";
				libro = factory.getLibro();
				if (libro != nullptr) {
					libro->actualizarLibro();
					delete libro;
					libro = nullptr;
				} else {
					cout << "Opcion invalida seleccionada.\n";
				}
				pausar();
			}
			break;
		}
		
		case 3: {
			cout << "\n=== BUSCAR LIBRO ===\n";
			libro = factory.getLibro();
			if (libro != nullptr) {
				libro->setbuscar();
				libro->processBuscar();
				delete libro;
				libro = nullptr;
			} else {
				cout << "Opcion invalida seleccionada.\n";
			}
			pausar();
			break;
		}
		
		case 4: {
			cout << "\n=== VER TODOS LOS LIBROS ===\n";
			
			cout << "\n--- LIBROS DIGITALES ---\n";
			LibroDigital* libroDigital = new LibroDigital("", "", "Digital");
			libroDigital->verLibros();
			delete libroDigital;
			
			cout << "\n--- LIBROS FISICOS ---\n";
			LibroFisico* libroFisico = new LibroFisico("", "", "Fisico");
			libroFisico->verLibros();
			delete libroFisico;
			
			pausar();
			break;
		}
		case 5:
			cout << "Volviendo al menu principal...\n";
			return;
			
		default:
			cout << "Opcion invalida. Por favor seleccione una opcion del 1 al 5.\n";
			pausar();
			break;
		}
		
	} while (opcion != 5);
}

void mostrarMenuLibros() {
	cout << "\n=== GESTION DE LIBROS ===\n";
	if (esAdministrador) {
		cout << "[MODO ADMINISTRADOR ACTIVO]\n";
	}
	cout << "1. Registrar Libro\n";
	cout << "2. Actualizar Libro\n";
	cout << "3. Buscar Libro\n";
	cout << "4. Ver Todos los Libros\n";
	cout << "5. Volver al Menu Principal\n";
	cout << "==========================\n";
	cout << "Seleccione una opcion: ";
}

void gestionarPrestamos() {
	int opcion = 0;
	
	do {
		limpiarPantalla();
		mostrarMenuPrestamos();
		cin >> opcion;
		
		switch (opcion) {
		case 1: {
			cout << "\n=== REGISTRAR PRESTAMO ===\n";
			Prestamo* prestamo = new Prestamo("", "", "Activo", "Digital", "Estudiante");
			prestamo->registrarPrestamo();
			delete prestamo;
			pausar();
			break;
		}
		
		case 2: {
			cout << "\n=== VER PRESTAMOS POR CEDULA ===\n";
			Prestamo* prestamo = new Prestamo("", "", "Activo", "Digital", "Estudiante");
			prestamo->verPrestamo();
			delete prestamo;
			pausar();
			break;
		}
		
		case 3: {
			if (verificarAdmin()) {
				cout << "\n=== VER TODOS LOS PRESTAMOS ===\n";
				Prestamo* prestamo = new Prestamo("", "", "Activo", "Digital", "Estudiante");
				prestamo->verTodosPrestamos();
				delete prestamo;
				pausar();
			}
			break;
		}
		
		case 4: {
			cout << "\n=== DEVOLVER LIBRO ===\n";
			Prestamo* prestamo = new Prestamo("", "", "Activo", "Digital", "Estudiante");
			prestamo->devolverLibro();
			delete prestamo;
			pausar();
			break;
		}
		case 5:
			cout << "Volviendo al menu principal...\n";
			return;
			
		default:
			cout << "\nOpcion invalida. Por favor seleccione una opcion del 1 al 5.\n";
			pausar();
			break;
		}
		
	} while (opcion != 5);
}

void mostrarMenuPrestamos() {
	cout << "\n========================================\n";
	cout << "    GESTION DE PRESTAMOS\n";
	if (esAdministrador) {
		cout << "     [MODO ADMINISTRADOR ACTIVO]\n";
	}
	cout << "========================================\n";
	cout << "1. Registrar Prestamo\n";
	cout << "2. Ver Prestamos por Cedula\n";
	cout << "3. Ver Todos los Prestamos\n";
	cout << "4. Devolver Libro\n";
	cout << "5. Volver al Menu Principal\n";
	cout << "========================================\n";
	cout << "Seleccione una opcion: ";
}

void limpiarPantalla() {
	system("cls");
}

void pausar() {
	cout << "\nPresione cualquier tecla para continuar...";
	getch();
}
