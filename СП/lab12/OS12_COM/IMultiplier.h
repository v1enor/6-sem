#pragma once
#include <objbase.h>

interface IMultiplier : public IUnknown
{
	STDMETHOD(Mul(const double, const double, double&)) PURE;
	STDMETHOD(Div(const double, const double, double&)) PURE;
};