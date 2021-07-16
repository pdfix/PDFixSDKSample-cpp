////////////////////////////////////////////////////////////////////////////////////////////////////
// ExtractData.cpp
// Copyright (c) 2020 Pdfix. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "pdfixsdksamples/ExtractData.h"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
// project
#include "Pdfix.h"

namespace ExtractData {

  void ExtractStructElement(PdsStructElement* elem, ptree &node, const DataType& data_types) {
    auto put_non_empty = [&](const auto &key, const auto &value) {
      if (!value.length()) return;
      node.put(key, EncodeText(value));  
    };
    put_non_empty("type", elem->GetType(true));
    put_non_empty("title", elem->GetTitle());
    put_non_empty("lang", elem->GetLang());
    put_non_empty("id", elem->GetId());
    put_non_empty("alt", elem->GetAlt());
    put_non_empty("actual_text", elem->GetActualText());

    ptree kids_node;
    for (int i = 0; i < elem->GetNumKids(); i++) {
      ptree kid_node;
      switch (elem->GetKidType(i)) {
        case kPdsStructKidElement: {
          // structure element reference
          kid_node.put("kid_type", "element");
          auto kid_obj = elem->GetKidObject(i);
          ExtractStructObject(elem->GetStructTree(), kid_obj, kid_node, data_types);
          break;
        }
        case kPdsStructKidStreamContent: {
          kid_node.put("kid_type", "stream_content");
          // object reference
          auto kid_obj = elem->GetKidObject(i);
          kid_node.put("obj", kid_obj->GetId());
          break;
        }
        case kPdsStructKidObject: {
          kid_node.put("kid_type", "object");
          // object reference
          auto kid_obj = elem->GetKidObject(i);
          kid_node.put("obj", kid_obj->GetId());
          break;
        }
        case kPdsStructKidPageContent: {
          kid_node.put("kid_type", "page_content");
          // content element reference
          kid_node.put("mcid", elem->GetKidMcid(i));
          kid_node.put("page_num", elem->GetKidPageNumber(i));
          break;
        }
        default:; // unknown/invalid reference
      }
      kids_node.push_back(std::make_pair("", kid_node));
    }
    if (!kids_node.empty())
      node.put_child("kids", kids_node);
  }

  void ExtractStructObject(PdsStructTree* struct_tree, PdsObject* object, ptree &node, 
    const DataType& data_types) {
    auto elem = struct_tree->GetStructElement(object);
    if (!elem)
      throw PdfixException();
    ExtractStructElement(elem, node, data_types);
  }

  void ExtractStructTree(PdsStructTree* struct_tree, ptree &node, const DataType& data_types) {
    ptree kids_node;
    for (int i = 0; i < struct_tree->GetNumKids(); i++) {
      auto struct_elem_obj = struct_tree->GetKidObject(i);
      ptree kid_node;
      ExtractStructObject(struct_tree, struct_elem_obj, kid_node, data_types);
      kids_node.push_back(std::make_pair("", kid_node));
    }
    if (!kids_node.empty())
      node.put_child("kids", kids_node);
  }
}