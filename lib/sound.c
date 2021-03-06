#include <sparrow3d.h>
#include <string.h>
#include "sound.h"

int soundCount = 0;
spSound* sounds[10] = { NULL };

// add a sound to the global sounds array
void
addSound ( char soundpath[512] )
{
	sounds[soundCount] = spSoundLoad(soundpath);
	soundCount++;
}

// cleanup all sounds
void
cleanupSounds ( void )
{
	for ( int i = 0; i < soundCount; i++ ) {
		spSoundDelete( sounds[i] );
	}
}

