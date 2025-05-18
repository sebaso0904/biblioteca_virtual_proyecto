// Libro.h - Implementaci�n de jerarqu�a de libros, patr�n Factory Method y Decorator
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
	* @brief Obtiene una descripci�n completa del libro
	* @return String con la descripci�n
	*/
	virtual std::string getDescripcion() const = 0;
	
	/**
	* @brief Obtiene el ID del libro
	* @return ID �nico
	*/
	int getId() const { return id; }
	
	/**
	* @brief Obtiene el t�tulo del libro
	* @return T�tulo
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
	* @brief Verifica si el libro est� disponible
	* @return true si est� disponible
	*/
	bool estaDisponible() const { return disponible; }
	
	/**
	* @brief Establece la disponibilidad del libro
	* @param estado Nuevo estado de disponibilidad
	*/
	void setDisponible(bool estado) { disponible = estado; }
	
	/**
	* @brief A�ade una categor�a al libro
	* @param categoria Categor�a a a�adir
	*/
	void agregarCategoria(const std::string& categoria);
	
	/**
	* @brief Obtiene las categor�as del libro
	* @return Vector con las categor�as
	*/
	const std::vector<std::string>& getCategorias() const { return categorias; }
	
	/**
	* @brief M�todo virtual para obtener el tipo de libro
	* @return String con el tipo
	*/
	virtual std::string getTipo() const = 0;
};

/**
* @class LibroFisico
* @brief Representa un libro f�sico en el sistema
*/
class LibroFisico : public Libro {
private:
	std::string ubicacion;
	int numPaginas;
	std::string estado; // Nuevo, Usado, Deteriorado, etc.
	
public:
	/**
	* @brief Constructor para libro f�sico
	*/
	LibroFisico(int id, const std::string& titulo, const std::string& autor, 
				const std::string& isbn, int anioPublicacion, const std::string& editorial,
				const std::string& ubicacion, int numPaginas, const std::string& estado);
	
	/**
	* @brief Implementaci�n de getDescripcion para libro f�sico
	*/
	std::string getDescripcion() const override;
	
	/**
	* @brief Obtiene la ubicaci�n f�sica del libro
	* @return String con la ubicaci�n
	*/
	const std::string& getUbicacion() const { return ubicacion; }
	
	/**
	* @brief Obtiene el n�mero de p�ginas
	* @return N�mero de p�ginas
	*/
	int getNumPaginas() const { return numPaginas; }
	
	/**
	* @brief Obtiene el estado f�sico del libro
	* @return Estado del libro
	*/
	const std::string& getEstado() const { return estado; }
	
	/**
	* @brief Establece un nuevo estado para el libro
	* @param nuevoEstado Estado a establecer
	*/
	void setEstado(const std::string& nuevoEstado) { estado = nuevoEstado; }
	
	/**
	* @brief Implementaci�n de getTipo
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
	* @brief Implementaci�n de getDescripcion para libro digital
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
	* @brief Implementaci�n de getTipo
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
	* @brief Crea un libro f�sico
	* @param datos Mapa con los datos necesarios
	* @return Puntero al libro creado o nullptr si fall�
	*/
	static Libro* crearLibroFisico(const std::string& titulo, const std::string& autor,
								   const std::string& isbn, int anioPublicacion, 
								   const std::string& editorial, const std::string& ubicacion,
								   int numPaginas, const std::string& estado);
	
	/**
	* @brief Crea un libro digital
	* @param datos Mapa con los datos necesarios
	* @return Puntero al libro creado o nullptr si fall�
	*/
	static Libro* crearLibroDigital(const std::string& titulo, const std::string& autor,
									const std::string& isbn, int anioPublicacion, 
									const std::string& editorial, const std::string& formato,
									const std::string& url, long tamanioBytes, bool descargable);
	
	/**
	* @brief Genera un ID �nico para libros
	* @return ID �nico
	*/
	static int generarId();
};

/**
* @class LibroDecorator
* @brief Implementaci�n del patr�n Decorator para a�adir funcionalidades a libros
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
	* @brief Implementaci�n por defecto que delega en el libro base
	*/
	std::string getDescripcion() const override;
	
	/**
	* @brief Delegaci�n al m�todo del libro base
	*/
	std::string getTipo() const override { return libroBase->getTipo(); }
};

/**
* @class LibroConNotas
* @brief Decorator que a�ade notas personalizadas a un libro
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
	* @brief Implementaci�n que extiende la descripci�n con notas
	*/
	std::string getDescripcion() const override;
	
	/**
	* @brief A�ade una nota al libro
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
* @brief Decorator que a�ade marcadores de p�gina a un libro
*/
class LibroConMarcadores : public LibroDecorator {
private:
	std::vector<std::pair<int, std::string>> marcadores; // p�gina y descripci�n
	
public:
	/**
	* @brief Constructor
	* @param base Libro base a decorar
	*/
	LibroConMarcadores(Libro* base);
	
	/**
	* @brief Implementaci�n que extiende la descripci�n con marcadores
	*/
	std::string getDescripcion() const override;
	
	/**
	* @brief A�ade un marcador al libro
	* @param pagina N�mero de p�gina
	* @param descripcion Descripci�n del marcador
	*/
	void agregarMarcador(int pagina, const std::string& descripcion);
	
	/**
	* @brief Obtiene todos los marcadores del libro
	* @return Vector con los marcadores
	*/
	const std::vector<std::pair<int, std::string>>& getMarcadores() const { return marcadores; }
};
