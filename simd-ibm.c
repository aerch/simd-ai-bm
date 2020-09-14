#include <stdio.h>
#include <time.h>
#include <string.h>
#include <inttypes.h>
#include <immintrin.h>
#include <linux/limits.h>

#include "defs.h"
#include "init.h"
#include "print.h"

#include "avx2/simd-ai-epx8.h"
#include "avx2/simd-ai-epx16.h"
#include "avx2/simd-ai-epx32.h"
#include "avx2/simd-ai-epx64.h"

int main( int argc, char const *argv[] ) {

	make_inits();

	avx2_simd_ai_epx8_bm();
	avx2_simd_ai_epx16_bm();
	avx2_simd_ai_epx32_bm();
	avx2_simd_ai_epx64_bm();

	make_finits();

	exit(EXIT_SUCCESS);
}