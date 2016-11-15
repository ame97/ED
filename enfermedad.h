/* 
 * enfermedad.h
 * 
 * Copyright  (C) Juan F. Huete y Carlos Cano 
*/
#ifndef __ENFERMEDAD_H
#define __ENFERMEDAD_H

#include <string>
#include <iostream> 

using namespace std;

//! Clase enfermedad, asociada al TDA enfermedad
/*! enfermedad::enfermedad,  .....
 * Descripción contiene toda la información asociada a una enfermedad almacenada en la BD ClinVar-dbSNP (nombre de la enfermedad, id, BD que provee el id)
 
 @todo Implementa esta clase, junto con su documentación asociada

*/

class enfermedad {
private:
	string  name;       // nombre de la enfermedad. Almacenar completo en minúscula.
	string  ID;         // ID único para la enfermedad
	string  database;   // Base de datos que provee el ID

public:
	/** @brief Constructor por defecto de la clase enfermedad
	*/
	enfermedad ();

	/** @brief Constructor de la clase enfermedad. Asigna @a name, @a ID y @a database a los atributos 
	*	 del objeto creado.
	*   @param name Nombre de la enfermedad.
	*   @param ID Identificador de la enfermedad.
	*   @param database La base de datos donde se encuentra la información.
	*/
	enfermedad (const string & name, const string & ID, const string & database);

	/** @brief Asigna @a name al atributo del objeto llamado name.
	*/
	void setName(const string & name);
	
	/** @brief Asigna @a ID al atributo del objeto llamado ID.
	*/
	void setID(const string & ID);

	/** @brief Asigna @a database al atributo del objeto llamado database.
	*/
	void setDatabase(const string & database);

	/** @brief Deuelve el nombre de la enfermedad.
	*   @return El atributo name del objeto.
	*/
	string getName( ) const;
	
	/** @brief Deuelve el ID de la enfermedad.
	*   @return El atributo ID del objeto.
	*/
	string getID( ) const;
	
	/** @brief Deuelve donde se encuentra la información de la enfermedad.
	*   @return El atributo name del objeto.
	*/
	string getDatabase( ) const;
	
	/** @brief Sobrecarga del operador de asignación. Realiza la asignacion de una enfermedad a otra asignando
	*	   parámetro por parámetro.
	*   @param e Enfermedad que se desea asignar.
	*   @return Devuelve una referencia al objeto.
	*/
	enfermedad & operator=(const enfermedad & e);
	
	/** @brief Pasa a una cadena todos los atributos de una enfermedad.
	*   @return Un string con toda la información de la enfermedad.
	*/
	string toString() const;
	
	/** @brief Sobrecarga del operador de igualdad. ¿Es una enfermedad igual que la enfermedad @a e?.
	*   @param e Enfermedad con la que se desea comparar.
	*   @return Verdadero o Falso
	*/
	bool operator==(const enfermedad & e) const; 
	
	/** @brief Sobrecarga del operador de desigualdad. ¿Es una enfermedad distinta a la enfermedad @a e?.
	*   @param e Enfermedad con la que se desea comparar.
	*   @return Verdadero o Falso
	*/
	bool operator!=(const enfermedad & e) const;
	
	/** @brief Sobrecarga del operador menor estricto. ¿Es una enfermedad menor que la enfermedad @a e?
	*	 Se sigue el orden alfabetico teniendo en cuenta el atributo name.
	*   @param e Enfermedad con la que se desea comparar.
	*   @return Verdadero o Falso
	*/
	bool operator<(const enfermedad & e) const;

	/** @brief ¿El nombre de la enfermedad contiene @a str?
	*   @param str Cadena que se busca en el nombre de la enfermedad
	*   @return Verdadero o Falso
	*/
	bool nameContains(const string & str) const;
};	

/** @brief Sobrecarga del operador de extracción de flujo. Inserta en @a os todos los valores
*	 de los atributos de @a e.	
*   @param os Un flujo de salida
*   @param e Enfermedad de la que se desea extraer información
*   @return Un flujo de salida co la informacion de la enfermedad.
*/
ostream& operator<< ( ostream& os, const enfermedad & e); //imprime enfermedad (con TODOS sus campos)


//#include "enfermedad.hxx" // Incluimos la implementacion.
#include "enfermedad2.hpp"

#endif
