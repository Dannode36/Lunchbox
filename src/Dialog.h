#pragma once
#include <functional>
#include <vector>
#include <string>

struct DialogGroup {
	std::function<bool()> condition;
	std::vector<std::string> lines;
};

class Dialog {
public:
	std::vector<DialogGroup> dialogs;

	DialogGroup& GetDialog();

	Dialog();
	Dialog(std::string name);
	~Dialog();
};