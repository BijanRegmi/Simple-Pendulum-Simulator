#include "Pendulum.h"

pendulum::pendulum(float length, float mass, float angle){
    this->length = length;
    this->mass = mass;
    this->angle = angle;

    angularAccel = 0;
    angularVel = 0;

}

void pendulum::setupRenderobjects(float width, float height){
    textr.create(width, height);
    this->setTexture(textr.getTexture());

    vb.create(2);
    vb.setPrimitiveType(sf::Lines);

    rodVertices[0].position = sf::Vector2f(width/2, 0.1*height);
    rodVertices[0].color = sf::Color::Black;
    rodVertices[1].color = sf::Color::Black;

    bob.setRadius(mass);
    bob.setOrigin(bob.getRadius(), bob.getRadius());
    bob.setFillColor(sf::Color::Black);
}

void pendulum::changestate(){
    hold = !hold;
}

void pendulum::update(){
    if (hold) return;

    angularAccel = -(gravity/length * std::sin(angle))/(FPS*FPS);
    angularVel += angularAccel;
    angle += angularVel;

    updatexy();
    angularVel *= damp;
}

void pendulum::render(){
    sf::Vector2f endPos = sf::Vector2f(posX*100 + rodVertices[0].position.x, posY*100 + rodVertices[0].position.y);
    rodVertices[1].position = endPos;
    vb.update(rodVertices);

    bob.setPosition(endPos);

    textr.clear(sf::Color::White);
    textr.draw(vb);
    textr.draw(bob);
    textr.display();
}

void pendulum::updatexy(){
    posX = length * std::sin(angle);
    posY = length * std::cos(angle);
}

bool pendulum::bobclicked(sf::Vector2i mousePos){
    return bob.getGlobalBounds().contains(mousePos.x, mousePos.y);
}

void pendulum::clicked(sf::Vector2i mousePos){
    if (bobclicked(mousePos)){
        hold = true;
        moving = !moving;
    }
}

void pendulum::movebob(sf::Vector2i mousePos){
    if (!moving) return;

    float delx = mousePos.x - rodVertices[0].position.x;
    float dely = mousePos.y - rodVertices[0].position.y;

    angle = std::atan(delx/dely);

    length = std::sqrt(delx*delx + dely*dely) / 100;

    angularVel = 0;

    updatexy();

}
