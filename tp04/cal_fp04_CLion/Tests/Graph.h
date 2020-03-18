/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;


/****************** Provided structures  ********************/

template <class T>
class Vertex {
	T info;                // contents
	vector<Edge<T> > adj;  // list of outgoing edges
	bool visited;          // auxiliary field used by dfs and bfs
	int indegree;          // auxiliary field used by topsort
	bool processing;       // auxiliary field used by isDAG

	void addEdge(Vertex<T> *dest, double w);
	bool removeEdgeTo(Vertex<T> *d);
public:
	Vertex(T in);
	friend class Graph<T>;
};

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
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set

	void dfsVisit(Vertex<T> *v,  vector<T> & res) const;
	Vertex<T> *findVertex(const T &in) const;
	bool dfsIsDAG(Vertex<T> *v) const;
public:
	int getNumVertex() const;
	bool addVertex(const T &in);
	bool removeVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(const T &source) const;
	vector<T> topsort() const;
	int maxNewChildren(const T &source, T &inf) const;
	bool isDAG() const;
};

/****************** Provided constructors and functions ********************/

template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
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

/****************** 1a) addVertex ********************/

/*
 *  Adds a vertex with a given content/info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if(findVertex(in) == NULL){
        Vertex<T> *v = new Vertex<T>(in);
        vertexSet.push_back(v);
        return true;
    } else return false;
}

/****************** 1b) addEdge ********************/

/*
 * Adds an edge to a graph (this), given the contents of the source (sourc) and
 * destination (dest) vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    if(findVertex(sourc) == NULL || findVertex(dest) == NULL) return false;
    findVertex(sourc)->addEdge(findVertex(dest), w);
    return true;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
}


/****************** 1c) removeEdge ********************/

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    Vertex<T> *psourc = findVertex(sourc);
    Vertex<T> *pdest  = findVertex(dest );
    if(psourc == NULL || pdest == NULL) return false;
    return psourc->removeEdgeTo(pdest);
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
    for(auto it = adj.begin(); it != adj.end(); ++it){
        if(it->dest == d){
            adj.erase(it);
            return true;
        }
    }
    return false;
}


/****************** 1d) removeVertex ********************/

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
    Vertex<T> *p = NULL;
    for(auto it = vertexSet.begin(); it != vertexSet.end(); ++it){
        if((*it)->info == in){
            p = *it;
            vertexSet.erase(it);
            break;
        }
    }
    if(p == NULL) return false;
    p->adj.clear();
    for(auto it = vertexSet.begin(); it != vertexSet.end(); ++it){
        if(!((*it)->info == in)){
            (*it)->removeEdgeTo(p);
        }
    }
    return true;
}


/****************** 2a) dfs ********************/

/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::dfs() const {
    vector<T> res;
	for(Vertex<T> *p:vertexSet) p->visited = false;
	for(Vertex<T> *p:vertexSet)
	    if(!p->visited)
	        dfsVisit(p, res);
    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
	res.push_back(v->info);
	v->visited = true;
	for(const Edge<T> &e:v->adj)
	    if(!e.dest->visited)
	        dfsVisit(e.dest, res);
}

/****************** 2b) bfs ********************/

/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::bfs(const T & source) const {
	vector<T> res;
    for(Vertex<T> *p:vertexSet) p->visited = false;
    queue<Vertex<T>*> q;
    int curr = 0;
    while(!(q.empty() && curr == vertexSet.size()-1)){
        if(q.empty()) q.push(vertexSet[curr++]);
        Vertex<T> *p = q.front(); q.pop();
        if(p->visited) continue;
        res.push_back(p->info);
        p->visited = true;
        for(const Edge<T> &e: p->adj){
            q.push(e.dest);
        }
    }
	return res;
}

/****************** 2c) toposort ********************/

/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */

#include <unordered_map>

template<class T>
vector<T> Graph<T>::topsort() const {
	vector<T> res;
	unordered_map<const Vertex<T>*, int> indegree;
	for(const Vertex<T> *p:vertexSet) indegree[p] = 0;
	for(const Vertex<T> *p:vertexSet){
	    for(const Edge<T> &e:p->adj){
	        ++indegree[e.dest];
	    }
	}
    while(!indegree.empty()){
        const Vertex<T> *p = indegree.begin()->first;
        for(const auto &pr:indegree)
            if(indegree[pr.first] < indegree[p] || (indegree[pr.first] == indegree[p] && pr.first->info < p->info))
                p = pr.first;
        if(indegree[p] > 0) return vector<T>();
        res.push_back(p->info);
        indegree.erase(indegree.find(p));
        for(const Edge<T> &e:p->adj) {
            if (indegree.find(e.dest) != indegree.end())
                --indegree[e.dest];
        }
    }
	return res;
}

/****************** 3a) maxNewChildren (HOME WORK)  ********************/

/*
 * Performs a breadth-first search in a graph (this), starting
 * from the vertex with the given source contents (source).
 * During the search, determines the vertex that has a maximum number
 * of new children (adjacent not previously visited), and returns the
 * contents of that vertex (inf) and the number of new children (return value).
 */

template <class T>
int Graph<T>::maxNewChildren(const T & source, T &inf) const {
    int res = 0;
    for(Vertex<T> *p:vertexSet) p->visited = false;
    queue<Vertex<T>*> q;
    Vertex<T> *p = findVertex(source); cout << "L296" << endl;
    if(p == NULL) return 0;  cout << "L297" << endl;
    q.push(p);
    while(!q.empty()){
        Vertex<T> *p = q.front(); q.pop();
        if(p->visited) continue;
        p->visited = true;
        int newres = 0;
        for(const Edge<T> &e: p->adj){
            if(!e.dest->visited) {
                ++newres;
                q.push(e.dest);
            }
        }
        if(newres > res){
            res = max(res, newres);
            inf = p->info;
        }
    }
    return res;
}

/****************** 3b) isDAG   (HOME WORK)  ********************/

/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

template <class T>
bool Graph<T>::isDAG() const {
    return (!topsort().empty());
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
template <class T>
bool Graph<T>::dfsIsDAG(Vertex<T> *v) const {
	// TODO (12 lines, mostly reused)
	return true;
}

#endif /* GRAPH_H_ */
