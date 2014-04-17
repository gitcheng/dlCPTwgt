//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Apr 17 14:11:44 2014 by ROOT version 5.26/00
// from TTree tr/event shape
// found on file: /nfs/farm/babar/AWG131/TDBC/tomo/reduced_ntuples/reduced_ntuples_SP1237/SJM_SP1237_Run1_R26b_reduced.root
//////////////////////////////////////////////////////////

#ifndef InTuple_h
#define InTuple_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class InTuple {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           lowerID;
   Int_t           upperID;
   Float_t         trueDt;
   Int_t           nmc;
   Int_t           mcLund[250];   //[nmc]
   Int_t           mothIdx[250];   //[nmc]
   Int_t           dauIdx[250];   //[nmc]
   Int_t           dauLen[250];   //[nmc]
   Int_t           imc1;
   Int_t           imc2;
   Int_t           B1mc;
   Int_t           B2mc;

   // List of branches
   TBranch        *b_lowerID;   //!
   TBranch        *b_upperID;   //!
   TBranch        *b_trueDt;   //!
   TBranch        *b_nmc;   //!
   TBranch        *b_mcLund;   //!
   TBranch        *b_mothIdx;   //!
   TBranch        *b_dauIdx;   //!
   TBranch        *b_dauLen;   //!
   TBranch        *b_imc1;   //!
   TBranch        *b_imc2;   //!
   TBranch        *b_B1mc;   //!
   TBranch        *b_B2mc;   //!

   InTuple(TTree *tree=0);
   virtual ~InTuple();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef InTuple_cxx
InTuple::InTuple(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
  assert(tree);
   Init(tree);
}

InTuple::~InTuple()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t InTuple::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t InTuple::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void InTuple::Init(TTree *tree)
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

   fChain->SetBranchAddress("lowerID", &lowerID, &b_lowerID);
   fChain->SetBranchAddress("upperID", &upperID, &b_upperID);
   fChain->SetBranchAddress("trueDt", &trueDt, &b_trueDt);
   fChain->SetBranchAddress("nmc", &nmc, &b_nmc);
   fChain->SetBranchAddress("mcLund", mcLund, &b_mcLund);
   fChain->SetBranchAddress("mothIdx", mothIdx, &b_mothIdx);
   fChain->SetBranchAddress("dauIdx", dauIdx, &b_dauIdx);
   fChain->SetBranchAddress("dauLen", dauLen, &b_dauLen);
   fChain->SetBranchAddress("imc1", &imc1, &b_imc1);
   fChain->SetBranchAddress("imc2", &imc2, &b_imc2);
   fChain->SetBranchAddress("B1mc", &B1mc, &b_B1mc);
   fChain->SetBranchAddress("B2mc", &B2mc, &b_B2mc);

   fChain->SetBranchStatus("*", 0);
   fChain->SetBranchStatus("lowerID", 1);
   fChain->SetBranchStatus("upperID", 1);
   fChain->SetBranchStatus("trueDt", 1);
   fChain->SetBranchStatus("nmc", 1);
   fChain->SetBranchStatus("mcLund", 1);
   fChain->SetBranchStatus("mothIdx", 1);
   fChain->SetBranchStatus("dauIdx", 1);
   fChain->SetBranchStatus("dauLen", 1);
   fChain->SetBranchStatus("imc1", 1);
   fChain->SetBranchStatus("imc2", 1);
   fChain->SetBranchStatus("B1mc", 1);
   fChain->SetBranchStatus("B2mc", 1);

   Notify();
}

Bool_t InTuple::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void InTuple::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t InTuple::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef InTuple_cxx
