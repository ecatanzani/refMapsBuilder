
#include "MyHead.h"

int main(int argc,char** argv) {
    
    if(argc<2) {
        std::cerr << "\n\nPlease, insert SBI file list, as argument\n\n";
        exit(100);
    }
    
    ////////////////////////////////////////////////////////// Variables declaration ///////////////////////////////////////////////////
    
    //////////////////////// TChain variables ////////////////////////
    
    Float_t g_lat = 0,g_lon = 0,geo_lat = 0,geo_lon = 0,sat_ra[3],sat_dec[3],lvtime=0;
    UInt_t sec = 0;
    UShort_t n_ev = 0;
    Int_t total_events = 0;
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
    create_binning(n_bin_lat,lat_bin_min,lat_bin_max,binning,true);
    
    //////////// Stuff variables
    
    TChain tree("SBItree");
    std::vector<std::string> SBIpaths;
    std::string listPath(argv[1]);
    gRandom->SetSeed(random_seed);
    std::string root_out_path = output_path_creator();
    std::vector<TEllipse> elly;
    
    TCanvas fCanvas("fCanvas","Satellite Pointing Check");
    fCanvas.cd();
    
    Double_t perc = 0;
    
    TString elly_name;
    
    //////////// Histos
    
    TH2D evDist;
    TH2D IRISmap("IRISmap","IRIS Map (1000)",n_bin_lon,lon_bin_min,lon_bin_max,n_bin_lat,binning);
    TH2D SBIpointment("SBIpointment","SBI Galactic Pointing Coordinates",n_bin_lon,lon_bin_min,lon_bin_max,n_bin_lat,binning);
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    load_list_paths(listPath,SBIpaths);
    read_SBI_data(g_lat,g_lon,geo_lat,geo_lon,sat_ra,sat_dec,sec,n_ev,good,tree,lvtime,SBIpaths,total_events);
    obtain_evDist(evDist);
    
    elly.resize(total_events);
    
    for(Int_t idx_ev = 0; idx_ev < total_events; ++idx_ev)  {
        tree.GetEntry(idx_ev);
        
        evaluate_percentage(perc,total_events,idx_ev);
        
        elly_name = "elly_";
        elly_name += idx_ev;
        
        if(!good)
            continue;
        
        if(g_lon>180)
            g_lon-=360;
        if(geo_lon>180)
            geo_lon-=360;
        
        ///////////// Setting arrays' values in radiants
        for(Int_t aidx=0; aidx<3; aidx++) {
            sat_ra[aidx]*=TMath::DegToRad();
            sat_dec[aidx]*=TMath::DegToRad();
        }
        
        Iris(floor(IRIS_events*lvtime),IRISmap,evDist,sat_ra,sat_dec);
        SBIpointment.Fill(g_lon,g_lat,1);
        
        TEllipse tmp_elly(g_lon,g_lat,3,2.8);
        tmp_elly.SetFillStyle(0);
        tmp_elly.SetLineWidth(3);
        tmp_elly.SetLineColor(kRed);
        TEllipse* ptmp_elly = &tmp_elly;
        new (&elly.at(idx_ev)) (TEllipse)(*(TEllipse*)ptmp_elly->Clone(elly_name));
        
    }
    
    //////////// Canvas superimpose
    
    IRISmap.Draw("colz");
    for(Int_t idx = 0; idx < total_events; ++idx)
        elly[idx].Draw("same");
    
    ///////////////////////////////
    
    std::cout << "\n\nSimulation comleted\n\n";
    
    //////////// Writing results
    
    TFile outFile(root_out_path.c_str(),"RECREATE");
    if(outFile.IsZombie()) {
        std::cerr << "\n\nError writing ROOT output file: " << root_out_path << "\n\n";
        exit(100);
    }
    
    fCanvas.Write();
    IRISmap.Write();
    SBIpointment.Write();
    
    outFile.Close();
    
    return 0;
    
}
