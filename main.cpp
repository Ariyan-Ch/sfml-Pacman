#include <iostream>

//#include <X11/Xlib.h>
//#undef Drawable
//#undef Window
//#undef Font
//#undef Status
//#undef Default
//#undef None

#include <SFML/Graphics.hpp>

using namespace sf;

//"-lX11"

int main(){


    RenderWindow window(VideoMode(1040,800), "Pac Man");

    while(window.isOpen()){

        window.display();
    }
    return 0;
}
