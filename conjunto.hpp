/** @brief fichero de implementacion de la clase conjunto

*/

/** \invariant
IR: rep ==> bool

\li Para todo i, 0 <= i < vm.size() se cumple
	- vm[i].chr está en ("1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "X", "Y", "MT")
	- vm[i].pos > 0;
	
\li Para todo i, 0 <= i < C.vm.size()-1 se cumple:
	a) si vm[i].chr == vm[i+1].chr, entonces: vm[i].pos < vm[i+1].pos
	b) si vm[i].chr != vm[i+1].chr, entonces  vm[i].chr < vm[i+1].chr (donde el orden para el número de cromosoma se rige por "1"<"2"<"3"<...<"22"<"X"<"Y"<"MT")
*/


/** @brief Chequea el Invariante de la representacion 
	@return true si el invariante es correcto, falso en caso contrario
*/
bool conjunto::cheq_rep( ) const{
	bool cond1, cond2, cond3;
	unsigned i;
	
	for (i = 0 ; i < size()-1 && cond2 ; i++){
		cond1 = ((stoi(vm[i].getChr())>=1 && stoi(vm[i].getChr())<=22) || vm[i].getChr()=="X" || vm[i].getChr()=="Y" || vm[i].getChr()=="MT");
		cond2 = (cond1 && vm[i].getPos()>0);
		cond3 = vm[i] < vm[i+1];
	}

	cond1 = ((stoi(vm[i].getChr())>=1 && stoi(vm[i].getChr())<=22) || vm[i].getChr()=="X" || vm[i].getChr()=="Y" || vm[i].getChr()=="MT");
	cond2 = (cond1 && vm[i].getPos()>0);
	
	return (cond2 && cond3);
}

/** @brief constructor primitivo. 
*/
conjunto::conjunto( ){
	vm.clear();
}
	

/** @brief constructor de copia
	@param[in] d conjunto a copiar
*/
conjunto::conjunto (const conjunto & d){
	vm=d.vm;
}
		

/** @brief busca una entrada en el conjunto
	@param[in] chr: cromosoma de la mutación a buscar. 
	@param[in] pos: posición en el cromosoma de la mutación.
	@param[in] ID: identificador de la mutación a buscar
	@param[in] e entrada. Utilizar e.getID() o la combinación e.getChr()/e.getPos() para buscar una mutación con igual ID o Chr/Pos, el resto de los valores de entrada pueden ser ignorados. 
 	@return Si existe una mutación en el conjunto con ese chr/pos o ID, respectivamente, devuelve un par con una copia de la mutación en el conjunto y con el segundo valor a true. Si no se encuentra, devuelve la mutación con la definicion por defecto y false 
	@post no modifica el conjunto.
	\verbatim Uso 1:
	if (C.find("1", 6433456).second ==true) cout << "Found." ;
	else cout << "Not found.";
	\endverbatim
	\verbatim Uso 2:
	if (C.findID("rs12345").second ==true) cout << "Found." ;
	else cout << "Not found.";
	\endverbatim

*/
pair<conjunto::value_type,bool>  conjunto::find (const string & chr, const unsigned int & pos) const{
	unsigned ini = 0, fin = size(), med;
	conjunto::value_type mut;
	bool esta = false;
	
	mut.setChr(chr);
	mut.setPos(pos);
	
	while(ini <= fin && !esta){
		med = (ini + fin)/2;
		if (!(vm[med] < mut) && !(vm[med] > mut)){
			mut = vm[med];
			esta = true;
		}
		else{
			if (mut < vm[med])
				fin -= 1;
			else
				ini += 1;
		}
	}
	
	return pair<conjunto::value_type, bool> (mut, esta);
}
	
pair<conjunto::value_type,bool>  conjunto::find (const string & ID) const{
	conjunto::const_iterator it;
	conjunto::value_type mut;
	bool esta = false;
	
	for (it = vm.cbegin() ; it < vm.cend() && !esta ; it++){
		if ((*it).getID() == ID){
			mut = *it;
			esta = true;
		}
	}
	
	return pair<conjunto::value_type,bool>(mut,esta);
}
	
pair<conjunto::value_type,bool>  conjunto::find (const conjunto::value_type & e) const{
	conjunto::value_type mut;
	bool esta = binary_search(cbegin(),cend(),e);
	
	if (esta)
		mut = e;
	
	return pair<conjunto::value_type,bool> (mut, esta);
}



/** @brief cuenta cuantas entradas coinciden con los parámetros dados. 
	@param[in] chr de la mutación.
	@param[in] pos de la mutación.
	@param[in] ID de la mutación.
	@param[in] e entrada. Utilizar e.getID() para buscar cuántas mutaciones tienen el mismo ID, el resto de los valores de entrada no son tenidos en cuenta
	@return Como el conjunto de mutaciones no puede tener entradas repetidas, devuelve 1 (si se encuentra la entrada) o 0 (si no se encuentra).
	@post no modifica el conjunto.
*/
typename conjunto::size_type conjunto::count (const string & chr, const unsigned int & pos) const{
	return (find(chr,pos).second)?1:0;
}
	
typename conjunto::size_type conjunto::count (const string & ID) const{
	return (find(ID).second)?1:0;
}
	
typename conjunto::size_type conjunto::count (const typename conjunto::value_type & e) const{
	return (find(e).second)?1:0;
}



