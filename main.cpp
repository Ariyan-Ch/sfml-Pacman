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

//==== DECLARATION OF ALL GLOBAL VARIABLES
const float movementSpeed = 0.1f;
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
    const float movementSpeed = 0.15f;
    float elapsed;
    sf::RectangleShape* character;

    Ghost(int x=0, int y=0, int vx = 0, int vy = 0){
        position.x = 1;
        position.y = 10;
        velocity.x = 0;
        velocity.y = -1;
        elapsed = 0.0f;

        character = new sf::RectangleShape(sf::Vector2f(playerSize, playerSize));
        character->setFillColor(sf::Color::Red);
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

//takes ghost structure and player position as parameters. returns nothing.
void ghostMovement(struct Ghost& g, Vector2i& playerPosition){

 

     if (g.elapsed >= g.movementSpeed) { // Check if enough time has passed
        double minDistance = 5000;
        double dist;
        if(numberMap[g.position.y][g.position.x-1] == 0 ){
            dist = calculateDistance(g.position.x-1, g.position.y, playerPosition.x, playerPosition.y);
            if(minDistance > dist){
                minDistance = dist;
                g.velocity.x = -1;
                g.velocity.y = 0;
            }
            //std::cout<<minDistance<<std::endl;
        }
        if(numberMap[g.position.y-1][g.position.x] == 0 ){
            dist = calculateDistance(g.position.x, g.position.y-1, playerPosition.x, playerPosition.y);
            if(minDistance > dist){
                minDistance = dist;
                g.velocity.x = 0;
                g.velocity.y = -1;
            }
        }
        if(numberMap[g.position.y][g.position.x+1] == 0 ){
            dist = calculateDistance(g.position.x+1, g.position.y, playerPosition.x, playerPosition.y);
            if(minDistance > dist){
                minDistance = dist;
                g.velocity.x = 1;
                g.velocity.y = 0;
            }
        }
        if(numberMap[g.position.y+1][g.position.x] == 0 ){
            dist = calculateDistance(g.position.x, g.position.y+1, playerPosition.x, playerPosition.y);
            if(minDistance > dist){
                minDistance = dist;
                g.velocity.x = 0;
                g.velocity.y = 1;
            }
        }
            Vector2i newPosition = g.position + g.velocity;
            
            //std::cout<<g.elapsed<<std::endl;
            if (numberMap[newPosition.y][newPosition.x] != 1) {
                g.position = newPosition;
                g.character->setPosition(newPosition.x * playerSize, newPosition.y * playerSize);
            }


            //teleportation
            /*
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
            }*/
            g.elapsed = 0.0f; // Reset the elapsed time
        }
}

//========================== Ghost Stuff


void constantMovement(Window& window, Vector2i& velocity, Vector2i& playerPosition, RectangleShape& player, float& elapsed)
{
    Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::KeyPressed) {
                switch (event.key.code) {
                    case Keyboard::W:
                        velocity = Vector2i(0, -1);
                        break;
                    case Keyboard::A:
                        velocity = Vector2i(-1, 0);
                        break;
                    case Keyboard::S:
                        velocity = Vector2i(0, 1);
                        break;
                    case Keyboard::D:
                        velocity = Vector2i(1, 0);
                        break;
                    default:
                        break;
                }
            }
        }

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

void pelletCollision(Sprite*& pellets, int size, bool*& ifcollected, int& score, RectangleShape& player)
{
    for (int i = 0; i < size; i++)
      {
        if (pellets[i].getPosition() == player.getPosition())
          {
            ifcollected[i] = 1;
            score++;
            break;
          }
      }

}



int main(){

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
        std::cout<<"Could not load pallet image"<<std::endl;
        return 1;
    }
    Font font;
    if(!font.loadFromFile("resources/pacFont.ttf")){
        // Error loading font
        std::cout<<"Could not load font"<<std::endl;
        return 1;
    }
    //=================---------- loading Resources

    Sprite map(texture);

    // Create the player (a simple rectangle for now)
    sf::RectangleShape player(sf::Vector2f(playerSize, playerSize));
    player.setFillColor(sf::Color::Yellow);
    player.setPosition(16*1, 16*4);

    sf::Vector2i playerPosition(1, 4);
    sf::Vector2i velocity (0, 0);

    int score = 0, lives = 3;
    Clock clock;
    float elapsed = 0.0f;
    int counter = 0;
    for (int i = 0; i < 36; i++)
       for (int j = 0; j < 28; j++)
          {
            if (!numberMap[i][j])
              counter++;
          }

    Sprite* pellets = new Sprite[counter];
    bool* ifcollected = new bool[counter];

    for (int i = 0; i < counter; i++)
       ifcollected[i] = 0;


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

    t_score.setPosition(290, 10);
    t_lives.setPosition(0, 10);
    r_score.setFont(font);
    r_lives.setFont(font);
    r_score.setPosition(150, 18);
    r_lives.setPosition(400, 10);
    r_score.setFillColor(sf::Color::Red);
    r_lives.setFillColor(sf::Color::Red);
    r_score.setCharacterSize(20);
    r_lives.setCharacterSize(20);
    //================================ lives + scoreboard setup
    Ghost g1;
    float seconds = 0.0f;
    // Game loop
    while (window.isOpen()) {
        //Update elasped
        seconds = clock.restart().asSeconds();
        elapsed += seconds;
        g1.elapsed += seconds;
        
        //Handle events
        usleep(3000);
        

       constantMovement(window, velocity, playerPosition, player, elapsed);
       ghostMovement(g1,playerPosition);
       pelletCollision(pellets, counter, ifcollected, score, player);
       

        
        window.clear();

        //draws the pellets
        for (int i = 0; i < counter; i++)
        {
            if (!ifcollected[i])
              window.draw(pellets[i]);
        }
     

        window.draw(map);
        window.draw(player);
        window.draw(*g1.character);

        window.draw(t_score);
        window.draw(t_lives);

        r_score.setString(to_string(score));
        //std::cout<<to_string(score)<<std::endl;

        //std::cout<<lives<<std::endl;
        window.draw(r_score);
        window.draw(r_lives);
        window.display();
    }

    return 0;

}
