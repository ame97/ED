#ifndef _CRITERIOS_H_
#define _CRITERIOS_H_

template<class T>
class crecienteCP {
	public:
		bool operator()(const T & e1,const T &e2) {
			return (e1<e2);
		}
};

#endif
