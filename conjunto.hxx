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


/********************************************CLASE CONJUNTO**********************************************/

using namespace std;


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
		while(count < size() && cond2 && cond3) {
			if(isdigit(stoi(vm[count].getChr())))
				cond21 = (stoi(vm[count].getChr()) > 0 && stoi(vm[count].getChr()) < 23);
			else
				cond21 = (vm[count].getChr() == "X" || vm[count].getChr() == "Y" || vm[count].getChr() == "MT");

			cond2 = (cond21 && vm[count].getPos() > 0);

			if(cond2)
				cond3 = comp(vm[count], vm[count+1]);
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
conjunto<T,CMP>::conjunto (const conjunto<T,CMP> & d) {
	vm = d.vm;
}


/** @brief busca una entrada en el conjunto
*   @param[in] s: entrada  a buscar. 
*   @return Si existe una entrada en el conjunto con ese valor devuelve el iterador a su posicion, 
*           en caso contrario devuelve iterador al final de conjunto
*   @post no modifica el conjunto.
*/
template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator  conjunto<T,CMP>::find (const typename conjunto<T,CMP>::value_type & s) {
	typename conjunto<T,CMP>::iterator itb = begin();
	unsigned int ini = 0, fin = size(), med;
	bool esta = false;

	while(ini < fin && !esta) {
		med = (ini + fin)/2;
		if(vm[med]==s)
			esta = true;
		else if(comp(s,vm[med]))
			fin = med-1;
		else
			ini = med+1;
	}

	if(esta)
		itb.it += med;
	else
		itb.it = vm.end();

	return itb;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::find(const typename conjunto<T,CMP>::value_type & s) const {
	typename conjunto<T,CMP>::const_iterator itb = cbegin();
	unsigned int ini = 0, fin = size(), med;
	bool esta = false;

	while(ini < fin && !esta) {
		med = (ini + fin)/2;
		if(vm[med] == s)
			esta = true;
		else if(comp(vm[med],s))
			++ini;
		else
			--fin;
	}

	if(esta)
		itb.it += med;
	else
		itb = cend();

	return itb;
}


/** @brief cuenta cuantas entradas coinciden con los parámetros dados. 
*   @param[in] e entrada. 
*   @return Como el conjunto no puede tener entradas repetidas, devuelve 1 
*           (si se encuentra la entrada) o 0 (si no se encuentra).
*   @post no modifica el conjunto.
*/
template <typename T, typename CMP>	
typename conjunto<T,CMP>::size_type conjunto<T,CMP>::count (const typename conjunto<T,CMP>::value_type & e) const{
	return std::count(cbegin().it,cend().it,e);
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
	bool insertado = false;
	typename conjunto<T,CMP>::iterator iti = lower_bound(val);
	
	if (iti != end()){
		if (*iti != val){
			vm.insert(iti.it,val);
			insertado = true;
		}
	}
	else{
		vm.push_back(val);
		insertado = true;
	}

	return pair<conjunto<T,CMP>::iterator,bool>(iti,insertado);

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
	typename conjunto<T,CMP>::iterator ite;
	ite.it = vm.erase(position.it);
	ite.elvector = &vm;

	return ite;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::size_type conjunto<T,CMP>::erase(const typename conjunto<T,CMP>::value_type & e) {
	typename conjunto<T,CMP>::iterator ite = find(e);

	if(ite != end())
		ite.it = vm.erase(ite.it);
		
	return (ite.it - vm.begin());
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
	if(this != &org)
		vm = org.vm;
	
	return (*this);
}



/** @brief begin del conjunto
    @return Devuelve un iterador (o iterador constante, respectivamente) al primer elemento del conjunto.
            Si no existe devuelve end
    @post no modifica el conjunto.
*/
template<typename T,typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::begin (){
	typename conjunto<T,CMP>::iterator itb;
	itb.elvector = &vm;
	itb.it = vm.begin();
	return itb;
}

template<typename T,typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::cbegin () const{
	typename conjunto<T,CMP>::const_iterator itcb;
	itcb.elvector = &vm;
	itcb.it = vm.cbegin();
	return itcb;
}

/** @brief end del conjunto
    @return Devuelve un iterador (o iterador constante, respectivamente) al final del conjunto (posicion siguiente al ultimo.
    @post no modifica el conjunto.
*/
template<typename T,typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::end (){
	typename conjunto<T,CMP>::iterator ite;
	ite.elvector = &vm;
	ite.it = vm.end();
	return ite;
}

template<typename T,typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::cend () const{
	typename conjunto<T,CMP>::const_iterator itce;
	itce.elvector = &vm;
	itce.it = vm.cend();
	return itce;
}

/** @brief begin del conjunto
    @return Devuelve un iterador seguro (o iterador seguro constante, respectivamente) al primer elemento del conjunto.
            Si no existe devuelve end
    @post no modifica el conjunto.
*/
template<typename T,typename CMP>
typename conjunto<T,CMP>::secure_iterator conjunto<T,CMP>::sbegin (){
	typename conjunto<T,CMP>::secure_iterator its;
	its.it = vm.begin();
	its.elvector = &vm;
	return its;
}

template<typename T,typename CMP>
typename conjunto<T,CMP>::const_secure_iterator conjunto<T,CMP>::csbegin( ) const{
	typename conjunto<T,CMP>::const_secure_iterator itcs;
	itcs.it = vm.cbegin();
	itcs.elvector = &vm;
	return itcs;
}

/** @brief end del conjunto
    @return Devuelve un iterador seguro (o iterador seguro constante, respectivamente) al final del conjunto
            (posicion siguiente al ultimo).
    @post no modifica el conjunto.
*/

template<typename T,typename CMP>
typename conjunto<T,CMP>::secure_iterator conjunto<T,CMP>::send (){
	typename conjunto<T,CMP>::secure_iterator its;
	its.it = vm.end();
	its.elvector = &vm;
	return its;
}

template<typename T,typename CMP>
typename conjunto<T,CMP>::const_secure_iterator conjunto<T,CMP>::csend( ) const{
	typename conjunto<T,CMP>::const_secure_iterator itcs;
	itcs.it = vm.cend();
	itcs.elvector = &vm;
	return itcs;
}

/** @brief begin del conjunto
    @return Devuelve un iterador impar (o iterador impar constante, respectivamente) al primer elemento
            (de posición impar) del conjunto. Si no existe devuelve end
    @post no modifica el conjunto.
*/

template<typename T,typename CMP>
typename conjunto<T,CMP>::impar_iterator conjunto<T,CMP>::ibegin(){
	typename conjunto<T,CMP>::impar_iterator iti;
	iti.it = vm.begin() + 1;
	iti.elvector = &vm;
	return iti;
}

template<typename T,typename CMP>
typename conjunto<T,CMP>::const_impar_iterator conjunto<T,CMP>::cibegin( ) const{
	typename conjunto<T,CMP>::const_impar_iterator itci;
	itci.it = vm.cbegin() + 1;
	itci.elvector = &vm;
	return itci;
}

/** @brief end del conjunto
    @return Devuelve un iterador impar (o iterador impar constante, respectivamente) al final del conjunto 
            (posicion siguiente al ultimo).
    @post no modifica el conjunto.
*/

template<typename T,typename CMP>
typename conjunto<T,CMP>::impar_iterator conjunto<T,CMP>::iend(){
	typename conjunto<T,CMP>::impar_iterator iti;
	iti.it = vm.end() + 1;
	iti.elvector = &vm;
	return iti;
}

template<typename T,typename CMP>
typename conjunto<T,CMP>::const_impar_iterator conjunto<T,CMP>::ciend( ) const{
	typename conjunto<T,CMP>::const_impar_iterator itci;
	itci.it = vm.cend()+1;
	itci.elvector = &vm;
	return itci;
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
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::lower_bound (const typename conjunto<T,CMP>::value_type & e){
	typename conjunto<T,CMP>::iterator itl;
	itl.it = std::lower_bound(vm.begin(), vm.end(), e, comp);
	itl.elvector = &vm;
	return itl;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::lower_bound (const typename conjunto<T,CMP>::value_type & e) const{
	typename conjunto<T,CMP>::const_iterator itcl;
	itcl.it = std::lower_bound(vm.cbegin(), vm.cend(), e, comp);
	itcl.elvector = &vm;
	return itcl;
}


/** @brief busca primer elemento por encima ('después', '>') de los parámetros dados. 
*   @param[in] chr de la mutación.
*   @param[in] pos de la mutación.
*   @param[in] e entrada. Devuelve un iterador al primer elemento que cumple que "elemento>e"
*		 esto es, el primer elemento ESTRICTAMENTE mayor que e. Si no existe devuelve end.
*   @post no modifica el conjunto.
*/

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::upper_bound (const typename conjunto<T,CMP>::value_type & e) {
	typename conjunto<T,CMP>::iterator itu;
	itu.it = std::upper_bound(vm.begin(), vm.end(), e, comp);
	itu.elvector = &vm;
	return itu;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::upper_bound (const typename conjunto<T,CMP>::value_type & e) const{
	typename conjunto<T,CMP>::const_iterator itcu;
	itcu.it = std::upper_bound(vm.cbegin(), vm.cend(), e, comp);
	itcu.elvector = &vm;
	return itcu;
}


/********************************************CLASE ITERATOR*****************************************/

template <typename T, typename CMP>
conjunto<T,CMP>::iterator::iterator() : elvector(NULL) {}

template <typename T, typename CMP>
conjunto<T,CMP>::iterator::iterator(const typename conjunto<T,CMP>::iterator &  x){
	elvector = x.elvector;
	it = x.it;
}

template <typename T, typename CMP>
conjunto<T,CMP>::iterator::iterator(const typename conjunto<T,CMP>::secure_iterator &  x){
	elvector = x.elvector;
	it = x.it;
}

template <typename T, typename CMP>
const typename conjunto<T,CMP>::value_type  & conjunto<T,CMP>::iterator::operator*(){
	return (*it);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator& conjunto<T,CMP>::iterator::operator++(){
	++it;
	return (*this);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::iterator::operator++(int i){
	typename conjunto<T,CMP>::iterator itv(*this);
	++it;
	return itv;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator& conjunto<T,CMP>::iterator::operator--(){
	--it;
	return *this;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::iterator::operator--(int i){
	typename conjunto<T,CMP>::iterator itv(*this);
	--it;
	return itv;
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::iterator::operator==(const typename conjunto<T,CMP>::iterator & x) const{
	return (it == x.it);
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::iterator::operator!=(const typename conjunto<T,CMP>::iterator & x) const{
	return (it != x.it);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator & conjunto<T,CMP>::iterator::operator=(const typename conjunto<T,CMP>::iterator& x){
	if(this != &x) {
		it = x.it;
		elvector = x.elvector;
	}

	return (*this);
}

/***************************************CLASE SECURE ITERATOR***************************************/

template <typename T, typename CMP>
conjunto<T,CMP>::secure_iterator::secure_iterator() : elvector(NULL) {}

template <typename T, typename CMP>
conjunto<T,CMP>::secure_iterator::secure_iterator(const typename conjunto<T,CMP>::secure_iterator &  x){
	elvector = x.elvector;
	it = x.it;
}

template <typename T, typename CMP>
const typename conjunto<T,CMP>::value_type  & conjunto<T,CMP>::secure_iterator::operator*(){
	assert(&(*elvector)[0] < &(*it) && &(*it) <= &(*elvector)[elvector->size()]);
	return (*it);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::secure_iterator& conjunto<T,CMP>::secure_iterator::operator++(){
	assert(&(*elvector)[0] < &(*it) && &(*it) <= &(*elvector)[elvector->size()]);
	++it;

	return (*this);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::secure_iterator conjunto<T,CMP>::secure_iterator::operator++(int i){
	assert(&(*elvector)[0] < &(*it) && &(*it) <= &(*elvector)[elvector->size()]);
	typename conjunto<T,CMP>::secure_iterator itv(*this);
	++it;
	return itv;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::secure_iterator& conjunto<T,CMP>::secure_iterator::operator--(){
	assert(&(*elvector)[0] < &(*it) && &(*it) <= &(*elvector)[elvector->size()]);
	--it;
	return (*this);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::secure_iterator conjunto<T,CMP>::secure_iterator::operator--(int i){
	assert(&(*elvector)[0] < &(*it) && &(*it) <= &(*elvector)[elvector->size()]);
	typename conjunto<T,CMP>::secure_iterator itv(*this);
	--it;
	return itv;
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::secure_iterator::operator==(const typename conjunto<T,CMP>::secure_iterator & x) const{
	assert(&(*elvector)[0] < &(*it) && &(*it) <= &(*elvector)[elvector->size()]);
	return (it == x.it);
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::secure_iterator::operator!=(const typename conjunto<T,CMP>::secure_iterator & x) const{
	assert(&(*elvector)[0] < &(*it) && &(*it) <= &(*elvector)[elvector->size()]);
	return (it != x.it);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::secure_iterator & conjunto<T,CMP>::secure_iterator::operator=(const typename conjunto<T,CMP>::secure_iterator& x){
	if(this != &x) {
		it = x.it;
		elvector = x.elvector;
	}

	return (*this);
}

/****************************************CLASE IMPAR ITERATOR***************************************/

template <typename T, typename CMP>
conjunto<T,CMP>::impar_iterator::impar_iterator() : elvector(NULL) {}

template <typename T, typename CMP>
conjunto<T,CMP>::impar_iterator::impar_iterator(const typename conjunto<T,CMP>::impar_iterator &  x){
	elvector = x.elvector;
	it = x.it;
}

template <typename T, typename CMP>
const typename conjunto<T,CMP>::value_type  & conjunto<T,CMP>::impar_iterator::operator*(){
	return (*it);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::impar_iterator& conjunto<T,CMP>::impar_iterator::operator++(){
	it += 2;
	return (*this);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::impar_iterator conjunto<T,CMP>::impar_iterator::operator++(int i){
	typename conjunto<T,CMP>::impar_iterator itv(*this);
	it += 2;
	return itv;
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::impar_iterator::operator==(const typename conjunto<T,CMP>::impar_iterator & x) const{
	return (it == x.it);
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::impar_iterator::operator!=(const typename conjunto<T,CMP>::impar_iterator & x) const{
	return (it != x.it);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::impar_iterator & conjunto<T,CMP>::impar_iterator::operator=(const typename conjunto<T,CMP>::impar_iterator& x){
	if(this != &x) {
		it = x.it;
		elvector = x.elvector;
	}

	return (*this);
}

/*************************************CLASE CONST ITERATOR******************************************/

template <typename T, typename CMP>
conjunto<T,CMP>::const_iterator::const_iterator() : elvector(NULL) {}

template <typename T, typename CMP>
conjunto<T,CMP>::const_iterator::const_iterator(const typename conjunto<T,CMP>::const_iterator &  x){
	elvector = x.elvector;
	it = x.it;
}

template <typename T, typename CMP>
conjunto<T,CMP>::const_iterator::const_iterator(const typename conjunto<T,CMP>::iterator &  x){
	elvector = x.elvector;
	it = x.it;
}

template <typename T, typename CMP>
conjunto<T,CMP>::const_iterator::const_iterator(const typename conjunto<T,CMP>::const_secure_iterator &  x){
	elvector = x.elvector;
	it = x.it;
}

template <typename T, typename CMP>
const typename conjunto<T,CMP>::value_type  conjunto<T,CMP>::const_iterator::operator*() const{
	conjunto<T,CMP>::value_type x = (*it);
	return x;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator& conjunto<T,CMP>::const_iterator::operator++(){
	++it;
	return (*this);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::const_iterator::operator++(int i){
	typename conjunto<T,CMP>::const_iterator itv(*this);
	++it;
	return itv;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator& conjunto<T,CMP>::const_iterator::operator--(){
	--it;
	return (*this);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::const_iterator::operator--(int i){
	typename conjunto<T,CMP>::const_iterator itv(*this);
	--it;
	return itv;
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::const_iterator::operator==(const typename conjunto<T,CMP>::const_iterator & x) const{
	return (it == x.it);
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::const_iterator::operator!=(const typename conjunto<T,CMP>::const_iterator & x) const{
	return (it != x.it);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator & conjunto<T,CMP>::const_iterator::operator=(const typename conjunto<T,CMP>::const_iterator& x){
	if(this != &x) {
		it = x.it;
		elvector = x.elvector;
	}

	return (*this);
}

/*********************************CLASE CONST SECURE ITERATOR***************************************/

template <typename T, typename CMP>
conjunto<T,CMP>::const_secure_iterator::const_secure_iterator() : elvector(NULL) {}

template <typename T, typename CMP>
conjunto<T,CMP>::const_secure_iterator::const_secure_iterator(const typename conjunto<T,CMP>::const_secure_iterator &  x){
	elvector = x.elvector;
	it = x.it;
}

template <typename T, typename CMP>
const typename conjunto<T,CMP>::value_type conjunto<T,CMP>::const_secure_iterator::operator*() const{
	assert(&(*elvector)[0] < &(*it) && &(*it) <= &(*elvector)[elvector->size()]);
	conjunto<T,CMP>::value_type x = (*it);
	return x;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_secure_iterator& conjunto<T,CMP>::const_secure_iterator::operator++(){
	assert(&(*elvector)[0] < &(*it) && &(*it) <= &(*elvector)[elvector->size()]);
	++it;
	return (*this);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_secure_iterator conjunto<T,CMP>::const_secure_iterator::operator++(int i){
	assert(&(*elvector)[0] < &(*it) && &(*it) <= &(*elvector)[elvector->size()]);
	typename conjunto<T,CMP>::const_secure_iterator_iterator itv(*this);
	++it;
	return itv;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_secure_iterator& conjunto<T,CMP>::const_secure_iterator::operator--(){
	assert(&(*elvector)[0] < &(*it) && &(*it) <= &(*elvector)[elvector->size()]);
	--it;
	return (*this);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_secure_iterator conjunto<T,CMP>::const_secure_iterator::operator--(int i){
	assert(&(*elvector)[0] < &(*it) && &(*it) <= &(*elvector)[elvector->size()]);
	typename conjunto<T,CMP>::const_secure_iterator_iterator itv(*this);
	--it;
	return itv;
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::const_secure_iterator::operator==(const typename conjunto<T,CMP>::const_secure_iterator & x) const{
	assert(&(*elvector)[0] < &(*it) && &(*it) <= &(*elvector)[elvector->size()]);
	return (it == x.it);
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::const_secure_iterator::operator!=(const typename conjunto<T,CMP>::const_secure_iterator & x) const{
	assert(&(*elvector)[0] < &(*it) && &(*it) <= &(*elvector)[elvector->size()]);
	return (it != x.it);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_secure_iterator & conjunto<T,CMP>::const_secure_iterator::operator=(const  typename conjunto<T,CMP>::const_secure_iterator& x){
	if(this != &x) {
		it = x.it;
		elvector = x.elvector;
	}

	return (*this);
}

/**********************************CLASE CONST IMPAR ITERATOR***************************************/

template <typename T, typename CMP>
conjunto<T,CMP>::const_impar_iterator::const_impar_iterator() : elvector(NULL) {}

template <typename T, typename CMP>
conjunto<T,CMP>::const_impar_iterator::const_impar_iterator(const typename conjunto<T,CMP>::const_impar_iterator &  x){
	elvector = x.elvector;
	it = x.it;
}

template <typename T, typename CMP>
const typename conjunto<T,CMP>::value_type conjunto<T,CMP>::const_impar_iterator::operator*() const{
	typename conjunto<T,CMP>::value_type x = (*it);
	return x;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_impar_iterator& conjunto<T,CMP>::const_impar_iterator::operator++(){
	it += 2;

	return (*this);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_impar_iterator conjunto<T,CMP>::const_impar_iterator::operator++(int i){
	typename conjunto<T,CMP>::impar_iterator itv(*this);
	it += 2;
	return itv;
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::const_impar_iterator::operator==(const typename conjunto<T,CMP>::const_impar_iterator & x) const{
	return (it == x.it);
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::const_impar_iterator::operator!=(const typename conjunto<T,CMP>::const_impar_iterator & x) const{
	return (it != x.it);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_impar_iterator & conjunto<T,CMP>::const_impar_iterator::operator=(const typename conjunto<T,CMP>::const_impar_iterator& x){
	if(this != &x) {
		it = x.it;
		elvector = x.elvector;
	}

	return (*this);
}

/***************************************************************************************************/

/** @brief imprime todas las entradas del conjunto 
*   @post No se modifica el conjunto.
*/

template <typename T, typename CMP>
ostream &  operator << ( ostream & os, const conjunto<T,CMP> & C) {
	typename conjunto<T,CMP>::const_iterator ini = C.cbegin();
	typename conjunto<T,CMP>::const_iterator fin = C.cend();

	while(ini != fin)
		os << *(ini++);

	return os;
}