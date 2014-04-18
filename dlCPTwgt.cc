#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>
#include "TH1D.h"

#define InTuple_cxx
#include "InTuple.h"

// Constants in Monte Carlo
#define DeltaM 0.489    // unit is ps^{-1}
#define cTau 0.462      // B0 lifetime c*tau in mm
#define cLight 0.299792458 // speed of light mm/ps 
#define Gamma_d cLight/cTau  // Decay rate Gamma_d = 1/tau


using namespace std;

# ifndef __CINT__
int print_message() {
  cout << "Usage:" << endl;
  cout << "   dlCPTwgt [options]" << endl;
  cout << "     options: \n"
       << "     -h, --help : print this message.\n"
       << "     --qop2 <value> : value of |q/p|^2. Default = 1.0 \n"
       << "     --dgog <value> : value of DeltaGamma/Gamma. Default = 0.0 \n"
       << "     --rez <value> : value of Re(z). Defalut = 0.0 \n"
       << "     --rmz <value> : value of Im(z). Defalut = 0.0 \n"
       << "     -i <path> : input root file path/name \n"
       << "     -t <value> : TTree name\n"
       << "     -o <path> : output file path/name \n"
       << "     -c <path> : common path to input and output files \n"
       << endl;
  return 0;
}


// Can option be found?
bool find_opt(string opt, int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    if (opt == argv[i]) return true;
  }
  return false;
}

// Return the value following the option specified by the argument opt.
string parse_opts(string opt, int argc, char *argv[], string default_value = "") {
  for (int i = 1; i < argc; i++) {
    if (opt == argv[i]) return argv[i+1];
  }
  return default_value;
}

// decay rate, without the exponential factor
double decay_rate(int q1, int q2, double dt, double qop2 = 1,
		  double dG = 0, double rez = 0, double imz = 0) {

  double fcom = 1;
  // coefficients of cosh, cos, sinh, sin terms
  double fcosh(0.5), fcos(-0.5), fsinh(0.0), fsin(0.0);
 
  if (q1 == q2) {
    // |1-z^2|
    double omz2 = sqrt((1-rez*rez+imz*imz)*(1-rez*rez+imz*imz) + 4*rez*rez*imz*imz);
    if (q1 > 0) fcom = 1.0/qop2 * omz2;
    else        fcom = qop2 * omz2;
  } else {
    fcosh = 0.5 * (1 + rez*rez + imz*imz);
    fcos =  0.5 * (1 - rez*rez - imz*imz);
    fsinh = -rez;
    fsin  = +imz;
  }
  
  return fcom * (fcosh * cosh(dG*dt/2) + fcos * cos(DeltaM*dt)
		 + fsinh * sinh(dG*dt/2) + fsin * sin(DeltaM*dt));
}


int main(int argc, char *argv[]) {

  if (argc == 1 || find_opt("-h", argc, argv) || find_opt("--help", argc, argv))
    return print_message();

  string commonpath = parse_opts("-c", argc, argv, "");
  string inname = parse_opts("-i", argc, argv);
  string treename = parse_opts("-t", argc, argv, "tr");
  string outname = parse_opts("-o", argc, argv);
  double qop2 = atof(parse_opts("--gop2", argc, argv, "1.0").c_str());
  double dGoG = atof(parse_opts("--dgog", argc, argv, "0.0").c_str());
  double rez = atof(parse_opts("--rez", argc, argv, "0.0").c_str());
  double imz = atof(parse_opts("--imz", argc, argv, "0.0").c_str());
  double dG = dGoG * Gamma_d;

  if (commonpath.length() > 0 && commonpath[commonpath.length()-1] != '/') {
    commonpath = commonpath + "/";
  }
  inname = commonpath + inname;
  outname = commonpath + outname;

  cout << "process ... \n"
       << "Input file : " << inname << "\n"
       << "Output file : " << outname << "\n"
       << "TTree name : " << treename << "\n"
       << "Parameters (|q/p|^2, DeltaGamma/Gamma, Re(z), Im(z)) = "
       << qop2 << ", " << dGoG << ", " << rez << ", " << imz << endl << endl;


  // Load input TTree
  TChain *ch = new TChain(treename.c_str());
  ch->Add(inname.c_str());
  ch->GetListOfFiles()->Print();
  long int nentries =  ch->GetEntries();
  cout << "Total entries: " << nentries << endl;
  InTuple T(ch);

  // create output
  double wgt;
  int upperID, lowerID;
  TFile *of(0);
  TTree *ot(0);
  of = new TFile(outname.c_str(), "RECREATE");
  ot = new TTree("W", "Event weights");
  ot->Branch("upperID", &upperID, "upperID/I");
  ot->Branch("lowerID", &lowerID, "lowerID/I");
  ot->Branch("wgt", &wgt, "wgt/D");
  // diagnostic histograms
  const int nbins = 100;
  const double dtlo(-20.0), dthi(20.0);
  TH1D *hpp = new TH1D("hpp", "N++ Delta t distribution", 100, dtlo, dthi);
  TH1D *hnn = new TH1D("hnn", "N-- Delta t distribution", 100, dtlo, dthi);
  TH1D *hpn = new TH1D("hpn", "N+- Delta t distribution", 100, dtlo, dthi);
  TH1D *hnp = new TH1D("hnp", "N-+ Delta t distribution", 100, dtlo, dthi);

  for (long j = 0; j < nentries; j++) {
    long ientry = T.LoadTree(j);
    if (ientry < 0) break;
    T.GetEntry(j);
    if ((j+1) % 100000 == 0) {
      cout << "processing event # " << j+1 << endl;
    }
    
    int q1 = T.mcLund[T.B1mc] > 0 ? 1 : -1;
    int q2 = T.mcLund[T.B2mc] > 0 ? 1 : -1;

    double pdf0 = decay_rate(q1, q2, T.trueDt, 1, 0, 0, 0);
    double pdf  = decay_rate(q1, q2, T.trueDt, qop2, dG, rez, imz);

    upperID = T.upperID;
    lowerID = T.lowerID;
    wgt = pdf0 / pdf;
    ot->Fill();

    if (q1 > 0 && q2 > 0) hpp->Fill(T.trueDt, wgt);
    else if (q1 > 0 && q2 < 0) hpn->Fill(T.trueDt, wgt);
    else if (q1 < 0 && q2 > 0) hnp->Fill(T.trueDt, wgt);
    else if (q1 < 0 && q2 < 0) hnn->Fill(T.trueDt, wgt);

  }
  if (of) {
    ot->Write();
    hpp->Write();
    hpn->Write();
    hnp->Write();
    hnn->Write();
    of->Close();
  }

}
#endif