/** @brief Inserta una entrada en el conjunto
	@param e entrada a insertar
	@return true si la entrada se ha podido insertar con �xito, esto es, no existe una mutaci�n con igual par chr/pos ni igual ID en el conjunto. False en caso contrario. 
	@post Si e no esta en el conjunto, el size() sera incrementado en 1.
*/
bool conjunto::insert(const typename conjunto::value_type & e){
	bool insertado = false;
	
	if(!binary_search(vm.begin(),vm.end(),e)){
		vm.insert(upper_bound(e),e);
		insertado = true;
	}
	
	if(vm.size() % 500 == 0)
		cout << vm.size() << endl;
	
	return insertado;
}

	
	
/** @brief Borra una entrada en el conjunto .
	Busca la entrada con chr/pos o id en el conjunto (utiliza e.getID() en el tercer caso) y si la encuentra la borra.
	@param[in] chr de la mutación a borrar.
	@param[in] pos de la mutación a borrar.
	@param[in] ID de la mutación a borrar.
	@param[in] e entrada con e.getID() que geremos borrar, el resto de los valores no son tenidos en cuenta
	@post Si esta en el conjunto su tamaño se decrementa en 1.
*/
bool conjunto::erase(const string & chr, const unsigned int & pos){
	typename conjunto::iterator it;
	
	for (it = vm.begin() ; it < vm.end() ; it++){
		if ((*it).getChr() == chr && (*it).getPos() == pos){
			vm.erase(it);
			return true;
		}
	}
		
	return false;
}
	
bool conjunto::erase(const string & ID){
	typename conjunto::iterator it;
	
	for (it = vm.begin() ; it < vm.end() ; it++){
		if ((*it).getID() == ID){
			vm.erase(it);
			return true;
		}
	}
	
	return false;
}
	
bool conjunto::erase(const typename conjunto::value_type & e){
	typename conjunto::iterator it;
	
	for (it = vm.begin() ; it < vm.end() ; it++){
		if (*it == e){
			vm.erase(it);
			return true;
		}
	}
	
	return false;
}
         

/** @brief Borra todas las entradas del conjunto, dejandolo vacio.
	@post El conjunto se modifica, quedando vacio. 
*/
void conjunto::clear(){
	vm.clear();
}

/** @brief numero de entradas en el conjunto
	@post  No se modifica el conjunto.
	@return numero de entradas en el conjunto
*/
typename conjunto::size_type conjunto::size() const{
	return vm.size();
}


/** @brief Chequea si el conjunto esta vacio (size()==0)
	@post  No se modifica el conjunto.
*/
bool conjunto::empty() const{
	return (vm.size() == 0)?true:false;
}


/** @brief operador de asignación
	@param[in] org conjunto a copiar.
	@return Crea y devuelve un conjunto duplicado exacto de org.
*/
conjunto & conjunto::operator=(const conjunto & org){
	if (this != &org)
		vm = org.vm;
	
	return *this;
}

/** @brief begin del conjunto
	@return Devuelve un iterador al primer elemento del conjunto. Si no existe devuelve end
	@post no modifica el conjunto.
*/
typename conjunto::iterator conjunto::begin (){
	return vm.begin();
}

/** @brief end del conjunto
	@return Devuelve un iterador al final del conjunto (posicion siguiente al ultimo.
	@post no modifica el conjunto.
*/
typename conjunto::iterator conjunto::end (){
	return vm.end();
}

/** @brief begin del conjunto
	@return Devuelve un iterador constante al primer elemento del conjunto. Si no existe devuelve end
	@post no modifica el conjunto.
*/
typename conjunto::const_iterator conjunto::cbegin () const{
	return vm.cbegin();
}

/** @brief end del conjunto
	@return Devuelve un iterador constante al final del conjunto (posicion siguiente al ultimo.
	@post no modifica el conjunto.
*/
typename conjunto::const_iterator conjunto::cend () const{
	return vm.cend();
}




/** @brief busca primer elemento por debajo ('antes', '<') de los parámetros dados. 
	@param[in] chr de la mutación.
	@param[in] pos de la mutación.
	@param[in] e entrada.  
	@return Devuelve un iterador al primer elemento que cumple que "elemento<e" es falso, esto es, el primer elemento que es menor o igual que e
	
	Si no existe devuelve end
	@post no modifica el conjunto.
*/
typename conjunto::const_iterator conjunto::lower_bound (const string & chr, const unsigned int & pos) const{
	mutacion mut;
	
	mut.setChr(chr);
	mut.setPos(pos);
		
	return lower_bound(mut);
}
	
typename conjunto::const_iterator conjunto::lower_bound (const typename conjunto::value_type & e) const{
	return std::lower_bound(vm.cbegin(),vm.cend(),e);
}



/** @brief busca primer elemento por encima ('después', '>') de los parámetros dados. 
	@param[in] chr de la mutación.
	@param[in] pos de la mutación.
	@param[in] e entrada. Devuelve un iterador al primer elemento que cumple que "elemento>e", esto es, el primer elemento ESTRICTAMENTE mayor que e


	Si no existe devuelve end
	@post no modifica el conjunto.
*/
typename conjunto::const_iterator conjunto::upper_bound (const string & chr, const unsigned int & pos) const{
	mutacion mut;
	
	mut.setChr(chr);
	mut.setPos(pos);
		
	return upper_bound(mut);
}
	
typename conjunto::const_iterator conjunto::upper_bound (const typename conjunto::value_type & e) const{
	return std::upper_bound(vm.cbegin(),vm.cend(),e);
}



/** @brief imprime todas las entradas del conjunto 
@post No se modifica el conjunto.
Implementar tambien esta funcion
	*/
ostream & operator << ( ostream & os, const conjunto & C){	
	for (typename conjunto::const_iterator it = C.cbegin() ; it < C.cend() ; it++)
		os << *it;
		
	return os;
}
