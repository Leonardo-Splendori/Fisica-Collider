#include "TLegend.h"
#include "TFile.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TF1.h"

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
    TFile *f172 = TFile::Open("outFile_m172.root");
    TH1F* h172 = (TH1F*)f172->Get("h_mt");
    h172->SetName("mt172");
    h172->SetLineWidth(2);
    h172->SetLineColor(kBlue);

    TFile *f170 = TFile::Open("outFile_m170.root");
    TH1F* h170 = (TH1F*)f170->Get("h_mt");
    h170->SetName("mt170");
    h170->SetLineWidth(2);
    h170->SetLineColor(kViolet);

    TFile *f168 = TFile::Open("outFile_m168.root");
    TH1F* h168 = (TH1F*)f168->Get("h_mt");
    h168->SetName("mt168");
    h168->SetLineWidth(2);
    h168->SetLineColor(kGreen);
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
    h168->Draw("sames");
    h170->Draw("sames");
    h172->Draw("sames");
    h174->Draw("sames");
    //...

    h176->Draw("sames");

    //Statistical comparison with chi2
    TGraph* mTop_chi2 = new TGraph(6);
    mTop_chi2->SetPoint(0, 166, h_pseudoData->Chi2Test(h166,"UUPCHI2OFUF"));
    //...
    mTop_chi2->SetPoint(1, 168, h_pseudoData->Chi2Test(h168,"UUPCHI2OFUF"));
    mTop_chi2->SetPoint(2, 170, h_pseudoData->Chi2Test(h170,"UUPCHI2OFUF"));
    mTop_chi2->SetPoint(3, 172, h_pseudoData->Chi2Test(h172,"UUPCHI2OFUF"));
    mTop_chi2->SetPoint(4, 174, h_pseudoData->Chi2Test(h174,"UUPCHI2OFUF"));
    //...
    mTop_chi2->SetPoint(5, 176, h_pseudoData->Chi2Test(h176,"UUPCHI2OFUF"));
    TCanvas* chi2_cv = new TCanvas("chi2_cv","chi2_cv");

    TF1* g = new TF1("g", "[1]*(x-[0])^2 + [2]");
    g->SetParameter(0, 180);
    mTop_chi2->Fit("g");
    
    mTop_chi2->Draw("AL*");
    
}
