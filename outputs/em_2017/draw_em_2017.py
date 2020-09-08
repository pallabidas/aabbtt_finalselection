#!/usr/bin/env python
import ROOT
import re
from array import array

def add_channel():
    lowX=0.155
    lowY=0.46
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.30, lowY+0.21, "NDC")
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.SetTextSize(0.072)
    lumi.SetTextFont (   42 )
    lumi.AddText("e#mu")
    return lumi

def add_lumi():
    lowX=0.58
    lowY=0.835
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.30, lowY+0.16, "NDC")
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.SetTextSize(0.09)
    lumi.SetTextFont (   42 )
    lumi.AddText("2017, 41.4 fb^{-1} (13 TeV)")
    return lumi

def add_CMS():
    lowX=0.155
    lowY=0.70
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(61)
    lumi.SetTextSize(0.10)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("CMS")
    return lumi

def add_Preliminary():
    lowX=0.155
    lowY=0.61
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(52)
    lumi.SetTextSize(0.07)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("Preliminary")
    return lumi

def make_legend():
        output = ROOT.TLegend(0.45, 0.50, 0.92, 0.85, "", "brNDC")
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        output.SetFillStyle(0)
        output.SetBorderSize(0)
        output.SetTextFont(62)
        output.SetNColumns(2)
        return output

ROOT.gStyle.SetFrameLineWidth(3)
ROOT.gStyle.SetLineWidth(3)
ROOT.gStyle.SetOptStat(0)

c=ROOT.TCanvas("canvas","",0,0,900,600)
c.cd()

file=ROOT.TFile("final_em_2017.root","r")

adapt=ROOT.gROOT.GetColor(12)
new_idx=ROOT.gROOT.GetListOfColors().GetSize() + 1
trans=ROOT.TColor(new_idx, adapt.GetRed(), adapt.GetGreen(),adapt.GetBlue(), "",0.5)

categories=["m_em_nobjet","e_pt_nobjet","mu_pt_nobjet","m_em_1bjet","m_emb_1bjet","e_pt_1bjet","mu_pt_1bjet","m_em_2bjet","m_emb_2bjet","m_embb_2bjet","e_pt_2bjet","mu_pt_2bjet","m_em_nobjet_VBFenriched","e_pt_nobjet_VBFenriched","mu_pt_nobjet_VBFenriched","m_em_1bjet_VBFenriched","m_emb_1bjet_VBFenriched","e_pt_1bjet_VBFenriched","mu_pt_1bjet_VBFenriched","m_em_2bjet_VBFenriched","m_emb_2bjet_VBFenriched","m_embb_2bjet_VBFenriched","e_pt_2bjet_VBFenriched","mu_pt_2bjet_VBFenriched","m_em_VV","e_pt_VV","mu_pt_VV","m_em_1","m_em_2","m_em_3","m_em_4","e_pt_1","e_pt_2","e_pt_3","e_pt_4","mu_pt_1","mu_pt_2","mu_pt_3","mu_pt_4"]
xaxis=["m_{e#mu} (GeV)","pt_{e} (GeV)","pt_{#mu} (GeV)","m_{e#mu} (GeV)","m_{e#mub} (GeV)","pt_{e} (GeV)","pt_{#mu} (GeV)","m_{e#mu} (GeV)","m_{e#mub} (GeV)","m_{e#mubb} (GeV)","pt_{e} (GeV)","pt_{#mu} (GeV)","m_{e#mu} (GeV)","pt_{e} (GeV)","pt_{#mu} (GeV)","m_{e#mu} (GeV)","m_{e#mub} (GeV)","pt_{e} (GeV)","pt_{#mu} (GeV)","m_{e#mu} (GeV)","m_{e#mub} (GeV)","m_{e#mubb} (GeV)","pt_{e} (GeV)","pt_{#mu} (GeV)","m_{e#mu} (GeV)","pt_{e} (GeV)","pt_{#mu} (GeV)","m_{e#mu} (GeV)","m_{e#mu} (GeV)","m_{e#mu} (GeV)","m_{e#mu} (GeV)","pt_{e} (GeV)","pt_{e} (GeV)","pt_{e} (GeV)","pt_{e} (GeV)","pt_{#mu} (GeV)","pt_{#mu} (GeV)","pt_{#mu} (GeV)","pt_{#mu} (GeV)"]
ncat=39

