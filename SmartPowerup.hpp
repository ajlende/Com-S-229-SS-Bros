/*
 * SmartPowerup.hpp
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

#ifndef SMARTPOWERUP_HPP_
#define SMARTPOWERUP_HPP_

#include "Actor.hpp"
#include "GraphMap.hpp"

/**
 * 
 */
class SmartPowerup : public Actor
{
	protected:
		// TODO: Member variables		
	public:
		SmartPowerup(int type);
		virtual ~SmartPowerup();
		virtual int selectNeighbor(GraphMap* map, int x, int y);
		virtual Actor* duplicate();
		virtual const char* getActorId();
		virtual const char* getNetId();
};

#endif /* SMARTPOWERUP_HPP_ */


