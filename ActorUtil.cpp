#include "Actor.hpp"
#include "GraphMap.hpp"
#include "ActorUtil.hpp"
#include <queue>
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
