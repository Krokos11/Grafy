#ifndef vertex_h
#define vertex_h

class Vertex{

	int numer;
	Vertex *next;
	
public:

	Vertex(int nr){
		numer = nr;
		next = NULL;
	}

	Vertex *getNext(){ return next; }
	void setNext(Vertex *tmp) { next = tmp; }

};
//przechowuje numery wierzcholkow

#endif