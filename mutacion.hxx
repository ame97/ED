/** @brief fichero de implementacion de la clase mutacion

*/

/** @brief Constructor por defecto

*/
mutacion::mutacion(){
	setID("");
	setChr("");
	setPos(0);
	setCommon(false);
}

/** @brief Constructor de copia

*/
mutacion::mutacion(const mutacion& m){
	setID(m.getID());
	setChr(m.getChr());
	setPos(m.getPos());
	setRef_alt(m.getRef_alt());
	setGenes(m.getGenes());
	setCommon(m.getCommon());
	setCaf(m.getCaf());
	setEnfermedades(m.getEnfermedades());
	setClnsig(m.getClnsig());
}

/** @brief Construimos una mutacion a travÃ©s de una cadena (@a str) de la base de datos. Se buscan distintos campos que      *          indiquen el atributo al que pertenece y se le asigna.
*   @param str Es un string de la base de datos
*/
mutacion::mutacion(const string & str){
	unsigned int ini=0; 	//Desde donde empieza a buscar
	int fin;	//Hasta donde termina de buscar
	string aux;
	vector<string> name,id,database;
	
	//Leer CHR
	fin=str.find("\t");
	this->chr=str.substr(ini,fin-ini);
	ini=fin+1;
	
	//Leer POS
	fin=str.find("\t",ini);
	this->pos=stoi(str.substr(ini,fin-ini));
	ini=fin+1;

	//Leer ID
	ini=str.find("rs",ini);
	if(ini!=string::npos) {
		fin=str.find("\t",ini);
		this->ID=str.substr(ini,fin-ini);
		ini=fin+1;
	}
	else
		this->ID="S/N";
	
	//Leer REF_ALT
	for(int j=0;j<2;j++) {
		fin=str.find('\t',ini);
		(this->ref_alt).push_back(str.substr(ini,fin-ini));
		ini=fin+1;
	}

	//Leer Genes
	ini=leer_despues(str,"GENEINFO=",ini);
	if(ini!=string::npos) {
		do{
			ini=leer_sin_separadores(str,aux,ini);
			(this->genes).push_back(aux);
		}while(str[ini-1]!=';');
	}

	//Leer CLNSIG
	ini=leer_despues(str,"CLNSIG=",ini);
	if(ini!=string::npos) {
		do{
			ini=leer_sin_separadores(str,aux,ini);
			(this->clnsig).push_back(stoi(aux));
		}while(str[ini-1]!=';');
	}

	//Leer CLNDSDB
	ini=leer_despues(str,"CLNDSDB=",ini);
	if(ini!=string::npos) {
		do{
			ini=leer_sin_separadores(str,aux,ini);
			database.push_back(aux);
		}while(str[ini-1]!=';');
	}

	//Leer CLNDSDBID
	ini=leer_despues(str,"CLNDSDBID=",ini);
	if(ini!=string::npos) {
		do{
			ini=leer_sin_separadores(str,aux,ini);
			id.push_back(aux);
		}while(str[ini-1]!=';');
	}

	//Leer CLNDBN
	ini=leer_despues(str,"CLNDBN=",ini);
	if(ini!=string::npos) {
		do{
			ini=leer_sin_separadores(str,aux,ini);
			name.push_back(aux);
		}while(str[ini-1]!=';');
	}
	
	//Rellenar vector enfermedades
	for(unsigned int i=0 ; i<name.size() && i<id.size() && i<database.size() ; i++) {
		enfermedad A(name[i],id[i],database[i]);
		(this->enfermedades).push_back(A);
	}

	//Leer CAF
	ini=leer_despues(str,"CAF=",ini);
	if(ini > string::npos) {
		for (int j=0 ; j<2 ; j++) {
			ini=leer_sin_separadores(str,aux,ini,',',';');
			(this->caf).push_back(stof(aux));
		}		
	}

	//Leer COMMON
	ini=leer_despues(str,"COMMON=",ini);
	if(ini!=string::npos)
		this->common=str[ini];
	else
		this->common=false;	//Si no existe el campo COMMON
}


/** @brief Asigna @a id al atributo del objeto llamado ID.
*/
void mutacion::setID(const string & id){
	this->ID = id;
}

/** @brief Asigna @a chr al atributo del objeto llamado Chr.
*/
void mutacion::setChr(const string & chr){
	this->chr = chr;
}

/** @brief Asigna @a pos al atributo del objeto llamado Pos.
*/
void mutacion::setPos(const unsigned int & pos){
	this->pos = pos;
}

