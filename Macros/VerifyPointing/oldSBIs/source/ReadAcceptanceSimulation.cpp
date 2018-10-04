
#include "MyHead.h"

void obtain_evDist(TH2D &evDist) {
    
    TFile infile(evDistr_final_plot.c_str());
    if(infile.IsZombie()) {
        std::cerr << "\n\nError opening DAMPE Events Distribution TFile. Prorgram finished \n\n";
        exit(100);
    }
    
    new (&evDist) TH2D(*(TH2D*)infile.Get("EventsDistribution"));
    evDist.SetName("evDistribution");
    
    infile.Close();
}
