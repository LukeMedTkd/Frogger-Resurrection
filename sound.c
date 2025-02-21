#ifndef SOUND_H
#define SOUND_H
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include "sound.h"
#endif

Sound sounds[N_SOUND];
char *audio_files[N_SOUND] = {"sound/demo_music.wav", "sound/manche.wav", "sound/frog_jump.wav", "sound/fall_water.wav", "sound/won.wav", "sound/lost.wav", "sound/den_close.wav", "sound/dead.wav"};
ma_engine engine;


void init_ma_engine(Sound *sounds) {
    ma_engine_config engineConfig = ma_engine_config_init();
    engineConfig.sampleRate = 44100;  // Sample rate elevato per ridurre la latenza
    engineConfig.periodSizeInFrames = 64; // Minore è il valore, minore è la latenza

    // Initialize the engine
    if (ma_engine_init(&engineConfig, &engine) != MA_SUCCESS) {
        printf("Errore nell'inizializzazione del motore audio\n");
        return;
    }

    // Set Sound structs
    for (int i = 0; i < N_SOUND; i++) {
        sounds[i].filename = audio_files[i];
    }

    // Upload all sounds/musics
    for (int i = 0; i < N_SOUND; i++) {
        if (ma_sound_init_from_file(&engine, sounds[i].filename, 0, NULL, NULL, &sounds[i].sound) != MA_SUCCESS) {
            printf("Errore nel caricamento del file audio: %s\n", sounds[i].filename);
            ma_engine_uninit(&engine);
            return;
        }
    }
}



// Play the sound in input
void play_sound(ma_sound *sound_to_play){
    if(ma_sound_seek_to_pcm_frame(sound_to_play, 0) != MA_SUCCESS) return;
    if(ma_sound_start(sound_to_play) != MA_SUCCESS) return;
}

// Stop the sound in input
void stop_sound(ma_sound *sound_to_stop){
    if(ma_sound_stop(sound_to_stop)!= MA_SUCCESS) return;
}