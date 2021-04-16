////////////////////////////////////////////////////////////////////////////////////////////////////
// DocumentSecurity.cpp
// Copyright (c) 2021 Pdfix. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "pdfixsdksamples/DocumentSecurity.h"

// project
#include "Pdfix.h"

using namespace PDFixSDK;

namespace DocumentSecurity {

  void RemoveSecurity(
      const std::wstring& open_path,  // source PDF document
      const std::wstring& save_path,  // output PDF doucment
      const std::wstring& password    // source PDF document passowrd
  ) {
    // initialize Pdfix
    if (!Pdfix_init(Pdfix_MODULE_NAME))
      throw std::runtime_error("Pdfix initialization fail");

    Pdfix* pdfix = GetPdfix();
    if (!pdfix)
      throw std::runtime_error("GetPdfix fail");

    if (pdfix->GetVersionMajor() != PDFIX_VERSION_MAJOR || 
      pdfix->GetVersionMinor() != PDFIX_VERSION_MINOR ||
      pdfix->GetVersionPatch() != PDFIX_VERSION_PATCH)
      throw std::runtime_error("Incompatible version");

    auto doc = pdfix->OpenDoc(open_path.c_str(), password.c_str());
    if (!doc)
      throw std::runtime_error(pdfix->GetError());

    // remove document security by setting security handler to null
    //doc->SetSecurityHandler(nullptr);

    if (!doc->Save(save_path.c_str(), kSaveFull) )
      throw std::runtime_error(pdfix->GetError());

    doc->Close();
    pdfix->Destroy();
  }

  void AddSecurity(
      const std::wstring& open_path,  // source PDF document
      const std::wstring& save_path,  // output PDF doucment
      const std::wstring& password    // output PDF document passowrd
  ) {
// TODO:
  }

  void AddCustomSecurity(
      const std::wstring& open_path,  // source PDF document
      const std::wstring& save_path  // output PDF doucment
  ) {
// TODO:
  }

  void RemoveCustomSecurity(
      const std::wstring& open_path,  // source PDF document
      const std::wstring& save_path  // output PDF doucment
  ) {
    // TODO:
  }
};

