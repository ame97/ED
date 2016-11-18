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

bool load(conjunto<mutacion,crecienteCP<mutacion>> &cm, const string &s) {
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
	conjunto<mutacion,crecienteCP<mutacion>> conjuntoMutaciones;
	string query_str;  
	high_resolution_clock::time_point tantes,tdespues;
	duration<double> tiempo_transcurrido;
    
	tantes = high_resolution_clock::now();
	load(conjuntoMutaciones, "clinvar_20160831.vcf");
	tdespues = high_resolution_clock::now();
	
	tiempo_transcurrido  = duration_cast<duration<double> >(tdespues - tantes);
	cout << "Tiempo = " << tiempo_transcurrido.count() << endl;
   
	cout << conjuntoMutaciones.size() << endl;
}
