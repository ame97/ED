/** @brief fichero de implementacion de la clase enfermedad

*/

using namespace std;

/** @brief Constructor por defecto de la clase enfermedad
*/
enfermedad::enfermedad(){
  // @todo implementar esta funcion
	setName("");
	setID("");
	setDatabase("");
}

/** @brief Constructor de la clase enfermedad. Asigna @a name, @a ID y @a database a los atributos del objeto creado.
*   @param name Nombre de la enfermedad.
*   @param ID Identificador de la enfermedad.
*   @param database La base de datos donde se encuentra la información.
*/
enfermedad::enfermedad(const string & name, const string & ID, const string & database){
	setName(name);
	setID(ID);
	setDatabase(database);
}
  
/** @brief Asigna @a name al atributo del objeto llamado name.
*/    
void enfermedad::setName(const string & name){
	this->name = name;
}

/** @brief Asigna @a ID al atributo del objeto llamado ID.
*/
void enfermedad::setID(const string & ID){
	this->ID = ID;
}

/** @brief Asigna @a database al atributo del objeto llamado database.
*/
void enfermedad::setDatabase(const string & database){
	this->database = database;
}


/** @brief Deuelve el nombre de la enfermedad.
*   @return El atributo name del objeto.
*/
string enfermedad::getName( )const{
	return name;
}

/** @brief Deuelve el ID de la enfermedad.
*   @return El atributo ID del objeto.
*/
string enfermedad::getID( )const{
	return ID;
}

/** @brief Deuelve donde se encuentra la información de la enfermedad.
*   @return El atributo name del objeto.
*/
string enfermedad::getDatabase( )const{
	return database;
}


/** @brief Sobrecarga del operador de asignación. Realiza la asignacion de una enfermedad a otra asignando
*	 parámetro por parámetro.
*   @param e Enfermedad que se desea asignar.
*   @return Devuelve una referencia al objeto.
*/
enfermedad & enfermedad::operator=(const enfermedad & e){
	if(this != &e){
		this->name=e.name;
		this->ID=e.ID;
		this->database=e.database;
	}

	return *this;
}

/** @brief Pasa a una cadena todos los atributos de una enfermedad.
*   @return Un string con toda la información de la enfermedad.
*/
string enfermedad::toString() const{
	return (getName() + "/" + getID() + "/" + getDatabase());
}


/** @brief Sobrecarga del operador de igualdad. ¿Es una enfermedad igual que la enfermedad @a e?.
*  @param e Enfermedad con la que se desea comparar.
*  @return Verdadero o Falso
*/
bool enfermedad::operator==(const enfermedad & e) const{
	return (getID() == e.getID());
}

/** @brief Sobrecarga del operador de desigualdad. ¿Es una enfermedad distinta a la enfermedad @a e?.
*   @param e Enfermedad con la que se desea comparar.
*   @return Verdadero o Falso
*/
bool enfermedad::operator!=(const enfermedad & e) const{
	return (getID() != e.getID());
}

/** @brief Sobrecarga del operador menor estricto. ¿Es una enfermedad menor que la enfermedad @a e?
*	 Se sigue el orden alfabetico teniendo en cuenta el atributo name.
*   @param e Enfermedad con la que se desea comparar.
*   @return Verdadero o Falso
*/
bool enfermedad::operator<(const enfermedad & e) const{
	return (getName() < e.getName());
}

/** @brief ¿El nombre de la enfermedad contiene @a str?
*   @param str Cadena que se busca en el nombre de la enfermedad
*   @return Verdadero o Falso
*/
bool enfermedad::nameContains(const string & str) const{
	//Devuelve True si str estᡩncluido en el nombre de la enfermedad, aunque no se trate del nombre completo
	//No debe ser sensible a mayúsculas/min򳣵las
	string s1, s2;
	
	for (unsigned int i = 0 ; i < str.size() ; i++)
		s1.push_back(toupper(str[i]));
	
	for (unsigned int i = 0 ; i < name.size() ; i++)
		s2.push_back(toupper(name[i]));
	
	return (s2.find(s1) != string::npos);
}

/** @brief Sobrecarga del operador de extracción de flujo. Inserta en @a os todos los valores de los atributos de @a e.
*   @param os Un flujo de salida
*   @param e Enfermedad de la que se desea extraer informaci󮍊*   @return Un flujo de salida con la informacion
*	     de la enfermedad.
*/
 ostream& operator<< ( ostream& os, const enfermedad & e){
	os << e.toString();
	
	return os;
 }
