
#include "MyHead.h"

int main(int argc,char *argv[]) {

    ////////////////////////////////////////////////////////// Variables declaration ///////////////////////////////////////////////////
    
    //////////////////////// TChain variables ////////////////////////
    
    Double_t g_lat = 0;
    Double_t g_lon = 0;
    Double_t geo_lat = 0;
    Double_t geo_lon = 0;
    
    Double_t sat_ra[3],sat_dec[3];
    Float_t lvtime = 0;
    
    UInt_t sec = 0;
    UShort_t n_ev = 0;
    bool good = true;
    
    ///////// Set initial arrays' variables to 0
    
    for(Int_t idx=0; idx<3; idx++) {
        sat_ra[idx]=0;
        sat_dec[idx]=0;
    }
    
    //////////// Costheta flat binning variables

    Int_t n_bin_lon = 360;
    Double_t lon_bin_min = -180.0;
    Double_t lon_bin_max = 180.0;

    Int_t n_bin_lat = 180;
    Double_t lat_bin_min = -90.0;
    Double_t lat_bin_max = 90.0;

    Double_t* binning = nullptr;
    
    //////////// Stuff variables
    
    Long64_t chain_entries;
    UInt_t random_seed;
    Double_t perc = 0;
    TChain tree("SBItree");
    
    std::vector<std::string> SBIpaths;
    std::string list_path(argv[1]);
    
    obtain_single_paths(SBIpaths,list_path);
    std::string tmpSeed = SBIpaths.at(SBIpaths.size()-1);
    random_seed = std::stoul(tmpSeed,nullptr);
    SBIpaths.erase(SBIpaths.begin()+SBIpaths.size()-1);
    
    std::string log_path = output_path_creator(0,SBIpaths.at(0)),root_out_path = output_path_creator(1,SBIpaths.at(0));
    std::ofstream output_log_file(log_path);
    
    gRandom->SetSeed(random_seed);
    
    std::vector<TEllipse> elly;
    
    TString elly_name;
    
    TCanvas fCanvas("fCanvas","Satellite Pointing Check");
    fCanvas.cd();
    
    //////////// Histos
    
    create_binning(n_bin_lat,lat_bin_min,lat_bin_max,binning,true);
    
    static TH2D evDist;
    TH2D IRISmap("IRISmap","IRIS Map (1000); Galactic Longitude (#circ);  Galactic Latitude (#circ); Entries",n_bin_lon,lon_bin_min,lon_bin_max,n_bin_lat,binning);
    TH2D SBIpointment("SBIpointment","SBI Galactic Pointing Coordinates; Galactic Longitude (#circ);  Galactic Latitude (#circ); Entries ",n_bin_lon,lon_bin_min,lon_bin_max,n_bin_lat,binning);
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    create_and_initialize_log(output_log_file,random_seed);
    read_SBI_data(g_lat,g_lon,geo_lat,geo_lon,sat_ra,sat_dec,sec,n_ev,good,tree,lvtime,output_log_file,SBIpaths,chain_entries);
    obtain_evDist(evDist,output_log_file);
    
    elly.resize(chain_entries);
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    
    for(Long64_t tree_idx = 0; tree_idx < chain_entries; ++tree_idx) {
        
        tree.GetEntry(tree_idx);
        
        if(!good)
            continue;

        if(g_lon>180)
            g_lon-=360;
        if(geo_lon>180)
            geo_lon-=360;

        evaluatePercentage(perc,chain_entries,tree_idx,output_log_file);
        
        elly_name = "elly_";
        elly_name += tree_idx;
        
        ///////////// Setting arrays' values in radiants
        for(Int_t aidx=0; aidx<3; aidx++) {
            sat_ra[aidx]*=TMath::DegToRad();
            sat_dec[aidx]*=TMath::DegToRad();
        }
        
        ///////////// IRIS (ICRC 2014) simulation
        Iris(floor(Nev[5]*lvtime),IRISmap,evDist,sat_ra,sat_dec);
        
        SBIpointment.Fill(g_lon,g_lat,1);
        
        TEllipse tmp_elly(g_lon,g_lat,3,2.8);
        tmp_elly.SetFillStyle(0);
        tmp_elly.SetLineWidth(3);
        tmp_elly.SetLineColor(kRed);
        TEllipse* ptmp_elly = &tmp_elly;
        new (&elly.at(tree_idx)) (TEllipse)(*(TEllipse*)ptmp_elly->Clone(elly_name));
        
    }
 
    std::cout<<"\n\nSimulation Completed !\n\n";
    output_log_file << "\n\nSimulation Completed !\n\n";
    
    //////////// Canvas superimpose
    
    IRISmap.Draw("colz");
    for(Int_t idx = 0; idx < chain_entries; ++idx)
        elly[idx].Draw("same");
    
    //////////////////////////////////// Creating out file
    
    TFile results_file(root_out_path.c_str(),"RECREATE");
    if(results_file.IsZombie()) {
        std::cout << "\n\nError writing ROOT results TFile. Prorgram finished \n\n";
        output_log_file << "\n\nError ROOT results TFile. Prorgram finished \n\n";
        exit(100);
    }
    
    //////////////////////////////////// Writing results
    
    fCanvas.Write();
    IRISmap.Write();
    SBIpointment.Write();
    
    results_file.Write();
    
    //////////////////////////////////// Closing files
  
    results_file.Close();
    
    output_log_file.close();
    
    return 0;
  
}
