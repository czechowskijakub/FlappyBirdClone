# Flappy Bird Clone

A simple **Flappy Bird** clone made in **C** using the **SDL2** library.

---

## How does it work?

The game simulates a world loop by constantly moving background elements and obstacles from **right to left**, creating the illusion of a moving bird.  
It simply moves **SDL Rects** objects on x axis.\
The player controls the bird to avoid obstacles and score points.

---

## Features

- Smooth 2D graphics using SDL2  
- Simple physics for bird movement  
- Procedurally generated obstacles  
- Score tracking  

---

## Requirements

- **C compiler** (e.g., `gcc`)  
- **SDL2** library installed  
- ucrt64 launch: gcc Source/*.c -o main.exe \$(pkg-config --cflags --libs sdl2 SDL2_image SDL2_mixer SDL2_ttf SDL2_net)

## Controls

Enter - begin play\
Space - jump\
Escape - exit

## Screenshots
<img width="1918" height="1077" alt="mmfb" src="https://github.com/user-attachments/assets/4b21e6a1-fdd2-4d10-a303-1c2180f36bec" />
<img width="1914" height="1074" alt="GAME" src="https://github.com/user-attachments/assets/6ac5926b-5f2b-40d2-878b-06d4dfdfa0a3" />
<img width="1915" height="1075" alt="endgame" src="https://github.com/user-attachments/assets/24b67842-2992-4314-b374-d783b574eb40" />
