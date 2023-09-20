#include "RK.hpp"
#include "TROOT.h"
#include "TApplication.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TGClient.h"
#include "TF1.h"
#include "TCanvas.h"
#include <iostream>
#include <cstdio>

using namespace std;

// differential equation to be solved
double fun1(double x, double y){
  (void)x;              // prevent unused variable warning
  return -2*y;          // f = y'(x,y) = -2 * y(x)  
}                       // solution: y(x) = 3 * exp(-2*x) ; with initial condition y(0)=3

double fun2(double x, double y){
  return -y/x-2/(x*x);  // f = y'(x,y) = -y(x)/x - 2/x^2 
}                       // -2*log(|x|)/x+2/x  ; with initial condition y(0)=2

int main(int argc, char **argv){
  TApplication theApp("App", &argc, argv); // init ROOT App for displays

  // solve our DEQ using RK1 or RK2 methods!
  // Two examples are given.  Choose a function for testing
  TGraph tg1=RK1Solve(fun1,3,30,0,3);                     // initial condition y(0)=3
  TGraph tg2=RK2Solve(fun1,3,30,0,3);
  TF1 fun_sol=TF1("fun_sol","3*exp(-2*x)",0,3);           // exact solution
  //TGraph tg1=RK1Solve(fun2,2,100,1,100);                // initial condition y(1)=2
  //TGraph tg2=RK2Solve(fun2,2,100,1,100);
  //TF1 fun_sol=TF1("fun_sol","-2*log(x)/x+2/x",1,100);   // exact solution

  // ******************************************************************************
  // ** this block is useful for supporting both high and std resolution screens **
  UInt_t dh = gClient->GetDisplayHeight()/2;   // fix plot to 1/2 screen height  
  //UInt_t dw = gClient->GetDisplayWidth();
  UInt_t dw = 1.1*dh;
  // ******************************************************************************

  TCanvas *c1 = new TCanvas("c1","DEQ solutions",dw,dh);

  tg1.SetMarkerSize(0.015*dh/8);  // size scale: 1 = 8 pixels, so here we choose the size to be 1.5% of the window height
  tg2.SetMarkerSize(0.015*dh/8);
  tg1.SetMarkerStyle(kFullTriangleUp);
  tg2.SetMarkerStyle(kFullTriangleDown);
  tg1.SetMarkerColor(kRed);
  tg2.SetMarkerColor(kGreen-2);
  fun_sol.SetLineColor(kBlack);
  fun_sol.SetLineStyle(2);
  
  // plot the results
  tg1.SetTitle("ODE demo;x;y");
  tg1.Draw("AP");
  tg2.Draw("P");
  fun_sol.Draw("same");
  
  TLegend *tl = new TLegend(0.6,0.7,0.9,0.9);
  tl->AddEntry(&tg1,"RK1 Solution","p");
  tl->AddEntry(&tg2,"RK2 Solution","p");
  tl->AddEntry(&fun_sol,"Exact Solution","l");
  tl->Draw();
  c1->Draw();
  c1->Update();
  c1->Print("OED_cpp.png");

  // retreive the data from the graphs and write to a file
  FILE *fp=fopen("RKdemo.dat","w");
  double *x, *y1, *y2;
  x=tg1.GetX();
  y1=tg1.GetY();
  y2=tg2.GetY();
  fprintf(fp,"#%8s %9s %9s %9s\n","x","RK1","RK2","Exact");
  for (int i=0; i<tg1.GetN(); i++){
    fprintf(fp,"%9.4lf %9.4lf %9.4lf %9.4lf\n",x[i],y1[i],y2[i],fun_sol.Eval(x[i]));
  }
  fclose(fp);
  
  cout << "Press ^c to exit" << endl;
  theApp.SetIdleTimer(30,".q");  // set up a failsafe timer to end the program  
  theApp.Run();
}

