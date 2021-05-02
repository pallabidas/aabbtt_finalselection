double GetSF2016(int WP, float x, int flavour, int syst){

   if (WP==1){
      if (fabs(flavour)==4 or fabs(flavour)==5){
        if (syst==0){
	   return 0.653526*((1.+(0.220245*x))/(1.+(0.14383*x)));
        }
      }
      else {
        if (syst==0) return 1.09286+-0.00052597*x+1.88225e-06*x*x+-1.27417e-09*x*x*x;
     }
   }
   else return 0;
}


double bTagEventWeight2016(int nBtaggedJets, float bjetpt_1, int bjetflavour_1, float bjetpt_2, int bjetflavour_2, int WP, int syst, int nBTags)
{
  if (nBtaggedJets > 2) return -10000;
  if( nBTags > 2 ) return -10000;

  /*
    ##################################################################
    Event weight matrix:
    ------------------------------------------------------------------
    nBTags\b-tagged jets  |    0        1             2
    ------------------------------------------------------------------
      0                   |    1      1-SF      (1-SF1)(1-SF2)
                          |
      1                   |    0       SF    SF1(1-SF2)+(1-SF1)SF2
                          |
      2                   |    0        0           SF1SF2
    ##################################################################
  */
  
  if( nBTags > nBtaggedJets) return 0;
  if( nBTags==0 && nBtaggedJets==0) return 1;

  double weight = 0;
  if(nBtaggedJets==1){
    double SF = GetSF2016(WP,bjetpt_1,bjetflavour_1,syst);
    for( unsigned int i=0; i<=1; ++i ){
      if( i != nBTags ) continue;
      weight += pow(SF,i)*pow(1-SF,1-i);
    }
  }
  else if(nBtaggedJets==2 ){
    double SF1 = GetSF2016(WP,bjetpt_1,bjetflavour_1,syst);
    double SF2 = GetSF2016(WP,bjetpt_2,bjetflavour_2,syst);
    
    for( unsigned int i=0; i<=1; ++i ){
      for( unsigned int j=0; j<=1; ++j ){
        if( (i+j) != nBTags ) continue;
        weight += pow(SF1,i)*pow(1-SF1,1-i)*pow(SF2,j)*pow(1-SF2,1-j);
      }
    }
  }
  return weight;
}

