#include "common.h"



void chaine(const struct map_t* map) {


  // ************* Initialization  ******************// 

  struct p_planets my_planets=find_planets( map , 1 );
  struct p_planets neutral_planets=find_planets( map , 0 );
  struct p_planets enemy_planets=find_planets( map , 2 );

  struct planet Pdef;
  struct planet Pdef2;
  struct planet nearest; // nearest planet
  int my_total_ships=nb_total_ship( map , 1 ); // my total number of ships
  int enemy_total_ships=nb_total_ship( map , 2 );



  
    // ***************** Attack ******************// 
  
  // activation conditions for the attack mode
  if( my_total_ships > 7*enemy_total_ships/3 && enemy_planets.n != 0 || ( my_total_ships >= enemy_total_ships && enemy_planets.n != 0 && neutral_planets.n == 0 ) ){

    for(int i=0; i < my_planets.n; i++){

      int attacked=nb_ships_sent( map,2,my_planets.owned_planets[i].id );
      for(int k=0; k < enemy_planets.n ; k++){

	int x = enemy_planets.owned_planets[k].growth *(distance(my_planets.owned_planets[i],enemy_planets.owned_planets[k]));
	if ( my_planets.owned_planets[i].numShips > (enemy_planets.n*my_planets.owned_planets[i].growth+attacked+1) &&  nb_ships_sent(map,1,enemy_planets.owned_planets[k].id) < (enemy_planets.owned_planets[i].numShips + x) ){
	  printf("%d %d %d\n", my_planets.owned_planets[i].id , enemy_planets.owned_planets[k].id , my_planets.owned_planets[i].growth );
	}

      }

    }
    return;
    }
  

  // ***************** Defense *******************//
  
  for(int i=0 ; i < my_planets.n ; i++){ 

    int attacked = nb_ships_sent(map,2,my_planets.owned_planets[i].id);
    int nearest_distance = nearest_attack( map, my_planets.owned_planets[i]); // distance to the nearest attack
    int growth = nearest_distance * my_planets.owned_planets[i].growth; 
  
    //search if one of my planets is attacked
    if( (my_planets.owned_planets[i].numShips + growth) < attacked && my_planets.owned_planets[i].growth>1 && nb_ships_sent(map,1,my_planets.owned_planets[i].id) == 0 ){
      nearest=nearest_planet(my_planets,my_planets.owned_planets[i]);


      if(distance(nearest,my_planets.owned_planets[i]) <= nearest_distance){ // distinguish cases for the distance
	if( nearest.numShips > (attacked-my_planets.owned_planets[i].numShips-growth) && nb_ships_sent(map,2,nearest.id)<(attacked-my_planets.owned_planets[i].numShips-growth) ){
	  printf("%d %d %d\n", nearest.id , my_planets.owned_planets[i].id , attacked-my_planets.owned_planets[i].numShips-growth + 1 );
	  return;
	}
      }
      else if( distance(nearest,my_planets.owned_planets[i]) > nearest_distance){ // distinguish cases for the distance
	int a = distance(nearest,my_planets.owned_planets[i]) - nearest_distance;
	if(nearest.numShips > (attacked-my_planets.owned_planets[i].numShips-growth + my_planets.owned_planets[i].growth * a  ) && nb_ships_sent(map,2,nearest.id)<(attacked-my_planets.owned_planets[i].numShips-growth+my_planets.owned_planets[i].growth * a) ){
	  printf("%d %d %d\n", nearest.id , my_planets.owned_planets[i].id , attacked-my_planets.owned_planets[i].numShips-growth + my_planets.owned_planets[i].growth * a + 1 );
	  return;
	}
      }
    }
  }    
  
  
  
  // ****************** Expansion ******************//

  if( neutral_planets.n != 0 && enemy_planets.n != 0){
  
    for(int i=0; i < my_planets.n; i++){
  
      
      Pdef=most_profitable_planet(map,neutral_planets,my_planets.owned_planets[i]);
      int profit_1=profitability(my_planets.owned_planets[i],Pdef);

      // look for the most profitable enemy planet
      Pdef2=most_profitable_planet(map,enemy_planets,my_planets.owned_planets[i]);
      int profit_2=profitability(my_planets.owned_planets[i],Pdef2);
      
      // look for the most profitable neutral planet
      if(profit_1 > profit_2){
	int attacked=nb_ships_sent(map,2,my_planets.owned_planets[i].id);
	if(my_planets.owned_planets[i].numShips > (Pdef.numShips+attacked+5) && nb_ships_sent(map,1,Pdef.id)==0  ) {
	  send(my_planets.owned_planets[i],Pdef);
	  break;
	}
      }      
      if(profit_1 <= profit_2){
	int attacked=nb_ships_sent(map,2,my_planets.owned_planets[i].id);
	int x = Pdef2.growth *(distance(my_planets.owned_planets[i],Pdef2));
	if (my_planets.owned_planets[i].numShips > (Pdef2.numShips+5+x+attacked) && nb_ships_sent(map,1,Pdef2.id)==0  ){	
	  send(my_planets.owned_planets[i],Pdef2);
	  break;
	}
      }
    }
  }
  
  else if(neutral_planets.n == 0 && enemy_planets.n != 0){
    for(int i=0; i < my_planets.n; i++){
      Pdef=most_profitable_planet(map,enemy_planets,my_planets.owned_planets[i]);
      int x = Pdef.growth *(distance(my_planets.owned_planets[i],Pdef));
      int attacked=nb_ships_sent(map,2,my_planets.owned_planets[i].id);
      if(my_planets.owned_planets[i].numShips > (Pdef.numShips +attacked+ x + 5) && nb_ships_sent(map,1,Pdef.id) == 0 ) {
	send(my_planets.owned_planets[i],Pdef);
	break;
      }
          
    }
  }

}



   // **************** Main *****************//


int main() {
  
  struct map_t map;
 
  while (1) {
    map = get_map();
    chaine(&map);
    

    fprintf(stdout, "go\n");
    fflush(stdout);
   
    remove_data(&map);
 
  }

  return EXIT_SUCCESS;
}
