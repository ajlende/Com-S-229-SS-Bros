/*
 * SmartEnemy.cpp
 * by Alex Lende
 * 
 * This enemy will have a coordinated strategy that will guarantee the enemies win (by eating the hero, or by making time run out).
 * 
 * Grading Details
 *   • There will be no "traps" (if you can reach an actor, then that actor can reach you.)
 *   • There will be heroes, enemies, and powerups available.
 *   • Heroes will not move much faster than enemies.
 *   • 50% for the portion of heroes that die.
 *   • 50% for the portion of powerups that survive.
 *   • 50% for the portion of eatables that survive.
 *   • [For a 10pt test case, 5pts for each of the three conditions.]
 */

#include "Actor.hpp"
#include "SmartEnemy.hpp"
#include "GraphMap.hpp"
#include "ActorUtil.hpp"
#include <climits>
#include <vector>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;
using namespace util;

// Initializing the random generator and uniform distributors
unsigned seed = system_clock::now().time_since_epoch().count();
default_random_engine SmartEnemy::generator(seed);
uniform_int_distribution<int> SmartEnemy::personalityDistribution(0,2);
uniform_int_distribution<int> SmartEnemy::generalDistribution(0,99);


SmartEnemy::SmartEnemy(int type) : Actor(type) {
	this->personality = 0;
}

SmartEnemy::SmartEnemy(int type, int personality) : Actor(type) {
	this->personality = personality;
}

SmartEnemy::~SmartEnemy() {
	
}

int SmartEnemy::getPersonality() {
	return this->personality;
}

void SmartEnemy::getHeroes(GraphMap* map, vector<int>* allEatables) {
	getActors(map, ACTOR_HERO, ACTOR_DEAD, allEatables);
}

int SmartEnemy::selectNeighbor(GraphMap* map, int x, int y) {
	switch ( this->personality ) {
	case 1:
		printf("Selecting for pursue\n");
		return this->pursue(map, x, y);
	case 2:
		printf("Selecting for lazyPursue\n");
		return this->lazyPursue(map, x, y, 1);
	default:
		printf("Selecting default\n");
		return 0;
	}
}

int SmartEnemy::pursue(GraphMap* map, int x, int y) {
	int d = map->getNumNeighbors(x, y);

	if ( d <= 1 ) return 0;

	int start = map->getVertex(x, y);
	int closest = 0;
	unsigned int min_distance = UINT_MAX;

	auto heroes = new vector<int>();
	this->getHeroes(map, heroes);
	
	auto path = new vector<int>();
	
	// Look through all the heroes for the closest one
	for (int& h : *heroes) {
		if (findPath(map, start, h, path)) {

			int path_size = path->size();
	
			if (!path->empty() && (path_size < min_distance)) {
				min_distance = path_size;
				closest = path->back();
			}
	
			path->clear();
		}
	}
	
	delete path;

	delete heroes;

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

int SmartEnemy::lazyPursue(GraphMap* map, int x, int y, int lazyness) {
	if (SmartEnemy::generalDistribution(SmartEnemy::generator) < lazyness) {
		int d = map->getNumNeighbors(x, y);
		uniform_int_distribution<int> distribution(0,d);

		return distribution(SmartEnemy::generator);
	} else {
		return this->pursue(map, x, y);
	}
}

Actor* SmartEnemy::duplicate() {
	// return new SmartEnemy(this->getType(), SmartEnemy::personalityDistribution(SmartEnemy::generator));
	return new SmartEnemy(this->getType(), 1);
}

const char* SmartEnemy::getActorId() {
	return "smartenemy";
}

const char* SmartEnemy::getNetId() {
	return "ajlende";
}



