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

bool SimpleHero::findPath(GraphMap* map, int start, int end, std::vector<int>* V) {
	int numVerts = map->getNumVertices();
	bool* visited = new bool[numVerts]();
	int* previous = new int[numVerts]();

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

void SimpleHero::getEatables(GraphMap* map, std::vector<int>* allEatables) {
	int numActors = map->getNumActors();
	for (int i = 0; i < numActors; i++) {
		int actor = map->getActorType(i);
		if ((actor & ACTOR_EATABLE) && !(actor & ACTOR_DEAD)) {
			int x, y;
			map->getActorPosition(i, x, y);
			int vertex = map->getVertex(x, y);
			allEatables->push_back(vertex);
		}
	}
}

int SimpleHero::selectNeighbor( GraphMap* map, int x, int y ) {

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
	
	auto path = new std::vector<int>();
	auto second_path = new std::vector<int>();
	bool a_trap = false;

	// Look through all the eatables for the closest one
	for (int& e : *eatables) {
		this->findPath(map, start, e, path);

		// Check to see if there is a path to all other ACTOR_EATABLEs before setting closest
		for (int& second : *eatables) {
			if (e == second) continue;
			if (!this->findPath(map, e, second, second_path)) a_trap = true;
			second_path->clear();
		}

		if (!path->empty() && path->size() < min_distance && !a_trap) {
			min_distance = path->size();
			closest = path->back();
		}

		a_trap = false;

		path->clear();
	}

	delete path;
	delete second_path;

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
	
	return 0;
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


