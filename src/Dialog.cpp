#include "Dialog.h"
#include "Globals.h"

DialogGroup& Dialog::GetDialog() {
	for (auto& group : dialogs) {
		if (group.condition()) {
			return group;
		}
	}
	return Global::dialogFallback;
}

Dialog::Dialog() {}
Dialog::Dialog(std::string name) {
	//Load stuff
}
Dialog::~Dialog() {

}