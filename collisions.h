#include "entity.h"
#include "struct.h"

#define CROCODILE_TAIL_OFFSET 0
#define CROCODILE_HEAD_OFFSET 0


// Functions Prototypes
void set_outcome(Game_var *gameVar, bool *manche_ended);
void is_time_up(WINDOW *game, Character *Entities, Character * Bullets,  Game_var *gameVar, bool *manche_ended);
void dens_collision(Character *Entities, Game_var *gameVar, bool *manche_ended);
void frog_bullets_collision(Character *Entities, Character *Bullets, bool *manche_ended);
void frog_on_crocodile_collision(Character *Entities, Game_var *gameVar, bool *manche_ended);