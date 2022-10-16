#include "Dialog.h"
namespace Global {
	bool test = false;
	DialogGroup dialogFallback{ []() {return true;}, std::vector<std::string>{"Hi."}};
}