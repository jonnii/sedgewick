#include <stdlib.h>
#include <stdio.h>

#define NUM_DICE 2
#define SIDES 6

void print_dist(float cnt, float* dist)
{
  for(int i = 0 ; i < cnt; ++i){
    printf("%f\n", dist[i]);
  }
}

int random_roll()
{
  int total = 0;
  for(int i = 0 ; i < NUM_DICE; ++i){
      total += rand() % SIDES + 1;
  }
  return total;
}

int main(int argc, char *argv[])
{
  if(argc < 1) {
    printf("Usage: experiment_1_1_35 <numsimulations>\n");
    return 1;
  }

  int range = NUM_DICE * SIDES + 1;
  float *dist = calloc(sizeof(float), range);

  printf("populating distribution\n");
  for(int i = 1; i <= SIDES; ++i){
    for(int j = 1 ; j <= SIDES; ++j){
      dist[i+j] += 1.0f;
    }
  }

  for(int i = 1; i < range; ++i){
    dist[i] /= 36.0f;
  }

  print_dist(range, dist);

  int num_simulations = atoi(argv[1]);
  printf("running simulations: %d\n", num_simulations);

  float *simulation = calloc(sizeof(float), range);
  for(int i = 0 ; i < num_simulations ; ++i) {
    int random = random_roll();
    simulation[random] += 1;
  }

  for(int i = 0 ; i < range ; ++i){
    simulation[i] /= num_simulations;
  }

  print_dist(range, simulation);

  free(dist);
  free(simulation);
  
  return 0; 
}