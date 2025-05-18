#pragma once
#include <string>
#include <chrono>
#include "Libro.h"
#include "Usuario.h"

// Declaraci�n adelantada para evitar dependencia circular
class EstadoPrestamo;

/**
* Clase que implementa el patr�n State para gestionar los estados de un pr�stamo
*/
class Prestamo {
private:
	int id;
	static int ultimoId;
	Libro* libro;
	Usuario* usuario;
	EstadoPrestamo* estado;
	std::chrono::system_clock::time_point fechaPrestamo;
	std::chrono::system_clock::time_point fechaDevolucion;
	
public:
	Prestamo(Libro* libro, Usuario* usuario);
	~Prestamo();
	
	void cambiarEstado(EstadoPrestamo* nuevo);
	std::string estadoActual() const;
	
	int getId() const;
	Libro* getLibro() const;
	Usuario* getUsuario() const;
	void setFechaDevolucion(const std::chrono::system_clock::time_point& fecha);
	std::chrono::system_clock::time_point getFechaPrestamo() const;
	std::chrono::system_clock::time_point getFechaDevolucion() const;
	
	bool estaVencido() const;
	int diasRestantes() const;
};

/**
* Interfaz base para todos los estados de pr�stamo (State pattern)
*/
class EstadoPrestamo {
public:
	virtual void manejar(Prestamo* prestamo) = 0;
	virtual std::string nombre() const = 0;
	virtual ~EstadoPrestamo() {}
};

/**
* Estado para libros disponibles
*/
class Disponible : public EstadoPrestamo {
public:
	void manejar(Prestamo* prestamo) override;
	std::string nombre() const override { return "Disponible"; }
};

/**
* Estado para libros prestados
*/
class Prestado : public EstadoPrestamo {
public:
	void manejar(Prestamo* prestamo) override;
	std::string nombre() const override { return "Prestado"; }
};

/**
* Estado para libros reservados
*/
class Reservado : public EstadoPrestamo {
public:
	void manejar(Prestamo* prestamo) override;
	std::string nombre() const override { return "Reservado"; }
};

/**
* Estado para pr�stamos con fecha vencida
*/
class Retrasado : public EstadoPrestamo {
public:
	void manejar(Prestamo* prestamo) override;
	std::string nombre() const override { return "Retrasado"; }
};
