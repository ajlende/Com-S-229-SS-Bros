/*
 * SimpleHero.cpp
 * by Alex Lende
 *
 * TODO: Allocate structures on the stack because it is faster.
 */

#include "SimpleHero.hpp"
#include "ActorUtil.hpp"
#include <ncurses.h>
#include <cstdlib>
#include <climits>
#include <vector>
#include <deque>

using namespace std;
using namespace util;

SimpleHero::SimpleHero( int type ) : Actor(type) {
	this->goal = new deque<int>();
	this->food = new vector<int>();
}

SimpleHero::~SimpleHero() {
	delete this->goal;
	delete this->food;
}

void SimpleHero::getEatables(GraphMap* map, vector<int>* allEatables) {
	getActors(map, ACTOR_EATABLE, ACTOR_DEAD, allEatables);
}

int SimpleHero::selectNeighbor( GraphMap* map, int x, int y ) {

	int d = map->getNumNeighbors(x, y);

	if ( d <= 1 ) return 0;

	int start = map->getVertex(x, y);
	int closest = 0;
	unsigned int min_distance = UINT_MAX;
	// unsigned int t_min_distance = UINT_MAX;

	if (this->goal->empty()) {

		auto eatables = new vector<int>();
		this->getEatables(map, eatables);
		
		auto path = new vector<int>();
		auto second_path = new vector<int>();
		bool a_trap = false;

		auto reachable = new vector<int>();

		for (int& e : *eatables) {
			if (findPath(map, start, e, path))
				reachable->push_back(e);
			path->clear();
		}

	
		// Look through all the eatables for the closest one
		for (int& e : *reachable) {
			findPath(map, start, e, path);
				
			int path_size = path->size();
	
			if (!path->empty() && (path_size < min_distance)) {
				
				// Check to see if there is a path to all other ACTOR_EATABLEs before setting closest
				for (int& second : *reachable) {
					if (e == second) continue;
					if (!findPath(map, e, second, second_path)) a_trap = true;
					second_path->clear();
				}
	
				if (!a_trap) {
					min_distance = path_size;
					closest = path->back();
					this->goal->clear();
					for (int& p : *path)
						goal->push_back(p);
				}
		}
	
			a_trap = false;
	
			path->clear();
		}
	
		delete path;
		delete second_path;
		delete reachable;
	
		delete eatables;

	} else {
		closest = this->goal->back();
		goal->pop_back();
	}

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


