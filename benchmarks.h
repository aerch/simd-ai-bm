#ifndef __BENCHMARKS_H__
#define __BENCHMARKS_H__

#include "bmuthreads.h"

#include "cpuwarmup.h"

// #include "mmx/simd-ai-epx8.h"
// #include "mmx/simd-ai-epx16.h"
// #include "mmx/simd-ai-epx32.h"

// #include "sse/simd-ai-epx8.h"
// #include "sse/simd-ai-epx16.h"
// #include "sse/simd-ai-ps32.h"

// #include "sse2/simd-ai-epx8.h"
// #include "sse2/simd-ai-epx16.h"
// #include "sse2/simd-ai-epx32.h"
// #include "sse2/simd-ai-epx64.h"
// #include "sse2/simd-ai-pd64.h"

// #include "sse3/simd-ai-ps32.h"
// #include "sse3/simd-ai-pd64.h"

// #include "ssse3/simd-ai-epx8.h"
// #include "ssse3/simd-ai-epx16.h"
// #include "ssse3/simd-ai-epx32.h"

// #include "sse4.1/simd-ai-epx8.h"
// #include "sse4.1/simd-ai-epx32.h"
// #include "sse4.1/simd-ai-ps32.h"
// #include "sse4.1/simd-ai-pd64.h"

// #include "avx/simd-ai-ps32.h"
// #include "avx/simd-ai-pd64.h"

#include "avx2/simd-ai-epx8.h"
#include "avx2/simd-ai-epx16.h"
// #include "avx2/simd-ai-epx32.h"
// #include "avx2/simd-ai-epx64.h"

// #include "fma/simd-ai-ps32.h"
// #include "fma/simd-ai-pd64.h"

