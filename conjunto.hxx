/** \invariant
		 
IR: rep ==> bool
		 
\li Para todo i, 0 <= i < vm.size() se cumple
	- vm[i].chr está en ("1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15",
			    "16", "17", "18", "19", "20", "21", "22", "X", "Y", "MT")

	- vm[i].pos > 0;
\li Para todo i, 0 <= i < C.vm.size()-1 se cumple:
  	a) si vm[i].chr == vm[i+1].chr, entonces: vm[i].pos < vm[i+1].pos
  	b) si vm[i].chr != vm[i+1].chr, entonces  vm[i].chr < vm[i+1].chr 
	   (donde el orden para el número de cromosoma se rige por "1"<"2"<"3"<...<"22"<"X"<"Y"<"MT")
*/

		
/** @brief Chequea el Invariante de la representacion 
*   @return true si el invariante es correcto, falso en caso contrario
*/
template <typename T, typename CMP>
bool conjunto<T,CMP>::cheq_rep( ) const {
	bool cond1= (size() == vm.size());
	bool cond21, cond2;
	bool cond3;
	unsigned int count = 0;
	
	if(cond1)
		while(count<size() && cond2 && cond3) {
			if(isdigit(stoi(vm[count].getChr())))
				cond21=(stoi(vm[count].getChr())>0 && stoi(vm[count].getChr())<23);
			else
				cond21=(vm[count].getChr()=="X" || vm[count].getChr()=="Y" || vm[count].getChr()=="MT");

			cond2=(cond21 && vm[count].getPos()>0);

			if(cond2)
				cond3=comp(vm[count],vm[count+1]);
		}

	return (cond1 && cond2 && cond3);
}

/** @brief constructor primitivo. 
*/
template <typename T, typename CMP>
conjunto<T,CMP>::conjunto() {
	vm.clear();
}
	
	

/** @brief constructor de copia
*   @param[in] d conjunto a copiar
*/
template <typename T, typename CMP>
conjunto<T,CMP>::conjunto (const conjunto<T,CMP> & d) { //Cambia
	vm=d.vm;
}

