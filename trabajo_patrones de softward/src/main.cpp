#include <iostream>
#include <memory>
#include "../include/Sistema.h"
#include "../include/Usuario.h"
#include "../include/Libro.h"
#include "../include/Prestamo.h"
#include "../include/EstrategiaBusqueda.h"
#include "../include/ElementoBiblioteca.h"

// Función de utilidad para imprimir una línea separadora
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
		{"nombre", "Juan Pérez"},
	{"correo", "juan@universidad.edu"},
		{"contrasena", "pass123"},
	{"carrera", "Ingeniería de Sistemas"}
	};
	
	std::map<std::string, std::string> datosProfesor = {
		{"nombre", "María Rodríguez"},
	{"correo", "maria@universidad.edu"},
		{"contrasena", "prof456"},
	{"departamento", "Ciencias de la Computación"}
	};
	
	std::map<std::string, std::string> datosAdmin = {
		{"nombre", "Carlos Gómez"},
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
	
	Libro* libroC = LibroFactory::crearLibro("Fisico", "Programación en C", "Bjarne Stroustrup", "Estante A-12");
	Libro* libroJava = LibroFactory::crearLibro("Fisico", "Java para principiantes", "James Gosling", "Estante B-5");
	Libro* libroPython = LibroFactory::crearLibro("Digital", "Python Avanzado", "Guido van Rossum", "PDF");
	
	// Aplicar decoradores a algunos libros
	libroC = new LibroConNotas(libroC, "Notas sobre programación estructurada");
	libroPython = new LibroConMarcadores(libroPython);
	
	// Agregar marcadores al libro de Python
	dynamic_cast<LibroConMarcadores*>(libroPython)->agregarMarcador(42);
	dynamic_cast<LibroConMarcadores*>(libroPython)->agregarMarcador(78);
	
	sistema->agregarLibro(libroC);
	sistema->agregarLibro(libroJava);
	sistema->agregarLibro(libroPython);
	
	std::cout << "Libros agregados al sistema\n";
	
	imprimirSeparador();
	
	// Crear estructura de categorías usando el patrón Composite
	std::cout << "Creando estructura de categorías...\n";
	
	auto informatica = new Categoria("Informática");
	auto programacion = new Categoria("Programación");
	auto redes = new Categoria("Redes");
	
	informatica->agregar(programacion);
	informatica->agregar(redes);
	
	programacion->agregar(new LibroElemento(libroC));
	programacion->agregar(new LibroElemento(libroJava));
	programacion->agregar(new LibroElemento(libroPython));
	
	std::cout << "Estructura de categorías creada\n";
	std::cout << "Mostrando categoría principal:\n";
	informatica->mostrar();
	
	imprimirSeparador();
	
	// Realizar búsquedas usando el patrón Strategy
	std::cout << "Realizando búsquedas...\n";
	
	// Crear estrategias de búsqueda
	BuscarPorTitulo buscarTitulo;
	BuscarPorAutor buscarAutor;
	
	// Crear contexto y configurar estrategia
	ContextoBusqueda contexto(&buscarTitulo);
	
	// Realizar búsqueda por título
	std::cout << "Búsqueda por título (Python):\n";
	auto resultadosTitulo = contexto.ejecutarBusqueda(sistema->getLibros(), "Python");
	
	for (auto libro : resultadosTitulo) {
		std::cout << libro->getDescripcion() << "\n";
	}
	
	// Cambiar estrategia y buscar por autor
	contexto.setEstrategia(&buscarAutor);
	
	std::cout << "\nBúsqueda por autor (Guido):\n";
	auto resultadosAutor = contexto.ejecutarBusqueda(sistema->getLibros(), "Guido");
	
	for (auto libro : resultadosAutor) {
		std::cout << libro->getDescripcion() << "\n";
	}
	
	imprimirSeparador();
	
	// Gestionar préstamos usando el patrón State
	std::cout << "Gestionando préstamos...\n";
	
	// Realizar un préstamo
	std::cout << "Estado inicial del libro Java: " 
		<< (libroJava->estaDisponible() ? "Disponible" : "No disponible") << "\n";
	
	std::cout << "Intentando prestar libro Java a " << estudiante->getNombre() << "...\n";
	if (estudiante->prestarLibro(libroJava)) {
		std::cout << "Préstamo realizado exitosamente.\n";
	} else {
		std::cout << "No se pudo realizar el préstamo.\n";
	}
	
	std::cout << "Estado actual del libro Java: " 
								 << (libroJava->estaDisponible() ? "Disponible" : "No disponible") << "\n";
	
	// Mostrar préstamos activos del estudiante
	std::cout << "\nPréstamos activos de " << estudiante->getNombre() << ":\n";
	for (auto prestamo : estudiante->getPrestamos()) {
		std::cout << "- " << prestamo->getLibro()->getTitulo() 
			<< " (Estado: " << prestamo->estadoActual() << ")\n";
		std::cout << "  Días restantes: " << prestamo->diasRestantes() << "\n";
	}
	
	// Devolver el libro
	std::cout << "\nDevolviendo libro Java...\n";
	estudiante->devolverLibro(libroJava);
	
	std::cout << "Estado final del libro Java: " 
		<< (libroJava->estaDisponible() ? "Disponible" : "No disponible") << "\n";
	
	imprimirSeparador();
	
	// Simulación de autenticación de usuario
	std::cout << "Simulando autenticación de usuario...\n";
	
	std::string correo = "juan@universidad.edu";
	std::string contrasena = "pass123";
	
	Usuario* usuarioAutenticado = sistema->autenticarUsuario(correo, contrasena);
	
	if (usuarioAutenticado) {
		std::cout << "Autenticación exitosa. Bienvenido " << usuarioAutenticado->getNombre() << "\n";
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
		std::cout << "Error de autenticación. Credenciales incorrectas.\n";
	}
	
	imprimirSeparador();
	std::cout << "Finalizando demostración de la biblioteca digital.\n";
	
	// Limpieza de memoria (en un sistema real usaríamos smart pointers)
	delete informatica; // Esto elimina toda la estructura Composite
	delete estudiante;
	delete profesor;
	delete administrador;
	
	// No necesitamos eliminar libroC, libroJava ni libroPython aquí
	// porque el sistema se encarga de ellos
	
	return 0;
}

