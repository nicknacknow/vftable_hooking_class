#pragma once
#include <Windows.h>
#include <vector>

#define cast(a,b) (reinterpret_cast<b>(a))

class vftable_hook {
public:
	vftable_hook(uintptr_t c, int vftable_size) : target_class(c), stored_vftable(this->get_current_vftable()) { this->initiate(vftable_size); }

	void initiate(int vftable_size/* = this->get-vftable_size() */);
	void restore();

	void add_func(uintptr_t func, int index, LPVOID* callback);
private:
	uintptr_t get_current_vftable();
	int get_vftable_size();

	uintptr_t target_class;
	uintptr_t stored_vftable;
	bool is_hooked = false;
};