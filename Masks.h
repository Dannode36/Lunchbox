#pragma once
class Mask
{
};

namespace Masks {
	const int dialateMask[3][3] = {
		{0, 1, 0},
		{1, 0, 1},
		{0, 1, 0}
	};
	const int squareMask[3][3] = {
		{1, 1, 1},
		{1, 1, 1},
		{1, 1, 1}
	};
}