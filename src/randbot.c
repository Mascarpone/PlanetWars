#include "common.h"

#include <time.h>
#define MAX_SHOT 10

void rand_shot(const struct map_t* map) {

  struct p_planets o_planets;

  // Find the not owned planets
  struct p_planets e_planets = find_planets(map, 2);
  struct p_planets n_planets = find_planets(map, 0);

  o_planets.n = (e_planets.n) + (n_planets.n);
  struct planet notowned_planets[o_planets.n];

  for (int i = 0; i < e_planets.n; i++) {
    notowned_planets[i] = e_planets.owned_planets[i];
  }
  for (int i = 0; i < n_planets.n; i++) {
    notowned_planets[i + e_planets.n] = n_planets.owned_planets[i];
  }

  o_planets.owned_planets = notowned_planets;

  
  int r;
  if (o_planets.n) {

    // Choose a random index
    r = rand() % (o_planets.n);
    int id = o_planets.owned_planets[r].id;
  
    // Send random fleets to this planet from all your planets
    struct p_planets m_planets = find_planets(map, 1);
    int max = (m_planets.n < MAX_SHOT) ? rand() % (m_planets.n + 1) : rand() % (MAX_SHOT + 1);
    for (int i = 0; i < max; i++) {
      r = rand() % (m_planets.owned_planets[i].numShips + 1);
      printf("%d %d %d\n", m_planets.owned_planets[i].id, id, r);
    }

  }
  
}


int main() {

  srand(time(NULL));
  
  struct map_t map;

  while (1) {
   
    map = get_map();
    rand_shot(&map);

    fprintf(stdout, "go\n");
    fflush(stdout);
   
    remove_data(&map);
 
  }

  return EXIT_SUCCESS;
}
