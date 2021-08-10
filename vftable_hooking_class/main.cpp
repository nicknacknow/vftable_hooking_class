#include <Windows.h>
#include <iostream>
#include <thread>
#include <future>

#include "vftable_hook.h"

class Test_Class {
public:
	virtual const char* getName() {
		return this->name;
	}
private:
	const char* name = "Test 1";
};

typedef const char* (__thiscall* td_getName)();
td_getName cb_getName;

const char* hook_getName() {
	return "lol";
}

int main() {
	Test_Class test;

	printf("test: %p\n", &test);
	vftable_hook hook(cast(&test, uintptr_t), 1);
	
	hook.add_func(cast(&hook_getName, uintptr_t), 0, cast(&cb_getName, LPVOID*));

	std::cin.get();
	return 1;
}