/** @brief busca una entrada en el conjunto
*   @param[in] s: entrada  a buscar. 
*   @return Si existe una entrada en el conjunto con ese valor devuelve el iterador a su posicion, 
*           en caso contrario devuelve iterador al final de conjunto
*   @post no modifica el conjunto.
*/
template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator  conjunto<T,CMP>::find (const typename conjunto<T,CMP>::value_type & s) {
	typename conjunto<T,CMP>::iterator buscado=begin();
	bool encontrado=false;
	unsigned int inf=0,med,sup=size();

	while(inf<sup && !encontrado) {
		med=(inf+sup)/2;
		if(vm[med]==s)
			encontrado=true;
		else if(comp(vm[med],s))
			inf=med;
		else
			sup=med;
	}

	if(encontrado)
		buscado=buscado+med;
	else
		buscado=end();

	return buscado;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::find(const typename conjunto<T,CMP>::value_type & s) const {
	typename conjunto<T,CMP>::const_iterator buscado=cbegin();
	bool encontrado=false;
	unsigned int inf=0,med,sup=size();

	while(inf<sup && !encontrado) {
		med=(inf+sup)/2;
		if(vm[med]==s)
			encontrado=true;
		else if(comp(vm[med],s))
			sup=med;
		else
			inf=med;
	}

	if(encontrado)
		buscado=buscado+med;
	
	else
		buscado=cend();

	return buscado;
}

/** @brief cuenta cuantas entradas coinciden con los parámetros dados. 
*   @param[in] e entrada. 
*   @return Como el conjunto no puede tener entradas repetidas, devuelve 1 
*           (si se encuentra la entrada) o 0 (si no se encuentra).
*   @post no modifica el conjunto.
*/

template <typename T, typename CMP>	
typename conjunto<T,CMP>::size_type conjunto<T,CMP>::count (const typename conjunto<T,CMP>::value_type & e) const{
	return std::count(cbegin(),cend(),e);
}

/** @brief Inserta una entrada en el conjunto
*   @param val entrada a insertar
*   @return un par donde el segundo campo vale true si la entrada se ha podido insertar
*           con éxito, esto es, no existe una mutación con igual valor en el conjunto. False en caso contrario. 
*           El primer campo del par devuelve un iterador al elemento insertado, o end() si no fue posible la insercion
*   @post Si e no esta en el conjunto, el size() sera incrementado en 1.
*/

template <typename T, typename CMP>
pair<typename conjunto<T,CMP>::iterator,bool> conjunto<T,CMP>::insert (const typename conjunto<T,CMP>::value_type& val){
	typename conjunto<T,CMP>::iterator it;
	bool insertado=false;

	if(size()>0) {
		typename conjunto<T,CMP>::iterator inicio=begin();
		typename conjunto<T,CMP>::iterator fin=end();

	 	bool encontrado=false;

		while(inicio!=fin && !encontrado && !insertado) {
			if(*inicio==val)
				encontrado=true;
			else if(!comp(*inicio,val)) {
				it=vm.insert(inicio,val);
				insertado=true;
			}else
				++inicio;
		}

		if(encontrado==true)
			it=end();

	}

	else {
		vm.push_back(val);
		insertado=true;
		it=begin();
	}

	return pair<typename conjunto<T,CMP>::iterator,bool>(it,insertado);

} //cambiar	
	
/** @brief Borra una entrada en el conjunto .
*	   Busca la entrada con chr/pos o id en el conjunto (utiliza e.getID()
*	   en el tercer caso) y si la encuentra la borra.
*   @param[in] chr de la mutación a borrar.
*   @param[in] pos de la mutación a borrar.
*   @param[in] ID de la mutación a borrar.
*   @param[in] e entrada con e.getID() que geremos borrar, el resto de los
*		 valores no son tenidos en cuenta
*   @return Devuelve 1 si se consige eliminar satisfactoriamente el elemento,
*	    0 en caso contrario. 
*   @post Si esta en el conjunto su tamaño se decrementa en 1.
*/

/** @brief Borra una entrada en el conjunto .
*          Busca la entrada y si la encuentra la borra.
*   @param[in] val entrada a borrar.
*   @param[in] position itarador que apunta a la  entrada que geremos borrar
*   @return devuelve la posicion siguiente al elemento borrado (para la version con iterador)
*           o el numero de elementos borrados
*   @post Si esta en el conjunto su tamaño se decrementa en 1.
*/

template <typename T, typename CMP>	
typename conjunto<T,CMP>::iterator  conjunto<T,CMP>::erase (const typename conjunto<T,CMP>::iterator position) {
	typename conjunto<T,CMP>::iterator it=vm.erase(position);

	return it;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::size_type conjunto<T,CMP>::erase(const typename conjunto<T,CMP>::value_type & e) {
	typename conjunto<T,CMP>::const_iterator it=find(e);

	if(it!=cend()) {
		it=vm.erase(it);

	}
	
	return (it-cbegin());
}
		
		 

/** @brief Borra todas las entradas del conjunto, dejandolo vacio.
*   @post El conjunto se modifica, quedando vacio. 
*/

template <typename T, typename CMP>
void conjunto<T,CMP>::clear() {
	vm.clear();
}

/** @brief numero de entradas en el conjunto
*   @post  No se modifica el conjunto.
*   @return numero de entradas en el conjunto
*/

template <typename T, typename CMP>
typename conjunto<T,CMP>::size_type conjunto<T,CMP>::size() const {
	return vm.size();
}


/** @brief Chequea si el conjunto esta vacio (size()==0)
*   return Devuelve 1 si el conjunto esta vacio, y 0 en caso contrario
*   @post  No se modifica el conjunto.
*/
template <typename T, typename CMP>
bool conjunto<T,CMP>::empty() const {
	return vm.empty();
}


/** @brief operador de asignación
*   @param[in] org conjunto a copiar.
*   @return Crea y devuelve un conjunto duplicado exacto de org.
*/
template <typename T, typename CMP>
conjunto<T,CMP> & conjunto<T,CMP>::operator=( const conjunto<T,CMP> & org) {
	if(this!=&org)
		vm=org.vm;
	
	return *this;
}



/** @brief begin del conjunto
*   @return Devuelve un iterador al primer elemento del conjunto. Si no existe devuelve end
*   @post no modifica el conjunto.
*/
template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::begin () {
	return vm.begin();
}	

/** @brief end del conjunto
*   @return Devuelve un iterador al final del conjunto (posicion siguiente al ultimo.
*   @post no modifica el conjunto.
*/
template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::end () {
	return vm.end();
}

/** @brief begin del conjunto
*   @return Devuelve un iterador constante al primer elemento del conjunto. Si no existe devuelve end
*   @post no modifica el conjunto.
*/
template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::cbegin () const {
	return vm.cbegin();
}

/** @brief end del conjunto
*   @return Devuelve un iterador constante al final del conjunto (posicion siguiente al ultimo.
*   @post no modifica el conjunto.
*/
template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::cend () const {
	return vm.cend();	
}

/** @brief busca primer elemento por debajo ('antes', '<') de los parámetros dados. 
*   @param[in] chr de la mutación.
*   @param[in] pos de la mutación.
*   @param[in] e entrada.  
*   @return Devuelve un iterador al primer elemento que cumple que "elemento<e" es falso
*	    esto es, el primer elemento que  es mayor o igual que e. Si no existe devuelve end.
*   @post no modifica el conjunto.
*/
template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::lower_bound (const conjunto<T,CMP>::value_type & e){
	typename conjunto<T,CMP>::iterator it=find(e);
	return it;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::lower_bound (const conjunto<T,CMP>::value_type & e) const{
	typename conjunto<T,CMP>::const_iterator it=find(e);
	return it;
}


/** @brief busca primer elemento por encima ('después', '>') de los parámetros dados. 
*   @param[in] chr de la mutación.
*   @param[in] pos de la mutación.
*   @param[in] e entrada. Devuelve un iterador al primer elemento que cumple que "elemento>e"
*		 esto es, el primer elemento ESTRICTAMENTE mayor que e. Si no existe devuelve end.
*   @post no modifica el conjunto.
*/

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::upper_bound (const conjunto<T,CMP>::value_type & e) {
	typename conjunto<T,CMP>::iterator it=find(e);
	return ++it;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::upper_bound (const conjunto<T,CMP>::value_type & e) const{
	typename conjunto<T,CMP>::const_iterator it=find(e);
	return ++it;
}


/** @brief imprime todas las entradas del conjunto 
*   @post No se modifica el conjunto.
*/

template <typename T, typename CMP>
ostream &  operator << ( ostream & sal, const conjunto<T,CMP> & C) {
	typename conjunto<T,CMP>::const_iterator beg=C.cbegin();
	typename conjunto<T,CMP>::const_iterator end=C.cend();

	while(beg!=end) {
		sal << *beg;
		beg++;
	}

	return sal;
}

