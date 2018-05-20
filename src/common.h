#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


// ----- STRUCTS ----- //

struct planet {

  int id;
  float x;
  float y;
  int owner;
  int numShips;
  int growth;
  
};

struct fleet {
  
  int owner;
  int ships;
  int source;
  int destination;
  int total_turns;
  int remaining_turns;

};

struct map_t {
  
  int planet_nb;
  struct planet* P;
  int fleet_nb;
  struct fleet* F;

};

struct p_planets {

  int n;
  struct planet* owned_planets; // contains the owned planets of the player

};

struct point {
  float x;
  float y;
};


// ------------------- //



// ---- FUNCTIONS ---- //

// Returns the current state of the map
struct map_t get_map();

// Frees the memory allocated by get_map()
void remove_data(struct map_t*);

//Returns the planets of a player
struct p_planets find_planets(const struct map_t* map, int owner);

//Returns the temporal distance between 2 planets
int distance(struct planet P1, struct planet P2);

//Returns the number of ships sent by a player to a planet
int nb_ships_sent(const struct map_t* map,int owner,int id);

//Returns the profitability of a planet in relation with an allied planet
int profitability(struct planet planet_src , struct planet planet_dest);

//returns the most profitable planet
struct planet most_profitable_planet(const struct map_t* map, struct p_planets others_planets, struct planet planet_src );

// Send the floats
void send(struct planet src , struct planet dest);

// Returns the total number of floats of a player
int nb_total_ship(const struct map_t* map,int owner);

// Returns the nearest planet from another planet
struct planet nearest_planet(struct p_planets P, struct planet src);

// Returns the temporal distance to the nearest float which is coming to a planet
int nearest_attack(const struct map_t* map, struct planet src );

// ------------------- //
