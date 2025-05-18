// Libro.h - Implementación de jerarquía de libros, patrón Factory Method y Decorator
#pragma once
#include <string>
#include <vector>

/**
* @class Libro
* @brief Clase base abstracta para todos los tipos de libros
*/
class Libro {
protected:
	int id;
	std::string titulo;
	std::string autor;
	std::string isbn;
	int anioPublicacion;
	std::string editorial;
	std::vector<std::string> categorias;
	bool disponible;
	
public:
	/**
	* @brief Constructor base para libros
	*/
	Libro(int id, const std::string& titulo, const std::string& autor, 
		  const std::string& isbn, int anioPublicacion, const std::string& editorial);
	
	/**
	* @brief Destructor virtual
	*/
	virtual ~Libro() {}
	
	/**
	* @brief Obtiene una descripción completa del libro
	* @return String con la descripción
	*/
	virtual std::string getDescripcion() const = 0;
	
	/**
	* @brief Obtiene el ID del libro
	* @return ID único
	*/
	int getId() const { return id; }
	
	/**
	* @brief Obtiene el título del libro
	* @return Título
	*/
	const std::string& getTitulo() const { return titulo; }
	
	/**
	* @brief Obtiene el autor del libro
	* @return Autor
	*/
	const std::string& getAutor() const { return autor; }
	
	/**
	* @brief Obtiene el ISBN del libro
	* @return ISBN
	*/
	const std::string& getIsbn() const { return isbn; }
	
	/**
	* @brief Verifica si el libro está disponible
	* @return true si está disponible
	*/
	bool estaDisponible() const { return disponible; }
	
	/**
	* @brief Establece la disponibilidad del libro
	* @param estado Nuevo estado de disponibilidad
	*/
	void setDisponible(bool estado) { disponible = estado; }
	
	/**
	* @brief Añade una categoría al libro
	* @param categoria Categoría a añadir
	*/
	void agregarCategoria(const std::string& categoria);
	
	/**
	* @brief Obtiene las categorías del libro
	* @return Vector con las categorías
	*/
	const std::vector<std::string>& getCategorias() const { return categorias; }
	
	/**
	* @brief Método virtual para obtener el tipo de libro
	* @return String con el tipo
	*/
	virtual std::string getTipo() const = 0;
};

/**
* @class LibroFisico
* @brief Representa un libro físico en el sistema
*/
class LibroFisico : public Libro {
private:
	std::string ubicacion;
	int numPaginas;
	std::string estado; // Nuevo, Usado, Deteriorado, etc.
	
public:
	/**
	* @brief Constructor para libro físico
	*/
	LibroFisico(int id, const std::string& titulo, const std::string& autor, 
				const std::string& isbn, int anioPublicacion, const std::string& editorial,
				const std::string& ubicacion, int numPaginas, const std::string& estado);
	
	/**
	* @brief Implementación de getDescripcion para libro físico
	*/
	std::string getDescripcion() const override;
	
	/**
	* @brief Obtiene la ubicación física del libro
	* @return String con la ubicación
	*/
	const std::string& getUbicacion() const { return ubicacion; }
	
	/**
	* @brief Obtiene el número de páginas
	* @return Número de páginas
	*/
	int getNumPaginas() const { return numPaginas; }
	
	/**
	* @brief Obtiene el estado físico del libro
	* @return Estado del libro
	*/
	const std::string& getEstado() const { return estado; }
	
	/**
	* @brief Establece un nuevo estado para el libro
	* @param nuevoEstado Estado a establecer
	*/
	void setEstado(const std::string& nuevoEstado) { estado = nuevoEstado; }
	
	/**
	* @brief Implementación de getTipo
	*/
	std::string getTipo() const override { return "Fisico"; }
};

/**
* @class LibroDigital
* @brief Representa un libro en formato digital
*/
class LibroDigital : public Libro {
private:
	std::string formato; // PDF, EPUB, etc.
	std::string url;
	long tamanioBytes;
	bool descargable;
	
public:
	/**
	* @brief Constructor para libro digital
	*/
	LibroDigital(int id, const std::string& titulo, const std::string& autor, 
				 const std::string& isbn, int anioPublicacion, const std::string& editorial,
				 const std::string& formato, const std::string& url, 
				 long tamanioBytes, bool descargable);
	
