#include "CustomUtil.h"

template <typename T>
T clip(const T& n, const T& lower, const T& upper)
{
	return n <= lower ? lower : n >= upper ? upper : n;
}