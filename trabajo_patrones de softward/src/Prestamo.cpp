#include "../include/Prestamo.h"
#include <iostream>

// Inicialización de variables estáticas
int Prestamo::ultimoId = 0;

// Implementación de la clase Prestamo
Prestamo::Prestamo(Libro* libro, Usuario* usuario)
	: libro(libro), usuario(usuario) {
	id = ++ultimoId;
	estado = new Disponible();
	fechaPrestamo = std::chrono::system_clock::now();
	// Fecha de devolución predeterminada: 14 días después
	fechaDevolucion = fechaPrestamo + std::chrono::hours(24 * 14);
}

Prestamo::~Prestamo() {
	delete estado;
}

void Prestamo::cambiarEstado(EstadoPrestamo* nuevo) {
	delete estado;
	estado = nuevo;
}

std::string Prestamo::estadoActual() const {
	return estado->nombre();
}

int Prestamo::getId() const {
	return id;
}

Libro* Prestamo::getLibro() const {
	return libro;
}

Usuario* Prestamo::getUsuario() const {
	return usuario;
}

void Prestamo::setFechaDevolucion(const std::chrono::system_clock::time_point& fecha) {
	fechaDevolucion = fecha;
}

std::chrono::system_clock::time_point Prestamo::getFechaPrestamo() const {
	return fechaPrestamo;
}

std::chrono::system_clock::time_point Prestamo::getFechaDevolucion() const {
	return fechaDevolucion;
}

bool Prestamo::estaVencido() const {
	auto ahora = std::chrono::system_clock::now();
	return ahora > fechaDevolucion;
}

int Prestamo::diasRestantes() const {
	auto ahora = std::chrono::system_clock::now();
	
	if (ahora > fechaDevolucion) {
		// Ya está vencido, devolver días en negativo
		auto diferencia = ahora - fechaDevolucion;
		return -static_cast<int>(std::chrono::duration_cast<std::chrono::hours>(diferencia).count() / 24);
	} else {
		// Todavía no venció, devolver días restantes
		auto diferencia = fechaDevolucion - ahora;
		return static_cast<int>(std::chrono::duration_cast<std::chrono::hours>(diferencia).count() / 24);
	}
}

// Implementación de los estados

void Disponible::manejar(Prestamo* prestamo) {
	std::cout << "El libro está disponible para préstamo." << std::endl;
	
	// Marcar el libro como no disponible cuando se presta
	prestamo->getLibro()->setDisponible(false);
	
	// Cambiar al estado "Prestado"
	prestamo->cambiarEstado(new Prestado());
}

void Prestado::manejar(Prestamo* prestamo) {
	std::cout << "Procesando devolución del libro..." << std::endl;
	
	// Verificar si está vencido
	if (prestamo->estaVencido()) {
		std::cout << "El préstamo está vencido. Se aplicarán multas." << std::endl;
		prestamo->cambiarEstado(new Retrasado());
	} else {
		// Marcar el libro como disponible
		prestamo->getLibro()->setDisponible(true);
		prestamo->cambiarEstado(new Disponible());
	}
}

void Reservado::manejar(Prestamo* prestamo) {
	std::cout << "El libro está reservado. Comprobando disponibilidad..." << std::endl;
	
	// Lógica para manejar la reserva
	// Por simplicidad, pasamos directamente a estado "Prestado"
	prestamo->cambiarEstado(new Prestado());
}

void Retrasado::manejar(Prestamo* prestamo) {
	std::cout << "Procesando devolución de libro retrasado..." << std::endl;
	
	// Calcular multa (en un sistema real)
	int diasRetraso = -prestamo->diasRestantes(); // Convertir a positivo
	double multa = diasRetraso * 0.5; // 50 centavos por día de retraso
	
	std::cout << "Multa por retraso: $" << multa << std::endl;
	
	// Marcar el libro como disponible y cambiar el estado
	prestamo->getLibro()->setDisponible(true);
	prestamo->cambiarEstado(new Disponible());
}

