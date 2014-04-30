/*
 * ActorUtil.cpp
 * by Alex Lende
 */

#include "Actor.hpp"
#include "GraphMap.hpp"
#include "ActorUtil.hpp"
#include <queue>
#include <stack>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

bool util::findPath(GraphMap* map, int start, int end, vector<int>* V) {
	int   numVerts = map->getNumVertices();
	bool* visited = new bool[numVerts]();
	int*  previous = new int[numVerts]();

	auto Q = new queue<int>();

	previous[start] = start;
	visited[start] = true;
	Q->push(start);

	while (!Q->empty()) {
		int vertex = Q->front();
		Q->pop();

		// Get an array of the vertex's neighbors
		int x, y;
		map->getPosition(vertex, x, y);
		int numNeighbors = map->getNumNeighbors(x, y);
		int* neighbors = new int[numNeighbors]();
		
		for (int i = 0; i < numNeighbors; i++) {
			int a, b;
			map->getNeighbor(x, y, i, a, b);
			neighbors[i] = map->getVertex(a, b);
		}
		

		// For each of the neighbors, if it isn't visited, then put it on the queue and mark the vertex that we came from to reach it
		for (int n = 0; n < numNeighbors; n++) {
			if (!visited[neighbors[n]]) {
				visited[neighbors[n]] = true;
				previous[neighbors[n]] = vertex;
				Q->push(neighbors[n]);
			}
		}

		delete[] neighbors;

		if (visited[end]) break;

	}
	
	// If the end vertex hasn't been visited, then there is no path
	if (!visited[end]) {
		return false;
	} else {
		int n = end;
		while (n != start) {
			V->push_back(n);
			n = previous[n];
		}
	}

	delete[] visited;
	delete[] previous;
	delete Q;

	return true;
}

bool util::findPath(GraphMap* map, int start, int end, vector<int>* V, int avoidtype) {
	int   numVerts = map->getNumVertices();
	bool* visited = new bool[numVerts]();
	int*  previous = new int[numVerts]();

	auto Q = new queue<int>();

	auto avoid = new vector<int>();
	util::getActors(map, avoidtype, ACTOR_DEAD, avoid);

	previous[start] = start;
	visited[start] = true;
	Q->push(start);

	while (!Q->empty()) {
		int vertex = Q->front();
		Q->pop();

		// Get an array of the vertex's neighbors
		int x, y;
		map->getPosition(vertex, x, y);
		int numNeighbors = map->getNumNeighbors(x, y);
		int* neighbors = new int[numNeighbors]();
		
		for (int i = 0; i < numNeighbors; i++) {
			int a, b, vert;
			map->getNeighbor(x, y, i, a, b);
			vert = map->getVertex(a, b);
			if (find(avoid->begin(), avoid->end(), vert) != avoid->end()) {
				// We found something that we want to avoid, so it no longer counts as a neighbor
				numNeighbors--;
			} else {
				// We didn't find something that we want to avoid, so it's okay to add it to the list of neighbors.
				neighbors[i] = vert;
			}
		}
		

		// For each of the neighbors, if it isn't visited, then put it on the queue and mark the vertex that we came from to reach it
		for (int n = 0; n < numNeighbors; n++) {
			if (!visited[neighbors[n]]) {
				visited[neighbors[n]] = true;
				previous[neighbors[n]] = vertex;
				Q->push(neighbors[n]);
			}
		}

		delete[] neighbors;

		if (visited[end]) break;

	}
	
	// If the end vertex hasn't been visited, then there is no path
	if (!visited[end]) {
		return false;
	} else {
		int n = end;
		while (n != start) {
			V->push_back(n);
			n = previous[n];
		}
	}

	delete[] visited;
	delete[] previous;
	delete Q;

	return true;
}

bool util::searchAll(GraphMap* map, int start, int searchtype) {

	int depth = 0;

	int numVerts = map->getNumVertices();
	bool* visited = new bool[numVerts]();
	
	auto V = new vector<int>();
	getActors(map, searchtype, ACTOR_DEAD, V);

	auto S = new stack<int>();

	S->push(start);

	while (!S->empty()) {

		int vertex = S->top();
		S->pop();

		if (!visited[vertex] && depth < radius) {

			visited[vertex] = true;

			// Check to see if the current vertex is one of the vertexes with an actor with the searchtype at it's position
			for (auto a : *V) if (a == vertex) {
				printf("Found at vertex: %d\n", vertex);
				return true;
			}

			int x, y;
			map->getPosition(vertex, x, y);
			int numNeighbors = map->getNumNeighbors(x, y);
		
			for (int i = 0; i < numNeighbors; i++) {
				int a, b;
				map->getNeighbor(x, y, i, a, b);
				S->push(map->getVertex(a, b));
			}

		}
	}

	delete S;
	delete V;
	delete[] visited;

	return false;
}

bool util::searchRadius(GraphMap* map, int start, int radius, int searchtype) {
	bool searchflag = false;

	int numVerts = map->getNumVertices();
	bool* visited = new bool[numVerts]();

	auto searchvect = new vector<int>();
	getActors(map, searchtype, ACTOR_DEAD, searchvect);

	bool result = searchRadiusRec(map, start, radius, searchtype, visited, searchvect, searchflag);

	delete[] visited;
	delete searchvect;

	return result;
}

bool util::searchRadiusRec(GraphMap* map, int vertex, int radius, int searchtype, bool* visited, vactor<int>* searchvect, bool& searchflag) {
	if (radius < 0) {
		return searchflag;
	}

	visited[vertex] = true;

	for (auto a : *searchvect) if (a == vertex) {
		printf("Rec found at vertex: %d\n", vertex);
		searchflag = true;
		return true;
	}
	
	// Get an array of the vertex's neighbors
	int x, y;
	map->getPosition(vertex, x, y);
	int numNeighbors = map->getNumNeighbors(x, y);
	// int* neighbors = new int[numNeighbors]();
	
	for (int i = 0; i < numNeighbors; i++) {
		int a, b;
		map->getNeighbor(x, y, i, a, b);
		int nextneighbor = map->getVertex(a, b);
		if (!visited[nextneighbor]) {
			searchRadiusRec(map, nextneighbor, radius-1, searchtype, visited, searchvect, searchflag);
		}
	}

}

void util::getActors(GraphMap* map, int y_type, int n_type, vector<int>* allActors) {
	int numActors = map->getNumActors();
	for (int i = 0; i < numActors; i++) {
		int actor = map->getActorType(i);
		if ((actor & y_type) == y_type && (actor & n_type) == 0) {
			int x, y;
			map->getActorPosition(i, x, y);
			int vertex = map->getVertex(x, y);
			allActors->push_back(vertex);
		}
	}
}
