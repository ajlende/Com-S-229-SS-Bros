/*
 * ssbros.cpp
 *
 *  Created on: Mar 7, 2014
 *      Author: stolee
 */

#include "GraphMap.hpp"
#include "GameManager.hpp"
#include "Actor.hpp"
#include "OtherActors.hpp"
#include "SimpleHero.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main( int argc, char** argv )
{
	Actor** actors = (Actor**) malloc(10 * sizeof(Actor*));

	int num_actors = 1;
	actors[0] = new SimpleHero(ACTOR_HERO);

	GameManager* manager = new GameManager(argc, argv, actors, num_actors);
	manager->addActor(new Actor(ACTOR_HERO));


	// TODO: Remove clock
	clock_t t;
	t = clock();
	manager->play();
	t = clock() - t;
	printf ("It took %d cycles (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);


	delete manager;
	manager = 0;

	for ( int i = 0; i < num_actors; i++ )
	{
		delete actors[i];
	}
	free(actors);
	actors = 0;
	return 0;
}
