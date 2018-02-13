#include "CalibTracker/SiPixelQuality/interface/SiPixelDetectorStatus.h"
#include "DataFormats/Common/interface/Wrapper.h"

namespace DataFormats_SiPixelStatus {
  struct dictionary {

    SiPixelRocStatus rs;
    std::vector<SiPixelRocStatus> v_rs;
    SiPixelModuleStatus ms;
    std::pair<int, SiPixelModuleStatus> p_ms;
    std::map<int, SiPixelModuleStatus> m_ms;
    SiPixelDetectorStatus ss;
    edm::Wrapper<SiPixelDetectorStatus> w_ss;

  };
}

