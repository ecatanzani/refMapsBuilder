
#include "MyHead.h"

void evaluate_percentage(Double_t &perc,Int_t total_events,Int_t idx_ev) {
    
    if(((Double_t)idx_ev/total_events)>(perc*0.01)) {
        std::cout << "-> Tree events: [ " << perc << " % ]" << std::endl;
        perc++;
    }
    
}
