#include <iostream>
#include <ctime>
#include"graph.h"
#include"list.h"
#include"vertex.h"
#include"node.h"

void Graph::RandomGraph(int D){

	srand(time(NULL));
    
    int u, v, w;
    float E = D*V*(V-1)/200;
    
    std::cout<< "\nVertexes = " << V << ", Edges = " << E << ", Density = " << D << "\n\n"; 
    
    for(int i = 0; i < E; i++){
        u = rand() % V;
        v = rand() % V;
        while(u == v){
            u = rand() % V;
            v = rand() % V;
        }
        w = rand() % V + 1;

    AddEdge(u, v, w);
    AddEdge(v, u, w);
	}

}



void Graph::DijkstraLista(int D){

	const int MAXINT = 247483647;   //nieskonczonosc
	bool *QS;                       // Zbiory Q i S, sprawdzenie w ktorym zbiorze jest dany wierzcholek
  	ListaSasiedztwa **graf;         // Tablica list sąsiedztwa
  	ListaSasiedztwa *pw,*rw;

  	int i, j, x, y, w, u;

  	int v = 0; //wierzcholek startowy
  	int n = V; //liczba wierzcholkow
  	int m = D*V*(V-1)/200;	//ilosc krawedzi

//Tablice dynamiczne

  	int *d = new int [n];             // Tablica kosztów dojścia
  	int *p = new int [n];             // Tablica poprzedników
  	QS = new bool [n];            // Zbiory Q i S
  	graf = new ListaSasiedztwa * [n];       // Tablica list sąsiedztwa, tworzenie obiektow na liscie
  	int *S    = new int [n];             // Stos
   	int sptr = 0;                       // Wskaźnik stosu

  	 for(i = 0; i < n; i++)
  	{
	    d[i] = MAXINT;
	    p[i] = -1;
	    QS[i] = false;
	    graf[i] = NULL;	//lista sasiedztwa
	}
//do tej chwili mamy stworzone obiekty, ale lista sasiedztwa nie jest wypelniona
  	
  // Odczytujemy dane wejściowe

  	int inkr = 0; //nadanie startowego wierzcholka
  	Node *tmp = getList(inkr).getNode(); //pobieranie z listy krawedzi, krawedz
  	for(i = 0; i < 2*m; i++){ //wykonanie petli
  		if(tmp == NULL){ //czy dany wierzcholek funkcji ma jakies polaczenia
  			inkr++; //inkrementacja wierzcholka
  			while(getList(inkr).getNode() == NULL) //dopuki nie znajdzie wierzcholka z jakims polaczeniem, to szuka kolejnego wierzcholka
  				inkr++;
  			if(inkr<n) tmp = getList(inkr).getNode();
  		}
  		x = tmp->getStart(); //wierzcholke poczatkowy
  		y = tmp->getEnd();	//wierzcholek koncowy
  		w = tmp->getWeight(); //waga
  		pw = new ListaSasiedztwa;
  		pw->v = y; //przypisywnie wierzcholka docelowego do listy
  		pw->w = w; //wagi
  		pw->next = graf[x];//tworzenie nastepnego polaczenia
  		graf[x] = pw;
  		if(tmp->getNext() != NULL) tmp = tmp->getNext(); //sprawdzenie czy dany wierzcholek ma kolejne polaczenie, jesli nie to przechodzi do nastepnego miejsca w liscie( kolejnego wierzcholka)
  		else if(inkr<n) tmp = getList(++inkr).getNode(); //przejscie do kolejnego wierzcholka
  	}

  	//std::cout<<std::endl;

  	d[v] = 0;                       // Koszt dojścia v jest zerowy

    for(i = 0; i < n; i++) //szukanie wierzcholka o najmniejszym kojscie dojscia
  	{
	    // Szukamy wierzchołka w Q o najmniejszym koszcie d

	    for(j = 0; QS[j]; j++);
	    for(u = j++; j < n; j++)
	      if(!QS[j] && (d[j] < d[u])) u = j;

	    // Znaleziony wierzchołek przenosimy do S

	    QS[u] = true;
	    //std::cout<<u<<std::endl<<std::endl;
	    // Modyfikujemy odpowiednio wszystkich sąsiadów u, którzy są w Q

	    for(pw = graf[u]; pw; pw = pw->next)
	      if(!QS[pw->v] && (d[pw->v] > d[u] + pw->w))
	      {
	        d[pw->v] = d[u] + pw->w;
	        p[pw->v] = u;
	        //std::cout<<pw->v<<std::endl;
	        //std::cout<<d[pw->v]<<std::endl;
	      }
  	}


	   // wyswietlanie

  /*for(i = 0; i < n; i++)
  {
    std::cout << i << ": ";

    // Ścieżkę przechodzimy od końca ku początkowi,
    // Zapisując na stosie kolejne wierzchołki

    for(j = i; j > -1; j = p[j]) S[sptr++] = j;

    // Wyświetlamy ścieżkę, pobierając wierzchołki ze stosu

    while(sptr) std::cout << S[--sptr] << " ";

    // Na końcu ścieżki wypisujemy jej koszt

    std::cout << "$" << d[i] << std::endl;
  }*/


  delete [] d;
  delete [] p;
  delete [] QS;
  delete [] S;

  for(i = 0; i < n; i++)
  {
    pw = graf[i];
    while(pw)
    {
      rw = pw;
      pw = pw->next;
      delete rw;
    }
  }

  delete [] graf;

}

