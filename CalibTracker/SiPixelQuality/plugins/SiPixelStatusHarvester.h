#ifndef SiPixelStatusHarvester_H
#define SiPixelStatusHarvester_H

/** \class SiPixelStatusHarvester
 *  harvest per-lumi prduced SiPixelDetector status and make the payload for SiPixelQualityFromDB
 *
 */
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "CalibTracker/SiPixelQuality/interface/SiPixelStatusManager.h"
#include "CondFormats/SiPixelObjects/interface/SiPixelQuality.h"

// PixelDQM Framework
#include "DQM/SiPixelPhase1Common/interface/SiPixelPhase1Base.h"

class SiPixelStatusHarvester : public SiPixelPhase1Base {
    enum {
      BADROC,
      PERMANENTBADROC,
      FEDERRORROC,
      STUCKTBMROC,
      OTHERBADROC,
      PROMPTBADROC
    };

 public:

  // Constructor
  SiPixelStatusHarvester(const edm::ParameterSet&);

  // Destructor
  ~SiPixelStatusHarvester() override;
  
  // Operations
  void beginJob            () override;
  void endJob              () override;  
  void endRunProduce       (edm::Run&, const edm::EventSetup&) final;
  void analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) final;

  void beginLuminosityBlock(const edm::LuminosityBlock&, const edm::EventSetup&) final;
  void endLuminosityBlock  (const edm::LuminosityBlock&, const edm::EventSetup&) final;

 private:

  // Parameters
  std::string outputBase_;
  int aveDigiOcc_;
  int nLumi_;
  std::string moduleName_;
  std::string label_;  
  // harvest helper classs that setup the IOV structure
  SiPixelStatusManager siPixelStatusManager_;
  // debug mode
  bool debug_;
  // for DB output naming
  std::string recordName_;

  // permanent known bad components
  const SiPixelQuality* badPixelInfo_;

  // totoal number of lumi blocks with non-zero pixel DIGIs
  int countLumi_;
  // last lumi section of the SiPixeDetectorStatus data
  edm::LuminosityBlockNumber_t endLumiBlock_;

  // "step function" for IOV
  edm::LuminosityBlockNumber_t stepIOV(edm::LuminosityBlockNumber_t pin, std::map<edm::LuminosityBlockNumber_t,edm::LuminosityBlockNumber_t> IOV);

  const TrackerGeometry* trackerGeometry_ = nullptr;
  const SiPixelFedCabling* cablingMap_ = nullptr;
  std::map<int, int> sensorSize_;

  // pixel online to offline pixel row/column 
  std::map<int, std::map<int, std::pair<int,int> > > pixelO2O_;

};

#endif
