#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "InTuple.h"

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


int main(int argc, char *argv[]) {

  if (argc == 1 || find_opt("-h", argc, argv) || find_opt("--help", argc, argv))
    return print_message();

  string commonpath = parse_opts("-c", argc, argv, "");
  string inname = parse_opts("-i", argc, argv);
  string treename = parse_opts("-t", argc, argv, "tr");
  string outname = parse_opts("-t", argc, argv);
  double qop2 = atof(parse_opts("--gop2", argc, argv, "1.0").c_str());
  double dGoG = atof(parse_opts("--dgog", argc, argv, "0.0").c_str());
  double rez = atof(parse_opts("--rez", argc, argv, "0.0").c_str());
  double imz = atof(parse_opts("--imz", argc, argv, "0.0").c_str());
  
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
  TChain *T = new TChain(treename.c_str());
  T->Add(inname.c_str());
  T->GetListOfFiles()->Print();
  long int nentries =  T->GetEntries();
  cout << "Total entries: " << nentries << endl;


}
#endif

