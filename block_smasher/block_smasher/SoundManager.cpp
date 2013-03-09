#include "SDL_mixer.h"

//call in main
void initTheSound()
{
	//All notes
	Mix_Chunk *a = NULL;
	Mix_Chunk *b = NULL;
	Mix_Chunk *c = NULL;
	Mix_Chunk *d = NULL;
	Mix_Chunk *e = NULL;
	Mix_Chunk *f = NULL;
	Mix_Chunk *g = NULL;

	//All chords
	Mix_Chunk *aChord = NULL;
	Mix_Chunk *bChord = NULL;
	Mix_Chunk *cChord = NULL;
	Mix_Chunk *dChord = NULL;
	Mix_Chunk *eChord = NULL;
	Mix_Chunk *fChord = NULL;
	Mix_Chunk *gChord = NULL;

	//Background base track
	Mix_Music *baseTrack = NULL;

	int phaserChannel = -1;

	/* Same setup as before */
	int audio_rate = 22050;
  Uint16 audio_format = AUDIO_S16; 
  int audio_channels = 2;
  int audio_buffers = 4096;

	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
    printf("Unable to open audio!\n");
    exit(1);
  }

	/*
	//load all sound files
	a = Mix_LoadWAV("a.wav");
	b = Mix_LoadWAV("b.wav");
	c = Mix_LoadWAV("c.wav");
	d = Mix_LoadWAV("d.wav");
	e = Mix_LoadWAV("e.wav");
	f = Mix_LoadWAV("f.wav");
	g = Mix_LoadWAV("g.wav");
	*/
};


void startMusic(char *filename)
{

};


void playSound(const char note[2])
{

};


void breakdownSound()
{

};