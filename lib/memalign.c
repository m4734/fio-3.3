#include <stdlib.h>
#include <assert.h>
#include <inttypes.h>

#include "memalign.h"
#include <malloc.h>

#define PTR_ALIGN(ptr, mask)   \
	(char *)((uintptr_t)((ptr) + (mask)) & ~(mask))

struct align_footer {
	unsigned int offset;
};

void *fio_memalign(size_t alignment, size_t size)
{
	struct align_footer *f;
	void *ptr, *ret = NULL;

//	int s2;
//	alignment = 4096;
//	s2 = (size + alignment + sizeof(*f) -1+4096)%4096;
//	s2 = size%4096;	

	assert(!(alignment & (alignment - 1)));

	ptr = malloc(size + alignment + sizeof(*f) - 1);
//	ptr = memalign(4096,(size + alignment + sizeof(*f) -1+4096)-s2); //cgmin align
//	ptr = memalign(4096,(size+4096)-s2); //cgmin align
//	posix_memalign(&ptr,4096,size);	
	/*
	if (ptr)
	{
		ret = ptr;
		f = ret+size;
		f->offset = 0;
	}
	*/

	if (ptr) {
		ret = PTR_ALIGN(ptr, alignment - 1);
		f = ret + size;
		f->offset = (uintptr_t) ret - (uintptr_t) ptr;
	}

	return ret;
	printf("%s: ptr addr=%p\n", __func__, ptr);
	return ptr;
}

void fio_memfree(void *ptr, size_t size)
{
	printf("%s: ptr addr=%p\n", __func__, ptr);
//	free(ptr);
#if 1 
	struct align_footer *f = ptr + size;

	free(ptr - f->offset);
#endif
}
