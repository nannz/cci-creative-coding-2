#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    int screenW = ofGetWindowWidth();//ofGetScreenWidth();
    int screenH = ofGetWindowHeight();//ofGetScreenHeight();

    ofBackground(10,10,10);
    
    // set up the boids
    for (int i = 0; i < 50; i++){
        myBoids.push_back(new Boid());
    }
    for (int i = 0; i < 10; i++){
        myPlanes.push_back(new Plane());
    }
    //initialize two flocks based on MyBoid() class;
    for (int i = 0; i < 50; i++){
        myVehicles.push_back(new MyBoid());
        myVehicles2.push_back(new MyBoid());
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    ofVec3f min(0, 0);
    ofVec3f max(ofGetWidth(), ofGetHeight());
    ofVec2f mouseVec = ofVec2f(ofGetMouseX(),ofGetMouseY());
    
    //uncomment below to update the original Boid class and the inherited Plane class
//    for (int i = 0; i < myBoids.size(); i++)
//    {myBoids[i]->update(myBoids, min, max);}
//
//    for (int i = 0; i < myPlanes.size(); i++)
//    {myPlanes[i]->update(myPlanes, min, max);}
    
    //the first flock system update.
    //it will be attracted by the mouse position.
    ofVec2f sepSteer;//create a virable for calculating the steer force on separation.
    ofVec2f sepNearSteer;//create a virable for calculating the steer force on the neareast separation force.
    for (int i = 0; i < myVehicles.size(); i++)
    {
        //calculate the mouse direction and apply the corresponding seek force.
        ofVec2f seekForce = myVehicles[i]->seek(mouseVec);
        myVehicles[i]->applyForce(seekForce);
        
        //the flock and check edge functions.
        myVehicles[i]->flock(myVehicles);
        myVehicles[i]->checkWalls();
        
        //be aware of another group of myVehicles.
        sepSteer = myVehicles[i]->separate(myVehicles2);
        sepNearSteer =myVehicles[i]->separateNearest(myVehicles2);
        myVehicles[i]->applyForce(sepSteer);
        myVehicles[i]->applyForce(sepNearSteer);
        
        myVehicles[i]->update();
    }
    //the second flock system. It will just wander around. But keep themselves from another group of flocking system.
    for (int i = 0; i < myVehicles2.size(); i++)
    {
        //the flock and check edge functions.
        myVehicles2[i]->flock(myVehicles2);
        myVehicles2[i]->checkWalls();
        
        //be aware of another group of myVehicles.
        //be aware of another group of myVehicles.
        sepSteer = myVehicles2[i]->separate(myVehicles);
        sepNearSteer =myVehicles2[i]->separateNearest(myVehicles);
        myVehicles2[i]->applyForce(sepSteer);
        myVehicles2[i]->applyForce(sepNearSteer);
        
        myVehicles2[i]->update();
    }

    
}

//--------------------------------------------------------------
void ofApp::draw(){
    //uncomment below to draw the original Boid class and the inherited Plane class
//    for (int i = 0; i < myBoids.size(); i++)
//    {myBoids[i]->draw();}
//
//    for (int i = 0; i < myPlanes.size(); i++)
//    {myPlanes[i]->draw();}
    
    //draw the two flocking systems
    for (int i = 0; i < myVehicles.size(); i++)
    {
        myVehicles[i]->draw();
    }
    for (int i = 0; i < myVehicles2.size(); i++)
    {
        myVehicles2[i]->draw();
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
//when click the mouse. A force pointing the negative direction of the mouse towards each vehicle will be applied, creating an effect of explosion. The color of the vehicles will change as well.
void ofApp::mouseReleased(int x, int y, int button){
    ofColor newC =ofColor(ofRandom(200, 255),ofRandom(200, 255),ofRandom(200, 255), 210);
    ofVec2f mouseVec = ofVec2f(ofGetMouseX(),ofGetMouseY());
    ofVec2f zero = ofVec2f(0,0);
    for (int i = 0; i < myVehicles.size(); i++)
    {
        myVehicles[i]->setC(newC);
        //explosion effect
        ofVec2f diff =myVehicles[i]->getPosition() - mouseVec;
        diff.normalize();
        diff *= 10.0;
        myVehicles[i]->setVelocity(zero);
        myVehicles[i]->applyForce(diff);
    }
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
