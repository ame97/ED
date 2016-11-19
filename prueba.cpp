#include "mutacion.h"
#include "enfermedad.h"
#include "conjunto.h"
#include "criterios.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;


/* ----------------------------------------- * /

	conjunto<mutacion,creciente<mutacion>>    conjuntoMutaciones;
	string criterio = "Creciente Chr - Pos";
	bool load(conjunto<mutacion,creciente<mutacion>> &cm, const string &s)
	
/* ----------------------------------------- * /

	conjunto<mutacion,decreciente<mutacion>>  conjuntoMutaciones;
	string criterio = "Decreciente Chr - Pos";
	bool load(conjunto<mutacion,decreciente<mutacion>> &cm, const string &s)
	
/* ----------------------------------------- */

	conjunto<mutacion,crecienteID>            conjuntoMutaciones;
	string criterio = "Creciente ID";
	bool load(conjunto<mutacion,crecienteID> &cm, const string &s)
	
/* ----------------------------------------- * /

	conjunto<mutacion,decrecienteID>          conjuntoMutaciones;
	string criterio = "Decreciente ID";
	bool load(conjunto<mutacion,decrecienteID> &cm, const string &s)
	
/* ----------------------------------------- * /

	conjunto<mutacion,crecienteEnfermedad>    conjuntoMutaciones;
	string criterio = "Creciente Enfermedades";
	bool load(conjunto<mutacion,crecienteEnfermedad> &cm, const string &s)
	
/* ----------------------------------------- * /

	conjunto<mutacion,decrecienteEnfermedad>  conjuntoMutaciones;
	string criterio = "Decreciente Enfermedades";
	bool load(conjunto<mutacion,decrecienteEnfermedad> &cm, const string &s)
	
/* ----------------------------------------- */

{
	ifstream fe;
	string cadena;
	
	cout << "Abrimos "<< s << endl;
	fe.open(s.c_str(), ifstream::in);
	if (fe.fail()){
		cerr << "Error al abrir el fichero " << s << endl;
	} 
	else {
	   //leo la cabecera del fichero (líneas que comienzan con #)
	   do{ 
		   getline(fe,cadena,'\n'); 
	   }while (cadena.find("#")==0 && !fe.eof());
	
	   //leo la tabla de mutaciones, una línea cada vez
	   while ( !fe.eof() ){ 
	      //cout << "leo:: "<< cadena << endl;
	      // Invoco el constructor de mutación que recibe una cadena completa, la parsea y crea la mutación.
	      mutacion mut = mutacion(cadena);
	      // Insertar mutación en el conjunto
	      cm.insert(mut);
	      getline(fe,cadena,'\n');
	   }
	   fe.close(); 
	   return true;
	} // else
	fe.close();
	return false;
}

int main(){
	high_resolution_clock::time_point tantes,tdespues;
	duration<double> tiempo_transcurrido;
	
	tantes = high_resolution_clock::now();
	load(conjuntoMutaciones, "clinvar_20160831.vcf");
	tdespues = high_resolution_clock::now();
	
	tiempo_transcurrido  = duration_cast<duration<double> >(tdespues - tantes);
	
	cout << criterio << ":" << endl;
	cout << "\tTiempo               =  " << tiempo_transcurrido.count() << endl;
	cout << "\tMutaciones cargadas  =  " << conjuntoMutaciones.size() << endl;
}