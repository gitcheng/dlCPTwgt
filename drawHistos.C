// A ROOT macro to draw diagnostic histograms.
void drawOverlay(TH1D *h1, TH1D* h2) {
  h1->SetLineColor(4);
  h2->SetLineColor(2);
  h1->Draw();
  gPad->Update();
  TPaveStats *tps1 = (TPaveStats*) h1->FindObject("stats");
  double X1 = tps1->GetX1NDC();
  double Y1 = tps1->GetY1NDC();
  double X2 = tps1->GetX2NDC();
  double Y2 = tps1->GetY2NDC();

  h2->Draw("sames");
  gPad->Update();
  TPaveStats *tps2 = (TPaveStats*) h2->FindObject("stats");
  tps2->SetX1NDC(X1);
  tps2->SetX2NDC(X2);
  tps2->SetY1NDC(Y1-(Y2-Y1));
  tps2->SetY2NDC(Y1);
  tps2->Draw();
  
}

void drawHistos(TString rfile) {
  
  TH1::AddDirectory(0);

  TFile f(rfile);
  f.ls();
  TH1D *hpp = (TH1D*)f.Get("hpp");
  TH1D *hpn = (TH1D*)f.Get("hpn");
  TH1D *hnp = (TH1D*)f.Get("hnp");
  TH1D *hnn = (TH1D*)f.Get("hnn");

  hpp->Print();
  hnn->Print();
  hpn->Print();
  hnp->Print();
 
  TCanvas *cv = new TCanvas("cv", "Delta t", 500, 700);
  cv->Divide(1,2);
  
  cv->cd(1);
  drawOverlay(hpp, hnn);
  cv->cd(2);
  drawOverlay(hpn, hnp);

  f.Close();
}
