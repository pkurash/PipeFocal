// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See http://alice-o2.web.cern.ch/license for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

#ifndef ALICEO2_PASSIVE_PIPEFOCAL_H
#define ALICEO2_PASSIVE_PIPEFOCAL_H

#include "FairModule.h" // for FairModule
#include "Rtypes.h"     // for Pipe::Class, ClassDef, Pipe::Streamer

class TGeoPcon;

namespace o2
{
namespace passive
{
class PipeFocal : public FairModule
{
 public:
  PipeFocal(const char* name, const char* Title = "Alice Pipe", float rho = 0.f, float thick = 0.f);
  PipeFocal();

  ~PipeFocal() override;
  void ConstructGeometry() override;

  /// Clone this object (used in MT mode only)
  FairModule* CloneModule() const override;

  float getRmin() const { return mBePipeRmax - mBePipeThick; }
  float getRmax() const { return mBePipeRmax; }
  float getWidth() const { return mBePipeThick; }
  float getDz() const { return mIpHLength; }

 private:
  void createMaterials();
  PipeFocal(const PipeFocal& orig);
  PipeFocal& operator=(const PipeFocal&);

  TGeoPcon* MakeMotherFromTemplate(const TGeoPcon* shape, Int_t imin = -1, Int_t imax = -1, Float_t r0 = 0.,
                                   Int_t nz = -1);
  TGeoPcon* MakeInsulationFromTemplate(TGeoPcon* shape);
  TGeoVolume* MakeBellow(const char* ext, Int_t nc, Float_t rMin, Float_t rMax, Float_t dU, Float_t rPlie,
                         Float_t dPlie);
  TGeoVolume* MakeBellowCside(const char* ext, Int_t nc, Float_t rMin, Float_t rMax, Float_t rPlie, Float_t dPlie);

  float mBePipeRmax = 0.;  // outer diameter of the Be section
  float mBePipeThick = 0.; // Be section thickness
  float mIpHLength = 0.;   // half length of the beampipe around the IP // FixMe: up to now, hardcoded to 57.25cm

  ClassDefOverride(PipeFocal, 1);
};
} // namespace passive
} // namespace o2
#endif // PIPEFOCAL_H
