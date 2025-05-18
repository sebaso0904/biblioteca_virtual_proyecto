#pragma once
#include <vector>
#include <string>
#include "Libro.h"

/**
* Clase base para el patr�n Composite que permite manejar
* la estructura jer�rquica de la biblioteca
*/
class ElementoBiblioteca {
public:
	virtual void mostrar() const = 0;
	virtual ~ElementoBiblioteca() {}
};

/**
* Implementa una categor�a que puede contener otras categor�as o libros
* siguiendo el patr�n Composite
*/
class Categoria : public ElementoBiblioteca {
private:
	std::string nombre;
	std::vector<ElementoBiblioteca*> hijos;
public:
	Categoria(const std::string& nombre);
	void agregar(ElementoBiblioteca* elem);
	void mostrar() const override;
	std::string getNombre() const;
};

/**
* Implementa un libro como elemento hoja dentro del patr�n Composite
*/
class LibroElemento : public ElementoBiblioteca {
private:
	Libro* libro;
public:
	LibroElemento(Libro* libro) : libro(libro) {}
	void mostrar() const override;
};
