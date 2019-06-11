#ifndef node_h
#define node_h

class Node{

	int v1, v2, weight;
	Node *next;

public:
	Node(int u, int v, int w){
		v1 = u;
		v2 = v;
		weight = w;
		next = NULL;
	}

	Node *getNext(){ return next; }
	void setNext(Node *tmp) { next = tmp; }
	int getWeight(){ return weight; }
	int getStart(){ return v1; };
	int getEnd(){ return v2; }
};

//przechowuje krawedzie

#endif