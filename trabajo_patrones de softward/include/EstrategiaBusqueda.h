// EstrategiaBusqueda.h - Implementación del patrón Strategy para búsquedas
#pragma once
#include <vector>
#include <string>

// Declaración anticipada
class Libro;

/**
* @class EstrategiaBusqueda
* @brief Interfaz para estrategias de búsqueda (Strategy pattern)
*/
class EstrategiaBusqueda {
public:
	/**
	* @brief Método abstracto para realizar la búsqueda
	* @param libros Vector de libros donde buscar
	* @param criterio Texto o criterio de búsqueda
	* @return Vector con los resultados encontrados
	*/
	virtual std::vector<Libro*> buscar(const std::vector<Libro*>& libros, 
									   const std::string& criterio) = 0;
	
	/**
	* @brief Destructor virtual
	*/
	virtual ~EstrategiaBusqueda() {}
	
	/**
	* @brief Obtiene una descripción de la estrategia
	* @return String descriptivo
	*/
	virtual std::string getDescripcion() const = 0;
};

/**
* @class BuscarPorTitulo
* @brief Estrategia para buscar libros por título
*/
class BuscarPorTitulo : public EstrategiaBusqueda {
public:
	/**
	* @brief Implementación de búsqueda por título
	*/
	std::vector<Libro*> buscar(const std::vector<Libro*>& libros, 
							   const std::string& criterio) override;
	
	/**
	* @brief Descripción de la estrategia
	*/
	std::string getDescripcion() const override { 
		return "Búsqueda por título"; 
	}
};

/**
* @class BuscarPorAutor
* @brief Estrategia para buscar libros por autor
*/
class BuscarPorAutor : public EstrategiaBusqueda {
public:
	/**
	* @brief Implementación de búsqueda por autor
	*/
	std::vector<Libro*> buscar(const std::vector<Libro*>& libros, 
							   const std::string& criterio) override;
	
	/**
	* @brief Descripción de la estrategia
	*/
	std::string getDescripcion() const override { 
		return "Búsqueda por autor"; 
	}
};

/**
* @class BuscarPorCategoria
* @brief Estrategia para buscar libros por categoría
*/
class BuscarPorCategoria : public EstrategiaBusqueda {
public:
	/**
	* @brief Implementación de búsqueda por categoría
	*/
	std::vector<Libro*> buscar(const std::vector<Libro*>& libros, 
							   const std::string& criterio) override;
	
	/**
	* @brief Descripción de la estrategia
	*/
	std::string getDescripcion() const override { 
		return "Búsqueda por categoría"; 
	}
};

/**
* @class BuscarPorDisponibilidad
* @brief Estrategia para buscar libros por disponibilidad
*/
class BuscarPorDisponibilidad : public EstrategiaBusqueda {
public:
	/**
	* @brief Implementación de búsqueda por disponibilidad
	*/
	std::vector<Libro*> buscar(const std::vector<Libro*>& libros, 
							   const std::string& criterio) override;
	
	/**
	* @brief Descripción de la estrategia
	*/
	std::string getDescripcion() const override { 
		return "Búsqueda por disponibilidad"; 
	}
};

/**
* @class BuscarPorAño
* @brief Estrategia para buscar libros por año de publicación
*/
class BuscarPorAnio : public EstrategiaBusqueda {
public:
	/**
	* @brief Implementación de búsqueda por año
	*/
	std::vector<Libro*> buscar(const std::vector<Libro*>& libros, 
							   const std::string& criterio) override;
	
	/**
	* @brief Descripción de la estrategia
	*/
	std::string getDescripcion() const override { 
		return "Búsqueda por año de publicación"; 
	}
};

/**
* @class EstrategiaBusquedaFactory
* @brief Factory para crear diferentes estrategias de búsqueda
*/
class EstrategiaBusquedaFactory {
public:
	/**
	* @brief Crea una estrategia según el tipo especificado
	* @param tipo Tipo de estrategia a crear
	* @return Puntero a la estrategia creada o nullptr si no se reconoce
	*/
	static EstrategiaBusqueda* crearEstrategia(const std::string& tipo);
};

