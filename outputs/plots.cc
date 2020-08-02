void plots(){
    gStyle->SetOptStat(0);
    
    TFile * tf1 = new TFile("data_obs.root", "READ");
    TFile * tf2 = new TFile("background.root", "READ");

    TH1F * m_em_data = (TH1F*) tf1->Get("m_em/data_obs");
    TH1F * m_em_background = (TH1F*) tf2->Get("m_em/background");
    TH1F * m_emb_data = (TH1F*) tf1->Get("m_emb/data_obs");
    TH1F * m_emb_background = (TH1F*) tf2->Get("m_emb/background");
    TH1F * m_embb_data = (TH1F*) tf1->Get("m_embb/data_obs");
    TH1F * m_embb_background = (TH1F*) tf2->Get("m_embb/background");
    
    TCanvas * c = new TCanvas();
    c->Divide(2,2);
    c->cd(1);
    m_em_data->SetTitle("m_em");
    m_em_data->Draw();
    m_em_data->SetLineColor(kRed);
    m_em_data->SetMaximum(3000);
    m_em_background->Draw("same");
    m_em_background->SetMaximum(3000);
    auto legend1 = new TLegend(0.7,0.7,0.9,0.9);
    legend1->AddEntry(m_em_data,"data");
    legend1->AddEntry(m_em_background,"background");
    legend1->Draw("same");
    
    c->cd(2);
    m_emb_data->SetTitle("m_emb");
    m_emb_data->Draw();
    m_emb_data->SetLineColor(kRed);
    m_emb_data->SetMaximum(1200);
    m_emb_background->Draw("same");
    m_emb_background->SetMaximum(1200);
    auto legend2 = new TLegend(0.7,0.7,0.9,0.9);
    legend2->AddEntry(m_em_data,"data");
    legend2->AddEntry(m_em_background,"background");
    legend2->Draw("same");
    
    c->cd(3);
    m_embb_data->SetTitle("m_embb");
    m_embb_data->Draw();
    m_embb_data->SetLineColor(kRed);
    m_embb_data->SetMaximum(1000);
    m_embb_background->Draw("same");
    m_embb_background->SetMaximum(1000);
    auto legend3 = new TLegend(0.7,0.7,0.9,0.9);
    legend3->AddEntry(m_em_data,"data");
    legend3->AddEntry(m_em_background,"background");
    legend3->Draw("same");
    
    c->Print("compare.png");
    
}

