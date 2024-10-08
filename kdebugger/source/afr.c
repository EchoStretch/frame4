#include "afr.h"

#include "hooks.h"

int sys_open_hook(struct thread *td, struct syscall_open *args) { // this entire hook must NOT be rip dependent
	uint32_t edx, eax;
    __asm__ ("rdmsr" : "=d"(edx), "=a"(eax) : "c"(0xC0000082));
	uint8_t* ptrKernel = (uint8_t *)((((uint64_t)edx) << 32) | (uint64_t)eax) - __Xfast_syscall;

	struct hook_data *data = (struct hook_data *)( *(uint64_t*)ptrKernel );
	struct proc_505 *castedProc = (struct proc_505 *)td->td_proc;
    struct ucred *cred = td->td_proc->p_ucred; // doesn't need a check as 5.05 is the same
	
	int(*_printf)(const char *fmt, ...);
	uint64_t(*_strlen)(const char *s);
	char *(*_strcpy)(char *dst, const char *src);
	char *(*_strncmp)(char *dst, const char *src, uint64_t len);
	int(*_sys_stat)(struct thread *td, void *args);
	int(*original_call)(struct thread *td, void *args);

	_printf = (void *)0;
	_strlen = (void *)0;
	_strcpy = (void *)0;
	_strncmp = (void *)0;
	_sys_stat = (void *)0;
	original_call = (void *)0;

	switch (data->cachedFw) {
		case 505:
			_printf = (void *)&ptrKernel[0x436040];
			_strlen = (void *)&ptrKernel[0x3B71A0];
			_strcpy = (void *)&ptrKernel[0x8F250];
			_strncmp = (void *)&ptrKernel[0x1B8FE0];
			_sys_stat = (void *)&ptrKernel[0x33DFE0];
			original_call = (void *)&ptrKernel[0x33B990];
			break;
		case 672:
			_printf = (void *)&ptrKernel[0x123280];
			_strlen = (void *)&ptrKernel[0x2433E0];
			_strcpy = (void *)&ptrKernel[0x2390C0];
			_strncmp = (void *)&ptrKernel[0x39B6E0];
			_sys_stat = (void *)&ptrKernel[0x4A0F30];
			original_call = (void *)&ptrKernel[0x49E970];
			break;
		case 700:
		case 701:
		case 702:
			_printf = (void *)&ptrKernel[0xBC730];
			_strlen = (void *)&ptrKernel[0x93FF0];
			_strcpy = (void *)&ptrKernel[0x2CC70];
			_strncmp = (void *)&ptrKernel[0x3DABE0];
			_sys_stat = (void *)&ptrKernel[0x357F20];
			original_call = (void *)&ptrKernel[0x355940];
			break;
		case 750:
		case 751:
		case 755:
			_printf = (void*)&ptrKernel[0x26f740];
			_strlen = (void*)&ptrKernel[0x2e8bc0];
			_strcpy = (void*)&ptrKernel[0x46b0b0];
			_strncmp = (void*)&ptrKernel[0xbf670];
			_sys_stat = (void*)&ptrKernel[0xf6fe0];
			original_call = (void*)&ptrKernel[0xf49c0];
			break;
		case 800:
		case 801:
		case 803:
			_printf = (void*)&ptrKernel[0x430ae0];
			_strlen = (void*)&ptrKernel[0x2f6090];
			_strcpy = (void*)&ptrKernel[0x1e0870];
			_strncmp = (void*)&ptrKernel[0x1846d0];
			_sys_stat = (void*)&ptrKernel[0x215ee0];
			original_call = (void*)&ptrKernel[0x2138b0];
			break;
		case 850:
		case 852:
			_printf = (void*)&ptrKernel[0x15d570];
			_strlen = (void*)&ptrKernel[0x270c40];
			_strcpy = (void*)&ptrKernel[0x21ad40];
			_strncmp = (void*)&ptrKernel[0x3cf6d0];
			_sys_stat = (void*)&ptrKernel[0x32fb40];
			original_call = (void*)&ptrKernel[0x32d510];
			break;
		case 900:
			_printf = (void *)&ptrKernel[0xB7A30];
			_strlen = (void *)&ptrKernel[0x30F450];
			_strcpy = (void *)&ptrKernel[0x189F80];
			_strncmp = (void *)&ptrKernel[0x124750];
			_sys_stat = (void *)&ptrKernel[0x1DC4F0];
			original_call = (void *)&ptrKernel[0x1D9EC0];
			break;
		case 903:
		case 904:
			_printf = (void*)&ptrKernel[0xb79e0];
			_strlen = (void*)&ptrKernel[0x30f0f0];
			_strcpy = (void*)&ptrKernel[0x189f30];
			_strncmp = (void*)&ptrKernel[0x124700];
			_sys_stat = (void*)&ptrKernel[0x1dc4a0];
			original_call = (void*)&ptrKernel[0x1d9e70];
			break;
		case 950:
		case 951:
		case 960:
			_printf = (void*)&ptrKernel[0x205470];
			_strlen = (void*)&ptrKernel[0x3f1980];
			_strcpy = (void*)&ptrKernel[0x21f500];
			_strncmp = (void*)&ptrKernel[0x1360b0];
			_sys_stat = (void*)&ptrKernel[0x1f4a90];
			original_call = (void*)&ptrKernel[0x1f2460];
			break;
		case 1000:
		case 1001:
			_printf = (void*)&ptrKernel[0xc50f0];
			_strlen = (void*)&ptrKernel[0x2e0340];
			_strcpy = (void*)&ptrKernel[0x466e30];
			_strncmp = (void*)&ptrKernel[0x1219b0];
			_sys_stat = (void*)&ptrKernel[0x210720];
			original_call = (void*)&ptrKernel[0x20e0f0];
			break;
		case 1050:
		case 1070:
		case 1071:
			_printf = (void*)&ptrKernel[0x450e80];
			_strlen = (void*)&ptrKernel[0x160da0];
			_strcpy = (void*)&ptrKernel[0x3f0ba0];
			_strncmp = (void*)&ptrKernel[0x1ddda0];
			_sys_stat = (void*)&ptrKernel[0x3806c0];
			original_call = (void*)&ptrKernel[0x37e090];
			break;
		case 1100:
			_printf = (void *)&ptrKernel[0x2FCBD0];
			_strlen = (void *)&ptrKernel[0x21DC40];
			_strcpy = (void *)&ptrKernel[0x1AA590];
			_strncmp = (void *)&ptrKernel[0x313B10];
			_sys_stat = (void *)&ptrKernel[0xE8960];
			original_call = (void *)&ptrKernel[0xE6330];
			break;
		default:
			break;
	}

	int ret = -1;
	char possible_path[500];
	char statStruct[500];
	const char *real_path = args->path;
	
	//if (cred->cr_uid == 1)
	//if (!_strncmp(cachedFirmware == 505 ? castedProc->titleid : td->td_proc->titleid, data->cusa, 4))
		//_printf(data->print_debug1, cred->cr_uid, cachedFirmware == 505 ? castedProc->titleid : td->td_proc->titleid, args->path, ret);
	
	if (cred->cr_uid == 0 || _strncmp(cachedFirmware == 505 ? castedProc->titleid : td->td_proc->titleid, data->cusa, 4) != 0)
		goto original;

	_strcpy(possible_path, data->data_path);
	_strcpy(possible_path + _strlen(possible_path), cachedFirmware == 505 ? castedProc->titleid : td->td_proc->titleid);
	_strcpy(possible_path + _strlen(possible_path), args->path);
	
	data->statData->path = possible_path;
	data->statData->sb = &statStruct;
	int retVal = _sys_stat(td, data->statData);

	//if ((*(uint32_t *)((uint64_t)data->statData->sb + 0x08) & 0170000) != 0100000 || retVal != 0) // st_mode & 0170000 == 0100000 would be a file //... == 0040000 is a dir;
	if ((*(uint32_t *)((uint64_t)data->statData->sb + 0x08) & S_IFDIR) || retVal != 0)
		goto original;

	args->path = possible_path;
	ret = original_call(td, args);

	//_printf(data->print_debug2, args->path, ret);

	if (ret > 0) {
		original:
		args->path = real_path;
		ret = original_call(td, args);

		//_printf(data->print_debug1, cred->cr_uid, cachedFirmware == 505 ? castedProc->titleid : td->td_proc->titleid, args->path, ret);
	}
	else {
		_printf(data->print_debug2, args->path, ret);
	}

	return ret;
}

