# Week 9 OpenFrameworks

In this exercise, I created **my own Boid class**(class MyBoid) with more features and implementations, in addition to writing an inherited class(Plane). I also created **two flocking systems** and implemented **mouse interaction.**

The example videos are documented and saved in the folder. The number on the video name indicates the developing progress.

- `Class Plane` is a class inherited from `Class Boid`. I adjusted the variables in Plane.
- `Class MyBoid` is the one I re-wrote based on the Boid class. I added some variables, and refined a few original functions. My flocking systems are based on this class.
- - Add acceleration, color variables
  - Add `seek()`, `setVelocity()`, `setColor()`, `applyForce()` functions
  - Add `flock()` function to wrap up the separate, cohesion, and alignment functions
  - Change the Wall() function. Instead of bouncing around, a vehicle(Boid) will appear to the other side of the window when touching one side. The function is called `checkWalls()`.
  - Modify the `separation()`, `cohesion()`, and `alignment()` function. Add check statement, for example, only when count > 0 the average force would be calculated. 
- Add **mouse interactions**: mouse following and clicking explosion.
- Create **two flocking systems**, which they are separating themselves from another group. I wrote another separateNeareast() function to calculate the nearest Boid and keep one Boid from that neareast one. It is working with the separate() function.

