#pragma once
#include "Province.h"
namespace ProvinceLoader
{
    Province* loadProvince(const std::string& location);
    bool saveProvinces(std::vector<std::string>* locationsVec, Province * prov);
}

