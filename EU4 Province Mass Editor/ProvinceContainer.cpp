#include "ProvinceContainer.h"

ProvinceContainer * ProvinceContainerSingleton::provCont = new ProvinceContainer();

ProvinceContainer::ProvinceContainer()
{
}


ProvinceContainer::~ProvinceContainer()
{
}

Province * ProvinceContainer::getProvince(int id)
{
    for (auto it : provincesVec)
    {
        if (it->getID() == id)
            return it;
    }
    return nullptr;
}
