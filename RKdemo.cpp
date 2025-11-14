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

// ---------------------------------------------------------
// Example ODEs
// ---------------------------------------------------------

// Example from original demo (unused here)
double fun1(double x, double y){
  (void)x;
  return -2*y;
}

// Another demo example (unused here)
double fun2(double x, double y){
  return -y/x - 2.0/(x*x);
}

// ---------------------------------------------------------
// NEW ODE for RK4 Assignment
// dy/dx = x - y,   y(0) = 1
// exact: y = x - 1 + 2 e^{-x}
// ---------------------------------------------------------
double fun3(double x, double y){
    return x - y;
}

// ---------------------------------------------------------
// MAIN PROGRAM
// ---------------------------------------------------------
int main(int argc, char **argv){
    TApplication theApp("App", &argc, argv);

    // Number of steps and range
    int nsteps = 60;
    double x0 = 0.0;
    double xmax = 3.0;
    double y0 = 1.0;

    // ---------------------------------------------------------
    // Solve ODE with RK1, RK2, RK4
    // ---------------------------------------------------------
    TGraph g1 = RK1Solve(fun3, y0, nsteps, x0, xmax);
    TGraph g2 = RK2Solve(fun3, y0, nsteps, x0, xmax);
    TGraph g4 = RK4Solve(fun3, y0, nsteps, x0, xmax);

    // Exact solution y = x - 1 + 2 exp(-x)
    TF1 exact("exact","x - 1 + 2*exp(-x)", x0, xmax);

    // ---------------------------------------------------------
    // Canvas setup (auto scales to screen)
    // ---------------------------------------------------------
    UInt_t dh = gClient->GetDisplayHeight()/2;   // half screen height  
    UInt_t dw = 1.1*dh;

    TCanvas *c1 = new TCanvas("c1","RK1, RK2, RK4 Comparison",dw,dh);

    // ---------------------------------------------------------
    // Style settings
    // ---------------------------------------------------------
    g1.SetLineColor(kRed);
    g2.SetLineColor(kBlue);
    g4.SetLineColor(kGreen+2);
    exact.SetLineColor(kBlack);
    exact.SetLineStyle(2);

    g1.SetLineWidth(2);
    g2.SetLineWidth(2);
    g4.SetLineWidth(2);
    exact.SetLineWidth(2);

    // ---------------------------------------------------------
    // Draw curves
    // ---------------------------------------------------------
    g1.SetTitle("RK Method Comparison for dy/dx = x - y; x; y");
    g1.Draw("AL");
    g2.Draw("L SAME");
    g4.Draw("L SAME");
    exact.Draw("L SAME");

    // ---------------------------------------------------------
    // Legend
    // ---------------------------------------------------------
    TLegend *leg = new TLegend(0.60,0.70,0.90,0.90);
    leg->AddEntry(&g1,"RK1 (Euler)","l");
    leg->AddEntry(&g2,"RK2 (Midpoint)","l");
    leg->AddEntry(&g4,"RK4","l");
    leg->AddEntry(&exact,"Exact Solution","l");
    leg->Draw();

    c1->Draw();
    c1->Update();
    c1->Print("RK4_plot.png");   // saves your plot

    // ---------------------------------------------------------
    // Write data to file (including RK4)
    // ---------------------------------------------------------
    FILE *fp = fopen("RKdemo.dat","w");

    double *x = g1.GetX();
    double *y1 = g1.GetY();
    double *y2 = g2.GetY();
    double *y4 = g4.GetY();

    fprintf(fp,"#   x        RK1         RK2         RK4         Exact\n");

    for(int i = 0; i < g1.GetN(); i++){
        fprintf(fp,"%9.4lf %12.6lf %12.6lf %12.6lf %12.6lf\n",
                x[i], y1[i], y2[i], y4[i], exact.Eval(x[i]));
    }

    fclose(fp);

    std::cout << "Wrote data to RKdemo.dat\n";
    std::cout << "Press Ctrl+C to exit\n";

    theApp.SetIdleTimer(30,".q");  
    theApp.Run();
}
