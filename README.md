# sfml- Pacman

### - DESCRIPTION
### 1: Remake of Pacman as a semester-end project.
### 2: Uses SFML for graphics.
### 3: POSIX library used for threads
### 4: Game Engine, Player, and 4 Ghosts all run in separate threads.
### 5: Complete Synchronization using Semaphore Primitives. 

Some of the additional synchronization is only performed as a requirement of the project. They could've also been solved without the use of Semaphores.

### - INSTRUCTIONS
### 1: Install SFML library in your system.
### 2: Install X11 library (If its not included, Concurrent threads give errors because of SFML slight incompatibility with POSIX)
### 3: Include "-pthread" and "-lX11" together with sfml parameters while compiling.
### 4: Run.
