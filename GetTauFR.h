double GetTauFR(float pt, float dm, TGraphAsymmErrors *g_taufr_dm0T, TGraphAsymmErrors *g_taufr_dm1T, TGraphAsymmErrors *g_taufr_dm10T, TGraphAsymmErrors *g_taufr_dm11T, int syst){


    Double_t *taufr_dm0_y = g_taufr_dm0T->GetY();
    Double_t *taufr_dm1_y = g_taufr_dm1T->GetY();
    Double_t *taufr_dm10_y = g_taufr_dm10T->GetY();
    Double_t *taufr_dm11_y = g_taufr_dm11T->GetY();
    Double_t *taufr_dm0_ylow = g_taufr_dm0T->GetEYlow();
    Double_t *taufr_dm1_ylow = g_taufr_dm1T->GetEYlow();
    Double_t *taufr_dm10_ylow = g_taufr_dm10T->GetEYlow();
    Double_t *taufr_dm11_ylow = g_taufr_dm11T->GetEYlow();
    Double_t *taufr_dm0_yhigh = g_taufr_dm0T->GetEYhigh();
    Double_t *taufr_dm1_yhigh = g_taufr_dm1T->GetEYhigh();
    Double_t *taufr_dm10_yhigh = g_taufr_dm10T->GetEYhigh();
    Double_t *taufr_dm11_yhigh = g_taufr_dm11T->GetEYhigh();

    double fr=0.5;

        if (dm==0){
            if (pt<25) fr=taufr_dm0_y[0];
            else if (pt<30) fr=taufr_dm0_y[1];
            else if (pt<35) fr=taufr_dm0_y[2];
            else if (pt<40) fr=taufr_dm0_y[3];
            else if (pt<50) fr=taufr_dm0_y[4];
            else if (pt<60) fr=taufr_dm0_y[5];
            else fr=taufr_dm0_y[6];
        }
        if (dm==1){
            if (pt<25) fr=taufr_dm1_y[0];
            else if (pt<30) fr=taufr_dm1_y[1];
            else if (pt<35) fr=taufr_dm1_y[2];
            else if (pt<40) fr=taufr_dm1_y[3];
            else if (pt<50) fr=taufr_dm1_y[4];
            else if (pt<60) fr=taufr_dm1_y[5];
            else fr=taufr_dm1_y[6];
        }
        if (dm==10){
            if (pt<25) fr=taufr_dm10_y[0];
            else if (pt<30) fr=taufr_dm10_y[1];
            else if (pt<35) fr=taufr_dm10_y[2];
            else if (pt<40) fr=taufr_dm10_y[3];
            else if (pt<50) fr=taufr_dm10_y[4];
            else if (pt<60) fr=taufr_dm10_y[5];
            else fr=taufr_dm10_y[6];
        }
        if (dm==11){
            if (pt<25) fr=taufr_dm11_y[0];
            else if (pt<30) fr=taufr_dm11_y[1];
            else if (pt<35) fr=taufr_dm11_y[2];
            else if (pt<40) fr=taufr_dm11_y[3];
            else if (pt<50) fr=taufr_dm11_y[4];
            else if (pt<60) fr=taufr_dm11_y[5];
            else fr=taufr_dm11_y[6];
        }

	if (syst==1 && dm==0 && pt<25) fr=taufr_dm0_y[0]+taufr_dm0_yhigh[0];
        else if (syst==2 && dm==0 && pt<25) fr=taufr_dm0_y[0]-taufr_dm0_ylow[0];
        else if (syst==3 && dm==0 && pt>=25 && pt<30) fr=taufr_dm0_y[1]+taufr_dm0_yhigh[1];
        else if (syst==4 && dm==0 && pt>=25 && pt<30) fr=taufr_dm0_y[1]-taufr_dm0_ylow[1];
	else if (syst==5 && dm==0 && pt>=30 && pt<35) fr=taufr_dm0_y[2]+taufr_dm0_yhigh[2];
        else if (syst==6 && dm==0 && pt>=30 && pt<35) fr=taufr_dm0_y[2]-taufr_dm0_ylow[2];
        else if (syst==7 && dm==0 && pt>=35 && pt<40) fr=taufr_dm0_y[3]+taufr_dm0_yhigh[3];
        else if (syst==8 && dm==0 && pt>=35 && pt<40) fr=taufr_dm0_y[3]-taufr_dm0_ylow[3];
        else if (syst==9 && dm==0 && pt>=40 && pt<50) fr=taufr_dm0_y[4]+taufr_dm0_yhigh[4];
        else if (syst==10 && dm==0 && pt>=40 && pt<50) fr=taufr_dm0_y[4]-taufr_dm0_ylow[4];
        else if (syst==11 && dm==0 && pt>=50 && pt<60) fr=taufr_dm0_y[5]+taufr_dm0_yhigh[5];
        else if (syst==12 && dm==0 && pt>=50 && pt<60) fr=taufr_dm0_y[5]-taufr_dm0_ylow[5];
        else if (syst==13 && dm==0 && pt>=60) fr=taufr_dm0_y[6]+taufr_dm0_yhigh[6];
        else if (syst==14 && dm==0 && pt>=60) fr=taufr_dm0_y[6]-taufr_dm0_ylow[6];

        if (syst==15 && dm==1 && pt<25) fr=taufr_dm1_y[0]+taufr_dm1_yhigh[0];
        else if (syst==16 && dm==1 && pt<25) fr=taufr_dm1_y[0]-taufr_dm1_ylow[0];
        else if (syst==17 && dm==1 && pt>=25 && pt<30) fr=taufr_dm1_y[1]+taufr_dm1_yhigh[1];
        else if (syst==18 && dm==1 && pt>=25 && pt<30) fr=taufr_dm1_y[1]-taufr_dm1_ylow[1];
        else if (syst==19 && dm==1 && pt>=30 && pt<35) fr=taufr_dm1_y[2]+taufr_dm1_yhigh[2];
        else if (syst==20 && dm==1 && pt>=30 && pt<35) fr=taufr_dm1_y[2]-taufr_dm1_ylow[2];
        else if (syst==21 && dm==1 && pt>=35 && pt<40) fr=taufr_dm1_y[3]+taufr_dm1_yhigh[3];
        else if (syst==22 && dm==1 && pt>=35 && pt<40) fr=taufr_dm1_y[3]-taufr_dm1_ylow[3];
        else if (syst==23 && dm==1 && pt>=40 && pt<50) fr=taufr_dm1_y[4]+taufr_dm1_yhigh[4];
        else if (syst==24 && dm==1 && pt>=40 && pt<50) fr=taufr_dm1_y[4]-taufr_dm1_ylow[4];
        else if (syst==25 && dm==1 && pt>=50 && pt<60) fr=taufr_dm1_y[5]+taufr_dm1_yhigh[5];
        else if (syst==26 && dm==1 && pt>=50 && pt<60) fr=taufr_dm1_y[5]-taufr_dm1_ylow[5];
        else if (syst==27 && dm==1 && pt>=60) fr=taufr_dm1_y[6]+taufr_dm1_yhigh[6];
        else if (syst==28 && dm==1 && pt>=60) fr=taufr_dm1_y[6]-taufr_dm1_ylow[6];

        if (syst==29 && dm==10 && pt<25) fr=taufr_dm10_y[0]+taufr_dm10_yhigh[0];
        else if (syst==30 && dm==10 && pt<25) fr=taufr_dm10_y[0]-taufr_dm10_ylow[0];
        else if (syst==31 && dm==10 && pt>=25 && pt<30) fr=taufr_dm10_y[1]+taufr_dm10_yhigh[1];
        else if (syst==32 && dm==10 && pt>=25 && pt<30) fr=taufr_dm10_y[1]-taufr_dm10_ylow[1];
        else if (syst==33 && dm==10 && pt>=30 && pt<35) fr=taufr_dm10_y[2]+taufr_dm10_yhigh[2];
        else if (syst==34 && dm==10 && pt>=30 && pt<35) fr=taufr_dm10_y[2]-taufr_dm10_ylow[2];
        else if (syst==35 && dm==10 && pt>=35 && pt<40) fr=taufr_dm10_y[3]+taufr_dm10_yhigh[3];
        else if (syst==36 && dm==10 && pt>=35 && pt<40) fr=taufr_dm10_y[3]-taufr_dm10_ylow[3];
        else if (syst==37 && dm==10 && pt>=40 && pt<50) fr=taufr_dm10_y[4]+taufr_dm10_yhigh[4];
        else if (syst==38 && dm==10 && pt>=40 && pt<50) fr=taufr_dm10_y[4]-taufr_dm10_ylow[4];
        else if (syst==39 && dm==10 && pt>=50 && pt<60) fr=taufr_dm10_y[5]+taufr_dm10_yhigh[5];
        else if (syst==40 && dm==10 && pt>=50 && pt<60) fr=taufr_dm10_y[5]-taufr_dm10_ylow[5];
        else if (syst==41 && dm==10 && pt>=60) fr=taufr_dm10_y[6]+taufr_dm10_yhigh[6];
        else if (syst==42 && dm==10 && pt>=60) fr=taufr_dm10_y[6]-taufr_dm10_ylow[6];

        if (syst==43 && dm>10 && pt<25) fr=taufr_dm11_y[0]+taufr_dm11_yhigh[0];
        else if (syst==44 && dm>10 && pt<25) fr=taufr_dm11_y[0]-taufr_dm11_ylow[0];
        else if (syst==45 && dm>10 && pt>=25 && pt<30) fr=taufr_dm11_y[1]+taufr_dm11_yhigh[1];
        else if (syst==46 && dm>10 && pt>=25 && pt<30) fr=taufr_dm11_y[1]-taufr_dm11_ylow[1];
        else if (syst==47 && dm>10 && pt>=30 && pt<35) fr=taufr_dm11_y[2]+taufr_dm11_yhigh[2];
        else if (syst==48 && dm>10 && pt>=30 && pt<35) fr=taufr_dm11_y[2]-taufr_dm11_ylow[2];
        else if (syst==49 && dm>10 && pt>=35 && pt<40) fr=taufr_dm11_y[3]+taufr_dm11_yhigh[3];
        else if (syst==50 && dm>10 && pt>=35 && pt<40) fr=taufr_dm11_y[3]-taufr_dm11_ylow[3];
        else if (syst==51 && dm>10 && pt>=40 && pt<50) fr=taufr_dm11_y[4]+taufr_dm11_yhigh[4];
        else if (syst==52 && dm>10 && pt>=40 && pt<50) fr=taufr_dm11_y[4]-taufr_dm11_ylow[4];
        else if (syst==53 && dm>10 && pt>=50 && pt<60) fr=taufr_dm11_y[5]+taufr_dm11_yhigh[5];
        else if (syst==54 && dm>10 && pt>=50 && pt<60) fr=taufr_dm11_y[5]-taufr_dm11_ylow[5];
        else if (syst==55 && dm>10 && pt>=60) fr=taufr_dm11_y[6]+taufr_dm11_yhigh[6];
        else if (syst==56 && dm>10 && pt>=60) fr=taufr_dm11_y[6]-taufr_dm11_ylow[6];

        return fr;
}

