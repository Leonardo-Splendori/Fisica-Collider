{
  TFile f("FlavTag.root");

  TH1D hb("hb","",100, 0, 10000);
  TH1D hc("hc","",100, 0, 10000);
  TH1D hl("hl","",100, 0, 10000);

  FlavTag->Draw("jf_m>>hb","label==5");
  FlavTag->Draw("jf_m>>hc","label==4");
  FlavTag->Draw("jf_m>>hl","label==0");

  hb.Draw("SAME");
  hb.SetLineColor(2);
  hc.Draw("SAME");
  hc.SetLineColor(4);
  hl.Draw("SAME");
  hl.SetLineColor(11);

  TLegend l(0.2, 0.8, 0.4, 0.9);
  l.AddEntry(&hb,"b-jets");
  l.AddEntry(&hc,"c-jets");
  l.AddEntry(&hl,"l-jets");
  l.Draw();
}
