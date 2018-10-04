///// Head file ///////

///// C++ libraries

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
#include <sstream>

///// ROOT libraries

#include "TRandom3.h"
#include "TMath.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TH2.h"
#include "TTree.h"
#include "TGraph.h"
#include "TStyle.h"
#include "TNamed.h"
#include "TFile.h"
#include "TChain.h"
#include "TColor.h"

///////////////// Other dependancies

#include "orbitStruct.h"

///////////////////////////////////////////////////////

#define EPS 1.e-12

//////////////////////////// Generation Parameters ////////////////////////////

///////////////////////////////////////////////////////////////////////////////


const static UInt_t random_seed = 9;
const static Int_t number_SBI_files = 3;

const static time_t time_stamp=time(0);                                     //Setting timestamp for the out files
const static Int_t Nchoices=6;
const static Int_t Nev[Nchoices]={5,10,50,100,500,1000};                    //Number of events selected in each second. The result should not depend on that !


/////////////////////////////// Dependency Paths //////////////////////////////

///////////////////////////////////////////////////////////////////////////////


// ================= LOCAL COMPUTER

//////////////////////////// Input path for SBI data files: 

const static TString sbi_path = "/Users/enrico/Documents/Università/Magistrale/Tesi/MyCode/MyRepos/GitHub/Salomon/SampleSBI/";

//////////////////////////// Input path for the acceptance final histo:

const static std::string evDistr_final_plot = "/Users/enrico/Documents/Università/Magistrale/Tesi/MyCode/MyRepos/GitHub/Stuff/DAMPE-GAcceptance/SubmitJob/ToJarvis/results/1529438721_maps_result.root";

//////////////////////////// Outh paths for logs and ROOT files:

const static std::string output_log = "/Users/enrico/Documents/Università/Magistrale/Tesi/MyCode/MyRepos/GitHub/Salomon/logs/";
const static std::string output_root = "/Users/enrico/Documents/Università/Magistrale/Tesi/MyCode/MyRepos/GitHub/Salomon/results/";


//////////////////////////////// SBI Parameters ///////////////////////////////

///////////////////////////////////////////////////////////////////////////////

const static TString sbi_subsample = "010";
const static std::string string_sbi_subsample = "010";                           //This is usefull into the function that writes log files and output ROOT files


///////////////////////////////////////////////////////////////////////////////////////////// Functions         ;-)

////////////////// Stuff functions //////////////////

extern std::string output_path_creator(const Int_t out_choose);
extern void create_and_initialize_log(std::ofstream &log_file);
extern void log_file_init(std::ofstream &out_file);
extern void read_SBI_data(Float_t &galactic_lat,Float_t &galactic_lon,Float_t &geographic_lat,Float_t &geographic_lon,Float_t sat_ra[],Float_t sat_dec[],UInt_t &sec,UShort_t &n_events,bool &good,TChain &tree,Float_t &lvtime,TString sbi_data_path,std::ofstream &out_file);

// extern Bool_t check_sbi_loading(Float_t galactic_lat,Float_t galactic_lon,Float_t geographic_lat,Float_t geographic_lon,Float_t sat_ra[],Float_t sat_dec[],UInt_t sec,UShort_t n_events);
// extern void reinitialize_all_variables(Float_t &galactic_lat,Float_t &galactic_lon,Float_t &geographic_lat,Float_t &geographic_lon,Float_t sat_ra[],Float_t sat_dec[],UInt_t &sec,UShort_t &n_events);
// extern Bool_t chech_if_null_variable(Float_t in_variable);

extern void create_binning(Int_t n_bin_lat,Double_t lat_bin_min,Double_t lat_bin_max,Double_t* &binning,Bool_t cos_scale);
extern void obtain_evDist(TH2D &evDist,std::ofstream &log_file);
extern void obtain_orbit_rate(TH2D &Orbit,TH2D &Rate,TChain &tree,Float_t &g_lat,Float_t &g_lon,Float_t &geo_lat,Float_t &geo_lon,Float_t sat_ra[],Float_t sat_dec[],UInt_t &sec,UShort_t &n_ev,bool &good,std::ofstream &log_file);
extern void extract_mean_rate(TH2D &Rate,Int_t &tmp_rate,Double_t geo_lon,Double_t geo_lat);
extern void EvaluatePercentage(Double_t &percentage,Int_t entries,Int_t idx,std::ofstream &log_file);

////////////////// Analysis functions //////////////////

extern void Iris(Int_t events,TH2D &map,TH2D &evDist,Float_t sat_ra[],Float_t sat_dec[],Float_t lvtime);
extern void CustomIris(TH2D &evDist,TH2D &IsoMap_ModIris,TH2D &Rate,Float_t geo_lon,Float_t geo_lat,Float_t sat_ra[],Float_t sat_dec[]);
extern void compute_maps_ratio(std::vector<TH2D> &iso_map,Int_t maps_number,TH2D &iso_map_ModIris,TH2D &mapsRatio,TH1D &hRatio,std::ofstream &log_file);
extern Int_t found_best_Iris_map(std::vector<TH2D> &iso_map,Int_t maps_number,TH2D &iso_map_ModIris);
extern void create_ratio_distribution(TH2D* mapsRatio,TH1D &hRatio);

//////////// Coordinates Transformation Functions ////////////

extern void from_local_to_galactic(Double_t costheta,Double_t phi,Double_t &l,Double_t &b,Float_t sat_ra[],Float_t sat_dec[]);
extern void from_satellite_to_celestial(Float_t ra[],Float_t dec[],double vectorin[],AtPolarVect &vector_out);
extern void AtVect_To_AtPolarVect(double in_vector[],AtPolarVect &vector_out);
extern void invert_AtPolarVect_direction(AtPolarVect vector_out,AtPolarVect &vector_out_inv);
extern void AtPolarVect_to_vector(AtPolarVect &input_polar,double out_array[]);
extern void from_celestial_to_galactic(Double_t ra,Double_t dec,Double_t &l,Double_t &b);