/** @brief Asigna @a ref_alt al atributo del objeto llamado Ref_alt.
*/
void mutacion::setRef_alt(const std::vector<string> & ref_alt){
	this->ref_alt = ref_alt;
}

/** @brief Asigna @a genes al atributo del objeto llamado Genes.
*/
void mutacion::setGenes (const std::vector<string> & genes){
	this->genes = genes;
}

/** @brief Asigna @a common al atributo del objeto llamado Common.
*/
void mutacion::setCommon (const bool & common){
	this->common = common;
}

/** @brief Asigna @a caf al atributo del objeto llamado Caf.
*/
void mutacion::setCaf (const std::vector<float> & caf){
	this->caf = caf;
}

/** @brief Asigna @a enfermedades al atributo del objeto llamado Enfermedades.
*/
void mutacion::setEnfermedades (const std::vector<enfermedad> & enfermedades){
	this->enfermedades = enfermedades;
}

/** @brief Asigna @a clnsig al atributo del objeto llamado Clnsig.
*/
void mutacion::setClnsig (const std::vector<int> & clnsig){
	this->clnsig = clnsig;
}



/** @brief Devuelve el ID de la mutacion.
*   @return El atributo ID del objeto.
*/
string mutacion::getID() const{
	return ID;
}

/** @brief Devuelve el numero de cromosoma de la mutacion.
*   @return El atributo chr del objeto.
*/
string mutacion::getChr( ) const{
	return chr;
}

/** @brief Devuelve la posicion de la mutacion dentro del cromosoma.
*   @return El atributo pos del objeto.
*/
unsigned int mutacion::getPos( ) const{
	return pos;
}

/** @brief Devuelve las bases que aparecen en el genoma humano de referencia y las posibles mutaciones.
*   @return El atributo ref_alt del objeto.
*/
const std::vector<string> & mutacion::getRef_alt () const{
	return ref_alt;
}

/** @brief Devuelve el nombre e identificado del gen que contiene la mutacion.
*   @return El atributo genes del objeto.
*/
const std::vector<string> & mutacion::getGenes () const{
	return genes;
}

/** @brief Devuelve si la mutacion es común en la población.
*   @return El atributo common del objeto.
*/
bool mutacion::getCommon () const{
	return common;
}

/** @brief Devuelve la frecuencia con que se observa cada base descrita en la mutacion.
*   @return El atributo caf del objeto.
*/
const std::vector<float> & mutacion::getCaf () const{
	return caf;
}

/** @brief Devuelve el nombre, ID y la base de datos de las enfermedades asociadas a la mutacion.
*   @return El atributo enfermedades del objeto.
*/
const std::vector<enfermedad> & mutacion::getEnfermedades () const{
	return enfermedades;
}

/** @brief Devuelve la relevancia clínica de la mutacion.
*   @return El atributo clnsig del objeto.
*/
const std::vector<int> & mutacion::getClnsig () const{
	return clnsig;
}



/** @brief Sobrecarga del operador de asignación. Realiza la asignacion de una enfermedad a otra 
*	   asignando parámetro por parámetro.
*   @param m Mutación que se desea asignar.
*   @return Devuelve una referencia al objeto.
*/
mutacion & mutacion::operator=(const mutacion & m){
	if(this != &m){
		this->ID = m.ID;
		this->chr = m.chr;
		this->pos = m.pos;
		this->ref_alt = m.ref_alt;
		this->genes = m.genes;
		this->common = m.common;
		this->caf = m.caf;
		this->enfermedades = m.enfermedades;
		this->clnsig = m.clnsig;
	}

	return *this;
}

/** @brief Sobrecarga del operador de igualdad. ¿Es una mutación igual que la mutación @a m?.
*   @param m Mutación que se quiere comparar
*   @return Verdadero o Falso
*/
bool mutacion::operator==(const mutacion & m) const{
	return (getID() == m.getID());
}

bool mutacion::operator!=(const mutacion & m) const{
	return (getChr() != m.getChr()) || (getPos() != m.getPos());
}

/** @brief Sobrecarga del operador menor estricto. ¿Es una mutación menor que la mutación @a m?
*	   Se sigue el orden del número de cromosoma que ocupa y, si son iguales, se compara la posición
*	   que ocupa dentro del cromosoma
*   @param m Mutación que se quiere comparar
*   @return Verdadero o Falso
*/
bool mutacion::operator<(const mutacion & m) const{

	string s1 = getChr(), s2 = m.getChr();
	
	if (s1 == s2) {
		if(getPos() == m.getPos())
			return (getID() != m.getID());
		else
			return (getPos() < m.getPos());
	}else if (s1 == "MT")
		return false;
	else if (s2 == "MT")
		return true;
	else if (s1=="X" && s2=="Y")
		return true;
	else if (s1=="Y" && s2=="X")
		return false;
	else if(isalpha(s1[0]) && isdigit(s2[0]))
		return false;
	else if(isalpha(s2[0]) && isdigit(s1[0]))
		return true;
	else if(stoi(s1)<stoi(s2))
		return(stoi(s1)<stoi(s2));
		
} 

