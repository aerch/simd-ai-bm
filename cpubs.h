#ifndef __CPU_ID_H__
#define __CPU_ID_H__

void get_cpu_brand_string( char *brand_string ) {
	uint32_t *bs = (uint32_t*)brand_string;

	if ( !__get_cpuid_max( 0x80000004, NULL ) ) {
		perror("__get_cpuid_max(): feature not implemented");
		exit(EXIT_FAILURE);
	}

	__get_cpuid(0x80000002, bs+0x0, bs+0x1, bs+0x2, bs+0x3);
	__get_cpuid(0x80000003, bs+0x4, bs+0x5, bs+0x6, bs+0x7);
	__get_cpuid(0x80000004, bs+0x8, bs+0x9, bs+0xa, bs+0xb);
	brand_string[48] = 0;

	return;
}

#endif // !__CPU_ID_H__