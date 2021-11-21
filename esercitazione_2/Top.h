#ifndef Top_h
#define Top_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class Top {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           njet;
   Float_t         jetpt[4];   //[njet]
   Float_t         jeteta[4];   //[njet]
   Float_t         jetphi[4];   //[njet]
   Int_t           jetlabel[4];   //[njet]
   Int_t           jettruth[4];   //[njet]
   Float_t         jettruthpt[4];   //[njet]
   Float_t         mupt;
   Float_t         mueta;
   Float_t         muphi;
   Float_t         metpt;
   Float_t         metphi;
   Float_t         nutruthpt;
   Float_t         nutruthphi;
   Float_t         nutruthpz;
   
   // List of branches
   TBranch        *b_njet;   //!
   TBranch        *b_jetpt;   //!
   TBranch        *b_jeteta;   //!
   TBranch        *b_jetphi;   //!
   TBranch        *b_jetlabel;   //!
   TBranch        *b_jettruth;   //!
   TBranch        *b_jettruthpt;   //!
   TBranch        *b_mupt;   //!
   TBranch        *b_mueta;   //!
   TBranch        *b_muphi;   //!
   TBranch        *b_metpt;   //!
   TBranch        *b_metphi;   //!
   TBranch        *b_nutruthpt;   //!
   TBranch        *b_nutruthphi;   //!
   TBranch        *b_nutruthpz;   //!
   
   Top(TTree *tree=0);
   virtual ~Top();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   void Loop(string outFileStr, bool isMC);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Top_cxx
Top::Top(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("TopMass.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("TopMass.root");
      }
      f->GetObject("Top",tree);

   }
   Init(tree);
}

Top::~Top()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Top::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Top::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Top::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("njet", &njet, &b_njet);
   fChain->SetBranchAddress("jetpt", jetpt, &b_jetpt);
   fChain->SetBranchAddress("jeteta", jeteta, &b_jeteta);
   fChain->SetBranchAddress("jetphi", jetphi, &b_jetphi);
   fChain->SetBranchAddress("jetlabel", jetlabel, &b_jetlabel);
   fChain->SetBranchAddress("jettruth", jettruth, &b_jettruth);
   fChain->SetBranchAddress("jettruthpt", jettruthpt, &b_jettruthpt);
   fChain->SetBranchAddress("mupt", &mupt, &b_mupt);
   fChain->SetBranchAddress("mueta", &mueta, &b_mueta);
   fChain->SetBranchAddress("muphi", &muphi, &b_muphi);
   fChain->SetBranchAddress("metpt", &metpt, &b_metpt);
   fChain->SetBranchAddress("metphi", &metphi, &b_metphi);
   fChain->SetBranchAddress("nutruthpt", &nutruthpt, &b_nutruthpt);
   fChain->SetBranchAddress("nutruthphi", &nutruthphi, &b_nutruthphi);
   fChain->SetBranchAddress("nutruthpz", &nutruthpz, &b_nutruthpz);
   Notify();
}

Bool_t Top::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Top::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Top::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Top_cxx
