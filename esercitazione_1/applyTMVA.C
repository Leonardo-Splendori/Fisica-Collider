#include <iostream>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TROOT.h"

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

using namespace TMVA;

// .L applyMVA.C
// applyMVA("BDT")
// applyMVA("Fisher")
// applyMVA("LD")
void applyMVA(TString method){

  TCanvas *c1 = new TCanvas("c1", "c1", 1000, 1000);
  c1->Divide(2, 1);

   //---------------------------------------------------------------
   TMVA::Tools::Instance();
   TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );    

   Float_t official_mv2;
   Float_t ip3d_pb;
   Float_t ip3d_pc;
   Float_t ip3d_pu;
   Float_t jf_m;
   Int_t label;

   Int_t num=0;
   Int_t den=0;

   // --> Configure reader (same variables, in the same order as in the training) <--
   reader->AddVariable("ip3d_pb", &ip3d_pb);
   reader->AddVariable("ip3d_pc", &ip3d_pc);
   reader->AddVariable("ip3d_pu", &ip3d_pu);
   reader->AddVariable("jf_m",    &jf_m);
   
   // Loading config. files
   TString dir    = "dataset/weights/";
   TString prefix = "TMVAClassificationCategory";
   TString methodName = method + TString(" method");
   TString weightfile = dir + prefix + TString("_") + method + TString(".weights.xml");
   reader->BookMVA( methodName, weightfile ); 

   // Reading data
   TFile*  input   = new TFile("FlavTag.root");
   TTree*  theTree = (TTree*) input->Get("FlavTag");
   
   // --> Access to Tree variables (same name used in the reader) <--
   theTree->SetBranchAddress("mv2",&official_mv2);   
   theTree->SetBranchAddress("ip3d_pb",&ip3d_pb);
   theTree->SetBranchAddress("ip3d_pc",&ip3d_pc);
   theTree->SetBranchAddress("ip3d_pu",&ip3d_pu);
   theTree->SetBranchAddress("jf_m",&jf_m);
   theTree->SetBranchAddress("label",&label);

   // --> Define histograms to check mva performance <--
   // s == signal ; b == background
   TH1F *hMVA = new TH1F( "MVA_"+method, "MVA_"+method, 100, -1, 1);
   TH1F *hmv2 = new TH1F( "official_mv2", "official_mv2", 100, -1, 1);      
   TH1F *hs   = new TH1F( "hs", "hs", 100, -1.5, 2.5);
   TH1F *hb   = new TH1F( "hb", "hb", 100, -1.5, 2.5);

   for (Long64_t ievt=0; ievt<theTree->GetEntries();ievt++) {
     
      theTree->GetEntry(ievt);

      // mva_val -> value of the discriminant variable for this event      
      Float_t mva_val = reader->EvaluateMVA(methodName);

      // distribution of the MVA score
      hMVA->Fill(mva_val);
      hmv2->Fill(official_mv2);
      
      // How does mva_val compare with the official MV2 classifier? 
      // The mv2 score could be saved in the root file below for further comparisons
      
      // same distribution with truth label
      if (label == 5)
	hs->Fill(mva_val);
      else if (label == 0)
	hb->Fill(mva_val);
   }

   c1->cd(1);
   hMVA->Draw();   
   // --> Compare results
   c1->cd(2);
   hb->Draw(); hs->Draw("SAME"); hs->SetLineColor(2);
   
   TFile *output = TFile::Open("MVA_plots_" + method + ".root", "RECREATE");
   output->cd();
   
   hs->Write();
   hb->Write();
   hmv2->Write();
   
   output->Close();

} 
