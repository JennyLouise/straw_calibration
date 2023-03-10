#include <TH1D.h>
#include <TPolyMarker.h>
#include "TList.h"
#include "TF1.h"
#include "H5Cpp.h"
#include "TCanvas.h"


class CalibrationCalculator {

public:

  bool plottingGraphs = false;
  int strawResolution = 512;


  /// \brief takes measured and simulated events as a vector of vectors of ints, where each vector of ints represents a straw, and each int represents a neutron event's position along the straw
  /// and calculates a 4th order polynomial relationship between the measured peaks of events and the simulated peaks of events, then saving it to a json file
  void calculateCalibration(std::vector<std::vector<int>> measuredEvents, std::vector<std::vector<int>> simulatedEvents);

  std::vector<double> getStrawPeaksSimple(std::vector<int> hits, int strawNum, std::string file_prefix);
  
  /// \brief takes the hits for a single straw and uses ROOTs ShowPeaks function for first pass, and then multi gaussian fitting to refine
  /// and returns the x values of the peaks on the straw
  std::vector<double> getStrawPeaksGaussian(std::vector<int> hits, int strawNum, std::string file_prefix);
  
  
  void fillHistogram1D(std::vector<int> hits, TH1D* histogram);
  
  /// \brief given the x and y values of pre-calculated peaks, and a histogram, refines those peaks using multi-gaussian fits
  /// x will be adjusted according to the newly refined peak locations, return is void
  void gaussianFit(std::vector<double> x, std::vector<double> y, TH1D* histogram);
  
  
  std::pair<std::vector<double>, std::vector<double>> findPeaks(TH1D* histogram);
    
  
  std::vector<double> calculateStrawCalibrationParameters(std::vector<double> measuredPeaks, std::vector<double> simulatedPeaks, int strawId);


  void writePeaksToFile(std::vector<double> peaks, std::string filename);
  
  
  void loadPeaksFromFile();
  void saveCalibrationParametersToFile(std::map<int, std::vector<double>> calibrationPerStraw);

  // sorts the elements in array a from smallest to largest, and re-organises
  // array b the same way, regardless of the numerical order of elements in b
  // n is the length of both arrays a and b 
  void selectionSort(std::vector<double> a, std::vector<double> b, int n);

  bool checkRange(std::vector<double> strawCalibrationParams);

  std::vector<double> applyCalibrationParams(std::vector<double> measured, std::vector<double> params);


};