// EstrategiaBusqueda.h - Implementaci�n del patr�n Strategy para b�squedas
#pragma once
#include <vector>
#include <string>

// Declaraci�n anticipada
class Libro;

/**
* @class EstrategiaBusqueda
* @brief Interfaz para estrategias de b�squeda (Strategy pattern)
*/
class EstrategiaBusqueda {
public:
	/**
	* @brief M�todo abstracto para realizar la b�squeda
	* @param libros Vector de libros donde buscar
	* @param criterio Texto o criterio de b�squeda
	* @return Vector con los resultados encontrados
	*/
	virtual std::vector<Libro*> buscar(const std::vector<Libro*>& libros, 
									   const std::string& criterio) = 0;
	
	/**
	* @brief Destructor virtual
	*/
	virtual ~EstrategiaBusqueda() {}
	
	/**
	* @brief Obtiene una descripci�n de la estrategia
	* @return String descriptivo
	*/
	virtual std::string getDescripcion() const = 0;
};

/**
* @class BuscarPorTitulo
* @brief Estrategia para buscar libros por t�tulo
*/
class BuscarPorTitulo : public EstrategiaBusqueda {
public:
	/**
	* @brief Implementaci�n de b�squeda por t�tulo
	*/
	std::vector<Libro*> buscar(const std::vector<Libro*>& libros, 
							   const std::string& criterio) override;
	
	/**
	* @brief Descripci�n de la estrategia
	*/
	std::string getDescripcion() const override { 
		return "B�squeda por t�tulo"; 
	}
};

/**
* @class BuscarPorAutor
* @brief Estrategia para buscar libros por autor
*/
class BuscarPorAutor : public EstrategiaBusqueda {
public:
	/**
	* @brief Implementaci�n de b�squeda por autor
	*/
	std::vector<Libro*> buscar(const std::vector<Libro*>& libros, 
							   const std::string& criterio) override;
	
	/**
	* @brief Descripci�n de la estrategia
	*/
	std::string getDescripcion() const override { 
		return "B�squeda por autor"; 
	}
};

/**
* @class BuscarPorCategoria
* @brief Estrategia para buscar libros por categor�a
*/
class BuscarPorCategoria : public EstrategiaBusqueda {
public:
	/**
	* @brief Implementaci�n de b�squeda por categor�a
	*/
	std::vector<Libro*> buscar(const std::vector<Libro*>& libros, 
							   const std::string& criterio) override;
	
	/**
	* @brief Descripci�n de la estrategia
	*/
	std::string getDescripcion() const override { 
		return "B�squeda por categor�a"; 
	}
};

/**
* @class BuscarPorDisponibilidad
* @brief Estrategia para buscar libros por disponibilidad
*/
class BuscarPorDisponibilidad : public EstrategiaBusqueda {
public:
	/**
	* @brief Implementaci�n de b�squeda por disponibilidad
	*/
	std::vector<Libro*> buscar(const std::vector<Libro*>& libros, 
							   const std::string& criterio) override;
	
	/**
	* @brief Descripci�n de la estrategia
	*/
	std::string getDescripcion() const override { 
		return "B�squeda por disponibilidad"; 
	}
};

/**
* @class BuscarPorA�o
* @brief Estrategia para buscar libros por a�o de publicaci�n
*/
class BuscarPorAnio : public EstrategiaBusqueda {
public:
	/**
	* @brief Implementaci�n de b�squeda por a�o
	*/
	std::vector<Libro*> buscar(const std::vector<Libro*>& libros, 
							   const std::string& criterio) override;
	
	/**
	* @brief Descripci�n de la estrategia
	*/
	std::string getDescripcion() const override { 
		return "B�squeda por a�o de publicaci�n"; 
	}
};

/**
* @class EstrategiaBusquedaFactory
* @brief Factory para crear diferentes estrategias de b�squeda
*/
class EstrategiaBusquedaFactory {
public:
	/**
	* @brief Crea una estrategia seg�n el tipo especificado
	* @param tipo Tipo de estrategia a crear
	* @return Puntero a la estrategia creada o nullptr si no se reconoce
	*/
	static EstrategiaBusqueda* crearEstrategia(const std::string& tipo);
};

