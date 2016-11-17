/* 
 * mutacion.h
 * 
 * Copyright  (C) Juan F. Huete y Carlos Cano 
*/
#ifndef __MUTACION_H
#define __MUTACION_H

#include <string>
#include <iostream> 
#include <vector>
#include <fstream>
#include <cctype>
#include "enfermedad.h"

using namespace std;

//! Clase mutacion, asociada al TDA mutacion
/*! mutacion::mutacion,  .....
 * Descripción contiene la informacion genetica de las mutaciones asociadas a una o varias enfermedades
 
 @todo Implementa esta clase, junto con su documentación asociada

*/

class mutacion {
private:
	string ID;								//identificador del SNP
	string chr; 								//numero de cromosoma
	unsigned int pos; 						//posicion del SNP dentro del cromosoma
	vector<string> ref_alt; 		//bases del genoma de refencia/bases alternativas en la poblacion
	vector<string> genes; 			//genes que contiene el SNP
	bool common;								//indica si el SNP es comun en la poblacion
	vector<float> caf;				//frecuencia de cada base del SNP en la poblacion
	vector<enfermedad> enfermedades;	//enfermedades asociadas al SNP
	vector<int> clnsig;				//relevancia clinica del SNP




	/** @brief Devuelve la posición siguiente a @a busca dentro de @a texto buscando desde la posicion @a pos_ini
	*   @param texto String donde se encuentra el string que queremos saltar
	*   @param busca String a buscar
	*   @param pos_ini Posición desde la que se desea empezar a buscar. Si no se dice nada empieza desde la posición 0
	*   @return Posición siguiente a la posición del último caracter de @a busca. En caso de que no lo encuentre devuelve
	*	    string::npos
	*/
	int leer_despues(const string &texto, const string &busca, const int pos_ini);

	/** @brief Escribe en @a cad la subcadena de @a texto desde @a pos hasta un caracter @a ignorar o hasta @a terminar
	*   @param texto String de donde queremos extraer la subcadena
	*   @param cad String donde desea que se escriba la subcadena
	*   @param pos_ini Posicion donde comienza la subcadena
	*   @param ignorar Caracter hasta donde se desea leer
	*   @param terminar Caracter con el que termina la subcadena si no encuentra @a ignorar
	*   @return La posición siguiente al fin de la subcadena
	*/
	int leer_sin_separadores(const string &texto, string &cad, const int pos_ini, const char &ignorar='|', const char &terminar=';');
	
public:

	/** @brief Constructor por defecto
	*/
	mutacion();

	/** @brief Constructor de copia
	*/
	mutacion(const mutacion& m);

	/** @brief Construimos una mutacion a traves de una cadena (@a str) de la base de datos.
	*          Se buscan distintos campos que indiquen el atributo al que pertenece y se le asigna.
	*   @param str Es un string de la base de datos
	*/
	mutacion(const string & str);
	
	/** @brief Asigna @a id al atributo del objeto llamado ID.
	*/
	void setID(const string & id);

	/** @brief Asigna @a chr al atributo del objeto llamado Chr.
	*/
	void setChr(const string & chr);

	/** @brief Asigna @a pos al atributo del objeto llamado Pos.
	*/
	void setPos(const unsigned int & pos);

	/** @brief Asigna @a ref_alt al atributo del objeto llamado Ref_alt.
	*/
	void setRef_alt(const vector<string> & ref_alt);

	/** @brief Asigna @a genes al atributo del objeto llamado Genes.
	*/
	void setGenes (const vector<string> & genes);

	/** @brief Asigna @a common al atributo del objeto llamado Common.
	*/		
	void setCommon (const bool & common);

	/** @brief Asigna @a caf al atributo del objeto llamado Caf.
	*/
	void setCaf (const vector<float> & caf);

	/** @brief Asigna @a enfermedades al atributo del objeto llamado Enfermedades.
	*/
	void setEnfermedades (const vector<enfermedad> & enfermedades);

	/** @brief Asigna @a clnsig al atributo del objeto llamado Clnsig.
	*/
	void setClnsig (const vector<int> & clnsig);  
	 
	/** @brief Devuelve el ID de la mutacion.
	*   @return El atributo ID del objeto.
	*/
	string getID( ) const;

	/** @brief Devuelve el numero de cromosoma de la mutacion.
	*   @return El atributo chr del objeto.
	*/
	string getChr( ) const;

	/** @brief Devuelve la posicion de la mutacion dentro del cromosoma.
	*   @return El atributo pos del objeto.
	*/
	unsigned int getPos( ) const;

	/** @brief Devuelve las bases que aparecen en el genoma humano de referencia y las posibles mutaciones.
	*   @return El atributo ref_alt del objeto.
	*/
	const vector<string> & getRef_alt () const;

	/** @brief Devuelve el nombre e identificado del gen que contiene la mutacion.
	*   @return El atributo genes del objeto.
	*/
	const vector<string> & getGenes () const;

	/** @brief Devuelve si la mutacion es común en la población.
	*   @return El atributo common del objeto.
	*/
	bool getCommon () const;

	/** @brief Devuelve la frecuencia con que se observa cada base descrita en la mutacion.
	*   @return El atributo caf del objeto.
	*/
	const vector<float> & getCaf () const;

	/** @brief Devuelve el nombre, ID y la base de datos de las enfermedades asociadas a la mutacion.
	*   @return El atributo enfermedades del objeto.
	*/
	const vector<enfermedad> & getEnfermedades () const;

	/** @brief Devuelve la relevancia clínica de la mutacion.
	*   @return El atributo clnsig del objeto.
	*/
	const vector<int> & getClnsig () const;

	/** @brief Sobrecarga del operador de asignación. Realiza la asignacion de una enfermedad a
	*	   otra asignando parámetro por parámetro.
	*   @param m Mutación que se desea asignar.
	*   @return Devuelve una referencia al objeto.
	*/
	mutacion & operator=(const mutacion & m);

	/** @brief Sobrecarga del operador de igualdad. ¿Es una mutación igual que la mutación @a m?.
	*   @param m Mutación que se quiere comparar
	*   @return Verdadero o Falso
	*/
	bool operator==(const mutacion & m) const;
	bool operator!=(const mutacion & m) const;

	/** @brief Sobrecarga del operador menor estricto. ¿Es una mutación menor que la mutación @a m?
	*	   Se sigue el orden del número de cromosoma que ocupa y, si son iguales, se compara la posición
	*	   que ocupa dentro del cromosoma
	*   @param m Mutación que se quiere comparar
	*   @return Verdadero o Falso
	*/
	bool operator<(const mutacion & m) const; 

	/** @brief Sobrecarga del operador mayor estricto. ¿Es una mutación mayor que la mutación @a m?
	*	   Se sigue el orden del número de cromosoma que ocupa y, si son iguales, se compara la posición
	*	   que ocupa dentro del cromosoma
	*   @param m Mutación que se quiere comparar
	*   @return Verdadero o Falso
	*/
	bool operator>(const mutacion & m) const; 

	/** @brief Sobrecarga del operador de extracción de flujo. Inserta en @a os todos los
	*	   valores de los atributos de @a m.
	*   @param os Flujo de salida
	*   @param m Mutación de la que se desea extraer la información
	*   @return Un flujo de salida con la informacion de la mutacion.
	*/
	friend ostream& operator<< ( ostream& , const mutacion& );
};

#include "mutacion.hxx"

#endif
