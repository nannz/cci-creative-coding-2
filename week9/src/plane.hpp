//
//  plane.hpp
//  w9-artificial-life
//
//  Created by 赵楠 on 2021/4/8.
//

#ifndef plane_hpp
#define plane_hpp

#include <stdio.h>
#include <vector>
#include "ofMain.h"
#include "boid.h"

class Plane: public Boid {
protected:
    ofVec3f separation(std::vector<Plane *> &otherPlanes);
    ofVec3f cohesion(std::vector<Plane *> &otherPlanes);
    ofVec3f alignment(std::vector<Plane *> &otherPlanes);
public:
    Plane();
    void update(std::vector<Plane *> &otherPlanes, ofVec3f &min, ofVec3f &max);
    void draw();
};
#endif /* plane_hpp */
