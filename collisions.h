#include "entity.h"
#include "struct.h"

#define CROCODILE_TAIL_OFFSET 0
#define CROCODILE_HEAD_OFFSET 0


// Functions Prototypes
void set_outcome(Game_var *gameVar, bool *manche_ended);
void is_time_up(WINDOW *game, Character *Entities, Character * Bullets,  Game_var *gameVar, bool *manche_ended);
void dens_collision(Character *Entities, Game_var *gameVar, bool *manche_ended);
void generate_bullets(int *fds, Character *Entities, Character *Bullets, Game_var *gameVar, Msg *msg, int *random_shot, void (* crocodile_bullet_process));
void bullets_collision(Character *Entities, Character *Bullets, bool *manche_ended);
void deactive_bullets_out_game(Character *Bullets, int *current_bullet_id,  Msg *msg);
void frog_killed(Character *Entities, Character *Bullets, Game_var *gameVar, bool *manche_ended, int *current_bullet_id);
void bullets_neutralization(Character *Entities, Character *Bullets, Msg *msg, int *current_bullet_id);
void frog_on_crocodile_collision(Character *Entities, Game_var *gameVar, bool *manche_ended);