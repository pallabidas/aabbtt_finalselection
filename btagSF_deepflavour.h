//In ntuples, "flavour"==5 for b, 4 for c, 0 for light udsg
//In btag csv, "jetFlavour"==0 for b, 1 for c, 2 for light udsg
//2018 formula from https://twiki.cern.ch/twiki/pub/CMS/BtagRecommendation102X/DeepJet_102XSF_WP_V1.csv
//2017 formula from https://twiki.cern.ch/twiki/pub/CMS/BtagRecommendation94X/DeepFlavour_94XSF_WP_V3_B_F.csv
//2016 formula from https://twiki.cern.ch/twiki/pub/CMS/BtagRecommendation2016Legacy/DeepJet_2016LegacySF_WP_V1.csv
double GetbtagSF(int yr, float x, int flavour, int syst){//Medium WP only
    if (yr==2018){
        if (syst==0){
            if (fabs(flavour)==4 or fabs(flavour)==5) return 1.0097+(-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18))))))));
            else return 1.59373+-0.00113028*x+8.66631e-07*x*x+-1.10505/x;
        }
        if (syst==1){//b and c up; udsg central
            if (fabs(flavour)==4){
                if (x<30) return (1.0097+(-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18)))))))))+0.19459584355354309;
                else if (x<50) return (1.0097+(-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18)))))))))+0.04693598672747612;
                else if (x<70) return (1.0097+(-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18)))))))))+0.041476961225271225;
                else if (x<100) return (1.0097+(-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18)))))))))+0.037213429808616638;
                else if (x<140) return (1.0097+(-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18)))))))))+0.033781636506319046;
                else if (x<200) return (1.0097+(-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18)))))))))+0.035268638283014297;
                else if (x<300) return (1.0097+(-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18)))))))))+0.043516248464584351;
                else if (x<600) return (1.0097+(-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18)))))))))+0.10369165241718292;
                else return (1.0097+(-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18)))))))))+0.29925653338432312;
            }
            else if (fabs(flavour)==5){
                if (x<30) return (1.0097+(-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18)))))))))+0.064865283668041229;
                else if (x<50) return (1.0097+(-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18)))))))))+0.015645328909158707;
                else if (x<70) return (1.0097+(-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18)))))))))+0.013825654052197933;
                else if (x<100) return (1.0097+(-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18)))))))))+0.012404476292431355;
                else if (x<140) return (1.0097+(-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18)))))))))+0.011260545812547207;
                else if (x<200) return (1.0097+(-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18)))))))))+0.011756212450563908;
                else if (x<300) return (1.0097+(-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18)))))))))+0.01450541615486145;
                else if (x<600) return (1.0097+(-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18)))))))))+0.034563884139060974;
                else return (1.0097+(-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18)))))))))+0.099752180278301239;
            }
            else return 1.59373+-0.00113028*x+8.66631e-07*x*x+-1.10505/x;
        }
        if (syst==2){//b and c down; udsg central
            if (fabs(flavour)==4){
                if (x<30) return 1.0097+((-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18))))))))-0.19459584355354309);
                else if (x<50) return 1.0097+((-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18))))))))-0.04693598672747612);
                else if (x<70) return 1.0097+((-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18))))))))-0.041476961225271225);
                else if (x<100) return 1.0097+((-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18))))))))-0.037213429808616638);
                else if (x<140) return 1.0097+((-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18))))))))-0.033781636506319046);
                else if (x<200) return 1.0097+((-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18))))))))-0.035268638283014297);
                else if (x<300) return 1.0097+((-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18))))))))-0.043516248464584351);
                else if (x<600) return 1.0097+((-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18))))))))-0.10369165241718292);
                else return 1.0097+((-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18))))))))-0.29925653338432312);
            }
            else if (fabs(flavour)==5){
                if (x<30) return 1.0097+((-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18))))))))-0.064865283668041229);
                else if (x<50) return 1.0097+((-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18))))))))-0.015645328909158707);
                else if (x<70) return 1.0097+((-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18))))))))-0.013825654052197933);
                else if (x<100) return 1.0097+((-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18))))))))-0.012404476292431355);
                else if (x<140) return 1.0097+((-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18))))))))-0.011260545812547207);
                else if (x<200) return 1.0097+((-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18))))))))-0.011756212450563908);
                else if (x<300) return 1.0097+((-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18))))))))-0.01450541615486145);
                else if (x<600) return 1.0097+((-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18))))))))-0.034563884139060974);
                else return 1.0097+((-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18))))))))-0.099752180278301239);
            }
            else return 1.59373+-0.00113028*x+8.66631e-07*x*x+-1.10505/x;
        }
        if (syst==3){//b and c central; udsg up
            if (fabs(flavour)==4 or fabs(flavour)==5) return 1.0097+(-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18))))))));
            else return (1.59373+-0.00113028*x+8.66631e-07*x*x+-1.10505/x)*(1+(0.142253+0.000227323*x+-2.71704e-07*x*x));
        }
        if (syst==4){//b and c central; udsg down
            if (fabs(flavour)==4 or fabs(flavour)==5) return 1.0097+(-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18))))))));
            else return (1.59373+-0.00113028*x+8.66631e-07*x*x+-1.10505/x)*(1-(0.142253+0.000227323*x+-2.71704e-07*x*x));
        }
    }
    if (yr==2017){
        if (syst==0){
            if (fabs(flavour)==4 or fabs(flavour)==5) return 0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x)));
            else return 1.40779+-0.00094558*x+8.74982e-07*x*x+-4.67814/x;
        }
        if (syst==1){//b and c up; udsg central
            if (fabs(flavour)==4){
                if (x<30) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.22882774472236633;
                else if (x<50) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.079194873571395874;
                else if (x<70) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.07602342963218689;
                else if (x<100) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.073120191693305969;
                else if (x<140) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.078529126942157745;
                else if (x<200) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.086113773286342621;
                else if (x<300) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.11148297786712646;
                else if (x<600) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.10986694693565369;
                else return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.12645691633224487;
            }
            else if (fabs(flavour)==5){
                if (x<30) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.076275914907455444;
                else if (x<50) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.026398291811347008;
                else if (x<70) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.02534114383161068;
                else if (x<100) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.02437339723110199;
                else if (x<140) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.026176376268267632;
                else if (x<200) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.02870459109544754;
                else if (x<300) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.037160992622375488;
                else if (x<600) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.036622315645217896;
                else return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.04215230792760849;
            }
            else return 1.40779+-0.00094558*x+8.74982e-07*x*x+-4.67814/x;
        }
        if (syst==2){//b and c down; udsg central
            if (fabs(flavour)==4){
                if (x<30) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.22882774472236633;
                else if (x<50) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.079194873571395874;
                else if (x<70) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.07602342963218689;
                else if (x<100) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.073120191693305969;
                else if (x<140) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.078529126942157745;
                else if (x<200) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.086113773286342621;
                else if (x<300) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.11148297786712646;
                else if (x<600) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.10986694693565369;
                else return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.12645691633224487;
            }
            else if (fabs(flavour)==5){
                if (x<30) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.076275914907455444;
                else if (x<50) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.026398291811347008;
                else if (x<70) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.02534114383161068;
                else if (x<100) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.02437339723110199;
                else if (x<140) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.026176376268267632;
                else if (x<200) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.02870459109544754;
                else if (x<300) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.037160992622375488;
                else if (x<600) return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.036622315645217896;
                else return (0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.04215230792760849;
            }
            else return 1.40779+-0.00094558*x+8.74982e-07*x*x+-4.67814/x;
        }
        if (syst==3){//b and c central; udsg up
            if (fabs(flavour)==4 or fabs(flavour)==5) return 0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x)));
            else return (1.40779+-0.00094558*x+8.74982e-07*x*x+-4.67814/x)*(1+(0.100661+0.000294578*x+-3.2739e-07*x*x));
        }
        if (syst==4){//b and c central; udsg down
            if (fabs(flavour)==4 or fabs(flavour)==5) return 0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x)));
            else return (1.40779+-0.00094558*x+8.74982e-07*x*x+-4.67814/x)*(1-(0.100661+0.000294578*x+-3.2739e-07*x*x));
        }
    }
    if (yr==2016){
        if (syst==0){
            if (fabs(flavour)==4 or fabs(flavour)==5) return 0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x)));
            else return 1.09149+3.31851e-05*x+2.34826e-07*x*x+-0.888846/x;
        }
        if (syst==1){//b and c up; udsg central
            if (fabs(flavour)==4){
                if (x<30) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))+0.13967660069465637;
                else if (x<50) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))+0.049122259020805359;
                else if (x<70) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))+0.043598789721727371;
                else if (x<100) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))+0.038782715797424316;
                else if (x<140) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))+0.036949444562196732;
                else if (x<200) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))+0.043523617088794708;
                else if (x<300) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))+0.04994809627532959;
                else if (x<600) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))+0.090836621820926666;
                else return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))+0.16102308034896851;
            }
            else if (fabs(flavour)==5){
                if (x<30) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))+0.046558864414691925;
                else if (x<50) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))+0.016374086961150169;
                else if (x<70) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))+0.014532930217683315;
                else if (x<100) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))+0.012927571311593056;
                else if (x<140) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))+0.012316481210291386;
                else if (x<200) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))+0.014507872052490711;
                else if (x<300) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))+0.016649365425109863;
                else if (x<600) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))+0.030278874561190605;
                else return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))+0.053674362599849701;
            }
            else return 1.09149+3.31851e-05*x+2.34826e-07*x*x+-0.888846/x;
        }
        if (syst==2){//b and c down; udsg central
            if (fabs(flavour)==4){
                if (x<30) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))-0.13967660069465637;
                else if (x<50) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))-0.049122259020805359;
                else if (x<70) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))-0.043598789721727371;
                else if (x<100) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))-0.038782715797424316;
                else if (x<140) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))-0.036949444562196732;
                else if (x<200) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))-0.043523617088794708;
                else if (x<300) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))-0.04994809627532959;
                else if (x<600) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))-0.090836621820926666;
                else return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))-0.16102308034896851;
            }
            else if (fabs(flavour)==5){
                if (x<30) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))-0.046558864414691925;
                else if (x<50) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))-0.016374086961150169;
                else if (x<70) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))-0.014532930217683315;
                else if (x<100) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))-0.012927571311593056;
                else if (x<140) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))-0.012316481210291386;
                else if (x<200) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))-0.014507872052490711;
                else if (x<300) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))-0.016649365425109863;
                else if (x<600) return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))-0.030278874561190605;
                else return (0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x))))-0.053674362599849701;
            }
            else return 1.09149+3.31851e-05*x+2.34826e-07*x*x+-0.888846/x;
        }
        if (syst==3){//b and c central; udsg up
            if (fabs(flavour)==4 or fabs(flavour)==5) return 0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x)));
            else return (1.09149+3.31851e-05*x+2.34826e-07*x*x+-0.888846/x)*(1+(0.127379+0.000199537*x+-2.43111e-07*x*x));
        }
        if (syst==4){//b and c central; udsg down
            if (fabs(flavour)==4 or fabs(flavour)==5) return 0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x)));
            else return (1.09149+3.31851e-05*x+2.34826e-07*x*x+-0.888846/x)*(1-(0.127379+0.000199537*x+-2.43111e-07*x*x));
        }
    }
}
