////////////////////////////////////////////////////////////////////////////////////////////////////
// LicenseStatus.cpp
// Copyright (c) 2019 Pdfix. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
\page CPP_Samples C++ Samples
- \subpage LicenseStatus_cpp
*/
/*!
\page LicenseStatus_cpp Activate the license
Example how to update product standard license.
\snippet /LicenseStatus.hpp LicenseStatus_cpp
*/

#include "pdfixsdksamples/LicenseStatus.h"

//! [LicenseStatus_cpp]
// system
#include <string>
#include <iostream>
// other libraries
#include "Pdfix.h"

using namespace PDFixSDK;
namespace LicenseStatus {
    // write license status into an output stream
  void Run(std::ostream& os) {
    // initialize Pdfix
    if (!Pdfix_init(Pdfix_MODULE_NAME))
      throw std::runtime_error("Pdfix initialization fail");

    Pdfix* pdfix = GetPdfix();
    if (!pdfix)
      throw std::runtime_error("GetPdfix fail");

    auto authorization = pdfix->GetAuthorization();
    if (!authorization)
      throw PdfixException();

    auto stm = pdfix->CreateMemStream();
    if (!stm)
      throw PdfixException();

    if (!authorization->SaveToStream(stm, kDataFormatJson))
      throw PdfixException();
    
    std::string json;
    json.resize((int)stm->GetSize());
    stm->Read(0, (uint8_t*)&json[0], (int)json.size());
    
    os << json;
    
    stm->Destroy();
    pdfix->Destroy();
  }
}

//! [LicenseStatus_cpp]
