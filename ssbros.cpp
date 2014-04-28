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

void helpmsg();

int main( int argc, char** argv ) {

	bool t = false;

	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "--timer") == 0 || strcmp(argv[i], "-t") == 0) {
			t = true;
		} else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
			helpmsg();
			return 0;
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

void helpmsg() {
	printf(
		"Usage: ssbros [MAP] [OPTION]...\n"
		"\n"
		"Options:\n"
		"\t--moves #         How many turns to allow before quitting.\n"
		"\t--[TYPE] [ID]     Use the actor with the given ID for the given TYPE.\n"
		"\t--delay-[TYPE] #  Let actors of the given TYPE only make moves every # turns.\n"
		"\t--delay #         Make every move last # miliseconds.\n"
		"\t--render-off      Do not render the map, or make timed delays. Useful if you want to use printf for debugging.\n"
		"\t--goal [TYPE]     Sets grading criteria for all types except eatable (Used in part B)."
		"\t--bestof #        Runs the map # times and take the maximum score.\n"
		"\t--window #        Gives a hero # moves to eat enemies after eating a powerup.\n"
		"\n"
		"Types:\n"
		"\thero              Represented as the \x1b[33;1;40m C \x1b[0m in game.\n"
		"\tenemy             Reptesented as the \x1b[31;1;40m E \x1b[0m in game.\n"
		"\teatable           Represented as the \x1b[31;1;40m @ \x1b[0m in game.\n"
		"\tpowerup           Represented as the \x1b[37;1;40m * \x1b[0m in game.\n"
		"\n"
		"IDs:\n"
		"\tsimplehero        My Simple Hero.\n"
		"\tsmarthero         My Smart Hero.\n"
		"\tsmartenemy        My Smart Enemy.\n"
		"\tsmartpowerup      My Smart Powerup.\n"
		"\tactor             Stationary actor.\n"
		"\trandom            Moves randomly about the map avoiding recent places.\n"
		"\tkeyboard          Uses keyboard input for control.\n"
		"\tpursuer           Goes after the closest hero.\n"
		"\tenemypursuer      Goes after the closest enemy.\n"
		"\theropursuer       Goes after the closest hero.\n"
		"\teatablepursuer    Goes after the closest eatable (or powerup).\n"
		"\tpoweruppursuer    Goes after the closest powerup.\n"
		"\tenemyavoider      Tries to go as far as possible from all enemies.\n"
		"\theroavoider       Tries to go as far as possible from all heroes.\n"
		"\tlazypursuer       25\% of the time moves randomly, otherwise chases heroes.\n"
		"\teatableenemypa    Pursues eatables while avoiding enemies.\n"
		"\tpowerupenemypa    Pursues powerups while avoiding enemies.\n"
		"\tenemyheropa       Pursues enemies while avoiding heroes.\n"
	);

}
