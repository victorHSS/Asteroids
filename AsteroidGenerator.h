#ifndef ASTEROIDGENERATOR_H_INCLUDED
#define ASTEROIDGENERATOR_H_INCLUDED

#include "Asteroid.h"
#include "GameObj.h"

#include <list>
#include <random>

class AsteroidGenerator : public GameObj
{
    public:
        AsteroidGenerator() = delete;
        AsteroidGenerator(const AsteroidGenerator &) = delete;
        AsteroidGenerator &operator=(const AsteroidGenerator &) = delete;

        AsteroidGenerator(int posMinx, int posMaxX, unsigned maxAsteroids);
        virtual ~AsteroidGenerator();

        virtual bool init();
        virtual void update(double seconds);
        virtual void draw();

        const std::list<Asteroid *> &getAsteroids() const;
        void explodeAsteroid(Asteroid *asteroid);

        void setDifficulty(unsigned difficulty);
        void increaseDifficulty(unsigned iDifficulty);
        unsigned getDifficulty() const;

    private:
        std::list<Asteroid *> asteroids;
        unsigned maxAsteroids;
        Asteroid *models[3];
        unsigned difficulty;

        std::default_random_engine generator;
        std::uniform_int_distribution<int> dPos;
        std::uniform_int_distribution<int> dVel;
        std::uniform_int_distribution<int> dModel;
        std::uniform_int_distribution<int> dFPS;
        std::uniform_int_distribution<int> dNew;
        std::uniform_int_distribution<int> dDir;
};


#endif // ASTEROIDGENERATOR_H_INCLUDED
