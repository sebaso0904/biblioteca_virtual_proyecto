#pragma once
#include <vector>
#include <string>
#include "Libro.h"

/**
* Clase base para el patrón Composite que permite manejar
* la estructura jerárquica de la biblioteca
*/
class ElementoBiblioteca {
public:
	virtual void mostrar() const = 0;
	virtual ~ElementoBiblioteca() {}
};

/**
* Implementa una categoría que puede contener otras categorías o libros
* siguiendo el patrón Composite
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
* Implementa un libro como elemento hoja dentro del patrón Composite
*/
class LibroElemento : public ElementoBiblioteca {
private:
	Libro* libro;
public:
	LibroElemento(Libro* libro) : libro(libro) {}
	void mostrar() const override;
};
