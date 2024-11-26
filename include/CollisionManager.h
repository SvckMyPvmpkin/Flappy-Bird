#pragma once
#include "Bird.h"
#include "Starbucks.h"

class CollisionManager {
public:
    static bool checkCollisions(const Bird* bird, const Pipe& pipe) {
        if (!bird) return false;
        
        auto birdBounds = bird->getBounds();
        auto pipeBounds = pipe.getBounds();
        
        return birdBounds.intersects(pipeBounds[0]) || 
               birdBounds.intersects(pipeBounds[1]);
    }

    static bool checkWindowBounds(const Bird* bird, float windowHeight) {
        if (!bird) return false;
        
        auto birdRect = bird->getRect();
        return birdRect.top < 0 || birdRect.top + birdRect.height > windowHeight;
    }
};
