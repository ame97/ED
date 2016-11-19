#include "mutacion.h"
#include "enfermedad.h"
#include "criterios.h"
#include "conjunto.h"
#include <iostream>
#include <fstream>
#include <vector>


using namespace std;
	
/** @brief lee un fichero de mutaciones, linea a linea
	@param[in] s nombre del fichero
	@param[in,out] cm objeto tipo conjunto sobre el que se almacenan las mutaciones
	@return true si la lectura ha sido correcta, false en caso contrario
*/

bool load(conjunto<mutacion,creciente<mutacion>> &  cm, const string & s) {
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


int main(int argc, char *argv[]){
   conjunto<mutacion,creciente<mutacion>> conjuntoMutaciones;
   string query_str; 

   //Cargar las mutaciones en vectorSNPs
   load(conjuntoMutaciones, "clinvar_20160831.vcf");

   //Imprimir número de elementos almacenados en conjuntoMutaciones
   cout << "Lectura del fichero finalizada. Mutaciones cargadas: " << conjuntoMutaciones.size() << endl;  
   
   return 0;
}
