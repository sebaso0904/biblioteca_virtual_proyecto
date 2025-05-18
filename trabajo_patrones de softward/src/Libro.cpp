// Libro.cpp - Implementaci�n de clases de libros
#include "Libro.h"
#include <sstream>

// Contador est�tico para generar IDs �nicos
static int contadorIdLibro = 5000;

// Implementaci�n de Libro base
Libro::Libro(int id, const std::string& titulo, const std::string& autor, 
			 const std::string& isbn, int anioPublicacion, const std::string& editorial)
	: id(id), titulo(titulo), autor(autor), isbn(isbn), 
	anioPublicacion(anioPublicacion), editorial(editorial), disponible(true) {
}

void Libro::agregarCategoria(const std::string& categoria) {
	categorias.push_back(categoria);
}

// Implementaci�n de LibroFisico
LibroFisico::LibroFisico(int id, const std::string& titulo, const std::string& autor, 
						 const std::string& isbn, int anioPublicacion, const std::string& editorial,
						 const std::string& ubicacion, int numPaginas, const std::string& estado)
	: Libro(id, titulo, autor, isbn, anioPublicacion, editorial),
	ubicacion(ubicacion), numPaginas(numPaginas), estado(estado) {
}

std::string LibroFisico::getDescripcion() const {
	std::stringstream ss;
	ss << "LIBRO F�SICO: " << titulo << " por " << autor << std::endl;
	ss << "ISBN: " << isbn << " | Editorial: " << editorial << " | A�o: " << anioPublicacion << std::endl;
	ss << "Ubicaci�n: " << ubicacion << " | P�ginas: " << numPaginas << " | Estado: " << estado << std::endl;
	
	if (!categorias.empty()) {
		ss << "Categor�as: ";
		for (size_t i = 0; i < categorias.size(); ++i) {
			ss << categorias[i];
			if (i < categorias.size() - 1) ss << ", ";
		}
		ss << std::endl;
	}
	
	ss << "Disponibilidad: " << (disponible ? "Disponible" : "No disponible");
	
	return ss.str();
}

// Implementaci�n de LibroDigital
LibroDigital::LibroDigital(int id, const std::string& titulo, const std::string& autor, 
						   const std::string& isbn, int anioPublicacion, const std::string& editorial,
						   const std::string& formato, const std::string& url, 
						   long tamanioBytes, bool descargable)
	: Libro(id, titulo, autor, isbn, anioPublicacion, editorial),
	formato(formato), url(url), tamanioBytes(tamanioBytes), descargable(descargable) {
}

std::string LibroDigital::getDescripcion() const {
	std::stringstream ss;
	ss << "LIBRO DIGITAL: " << titulo << " por " << autor << std::endl;
	ss << "ISBN: " << isbn << " | Editorial: " << editorial << " | A�o: " << anioPublicacion << std::endl;
	ss << "Formato: " << formato << " | Tama�o: " << (tamanioBytes / 1024.0 / 1024.0) << " MB" << std::endl;
	ss << "URL de acceso: " << url << std::endl;
	ss << "Descargable: " << (descargable ? "S�" : "No") << std::endl;
	
	if (!categorias.empty()) {
		ss << "Categor�as: ";
		for (size_t i = 0; i < categorias.size(); ++i) {
			ss << categorias[i];
			if (i < categorias.size() - 1) ss << ", ";
		}
		ss << std::endl;
	}
	
	ss << "Disponibilidad: " << (disponible ? "Disponible" : "No disponible");
	
	return ss.str();
}

// Implementaci�n de LibroFactory
Libro* LibroFactory::crearLibroFisico(const std::string& titulo, const std::string& autor,
									  const std::string& isbn, int anioPublicacion, 
									  const std::string& editorial, const std::string& ubicacion,
									  int numPaginas, const std::string& estado) {
	int id = generarId();
	return new LibroFisico(id, titulo, autor, isbn, anioPublicacion, editorial,
						   ubicacion, numPaginas, estado);
}

Libro* LibroFactory::crearLibroDigital(const std::string& titulo, const std::string& autor,
									   const std::string& isbn, int anioPublicacion, 
									   const std::string& editorial, const std::string& formato,
									   const std::string& url, long tamanioBytes, bool descargable) {
	int id = generarId();
	return new LibroDigital(id, titulo, autor, isbn, anioPublicacion, editorial,
							formato, url, tamanioBytes, descargable);
}

int LibroFactory::generarId() {
	return contadorIdLibro++;
}

// Implementaci�n de LibroDecorator
LibroDecorator::LibroDecorator(Libro* base)
	: Libro(base->getId(), base->getTitulo(), base->getAutor(), base->getIsbn(), 0, ""),
	libroBase(base) {
}

LibroDecorator::~LibroDecorator() {
	// No eliminamos libroBase aqu� para evitar doble eliminaci�n
}

std::string LibroDecorator::getDescripcion() const {
	return libroBase->getDescripcion();
}

// Implementaci�n de LibroConNotas
LibroConNotas::LibroConNotas(Libro* base) : LibroDecorator(base) {
}

std::string LibroConNotas::getDescripcion() const {
	std::stringstream ss;
	ss << libroBase->getDescripcion() << std::endl;
	
	if (!notas.empty()) {
		ss << "\n--- NOTAS ---" << std::endl;
		for (size_t i = 0; i < notas.size(); ++i) {
			ss << (i + 1) << ". " << notas[i] << std::endl;
		}
	}
	
	return ss.str();
}

void LibroConNotas::agregarNota(const std::string& nota) {
	notas.push_back(nota);
}

// Implementaci�n de LibroConMarcadores
LibroConMarcadores::LibroConMarcadores(Libro* base) : LibroDecorator(base) {
}

std::string LibroConMarcadores::getDescripcion() const {
	std::stringstream ss;
	ss << libroBase->getDescripcion() << std::endl;
	
	if (!marcadores.empty()) {
		ss << "\n--- MARCADORES ---" << std::endl;
		for (const auto& marcador : marcadores) {
			ss << "P�gina " << marcador.first << ": " << marcador.second << std::endl;
		}
	}
	
	return ss.str();
}

void LibroConMarcadores::agregarMarcador(int pagina, const std::string& descripcion) {
	marcadores.push_back(std::make_pair(pagina, descripcion));
}
