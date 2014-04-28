/*
 * SmartEnemy.hpp
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

#ifndef SMARTENEMY_HPP_
#define SMARTENEMY_HPP_

#include "Actor.hpp"
#include "GraphMap.hpp"
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;

class SmartEnemy : public Actor {
	private:
		int personality;
		static default_random_engine generator;
		static uniform_int_distribution<int> personalityDistribution;
		static uniform_int_distribution<int> generalDistribution;		

	protected:
		// TODO: Member variables
		void getHeroes(GraphMap* map, vector<int>* allHeroes);
		int getPersonality();
		int pursue(GraphMap* map, int x, int y);
		int lazyPursue(GraphMap* map, int x, int y, int lazyness);

	public:
		SmartEnemy(int type);
		SmartEnemy(int type, int personality);
		virtual ~SmartEnemy();
		virtual int selectNeighbor(GraphMap* map, int x, int y);
		virtual Actor* duplicate();
		virtual const char* getActorId();
		virtual const char* getNetId();
};

#endif /* SMARTENEMY_HPP_ */

