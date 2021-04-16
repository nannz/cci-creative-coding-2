

#ifndef _BOID
#define _BOID
#include <vector>
#include "ofMain.h"

class Boid
{
//I change the access specifier from private to protected. so that the child class can access the variables
protected:
	ofVec3f position;
	ofVec3f velocity;
	
	float separationWeight;
	float cohesionWeight;
	float alignmentWeight;
	
	float separationThreshold;
	float neighbourhoodSize;
	
	ofVec3f separation(std::vector<Boid *> &otherBoids);
	ofVec3f cohesion(std::vector<Boid *> &otherBoids);
	ofVec3f alignment(std::vector<Boid *> &otherBoids);
	

public:	
	Boid();
	Boid(ofVec3f &pos, ofVec3f &vel);
	
	~Boid();
	
	ofVec3f getPosition();
	ofVec3f getVelocity();
	
	
	float getSeparationWeight();
	float getCohesionWeight();
	float getAlignmentWeight();
	
	float getSeparationThreshold();
	float getNeighbourhoodSize();
	
	void setSeparationWeight(float f);
	void setCohesionWeight(float f);
	void setAlignmentWeight(float f);
	
	void setSeparationThreshold(float f);
	void setNeighbourhoodSize(float f);
	
	void update(std::vector<Boid *> &otherBoids, ofVec3f &min, ofVec3f &max);
	
	void walls(ofVec3f &min, ofVec3f &max);
	
	void draw();
};

#endif
