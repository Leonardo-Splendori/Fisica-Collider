#include <iostream>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TROOT.h"

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

using namespace std;

void makeROC(TString method){

  TCanvas* c1 = new TCanvas("c1", "c1"); c1->SetLogy();

  TFile* f = new TFile("MVA_plots_" + method + ".root");

  TH1F* hs = NULL;
  TH1F* hb = NULL;
  f->GetObject("hs", hs);
  f->GetObject("hb", hb);

  int num=100;  
  double eff_s[100], rej_b[100];
  float low=-0.8;
  float high=2.2;
  float last=0;
  
  for (int i=0;i<num;i++) {

    float val = i*(fabs(low)+high)/num-fabs(low);

    eff_s[i] = (float)(hs->Integral(hs->GetXaxis()->FindBin(val),hs->GetXaxis()->FindBin(high)-1)/hs->Integral());
    if (hb->Integral(hb->GetXaxis()->FindBin(val),hb->GetXaxis()->FindBin(high))) {
      rej_b[i] = (float)hb->Integral()/(hb->Integral(hb->GetXaxis()->FindBin(val),hb->GetXaxis()->FindBin(high)-1));
      last = rej_b[i];
    } else
      rej_b[i] = last;
      
    
  }

  TGraph* gr = new TGraph(num,eff_s,rej_b);
  gr->Draw("AC*");
  gr->GetXaxis()->SetTitle("Signal efficiency");
  gr->GetYaxis()->SetTitle("Background rejection");  
  
}
