//
//  myBoid.cpp
//  add acc variable
//  add seek, applyForce functions
//  refine the separate, cohe, and alignment functions.
//  change to ofVec2f
//  add mouse interaction.
//
//  w9-artificial-life
//  Created by 赵楠 on 2021/4/9.
//

#include "myBoid.hpp"
#include "ofMain.h"

MyBoid::MyBoid(){
    pos = ofVec2f(ofRandom(ofGetWindowWidth()/4, ofGetWindowWidth()*3/4), ofRandom(ofGetWindowHeight()/4, ofGetWindowHeight()*3/4));
    vel = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1));
    acc = ofVec2f(0, 0);
    c = ofColor(255,255,0, 210);
    
    maxSpeed = 5.0f;
    maxSteerForce = 0.5f;
    
    separationThreshold = 20;
    neighbourhoodSize = 50;
    
    rad = 3;
}

MyBoid::~MyBoid()
{}

ofVec2f MyBoid::getPosition(){
    return pos;
}
ofVec2f MyBoid::getVelocity(){
    return vel;
}
float MyBoid::getRad(){
    return rad;
}
void MyBoid::setC(ofColor &_c){
    c = _c;
}

void MyBoid::setVelocity(ofVec2f &_v){
    vel = _v;
}

void MyBoid::update(){
    vel += acc;
    vel.limit(maxSpeed);
    pos += vel;
    acc *= 0;
}

void MyBoid::applyForce(ofVec2f &_f){
    acc += _f;
}

void MyBoid::flock(std::vector<MyBoid *> &otherMyBoids){
    
    //calculate the forces
    ofVec2f aliForce = alignment(otherMyBoids);
    ofVec2f sepForce = separate(otherMyBoids);
    ofVec2f cohForce = cohesion(otherMyBoids);
    
    //give some weight
    aliForce *= 1.0;
    sepForce *= 1.5;
    cohForce *= 1.0;
    
    //apply the force to the acceleration
    applyForce(sepForce);
    applyForce(cohForce);
    applyForce(aliForce);
}

ofVec2f MyBoid::seek(ofVec2f &target){
    ofVec2f desired = target - pos;
    desired.normalize();
    desired.scale(maxSpeed);
    ofVec2f steer = desired - vel;
    steer.limit(maxSteerForce);
    return steer;
}

ofVec2f MyBoid:: separate(std::vector<MyBoid *> &otherMyBoids){
    ofVec2f steer;
    int count = 0;
    
    for (int i = 0; i < otherMyBoids.size(); i++)
    {
        if (pos.distance(otherMyBoids[i]->getPosition()) < separationThreshold && pos.distance(otherMyBoids[i]->getPosition()) > 0)
        {
            ofVec2f diff = getPosition() -otherMyBoids[i]->getPosition();
            diff.normalize();
            //the diff weights by distance
            diff/=pos.distance(otherMyBoids[i]->getPosition());
            steer += diff;
            count += 1;
        }
    }
    if(count >0) steer /= count;
    if(steer.length() >0){
        //steering = desired - vel
        steer.normalize();
        steer *= maxSpeed;
        steer -= getVelocity();
        steer.limit(maxSteerForce);
    }
    return steer;
}

//sperate from the nearest boid.
ofVec2f MyBoid::separateNearest(std::vector<MyBoid *> &otherMyBoids){
    
    float nearDis = 1000;//virable to record the neareast dis
    ofVec2f nearDiff;//virable to record the direction toward the neareast boid
    float dis = 0;
    for (int i = 0; i < otherMyBoids.size(); i++)
    {
        dis =pos.distance(otherMyBoids[i]->getPosition());
        if (dis < separationThreshold && dis > 0)
        {
            if(dis < nearDis){
                nearDis = dis;
                nearDiff =getPosition() -otherMyBoids[i]->getPosition();
            }
        }
    }
    nearDiff.normalize();
    nearDiff *= maxSpeed;
    nearDiff -= getVelocity();
    nearDiff.limit(maxSteerForce);
    return nearDiff;
}

//alignment -  Steer towards the average heading of all boids
ofVec2f MyBoid::alignment(std::vector<MyBoid *> &otherMyBoids){
    ofVec2f average(0,0);
    int count = 0;
    for (int i = 0; i < otherMyBoids.size(); i++)
    {
        if (pos.distance(otherMyBoids[i]->getPosition()) < neighbourhoodSize)
        {
            average += otherMyBoids[i]->getVelocity();
            count += 1;
        }
    }
    if(count >0){
        average /= count;
        average.normalize();
        average *= maxSpeed;
        ofVec2f steer =  average - getVelocity();
        steer.limit(maxSteerForce);
        return steer;
    }else{
        return ofVec2f(0,0);
    }
}
// move towards the centre of mass of all boids
ofVec2f MyBoid:: cohesion(std::vector<MyBoid *> &otherMyBoids){
    ofVec2f average(0,0);
    int count = 0;
    for (int i = 0; i < otherMyBoids.size(); i++)
    {
        if (pos.distance(otherMyBoids[i]->getPosition()) < neighbourhoodSize && pos.distance(otherMyBoids[i]->getPosition())>0)
        {
            average += otherMyBoids[i]->getPosition();
            count += 1;
        }
    }
    if(count>0){
        average /= count;
        return seek(average);//steer towards the average location
    }else{
        return ofVec2f(0,0);
    }

}

//the wall function is refined here. Rather than rebounding, I make it scrolling across the screen.
void MyBoid::checkWalls(){
    if(getPosition().x < -getRad()) pos.x = ofGetWidth() + rad;
    if(getPosition().y < -getRad()) pos.y = ofGetHeight() + rad;
    if(getPosition().x > ofGetWidth() + getRad()) pos.x = - rad;
    if(getPosition().y > ofGetHeight() + getRad()) pos.y = - rad;
}

void MyBoid::draw(){
    ofPushMatrix();
    ofTranslate(pos);
    ofSetColor(c);
    //because ofCircle is deprecated. So using ofDrawCircle here.
    ofDrawCircle(0,0,rad);//x,y,radius
    ofPopMatrix();
}


