#ifndef IOBJECT_H
#define IOBJECT_H

#include <SDL.h>
class IObject
{
    public:
        virtual void Draw() = 0;
        virtual void Update(float dt) = 0;
        virtual void Clean() = 0;

    protected:

    private:
};

#endif // IOBJECT_H
