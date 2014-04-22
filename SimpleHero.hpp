/*
 * SimpleHero.hpp
 * by Alex Lende
 */

#ifndef SIMPLEHERO_HPP_
#define SIMPLEHERO_HPP_

#include "Actor.hpp"
#include "GraphMap.hpp"
#include <vector>
#include <deque>

using namespace std;

/**
 * The SimpleHero follows a simple greedy type strategy to collect all of the eatables, however, it also checks to make sure that all other eatables are reachable if it goes to it.
 */
class SimpleHero : public Actor
{
	protected:
		deque<int>* goal;
		vector<int>* food;
		
		/**
		 * Gets all of the eatables reamining on the map.
		 */
		void getEatables(GraphMap* map, vector<int>* allEatables);
		
	public:
		SimpleHero(int type);
		virtual ~SimpleHero();
		virtual int selectNeighbor(GraphMap* map, int x, int y);
		virtual Actor* duplicate();
		virtual const char* getActorId();
		virtual const char* getNetId();
};

#endif /* SIMPLEHERO_HPP_ */