int sys_openat_hook(struct thread *td, struct syscall_openat *args) { // this entire hook must NOT be rip dependent
	uint32_t edx, eax;
    __asm__ ("rdmsr" : "=d"(edx), "=a"(eax) : "c"(0xC0000082));
	uint8_t *ptrKernel = (uint8_t *)((((uint64_t)edx) << 32) | (uint64_t)eax) - __Xfast_syscall;

	struct hook_data *data = (struct hook_data *)(*(uint64_t *)ptrKernel);
	struct proc_505 *castedProc = (struct proc_505 *)td->td_proc;
    struct ucred *cred = td->td_proc->p_ucred; // doesn't need a check as 5.05 is the same
	
	int(*_printf)(const char *fmt, ...);
	uint64_t(*_strlen)(const char *s);
	char *(*_strcpy)(char *dst, const char *src);
	char *(*_strncmp)(char *dst, const char *src, uint64_t len);
	int(*_sys_stat)(struct thread *td, void *args);
	int(*original_call)(struct thread *td, void *args);

	_printf = (void *)0;
	_strlen = (void *)0;
	_strcpy = (void *)0;
	_strncmp = (void *)0;
	_sys_stat = (void *)0;
	original_call = (void *)0;

	switch (data->cachedFw) {
		case 505:
			_printf = (void *)&ptrKernel[0x436040];
			_strlen = (void *)&ptrKernel[0x3B71A0];
			_strcpy = (void *)&ptrKernel[0x8F250];
			_strncmp = (void *)&ptrKernel[0x1B8FE0];
			_sys_stat = (void *)&ptrKernel[0x33DFE0];
			original_call = (void *)&ptrKernel[0x33B9D0];
			break;
		case 672:
			_printf = (void *)&ptrKernel[0x123280];
			_strlen = (void *)&ptrKernel[0x2433E0];
			_strcpy = (void *)&ptrKernel[0x2390C0];
			_strncmp = (void *)&ptrKernel[0x39B6E0];
			_sys_stat = (void *)&ptrKernel[0x4A0F30];
			original_call = (void *)&ptrKernel[0x49E9B0];
			break;
		case 702:
			_printf = (void *)&ptrKernel[0xBC730];
			_strlen = (void *)&ptrKernel[0x93FF0];
			_strcpy = (void *)&ptrKernel[0x2CC70];
			_strncmp = (void *)&ptrKernel[0x3DABE0];
			_sys_stat = (void *)&ptrKernel[0x357F20];
			original_call = (void *)&ptrKernel[0x355980];
			break;
		case 900:
			_printf = (void *)&ptrKernel[0xB7A30];
			_strlen = (void *)&ptrKernel[0x30F450];
			_strcpy = (void *)&ptrKernel[0x189F80];
			_strncmp = (void *)&ptrKernel[0x124750];
			_sys_stat = (void *)&ptrKernel[0x1DC4F0];
			original_call = (void *)&ptrKernel[0x1D9F00];
			break;
		case 1100:
			_printf = (void *)&ptrKernel[0x2FCBD0];
			_strlen = (void *)&ptrKernel[0x21DC40];
			_strcpy = (void *)&ptrKernel[0x1AA590];
			_strncmp = (void *)&ptrKernel[0x313B10];
			_sys_stat = (void *)&ptrKernel[0xE8960];
			original_call = (void *)&ptrKernel[0xE6370];
			break;
		default:
			break;
	}

	int ret = -1;
	char possible_path[500];
	char statStruct[500];
	const char *real_path = args->path;
	
	if (cred->cr_uid == 1)
	//if (!_strncmp(cachedFirmware == 505 ? castedProc->titleid : td->td_proc->titleid, data->cusa, 4))
		_printf(data->print_debug1, cred->cr_uid, cachedFirmware == 505 ? castedProc->titleid : td->td_proc->titleid, args->path, 11111111);
	
	if (cred->cr_uid == 0 || _strncmp(cachedFirmware == 505 ? castedProc->titleid : td->td_proc->titleid, data->cusa, 4) != 0)
		goto original;

	_strcpy(possible_path, data->data_path);
	_strcpy(possible_path + _strlen(possible_path), cachedFirmware == 505 ? castedProc->titleid : td->td_proc->titleid);
	_strcpy(possible_path + _strlen(possible_path), args->path);
	
	data->statData_at->path = possible_path;
	data->statData_at->sb = &statStruct;
	int retVal = _sys_stat(td, data->statData_at);

	//if ((*(uint32_t *)((uint64_t)data->statData_at->sb + 0x08) & 0170000) != 0100000 || retVal != 0) // st_mode & 0170000 == 0100000 would be a file //... == 0040000 is a dir;
	if ((*(uint32_t *)((uint64_t)data->statData_at->sb + 0x08) & S_IFDIR) || retVal != 0)
		goto original;

	args->path = possible_path;
	ret = original_call(td, args);

	//_printf(data->print_debug2, args->path, ret);

	if (ret > 0) {
		original:
		args->path = real_path;
		ret = original_call(td, args);

		//_printf(data->print_debug1, cred->cr_uid, cachedFirmware == 505 ? castedProc->titleid : td->td_proc->titleid, args->path, ret);
	} else {
		_printf(data->print_debug2, args->path, ret);
	}

	return ret;
}

