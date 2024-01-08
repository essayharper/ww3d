#ifndef WW3D_ACTOR_H
#define WW3D_ACTOR_H

#include "vector.h"

typedef enum {
    ACTOR_DEFAULT,
} ActorType;

class actor {
    public: 

    virtual void Draw() = 0;
    virtual void Calc() = 0;

    ActorType type;
    friend class player;

    private:
    vec3 position;
    vec3 rotation;
    vec3 scale;

    bool drawFlag, calcFlag;
};
#endif //WW3D_ACTOR_H