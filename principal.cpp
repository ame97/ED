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
   
   //Imprimir cuántas mutaciones están asociadas al cromosoma 1:
   cout << "Mutaciones asociadas a Chr 1: " << *conjuntoMutaciones.lower_bound("2",1) << endl;
   
   //for(typename conjunto::iterator i = conjuntoMutaciones.begin() ; i < conjuntoMutaciones.lower_bound("2",1) ; i++)
   //	cout << *i << endl;

   /**@todo ¿Existe la mutación con ID "rs147165522"? Imprimir la mutación y las enfermedades asociadas */
	typename conjunto::value_type mut;
	bool esta;
	
	pair<typename conjunto::value_type, bool> (mut, esta) = conjuntoMutaciones.conjunto::find("rs147165522");
	
	if (esta){
		cout << mut << endl;
	}
	else
		cout << "No existe la mutacion con ID rs147165522" << endl;
	
   /**@todo ¿Existe la mutación en chr/pos "14"/67769578? Imprimir la mutación y las enfermedades asociadas */
	pair<typename conjunto::value_type, bool> (mut, esta) = conjuntoMutaciones.conjunto::find("14",67769578);
	
	if (esta)
		cout << mut << endl;
	else
		cout << "No existe la mutacion en la posicion 67769578 del cromosoma 14" << endl;
	
   /**@todo ¿Cómo podríamos calcular el número de mutaciones del cromosoma 3? (utiliza lower_bound / upper_bound) */
	
	//cout << "Hay " << conjuntoMutaciones.lower_bound("4",1) - conjuntoMutaciones.upper_bound("3",0) << " mutaciones en el cromosoma 3" << endl;
	cout << "Lower -> " << *conjuntoMutaciones.lower_bound("4",1) << endl;
	cout << "Upper -> " << *conjuntoMutaciones.upper_bound("3",0) << endl;
	
   /**@todo Analiza la eficiencia teórica y empírica de las operaciones find, insert y erase */
   
   return 0;
}
