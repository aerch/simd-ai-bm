#include <stdio.h>
#include <stdint.h>
#include <cpuid.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <inttypes.h>
#include <sys/prctl.h>
#include <sys/sysinfo.h>
#include <linux/limits.h>

#include <mmintrin.h>  //MMX
#include <xmmintrin.h> //SSE
#include <emmintrin.h> //SSE2
#include <pmmintrin.h> //SSE3
#include <tmmintrin.h> //SSSE3
#include <smmintrin.h> //SSSE4.1
#include <nmmintrin.h> //SSSE4.2
#include <immintrin.h> //AVX & AXX2
#include <wmmintrin.h> //AES

#include "init.h"

int main( int argc, char const *argv[] ) {

	make_inits();

	make_st_banchmarks();
	// make_mt_banchmarks();

	make_finits();

	exit(EXIT_SUCCESS);
}
