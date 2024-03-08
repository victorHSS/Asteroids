#ifndef GAMEOBJ_H_INCLUDED
#define GAMEOBJ_H_INCLUDED

class GameObj
{
    public:
        GameObj ();
        virtual ~GameObj(){};//base virtual, todos as derivadas são virtuais

        virtual bool init() = 0;
        virtual void update(double seconds) = 0;
        virtual void draw() = 0;

        //virtual void delete() = 0; //????
        void setGameObjType(unsigned type);
        unsigned getGameObjType() const;

    protected:
        unsigned objType;
};


#endif // GAMEOBJ_H_INCLUDED
