#ifndef _ACTORUTIL_H_
#define _ACTORUTIL_H_

#include "GraphMap.hpp"
#include <vector>

using namespace std;

namespace util {

	/**
	 * Finds the shortest path from vertex start to vertex end in the map.
	 * Returns true if a path was found and false if no path was found.
	 */
	bool findPath(GraphMap* map, int start, int end, vector<int>* V);

	/**
	 * Gets all actors with the specified y_type attributes and without the n_type attributes.
	 */
	void getActors(GraphMap* map, int y_type, int n_type, vector<int>* allActors);

}

#endif
