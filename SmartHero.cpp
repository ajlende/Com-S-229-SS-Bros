/*
 * SmartHero.cpp
 * by Alex Lende
 *
 * This hero will eat all eatables, given sufficient time, “slow” enemies, and no “fast” powerups.
 * 
 * Grading Details
 *   • There will be no "traps" (if you can reach an actor, then that actor can reach you.)
 *   • There will be heroes, enemies, and powerups available.
 *   • Enemies and powerups will not move faster than heroes (and will likely move slower)
 *   • 50% for the portion of heroes that survive.
 *   • 50% for the portion of powerups that are eaten.
 *   • 50% for the portion of eatables that are eaten.
 *   • [For a 10pt test case, 5pts for each of the three conditions.]
 */

#include "Actor.hpp"
#include "SmartHero.hpp"
#include "GraphMap.hpp"
#include "ActorUtil.hpp"
#include <climits>
#include <vector>
#include <deque>

using namespace std;
using namespace util;

SmartHero::SmartHero(int type) : Actor(type) {
	
}

SmartHero::~SmartHero() {
	
}

void SmartHero::getEatables(GraphMap* map, vector<int>* allEatables) {
	getActors(map, ACTOR_EATABLE, ACTOR_DEAD, allEatables);
}

int SmartHero::selectNeighbor(GraphMap* map, int x, int y) {
	int d = map->getNumNeighbors(x, y);

	if ( d <= 1 ) return 0;

	int start = map->getVertex(x, y);
	int closest = 0;
	unsigned int min_distance = UINT_MAX;

	auto eatables = new vector<int>();
	this->getEatables(map, eatables);
	
	auto path = new vector<int>();
	
	// Look through all the eatables for the closest one
	for (int& e : *eatables) {
		if (findPath(map, start, e, path, ACTOR_ENEMY/*, map->getDelayHero() - map->getDelayEnemy() + 1*/)) {

			int path_size = path->size();
	
			if (!path->empty() && (path_size < min_distance)) {
				min_distance = path_size;
				closest = path->back();
			}
	
			path->clear();
		}
	}
	
	delete path;
	
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

void SmartHero::runAway(GraphMap* map, int x, int y) {
	return;
}

Actor* SmartHero::duplicate() {
	return new SmartHero(this->getType());
}

const char* SmartHero::getActorId() {
	return "smarthero";
}

const char* SmartHero::getNetId() {
	return "ajlende";
}


