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
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <getopt.h>

int main( int argc, char** argv ) {

	bool t = false;
	bool s = false;
	char* seed = 0;

	while(true) {
		static struct option long_options[] = {
			{"timer",         no_argument,       0, 't'},
			{"seed",          optional_argument, 0, 's'},
			{"moves",         required_argument, 0, 0},
			{"hero",          required_argument, 0, 0},
			{"enemy",         required_argument, 0, 0},
			{"eatable",       required_argument, 0, 0},
			{"powerup",       required_argument, 0, 0},
			{"delay-hero",    required_argument, 0, 0},
			{"delay-enemy",   required_argument, 0, 0},
			{"delay-eatable", required_argument, 0, 0},
			{"delay-powerup", required_argument, 0, 0},
			{"delay",         required_argument, 0, 0},
			{"render-off",    no_argument,       0, 0}
		};

		int option_index = 0;
		int c = getopt_long (argc, argv, "ts:", long_options, &option_index);

		if (c == -1)
			break;

		switch (c) {
			case 0:
				
				break;
			case 't':
				t = true;
				break;
			case 's':
				s = true;
				seed = optarg;
				break;
		}
	}

	if (s) {
		if (seed) srand(std::stoi(seed,nullptr,0));
		else printf("seed: %ld\n", time(NULL));
	}

	Actor** actors = (Actor**) malloc(10 * sizeof(Actor*));

	int num_actors = 1;
	actors[0] = new SimpleHero(ACTOR_HERO);

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
