#include <iostream>

//#include <X11/Xlib.h>
//#undef Drawable
//#undef Window
//#undef Font
//#undef Status
//#undef Default
//#undef None
//"-lX11"

#include <unistd.h>
#include <math.h>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;


//==================================== Defining constants
const float movementSpeed = 0.07f;
const int playerSize = 16;

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
        {1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1},
        {1,1,1,1,1,1,0,1,1,0,1,2,2,2,2,2,2,1,0,1,1,0,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,0,1,1,0,1,2,2,2,2,2,2,1,0,1,1,0,1,1,1,1,1,1},
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

//================================================================------...... DECLARATION OF GLOBAL VARS


//========================== Ghost Stuff
struct Ghost{
    Vector2i position;
    Vector2i velocity;
    char name;
    const float movementSpeed = 0.15f;
    float elapsed;
    sf::RectangleShape* character;

    Ghost(char n = '-',int x=0, int y=0, int vx = 0, int vy = 0){
        position.x = 1;
        position.y = 10;
        velocity.x = 0;
        velocity.y = -1;
        elapsed = 0.0f;
        name = n;
        character = new sf::RectangleShape(sf::Vector2f(playerSize, playerSize));
        if(n=='r')
        {
            character->setFillColor(sf::Color::Red);        
            position.x = 13;
            position.y = 14;
        }
        else if(n=='g')
        {
            character->setFillColor(sf::Color::Green);        
            position.x = 14;
            position.y = 14;
        }
        else if(n=='b')
        {
            character->setFillColor(sf::Color::Blue);        
            position.x = 15;
            position.y = 14;
        }
        else if(n=='p')
        {
            character->setFillColor(sf::Color::Magenta);        
            position.x = 16;
            position.y = 14;
        }        
        else
            {character->setFillColor(sf::Color::White);}

        character->setPosition(16*position.x, 16*position.y);
    }
};

