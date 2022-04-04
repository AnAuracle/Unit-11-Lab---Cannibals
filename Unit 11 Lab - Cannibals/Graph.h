#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;


template <typename Type>
class Graph;

template <typename Type>
ostream& operator << (ostream & out, const Graph<Type> &g);

template <typename Type>
class Graph {
private:
	vector<Type> vertices;
	vector<vector<Type>>edges;

public:
	Graph();
	void addVertex(Type vertex);
	void addEdge(Type, Type);
	int getVertexPos(Type item);
	int getNumVertices()const;
	bool isEdge(Type, Type);
	friend ostream& operator << <>(ostream & out, const Graph<Type> &g);
	vector<Type>getPath(Type, Type);
	void getPath(Type source, Type dest, vector<Type>sol, vector<vector<Type>>& possibleSolutions);
};



/*********************************************
* Constructs an empty graph
*
*********************************************/
template<typename Type>
Graph<Type>::Graph() {

}




/*********************************************
* Adds a Vertex to the Graphs. Note that the vertex may not be an int value
*********************************************/
template <typename Type>
void Graph<Type>::addVertex(Type vertex) {
	vertices.push_back(vertex);
	vector<Type> lst;
	edges.push_back(lst);
}

/*********************************************
* Returns the current number of vertices
*
*********************************************/
template<typename Type>
int Graph<Type>::getNumVertices()const {
	return vertices.size();
}



/*********************************************
* Returns the position in the verticies list where the given vertex is located, -1 if not found.
*
*********************************************/
template <typename Type>
int Graph<Type>::getVertexPos(Type item) {
	for (unsigned int i = 0; i < vertices.size(); i++) {
		if (item == vertices[i]) {
			return i;
		}
	}
	return -1; //return negative one
}//End findVertexPos

/*********************************************
* Adds an edge going in the direction of source going to target
*
*********************************************/
template <typename Type>
void Graph<Type>::addEdge(Type source, Type target) {
	int srcPos = getVertexPos(source);
	if (srcPos < 0) {
		throw runtime_error("Vertex not found");
	}
	edges[srcPos].push_back(target);
}

template <typename Type>
bool Graph<Type>::isEdge(Type source, Type dest) {
	int srcPos = getVertexPos(source);
	if (srcPos < 0) {
		throw runtime_error("Vertex not found");
	}
	for (unsigned int i = 0; i < edges[i].size(); i++) {
		if (edges[srcPos][i] == dest) {
			return true;
		}
	}
	return false;
}



/*********************************************
* Returns a display of the graph in the format
* vertex: edge edge
* Note: This is not a traversal, just output
*********************************************/
template <typename Type>
ostream& operator << (ostream & out, const Graph<Type> &g) {
	for (unsigned int i = 0; i < g.vertices.size(); i++) {
		out << g.vertices[i] << ": ";
		for (unsigned int e = 0; e < g.edges[i].size(); e++) {
			out << g.edges[i][e] << " ";
		}
		out << endl;
	}
	return out;
}

/*
  getPath will return the shortest path from source to dest.
  You are welcome to use any solution not limited to the following, depth first search to traverse
  graph to find the solution, breadth first, shortest path first, or any
  other graph algorithm.

  You will return a vector with the solution from the source to the destination.
  IE: The source will be in position 1 the destination is in the last position of the solution, and each node in between
  are the verticies it will travel to get to the destination.  There will not be any
  other verticies in the list.
*/


template <typename Type>
vector<Type> Graph<Type>::getPath(Type source, Type dest) {
	int sourceIdx = getVertexPos(source);
	vector<Type> solution;
	vector<vector<Type>> possibleSolutions;
	if (isEdge(source, dest)) {
		solution.push_back(source);
		solution.push_back(dest);
	}

	for (int i = 0; i < edges[sourceIdx].size(); i++) {
		getPath(source, dest, solution, possibleSolutions);
	}
	for (int i = 0; i < possibleSolutions.size(); i++) {
		if (solution.size() == 0) {
			solution = possibleSolutions[i];
		}
		else if (solution.size() > possibleSolutions[i].size()) {
			solution = possibleSolutions[i];
		}
	}
	return solution;
}

template <typename Type>
void Graph<Type>::getPath(Type source, Type dest, vector<Type>sol, vector<vector<Type>>& possibleSolutions) {
	sol.push_back(source);
	int sourceIdx = getVertexPos(source);
	for (int i = 0; i < edges[sourceIdx].size(); i++) {

		if (edges[sourceIdx][i] == dest) {
			sol.push_back(edges[sourceIdx][i]);
			possibleSolutions.push_back(sol);
			return;
		}
		if (find(begin(sol), end(sol), edges[sourceIdx][i]) == end(sol)) {
			getPath(edges[sourceIdx][i], dest, sol, possibleSolutions);
		}
	}
}

