#ifndef _CRITERIOS_H_
#define _CRITERIOS_H_

template<class T>
class crecienteCP {
	bool operator()(const T &e) {
		return (*this<e);
	}
};

#endif
