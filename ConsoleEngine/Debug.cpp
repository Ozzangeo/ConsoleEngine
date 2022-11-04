#include "Debug.h"

ofstream Debug::debug("Debug.Log.txt");
void Debug::Log(string log) {
	if (debug.is_open()) { debug << log << '\n'; }
}
void Debug::Release() {
	if (debug.is_open()) {
		debug << "[ Debug ] : Release";
		debug.close();
	}
}