/** @brief Sobrecarga del operador mayor estricto. ¿Es una mutación mayor que la mutación @a m?
*	   Se sigue el orden del número de cromosoma que ocupa y, si son iguales, se compara la posición
*	   que ocupa dentro del cromosoma
*   @param m Mutación que se quiere comparar
*   @return Verdadero o Falso
*/
bool mutacion::operator>(const mutacion & m) const {
	return !(*this<m) && !(*this==m);
}


/** @brief Sobrecarga del operador de extracción de flujo. Inserta en @a os todos los valores de los atributos de @a m.
*   @param os Flujo de salida
*   @param m Mutación de la que se desea extraer la información
*   @return Un flujo de salida con la informacion de la mutacion.
*/
ostream& operator<< ( ostream& os, const mutacion& m){
	unsigned i;
	
	os << m.getChr() << "\t" << m.getPos() << "\t" << m.getID() << "\t";
	
	os << m.getRef_alt()[0] << "\t" << m.getRef_alt()[1] << "\t";
	
	if(!m.getGenes().empty()) {
	os << "GENEINFO=";
		for (i = 0 ; i < m.getGenes().size()-1 ; i++)
			os << m.getGenes()[i] << "|";
		os << m.getGenes()[i] << ";";
	}

	if(!m.getClnsig().empty()) {
		os << "CLNSIG=";
		for (i = 0 ; i < m.getClnsig().size()-1 ; i++)
			os << m.getClnsig()[i] << "|";
		os << m.getClnsig()[i] << ";";
	}
	
	if(!m.getEnfermedades().empty()) {
		os << "CLNDSDB=";
		for (i = 0 ; i < m.getEnfermedades().size()-1 ; i++)
			os << m.getEnfermedades()[i].getDatabase() << "|";
		os << m.getEnfermedades()[i].getDatabase() << ";";
	
		os << "CLNDSDBID=";
		for (i = 0 ; i < m.getEnfermedades().size()-1 ; i++)
			os << m.getEnfermedades()[i].getID() << "|";
		os << m.getEnfermedades()[i].getID() << ";";
	

		os << "CLNDBN=";
		for (i = 0 ; i < m.getEnfermedades().size()-1 ; i++)
			os << m.getEnfermedades()[i].getName() << "|";
		os << m.getEnfermedades()[i].getName() << ";";
	}
	
	if(!m.getCaf().empty()) {
		os << "CAF=";
		for (i = 0 ; i < m.getCaf().size()-1 ; i++)
			os << m.getCaf()[i] << ",";
		os << m.getCaf()[i] << ";";
	}

	os << "COMMON=" << m.getCommon() << ";\n";
	
	
	return os;
}


/** @brief Devuelve la posición siguiente a @a busca dentro de @a texto buscando desde la posicion @a pos_ini
*   @param texto String donde se encuentra el string que queremos saltar
*   @param busca String a buscar
*   @param pos_ini Posición desde la que se desea empezar a buscar. Si no se dice nada empieza desde la posición 0
*   @return Posición siguiente a la posición del último caracter de @a busca. En caso de que no lo encuentre devuelve
*	    string::npos
*/
int mutacion::leer_despues(const string &texto, const string &busca, const int pos_ini){
	unsigned int pos = texto.find(busca,pos_ini);
	if (pos != string::npos)
		pos += busca.size();
		
	return pos;
}

/** @brief Escribe en @a cad la subcadena de @a texto desde @a pos hasta un caracter @a ignorar o hasta @a terminar
*   @param texto String de donde queremos extraer la subcadena
*   @param cad String donde desea que se escriba la subcadena
*   @param pos_ini Posicion donde comienza la subcadena
*   @param ignorar Caracter hasta donde se desea leer
*   @param terminar Caracter con el que termina la subcadena si no encuentra @a ignorar
*   @return La posición siguiente al fin de la subcadena
*/
int mutacion::leer_sin_separadores(const string &texto, string &cad, const int pos_ini, const char &ignorar, const char &terminar){
	int i = pos_ini;
	cad = "";
	
	while(texto[i] != ignorar && texto[i] != terminar)
		cad += texto[i++];
	
	return i+1;
}

