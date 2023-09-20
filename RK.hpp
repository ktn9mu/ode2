// generic solvers for linear first order ODE
// for convenience these functions return a graph of y(x)
#pragma once 

#include <TGraph.h>

// generic fcn pointer for a linear differential equation, f = y'(x,y)
// double (*f)(double x, double y)
// The equation has one independent variable (x)
// and a single dependent variable (y)
// y0: initial condition
// nsteps, x0, xmax are used to set the range and the step size
TGraph RK1Solve(double (*f)(double x, double y), double y0,
		int nsteps, double x0, double xmax);


TGraph RK2Solve(double (*f)(double x, double y), double y0,
		int nsteps, double x0, double xmax);