//takes ghost coords and player coords, returns distance between them.
double calculateDistance(int x1, int y1, int x2, int y2) {
    double deltaX = x1 - x2;
    double deltaY = y1 - y2;
    deltaX = deltaX * deltaX;
    deltaY = deltaY * deltaY;

    return std::pow(deltaX+deltaY, 0.5);;
}
void decideVelo(struct Ghost& g, Vector2i& playerPosition){
    double minDistance = 5000;
    double dist;
    if(g.name == 'r'){
        if(numberMap[g.position.y][g.position.x-1] == 0 && g.velocity.x != 1 || (g.position.y == 17 && g.position.x <28 && g.position.x > 22)){
            dist = calculateDistance(g.position.x-1, g.position.y, playerPosition.x, playerPosition.y);
            if(minDistance > dist){
                minDistance = dist;
                g.velocity.x = -1;
                g.velocity.y = 0;
            }
            //std::cout<<minDistance<<std::endl;
        }
        if(numberMap[g.position.y-1][g.position.x] == 0 && g.velocity.y !=1){
            dist = calculateDistance(g.position.x, g.position.y-1, playerPosition.x, playerPosition.y);
            if(minDistance > dist){
                minDistance = dist;
                g.velocity.x = 0;
                g.velocity.y = -1;
            }
        }
        if(numberMap[g.position.y][g.position.x+1] == 0 && g.velocity.x!=-1 || (g.position.y==17 && g.position.x >0 && g.position.x < 6)){
            dist = calculateDistance(g.position.x+1, g.position.y, playerPosition.x, playerPosition.y);
            if(minDistance > dist){
                minDistance = dist;
                g.velocity.x = 1;
                g.velocity.y = 0;
            }
        }
        if(numberMap[g.position.y+1][g.position.x] == 0 && g.velocity.y != -1){
            dist = calculateDistance(g.position.x, g.position.y+1, playerPosition.x, playerPosition.y);
            if(minDistance > dist){
                minDistance = dist;
                g.velocity.x = 0;
                g.velocity.y = 1;
            }
        }
    }
    else if(g.name == 'b'){
        if(numberMap[g.position.y][g.position.x-1] == 0 && g.velocity.x != 1 || (g.position.y == 17 && g.position.x <28 && g.position.x > 22)){
            dist = calculateDistance(g.position.x-1, g.position.y, playerPosition.x+2, playerPosition.y);
            if(minDistance > dist){
                minDistance = dist;
                g.velocity.x = -1;
                g.velocity.y = 0;
            }
        }
        if(numberMap[g.position.y-1][g.position.x] == 0 && g.velocity.y !=1){
            dist = calculateDistance(g.position.x, g.position.y-1, playerPosition.x+2, playerPosition.y);
            if(minDistance > dist){
                minDistance = dist;
                g.velocity.x = 0;
                g.velocity.y = -1;
            }
        }
        if(numberMap[g.position.y][g.position.x+1] == 0 && g.velocity.x!=-1 || (g.position.y==17 && g.position.x >0 && g.position.x < 6)){
            dist = calculateDistance(g.position.x+1, g.position.y, playerPosition.x+2, playerPosition.y);
            if(minDistance > dist){
                minDistance = dist;
                g.velocity.x = 1;
                g.velocity.y = 0;
            }
        }
        if(numberMap[g.position.y+1][g.position.x] == 0 && g.velocity.y != -1){
            dist = calculateDistance(g.position.x, g.position.y+1, playerPosition.x+2, playerPosition.y);
            if(minDistance > dist){
                minDistance = dist;
                g.velocity.x = 0;
                g.velocity.y = 1;
            }
        }
    }
    else if(g.name == 'g'){
        if(numberMap[g.position.y][g.position.x-1] == 0 && g.velocity.x != 1 || (g.position.y == 17 && g.position.x <28 && g.position.x > 22)){
            dist = calculateDistance(g.position.x-1, g.position.y, playerPosition.x+4, playerPosition.y);
            if(minDistance > dist){
                minDistance = dist;
                g.velocity.x = -1;
                g.velocity.y = 0;
            }
        }
        if(numberMap[g.position.y-1][g.position.x] == 0 && g.velocity.y !=1){
            dist = calculateDistance(g.position.x, g.position.y-1, playerPosition.x+4, playerPosition.y);
            if(minDistance > dist){
                minDistance = dist;
                g.velocity.x = 0;
                g.velocity.y = -1;
            }
        }
        if(numberMap[g.position.y][g.position.x+1] == 0 && g.velocity.x!=-1 || (g.position.y==17 && g.position.x >0 && g.position.x < 6)){
            dist = calculateDistance(g.position.x+1, g.position.y, playerPosition.x+4, playerPosition.y);
            if(minDistance > dist){
                minDistance = dist;
                g.velocity.x = 1;
                g.velocity.y = 0;
            }
        }
        if(numberMap[g.position.y+1][g.position.x] == 0 && g.velocity.y != -1){
            dist = calculateDistance(g.position.x, g.position.y+1, playerPosition.x+4, playerPosition.y+1);
            if(minDistance > dist){
                minDistance = dist;
                g.velocity.x = 0;
                g.velocity.y = 1;
            }
        }
    }
    else if(g.name == 'p'){
        minDistance = -1;
        if(numberMap[g.position.y][g.position.x-1] == 0 && g.velocity.x != 1 || (g.position.y == 17 && g.position.x <28 && g.position.x > 22)){
            dist = calculateDistance(g.position.x-1, g.position.y, playerPosition.x, playerPosition.y);
            if(minDistance < dist){
                minDistance = dist;
                g.velocity.x = -1;
                g.velocity.y = 0;
            }
        }
        if(numberMap[g.position.y-1][g.position.x] == 0 && g.velocity.y !=1){
            dist = calculateDistance(g.position.x, g.position.y-1, playerPosition.x, playerPosition.y);
            if(minDistance < dist){
                minDistance = dist;
                g.velocity.x = 0;
                g.velocity.y = -1;
            }
        }
        if(numberMap[g.position.y][g.position.x+1] == 0 && g.velocity.x!=-1 || (g.position.y==17 && g.position.x >0 && g.position.x < 6)){
            dist = calculateDistance(g.position.x+1, g.position.y, playerPosition.x, playerPosition.y);
            if(minDistance < dist){
                minDistance = dist;
                g.velocity.x = +1;
                g.velocity.y = 0;
            }
        }
        if(numberMap[g.position.y+1][g.position.x] == 0 && g.velocity.y != -1){
            dist = calculateDistance(g.position.x, g.position.y+1, playerPosition.x, playerPosition.y);
            if(minDistance < dist){
                minDistance = dist;
                g.velocity.x = 0;
                g.velocity.y = +1;
            }
        }
    }
}

