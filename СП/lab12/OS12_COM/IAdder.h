#pragma once
#include <objbase.h>

interface IAdder : public IUnknown 
{
	STDMETHOD(Add(const double, const double, double&)) PURE;
	STDMETHOD(Sub(const double, const double, double&)) PURE;
};
