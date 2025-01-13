# Problem 3.1 Comparing Euler Algorithms

a. Model a simple harmonic oscillator for which F = -kx. Choose units such that
   k=1 and m=1. Determine the numerical error in the position of the simple harmonic 
   oscillator after the particle has evolved for several cycles. Is the original
   Euler algorithm stable for this system?

  Euler algorithm
   v(t+dt) = v(t) + a(t)*dt
   y(t+dt) = y(t) + v(t)*dt

b. Repeat part a using the Euler-Cromer algorithm.

  Euler-Cromer algorithm
   v(t+dt) = v(t) + a(t)*dt
   y(t+dt) = y(t) + v(t+dt)*dt

c. Modify the program to compute the total energy E_{sho} = v^2/2 + x^2/2. How well is
   the total energy conserved for the two algorithms? Consider the quantity
   E~ = E_{sho} + (dt/2) * x * p
