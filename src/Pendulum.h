#ifndef PENDULUM_H
#define PENDULUM_H

#include "constants.h"
#include <SFML/Graphics.hpp>
#include <cmath>

class pendulum: public sf::Sprite{
private:
    //Params defining the state of pendulum
    float angle, length, angularAccel, angularVel, mass;
    float posX, posY;
    bool hold = false;
    bool moving = false;

    //Render Objects
    sf::RenderTexture textr;
    sf::Vertex rodVertices[2];
    sf::VertexBuffer vb;
    sf::CircleShape bob;

    //Functions
    void updatexy();
    bool bobclicked(sf::Vector2i mousePos);

public:
    //Constructors
    pendulum(float length, float mass, float angle);
    void setupRenderobjects(float width, float height);


    void update();
    void render();


    void changestate();
    void movebob(sf::Vector2i mousePos);
    void clicked(sf::Vector2i mousePos);
};


#endif // PENDULUM_H
