# Computational methods
---

### Task
In the assignment we were asked to examine the application of numerical schemes for the solution of partial differential equations as discussed in the Computational Methods lectures, using C++ Object Oriented and other programming practices as discussed in the C++ lectures.

The following problem was used to demonstrate our understanding of numerical schemes and object Oriented C++.



Consider  the first order wave equation:


![alt text](http://www.sciweavers.org/download/Tex2Img_1569426162.jpg)



where u, the speed of sound, is 250m/s. Assume that a disturbance is introduced in a one-dimensional long tube of length L= 400mwith both ends closed. The imposed boundary conditions are:

![](Assets/Analitical_part1)

![](http://www.sciweavers.org/download/Tex2Img_1569427454.jpg)

The analytical solution is the following:

![](http://www.sciweavers.org/download/Tex2Img_1569430086.jpg)

![](http://www.sciweavers.org/download/Tex2Img_1569430051.jpg)

![](http://www.sciweavers.org/download/Tex2Img_1569430124.jpg)

We must use the following methods:
  + Explicit Upwind (forward time, backward space)
  + Implicit Upwind (forward time, backward space)
  + Lax-Wendorff
  + Implicit FTCS (Forward time, Central space)

we also have to Investigate the effect of various step sizes on the accuracy of the solution and required computation time using the following three scenarios
  + change in space (x) is 5 meters and the change in time (t) is 0.02 seconds
  + change in space (x) is 5 meters and the change in time (t) is 0.01 seconds
  + change in space (x) is 5 meters and the change in time (t) is 0.005 seconds

  ---
  ### how to run
  Windows:
  just make a project and put the code in and then run it, simple as that
