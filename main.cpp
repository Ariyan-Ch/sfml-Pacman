
#include <X11/Xlib.h>
#undef Drawable
#undef Window
#undef Font
#undef Status
#undef Default
#undef None

#include <iostream>
#include <unistd.h>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <pthread.h>
#include <semaphore.h>
using namespace std;
using namespace sf;


//==================================== Defining Global Vars

const float movementSpeed = 0.1f;
const int playerSize = 16;
sf::Sprite playerSprite;
sf::Vector2i playerPosition(1, 4);
sf::Vector2i playerVelocity (0, 0);
sf::Text r_score, r_lives;
sf::Sprite BigPellets;
int BigPelletPositions [4][4] = {{1, 26, 1, 26}, //x-positions
                                {11, 11, 24, 24}}; //y-positions
bool BigPelletEaten = false; //to put ghosts in frightened state
int BigPellet_Index = 0;
                                  
short int numberMap [36][28] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
        {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
        {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1},
        {1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1},
        {1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1},
        {1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1},
        {1,1,1,1,1,1,0,1,1,0,1,1,1,2,2,1,1,1,0,1,1,0,1,1,1,1,1,1},
        {1,1,1,1,1,1,0,1,1,0,1,0,0,0,0,0,0,1,0,1,1,0,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,0,1,1,0,1,0,0,0,0,0,0,1,0,1,1,0,1,1,1,1,1,1},
        {1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1},
        {1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1},
        {1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1},
        {1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
        {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
        {1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1},
        {1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1},
        {1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1},
        {1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1},
        {1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
bool** ifcollected;

int score = 0, lives = 5;
bool ifwin = false;
bool ifhit = false;
bool gameRuns = true;

float keyPermElapsed = 0.0f;
float BP_elapsed = 0.0f;

pthread_t gameEngineThreadID, UIThreadID, ghost1ThreadID, ghost2ThreadID,ghost3ThreadID,ghost4ThreadID;
sem_t startRestThreads;
sem_t pacmanGhostReadWrite;
sem_t keys;
sem_t permits;

sem_t boosts;
sem_t mutexBoost; 
//================================================================------...... DECLARATION OF GLOBAL VARS

//========================== Ghost Stuff
//structure for all ghost functionalities
struct Ghost{
    Vector2i position;
    Vector2i housePosition;
    Vector2i velocity;
    char name;
    float movementSpeed = 0.2f;
    float elapsed;
    bool dead = false;
    bool speedBoost = false;
    sf::Sprite character;
    Ghost (char n = '-'){
        velocity.x = 0;
        velocity.y = -1;
        elapsed = 0.0f;
        name = n;
        if(n=='r')
        {   
            position.x = 12;
            position.y = 17;

        }
        else if(n=='g')
        {
            position.x = 13;
            position.y = 17;
        }
        else if(n=='b')
        {      
            position.x = 14;
            position.y = 17;
        }
        else if(n=='p')
        {      
            position.x = 15;
            position.y = 17;
        }      
        housePosition = position;
        //housePosition.y += 4;  
    }
    Ghost(Texture& t, char n = '-', int x=0, int y=0, int vx = 0, int vy = 0){
        position.x = 1;
        position.y = 10;
        velocity.x = 0;
        velocity.y = -1;
        elapsed = 0.0f;
        name = n;
        housePosition = position;
    }
};
Ghost g1('r');
Ghost g2('g');
Ghost g3('b');
Ghost g4('p');

//takes ghost coords and player coords, returns distance between them.
double calculateDistance(int x1, int y1, int x2, int y2) {
    double deltaX = x1 - x2;
    double deltaY = y1 - y2;
    deltaX = deltaX * deltaX;
    deltaY = deltaY * deltaY;

    return std::pow(deltaX+deltaY, 0.5);;
}
//decides where the ghost should move based on player's position
void decideVelo(struct Ghost& g){
    double minDistance = 5000;
    double dist;
    Vector2i oldWaes = g.velocity;
    if(g.dead){
        if(numberMap[g.position.y][g.position.x-1] !=1 && oldWaes.x != 1 || (g.position.y == 17 && g.position.x <28 && g.position.x > 22)){
            dist = calculateDistance(g.position.x-1, g.position.y, g.housePosition.x, g.housePosition.y);
            if(minDistance > dist){
                minDistance = dist;
                g.velocity.x = -1;
                g.velocity.y = 0;
            }
            //std::cout<<minDistance<<std::endl;
        }
        if(numberMap[g.position.y-1][g.position.x] !=1 && oldWaes.y !=1){
            dist = calculateDistance(g.position.x, g.position.y-1, g.housePosition.x, g.housePosition.y);
            if(minDistance > dist){
                minDistance = dist;
                g.velocity.x = 0;
                g.velocity.y = -1;
            }
        }
        if(numberMap[g.position.y][g.position.x+1] !=1 && oldWaes.x!=-1 || (g.position.y==17 && g.position.x >0 && g.position.x < 6)){
            dist = calculateDistance(g.position.x+1, g.position.y, g.housePosition.x, g.housePosition.y);
            if(minDistance > dist){
                minDistance = dist;
                g.velocity.x = 1;
                g.velocity.y = 0;
            }
        }
        if(numberMap[g.position.y+1][g.position.x] !=1 && oldWaes.y != -1){
            dist = calculateDistance(g.position.x, g.position.y+1,g.housePosition.x, g.housePosition.y);
            if(minDistance > dist){
                minDistance = dist;
                g.velocity.x = 0;
                g.velocity.y = 1;
            }

        }
    }
    else{
        if(g.name == 'r'){
            if(numberMap[g.position.y][g.position.x-1] == 0 && oldWaes.x != 1 || (g.position.y == 17 && g.position.x <28 && g.position.x > 22)){
                dist = calculateDistance(g.position.x-1, g.position.y, playerPosition.x, playerPosition.y);
                if(minDistance > dist){
                    minDistance = dist;
                    g.velocity.x = -1;
                    g.velocity.y = 0;
                }
                //std::cout<<minDistance<<std::endl;
            }
            if(numberMap[g.position.y-1][g.position.x] == 0 && oldWaes.y !=1){
                dist = calculateDistance(g.position.x, g.position.y-1, playerPosition.x, playerPosition.y);
                if(minDistance > dist){
                    minDistance = dist;
                    g.velocity.x = 0;
                    g.velocity.y = -1;
                }
            }
            if(numberMap[g.position.y][g.position.x+1] == 0 && oldWaes.x!=-1 || (g.position.y==17 && g.position.x >0 && g.position.x < 6)){
                dist = calculateDistance(g.position.x+1, g.position.y, playerPosition.x, playerPosition.y);
                if(minDistance > dist){
                    minDistance = dist;
                    g.velocity.x = 1;
                    g.velocity.y = 0;
                }
            }
            if(numberMap[g.position.y+1][g.position.x] == 0 && oldWaes.y != -1){
                dist = calculateDistance(g.position.x, g.position.y+1, playerPosition.x, playerPosition.y);
                if(minDistance > dist){
                    minDistance = dist;
                    g.velocity.x = 0;
                    g.velocity.y = 1;
                }

            }
        }
        else if(g.name == 'b'){
            if(numberMap[g.position.y][g.position.x-1] == 0 && oldWaes.x != 1 || (g.position.y == 17 && g.position.x <28 && g.position.x > 22)){
                dist = calculateDistance(g.position.x-1, g.position.y, playerPosition.x+2, playerPosition.y);
                if(minDistance > dist){
                    minDistance = dist;
                    g.velocity.x = -1;
                    g.velocity.y = 0;
                }
            }
            if(numberMap[g.position.y-1][g.position.x] == 0 && oldWaes.y !=1){
                dist = calculateDistance(g.position.x, g.position.y-1, playerPosition.x+2, playerPosition.y);
                if(minDistance > dist){
                    minDistance = dist;
                    g.velocity.x = 0;
                    g.velocity.y = -1;
                }
            }
            if(numberMap[g.position.y][g.position.x+1] == 0 && oldWaes.x!=-1 || (g.position.y==17 && g.position.x >0 && g.position.x < 6)){
                dist = calculateDistance(g.position.x+1, g.position.y, playerPosition.x+2, playerPosition.y);
                if(minDistance > dist){
                    minDistance = dist;
                    g.velocity.x = 1;
                    g.velocity.y = 0;
                }
            }
            if(numberMap[g.position.y+1][g.position.x] == 0 && oldWaes.y != -1){
                dist = calculateDistance(g.position.x, g.position.y+1, playerPosition.x+2, playerPosition.y);
                if(minDistance > dist){
                    minDistance = dist;
                    g.velocity.x = 0;
                    g.velocity.y = 1;
                }
            }
        }
        else if(g.name == 'g'){
            if(numberMap[g.position.y][g.position.x-1] == 0 && oldWaes.x != 1 || (g.position.y == 17 && g.position.x <28 && g.position.x > 22)){
                dist = calculateDistance(g.position.x-1, g.position.y, playerPosition.x-2, playerPosition.y);
                if(minDistance > dist){
                    minDistance = dist;
                    g.velocity.x = -1;
                    g.velocity.y = 0;
                }
            }
            if(numberMap[g.position.y-1][g.position.x] == 0 && oldWaes.y !=1){
                dist = calculateDistance(g.position.x, g.position.y-1, playerPosition.x-2, playerPosition.y);
                if(minDistance > dist){
                    minDistance = dist;
                    g.velocity.x = 0;
                    g.velocity.y = -1;
                }
            }
            if(numberMap[g.position.y][g.position.x+1] == 0 && oldWaes.x!=-1 || (g.position.y==17 && g.position.x >0 && g.position.x < 6)){
                dist = calculateDistance(g.position.x+1, g.position.y, playerPosition.x-2, playerPosition.y);
                if(minDistance > dist){
                    minDistance = dist;
                    g.velocity.x = 1;
                    g.velocity.y = 0;
                }
            }
            if(numberMap[g.position.y+1][g.position.x] == 0 && oldWaes.y != -1){
                dist = calculateDistance(g.position.x, g.position.y+1, playerPosition.x-2, playerPosition.y+1);

                if(minDistance > dist){
                    minDistance = dist;
                    g.velocity.x = 0;
                    g.velocity.y = 1;
                }

            }
        }
        else if(g.name == 'p'){
            minDistance = -1;
            if(numberMap[g.position.y][g.position.x-1] == 0 && oldWaes.x != 1 || (g.position.y == 17 && g.position.x <28 && g.position.x > 22)){
                dist = calculateDistance(g.position.x-1, g.position.y, playerPosition.x, playerPosition.y);
                if(minDistance < dist){
                    minDistance = dist;
                    g.velocity.x = -1;
                    g.velocity.y = 0;
                }
            }
            if(numberMap[g.position.y-1][g.position.x] == 0 && oldWaes.y !=1){
                dist = calculateDistance(g.position.x, g.position.y-1, playerPosition.x, playerPosition.y);
                if(minDistance < dist){
                    minDistance = dist;
                    g.velocity.x = 0;
                    g.velocity.y = -1;
                }
            }
            if(numberMap[g.position.y][g.position.x+1] == 0 && oldWaes.x!=-1 || (g.position.y==17 && g.position.x >0 && g.position.x < 6)){
                dist = calculateDistance(g.position.x+1, g.position.y, playerPosition.x, playerPosition.y);
                if(minDistance < dist){
                    minDistance = dist;
                    g.velocity.x = +1;
                    g.velocity.y = 0;
                }
            }
            if(numberMap[g.position.y+1][g.position.x] == 0 && oldWaes.y != -1){
                dist = calculateDistance(g.position.x, g.position.y+1, playerPosition.x, playerPosition.y);
                if(minDistance < dist){
                    minDistance = dist;
                    g.velocity.x = 0;
                    g.velocity.y = +1;
                }
            }
            if(g.position.y == 17 && g.position.x == 0)
            {
                g.velocity.x = 1;
                g.velocity.y = 0;
            }
            else if(g.position.y == 17 && g.position.x ==27){
                g.velocity.x = -1;
                g.velocity.y = 0;
            }
            
        }
    }
}
//takes ghost structure returns nothing. moves the ghost
void* ghostMovement(void* arg){
    sf::Clock timerGhost;
    float timePasedGhost = 0.0f;
    struct Ghost * g = (Ghost*)arg;

    while(gameRuns){

        if(!sem_trywait(&mutexBoost)){
            if(!sem_trywait(&boosts)){
                if(g->speedBoost == false)
                    g->speedBoost = true;
                else
                    sem_post(&boosts);
            }
            sem_post(&mutexBoost);
        }

        timePasedGhost = timerGhost.restart().asSeconds();
        g->elapsed += timePasedGhost;
        if(g->speedBoost)
            g->elapsed += timePasedGhost/2;

        if(g->dead == true){
            g->movementSpeed = 0.05f;
        }
        if(g->position.y>=16 && g->position.x>=11 && g->position.y<=18 && g->position.x<=17){
            g->dead = false;
            g->movementSpeed = 0.2f;
            if(keyPermElapsed>4){
                if(!sem_trywait(&permits)){
            
                    if(!sem_trywait(&keys)){
                        keyPermElapsed = 0;
                        if(g->name == 'r'){

                            g->position.x = 13;
                        }
                        else if(g->name == 'b')
                            g->position.x = 14;
                        else if(g->name == 'g')
                            g->position.x = 15;
                        else
                            g->position.x = 16;
                        g->position.y = 15;
                        sem_post(&keys);
                    }
                    sem_post(&permits);
                }
            }
        }

      //  if(g->position.y>=16 && g->position.x>=11 && g->position.y<=18 && g->position.x<=17)
        //    g->dead = false;
        if(!gameRuns)
            break;
        if (g->elapsed >= g->movementSpeed) { // Check if enough time has passed

            sem_wait(&pacmanGhostReadWrite);

            decideVelo(*g); // very long function. Decides the movement direction of ghost based on the user position on the board.
            Vector2i newPosition = g->position + g->velocity;
            if(numberMap[newPosition.y][newPosition.x] != 1){
                if(g->velocity.x==-1){
                    g->character.setTextureRect(sf::IntRect(playerSize*2,0,playerSize,playerSize));
                }
                else if(g->velocity.x == 1){
                    g->character.setTextureRect(sf::IntRect(playerSize*0,0,playerSize,playerSize));
                }
                else if(g->velocity.y == -1){
                    g->character.setTextureRect(sf::IntRect(playerSize*3,0,playerSize,playerSize));
                }
                else if(g->velocity.y == 1){
                    g->character.setTextureRect(sf::IntRect(playerSize*1,0,playerSize,playerSize));
                }
            }
            g->position = newPosition;
            g->character.setPosition(newPosition.x * playerSize, newPosition.y * playerSize);
            g->elapsed = 0.0f; // Reset the elapsed time

            sem_post(&pacmanGhostReadWrite);
        }
    }

    pthread_exit(0);
}

//========================== Ghost Stuff


void GhostCollision(float& hit_elapsed)
{
    if(ifhit){

        return;
    }
    if (playerPosition.x == g1.position.x && playerPosition.y == g1.position.y)
    {
        if(BigPelletEaten){
            g1.dead = true;
            g1.movementSpeed = 0.05f;
            if(g1.speedBoost){
                if(!sem_trywait(&mutexBoost)){
                    sem_post(&boosts);
                    g1.speedBoost = false;
                    sem_post(&mutexBoost);
                }
            }
        }
        ifhit = true; //to make player invincible
    }
    else if (playerPosition.x == g2.position.x && playerPosition.y == g2.position.y)
    {
        if(BigPelletEaten){
            g2.dead = true;
            g2.movementSpeed = 0.05f;
            if(g2.speedBoost){
                if(!sem_trywait(&mutexBoost)){
                    sem_post(&boosts);
                    g2.speedBoost = false;
                    sem_post(&mutexBoost);
                }
            }
        }
        ifhit = true; //to make player invincible
    }
    else if (playerPosition.x == g3.position.x && playerPosition.y == g3.position.y)
    {
        if(BigPelletEaten){
            g3.dead = true;
            g3.movementSpeed = 0.05f;
            if(g3.speedBoost){
                if(!sem_trywait(&mutexBoost)){
                    sem_post(&boosts);
                    g3.speedBoost = false;
                    sem_post(&mutexBoost);
                }
            }
        }
        ifhit = true; //to make player invincible
    }
    else if (playerPosition.x == g4.position.x && playerPosition.y == g4.position.y)
    {
        if(BigPelletEaten){
            g4.dead = true;
            g4.movementSpeed = 0.05f;
            if(g4.speedBoost){
                if(!sem_trywait(&mutexBoost)){
                    sem_post(&boosts);
                    g4.speedBoost = false;
                    sem_post(&mutexBoost);
                }
            }
        }
        ifhit = true; //to make player invincible
    }

    if(ifhit && !BigPelletEaten){
        lives--;
        r_lives.setString(std::to_string(lives));
        playerSprite.setPosition(16,16*4);
        playerPosition.x = 1;
        playerPosition.y = 4;
        hit_elapsed = 0.0;
    }
}
void* UI(void* arg){

    sf::Clock timerUI;
    float timePasedUI = 0.0f;
    float secondsUI = 0.0f;
    float elapsed = 0.0f;
    float hit_elapsed = 0.0f;
    while(gameRuns){
                 // Move the player
        secondsUI = timerUI.restart().asSeconds();
        elapsed += secondsUI;
        hit_elapsed += secondsUI;
        keyPermElapsed += secondsUI;

        if (elapsed >= movementSpeed) { // Check if enough time has passed
            
            if (sf::Keyboard::isKeyPressed(Keyboard::Up)){  
                playerVelocity = Vector2i(0, -1);
                playerSprite.setTextureRect(sf::IntRect(playerSize*1,0,playerSize,playerSize));
            }
            else if (sf::Keyboard::isKeyPressed(Keyboard::Down)){
                playerVelocity = Vector2i(0, 1);
                playerSprite.setTextureRect(sf::IntRect(playerSize*3,0,playerSize,playerSize));
            }
            else if (sf::Keyboard::isKeyPressed(Keyboard::Right)){
                playerVelocity = Vector2i(1, 0);
                playerSprite.setTextureRect(sf::IntRect(playerSize*0,0,playerSize,playerSize));
            }
            else if (sf::Keyboard::isKeyPressed(Keyboard::Left)){
                playerVelocity = Vector2i(-1, 0); 
                playerSprite.setTextureRect(sf::IntRect(playerSize*2,0,playerSize,playerSize));
            }     
            Vector2i newPosition = playerPosition + playerVelocity;
            if(!gameRuns)
                break;

            sem_wait(&pacmanGhostReadWrite); 

            if (numberMap[newPosition.y][newPosition.x] == 0) {
                playerPosition = newPosition;
                playerSprite.setPosition(playerPosition.x * playerSize, playerPosition.y * playerSize);
            }
            //teleportation
            if (newPosition.y == 17 && (newPosition.x < 0 || newPosition.x > 27))
            {
                if (newPosition.x < 0){
                    newPosition.x += 28;
                    playerSprite.setPosition( newPosition.x * playerSize, playerPosition.y * playerSize);
                }
                else if (newPosition.x > 27){
                        newPosition.x -= 28;
                        playerSprite.setPosition(newPosition.x * playerSize, playerPosition.y * playerSize);
                }
                playerPosition = newPosition;
            }
            elapsed = 0.0f; // Reset the elapsed time

            sem_post(&pacmanGhostReadWrite); 
        }
        

        //check if at the current position, a coint is present. If true, increment score and set the array to false at the position
        if (ifcollected[playerPosition.y][playerPosition.x])
        {
            score++;
            ifcollected[playerPosition.y][playerPosition.x] = 0;
            r_score.setString(std::to_string(score));
        }
        if(!gameRuns)
            break;

        sem_wait(&pacmanGhostReadWrite);
        if (playerPosition.x == BigPelletPositions[0][BigPellet_Index] && playerPosition.y == BigPelletPositions[1][BigPellet_Index] && !BigPelletEaten && BigPellet_Index < 4)
        {
            BigPelletEaten = true;
            score += 10;
            r_score.setString(std::to_string(score));
            BigPellet_Index++;
            BP_elapsed = 0.0f;    
        }
        
        if (!ifhit) { //only if player is no longer invincible do we check ghost collision
            GhostCollision(hit_elapsed);

        }
        else if (hit_elapsed > 5) //if invincibilty frames are over, reset the player
        {    
            ifhit = false; //the player can now be hit again
        }
        else if(BigPelletEaten){
                if (playerPosition.x == g1.position.x && playerPosition.y == g1.position.y)
                    g1.dead = true;
                else if (playerPosition.x == g2.position.x && playerPosition.y == g2.position.y)
                    g2.dead = true;

                else if (playerPosition.x == g3.position.x && playerPosition.y == g3.position.y)
                    g3.dead = true;

                else if (playerPosition.x == g4.position.x && playerPosition.y == g4.position.y)
                    g4.dead = true;
        }
        sem_post(&pacmanGhostReadWrite); 

        if(!gameRuns)
            break;
    }
    pthread_exit(NULL);
    return NULL;
}

void* gameEngine(void* arg){
    //sem_init(&semaGhost,0,1);
    //window
    sf::RenderWindow window(sf::VideoMode(448, 576), "Pac Man");

    sf::Texture texture;
    sf::Texture pellet_texture;
    sf::Texture Big_pellet_texture;
    sf::Font font;
    sf::Texture ending_screen;
    sf::Texture ghostRedTex, ghostBlueTex, ghostGreenTex, ghostPurpleTex;
    sf::Texture playerTex;
    sf::Texture playerDeadTex;
    sf::Texture eyes;
    sf::Texture ScaredGhost;

    //screens
    //============================================== loading resources.
    texture.loadFromFile("resources/map.png");
    pellet_texture.loadFromFile("resources/smallPellet.png");
    font.loadFromFile("resources/pacFont.ttf");
    ending_screen.loadFromFile("resources/win_screen.png");
    ghostRedTex.loadFromFile("resources/redGhostRect.png");
    ghostBlueTex.loadFromFile("resources/blueGhostRect.png");
    ghostGreenTex.loadFromFile("resources/greenGhostRect.png");
    ghostPurpleTex.loadFromFile("resources/purpleGhostRect.png");
    playerTex.loadFromFile("resources/pacmanRect.png");
    playerDeadTex.loadFromFile("resources/pacmanDeadRect.png");
    eyes.loadFromFile("resources/eyes.png");
    Big_pellet_texture.loadFromFile("resources/BigPellet.png");
    ScaredGhost.loadFromFile("resources/weakGhost.png");

    g1.character.setTexture(ghostRedTex); 
    g1.character.setTextureRect(sf::IntRect(0,0,playerSize,playerSize));
    g1.character.setPosition(16*g1.position.x, 16*g1.position.y);

    g2.character.setTexture(ghostBlueTex); 
    g2.character.setTextureRect(sf::IntRect(0,0,playerSize,playerSize));
    g2.character.setPosition(16*g2.position.x, 16*g2.position.y);

    g3.character.setTexture(ghostGreenTex); 
    g3.character.setTextureRect(sf::IntRect(0,0,playerSize,playerSize));
    g3.character.setPosition(16*g3.position.x, 16*g3.position.y);

    g4.character.setTexture(ghostPurpleTex); 
    g4.character.setTextureRect(sf::IntRect(0,0,playerSize,playerSize));
    g4.character.setPosition(16*g4.position.x, 16*g4.position.y);

    playerSprite.setTexture(playerTex);
    playerSprite.setTextureRect(sf::IntRect(playerSize*0,0,playerSize,playerSize));
    playerSprite.setPosition(16*1, 16*4);
    //=============================================== loading resources

    Sprite map(texture);
    Sprite end(ending_screen);

    //----small pellets
    int counter = 0;
    for (int i = 0; i < 36; i++)
       for (int j = 0; j < 28; j++)
          {
            if (!numberMap[i][j] && !(i>=16 && j>=11 && i<=18 && j<=17))
              counter++;
          }
    
    Sprite* pellets = new Sprite[counter];
    //bool array to keep track of pellet
    ifcollected = new bool*[36];
    for (int i = 0; i < 36; i++)
        ifcollected[i] = new bool[28];

    for (int i = 0; i < 36; i++){
       for (int j = 0; j < 28; j++)
          {
            if (!numberMap[i][j] && !(i>=16 && j>=11 && i<=18 && j<=17))
              ifcollected[i][j] = 1;
            else
                ifcollected[i][j] = 0;  
          }
    }

    int k = 0;
    for (int i = 0; i < 36; i++)
       for (int j = 0; j < 28; j++)
          {
            if (!numberMap[i][j] && !(i>=16 && j>=11 && i<=18 && j<=17))
              {
                pellets[k].setTexture(pellet_texture);
                pellets[k].setPosition(j * 16, i * 16);
                k++;
              }
          }

    //----small pellets

    //----Big Pellets    
    
    BigPellets.setTexture(Big_pellet_texture);
    BigPellets.setPosition(16 * BigPelletPositions[0][BigPellet_Index], 16 * BigPelletPositions[1][BigPellet_Index]);

    //----Big Pellets

    //================================ lives + scoreboard setup
    Text t_score, t_lives;

    t_score.setFont(font);
    t_score.setString("Score:");
    t_lives.setFont(font);
    t_lives.setString("Lives:");
    t_score.setCharacterSize(20);
    t_lives.setCharacterSize(20);

    t_score.setPosition(250, 10);
    t_lives.setPosition(0, 10);
    r_score.setFont(font);
    r_lives.setFont(font);
    r_score.setPosition(370, 10);
    r_lives.setPosition(120, 10);
    r_score.setFillColor(sf::Color::Red);
    r_lives.setFillColor(sf::Color::Red);
    r_score.setCharacterSize(20);
    r_lives.setCharacterSize(20);
    r_lives.setString(std::to_string(lives));
    //================================ lives + scoreboard setup




    Clock clock;
    float seconds = 0.0f;
    //================================-------------------- Game Loop - Start-----------===========================>>>
    sem_post(&startRestThreads);
    while (window.isOpen()) {
        //Update elasped
        seconds = clock.restart().asSeconds();
        BP_elapsed += seconds;

        //check if user closes the window
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        

        //----------- ghost dead texture change

        if(g1.dead){
            g1.character.setTexture(eyes);
        }
        else if(BigPelletEaten)
            g1.character.setTexture(ScaredGhost);
        else
            g1.character.setTexture(ghostRedTex);

        if(g2.dead){
            g2.character.setTexture(eyes);
        }
        else if(BigPelletEaten)
            g2.character.setTexture(ScaredGhost);
        else
            g2.character.setTexture(ghostBlueTex);

        if(g3.dead){
            g3.character.setTexture(eyes);
        }
        else if(BigPelletEaten)
            g3.character.setTexture(ScaredGhost);
        else
            g3.character.setTexture(ghostGreenTex);

        if(g4.dead){
            g4.character.setTexture(eyes);
        }
        else if(BigPelletEaten)
            g4.character.setTexture(ScaredGhost);
        else
            g4.character.setTexture(ghostPurpleTex);


        if(ifhit)
            playerSprite.setTexture(playerDeadTex);
        else
            playerSprite.setTexture(playerTex);


        if (score == counter + 40){
            window.close();
            ifwin = true;
            break;
        }

        if (lives == 0)
        {
          window.close();
          break;
        } 

        window.clear();
        //draws the pellets
        k = 0;
        for (int i = 0; i < 36; i++)
        {
            for (int j = 0; j < 28; j++)
            {
                if (!numberMap[i][j]&& !(i>=16 && j>=11 && i<=18 && j<=17)) //if a coin *should* be present
                {
                    if (ifcollected[i][j]) //and it is, the pellet is drawn
                      window.draw(pellets[k]);

                    k++; //k is incremented either way, skipping collected coins
                }
            }
        }

        if (BigPellet_Index <= 4 && BP_elapsed > 5)
        {
            if (BigPellet_Index < 4)
              BigPellets.setPosition(16 * BigPelletPositions[0][BigPellet_Index], 16 * BigPelletPositions[1][BigPellet_Index]);
            else
                BigPellets.setPosition(0, 0);
            BigPelletEaten = false;
        }

        for (int i = 0; i < 4; i++)
        {
            if (!BigPelletEaten && BigPellet_Index < 4)
            window.draw(BigPellets);
        }
     

        window.draw(map);
        window.draw(playerSprite);

        window.draw(g1.character);
        window.draw(g2.character);
        window.draw(g3.character);
        window.draw(g4.character);

        window.draw(t_score);
        window.draw(t_lives);
        window.draw(r_score);
        window.draw(r_lives);
        window.display();

    }
    //================================ Game Loop - End


    gameRuns = false;
    Text outcome;
    outcome.setFont(font);
    std::string title;
    end.setPosition(end.getPosition().x, end.getPosition().y + 25);
    
    if (ifwin) { //if the player won
      outcome.setString("You Won!!!");
      outcome.setFillColor(sf::Color::Yellow);
      title = "Victory!";
    }
    else
    {
      outcome.setString("Game Over");
      outcome.setFillColor(sf::Color::Red);
      title = "Defeat...";
    }
    
    
    sf::RenderWindow win_screen(sf::VideoMode(448, 576), title);
    outcome.setPosition(win_screen.getSize().x/2 - 140, win_screen.getSize().y/2 - 50);

    //End Screen Loop
    while(win_screen.isOpen())
    {
        usleep(3000);
        Event event;
        while (win_screen.pollEvent(event)) {
            if (event.type == Event::Closed) {
                win_screen.close();
            } 
        }

        if (Keyboard::isKeyPressed(Keyboard::Enter))
        {
            win_screen.close();
            break;
        }

        win_screen.clear();
        win_screen.draw(end);
        win_screen.draw(outcome);
        win_screen.display();
        gameRuns = false;
    }
    gameRuns = false;
    pthread_exit(0);
}


int main(){

    XInitThreads();
    sem_init (&startRestThreads,0,0);
    sem_init (&pacmanGhostReadWrite,0,1);//binary semaphore, a mutex used in Scenario 1
    sem_init (&keys,0,2);   //2 keys
    sem_init (&permits, 0, 2);  //2 permits
    sem_init (&mutexBoost,0,1);
    sem_init (&boosts,0,2);

    //loading resources, starting isOpen() window loop to continuously draw everything.
    pthread_create(&gameEngineThreadID,NULL,gameEngine,NULL);

    sem_wait(&startRestThreads);


    //player movement, pallet picking, collision with ghost checking
    pthread_create(&UIThreadID, NULL,UI ,NULL);

    //ghosts, their AI
    pthread_create(&ghost1ThreadID,NULL,ghostMovement,(void*)&g1);
    pthread_create(&ghost2ThreadID,NULL,ghostMovement,(void*)&g2);
    pthread_create(&ghost3ThreadID,NULL,ghostMovement,(void*)&g3);
    pthread_create(&ghost4ThreadID,NULL,ghostMovement,(void*)&g4);


    
    pthread_exit(NULL);
    return 0;
}
