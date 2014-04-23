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

using namespace std;
using namespace util;

SmartEnemy::SmartEnemy(int type) : Actor(type) {
	
}

SmartEnemy::~SmartEnemy() {
	
}

int SmartEnemy::selectNeighbor(GraphMap* map, int x, int y) {
	// TODO
	return 0;
}

Actor* SmartEnemy::duplicate() {
	return new SmartEnemy(this->getType());
}

const char* SmartEnemy::getActorId() {
	return "smartenemy";
}

const char* SmartEmemy::getNetId() {
	return "ajlende";
}



