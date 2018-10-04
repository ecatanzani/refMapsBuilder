///// Head file ///////

///// C++ libraries

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>
#include <string>

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
#include "TEllipse.h"
#include "TFile.h"
#include "TChain.h"
#include "TColor.h"

///////////////// Other dependancies

#include "orbitStruct.h"

///////////////////////////////////////////////////////

#define EPS 1.e-12

//////////////////////////// Generation Parameters ////////////////////////////

///////////////////////////////////////////////////////////////////////////////


const static time_t time_stamp=time(0);                                     //Setting timestamp for the out files
const static Int_t Nchoices = 6;
const static Int_t Nev[Nchoices] = {5,10,50,100,500,1000};                  //Number of events selected in each second. The result should not depend on that !


/////////////////////////////// Dependency Paths //////////////////////////////

///////////////////////////////////////////////////////////////////////////////

// ================= INFN CNAF

//////////////////////////// Input path for the acceptance final histo:

const static std::string evDistr_final_plot = "/storage/gpfs_data/dampe/users/ecatanzani/MyRepos/DAMPE/Stuff/DAMPE-GAcceptance/results/GAcceptanceFinalPlot.root";

//////////////////////////// Outh paths for logs and ROOT files:

const static std::string output_log = "./";
const static std::string output_root = "./";


///////////////////////////////////////////////////////////////////////////////////////////// Functions         ;-)

////////////////// Stuff functions //////////////////

extern std::string output_path_creator(const Int_t out_choose,const std::string first_path);
extern void create_and_initialize_log(std::ofstream &log_file,UInt_t random_seed);
extern void log_file_init(std::ofstream &out_file,UInt_t random_seed);

extern void read_SBI_data(
                            Double_t &galactic_lat,
                            Double_t &galactic_lon,
                            Double_t &geographic_lat,
                            Double_t &geographic_lon,
                            Double_t sat_ra[],
                            Double_t sat_dec[],
                            UInt_t &sec,
                            UShort_t &n_events,
                            bool &good,
                            TChain &tree,
                            Float_t &lvtime,
                            std::ofstream &out_file,
                            std::vector<std::string> &SBIpaths,
                            Long64_t &chain_entries
                          );

// extern Bool_t check_sbi_loading(Float_t galactic_lat,Float_t galactic_lon,Float_t geographic_lat,Float_t geographic_lon,Float_t sat_ra[],Float_t sat_dec[],UInt_t sec,UShort_t n_events);
// extern void reinitialize_all_variables(Float_t &galactic_lat,Float_t &galactic_lon,Float_t &geographic_lat,Float_t &geographic_lon,Float_t sat_ra[],Float_t sat_dec[],UInt_t &sec,UShort_t &n_events);
// extern Bool_t chech_if_null_variable(Float_t in_variable);

extern void get_name(std::string all_path,std::string &f_name);
extern void obtain_single_paths(std::vector<std::string> &SBIpaths,std::string list_path);
extern void create_binning(Int_t n_bin_lat,Double_t lat_bin_min,Double_t lat_bin_max,Double_t* &binning,Bool_t cos_scale);
extern void obtain_evDist(TH2D &evDist,std::ofstream &log_file);

extern void obtain_orbit_rate(
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
                              );

extern void extract_mean_rate(TH2D &Rate,Int_t &tmp_rate,Double_t geo_lon,Double_t geo_lat);
extern void evaluatePercentage(Double_t &percentage,Long64_t entries,Long64_t idx,std::ofstream &log_file);

////////////////// Analysis functions //////////////////

extern void Iris(
                    Int_t events,
                    TH2D &map,
                    TH2D &evDist,
                    Double_t sat_ra[],
                    Double_t sat_dec[]
                 );

extern void CustomIris(
                        TH2D &evDist,
                        TH2D &IsoMap_ModIris,
                        TH2D &Rate,
                        Double_t geo_lon,
                        Double_t geo_lat,
                        Double_t sat_ra[],
                        Double_t sat_dec[]
                       );

extern void compute_maps_ratio(
                                std::vector<TH2D> &iso_map,
                                Int_t maps_number,
                                TH2D &iso_map_ModIris,
                                TH2D &mapsRatio,
                                TH1D &hRatio,
                                std::ofstream &log_file
                               );

extern Int_t found_best_Iris_map(std::vector<TH2D> &iso_map,Int_t maps_number,TH2D &iso_map_ModIris);
extern void create_ratio_distribution(TH2D* mapsRatio,TH1D &hRatio);

//////////// Coordinates Transformation Functions ////////////

extern void from_local_to_galactic(
                                   Double_t costheta,
                                   Double_t phi,
                                   Double_t &l,
                                   Double_t &b,
                                   Double_t sat_ra[],
                                   Double_t sat_dec[]
                                   );

extern void from_satellite_to_celestial(Double_t ra[],Double_t dec[],double vectorin[],AtPolarVect &vector_out);
extern void AtVect_To_AtPolarVect(double in_vector[],AtPolarVect &vector_out);
extern void invert_AtPolarVect_direction(AtPolarVect vector_out,AtPolarVect &vector_out_inv);
extern void AtPolarVect_to_vector(AtPolarVect &input_polar,double out_array[]);
extern void from_celestial_to_galactic(Double_t ra,Double_t dec,Double_t &l,Double_t &b);
