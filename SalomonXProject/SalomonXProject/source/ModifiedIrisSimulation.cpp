
#include "MyHead.h"

void CustomIris(TH2D &evDist,TH2D &IsoMap_ModIris,TH2D &Rate,Float_t geo_lon,Float_t geo_lat,Float_t sat_ra[],Float_t sat_dec[]) {
    
    Int_t tmp_rate=0;
    Int_t ev_counter=0;
    Double_t costheta=0,phi=0,l=-999,b=-999;
    
    extract_mean_rate(Rate,tmp_rate,geo_lon,geo_lat);
    
    while(ev_counter!=tmp_rate) {
        evDist.GetRandom2(costheta,phi);
        from_local_to_galactic(costheta,phi,l,b,sat_ra,sat_dec);
    
        if(isnan(l))
            continue;
    
        if(l>180)
            l-=360;
        
        IsoMap_ModIris.Fill(l,b,1);
        ev_counter++;
    }
}
