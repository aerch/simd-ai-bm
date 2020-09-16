#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <inttypes.h>
#include <immintrin.h>
#include <sys/prctl.h>
#include <linux/limits.h>

#include "defs.h"
#include "vars.h"
#include "init.h"
#include "print.h"

#include "avx2/simd-ai-epx8.h"
#include "avx2/simd-ai-epx16.h"
#include "avx2/simd-ai-epx32.h"
#include "avx2/simd-ai-epx64.h"

int main( int argc, char const *argv[] ) {
	const uint8_t threads = 8;

	make_inits();

	// single thread benchmarks execution
	fprintf( stream, "SIMD Arithmetic Instructions Single-Threaded Benchmark start ...\n\n" );
	printf( BLUE "SIMD Arithmetic Instructions Single-Threaded Benchmark start ..." OFF "\n" );

	// avx2_simd_ai_epx8_bm();
	// avx2_simd_ai_epx16_bm();
	// avx2_simd_ai_epx32_bm();
	avx2_simd_ai_epx64_st_bm();


	fprintf( stream, "\nSIMD Arithmetic Instructions Single-Threaded Benchmark value\t\t [ SIMD-AI-ST-BM   %8i ]\n\n", (int32_t)round( total_tps ) );
	printf( BLUE "SIMD Arithmetic Instructions Single-Threaded Benchmark value             [ SIMD-AI-ST-BM   %8i ]" OFF "\n\n", (int32_t)round( total_tps ) );


	// multi-threaded benchmarks execution
	fprintf( stream, "SIMD Arithmetic Instructions Multi-Threaded Benchmark start ...\n\n" );
	printf( BLUE "SIMD Arithmetic Instructions Multi-Threaded Benchmark start ..." OFF "\n" );

	// avx2_simd_ai_epx8_mt_bm( threads );
	// avx2_simd_ai_epx16_mt_bm( threads );
	// avx2_simd_ai_epx32_mt_bm( threads );
	avx2_simd_ai_epx64_mt_bm( threads );

	fprintf( stream, "\nSIMD Arithmetic Instructions Multi-Threaded Benchmark value\t\t[ SIMD-AI-MT-BM   %8i ]\n\n", (int32_t)round( total_tps ) );
	printf( BLUE "SIMD Arithmetic Instructions Multi-Threaded Benchmark value              [ SIMD-AI-MT-BM   %8i ]" OFF "\n\n", (int32_t)round( total_tps ) );

	make_finits();

	exit(EXIT_SUCCESS);
}
