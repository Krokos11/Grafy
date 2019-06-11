#ifndef list_h
#define list_h
#include"vertex.h"
#include"node.h"

struct ListaSasiedztwa{
	ListaSasiedztwa *next; //wskaznik do tworzenia nastepnego polaczenia do kolejnego wierzcholka
	int v, w; //punkt docelowy i waga
};


class List{

	Vertex *wierz; //wierzcholek
	Node *polacz;	//polaczenie

public:
	List(){
		wierz = NULL;
		polacz = NULL;
	}

	void Add(int u, int v, int weight){
		Vertex *v_tmp = new Vertex(u);
		Node *n_tmp = new Node(u, v, weight);
		
		if(wierz == NULL) wierz = v_tmp;
		/*else{
			Vertex *vv_tmp = wierz;
			while(vv_tmp->getNext() != NULL)
				vv_tmp = vv_tmp->getNext();
			vv_tmp->setNext(v_tmp);
		}*/

		if(polacz == NULL) polacz = n_tmp;
		else{
			Node *nn_tmp = polacz;
			while(nn_tmp->getNext() != NULL)
				nn_tmp = nn_tmp->getNext();
			nn_tmp->setNext(n_tmp);
		}
	}

	Node *getNode(){ return polacz; }


};

#endif