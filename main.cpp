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
        
        //check if user closes the window
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
        } }

       
       constantMovement(velocity, playerPosition, player, elapsed);
       pelletCollision(playerPosition, ifcollected, score);
       
       r_score.setString(to_string(score));
       r_lives.setString(to_string(lives));

       if (score == counter)
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
        window.draw(t_score);
        window.draw(t_lives);
        window.draw(r_score);
        window.draw(r_lives);
        window.display();
    }

    //win screen
    sf::RenderWindow win_screen(sf::VideoMode(448, 576), "Victory!");
    Text victory_screen;
    victory_screen.setFont(font);
    victory_screen.setString("You Won!!!");
    victory_screen.setFillColor(sf::Color::Red);
    victory_screen.setPosition(win_screen.getSize().x/2 - 140, win_screen.getSize().y/2 - 50);
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
        win_screen.draw(victory_screen);
        win_screen.display();
    }


    return 0;

}