for i in range (0,ncat):
   Data=file.Get(categories[i]).Get("data_obs_OS")
   HTT=file.Get(categories[i]).Get("HTT_OS")
   HWW=file.Get(categories[i]).Get("HWW_OS")
   W=file.Get(categories[i]).Get("W_OS")
   TT=file.Get(categories[i]).Get("TT_OS")
   VV=file.Get(categories[i]).Get("VV_OS")
   Z=file.Get(categories[i]).Get("Z_OS")
   ST=file.Get(categories[i]).Get("ST_OS")
   ttHnonbb=file.Get(categories[i]).Get("ttHnonbb_OS")
   QCD=file.Get(categories[i]).Get("QCD")
#   bbtt60=divide_width(file.Get(categories[i]).Get("bbtt60"))

   Data.GetXaxis().SetTitle("")
   Data.GetXaxis().SetTitleSize(0)
   Data.GetXaxis().SetNdivisions(505)
   Data.GetYaxis().SetLabelFont(42)
   Data.GetYaxis().SetLabelOffset(0.01)
   Data.GetYaxis().SetLabelSize(0.06)
   Data.GetYaxis().SetTitleSize(0.085)
   Data.GetYaxis().SetTitleOffset(0.7)
   Data.SetTitle("")
   Data.GetYaxis().SetTitle("Events")

   HTT.SetFillColor(ROOT.TColor.GetColor("#C125F7"))
   HWW.SetFillColor(ROOT.TColor.GetColor("#3D4CFF"))
   W.SetFillColor(ROOT.TColor.GetColor("#75D185"))
   TT.SetFillColor(ROOT.TColor.GetColor("#9999cc"))
   VV.SetFillColor(ROOT.TColor.GetColor("#08F7F1"))
   Z.SetFillColor(ROOT.TColor.GetColor("#ffcc66"))
   ST.SetFillColor(ROOT.TColor.GetColor("#4496c8"))
   ttHnonbb.SetFillColor(ROOT.TColor.GetColor("#3DCCFF"))
   QCD.SetFillColor(ROOT.TColor.GetColor("#FDA5BA"))

   Data.SetMarkerStyle(20)
   Data.SetMarkerSize(1)
   HTT.SetLineColor(1)
   HWW.SetLineColor(1)
   W.SetLineColor(1)
   TT.SetLineColor(1)
   VV.SetLineColor(1)
   Z.SetLineColor(1)
   ST.SetLineColor(1)
   ttHnonbb.SetLineColor(1)
   QCD.SetLineColor(1)
   Data.SetLineColor(1)
   Data.SetLineWidth(2)
#   bbtt60.SetLineColor(2)
#   bbtt60.SetLineWidth(3)

   stack=ROOT.THStack("stack","stack")
   stack.Add(HTT)
   stack.Add(HWW)
   stack.Add(W)
   stack.Add(TT)
   stack.Add(VV)
   stack.Add(Z)
   stack.Add(ST)
   stack.Add(ttHnonbb)
   stack.Add(QCD)

   errorBand = HTT.Clone()
   errorBand.Add(HWW)
   errorBand.Add(W)
   errorBand.Add(TT)
   errorBand.Add(VV)
   errorBand.Add(Z)
   errorBand.Add(ST)
   errorBand.Add(ttHnonbb)
   errorBand.Add(QCD)
   errorBand.SetMarkerSize(0)
   errorBand.SetFillColor(new_idx)
   errorBand.SetFillStyle(3001)
   errorBand.SetLineWidth(1)

   pad1 = ROOT.TPad("pad1","pad1",0,0.35,1,1)
   pad1.Draw()
   pad1.cd()
   pad1.SetFillColor(0)
   pad1.SetBorderMode(0)
   pad1.SetBorderSize(10)
   pad1.SetTickx(1)
   pad1.SetTicky(1)
   pad1.SetLeftMargin(0.13)
   pad1.SetRightMargin(0.05)
   pad1.SetTopMargin(0.122)
   pad1.SetBottomMargin(0.026)
   pad1.SetFrameFillStyle(0)
   pad1.SetFrameLineStyle(0)
   pad1.SetFrameLineWidth(3)
   pad1.SetFrameBorderMode(0)
   pad1.SetFrameBorderSize(10)

   Data.GetXaxis().SetLabelSize(0)
   Data.SetMaximum(max(Data.GetMaximum()*2.0,errorBand.GetMaximum()*2.0))
   Data.SetMinimum(0)
   print Data.GetMaximum(),Data.GetMinimum()
   Data.Draw("e")
   stack.Draw("histsame")