void Graph::DijkstraTablica(int D){

	const int MAXINT = 247483647;
	bool *QS;                       // Zbiory Q i S
  	int i, j, x, y, w, u;
  	int **Tab;

  	int v = 0; //wierzcholek startowy
  	int n = V; //liczba wierzcholkow
  	int m = D*V*(V-1)/200;	//ilosc krawedzi

//Tablice dynamiczne

  	int *d = new int [n];             // Tablica kosztów dojścia
  	int *p = new int [n];             // Tablica poprzedników
  	QS = new bool [n];            // Zbiory Q i S
  	int *S    = new int [n];             // Stos
   	int sptr = 0;                       // Wskaźnik stosu

   	Tab = new int * [n];
   	for(i = 0; i < n; i++)
   		Tab[i] = new int [n];

  	 for(i = 0; i < n; i++)
  	{
	    d[i] = MAXINT;
	    p[i] = -1;
	    QS[i] = false;
	    for(j = 0; j < n; j++){
	    	Tab[i][j] = MAXINT;
	    	
	    }
	}

  	
  // Odczytujemy dane wejściowe

  	int inkr = 0;
  	Node *tmp = getList(inkr).getNode();
  	for(i = 0; i < 2*m; i++){
  		if(tmp == NULL){
  			inkr++;
  			while(getList(inkr).getNode() == NULL)
  				inkr++;
  			if(inkr<n) tmp = getList(inkr).getNode();
  		}
  		x = tmp->getStart();
  		y = tmp->getEnd();
  		w = tmp->getWeight();
        
        if(Tab[x][y] > w)
  			Tab[x][y] = w;

  		if(tmp->getNext() != NULL) tmp = tmp->getNext();
  		else if(inkr<n) tmp = getList(++inkr).getNode();
  	}

  	//std::cout<<std::endl;

  	d[v] = 0;                       // Koszt dojścia v jest zerowy

    for(i = 0; i < n; i++)
  	{
	    // Szukamy wierzchołka w Q o najmniejszym koszcie d

	    for(j = 0; QS[j]; j++);
	    for(u = j++; j < n; j++)
	      if(!QS[j] && (d[j] < d[u])) u = j;

	    // Znaleziony wierzchołek przenosimy do S

	    QS[u] = true;

	    //std::cout<<u<<std::endl<<std::endl;
	    // Modyfikujemy odpowiednio wszystkich sąsiadów u, którzy są w Q

	    for(int c = u; c < n ; c++)
	    	for(int k = 0; k < n; k++)
			    if(!QS[k] && (d[k] > d[c] + Tab[c][k]))
			    {
			    	//wg = Tab[c][k];
			    	d[k] = d[c] + Tab[c][k];
			    	p[k] = c;
			    	//std::cout<<d[k]<<std::endl;
			    	//std::cout<<i<<std::endl;
			    	//j=0;
			    }

	    /*for(pw = graf[u]; pw; pw = pw->next)
		      if(!QS[pw->v] && (d[pw->v] > d[u] + pw->w))
		      {
		        d[pw->v] = d[u] + pw->w;
		        p[pw->v] = u;
		      }*/
  	}


	   // wyświetlanie
     /*
  for(i = 0; i < n; i++)
  {
    std::cout << i << ": ";

    // Ścieżkę przechodzimy od końca ku początkowi,
    // Zapisując na stosie kolejne wierzchołki

    for(j = i; j > -1; j = p[j]) S[sptr++] = j;

    // Wyświetlamy ścieżkę, pobierając wierzchołki ze stosu

    while(sptr) std::cout << S[--sptr] << " ";

    // Na końcu ścieżki wypisujemy jej koszt

    std::cout << "$" << d[i] << std::endl;
  }*/

  delete [] d;
  delete [] p;
  delete [] QS;
  delete [] S;

}


std::ostream &operator << (std::ostream &strOut, Graph *test_graph){

	for(int i=0; i<test_graph->getVQuant(); ++i){

		Node *n_tmp = test_graph->getList(i).getNode();

		strOut<< i << " -> ";

		while(n_tmp != NULL){
			strOut<< n_tmp->getEnd() << "#" << n_tmp->getWeight() << ", ";
			n_tmp = n_tmp->getNext();
		}
		
		strOut<<"\n";
	}
	return strOut;
}


