#include "RK.hpp"

TGraph RK1Solve(double (*f)(double x, double y), double y0,
		int nsteps, double x0, double xmax){
  
  double h=(xmax-x0)/nsteps;     // step size
  double x=x0;                   // independent variable
  
  double y=y0;                   // dependent variable to plot vs x
  TGraph tg;
  tg.SetPoint(0,x0,y0);          // initial condition
	      
  double k1;
  for (int i=0; i<nsteps-1; i++){
    k1 = h*f(x,y);
    y = y+k1;
    x+=h;
    tg.SetPoint(i+1,x,y);
  }
  return tg;
}


TGraph RK2Solve(double (*f)(double x, double y), double y0,
		 int nsteps, double x0, double xmax){

  double h=(xmax-x0)/nsteps;     // step size
  double x=x0;                   // independent variable
  
  double y=y0;                   // dependent variable to plot vs x
  TGraph tg;
  tg.SetPoint(0,x0,y0);          // initial condition
	      
  double k1,k2;
  for (int i=0; i<nsteps-1; i++){
    k1 = h*f(x,y);
    k2 = h*f(x+h/2,y+k1/2);
    y  = y + k2;
    x+=h;
    tg.SetPoint(i+1,x,y);
  }
  return tg;
}

TGraph RK4Solve(double (*f)(double x, double y), double y0,
                int nsteps, double x0, double xmax){

    double h = (xmax - x0)/nsteps;
    double x = x0;
    double y = y0;

    TGraph tg;
    tg.SetPoint(0, x, y);

    for(int i=0; i<nsteps; i++){
        double k1 = h * f(x, y);
        double k2 = h * f(x + h/2.0, y + k1/2.0);
        double k3 = h * f(x + h/2.0, y + k2/2.0);
        double k4 = h * f(x + h, y + k3);

        y = y + (k1 + 2*k2 + 2*k3 + k4)/6.0;
        x = x + h;

        tg.SetPoint(i+1, x, y);
    }
    return tg;
}
