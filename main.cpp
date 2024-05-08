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
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

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
    if(!pellet_texture.loadFromFile("resources/pellet.png")){
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
                pellets[k].setScale(0.2,0.2);
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
  
        
    // Game loop
    while (window.isOpen()) {
        //Update elasped
        elapsed += clock.restart().asSeconds(); 
        //Handle events
        usleep(3000);
        

       constantMovement(window, velocity, playerPosition, player, elapsed);
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
 
        window.draw(t_score);
        window.draw(t_lives);

        r_score.setString(to_string(score));
        std::cout<<to_string(score)<<std::endl;

        std::cout<<lives<<std::endl;
        window.draw(r_score);
        window.draw(r_lives);
        window.display();
    }

    return 0;

}
