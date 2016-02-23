#pragma once
#include "Province.h"

class ProvinceContainer
{
public:
    ProvinceContainer();
    ~ProvinceContainer();

    Province* getProvince(int id);
    void addProvince(Province * prov) { provincesVec.push_back(prov); }

private:
    std::vector<Province*> provincesVec; //container for all loaded provinces
};

class ProvinceContainerSingleton
{
public:
    static ProvinceContainer * getProvinceContainer() { return provCont; }
private:
    static ProvinceContainer * provCont;
};