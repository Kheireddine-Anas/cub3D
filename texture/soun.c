#include <stdio.h>
#include <stdlib.h>
// #include <AL/al.h>
// #include <AL/alc.h>
#include <unistd.h>

void play_sound(const char* filename) {
    ALuint buffer;
    ALuint source;
    ALCdevice *device;
    ALCcontext *context;

    // Ouvrir un dispositif audio
    device = alcOpenDevice(NULL);
    if (!device) {
        fprintf(stderr, "Could not open audio device\n");
        return;
    }

    // Créer un contexte
    context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);

    // Générer un buffer et une source
    alGenBuffers(1, &buffer);
    alGenSources(1, &source);

    // Charger le fichier WAV dans le buffer
    // (Utilisez une fonction pour lire le fichier WAV ici)

    // Lire le son
    alSourcei(source, AL_BUFFER, buffer);
    alSourcePlay(source);

    // Attendre que le son finisse
    ALint state;
    do {
        alGetSourcei(source, AL_SOURCE_STATE, &state);
        usleep(100000); // Attendre un peu
    } while (state == AL_PLAYING);

    // Libérer les ressources
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);
}
int main ()
{
	play_sound("textures/music_gunshot.mp3");
}