//takes ghost structure and player position as parameters. returns nothing.
void ghostMovement(struct Ghost& g, Vector2i& playerPosition){

    decideVelo(g,playerPosition);

     if (g.elapsed >= g.movementSpeed) { // Check if enough time has passed
 
            Vector2i newPosition = g.position + g.velocity;
            
            if (numberMap[newPosition.y][newPosition.x] != 1) {
                g.position = newPosition;
                g.character->setPosition(newPosition.x * playerSize, newPosition.y * playerSize);
            }
            g.elapsed = 0.0f; // Reset the elapsed time
        }
}

//========================== Ghost Stuff


void constantMovement(Vector2i& velocity, Vector2i& playerPosition, RectangleShape& player, float& elapsed)
{

        if (sf::Keyboard::isKeyPressed(Keyboard::Up))
          velocity = Vector2i(0, -1);
        else if (sf::Keyboard::isKeyPressed(Keyboard::Down))
                velocity = Vector2i(0, 1);
        else if (sf::Keyboard::isKeyPressed(Keyboard::Right))
                velocity = Vector2i(1, 0);
        else if (sf::Keyboard::isKeyPressed(Keyboard::Left))
                velocity = Vector2i(-1, 0);      

  
         // Move the player
        if (elapsed >= movementSpeed) { // Check if enough time has passed
            Vector2i newPosition = playerPosition + velocity;
            if (numberMap[newPosition.y][newPosition.x] != 1) {
                playerPosition = newPosition;
                player.setPosition(playerPosition.x * playerSize, playerPosition.y * playerSize);
            }
            //teleportation
            if (newPosition.y == 17 && (newPosition.x < 0 || newPosition.x > 27))
            {
                if (newPosition.x < 0)
                  {
                    newPosition.x += 28;
                    player.setPosition( newPosition.x * playerSize, playerPosition.y * playerSize);
                  }
                else if (newPosition.x > 27)
                       {
                        newPosition.x -= 28;
                        player.setPosition(newPosition.x * playerSize, playerPosition.y * playerSize);
                       }
                       playerPosition = newPosition;
            }
                  elapsed = 0.0f; // Reset the elapsed time
        }
        
}

void pelletCollision(Vector2i& playerPosition, bool**& ifcollected, int& score)
{
    //check if at the current position, a coint is present. If true, increment score and set the array to false at the position
    if (ifcollected[playerPosition.y][playerPosition.x])
      {
        score++;
        ifcollected[playerPosition.y][playerPosition.x] = 0;
      }
}

void GhostCollision(Vector2i& playerPosition, RectangleShape& player, struct Ghost& ghost, int& lives, bool& ifhit, float& seconds)
{
   if (!ifhit && playerPosition.x == ghost.position.x && playerPosition.y == ghost.position.y)
     {
      //std::cout << "hit at player: " << playerPosition.x << ", " << playerPosition.y << " and ghost: " << ghost.position.x << ", " << ghost.position.y << " by ghost: " << ghost.name << endl << endl;
      //std::cout << "seconds: "<< seconds << endl;
      lives--; 
      player.setFillColor(sf::Color::White);
      ifhit = true; //to make player invincible
     }
}



