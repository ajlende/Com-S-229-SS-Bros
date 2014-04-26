/*
 * SmartPowerup.cpp
 * by Alex Lende
 *
 * This powerup will try to make the enemies win by avoiding the hero and “hiding” near the enemies.
 * 
 * Grading Details
 *   • There will be no "traps" (if you can reach an actor, then that actor can reach you.)
 *   • There will be heroes, enemies, and powerups available. (enemies will probably pursue heroes)
 *   • Heroes will not move faster than powerups.
 *   • 100% for the portion of powerups that survive.
 *   • 50% for the portion of heroes that die.
 *   • [For a 10pt test case, 10 pts for surviving powerups, and 5 pts for leading heroes to their death.]
 */

#include "Actor.hpp"
#include "SmartPowerup.hpp"
#include "GraphMap.hpp"
#include "ActorUtil.hpp"

using namespace std;
using namespace util;

SmartPowerup::SmartPowerup(int type) : Actor(type) {
	
}

SmartPowerup::~SmartPowerup() {
	
}

void SmartPowerup::getEnemies(GraphMap* map, vector<int>* allEnemies) {
	getActors(map, ACTOR_ENEMY, ACTOR_DEAD, allEnemies);
}

void SmartPowerup::getHeroes(GraphMap* map, vector<int>* allHeroes) {
	getActors(map, ACTOR_HERO, ACTOR_DEAD, allHeroes);
}

int SmartPowerup::selectNeighbor(GraphMap* map, int x, int y) {
	int d = map->getNumNeighbors(x, y);

	if ( d <= 1 ) return 0;

	int start = map->getVertex(x, y);
	int closest = 0;
	unsigned int min_distance = UINT_MAX;

	auto enemies = new vector<int>();
	this->getEnemies(map, enemies);

	// auto heroes = new vector<int>();
	// this->getHeroes(map, heroes);
	
	auto path = new vector<int>();
	
	// Look through all the enemies for the closest one
	for (int& e : *enemies) {
		if (findPath(map, start, e, path)) {

			int path_size = path->size();
	
			if (!path->empty() && (path_size < min_distance)) {
				min_distance = path_size;
				closest = path->back();
			}
	
			path->clear();
		}
	}
	
	delete path;
	
	delete enemies;

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

Actor* SmartPowerup::duplicate() {
	return new SmartPowerup(this->getType());
}

const char* SmartPowerup::getActorId() {
	return "smartpowerup";
}

const char* SmartPowerup::getNetId() {
	return "ajlende";
}

