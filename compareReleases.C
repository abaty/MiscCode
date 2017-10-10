#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TAxis.h"
#include "TAttAxis.h"
#include "TAttMarker.h"
#include "TLegend.h"
#include "TCut.h"

void formatPlot(TH1D* h, int color){
  h->SetStats(0);
  h->SetMarkerStyle(8);
  if(color==0){
    h->SetMarkerColor(kBlue);
    h->SetLineColor(kBlue);
  }
  if(color==1){
    h->SetMarkerColor(kRed);
    h->SetLineColor(kRed);
  }
  return;
}

void compareReleases(bool doCuts = false){

  TH1::SetDefaultSumw2();

  TCut cut = "";
  if(doCuts) cut = "recoTracks_generalTracks__RECO.obj->ptError()/recoTracks_generalTracks__RECO.obj->pt()<0.3 && (recoTracks_generalTracks__RECO.obj->qualityMask()==7 || recoTracks_generalTracks__RECO.obj->qualityMask()==15) && recoTracks_generalTracks__RECO.obj->normalizedChi2()<10 &&  recoTracks_generalTracks__RECO.obj->found()>7";

  TFile * f92 = TFile::Open("CMSSW_9_2_13/src/step3.root");
  TFile * f94 = TFile::Open("CMSSW_9_4_0_pre2/src/step3.root");

  TFile * out = TFile::Open("out.root","recreate");

  TTree * t92 = (TTree*)f92->Get("Events");
  TTree * t94 = (TTree*)f94->Get("Events");

  TH1D * pt92 = new TH1D("pt92",";pt;counts",25,0,5);
  TH1D * pt94 = new TH1D("pt94",";pt;counts",25,0,5);

  TH1D * pterr92 = new TH1D("pterr92",";pterr;counts",25,0,0.3);
  TH1D * pterr94 = new TH1D("pterr94",";pterr;counts",25,0,0.3);
  
  TH1D * eta92 = new TH1D("eta92",";eta;count",20,-2.4,2.4);
  TH1D * eta94 = new TH1D("eta94",";eta;count",20,-2.4,2.4);
  
  TH1D * nHit92 = new TH1D("nHit92",";nHits;count",30,0,30);
  TH1D * nHit94 = new TH1D("nHit94",";nHits;count",30,0,30);

  TH1D * d092 = new TH1D("d092",";d0/d0err;count",100,-100,100);
  TH1D * d094 = new TH1D("d094",";d0/d0err;count",100,-100,100);
  TH1D * dz92 = new TH1D("dz92",";dz/dzerr;count",100,-100,100);
  TH1D * dz94 = new TH1D("dz94",";dz/dzerr;count",100,-100,100);
  
  TH1D * chi92 = new TH1D("chi92",";#chi^2/ndof;count",20,0,2);
  TH1D * chi94 = new TH1D("chi94",";#chi^2/ndof;count",20,0,2);
  
  TH1D * algo92 = new TH1D("algo92",";algo;count",60,0,60);
  TH1D * algo94 = new TH1D("algo94",";algo;count",60,0,60);
  
  TH2D * etaphi92 = new TH2D("etaphi92",";eta;phi;",20,-2.4,2.4,20,-TMath::Pi(),TMath::Pi());
  TH2D * etaphi94 = new TH2D("etaphi94",";eta;phi;",20,-2.4,2.4,20,-TMath::Pi(),TMath::Pi());
 
  TH2D * etapt92 = new TH2D("etapt92",";eta;pt;",20,-2.4,2.4,25,0,5);
  TH2D * etapt94 = new TH2D("etapt94",";eta;pt;",20,-2.4,2.4,25,0,5);

  TH1D * nTrk92 = new TH1D("nTrk92","nTrk92",50,0,10000);
  TH1D * nTrk94 = new TH1D("nTrk94","nTrk94",50,0,10000);

  t92->Draw("recoTracks_generalTracks__RECO.obj->pt()>>pt92",cut); 
  t94->Draw("recoTracks_generalTracks__RECO.obj->pt()>>pt94",cut); 

  t92->Draw("recoTracks_generalTracks__RECO.obj->ptError()/recoTracks_generalTracks__RECO.obj->pt()>>pterr92",cut); 
  t94->Draw("recoTracks_generalTracks__RECO.obj->ptError()/recoTracks_generalTracks__RECO.obj->pt()>>pterr94",cut); 
  
  t92->Draw("recoTracks_generalTracks__RECO.obj->dxy(recoTracks_generalTracks__RECO.obj->referencePoint())/recoTracks_generalTracks__RECO.obj->dxyError()>>d092",cut); 
  t94->Draw("recoTracks_generalTracks__RECO.obj->dxy(recoTracks_generalTracks__RECO.obj->referencePoint())/recoTracks_generalTracks__RECO.obj->dxyError()>>d094",cut); 
  t92->Draw("recoTracks_generalTracks__RECO.obj->dz(recoTracks_generalTracks__RECO.obj->referencePoint())/recoTracks_generalTracks__RECO.obj->dzError()>>dz92",cut); 
  t94->Draw("recoTracks_generalTracks__RECO.obj->dz(recoTracks_generalTracks__RECO.obj->referencePoint())/recoTracks_generalTracks__RECO.obj->dzError()>>dz94",cut); 
  
  t92->Draw("recoTracks_generalTracks__RECO.obj->eta()>>eta92",cut); 
  t94->Draw("recoTracks_generalTracks__RECO.obj->eta()>>eta94",cut); 
  
  t92->Draw("recoTracks_generalTracks__RECO.obj->found()>>nHit92",cut); 
  t94->Draw("recoTracks_generalTracks__RECO.obj->found()>>nHit94",cut); 
  
  t92->Draw("(recoTracks_generalTracks__RECO.obj->chi2()/recoTracks_generalTracks__RECO.obj->ndof())>>chi92",cut); 
  t94->Draw("(recoTracks_generalTracks__RECO.obj->chi2()/recoTracks_generalTracks__RECO.obj->ndof())>>chi94",cut); 

  t92->Draw("recoTracks_generalTracks__RECO.obj->algo()>>algo92",cut); 
  t94->Draw("recoTracks_generalTracks__RECO.obj->algo()>>algo94",cut); 

  t92->Draw("recoTracks_generalTracks__RECO.obj->phi():recoTracks_generalTracks__RECO.obj->eta()>>etaphi92",cut);
  t94->Draw("recoTracks_generalTracks__RECO.obj->phi():recoTracks_generalTracks__RECO.obj->eta()>>etaphi94",cut);
  
  t92->Draw("recoTracks_generalTracks__RECO.obj->pt():recoTracks_generalTracks__RECO.obj->eta()>>etapt92",cut);
  t94->Draw("recoTracks_generalTracks__RECO.obj->pt():recoTracks_generalTracks__RECO.obj->eta()>>etapt94",cut);

  t92->Draw("Sum$(recoTracks_generalTracks__RECO.obj->pt()>0)>>nTrk92",cut);
  t94->Draw("Sum$(recoTracks_generalTracks__RECO.obj->pt()>0)>>nTrk94",cut);
  
  TH1D * ptRatio = (TH1D*)pt92->Clone("ptRatio");
  ptRatio->Divide(pt94);

  TH1D * pterrRatio = (TH1D*)pterr92->Clone("pterrRatio");
  pterrRatio->Divide(pterr94);

  TH1D * etaRatio = (TH1D*)eta92->Clone("etaRatio");
  etaRatio->Divide(eta94);

  TH1D * nHitRatio = (TH1D*)nHit92->Clone("nHitRatio");
  nHitRatio->Divide(nHit94);

  TH1D * chiRatio = (TH1D*)chi92->Clone("chiRatio");
  chiRatio->Divide(chi94);
  
  TH1D * d0Ratio = (TH1D*)d092->Clone("d0Ratio");
  d0Ratio->Divide(d094);
  
  TH1D * dzRatio = (TH1D*)dz92->Clone("dzRatio");
  dzRatio->Divide(dz94);

  TH1D * algoRatio = (TH1D*)algo92->Clone("algoRatio");
  algoRatio->Divide(algo94);

  TH2D * etaphiRatio = (TH2D*)etaphi92->Clone("etaphiRatio");
  etaphiRatio->Divide(etaphi94);
  
  TH2D * etaptRatio = (TH2D*)etapt92->Clone("etaptRatio");
  etaptRatio->Divide(etapt94);

  TH1D * nTrkRatio = (TH1D*)nTrk92->Clone("nTrkRatio");
  nTrkRatio->Divide(nTrk94);

  out->Write();

  TCanvas * c =new  TCanvas("c","c",800,600);
  c->SetLogy();
  formatPlot(pt92,0);
  formatPlot(pt94,1);
  pt92->Draw("p");
  pt94->Draw("p same");

  TLegend * l = new TLegend(0.6,0.6,0.8,0.8);
  l->AddEntry(pt92,"9_2_13","p");
  l->AddEntry(pt94,"9_4_0_pre2+PRs","p");
  l->Draw("same");

  c->SaveAs("img/pt.png");
  c->SaveAs("img/pt.pdf");

  c->SetLogy(0);
  formatPlot(eta92,0);
  formatPlot(eta94,1);
  eta92->Draw("p");
  eta94->Draw("p same");
  l->Draw("same");
  c->SaveAs("img/eta.png");
  c->SaveAs("img/eta.pdf");
  
  formatPlot(pterr92,0);
  formatPlot(pterr94,1);
  pterr92->Draw("p");
  pterr94->Draw("p same");
  l->Draw("same");
  c->SaveAs("img/pterr.png");
  c->SaveAs("img/pterr.pdf");

  c->SetLogy();
  formatPlot(nHit92,0);
  formatPlot(nHit94,1);
  nHit92->Draw("p");
  nHit94->Draw("p same");
  l->Draw("same");
  c->SaveAs("img/nHit.png");
  c->SaveAs("img/nHit.pdf");
 
  formatPlot(d092,0);
  formatPlot(d094,1);
  d092->Draw("p");
  d094->Draw("p same");
  l->Draw("same");
  c->SaveAs("img/d0.png");
  c->SaveAs("img/d0.pdf");

  formatPlot(dz92,0);
  formatPlot(dz94,1);
  dz92->Draw("p");
  dz94->Draw("p same");
  l->Draw("same");
  c->SaveAs("img/dz.png");
  c->SaveAs("img/dz.pdf");
 
  c->SetLogy(0);
  formatPlot(chi92,0);
  formatPlot(chi94,1);
  chi92->Draw("p");
  chi94->Draw("p same");
  l->Draw("same");
  c->SaveAs("img/chi.png");
  c->SaveAs("img/chi.pdf");
  
  formatPlot(algo92,0);
  formatPlot(algo94,1);
  algo92->Draw("p");
  algo94->Draw("p same");
  l->Draw("same");
  c->SaveAs("img/algo.png");
  c->SaveAs("img/algo.pdf");

  c->SetLogy();  
  formatPlot(nTrk92,0);
  formatPlot(nTrk94,1);
  nTrk92->Draw("p");
  nTrk94->Draw("p same");
  l->Draw("same");
  c->SaveAs("img/nTrk.png");
  c->SaveAs("img/nTrk.pdf");

  c->SetLogy(0);
  etaphi92->Draw("colz");
  c->SaveAs("img/etaphi92.png");
  c->SaveAs("img/etaphi92.pdf");
  etaphi94->Draw("colz");
  c->SaveAs("img/etaphi94.png");
  c->SaveAs("img/etaphi94.pdf");
  etaphiRatio->Draw("colz");
  c->SaveAs("img/etaphiRatio.png");
  c->SaveAs("img/etaphiRatio.pdf");
  
  etapt92->Draw("colz");
  c->SaveAs("img/etapt92.png");
  c->SaveAs("img/etapt92.pdf");
  etapt94->Draw("colz");
  c->SaveAs("img/etapt94.png");
  c->SaveAs("img/etapt94.pdf");
  etaptRatio->Draw("colz");
  c->SaveAs("img/etaptRatio.png");
  c->SaveAs("img/etaptRatio.pdf");

  //ratios
  c->SetLogy(0);
  formatPlot(ptRatio,0);
  ptRatio->GetYaxis()->SetTitle("92X/94X");
  ptRatio->GetYaxis()->SetRangeUser(0.5,1.5);
  ptRatio->Draw();
  c->SaveAs("img/ptRatio.png");
  c->SaveAs("img/ptRatio.pdf");

  formatPlot(pterrRatio,0);
  pterrRatio->GetYaxis()->SetTitle("92X/94X");
  pterrRatio->GetYaxis()->SetRangeUser(0.5,1.5);
  pterrRatio->Draw();
  c->SaveAs("img/pterrRatio.png");
  c->SaveAs("img/pterrRatio.pdf");
  
  formatPlot(d0Ratio,0);
  d0Ratio->GetYaxis()->SetTitle("92X/94X");
  d0Ratio->GetYaxis()->SetRangeUser(0.5,1.5);
  d0Ratio->Draw();
  c->SaveAs("img/d0Ratio.png");
  c->SaveAs("img/d0Ratio.pdf");

  formatPlot(dzRatio,0);
  dzRatio->GetYaxis()->SetTitle("92X/94X");
  dzRatio->GetYaxis()->SetRangeUser(0.5,1.5);
  dzRatio->Draw();
  c->SaveAs("img/dzRatio.png");
  c->SaveAs("img/dzRatio.pdf");

  formatPlot(etaRatio,0);
  etaRatio->GetYaxis()->SetTitle("92X/94X");
  etaRatio->GetYaxis()->SetRangeUser(0.5,1.5);
  etaRatio->Draw();
  c->SaveAs("img/etaRatio.png");
  c->SaveAs("img/etaRatio.pdf");

  formatPlot(nHitRatio,0);
  nHitRatio->GetYaxis()->SetTitle("92X/94X");
  nHitRatio->GetYaxis()->SetRangeUser(0.5,1.5);
  nHitRatio->Draw();
  c->SaveAs("img/nHitRatio.png");
  c->SaveAs("img/nHitRatio.pdf");

  formatPlot(chiRatio,0);
  chiRatio->GetYaxis()->SetTitle("92X/94X");
  chiRatio->GetYaxis()->SetRangeUser(0.5,1.5);
  chiRatio->Draw();
  c->SaveAs("img/chiRatio.png");
  c->SaveAs("img/chiRatio.pdf");


  formatPlot(algoRatio,0);
  algoRatio->GetYaxis()->SetTitle("92X/94X");
  algoRatio->GetYaxis()->SetRangeUser(0.5,1.5);
  algoRatio->Draw();
  c->SaveAs("img/algoRatio.png");
  c->SaveAs("img/algoRatio.pdf");

  formatPlot(nTrkRatio,0);
  nTrkRatio->GetYaxis()->SetTitle("92X/94X");
  nTrkRatio->GetYaxis()->SetRangeUser(0.5,1.5);
  nTrkRatio->Draw();
  c->SaveAs("img/nTrkRatio.png");
  c->SaveAs("img/nTrkRatio.pdf");

}