void *rwx_alloc(uint64_t size) {
    uint64_t alignedSize = (size + 0x3FFFull) & ~0x3FFFull;
    return (void *)kmem_alloc(*kernel_map, alignedSize);
}

int install_afr_hooks() {
	// sys_open afr hook
	printf("[Frame4] <AFR> loading application file redirector...\n");

	struct hook_data *data = (struct hook_data *)rwx_alloc(sizeof(struct hook_data));
	data->statData = (struct syscall_stat *)rwx_alloc(sizeof(struct syscall_stat));
	data->statData_at = (struct syscall_stat *)rwx_alloc(sizeof(struct syscall_stat));
	data->cachedFw = cachedFirmware;
	strcpy(data->data_path, "/user/data/");
	strcpy(data->cusa, "CUSA");
	strcpy(data->print_debug1, "[Frame4] <AFR> cred->cr_uid: %i, %s, %s (%i)\n");
	strcpy(data->print_debug2, "[Frame4] <AFR> Redirected: %s (%i)\n");


	void *hook_ptr = (void *)rwx_alloc(0x10000);
	memcpy(hook_ptr, sys_open_hook, 0x1000);

	void *hook_ptr_at = (void *)rwx_alloc(0x10000);
	memcpy(hook_ptr_at, sys_openat_hook, 0x1000);

	cpu_disable_wp();
	*(uint64_t *)cachedKernelBase = (uint64_t)data;
	sysents[5].sy_call = hook_ptr; // sys_open
	sysents[499].sy_call = hook_ptr_at; // sys_openat
	cpu_enable_wp();

	return 0;
}
