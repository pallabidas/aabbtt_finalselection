#!/usr/bin/env python
import ROOT
import re
from array import array
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--channel', '-c', default=None, choices=['et','mt','em'], help='channel')
parser.add_argument('--year', '-y', default=None, choices=['2018','2017','2016'], help='year')
parser.add_argument('--signal', '-s', default=None, choices=['yes','no'], help='signal')
args = parser.parse_args()

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
    if args.channel=="mt":
       lumi.AddText("#mu#tau_{h}")
    if args.channel=="et":
       lumi.AddText("e#tau_{h}")
    if args.channel=="em":
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
    if args.year=="2018":
       lumi.AddText("2018, 59.7 fb^{-1} (13 TeV)")
    if args.year=="2017":
       lumi.AddText("2017, 41.5 fb^{-1} (13 TeV)")
    if args.year=="2016":
       lumi.AddText("2016, 35.9 fb^{-1} (13 TeV)")
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

file=ROOT.TFile(args.channel+"_"+args.year+"/final_"+args.channel+"_"+args.year+".root","r")

adapt=ROOT.gROOT.GetColor(12)
new_idx=ROOT.gROOT.GetListOfColors().GetSize() + 1
trans=ROOT.TColor(new_idx, adapt.GetRed(), adapt.GetGreen(),adapt.GetBlue(), "",0.5)

if args.channel=="mt":
   dir=["pt_1_1b","pt_2_1b","m_tt_1b","m_btt_1b","pt_1_2b","pt_2_2b","m_tt_2b","m_btt_2b","m_bbtt_2b"]
   xaxis=["p_{T}(#mu) (GeV)","p_{T}(#tau_{h}) (GeV)","m_{#tau#tau} (GeV)","m_{b#tau#tau} (GeV)","p_{T}(#mu) (GeV)","p_{T}(#tau_{h}) (GeV)","m_{#tau#tau} (GeV)","m_{b#tau#tau} (GeV)","m_{bb#tau#tau} (GeV)"]
if args.channel=="et":
   dir=["pt_1_1b","pt_2_1b","m_tt_1b","m_btt_1b","pt_1_2b","pt_2_2b","m_tt_2b","m_btt_2b","m_bbtt_2b"]
   xaxis=["p_{T}(e) (GeV)","p_{T}(#tau_{h}) (GeV)","m_{#tau#tau} (GeV)","m_{b#tau#tau} (GeV)","p_{T}(e) (GeV)","p_{T}(#tau_{h}) (GeV)","m_{#tau#tau} (GeV)","m_{b#tau#tau} (GeV)","m_{bb#tau#tau} (GeV)"]
if args.channel=="em":
   dir=["pt_1_1b","pt_2_1b","m_tt_1b","m_btt_1b","pt_1_2b","pt_2_2b","m_tt_2b","m_btt_2b","m_bbtt_2b"]
   xaxis=["p_{T}(e) (GeV)","p_{T}(#mu) (GeV)","m_{#tau#tau} (GeV)","m_{b#tau#tau} (GeV)","p_{T}(e) (GeV)","p_{T}(#mu) (GeV)","m_{#tau#tau} (GeV)","m_{b#tau#tau} (GeV)","m_{bb#tau#tau} (GeV)"]

