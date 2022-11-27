#include "Debug.h"

ofstream Debug::debug("Debug.Log.txt");
bool Debug::isDisableDebugging = false;
void Debug::Log(string log) {
	if (!isDisableDebugging && debug.is_open()) { debug << log << '\n'; }
}
void Debug::DisableDebugging() {
	if (debug.is_open()) { debug.close(); }
	isDisableDebugging = true;
}
void Debug::Release() {
	if (debug.is_open()) {
		debug << "[ Debug ] : Release";
		debug.close();
	}
}
