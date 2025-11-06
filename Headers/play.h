#include "../Headers/renderer.h"
#include "../Headers/maps.h"
#include "../Headers/pipe.h"
#include "../Headers/bird.h"

bool playGame(struct Game* game, struct GameMaps* maps, struct pipePair* obstacles, int count, struct Bird* bird, SDL_Event* event);
void resetGame(struct Game* game, struct pipePair* obstacles, int count, struct Bird* bird);