int main(){

 //important booleans
 bool ifwin = false;
 bool ifhit = false;

 sf::RenderWindow window(sf::VideoMode(448, 576), "Pac Man");

    //============== loading resources 
    // Load the image
    sf::Texture texture;
    if (!texture.loadFromFile("resources/map.png"))
    {
        // Error loading image
        std::cout<<"Could not load map image"<<std::endl;
        return 1;
    }

    Texture pellet_texture;
    if(!pellet_texture.loadFromFile("resources/smallPellet.png")){
        // Error loading image
        std::cout<<"Could not load pellet image"<<std::endl;
        return 1;
    }
    Font font;
    if(!font.loadFromFile("resources/pacFont.ttf")){
        // Error loading font
        std::cout<<"Could not load font"<<std::endl;
        return 1;
    }

    Texture ending_screen;
    if (!ending_screen.loadFromFile("resources/win_screen.png")){
         // Error loading image
        std::cout<<"Could not load ending screen image"<<std::endl;
        return 1;
    }
    //=================---------- loading Resources

    Sprite map(texture);
    Sprite end(ending_screen);
    

    // Create the player (a simple rectangle for now)
    sf::RectangleShape player(sf::Vector2f(playerSize, playerSize));
    player.setFillColor(sf::Color::Yellow);
    player.setPosition(16*1, 16*4);

    sf::Vector2i playerPosition(1, 4);
    sf::Vector2i velocity (0, 0);

    int score = 0, lives = 30;
    Clock clock;
    float elapsed = 0.0f;
    float hit_elapsed = 0.0f;
    int counter = 0;
    for (int i = 0; i < 36; i++)
       for (int j = 0; j < 28; j++)
          {
            if (!numberMap[i][j])
              counter++;
          }
    
    Sprite* pellets = new Sprite[counter];
    //bool array to keep track of pellets
    bool** ifcollected;
    ifcollected = new bool*[36];
    for (int i = 0; i < 36; i++)
       ifcollected[i] = new bool[28];
    
    for (int i = 0; i < 36; i++)
       for (int j = 0; j < 28; j++)
          {
            if (!numberMap[i][j])
              ifcollected[i][j] = 1;
            else
                ifcollected[i][j] = 0;  
          }
    


    int k = 0;
    for (int i = 0; i < 36; i++)
       for (int j = 0; j < 28; j++)
          {
            if (!numberMap[i][j])
              {
                pellets[k].setTexture(pellet_texture);
                pellets[k].setPosition(j * 16, i * 16);
                k++;
              }
          }


    //================================ lives + scoreboard setup
    Text t_score, t_lives, r_score, r_lives;
    
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
    //================================ lives + scoreboard setup

    Ghost g1('r');
    Ghost g2('g');
    Ghost g3('b');
    Ghost g4('p');

    float seconds = 0.0f;
    //================================ Game Loop - Start
    while (window.isOpen()) {
        //Update elasped
        seconds = clock.restart().asSeconds();
        elapsed += seconds;
        g1.elapsed += seconds;
        g2.elapsed += seconds;
        g3.elapsed += seconds;
        g4.elapsed += seconds;
        hit_elapsed += seconds;

        //Handle events
        usleep(3000);
        
        //check if user closes the window
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
       ghostMovement(g1,playerPosition);
       ghostMovement(g2,playerPosition);
       ghostMovement(g3,playerPosition);
       ghostMovement(g4,playerPosition);


       constantMovement(velocity, playerPosition, player, elapsed);
       pelletCollision(playerPosition, ifcollected, score);
       
       if (!ifhit) { //only if player is no longer invincible do we check ghost collision
        GhostCollision(playerPosition, player, g1, lives, ifhit, seconds);
        GhostCollision(playerPosition, player, g2, lives, ifhit, seconds);
        GhostCollision(playerPosition, player, g3, lives, ifhit, seconds);
        GhostCollision(playerPosition, player, g4, lives, ifhit, seconds);
       }
       else
       {
        if (hit_elapsed > 3) //if invincibilty frames are over, reset the player
          {
            player.setFillColor(sf::Color::Yellow);
            hit_elapsed = 0.0;
            ifhit = false; //the player can now be hit again
          }
       }

       r_score.setString(std::to_string(score));
       r_lives.setString(std::to_string(lives));

       if (score == counter){
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
                if (!numberMap[i][j]) //if a coin *should* be present
                {
                    if (ifcollected[i][j]) //and it is, the pellet is drawn
                      window.draw(pellets[k]);

                   k++; //k is incremented either way, skipping collected coins
                }
            }
        }
     

        window.draw(map);
        window.draw(player);

        window.draw(*g1.character);
        window.draw(*g2.character);
        window.draw(*g3.character);
        window.draw(*g4.character);

        window.draw(t_score);
        window.draw(t_lives);
        window.draw(r_score);
        window.draw(r_lives);
        window.display();
    }
    //================================ Game Loop - End
    
    
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
        } }

            if (Keyboard::isKeyPressed(Keyboard::Enter))
            {
                win_screen.close();
            break;
            }

        win_screen.clear();
        win_screen.draw(end);
        win_screen.draw(outcome);
        win_screen.display();
    }
    
    return 0;

}
