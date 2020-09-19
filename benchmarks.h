#ifndef __BENCHMARKS_H__
#define __BENCHMARKS_H__

#include "sse3/simd-ai-ps32.h"
#include "sse3/simd-ai-pd64.h"

#include "ssse3/simd-ai-epx8.h"
// #include "ssse3/simd-ai-epx16.h"
// #include "ssse3/simd-ai-epx32.h"

#include "sse4.1/simd-ai-epx8.h"
#include "sse4.1/simd-ai-epx32.h"
#include "sse4.1/simd-ai-ps32.h"
#include "sse4.1/simd-ai-pd64.h"

#include "avx/simd-ai-ps32.h"
#include "avx/simd-ai-pd64.h"

#include "avx2/simd-ai-epx8.h"
#include "avx2/simd-ai-epx16.h"
#include "avx2/simd-ai-epx32.h"
#include "avx2/simd-ai-epx64.h"

inline void make_st_banchmarks() {
	total_tps = 0.0;
	cycles_count = CYCLES_COUNT;

	// single thread benchmarks execution
	make_message( 0 );

	make_title( "MMX" );
	make_title( "SSE" );
	make_title( "SSE2" );

	make_title( "SSE3" );
	sse3_ai_ps32_st_bm();
	sse3_ai_pd64_st_bm();

	make_title( "SSSE3" );
	ssse3_ai_epx8_st_bm();
	// ssse3_ai_epx16_st_bm();
	// ssse3_ai_epx32_st_bm();

	make_title( "SSE4.1" );
	sse4_1_ai_epx8_st_bm();
	sse4_1_ai_epx32_st_bm();
	sse4_1_ai_ps32_st_bm();
	sse4_1_ai_pd64_st_bm();

	make_title( "AVX" );
	avx_ai_ps32_st_bm();
	avx_ai_pd64_st_bm();

	make_title( "AVX2" );
	avx2_ai_epx8_st_bm();
	avx2_ai_epx16_st_bm();
	avx2_ai_epx32_st_bm();
	avx2_ai_epx64_st_bm();

	make_title( "FMA" );

	make_message( 1 );

	return;
}

inline void make_mt_banchmarks() {
	total_tps = 0.0;
	cycles_count = CYCLES_COUNT / 10;

	// multi-threaded benchmarks execution
	make_message( 2 );

	make_title( "MMX" );
	make_title( "SSE" );
	make_title( "SSE2" );

	make_title( "SSE3" );
	sse3_ai_ps32_mt_bm( THREADS_COUNT );
	sse3_ai_pd64_mt_bm( THREADS_COUNT );

	make_title( "SSSE3" );
	ssse3_ai_epx8_mt_bm( THREADS_COUNT );
	// ssse3_ai_epx16_mt_bm( THREADS_COUNT );
	// ssse3_ai_epx32_mt_bm( THREADS_COUNT );

	make_title( "SSE4.1" );
	sse4_1_ai_epx8_mt_bm( THREADS_COUNT );
	sse4_1_ai_epx32_mt_bm( THREADS_COUNT );
	sse4_1_ai_ps32_mt_bm( THREADS_COUNT );
	sse4_1_ai_pd64_mt_bm( THREADS_COUNT );

	make_title( "AVX" );
	avx_ai_ps32_mt_bm( THREADS_COUNT );
	avx_ai_pd64_mt_bm( THREADS_COUNT );

	make_title( "AVX2" );
	avx2_ai_epx8_mt_bm( THREADS_COUNT );
	avx2_ai_epx16_mt_bm( THREADS_COUNT );
	avx2_ai_epx32_mt_bm( THREADS_COUNT );
	avx2_ai_epx64_mt_bm( THREADS_COUNT );

	make_title( "FMA" );

	make_message( 3 );

	return;
}

#endif // !__BENCHMARKS_H__