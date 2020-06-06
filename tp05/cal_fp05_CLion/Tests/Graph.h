/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include "MutablePriorityQueue.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
	T info;						// content of the vertex
	vector<Edge<T> > adj;		// outgoing edges
	
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool visited = false;		// auxiliary field
	bool processing = false;	// auxiliary field

	void addEdge(Vertex<T> *dest, double w);

public:
	Vertex(T in);
	T getInfo() const;
	double getDist() const;
	Vertex *getPath() const;

	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

#include <unordered_map>

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set

public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;

	// Fp05 - single source
	void unweightedShortestPath(const T &s);    //TODO...
	void dijkstraShortestPath(const T &s);      //TODO...
	void bellmanFordShortestPath(const T &s);   //TODO...
	vector<T> getPathTo(const T &dest) const;   //TODO...

	// Fp05 - all pairs
    unordered_map<
        const Vertex<T>*,
        unordered_map<
            const Vertex<T>*,
            double
        >
    > D;
    unordered_map<
        const Vertex<T>*,
        unordered_map<
            const Vertex<T>*,
            const Vertex<T>*
        >
    > P;
    void floydWarshallShortestPath();   //TODO...
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...

};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/*
 * Adds a vertex with a given content or info (in) to a graph (this).
 * Returns true if successful,
 * and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful,
 * and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w);
	return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
    for(Vertex<T> *v:vertexSet) v->path = nullptr;
    Vertex<T> *origin = findVertex(orig);
    queue<Vertex<T> *> q;
    origin->path = origin; q.push(origin);
    while(!q.empty()){
        Vertex<T> *u = q.front(); q.pop();
        for(Edge<T> e : u->adj){
            if(e.dest->getPath() == nullptr) {
                e.dest->path = u;
                q.push(e.dest);
            }
        }
    }
    origin->path = nullptr;
}


template<class T>
void Graph<T>::dijkstraShortestPath(const T &orig) {
    for(Vertex<T> *v:vertexSet){
        v->path = nullptr;
        v->dist = 1e20;
    }
    Vertex<T> *origin = findVertex(orig);
    priority_queue<pair<double, Vertex<T>*> > q;
    origin->path = origin; origin->dist = 0.0; q.push(make_pair(-0.0, origin));
    while(!q.empty()){
        auto p = q.top(); q.pop();
        Vertex<T> *u = p.second;
        double c = u->dist;
        for(Edge<T> e:u->adj) {
            double c_ = c + e.weight;
            if(c_ < e.dest->getDist()){
                e.dest->dist = c_;
                e.dest->path = u;
                q.push(make_pair(-c_, e.dest));
            }
        }
    }
    origin->path = nullptr;
}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
    for(Vertex<T> *v:vertexSet){
	    v->dist = 1e20;
	    v->path = nullptr;
	}
    findVertex(orig)->dist = 0.0;
	for(size_t i = 0; i < vertexSet.size(); ++i){
	    for(Vertex<T> *u:vertexSet){
	        for(const Edge<T> &e:u->adj){
	            double c = u->dist+e.weight;
	            if(c < e.dest->dist){
	                e.dest->dist = c;
	                e.dest->path = u;
	            }
	        }
	    }
	}

}

template<class T>
vector<T> Graph<T>::getPathTo(const T &dest) const{
	vector<T> res;
	Vertex<T> *v = findVertex(dest);
	while(v != nullptr){
	    res.push_back(v->getInfo());
	    v = v->getPath();
	}
	reverse(res.begin(), res.end());
	return res;
}



/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
    D.clear(); P.clear();
    for(const Vertex<T> *u:vertexSet){
        for(const Vertex<T> *v:vertexSet) {
            D[u][v] = 1e20;
            P[u][v] = nullptr;
        }
    }
    for(const Vertex<T> *u:vertexSet){
        D[u][u] = 0.0;
    }
    for(const Vertex<T> *u:vertexSet){
        for(const Edge<T> &e:u->adj){
            if(e.weight < D[u][e.dest]) {
                D[u][e.dest] = e.weight;
                P[u][e.dest] = u;
            }
        }
    }
    for(const Vertex<T> *k:vertexSet){
        for(const Vertex<T> *i:vertexSet){
            if(D[i][k] == 1e20) continue;
            for(const Vertex<T> *j:vertexSet){
                double c = D[i][k] + D[k][j];
                if(c < D[i][j]){
                    D[i][j] = c;
                    P[i][j] = P[k][j];
                }
            }
        }
    }
	// TODO
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
    if(orig == dest) return vector<T>(1, orig);
    const Vertex<T> *i = findVertex(orig);
    const Vertex<T> *j = findVertex(dest);
    vector<T> res = getfloydWarshallPath(orig, P.at(i).at(j)->getInfo());
    res.push_back(dest);
    return res;
}


#endif /* GRAPH_H_ */