double GetMuFR(float pt, TGraphAsymmErrors *g_mufr, int syst){

    Double_t *mufr_y = g_mufr->GetY();
    Double_t *mufr_ylow = g_mufr->GetEYlow();
    Double_t *mufr_yhigh = g_mufr->GetEYhigh();

    double fr=0.5;

    if (pt<15) fr=mufr_y[0];
    else if (pt<20) fr=mufr_y[1];
    else if (pt<30) fr=mufr_y[2];
    else if (pt<40) fr=mufr_y[3];
    else fr=mufr_y[4];

    if (syst==1 && pt<15) fr=mufr_y[0]+mufr_yhigh[0];
    else if (syst==2 && pt<15) fr=mufr_y[0]-mufr_ylow[0];
    else if (syst==3 && pt>=15 && pt<20) fr=mufr_y[1]+mufr_yhigh[1];
    else if (syst==4 && pt>=15 && pt<20) fr=mufr_y[1]-mufr_ylow[1];
    else if (syst==5 && pt>=20 && pt<30) fr=mufr_y[2]+mufr_yhigh[2];
    else if (syst==6 && pt>=20 && pt<30) fr=mufr_y[2]-mufr_ylow[2];
    else if (syst==7 && pt>=30 && pt<40) fr=mufr_y[3]+mufr_yhigh[3];
    else if (syst==8 && pt>=30 && pt<40) fr=mufr_y[3]-mufr_ylow[3];
    else if (syst==9 && pt>=40) fr=mufr_y[4]+mufr_yhigh[4];
    else if (syst==10 && pt>=40) fr=mufr_y[4]-mufr_ylow[4];

    return fr;
}

