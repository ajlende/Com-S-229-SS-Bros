/*
 * SmartHero.hpp
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

#ifndef SMARTHERO_HPP_
#define SMARTHERO_HPP_

#include "Actor.hpp"
#include "GraphMap.hpp"
#include <vector>
#include <deque>

using namespace std;

class SmartHero : public Actor {

	protected:		
		/**
		 * Gets all of the eatables reamining on the map.
		 */
		void getEatables(GraphMap* map, vector<int>* allEatables);
		
	public:
		SmartHero(int type);
		virtual ~SmartHero();
		virtual int selectNeighbor(GraphMap* map, int x, int y);
		virtual Actor* duplicate();
		virtual const char* getActorId();
		virtual const char* getNetId();
};

#endif /* SMARTHERO_HPP_ */
