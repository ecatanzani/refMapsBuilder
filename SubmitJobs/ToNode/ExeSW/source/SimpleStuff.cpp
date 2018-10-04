
#include "MyHead.h"

void evaluatePercentage(Double_t &percentage,Long64_t entries,Long64_t idx,std::ofstream &log_file) {
    if(((Double_t)idx/entries)>(percentage*0.01)) {
        std::cout<<"-> Tree events: [ "<<percentage<<" % ]"<<std::endl;
        log_file<<"-> Tree events: [ "<<percentage<<" % ]"<<std::endl;
        percentage++;
    }
}

void obtain_orbit_rate(
                        TH2D &Orbit,
                        TH2D &Rate,
                        TChain &tree,
                        Double_t &g_lat,
                        Double_t &g_lon,
                        Double_t &geo_lat,
                        Double_t &geo_lon,
                        Double_t sat_ra[],
                        Double_t sat_dec[],
                        UInt_t &sec,
                        UShort_t &n_ev,
                        Long64_t &chain_entries,
                        bool &good,
                        std::ofstream &log_file
                       )

{

    TH2D* pRate = nullptr;
    TH2D* pOrbit = nullptr;
    
    for(Long64_t tree_idx=0; tree_idx<chain_entries; ++tree_idx) {
        
        tree.GetEntry(tree_idx);
        
        if(!good)
            continue;
        
        ///////////// Setting correct range for galactic latitude and longitude
        
        if(g_lon>180)
            g_lon-=360;
        if(geo_lon>180)
            geo_lon-=360;
        
        Orbit.Fill(geo_lon,geo_lat);
        Rate.Fill(geo_lon,geo_lat,n_ev);
        
    }
    
    pRate=&Rate;
    pOrbit=&Orbit;
       
    pRate->Divide(pOrbit);

    std::cout << "Rate and Orbit histos has been calculated \n\n";
    log_file <<  "Rate and Orbit histos has been calculated \n\n";
    
}

void extract_mean_rate(TH2D &Rate,Int_t &tmp_rate,Double_t geo_lon,Double_t geo_lat) {
    
    Int_t Xbin = 0,Ybin = 0;
    
    TAxis *Yaxis = Rate.GetYaxis();
    TAxis *Xaxis = Rate.GetXaxis();
    Ybin = Yaxis->FindBin(geo_lat);
    Xbin = Xaxis->FindBin(geo_lon);
    
    tmp_rate = Rate.GetBinContent(Xbin,Ybin);
    
}
