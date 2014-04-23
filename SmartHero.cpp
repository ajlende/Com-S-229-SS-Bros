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
#include <vector>
#include <deque>

using namespace std;
using namespace util;

void SmartHero::getEatables(GraphMap* map, vector<int>* allEatables) {
	
}

SmartHero::SmartHero(int type) : Actor(type) {
	
}

SmartHero::~SmartHero() {
	
}

virtual int SmartHero::selectNeighbor(GraphMap* map, int x, int y) {
	// TODO
	return 0;
}

virtual Actor* SmartHero::duplicate() {
	return new SmartHero(this->getType());
}

virtual const char* SmartHero::getActorId() {
	return "smarthero";
}

virtual const char* SmartHero::getNetId() {
	return "ajlende";
}