	/**
	* @brief Implementación de getDescripcion para libro digital
	*/
	std::string getDescripcion() const override;
	
	/**
	* @brief Obtiene el formato del libro digital
	* @return Formato del libro
	*/
	const std::string& getFormato() const { return formato; }
	
	/**
	* @brief Obtiene la URL del libro digital
	* @return URL de acceso
	*/
	const std::string& getUrl() const { return url; }
	
	/**
	* @brief Verifica si el libro es descargable
	* @return true si es descargable
	*/
	bool esDescargable() const { return descargable; }
	
	/**
	* @brief Implementación de getTipo
	*/
	std::string getTipo() const override { return "Digital"; }
};

/**
* @class LibroFactory
* @brief Factory Method para crear diferentes tipos de libros
*/
class LibroFactory {
public:
	/**
	* @brief Crea un libro físico
	* @param datos Mapa con los datos necesarios
	* @return Puntero al libro creado o nullptr si falló
	*/
	static Libro* crearLibroFisico(const std::string& titulo, const std::string& autor,
								   const std::string& isbn, int anioPublicacion, 
								   const std::string& editorial, const std::string& ubicacion,
								   int numPaginas, const std::string& estado);
	
	/**
	* @brief Crea un libro digital
	* @param datos Mapa con los datos necesarios
	* @return Puntero al libro creado o nullptr si falló
	*/
	static Libro* crearLibroDigital(const std::string& titulo, const std::string& autor,
									const std::string& isbn, int anioPublicacion, 
									const std::string& editorial, const std::string& formato,
									const std::string& url, long tamanioBytes, bool descargable);
	
	/**
	* @brief Genera un ID único para libros
	* @return ID único
	*/
	static int generarId();
};

/**
* @class LibroDecorator
* @brief Implementación del patrón Decorator para añadir funcionalidades a libros
*/
class LibroDecorator : public Libro {
protected:
	Libro* libroBase;
	
public:
	/**
	* @brief Constructor para el decorador
	* @param base Libro base a decorar
	*/
	LibroDecorator(Libro* base);
	
	/**
	* @brief Destructor virtual
	*/
	virtual ~LibroDecorator();
	
	/**
	* @brief Implementación por defecto que delega en el libro base
	*/
	std::string getDescripcion() const override;
	
	/**
	* @brief Delegación al método del libro base
	*/
	std::string getTipo() const override { return libroBase->getTipo(); }
};

/**
* @class LibroConNotas
* @brief Decorator que añade notas personalizadas a un libro
*/
class LibroConNotas : public LibroDecorator {
private:
	std::vector<std::string> notas;
	
public:
	/**
	* @brief Constructor
	* @param base Libro base a decorar
	*/
	LibroConNotas(Libro* base);
	
	/**
	* @brief Implementación que extiende la descripción con notas
	*/
	std::string getDescripcion() const override;
	
	/**
	* @brief Añade una nota al libro
	* @param nota Texto de la nota
	*/
	void agregarNota(const std::string& nota);
	
	/**
	* @brief Obtiene todas las notas del libro
	* @return Vector con las notas
	*/
	const std::vector<std::string>& getNotas() const { return notas; }
};

/**
* @class LibroConMarcadores
* @brief Decorator que añade marcadores de página a un libro
*/
class LibroConMarcadores : public LibroDecorator {
private:
	std::vector<std::pair<int, std::string>> marcadores; // página y descripción
	
public:
	/**
	* @brief Constructor
	* @param base Libro base a decorar
	*/
	LibroConMarcadores(Libro* base);
	
	/**
	* @brief Implementación que extiende la descripción con marcadores
	*/
	std::string getDescripcion() const override;
	
	/**
	* @brief Añade un marcador al libro
	* @param pagina Número de página
	* @param descripcion Descripción del marcador
	*/
	void agregarMarcador(int pagina, const std::string& descripcion);
	
	/**
	* @brief Obtiene todos los marcadores del libro
	* @return Vector con los marcadores
	*/
	const std::vector<std::pair<int, std::string>>& getMarcadores() const { return marcadores; }
};
