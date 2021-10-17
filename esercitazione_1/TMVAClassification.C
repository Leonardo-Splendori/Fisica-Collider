#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TMVA/MethodCategory.h"
#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"

void TMVAClassification(){

  // This loads the library
  TMVA::Tools::Instance();
  
  // Create a new root output file.
  TString outfileName = "TMVA.root";
  TFile* outputFile = TFile::Open(outfileName, "RECREATE" );
  
  // Create the factory object 
  TMVA::Factory *factory = new TMVA::Factory( "TMVAClassificationCategory", outputFile, "!V:!Silent:Transformations=I;D;P;G,D");

  // Create DataLoader
  TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset");
  
  // Define the input variables used for the MVA training
  // -- ADD CODE --
  // Use
  //   dataloader->AddVariable( "NomeVariabile", 'Tipo' ); // Tipo: 'F' (float) ,'I' (int)

  dataloader->AddVariable("ip3d_pb", 'F');
  dataloader->AddVariable("ip3d_pc", 'F');
  dataloader->AddVariable("ip3d_pu", 'F');
  dataloader->AddVariable("jf_m", 'F');

  TFile *input = new TFile("FlavTag.root");
  
  // You can add an arbitrary number of signal or background trees
  dataloader->AddSignalTree    ( (TTree*)input->Get("FlavTag"),  1.0);
  dataloader->AddBackgroundTree( (TTree*)input->Get("FlavTag"),  1.0);
  
  // Apply additional cuts on the signal and background samples (can be different)
  // -- ADD CODE --
  // Define cuts to select background and signal
  // b-jets == 5
  // c-jets == 4
  // light-flavour jets == 0
  TCut mycuts = "label==5";  
  TCut mycutb = "label==0";
  
  // Tell the factory how to use the training and testing events
  dataloader->PrepareTrainingAndTestTree(mycuts, mycutb, "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V" );

  // -- ADD CODE --
  // Define TMVA Methods..

  //LD
  factory->BookMethod(dataloader, TMVA::Types::kLD, "LD");

  // Fisher
  factory->BookMethod(dataloader,TMVA::Types::kFisher, "Fisher", "H:!V:Fisher:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );

  // Likelihood
  //factory->BookMethod(dataloader, TMVA::Types::kLikelihood, "Likelihood","H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmoothBkg[1]=10:NSmooth=1:NAvEvtPerBin=50" );
  
  // BDT
  factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDT","!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );

  //DL
  //factory->BookMethod(dataloader, TMVA::Types::kDL, "DNN", "Layout=BNORM,SIGMOID|128,SIGMOID|128");

  factory->TrainAllMethods();
  factory->TestAllMethods();
  factory->EvaluateAllMethods();
  
  outputFile->Close();
  
  // Analisi dei risultati
  TMVA::TMVAGui( outfileName );

}
