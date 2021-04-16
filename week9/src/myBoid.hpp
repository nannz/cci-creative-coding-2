//
//  myBoid.hpp
//  add acc variable
//  add seek, applyForce functions
//  refine the separate, cohe, and alignment functions.
//  change to ofVec2f
//  add mouse interaction.
//
//  w9-artificial-life
//  Created by 赵楠 on 2021/4/9.
//

#ifndef myBoid_hpp
#define myBoid_hpp

#include <stdio.h>
#include <vector>
#include "ofMain.h"

class MyBoid
{
private:
    ofVec2f pos;
    ofVec2f vel;
    ofVec2f acc;
    
    float maxSpeed;
    float maxSteerForce;
    float separationThreshold;
    float neighbourhoodSize;
    ofColor c;
    float rad;
public:
    MyBoid();
    ~MyBoid();
    
    ofVec2f getPosition();
    ofVec2f getVelocity();
    void setVelocity(ofVec2f &_v);
    void setC(ofColor &_c);
    float getRad();
    
    void update();
    void draw();
    
    void applyForce(ofVec2f &_f);
    void flock(std::vector<MyBoid *> &otherMyBoids);
    
    ofVec2f seek(ofVec2f &target);//return steer force
    ofVec2f separate(std::vector<MyBoid *> &otherMyBoids);
    ofVec2f alignment(std::vector<MyBoid *> &otherMyBoids);
    ofVec2f cohesion(std::vector<MyBoid *> &otherMyBoids);
    ofVec2f separateNearest(std::vector<MyBoid *> &otherMyBoids);
    void checkWalls();
    
};
#endif /* myBoid_hpp */
