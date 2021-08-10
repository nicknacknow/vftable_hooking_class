#include "vftable_hook.h"

void vftable_hook::initiate(int vftable_size) {
	uintptr_t* new_vftable = new uintptr_t[vftable_size];
	memcpy(cast(new_vftable, void*), cast(this->stored_vftable, void*), vftable_size * sizeof uintptr_t);

	DWORD old_prot = NULL;
	VirtualProtect(
		(LPVOID)this->target_class, sizeof LPVOID, 
		PAGE_READWRITE, &old_prot);
	*cast(this->target_class, uintptr_t*) = cast(new_vftable, uintptr_t);
	VirtualProtect(cast(this->target_class, LPVOID), sizeof LPVOID, old_prot, NULL);
}

void vftable_hook::restore() {
	DWORD old_prot;
	VirtualProtect(cast(this->target_class, LPVOID), sizeof LPVOID, PAGE_READWRITE, &old_prot);
	*cast(this->target_class, uintptr_t*) = this->stored_vftable;
	VirtualProtect(cast(this->target_class, LPVOID), sizeof LPVOID, old_prot, NULL);
}

void vftable_hook::add_func(uintptr_t func, int index, LPVOID* callback) {
	*callback = cast(this->get_current_vftable() + index * sizeof uintptr_t, LPVOID);

	*cast((this->get_current_vftable() + index * sizeof uintptr_t), uintptr_t*) = func;

	//*cast(*cast(this->target_class, uintptr_t*) + index * sizeof uintptr_t, uintptr_t*) = func;
}

uintptr_t vftable_hook::get_current_vftable() {
	return *cast(this->target_class, uintptr_t*);
}

int vftable_hook::get_vftable_size() {
	// to-do
}