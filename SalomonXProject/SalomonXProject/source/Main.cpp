
#include "MyHead.h"

int main(int argc,char *argv[]) {

    ////////////////////////////////////////////////////////// Variables declaration ///////////////////////////////////////////////////
    
    //////////////////////// TChain variables ////////////////////////
    
    Float_t g_lat=0,g_lon=0,geo_lat=0,geo_lon=0,sat_ra[3],sat_dec[3],lvtime=0;
    UInt_t sec=0;
    UShort_t n_ev=0;
    bool good=true;
    
    ///////// Set initial arrays' variables to 0
    
    for(Int_t idx=0; idx<3; idx++) {
        sat_ra[idx]=0;
        sat_dec[idx]=0;
    }
    
    //////////// Costheta flat binning variables

    Int_t n_bin_lon = 360;                                                                      // -> Number of bins along longitude axis
    Double_t lon_bin_min = -180.0;                                                              // -> Set max and min for longitude binning
    Double_t lon_bin_max = 180.0;

    Int_t n_bin_lat = 180;                                                                      // -> Number of bins along latitude axis
    Double_t lat_bin_min = -90.0;                                                               // -> Set max and min for latitude binning
    Double_t lat_bin_max = 90.0;

    Double_t* binning = nullptr;                                                                // -> Array used to store the custom binning intervals !!!
    
    //////////// Stuff variables
    
    Int_t chain_entries;                                                                        // -> Variable that stores the whole number of tchain entries
    Double_t perc=0;                                                                            // -> Just used to store the percentage values
    TString iso_map_name,iso_map_title;                                                         // -> Name and title of the isotrope sky map, made with different number of events
    TString c_iso_map_name;
    std::string log_path = output_path_creator(0),root_out_path = output_path_creator(1);       // -> Log end ROOT result file variables
    std::ofstream output_log_file(log_path);                                                    // -> log file creation !
    TChain tree("SBItree");                                                                     // -> Events ROOT TChain
    TRandom3 r_gen(random_seed);                                                                // -> Set a random seed and declaring a TRandom3 objects
    gRandom->SetSeed(random_seed);
    
    //////////// Histos
    
    create_binning(n_bin_lat,lat_bin_min,lat_bin_max,binning,true);                             // -> Custom binning for Healpix representation
    
    static TH2D evDist;
    TH2D Orbit("orbit","Exposure; Geographic Longitude (#circ);  Geographic Latitude (#circ); Exposure (s)", 180, -180, 180, 90, -90.0, 90.0);
    TH2D Rate("rate","Rate; Geographic Longitude (#circ);  Geographic Latitude (#circ); Rate (hz)", 180, -180, 180, 90, -90.0, 90.0);
  
    // ---------- Isotropic maps with infinite and realistic statistics
    
    std::vector<TH2D> IsoMap_Iris;
    IsoMap_Iris.resize(Nchoices);

    for(Int_t idx_h=0; idx_h<Nchoices; idx_h++) {
        c_iso_map_name = "SkyMap_";
        iso_map_name = "Iso_SkyMap_";
        iso_map_title = "Isotropic SkyMap (";
        iso_map_name += Nev[idx_h];
        iso_map_title += Nev[idx_h];
        c_iso_map_name += Nev[idx_h];
        iso_map_title += "); Galactic Longitude (#circ);  Galactic Latitude (#circ); Entries";
        TH2D tmpMap(iso_map_name,iso_map_title,n_bin_lon,lon_bin_min,lon_bin_max,n_bin_lat,binning);
        TH2D *ptmpMap = &tmpMap;
        new (&IsoMap_Iris[idx_h]) TH2D(*(TH2D*)ptmpMap->Clone(c_iso_map_name));
    }
  
    TH2D MapsRatio;
    TH1D HRatio("HRatio","Ratio Events Distribution",100,0,2);
    TH2D IsoMap_ModIris("IsoMap_ModIris","Reference Isotropic Sky Map (Mod Iris) ; Galactic Longitude (#circ);  Galactic Latitude (#circ); Entries",n_bin_lon,lon_bin_min,lon_bin_max,n_bin_lat,binning);
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    create_and_initialize_log(output_log_file);
    read_SBI_data(g_lat,g_lon,geo_lat,geo_lon,sat_ra,sat_dec,sec,n_ev,good,tree,lvtime,sbi_path,output_log_file);
    obtain_evDist(evDist,output_log_file);
    obtain_orbit_rate(Orbit,Rate,tree,g_lat,g_lon,geo_lat,geo_lon,sat_ra,sat_dec,sec,n_ev,good,output_log_file);
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    chain_entries = tree.GetEntries();
 
    for(Int_t tree_idx=0; tree_idx<chain_entries; tree_idx++) {
        tree.GetEntry(tree_idx);
        std::cout << "\n" << tree_idx;
        if((sec%100000)==0)
            continue;                           //there was a bug in the SBI production    !! Remember to verify is it's still present with new SBI files !
        if(!good)
            continue;

        if(g_lon>180)
            g_lon-=360;
        if(geo_lon>180)
            geo_lon-=360;

        EvaluatePercentage(perc,chain_entries,tree_idx,output_log_file);
        
        ///////////// Setting arrays' values in radiants
        for(Int_t aidx=0; aidx<3; aidx++) {
            sat_ra[aidx]*=TMath::DegToRad();
            sat_dec[aidx]*=TMath::DegToRad();
        }
        
        ///////////// IRIS (ICRC 2014) simulation
        for(Int_t ch_idx=0; ch_idx<Nchoices; ch_idx++)
            Iris(floor(Nev[ch_idx]*lvtime),IsoMap_Iris[ch_idx],evDist,sat_ra,sat_dec,lvtime);
    
        ///////////// IRIS (ICRC 2014) CUSTOM
        CustomIris(evDist,IsoMap_ModIris,Rate,geo_lon,geo_lat,sat_ra,sat_dec);
        
    }
 
    compute_maps_ratio(IsoMap_Iris,Nchoices,IsoMap_ModIris,MapsRatio,HRatio,output_log_file);
    
    std::cout<<"\n\nSimulation Completed !\n\n";
    output_log_file << "\n\nSimulation Completed !\n\n";
  
    //////////////////////////////////// Creating out file
    
    TFile results_file(root_out_path.c_str(),"RECREATE");
    if(results_file.IsZombie()) {
        std::cout << "\n\nError writing ROOT results TFile. Prorgram finished \n\n";
        output_log_file << "\n\nError ROOT results TFile. Prorgram finished \n\n";
        exit(-2);
    }
    
    //////////////////////////////////// Writing results
    
    for(Int_t idx_h=0; idx_h<Nchoices; idx_h++)
        IsoMap_Iris[idx_h].Write();
    
    IsoMap_ModIris.Write();
    MapsRatio.Write();
    HRatio.Write();
    
    results_file.Write();
    
    //////////////////////////////////// Closing files
  
    results_file.Close();
    
    output_log_file.close();
    
    return 0;
  
}
