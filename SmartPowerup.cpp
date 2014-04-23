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

SmartHero::SmartPowerup(int type) : Actor(type) {
	
}

SmartHero::~SmartPowerup() {
	
}

int SmartPowerup::selectNeighbor(GraphMap* map, int x, int y) {
	// TODO
	return 0;
}

Actor* SmartPowerup::duplicate() {
	return new SmartPowerup(this->getType());
}

const char* SmartPowerup::getActorId() {
	return "smartpowerup";
}

const char* SmartEmemy::getNetId() {
	return "ajlende";
}