#   bbtt60.Scale(10)
#   bbtt60.Draw("histsame")

   errorBand.Draw("e2same")
   Data.Draw("esame")

   legende=make_legend()
   legende.AddEntry(Data,"Observed","elp")
   legende.AddEntry(HTT,"H#rightarrow#tau#tau","f")
   legende.AddEntry(HWW,"HWW","f")
   legende.AddEntry(W,"W+jets","f")
   legende.AddEntry(TT,"t#bar{t}","f")
   legende.AddEntry(VV,"VV","f")
   legende.AddEntry(Z,"Embedded Z#rightarrow#tau#tau","f")
   legende.AddEntry(ST,"Single t","f")
   legende.AddEntry(ttHnonbb,"ttH (no H#rightarrowbb)","f")
   legende.AddEntry(QCD,"QCD","f")
#  legende.AddEntry(bbtt60,"m_{a}=60","l")
   legende.AddEntry(errorBand,"Uncertainty","f")
   legende.Draw()

   l1=add_lumi()
   l1.Draw("same")
   l2=add_CMS()
   l2.Draw("same")
   l3=add_Preliminary()
   l3.Draw("same")
   l4=add_channel()
   l4.Draw("same")

   pad1.RedrawAxis()

   c.cd()
   pad2 = ROOT.TPad("pad2","pad2",0,0,1,0.35);
   pad2.SetTopMargin(0.05);
   pad2.SetBottomMargin(0.35);
   pad2.SetLeftMargin(0.13);
   pad2.SetRightMargin(0.05);
   pad2.SetTickx(1)
   pad2.SetTicky(1)
   pad2.SetFrameLineWidth(3)
   pad2.SetGridx()
   pad2.SetGridy()
   pad2.Draw()
   pad2.cd()
   h1=Data.Clone()
   h1.SetMaximum(1.5)#FIXME(1.5)
   h1.SetMinimum(0.5)#FIXME(0.5)
   h1.SetMarkerStyle(20)
   h3=errorBand.Clone()
   hwoE=errorBand.Clone()
   for iii in range (1,hwoE.GetSize()-2):
     hwoE.SetBinError(iii,0)
   h3.Sumw2()
   h1.Sumw2()
   h1.SetStats(0)
   h1.Divide(hwoE)
   h3.Divide(hwoE)
   #h1.GetXaxis().SetTitle("b p_{T} (GeV)")
   h1.GetXaxis().SetTitle(xaxis[i])
   h1.GetXaxis().SetLabelSize(0.08)
   h1.GetYaxis().SetLabelSize(0.08)
   h1.GetYaxis().SetTitle("Obs./Exp.")
   h1.GetXaxis().SetNdivisions(505)
   h1.GetYaxis().SetNdivisions(5)

   h1.GetXaxis().SetTitleSize(0.15)
   h1.GetYaxis().SetTitleSize(0.15)
   h1.GetYaxis().SetTitleOffset(0.36)
   h1.GetXaxis().SetTitleOffset(1.04)
   h1.GetXaxis().SetLabelSize(0.11)
   h1.GetYaxis().SetLabelSize(0.11)
   h1.GetXaxis().SetTitleFont(42)
   h1.GetYaxis().SetTitleFont(42)

   h1.Draw("e0p")
   h3.Draw("e2same")

   c.cd()
   pad1.Draw()

   ROOT.gPad.RedrawAxis()

   c.Modified()
   c.SaveAs(categories[i]+".png")


