#ifndef _CRITERIOS_H_
#define _CRITERIOS_H_

template<class T>
class creciente {
	public:
		bool operator()(const T & e1,const T &e2) {
			return (e1<e2);
		}
};

template<class T>
class decreciente {
	public:
		bool operator()(const T & e1,const T &e2) {
			return (e1>e2);
		}
};

class crecienteID {
	public:
		bool operator()(const mutacion & e1,const mutacion &e2) {
			return (e1.getID()<e2.getID());
		}
};

template<class T>
class decrecienteID {
	public:
		bool operator()(const mutacion & e1,const mutacion &e2) {
			return (e1.getID()>e2.getID());
		}
};

class crecienteEnfermedad {
	public:
		bool operator()(const mutacion & e1,const mutacion &e2) {
			enfermedad min1=e1.getEnfermedades()[0];
			enfermedad min2=e2.getEnfermedades()[0];
			for(int i=1;i<e1.getEnfermedades().size();++i) {
				if(min1>e1.getEnfermedades()[i])
					min1=e1.getEnfermedades()[i]
			}
	
			for(int i=1;i<e2.getEnfermedades().size();++i) {
				if(min2>e2.getEnfermedades()[i])
					min2=e2.getEnfermedades()[i]
			}

			return (min1<min2);
		}
};

template<class T>
class decrecienteEnfermedad {
	public:
		bool operator()(const mutacion & e1,const mutacion &e2) {
			enfermedad max1=e1.getEnfermedades()[0];
			enfermedad max2=e2.getEnfermedades()[0];
			for(int i=1;i<e1.getEnfermedades().size();++i) {
				if(max<e1.getEnfermedades()[i])
					max1=e1.getEnfermedades()[i]
			}
	
			for(int i=1;i<e2.getEnfermedades().size();++i) {
				if(max2<e2.getEnfermedades()[i])
					max2=e2.getEnfermedades()[i]
			}

			return (max1>max2);
		}
};

#endif
