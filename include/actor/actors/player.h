#ifndef WW3D_PLAYER_H
#define WW3D_PLAYER_H

#include "actor.h"
#include <citro3d.h>

class player : public actor {
    public:

    C3D_Mtx GetViewMtx() const;
    private:

    // View Matrix
    C3D_Mtx viewMtx;
};
#endif //WW3D_PLAYER_H