#include "TLegend.h"
#include "TFile.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TH1F.h"

void compare_mTop(){
    //Retrieval of all the mass plots after the kinematic fit for the MC with known mTop
    TFile *f176 = TFile::Open("outFile_m176.root");
    TH1F* h176 = (TH1F*)f176->Get("h_mt");
    h176->SetName("mt176");
    h176->SetLineWidth(2);
    h176->SetLineColor(kRed);
    
    TFile *f174 = TFile::Open("outFile_m174.root");
    TH1F* h174 = (TH1F*)f174->Get("h_mt");
    h174->SetName("mt174");
    h174->SetLineWidth(2);
    h174->SetLineColor(kOrange);
    
    //...
    //...
    
    TFile *f166 = TFile::Open("outFile_m166.root");
    TH1F* h166 = (TH1F*)f166->Get("h_mt");
    h166->SetName("mt166");
    h166->SetLineWidth(2);
    h166->SetLineColor(kMagenta);

    //Retrieval of mass  after the kinematic fit for pseudodata of unknown mTop
    TFile *f_pseudoData = TFile::Open("outFile_pseudoData.root");
    TH1F* h_pseudoData = (TH1F*)f_pseudoData->Get("h_mt");
    h_pseudoData->SetName("mt_pseudoData");
    h_pseudoData->SetLineWidth(3);
    h_pseudoData->SetLineStyle(2);


    //Drawing templates with different colors for visual comparison
    TCanvas* c = new TCanvas("c","c");
    h_pseudoData->Draw("e0");
    h166->Draw("sames");
    //...
    //...

    h176->Draw("sames");

    //Statistical comparison with chi2
    TGraph* mTop_chi2 = new TGraph(6);
    mTop_chi2->SetPoint(0, 166, h_pseudoData->Chi2Test(h166,"UUPCHI2OFUF"));
    //...
    //...
    mTop_chi2->SetPoint(5, 176, h_pseudoData->Chi2Test(h176,"UUPCHI2OFUF"));
    TCanvas* chi2_cv = new TCanvas("chi2_cv","chi2_cv");
    mTop_chi2->Draw("AL*");
    
}
