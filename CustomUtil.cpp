#include "CustomUtil.h"

template <typename T>
T clip(const T& n, const T& lower, const T& upper)
{
	return n <= lower ? lower : n >= upper ? upper : n;
}

int clip(const int& n, const int& lower, const int& upper)
{
	return n <= lower ? lower : n >= upper ? upper : n;
}