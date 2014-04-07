/*
 * SimpleHero.hpp
 * by Alex Lende
 */

#ifndef SIMPLEHERO_HPP_
#define SIMPLEHERO_HPP_

#include "Actor.hpp"
#include "GraphMap.hpp"
#include <vector>

/**
 * The SimpleHero follows a simple greedy type strategy to collect all of the eatables.
 */
class SimpleHero : public Actor
{
	protected:
		/**
		 * Finds the shortest path from vertex start to vertex end in the map.
		 */
		std::vector<int>* SimpleHero::findPath(GraphMap* map, int start, int end);

		/**
		 * Gets all of the eatables reamining on the map.
		 */
		std::vector<int>* SimpleHero::getEatables(GraphMap* map);
		
	public:
		SimpleHero(int type);
		virtual ~SimpleHero();
		virtual int selectNeighbor(GraphMap* map, int x, int y);
		virtual Actor* duplicate();
		virtual const char* getActorId();
		virtual const char* getNetId();
};

#endif /* SIMPLEHERO_HPP_ */
