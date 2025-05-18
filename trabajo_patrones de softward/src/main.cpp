#include <iostream>
#include <memory>
#include "../include/Sistema.h"
#include "../include/Usuario.h"
#include "../include/Libro.h"
#include "../include/Prestamo.h"
#include "../include/EstrategiaBusqueda.h"
#include "../include/ElementoBiblioteca.h"

// Funci�n de utilidad para imprimir una l�nea separadora
void imprimirSeparador() {
	std::cout << "\n------------------------------------------------\n";
}

int main() {
	std::cout << "SISTEMA DE BIBLIOTECA DIGITAL\n";
	imprimirSeparador();
	
	// Obtener la instancia del sistema (Singleton)
	Sistema* sistema = Sistema::getInstancia();
	
	// Crear algunos usuarios usando el Factory Method
	std::cout << "Creando usuarios...\n";
	
	std::map<std::string, std::string> datosEstudiante = {
		{"nombre", "Juan P�rez"},
	{"correo", "juan@universidad.edu"},
		{"contrasena", "pass123"},
	{"carrera", "Ingenier�a de Sistemas"}
	};
	
	std::map<std::string, std::string> datosProfesor = {
		{"nombre", "Mar�a Rodr�guez"},
	{"correo", "maria@universidad.edu"},
		{"contrasena", "prof456"},
	{"departamento", "Ciencias de la Computaci�n"}
	};
	
	std::map<std::string, std::string> datosAdmin = {
		{"nombre", "Carlos G�mez"},
	{"correo", "carlos@universidad.edu"},
		{"contrasena", "admin789"},
	{"nivelAcceso", "3"}
	};
	
	Usuario* estudiante = UsuarioFactory::crearUsuario("Estudiante", datosEstudiante);
	Usuario* profesor = UsuarioFactory::crearUsuario("Profesor", datosProfesor);
	Usuario* administrador = UsuarioFactory::crearUsuario("Administrador", datosAdmin);
	
	sistema->agregarUsuario(estudiante);
	sistema->agregarUsuario(profesor);
	sistema->agregarUsuario(administrador);
	
	std::cout << "Usuarios creados: " << estudiante->getNombre() << ", " 
		<< profesor->getNombre() << ", " << administrador->getNombre() << "\n";
	
	imprimirSeparador();
	
	// Crear libros usando el Factory Method
	std::cout << "Creando libros...\n";
	
	Libro* libroC = LibroFactory::crearLibro("Fisico", "Programaci�n en C", "Bjarne Stroustrup", "Estante A-12");
	Libro* libroJava = LibroFactory::crearLibro("Fisico", "Java para principiantes", "James Gosling", "Estante B-5");
	Libro* libroPython = LibroFactory::crearLibro("Digital", "Python Avanzado", "Guido van Rossum", "PDF");
	
	// Aplicar decoradores a algunos libros
	libroC = new LibroConNotas(libroC, "Notas sobre programaci�n estructurada");
	libroPython = new LibroConMarcadores(libroPython);
	
	// Agregar marcadores al libro de Python
	dynamic_cast<LibroConMarcadores*>(libroPython)->agregarMarcador(42);
	dynamic_cast<LibroConMarcadores*>(libroPython)->agregarMarcador(78);
	
	sistema->agregarLibro(libroC);
	sistema->agregarLibro(libroJava);
	sistema->agregarLibro(libroPython);
	
	std::cout << "Libros agregados al sistema\n";
	
	imprimirSeparador();
	
	// Crear estructura de categor�as usando el patr�n Composite
	std::cout << "Creando estructura de categor�as...\n";
	
	auto informatica = new Categoria("Inform�tica");
	auto programacion = new Categoria("Programaci�n");
	auto redes = new Categoria("Redes");
	
	informatica->agregar(programacion);
	informatica->agregar(redes);
	
	programacion->agregar(new LibroElemento(libroC));
	programacion->agregar(new LibroElemento(libroJava));
	programacion->agregar(new LibroElemento(libroPython));
	
	std::cout << "Estructura de categor�as creada\n";
	std::cout << "Mostrando categor�a principal:\n";
	informatica->mostrar();
	
	imprimirSeparador();
	
	// Realizar b�squedas usando el patr�n Strategy
	std::cout << "Realizando b�squedas...\n";
	
	// Crear estrategias de b�squeda
	BuscarPorTitulo buscarTitulo;
	BuscarPorAutor buscarAutor;
	
	// Crear contexto y configurar estrategia
	ContextoBusqueda contexto(&buscarTitulo);
	
	// Realizar b�squeda por t�tulo
	std::cout << "B�squeda por t�tulo (Python):\n";
	auto resultadosTitulo = contexto.ejecutarBusqueda(sistema->getLibros(), "Python");
	
	for (auto libro : resultadosTitulo) {
		std::cout << libro->getDescripcion() << "\n";
	}
	
	// Cambiar estrategia y buscar por autor
	contexto.setEstrategia(&buscarAutor);
	
	std::cout << "\nB�squeda por autor (Guido):\n";
	auto resultadosAutor = contexto.ejecutarBusqueda(sistema->getLibros(), "Guido");
	
	for (auto libro : resultadosAutor) {
		std::cout << libro->getDescripcion() << "\n";
	}
	
	imprimirSeparador();
	
	// Gestionar pr�stamos usando el patr�n State
	std::cout << "Gestionando pr�stamos...\n";
	
	// Realizar un pr�stamo
	std::cout << "Estado inicial del libro Java: " 
		<< (libroJava->estaDisponible() ? "Disponible" : "No disponible") << "\n";
	
	std::cout << "Intentando prestar libro Java a " << estudiante->getNombre() << "...\n";
	if (estudiante->prestarLibro(libroJava)) {
		std::cout << "Pr�stamo realizado exitosamente.\n";
	} else {
		std::cout << "No se pudo realizar el pr�stamo.\n";
	}
	
	std::cout << "Estado actual del libro Java: " 
								 << (libroJava->estaDisponible() ? "Disponible" : "No disponible") << "\n";
	
	// Mostrar pr�stamos activos del estudiante
	std::cout << "\nPr�stamos activos de " << estudiante->getNombre() << ":\n";
	for (auto prestamo : estudiante->getPrestamos()) {
		std::cout << "- " << prestamo->getLibro()->getTitulo() 
			<< " (Estado: " << prestamo->estadoActual() << ")\n";
		std::cout << "  D�as restantes: " << prestamo->diasRestantes() << "\n";
	}
	
	// Devolver el libro
	std::cout << "\nDevolviendo libro Java...\n";
	estudiante->devolverLibro(libroJava);
	
	std::cout << "Estado final del libro Java: " 
		<< (libroJava->estaDisponible() ? "Disponible" : "No disponible") << "\n";
	
	imprimirSeparador();
	
	// Simulaci�n de autenticaci�n de usuario
	std::cout << "Simulando autenticaci�n de usuario...\n";
	
	std::string correo = "juan@universidad.edu";
	std::string contrasena = "pass123";
	
	Usuario* usuarioAutenticado = sistema->autenticarUsuario(correo, contrasena);
	
	if (usuarioAutenticado) {
		std::cout << "Autenticaci�n exitosa. Bienvenido " << usuarioAutenticado->getNombre() << "\n";
		std::cout << "Rol: ";
		
		switch (usuarioAutenticado->getRol()) {
		case RolUsuario::ESTUDIANTE:
			std::cout << "Estudiante";
		break;
		case RolUsuario::PROFESOR:
			std::cout << "Profesor";
		break;
		case RolUsuario::ADMINISTRADOR:
			std::cout << "Administrador";
		break;
		}
		std::cout << "\n";
	} else {
		std::cout << "Error de autenticaci�n. Credenciales incorrectas.\n";
	}
	
	imprimirSeparador();
	std::cout << "Finalizando demostraci�n de la biblioteca digital.\n";
	
	// Limpieza de memoria (en un sistema real usar�amos smart pointers)
	delete informatica; // Esto elimina toda la estructura Composite
	delete estudiante;
	delete profesor;
	delete administrador;
	
	// No necesitamos eliminar libroC, libroJava ni libroPython aqu�
	// porque el sistema se encarga de ellos
	
	return 0;
}

