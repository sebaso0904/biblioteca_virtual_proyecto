// Sistema.cpp - Implementación del Singleton
#include "Sistema.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

// Inicialización del atributo estático
Sistema* Sistema::instancia = nullptr;

Sistema* Sistema::getInstancia() {
	if (instancia == nullptr) {
		instancia = new Sistema();
	}
	return instancia;
}

Sistema::~Sistema() {
	// Liberar memoria de todas las colecciones
	for (auto usuario : usuarios) {
		delete usuario;
	}
	
	for (auto libro : libros) {
		delete libro;
	}
	
	for (auto prestamo : prestamos) {
		delete prestamo;
	}
	
	usuarios.clear();
	libros.clear();
	prestamos.clear();
}

bool Sistema::registrarUsuario(Usuario* usuario) {
	if (!usuario) return false;
	
	// Verificar si el usuario ya existe (por correo electrónico)
	auto it = std::find_if(usuarios.begin(), usuarios.end(), 
						   [usuario](Usuario* u) { return u->getCorreo() == usuario->getCorreo(); });
	
	if (it != usuarios.end()) {
		return false; // Usuario ya existe
	}
	
	usuarios.push_back(usuario);
	return true;
}

Usuario* Sistema::autenticarUsuario(const std::string& correo, const std::string& contrasena) {
	auto it = std::find_if(usuarios.begin(), usuarios.end(), 
						   [&correo, &contrasena](Usuario* u) { 
							   return u->getCorreo() == correo && u->verificarContrasena(contrasena); 
						   });
	
	return (it != usuarios.end()) ? *it : nullptr;
}

bool Sistema::agregarLibro(Libro* libro) {
	if (!libro) return false;
	
	// Podríamos verificar si el libro ya existe si tuviera un identificador único
	libros.push_back(libro);
	return true;
}

std::vector<Libro*> Sistema::buscarLibros(EstrategiaBusqueda* estrategia, const std::string& criterio) {
	if (!estrategia) {
		return {}; // Retornar vector vacío si no hay estrategia
	}
	
	return estrategia->buscar(libros, criterio);
}

Prestamo* Sistema::registrarPrestamo(Usuario* usuario, Libro* libro) {
	if (!usuario || !libro) return nullptr;
	
	// Verificar si el libro está disponible
	for (auto prestamo : prestamos) {
		if (prestamo->getLibro() == libro && prestamo->getEstadoActual() == "Prestado") {
			return nullptr; // Libro ya prestado
		}
	}
	
	// Crear nuevo préstamo
	Prestamo* nuevoPrestamo = new Prestamo(usuario, libro);
	nuevoPrestamo->cambiarEstado(new Prestado());
	prestamos.push_back(nuevoPrestamo);
	
	return nuevoPrestamo;
}

bool Sistema::registrarDevolucion(Prestamo* prestamo) {
	if (!prestamo) return false;
	
	// Verificar que el préstamo existe en el sistema
	auto it = std::find(prestamos.begin(), prestamos.end(), prestamo);
	if (it == prestamos.end()) {
		return false;
	}
	
	// Cambiar el estado del préstamo a disponible
	prestamo->cambiarEstado(new Disponible());
	return true;
}

std::vector<Prestamo*> Sistema::obtenerPrestamosUsuario(Usuario* usuario) {
	if (!usuario) return {};
	
	std::vector<Prestamo*> prestamosUsuario;
	for (auto prestamo : prestamos) {
		if (prestamo->getUsuario() == usuario && prestamo->getEstadoActual() == "Prestado") {
			prestamosUsuario.push_back(prestamo);
		}
	}
	
	return prestamosUsuario;
}

Libro* Sistema::obtenerLibroPorId(int id) {
	auto it = std::find_if(libros.begin(), libros.end(),
						   [id](Libro* libro) { return libro->getId() == id; });
	
	return (it != libros.end()) ? *it : nullptr;
}

Usuario* Sistema::obtenerUsuarioPorId(int id) {
	auto it = std::find_if(usuarios.begin(), usuarios.end(),
						   [id](Usuario* usuario) { return usuario->getId() == id; });
	
	return (it != usuarios.end()) ? *it : nullptr;
}
