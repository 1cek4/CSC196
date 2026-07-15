#pragma once
#include "Vector2.h"


namespace nu {
    struct Transform {
        Vector2 position;
        float rotation;
        Vector2 scale;
    };
};