double GetEleFR(float pt, TGraphAsymmErrors *g_efr, int syst){

    Double_t *efr_y = g_efr->GetY();
    Double_t *efr_ylow = g_efr->GetEYlow();
    Double_t *efr_yhigh = g_efr->GetEYhigh();

    double fr=0.5;
    
    if (pt<15) fr=efr_y[0];
    else if (pt<20) fr=efr_y[1];
    else if (pt<30) fr=efr_y[2];
    else if (pt<40) fr=efr_y[3];
    else fr=efr_y[4];

    if (syst==1 && pt<15) fr=efr_y[0]+efr_yhigh[0];
    else if (syst==2 && pt<15) fr=efr_y[0]-efr_ylow[0];
    else if (syst==3 && pt>=15 && pt<20) fr=efr_y[1]+efr_yhigh[1];
    else if (syst==4 && pt>=15 && pt<20) fr=efr_y[1]-efr_ylow[1];
    else if (syst==5 && pt>=20 && pt<30) fr=efr_y[2]+efr_yhigh[2];
    else if (syst==6 && pt>=20 && pt<30) fr=efr_y[2]-efr_ylow[2];
    else if (syst==7 && pt>=30 && pt<40) fr=efr_y[3]+efr_yhigh[3];
    else if (syst==8 && pt>=30 && pt<40) fr=efr_y[3]-efr_ylow[3];
    else if (syst==9 && pt>=40) fr=efr_y[4]+efr_yhigh[4];
    else if (syst==10 && pt>=40) fr=efr_y[4]-efr_ylow[4];

    return fr;
}