// single thread benchmarks execution
inline void make_st_banchmarks() {

	make_cpu_warmup();

	make_message( _ST_BM_START_MSG_ );

	// make_title( "MMX" );
	// bmu_threads( SINGLE_THREAD, mmx_ai_epx8_cnt, (char**)mmx_ai_epx8_instructions, &mmx_ai_epx8_bm_thread );
	// bmu_threads( SINGLE_THREAD, mmx_ai_epx16_cnt, (char**)mmx_ai_epx16_instructions, &mmx_ai_epx16_bm_thread );
	// bmu_threads( SINGLE_THREAD, mmx_ai_epx32_cnt, (char**)mmx_ai_epx32_instructions, &mmx_ai_epx32_bm_thread );

	// make_title( "SSE" );
	// bmu_threads( SINGLE_THREAD, sse_ai_epx8_cnt, (char**)sse_ai_epx8_instructions, &sse_ai_epx8_bm_thread );
	// bmu_threads( SINGLE_THREAD, sse_ai_epx16_cnt, (char**)sse_ai_epx16_instructions, &sse_ai_epx16_bm_thread );
	// bmu_threads( SINGLE_THREAD, sse_ai_ps32_cnt, (char**)sse_ai_ps32_instructions, &sse_ai_ps32_bm_thread );

	// make_title( "SSE2" );
	// bmu_threads( SINGLE_THREAD, sse2_ai_epx8_cnt, (char**)sse2_ai_epx8_instructions, &sse2_ai_epx8_bm_thread );
	// bmu_threads( SINGLE_THREAD, sse2_ai_epx16_cnt, (char**)sse2_ai_epx16_instructions, &sse2_ai_epx16_bm_thread );
	// bmu_threads( SINGLE_THREAD, sse2_ai_epx32_cnt, (char**)sse2_ai_epx32_instructions, &sse2_ai_epx32_bm_thread );
	// bmu_threads( SINGLE_THREAD, sse2_ai_epx64_cnt, (char**)sse2_ai_epx64_instructions, &sse2_ai_epx64_bm_thread );
	// bmu_threads( SINGLE_THREAD, sse2_ai_pd64_cnt, (char**)sse2_ai_pd64_instructions, &sse2_ai_pd64_bm_thread );

	// make_title( "SSE3" );
	// bmu_threads( SINGLE_THREAD, sse3_ai_ps32_cnt, (char**)sse3_ai_ps32_instructions, &sse3_ai_ps32_bm_thread );
	// bmu_threads( SINGLE_THREAD, sse3_ai_pd64_cnt, (char**)sse3_ai_pd64_instructions, &sse3_ai_pd64_bm_thread );

	// make_title( "SSSE3" );
	// bmu_threads( SINGLE_THREAD, ssse3_ai_epx8_cnt, (char**)ssse3_ai_epx8_instructions, &ssse3_ai_epx8_bm_thread );
	// bmu_threads( SINGLE_THREAD, ssse3_ai_epx16_cnt, (char**)ssse3_ai_epx16_instructions, &ssse3_ai_epx16_bm_thread );
	// bmu_threads( SINGLE_THREAD, ssse3_ai_epx32_cnt, (char**)ssse3_ai_epx32_instructions, &ssse3_ai_epx32_bm_thread );

	// make_title( "SSE4.1" );
	// bmu_threads( SINGLE_THREAD, sse4_1_ai_epx8_cnt, (char**)sse4_1_ai_epx8_instructions, &sse4_1_ai_epx8_bm_thread );
	// bmu_threads( SINGLE_THREAD, sse4_1_ai_epx32_cnt, (char**)sse4_1_ai_epx32_instructions, &sse4_1_ai_epx32_bm_thread );
	// bmu_threads( SINGLE_THREAD, sse4_1_ai_ps32_cnt, (char**)sse4_1_ai_ps32_instructions, &sse4_1_ai_ps32_bm_thread );
	// bmu_threads( SINGLE_THREAD, sse4_1_ai_pd64_cnt, (char**)sse4_1_ai_pd64_instructions, &sse4_1_ai_pd64_bm_thread );

	// make_title( "AVX" );
	// bmu_threads( SINGLE_THREAD, avx_ai_ps32_cnt, (char**)avx_ai_ps32_instructions, &avx_ai_ps32_bm_thread );
	// bmu_threads( SINGLE_THREAD, avx_ai_pd64_cnt, (char**)avx_ai_pd64_instructions, &avx_ai_pd64_bm_thread );

	make_title( "AVX2" );
	bmu_threads( SINGLE_THREAD, avx2_ai_epx8_cnt, (char**)avx2_ai_epx8_instructions, &avx2_ai_epx8_bm_thread, &avx2_ai_epx8_cpu_bm_thread );
	bmu_threads( SINGLE_THREAD, avx2_ai_epx16_cnt, (char**)avx2_ai_epx16_instructions, &avx2_ai_epx16_bm_thread, &avx2_ai_epx16_cpu_bm_thread );
	// bmu_threads( SINGLE_THREAD, avx2_ai_epx32_cnt, (char**)avx2_ai_epx32_instructions, &avx2_ai_epx32_bm_thread );
	// bmu_threads( SINGLE_THREAD, avx2_ai_epx64_cnt, (char**)avx2_ai_epx64_instructions, &avx2_ai_epx64_bm_thread );

	// make_title( "FMA" );
	// bmu_threads( SINGLE_THREAD, fma_ai_ps32_cnt, (char**)fma_ai_ps32_instructions, &fma_ai_ps32_bm_thread );
	// bmu_threads( SINGLE_THREAD, fma_ai_pd64_cnt, (char**)fma_ai_pd64_instructions, &fma_ai_pd64_bm_thread );

	make_message( _ST_BM_FINAL_MSG_ );

	return;
}

