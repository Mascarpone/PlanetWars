#include "common.h"

// Returns the current state of the map
struct map_t get_map() {
  
  struct map_t map;

  struct planet* P = malloc(sizeof(struct planet));
  struct fleet* F = malloc(sizeof(struct fleet));

  int i = 0; // planet nb
  int j = 0; // fleet nb

  int cont = 1;

  while(cont) {

    if (fscanf(stdin, "\nP %f %f %d %d %d", &P[i].x, &P[i].y, &P[i].owner, &P[i].numShips, &P[i].growth)) {
     
      P[i].id = i;
      i++;

      P = realloc(P, sizeof(struct planet) * (i + 1));
      if (P == NULL) {
	printf("Error in planet realloc\n");
	break;
      }

    } else if (fscanf(stdin, "\nF %d %d %d %d %d %d", &F[j].owner, &F[j].ships, &F[j].source, &F[j].destination, &F[j].total_turns, &F[j].remaining_turns)) {
    
      j++;

      F = realloc(F, sizeof(struct fleet) * (j + 1));
      if (F == NULL) {
	printf("Error in fleet realloc\n");
	break;
      }

    } else {
      
      char is_go[5];
      fgets(is_go, 4, stdin);
      if (strcmp(is_go, "\ngo")) {
	cont = 0;
      } else {
	printf("Unknown first char of the line in stdin\n");
      }

    }

  }


  map.planet_nb = i;
  map.P = P;
  map.fleet_nb = j;
  map.F = F;

  return map;
  
}


// Frees the memory allocated by get_map()
void remove_data(struct map_t *map) {

  free(map -> P), map -> P = NULL;
  map -> planet_nb = 0;
  free(map -> F), map -> F = NULL;
  map -> fleet_nb = 0;

}


//Returns the planets of a player
struct p_planets find_planets(const struct map_t* map, int owner) {

  struct p_planets p_planets;
  struct planet* owned_planets = malloc(sizeof(struct planet));
  int n = 0;

  for (int i = 0; i < map -> planet_nb; i++) {
    
    if (map -> P[i].owner == owner) {
      
      owned_planets[n] = map -> P[i];
      n++;

      owned_planets = realloc(owned_planets, sizeof(struct planet) * (n + 1));
      if (owned_planets == NULL) {
	printf("Error in owned_planets realloc\n");
	break;
      }
    
    }

  }

  p_planets.owned_planets = owned_planets;
  p_planets.n = n;

  return p_planets;

}

//Returns the temporal distance between 2 planets
int distance(struct planet P1, struct planet P2) {

  return 1+floor(sqrt(pow(P1.y - P2.y, 2) + pow(P1.x - P2.x, 2)));

}

//Returns the number of ships sent by a player to a planet
int nb_ships_sent(const struct map_t* map,int owner,int id){
  int a=0;
  for (int i=0; i < map->fleet_nb;i++)
    {
      if (map->F[i].destination == id && map->F[i].owner == owner)
	{
	  a+=map->F[i].ships;
	}
    
    }
  return a; 
  }


//Returns the profitability of a planet in relation with an allied planet
int profitability(struct planet planet_src , struct planet planet_dest){
  if(planet_dest.owner == 0)
    return (planet_src.numShips) -(planet_dest.numShips+1) + 25*(planet_src.growth)+(25-distance(planet_src,planet_dest))*(planet_dest.growth) ;
  else if(planet_dest.owner == 2)
    return (planet_src.numShips) -(planet_dest.numShips+distance(planet_src,planet_dest)*(planet_dest.growth)) + 25*(planet_src.growth)+(25-distance(planet_src,planet_dest))*(planet_dest.growth) ;
}


//returns the most profitable planet
struct planet most_profitable_planet(const struct map_t* map, struct p_planets others_planets, struct planet planet_src ){

  int profit_tmp;
  int profit = profitability (others_planets.owned_planets[0],planet_src);
  struct planet Pdef;
  Pdef=others_planets.owned_planets[0];
  for(int j=1 ; j < others_planets.n ; j++){
    profit_tmp = profitability (planet_src , others_planets.owned_planets[j]);
   
    if( profit_tmp > profit && nb_ships_sent(map,planet_src.owner, others_planets.owned_planets[j].id) == 0 ){
      profit=profit_tmp;
      Pdef=others_planets.owned_planets[j];
      }
  }   
  return Pdef;
}



// Send the floats
void send(struct planet src , struct planet dest){

  int x = dest.growth *(distance(src,dest));
  switch(dest.owner){

  case 0:
    printf("%d %d %d\n", src.id,dest.id,dest.numShips + 1);
    break;
  case 2:
    printf("%d %d %d\n", src.id,dest.id,dest.numShips + x + 1);
    break;
  }
 
}



// Returns the total number of floats of a player
int nb_total_ship(const struct map_t* map,int owner){
  int cpt=0;
  for(int i=0; i < map->planet_nb; i++){
    if(map->P[i].owner == owner)
      cpt+=map->P[i].numShips;
    cpt+=nb_ships_sent(map,owner,map->P[i].id);
  }
  return cpt;
}




// Returns the nearest planet from another planet
struct planet nearest_planet(struct p_planets P, struct planet src){
  struct planet dest;
  
  int dist_tmp=50;
  for (int i=0 ; i < P.n ; i++){
    int dist = distance(P.owned_planets[i],src);
    if( dist <= dist_tmp && P.owned_planets[i].id != src.id && P.owned_planets[i].growth > 1 ){
      dist_tmp = dist;
      dest = P.owned_planets[i]; 
    }
  }
 
  return dest;

}


// Returns the temporal distance to the nearest float which is coming to a planet
int nearest_attack(const struct map_t* map, struct planet src ){
  
  int a=50;
  for (int i=0; i < map->fleet_nb ; i++)
    {
      if (map->F[i].destination == src.id && map->F[i].owner != src.owner && map->F[i].remaining_turns < a  )
	{
	  a=map->F[i].remaining_turns;
	}
    }
  if(a==50)
    a=0;
  return a; 
}
