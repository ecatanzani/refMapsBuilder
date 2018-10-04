
#include "MyHead.h"

void obtain_evDist(TH2D &evDist,std::ofstream &log_file) {
    
    TFile infile(evDistr_final_plot.c_str());
    if(infile.IsZombie()) {
        std::cout << "\n\nError opening DAMPE Events Distribution TFile. Prorgram finished \n\n";
        log_file << "\n\nError opening DAMPE Events Distribution TFile. Prorgram finished \n\n";
        exit(-2);
    }
    
    new (&evDist) TH2D(*(TH2D*)infile.Get("EventsDistribution"));
    evDist.SetName("evDistribution");
    
    infile.Close();
}
