#include <iostream>
#include <unistd.h>

//#include <X11/Xlib.h>
//#undef Drawable
//#undef Window
//#undef Font
//#undef Status
//#undef Default
//#undef None

#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

const float movementSpeed = 0.05f;
int playerSize = 16;

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

//"-lX11"

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

    // Load the image
    sf::Texture texture;
    if (!texture.loadFromFile("resources/map.png"))
    {
        // Error loading image
        std::cout<<"Could not load map image"<<std::endl;
        return 1;
    }

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

    Texture pellet_texture;
    pellet_texture.loadFromFile("pellet.png");
    int k = 0;
    for (int i = 0; i < 36; i++)
       for (int j = 0; j < 28; j++)
          {
            if (!numberMap[i][j])
              {
                pellets[k].setTexture(pellet_texture);
                pellets[k].setPosition(j * 16, i * 16);
                pellets[k].setScale(0.05,0.05);
                k++;
              }
          }

    Font font;
    font.loadFromFile("Freedom.ttf");
    Text t_score, t_lives, r_score, r_lives;
    
    t_score.setFont(font);
    t_score.setString("Score:");
    t_lives.setFont(font);
    t_lives.setString("Lives:");
    t_score.setPosition(290, 10);
    t_lives.setPosition(0, 10);
    r_score.setFont(font);
    r_lives.setFont(font);
    r_score.setPosition(100, 10);
    r_lives.setPosition(400, 10);
    r_score.setColor(sf::Color::Red);
    r_lives.setColor(sf::Color::Red);
    r_score.setCharacterSize(20);
    r_lives.setCharacterSize(20);
   
    // Game loop
    while (window.isOpen()) {
        //Update elasped
        elapsed += clock.restart().asSeconds(); 
        //Handle events
        usleep(3000);
        
       constantMovement(window, velocity, playerPosition, player, elapsed);
       pelletCollision(pellets, counter, ifcollected, score, player);
       
       r_score.setString(to_string(score));
       r_lives.setString(to_string(lives));
        
        window.clear();
        for (int i = 0; i < counter; i++)
        {
            if (!ifcollected[i])
              window.draw(pellets[i]);
        }
     
        Sprite map(texture);
        window.draw(map);
        window.draw(player);
        window.draw(r_score);
        window.draw(r_lives);
        window.draw(t_score);
        window.draw(t_lives);
        window.display();
    }

    return 0;

}
