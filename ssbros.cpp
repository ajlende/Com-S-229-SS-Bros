/*
 * ssbros.cpp
 *
 *  Created on: Mar 7, 2014
 *	  Author: stolee
 */

#include "GraphMap.hpp"
#include "GameManager.hpp"

#include "Actor.hpp"
#include "OtherActors.hpp"
#include "SimpleHero.hpp"
#include "SmartHero.hpp"
#include "SmartEnemy.hpp"
#include "SmartPowerup.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <getopt.h>
#include <string.h>

int main( int argc, char** argv ) {

	bool t = false;

	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "--timer") == 0 || strcmp(argv[i], "-t") == 0) {
			t = true;
		}
	}

	Actor** actors = (Actor**) malloc(10 * sizeof(Actor*));

	int num_actors = 4;
	actors[0] = new SimpleHero(ACTOR_HERO);
	actors[1] = new SmartHero(ACTOR_HERO);
	actors[2] = new SmartEnemy(ACTOR_ENEMY);
	actors[3] = new SmartPowerup(ACTOR_POWERUP | ACTOR_EATABLE);
	

	GameManager* manager = new GameManager(argc, argv, actors, num_actors);
	manager->addActor(new Actor(ACTOR_HERO));

	clock_t clk;
	if (t) {
		clk = clock();
	}

	manager->play();

	if (t) {
		clk = clock() - clk;
		printf ("It took %ld cycles (%f seconds)\n",clk,((float)clk)/CLOCKS_PER_SEC);
	}

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
