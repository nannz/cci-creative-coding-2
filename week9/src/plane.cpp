//
//  plane.cpp
//  w9-artificial-life
//
//  Created by 赵楠 on 2021/4/8.
//

#include "plane.hpp"
#include "boid.h"

Plane::Plane()
{
    separationWeight = 1.0f;
    cohesionWeight = 0.2f;
    alignmentWeight = 0.1f;
    
    separationThreshold = 15;
    neighbourhoodSize = 100;
    
    position = ofVec3f(ofRandom(ofGetWindowWidth()/2-10,ofGetWindowWidth()/2+10), ofRandom(ofGetWindowHeight()/2 -10, ofGetWindowHeight()/2+10));
    velocity = ofVec3f(ofRandom(-2, 2), ofRandom(-2, 2));
}

ofVec3f Plane::separation(std::vector<Plane *> &otherPlanes)
{
    // finds the first collision and avoids that
    // should probably find the nearest one
    // can you figure out how to do that?
    for (int i = 0; i < otherPlanes.size(); i++)
    {
        if(position.distance(otherPlanes[i]->getPosition()) < separationThreshold)
        {
            ofVec3f v = position -  otherPlanes[i]->getPosition();
            v.normalize();
            return v;
        }
    }
}

ofVec3f Plane::cohesion(std::vector<Plane *> &otherPlanes)
{
    ofVec3f average(0,0,0);
    int count = 0;
    for (int i = 0; i < otherPlanes.size(); i++)
    {
        if (position.distance(otherPlanes[i]->getPosition()) < neighbourhoodSize)
        {
            average += otherPlanes[i]->getPosition();
            count += 1;
        }
    }
    average /= count;
    ofVec3f v =  average - getPosition();
    v.normalize();
    return v;
}

ofVec3f Plane::alignment(std::vector<Plane *> &otherPlanes)
{
    ofVec3f average(0,0,0);
    int count = 0;
    for (int i = 0; i < otherPlanes.size(); i++)
    {
        if (position.distance(otherPlanes[i]->getPosition()) < neighbourhoodSize)
        {
            average += otherPlanes[i]->getVelocity();
            count += 1;
        }
    }
    average /= count;
    ofVec3f v =  average - velocity;
    v.normalize();
    return v;
}
void Plane::update(std::vector<Plane *> &otherPlanes, ofVec3f &min, ofVec3f &max)
{
    velocity += separationWeight*separation(otherPlanes);
    velocity += cohesionWeight*cohesion(otherPlanes);
    velocity += alignmentWeight*alignment(otherPlanes);
    
    walls(min, max);
    position += velocity;
}

void Plane::draw()
{
    ofSetColor(100, 0, 100);
    ofCircle(position.x, position.y, 10);
}
