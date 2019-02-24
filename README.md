# LoST: Legend of Silence Tribute

## Inspiration

LoST is loosely based on a fictional video game described in the short story *Navigators* by Mike Meginnis. The game is described as being similar to Nintendo's *Metroid* for the NES, with a twist: the protagonist becomes weaker as the player progresses through the game.

## Build instructions

### macOS

Install SDL2 libraries locally, then in a terminal from the root folder type:

`g++ src/main.cpp -w -lSDL2 -o build/LoST.app -I/usr/local/include -L/usr/local/lib`
