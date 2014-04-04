/*
 * SimpleHero.hpp
 * by Alex Lende
 */

#ifndef SIMPLEHERO_HPP_
#define SIMPLEHERO_HPP_

#include "Actor.hpp"
#include "GraphMap.hpp"

/**
 * The SimpleHero follows a simple greedy type strategy to collect all of the eatables.
 */
class SimpleHero : public Actor
{
	protected:
		/**
		 * Does a Breadth First Search starting at index s
		 */
		int* BFS(GraphMap* map, int x, int y, int a, int b, int& first_neighbor);
		int getNumEatables();
		
		
	public:
		SimpleHero(int type);
		virtual ~SimpleHero();
		virtual int selectNeighbor(GraphMap* map, int x, int y);
		virtual Actor* duplicate();
		virtual const char* getActorId();
		virtual const char* getNetId();
};

#endif /* SIMPLEHERO_HPP_ */