for i in range(len(dir)):
   data=file.Get(dir[i]).Get("data_obs")
   ttbar=file.Get(dir[i]).Get("ttbar")
   embedded=file.Get(dir[i]).Get("embedded")
   if args.channel=="et" or args.channel=="mt":
      fake=file.Get(dir[i]).Get("fake")
   if args.channel=="em":
      fake=file.Get(dir[i]).Get("qcd")
   
   ZJ=file.Get(dir[i]).Get("ZJ")
   ST=file.Get(dir[i]).Get("ST")
   VV=file.Get(dir[i]).Get("VV")
   ggh_htt=file.Get(dir[i]).Get("ggh_htt")
   ggh_hww=file.Get(dir[i]).Get("ggh_hww")
   qqh_htt=file.Get(dir[i]).Get("qqh_htt")
   qqh_hww=file.Get(dir[i]).Get("qqh_hww")
   Zh_htt=file.Get(dir[i]).Get("Zh_htt")
   Zh_hww=file.Get(dir[i]).Get("Zh_hww")
   Wh_htt=file.Get(dir[i]).Get("Wh_htt")
   Wh_hww=file.Get(dir[i]).Get("Wh_hww")
   tth=file.Get(dir[i]).Get("tth")
   
   other=ZJ
   other.Add(ST)
   other.Add(VV)
   other.Add(ggh_htt)
   other.Add(ggh_hww)
   other.Add(qqh_htt)
   other.Add(qqh_hww)
   other.Add(Zh_htt)
   other.Add(Zh_hww)
   other.Add(Wh_htt)
   other.Add(Wh_hww)
   other.Add(tth)
   
   if args.channel=="em":
      WJ=file.Get(dir[i]).Get("WJ")
      other.Add(WJ)
      
   if args.signal=="yes":
      gghbbtt20=file.Get(dir[i]).Get("gghbbtt20")
      gghbbtt40=file.Get(dir[i]).Get("gghbbtt40")
      gghbbtt60=file.Get(dir[i]).Get("gghbbtt60")
      vbfbbtt20=file.Get(dir[i]).Get("vbfbbtt20")
      vbfbbtt40=file.Get(dir[i]).Get("vbfbbtt40")
      vbfbbtt60=file.Get(dir[i]).Get("vbfbbtt60")
      bbtt20=gghbbtt20
      bbtt20.Add(vbfbbtt20)
      bbtt40=gghbbtt40
      bbtt40.Add(vbfbbtt40)
      bbtt60=gghbbtt60
      bbtt60.Add(vbfbbtt60)
      
   data.GetXaxis().SetTitle("")
   data.GetXaxis().SetTitleSize(0)
   data.GetXaxis().SetNdivisions(505)
   data.GetYaxis().SetLabelFont(42)
   data.GetYaxis().SetLabelOffset(0.01)
   data.GetYaxis().SetLabelSize(0.06)
   data.GetYaxis().SetTitleSize(0.085)
   data.GetYaxis().SetTitleOffset(0.7)
   data.SetTitle("")
   data.GetYaxis().SetTitle("Events")
   
   ttbar.SetFillColor(ROOT.TColor.GetColor("#9999cc"))
   embedded.SetFillColor(ROOT.TColor.GetColor("#ffcc66"))
   fake.SetFillColor(ROOT.TColor.GetColor("#FDA5BA"))
   other.SetFillColor(ROOT.TColor.GetColor("#08F7F1"))
   
   data.SetMarkerStyle(20)
   data.SetMarkerSize(1)
   data.SetLineColor(1)
   data.SetLineWidth(2)
   ttbar.SetLineColor(1)
   embedded.SetLineColor(1)
   fake.SetLineColor(1)
   other.SetLineColor(1)
   
   if args.signal=="yes":
      bbtt20.SetLineColor(3)
      bbtt20.SetLineWidth(3)
      bbtt40.SetLineColor(2)
      bbtt40.SetLineWidth(3)
      bbtt60.SetLineColor(4)
      bbtt60.SetLineWidth(3)
      
   stack=ROOT.THStack("stack","stack")
   stack.Add(ttbar)
   stack.Add(embedded)
   stack.Add(other)
   stack.Add(fake)
   
   errorBand=ttbar.Clone()
   errorBand.Add(embedded)
   errorBand.Add(fake)
   errorBand.Add(other)
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
   
   data.GetXaxis().SetLabelSize(0)
   data.SetMaximum(max(data.GetMaximum()*2.0,errorBand.GetMaximum()*2.0))
   data.SetMinimum(0)
   data.Draw("e")
   stack.Draw("histsame")
   
   if args.signal=="yes":
      bbtt20.Scale(10)
      bbtt20.Draw("histsame")
      bbtt40.Scale(10)
      bbtt40.Draw("histsame")
      bbtt60.Scale(10)
      bbtt60.Draw("histsame")
   
   errorBand.Draw("e2same")
   data.Draw("esame")
   
   legende=make_legend()
   legende.AddEntry(data,"Observed","elp")
   legende.AddEntry(ttbar,"t#bar{t}","f")
   legende.AddEntry(embedded,"Z#rightarrow#tau#tau","f")
   
   if args.channel=="et" or args.channel=="mt":
      legende.AddEntry(fake,"jet#rightarrow#tau_{h}","f")
   if args.channel=="em":
      legende.AddEntry(fake,"QCD","f")
   legende.AddEntry(other,"Other","f")
   if args.signal=="yes":
      legende.AddEntry(bbtt20,"m_{a}=20GeV,B=10%","l")
      legende.AddEntry(bbtt40,"m_{a}=40GeV,B=10%","l")
      legende.AddEntry(bbtt60,"m_{a}=60GeV,B=10%","l")
      
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
   h1=data.Clone()
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
   h1.GetXaxis().SetTitle(xaxis[i])
   h1.GetXaxis().SetLabelSize(0.1)
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
   c.SaveAs(dir[i]+".png")