// multi-threaded benchmarks execution
inline void make_mt_banchmarks() {

	make_cpu_warmup();

	make_message( _MT_BM_START_MSG_ );

	// make_title( "MMX" );
	// bmu_threads( MULTIPLE_THREADS, mmx_ai_epx8_cnt, (char**)mmx_ai_epx8_instructions, &mmx_ai_epx8_bm_thread );
	// bmu_threads( MULTIPLE_THREADS, mmx_ai_epx16_cnt, (char**)mmx_ai_epx16_instructions, &mmx_ai_epx16_bm_thread );
	// bmu_threads( MULTIPLE_THREADS, mmx_ai_epx32_cnt, (char**)mmx_ai_epx32_instructions, &mmx_ai_epx32_bm_thread );

	// make_title( "SSE" );
	// bmu_threads( MULTIPLE_THREADS, sse_ai_epx8_cnt, (char**)sse_ai_epx8_instructions, &sse_ai_epx8_bm_thread );
	// bmu_threads( MULTIPLE_THREADS, sse_ai_epx16_cnt, (char**)sse_ai_epx16_instructions, &sse_ai_epx16_bm_thread );
	// bmu_threads( MULTIPLE_THREADS, sse_ai_ps32_cnt, (char**)sse_ai_ps32_instructions, &sse_ai_ps32_bm_thread );

	// make_title( "SSE2" );
	// bmu_threads( MULTIPLE_THREADS, sse2_ai_epx8_cnt, (char**)sse2_ai_epx8_instructions, &sse2_ai_epx8_bm_thread );
	// bmu_threads( MULTIPLE_THREADS, sse2_ai_epx16_cnt, (char**)sse2_ai_epx16_instructions, &sse2_ai_epx16_bm_thread );
	// bmu_threads( MULTIPLE_THREADS, sse2_ai_epx32_cnt, (char**)sse2_ai_epx32_instructions, &sse2_ai_epx32_bm_thread );
	// bmu_threads( MULTIPLE_THREADS, sse2_ai_epx64_cnt, (char**)sse2_ai_epx64_instructions, &sse2_ai_epx64_bm_thread );
	// bmu_threads( MULTIPLE_THREADS, sse2_ai_pd64_cnt, (char**)sse2_ai_pd64_instructions, &sse2_ai_pd64_bm_thread );

	// make_title( "SSE3" );
	// bmu_threads( MULTIPLE_THREADS, sse3_ai_ps32_cnt, (char**)sse3_ai_ps32_instructions, &sse3_ai_ps32_bm_thread );
	// bmu_threads( MULTIPLE_THREADS, sse3_ai_pd64_cnt, (char**)sse3_ai_pd64_instructions, &sse3_ai_pd64_bm_thread );

	// make_title( "SSSE3" );
	// bmu_threads( MULTIPLE_THREADS, ssse3_ai_epx8_cnt, (char**)ssse3_ai_epx8_instructions, &ssse3_ai_epx8_bm_thread );
	// bmu_threads( MULTIPLE_THREADS, ssse3_ai_epx16_cnt, (char**)ssse3_ai_epx16_instructions, &ssse3_ai_epx16_bm_thread );
	// bmu_threads( MULTIPLE_THREADS, ssse3_ai_epx32_cnt, (char**)ssse3_ai_epx32_instructions, &ssse3_ai_epx32_bm_thread );

	// make_title( "SSE4.1" );
	// bmu_threads( MULTIPLE_THREADS, sse4_1_ai_epx8_cnt, (char**)sse4_1_ai_epx8_instructions, &sse4_1_ai_epx8_bm_thread );
	// bmu_threads( MULTIPLE_THREADS, sse4_1_ai_epx32_cnt, (char**)sse4_1_ai_epx32_instructions, &sse4_1_ai_epx32_bm_thread );
	// bmu_threads( MULTIPLE_THREADS, sse4_1_ai_ps32_cnt, (char**)sse4_1_ai_ps32_instructions, &sse4_1_ai_ps32_bm_thread );
	// bmu_threads( MULTIPLE_THREADS, sse4_1_ai_pd64_cnt, (char**)sse4_1_ai_pd64_instructions, &sse4_1_ai_pd64_bm_thread );

	// make_title( "AVX" );
	// bmu_threads( MULTIPLE_THREADS, avx_ai_ps32_cnt, (char**)avx_ai_ps32_instructions, &avx_ai_ps32_bm_thread );
	// bmu_threads( MULTIPLE_THREADS, avx_ai_pd64_cnt, (char**)avx_ai_pd64_instructions, &avx_ai_pd64_bm_thread );

	make_title( "AVX2" );
	bmu_threads( MULTIPLE_THREADS, avx2_ai_epx8_cnt, (char**)avx2_ai_epx8_instructions, &avx2_ai_epx8_bm_thread, &avx2_ai_epx8_cpu_bm_thread );
	bmu_threads( MULTIPLE_THREADS, avx2_ai_epx16_cnt, (char**)avx2_ai_epx16_instructions, &avx2_ai_epx16_bm_thread, &avx2_ai_epx16_cpu_bm_thread );
	// bmu_threads( MULTIPLE_THREADS, avx2_ai_epx32_cnt, (char**)avx2_ai_epx32_instructions, &avx2_ai_epx32_bm_thread );
	// bmu_threads( MULTIPLE_THREADS, avx2_ai_epx64_cnt, (char**)avx2_ai_epx64_instructions, &avx2_ai_epx64_bm_thread );

	// make_title( "FMA" );
	// bmu_threads( MULTIPLE_THREADS, fma_ai_ps32_cnt, (char**)fma_ai_ps32_instructions, &fma_ai_ps32_bm_thread );
	// bmu_threads( MULTIPLE_THREADS, fma_ai_pd64_cnt, (char**)fma_ai_pd64_instructions, &fma_ai_pd64_bm_thread );

	make_message( _MT_BM_FINAL_MSG_ );

	return;
}

#endif // !__BENCHMARKS_H__