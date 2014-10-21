#include "VBFHiggsToInvisible/TriggerStudies/interface/HLTAlgoPFDijet.h"

using namespace std;

HLTAlgoPFDijet::HLTAlgoPFDijet(){

  m_algoName = "";
  m_vbf  = false;
  m_jet0 = 0;
  m_jet1 = 0;
  m_mjj  = 0;
  m_deta = 0;
  m_dphi = 0;
}

HLTAlgoPFDijet::HLTAlgoPFDijet(std::string algoName){
  
  m_algoName = algoName;
  
  m_vbf  = false;
  m_jet0 = 0;
  m_jet1 = 0;
  m_mjj  = 0;
  m_deta = 0;
  m_dphi = 100;
}

HLTAlgoPFDijet::~HLTAlgoPFDijet(){}

bool HLTAlgoPFDijet::evaluate(HLTEventData *hltData){
  
  if(!hltData->getPathFired("HLT_PFMET_PFVBF_v1")){return false;}
  
  bool out = false;
  
  HLTPathData* thePath = hltData->getPathData("HLT_PFMET_PFVBF_v1");  
  vector<HLTDiobject*> myDijet = thePath->getFilterDiobjects("hltDiPFJet10");
  
  for(unsigned i=0; i<myDijet.size(); i++){
    
    HLTDiobject* dijet = myDijet[i];
    
    // Checking jet pT conditions (dijet jets are pT sorted)
    if(dijet->j0()->pt()<m_jet0){continue;}
    if(dijet->j1()->pt()<m_jet1){continue;}
    
    // Checking VBF condition
    if(m_vbf){
      if(!dijet->vbf()){
        continue;
      }
    }

    if(dijet->mjj() <m_mjj) {continue;} // Checking VBF condition
    if(dijet->deta()<m_deta){continue;} // Checking Delta eta
    if(dijet->dphi()>m_dphi){continue;} // Checking Delta phi
    
    // If all conditions passed algo passed!
    out = true;
    break;
  }
  
  return out;
}

void HLTAlgoPFDijet::setVBF(bool vbf){
  m_vbf = vbf;
}

void HLTAlgoPFDijet::setJetsMinPt(double jet0,double jet1){
  m_jet0 = jet0;
  m_jet1 = jet1;
}

void HLTAlgoPFDijet::setDijetMinMjj(double mjj){
  m_mjj = mjj;
}

void HLTAlgoPFDijet::setDijetMinDEta(double deta){
  m_deta = deta;
}

void HLTAlgoPFDijet::setDijetMaxDPhi(double dphi){
  m_dphi = dphi;
}