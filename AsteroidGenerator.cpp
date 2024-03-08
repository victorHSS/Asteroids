#include "AsteroidGenerator.h"
#include <chrono>

AsteroidGenerator::AsteroidGenerator(int posMinX, int posMaxX, unsigned maxAsteroids):
    generator(std::chrono::system_clock::now().time_since_epoch().count()),
    dPos(posMinX,posMaxX),
    dVel(80,190),
    dModel(0,2),
    dFPS(20,60),
    dNew(0,1000),
    dDir(0,1)
{
    this->maxAsteroids = maxAsteroids;
    this->difficulty = 20;
    models[0] = new Asteroid(0,0,0,0,0);
    models[1] = new Asteroid(1,0,0,0,0);
    models[2] = new Asteroid(2,0,0,0,0);
}

AsteroidGenerator::~AsteroidGenerator()
{
    for (std::list<Asteroid*>::iterator it = asteroids.begin() ; it != asteroids.end() ; ++it)
        delete (*it);

    delete models[0];
    delete models[1];
    delete models[2];
}

const std::list<Asteroid *> &AsteroidGenerator::getAsteroids() const
{
    return asteroids;
}

bool AsteroidGenerator::init()
{

}

void AsteroidGenerator::draw()
{
    for (std::list<Asteroid*>::iterator it = asteroids.begin() ; it != asteroids.end() ; ++it)
        (*it)->draw();
}

void AsteroidGenerator::update(double seconds)
{
    if ( dNew(generator) <= difficulty && maxAsteroids > asteroids.size())
    {
        Asteroid *newAsteroid = new Asteroid();
        *newAsteroid = *models[dModel(generator)];

        newAsteroid->setPos(dPos(generator),-40);
        newAsteroid->setVelocity(dVel(generator));
        newAsteroid->setFPS(dFPS(generator));
        newAsteroid->setDirection(dDir(generator));

        asteroids.push_back(newAsteroid);
    }
    for (std::list<Asteroid*>::iterator it = asteroids.begin() ; it != asteroids.end() ; ++it)
        (*it)->update(seconds);
}

void AsteroidGenerator::explodeAsteroid(Asteroid* asteroid)
{
    asteroids.remove(asteroid);
    delete asteroid;
}

void AsteroidGenerator::setDifficulty(unsigned difficulty)
{
    this->difficulty = difficulty;
}

void AsteroidGenerator::increaseDifficulty(unsigned iDifficulty)
{
    difficulty += iDifficulty;
}

unsigned AsteroidGenerator::getDifficulty() const
{
    return difficulty;
}

