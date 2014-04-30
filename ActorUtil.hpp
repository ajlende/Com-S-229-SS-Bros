/*
 * ActorUtil.hpp
 * by Alex Lende
 */

#ifndef _ACTORUTIL_HPP_
#define _ACTORUTIL_HPP_

#include "GraphMap.hpp"
#include <vector>

using namespace std;

namespace util {

	/**
	 * Finds the shortest path from vertex start to vertex end in the map.
	 * Returns true if a path was found and false if no path was found.
	 */
	bool findPath(GraphMap* map, int start, int end, vector<int>* V);
	bool findPath(GraphMap* map, int start, int end, vector<int>* V, int avoidtype);
	bool searchRadius(GraphMap* map, int start, int end, int radius, int searchtype);

	/**
	 * Gets all actors with the specified y_type attributes and without the n_type attributes.
	 */
	void getActors(GraphMap* map, int y_type, int n_type, vector<int>* allActors);

}

#endif /* ACTORUTIL_HPP_ */
