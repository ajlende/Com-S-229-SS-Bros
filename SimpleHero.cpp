/*
 * SimpleHero.cpp
 * by Alex Lende
 */

#include "SimpleHero.hpp"
#include <ncurses.h>
#include <stdlib.h>
#include <limits.h>
#include <iostream>
#include <queue>
#include <vector>

SimpleHero::SimpleHero( int type ) : Actor(type) {
	// TODO: Initialize member variables
}

SimpleHero::~SimpleHero() {
	// TODO: Free all member variables
}

void SimpleHero::findPath(GraphMap* map, int start, int end, std::vector<int>* V) {
	int numVerts = map->getNumVertices();
	bool* visited = new bool[numVerts];
	int* previous = new int[numVerts];

	auto Q = new std::queue<int>();

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
		int* neighbors = new int[numNeighbors];
		
		printf("Neighbors to vertex [%d, (%d, %d)]: ");
		for (int i = 0; i < numNeighbors; i++) {
			int a, b;
			map->getNeighbor(x, y, i, a, b);
			neighbors[i] = map->getVertex(a, b);
			printf("[%d, (%d, %d)] ", neighbors[i], a, b);
		}
		printf("\n");
		

		// For each of the neighbors, if it isn't visited, then put it on the queue and mark the vertex that we came from to reach it
		for (int n = 0; n < numNeighbors; n++) {
			if (!visited[neighbors[n]]) {
				visited[neighbors[n]] = true;
				printf("visited %d", neighbors[n]);
				previous[neighbors[n]] = vertex;
				Q->push(neighbors[n]);
			}
		}

		delete[] neighbors;
	}
	
	// If the end vertex hasn't been visited, then there is no path
	if (!visited[end]) {
		printf("findPath() could not find a path to %d!\n", end);
	} else {
		// TODO: Build the array of the path to return
		int n = end;
		while (n != start) {
			n = previous[n];
			V->push_back(n);
		}

		printf("Path from %d to %d: ", start, end);
		for (auto& c : *V) {
    		printf("%d ", c);
		}
		printf("\n");
	}

	delete[] visited;
	delete[] previous;
	delete Q;
}

void SimpleHero::getEatables(GraphMap* map, std::vector<int>* allEatables) {
	// TODO: Get an array of the index of all of the eatables remaining to eat
	int numActors = map->getNumActors();
	for (int i = 0; i < numActors; i++) {
		int actor = map->getActorType(i);
		if ((actor & ACTOR_EATABLE) && !(actor & ACTOR_DEAD)) {
			int x, y;
			map->getActorPosition(i, x, y);
			int vertex = map->getVertex(x, y);
			allEatables->push_back(vertex);
			printf("Found Eatable %d at vertex %d: (%d, %d)\n", i, vertex, x, y);
		}
	}
}

int SimpleHero::selectNeighbor( GraphMap* map, int x, int y ) {
	// TODO: Select the next move that the SimpleHero is going to make.

	printf("Hero is at vertex %d: (%d, %d)\n", map->getVertex(x, y), x, y);

	int d = map->getNumNeighbors(x, y);

	if ( d <= 1 )
	{
		return 0;
	}

	auto eatables = new std::vector<int>();
	this->getEatables(map, eatables);

	int start = map->getVertex(x, y);
	int closest = 0;
	unsigned int min_distance = UINT_MAX;
	
	// Look through all the eatables for the closest one
	for (int& e : *eatables) {
		auto path = new std::vector<int>;
		this->findPath(map, start, e, path);
		
		if (!path->empty()) {
			printf("Path found to %d! Distance is %d\n", e, path->size());
		} else {
			printf("No path to eatable at vertex %d\n", e);
		}

		if (!path->empty() && path->size() < min_distance) {
			closest = path->back();
		}

		delete path;
	}

	delete eatables;

	int a, b;
	map->getPosition(closest, a, b);
	
	// Figure out which neighbor coresponds to the index that we want to go to.
	for (int i = 0; i < d; i++) {
		int p, q;
		map->getNeighbor(x, y, i, p, q);

		if ( p == a && q == b ) {
			return i;
		}
	}
	
	return 0; // TODO: Return the direction that the SimpleHero is going to go.
}

Actor* SimpleHero::duplicate() {
	return new SimpleHero(this->getType());
}

const char* SimpleHero::getActorId() {
	return "simplehero";
}

const char* SimpleHero::getNetId() {
	return "ajlende";
}


