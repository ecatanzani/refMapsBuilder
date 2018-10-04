
#include "MyHead.h"

void Iris(
          Int_t events,
          TH2D &map,
          TH2D &evDist,
          Double_t sat_ra[],
          Double_t sat_dec[]
          )

{
    
    Double_t b = 0,l = 0;
    Double_t costheta = -999, phi = -999;
    
    for(Int_t idx_ev = 0; idx_ev < events; ++idx_ev)  {
        
        evDist.GetRandom2(costheta,phi);
        from_local_to_galactic(costheta,phi,l,b,sat_ra,sat_dec);
        if(isnan(l)) {
            idx_ev--;
            continue;
        }
      
        if(l>180.0)
            l-=360.0;

        map.Fill(l,b,1);
      
    }
}
