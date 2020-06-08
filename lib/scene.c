#include <sparrow3d.h>
#include <string.h>
#include "scene.h"

// ============================================================================
// INIT
// ============================================================================
void
initScene ( struct eScene* scene, char background[512], struct eActor* actor )
{
	scene->surface = NULL;
	scene->background = NULL;
	strcpy(scene->backgroundPath, background);
	scene->actor = actor;
}

void
drawScene ( struct eScene* scene )
{
	SDL_Surface* old_target = spGetRenderTarget();
	spSelectRenderTarget( scene->surface );

	spBlitSurface( scene->surface->w/2,scene->surface->h/2,0, scene->background );
	drawActor( scene->actor );

	spSelectRenderTarget( old_target );
}


void
resizeScene ( struct eScene* scene )
{
	if ( scene->background != NULL )
		spDeleteSurface( scene->background );
	if ( scene->surface != NULL )
		spDeleteSurface( scene->surface );

	scene->background = spLoadSurfaceZoom( scene->backgroundPath,
						spGetSizeFactor()/ 2 );
	scene->surface = spCreateSurface(1000,1000);
}

void
initActor ( struct eActor* actor, char name[512] )
{
	strcpy(actor->name, name);
	actor->emoteCount = 0;
	actor->emoteSelection = -1;
}

void
drawActor ( struct eActor* actor )
{
	SDL_Surface* target = spGetRenderTarget();
	if ( actor->emote != NULL)
		spBlitSurface( target->w / 2,target->h - (target->h / 2),0, actor->emote );
}

void
resizeActor ( struct eActor* actor )
{
	int nowEmote = actor->emoteSelection;

	if ( actor->emote != NULL )
		spDeleteSurface( actor->emote );
	if ( nowEmote >= 0 && actor->emoteCount > 0 )
		actor->emote = spLoadSurfaceZoom( actor->emotePaths[nowEmote],
						  spGetSizeFactor()/ 3);
	else
		actor->emote = NULL;
}

void
addEmote ( struct eActor* actor, char path[512] )
{
	strcpy( actor->emotePaths[actor->emoteCount], path );
	actor->emoteCount += 1;
}
