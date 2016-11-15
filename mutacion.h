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
//! Clase mutacion, asociada a la definición de una mutación/SNP 
/*! mutacion::mutacion,  .....
 * 
 @todo Implementa esta clase, junto con su documentación asociada

*/

using namespace std;

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
	
public:
	mutacion();
	mutacion(const mutacion& m);
	mutacion(const string & str);   	//para crear objeto mutacion a partir de la cadena que contiene una línea completa del fichero de entrada
	
	void setID(const string & id);
	void setChr(const string & chr);
	void setPos(const unsigned int & pos);
	void setRef_alt(const vector<string> & ref_alt);
	void setGenes (const vector<string> & genes);  
	void setCommon (const bool & common);
	void setCaf (const vector<float> & caf);
	void setEnfermedades (const vector<enfermedad> & enfermedades);
	void setClnsig (const vector<int> & clnsig);  
	 
	string getID( ) const;
	string getChr( ) const;
	unsigned int getPos( ) const;
	const vector<string> & getRef_alt () const;
	const vector<string> & getGenes () const;
	bool getCommon () const;
	const vector<float> & getCaf () const;
	const vector<enfermedad> & getEnfermedades () const;
	const vector<int> & getClnsig () const;
	   
	mutacion & operator=(const mutacion & m);
	bool operator==(const mutacion & m) const;
	bool operator<(const mutacion & m) const;		//El orden viene determinado por Chr y pos. El primer criterio es el número de cromosoma. El orden para el número de cromosoma se rige por "1"<"2"<"3"<...<"22"<"X"<"Y"<"MT". Dos mutaciones del mismo cromosoma deben ordenarse según su posición, de menor posición a mayor (orden natural de enteros). 
	bool operator>(const mutacion & m) const;
};

	ostream& operator<< ( ostream& , const mutacion& );	//Imprimir TODOS los campos del objeto mutación.
	int leer_despues(const string &texto, const string &busca, const int pos_ini=0);
	int leer_sin_separadores(const string &texto, string &cad, const int pos=0, const char &ignora='|', const char &termina=';');
//#include "mutacion.hxx"
#include "mutacion2.hpp"

#endif
