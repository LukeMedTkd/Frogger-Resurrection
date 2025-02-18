#include "miniaudio.h"
#include "struct.h"

#define N_SOUND 8

#define DEMO 0
#define MANCHE 1
#define JUMP 2
#define FALL 3
#define WON 4
#define LOST 5
#define DEN 6
#define DEAD 7

// Functions Prototypes
void init_ma_engine(Sound *sounds);
void play_sound(ma_sound *sound_to_play);
void stop_sound(ma_sound *sound_to_stop);