/*
 * SimpleHero.cpp
 * by Alex Lende
 */

#include "SimpleHero.hpp"
#include <ncurses.h>
#include <stdlib.h>

SimpleHero::SimpleHero( int type ) : Actor(type) {
	// TODO: Initialize member variables
}

SimpleHero::~SimpleHero() {
	// TODO: Free all member variables
}

int SimpleHero::selectNeighbor( GraphMap* map, int x, int y ) {
	// TODO: Select the next move that the SimpleHero is going to make.
	
	int d = map->getNumNeighbors(x, y);

	if ( d <= 1 )
	{
		return 0;
	}

	return d; // TODO: Return the direction that the SimpleHero is going to go.
}

Actor* SimpleHero::duplicate() {
	return new SimpleHero(this->getType());
}

const char* SimpleHero::getActorId() {
	return "simplehero";
}

const char* SimpleHero::getNetId() {
	return "ajlende";
}


