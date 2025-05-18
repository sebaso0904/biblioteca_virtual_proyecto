#include "../include/Prestamo.h"
#include <iostream>

// Inicializaci�n de variables est�ticas
int Prestamo::ultimoId = 0;

// Implementaci�n de la clase Prestamo
Prestamo::Prestamo(Libro* libro, Usuario* usuario)
	: libro(libro), usuario(usuario) {
	id = ++ultimoId;
	estado = new Disponible();
	fechaPrestamo = std::chrono::system_clock::now();
	// Fecha de devoluci�n predeterminada: 14 d�as despu�s
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
		// Ya est� vencido, devolver d�as en negativo
		auto diferencia = ahora - fechaDevolucion;
		return -static_cast<int>(std::chrono::duration_cast<std::chrono::hours>(diferencia).count() / 24);
	} else {
		// Todav�a no venci�, devolver d�as restantes
		auto diferencia = fechaDevolucion - ahora;
		return static_cast<int>(std::chrono::duration_cast<std::chrono::hours>(diferencia).count() / 24);
	}
}

// Implementaci�n de los estados

void Disponible::manejar(Prestamo* prestamo) {
	std::cout << "El libro est� disponible para pr�stamo." << std::endl;
	
	// Marcar el libro como no disponible cuando se presta
	prestamo->getLibro()->setDisponible(false);
	
	// Cambiar al estado "Prestado"
	prestamo->cambiarEstado(new Prestado());
}

void Prestado::manejar(Prestamo* prestamo) {
	std::cout << "Procesando devoluci�n del libro..." << std::endl;
	
	// Verificar si est� vencido
	if (prestamo->estaVencido()) {
		std::cout << "El pr�stamo est� vencido. Se aplicar�n multas." << std::endl;
		prestamo->cambiarEstado(new Retrasado());
	} else {
		// Marcar el libro como disponible
		prestamo->getLibro()->setDisponible(true);
		prestamo->cambiarEstado(new Disponible());
	}
}

void Reservado::manejar(Prestamo* prestamo) {
	std::cout << "El libro est� reservado. Comprobando disponibilidad..." << std::endl;
	
	// L�gica para manejar la reserva
	// Por simplicidad, pasamos directamente a estado "Prestado"
	prestamo->cambiarEstado(new Prestado());
}

void Retrasado::manejar(Prestamo* prestamo) {
	std::cout << "Procesando devoluci�n de libro retrasado..." << std::endl;
	
	// Calcular multa (en un sistema real)
	int diasRetraso = -prestamo->diasRestantes(); // Convertir a positivo
	double multa = diasRetraso * 0.5; // 50 centavos por d�a de retraso
	
	std::cout << "Multa por retraso: $" << multa << std::endl;
	
	// Marcar el libro como disponible y cambiar el estado
	prestamo->getLibro()->setDisponible(true);
	prestamo->cambiarEstado(new Disponible());
}

