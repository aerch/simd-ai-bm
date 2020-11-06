#ifndef __BENCHMARKS_H__
#define __BENCHMARKS_H__

#include "bmuthreads.h"

#include "cpuwarmup.h"

#ifdef __MMX__
#include "mmx/simd-ai-epx8.h"
#include "mmx/simd-ai-epx16.h"
#include "mmx/simd-ai-epx32.h"
#endif // __MMX__

#ifdef __SSE__
#include "sse/simd-ai-epx8.h"
#include "sse/simd-ai-epx16.h"
#include "sse/simd-ai-ps32.h"
#endif // __SSE__

#ifdef __SSE2__
#include "sse2/simd-ai-epx8.h"
#include "sse2/simd-ai-epx16.h"
#include "sse2/simd-ai-epx32.h"
#include "sse2/simd-ai-epx64.h"
#include "sse2/simd-ai-pd64.h"
#endif // __SSE2__

#ifdef __SSE3__
#include "sse3/simd-ai-ps32.h"
#include "sse3/simd-ai-pd64.h"
#endif // __SSE3__

#ifdef __SSSE3__
#include "ssse3/simd-ai-epx8.h"
#include "ssse3/simd-ai-epx16.h"
#include "ssse3/simd-ai-epx32.h"
#endif // __SSSE3__

#ifdef __SSE4_1__
#include "sse4.1/simd-ai-epx8.h"
#include "sse4.1/simd-ai-epx32.h"
#include "sse4.1/simd-ai-ps32.h"
#include "sse4.1/simd-ai-pd64.h"
#endif // __SSE4_1__

#ifdef __AVX__
#include "avx/simd-ai-ps32.h"
#include "avx/simd-ai-pd64.h"
#endif // __AVX__

#ifdef __AVX2__
#include "avx2/simd-ai-epx8.h"
#include "avx2/simd-ai-epx16.h"
#include "avx2/simd-ai-epx32.h"
#include "avx2/simd-ai-epx64.h"
#endif // __AVX2__

#ifdef __FMA__
#include "fma3/simd-ai-ps32.h"
#include "fma3/simd-ai-pd64.h"
#endif // __FMA__

// single thread benchmarks execution
inline void make_st_banchmarks() {

	make_message( _ST_BM_START_MSG_ );

#ifdef __MMX__
	if (__builtin_cpu_supports("mmx")) {
		make_title( "MMX" );
		make_cpu_warmup( SINGLE_THREAD, _MMX_ );
		bmu_threads( SINGLE_THREAD, mmx_ai_epx8_cnt,  (char**)mmx_ai_epx8_instructions,  &mmx_ai_epx8_bm_thread,  &mmx_ai_epx8_cpu_bm_thread );
		bmu_threads( SINGLE_THREAD, mmx_ai_epx16_cnt, (char**)mmx_ai_epx16_instructions, &mmx_ai_epx16_bm_thread, &mmx_ai_epx16_cpu_bm_thread );
		bmu_threads( SINGLE_THREAD, mmx_ai_epx32_cnt, (char**)mmx_ai_epx32_instructions, &mmx_ai_epx32_bm_thread, &mmx_ai_epx32_cpu_bm_thread );
	} else make_unsupported_mode_title( "MMX" );
#endif // __MMX__

#ifdef __SSE__
	if (__builtin_cpu_supports("sse")) {
		make_title( "SSE" );
		make_cpu_warmup( SINGLE_THREAD, _SSE_ );
		bmu_threads( SINGLE_THREAD, sse_ai_epx8_cnt,  (char**)sse_ai_epx8_instructions,  &sse_ai_epx8_bm_thread,  &sse_ai_epx8_cpu_bm_thread );
		bmu_threads( SINGLE_THREAD, sse_ai_epx16_cnt, (char**)sse_ai_epx16_instructions, &sse_ai_epx16_bm_thread, &sse_ai_epx16_cpu_bm_thread );
		bmu_threads( SINGLE_THREAD, sse_ai_ps32_cnt,  (char**)sse_ai_ps32_instructions,  &sse_ai_ps32_bm_thread,  &sse_ai_ps32_cpu_bm_thread );
	} else make_unsupported_mode_title( "SSE" );
#endif // __SSE__

#ifdef __SSE2__
	if (__builtin_cpu_supports("sse2")) {
		make_title( "SSE2" );
		make_cpu_warmup( SINGLE_THREAD, _SSE2_ );
		bmu_threads( SINGLE_THREAD, sse2_ai_epx8_cnt,  (char**)sse2_ai_epx8_instructions,  &sse2_ai_epx8_bm_thread,  &sse2_ai_epx8_cpu_bm_thread );
		bmu_threads( SINGLE_THREAD, sse2_ai_epx16_cnt, (char**)sse2_ai_epx16_instructions, &sse2_ai_epx16_bm_thread, &sse2_ai_epx16_cpu_bm_thread );
		bmu_threads( SINGLE_THREAD, sse2_ai_epx32_cnt, (char**)sse2_ai_epx32_instructions, &sse2_ai_epx32_bm_thread, &sse2_ai_epx32_cpu_bm_thread );
		bmu_threads( SINGLE_THREAD, sse2_ai_epx64_cnt, (char**)sse2_ai_epx64_instructions, &sse2_ai_epx64_bm_thread, &sse2_ai_epx64_cpu_bm_thread );
		bmu_threads( SINGLE_THREAD, sse2_ai_pd64_cnt,  (char**)sse2_ai_pd64_instructions,  &sse2_ai_pd64_bm_thread,  &sse2_ai_pd64_cpu_bm_thread );
	} else make_unsupported_mode_title( "SSE2" );
#endif // __SSE2__

#ifdef __SSE3__
	if (__builtin_cpu_supports("sse3")) {
		make_title( "SSE3" );
		make_cpu_warmup( SINGLE_THREAD, _SSE3_ );
		bmu_threads( SINGLE_THREAD, sse3_ai_ps32_cnt, (char**)sse3_ai_ps32_instructions, &sse3_ai_ps32_bm_thread, &sse3_ai_ps32_cpu_bm_thread );
		bmu_threads( SINGLE_THREAD, sse3_ai_pd64_cnt, (char**)sse3_ai_pd64_instructions, &sse3_ai_pd64_bm_thread, &sse3_ai_pd64_cpu_bm_thread );
	} else make_unsupported_mode_title( "SSE3" );
#endif // __SSE3__

#ifdef __SSSE3__
	if (__builtin_cpu_supports("ssse3")) {
		make_title( "SSSE3" );
		make_cpu_warmup( SINGLE_THREAD, _SSSE3_ );
		bmu_threads( SINGLE_THREAD, ssse3_ai_epx8_cnt,  (char**)ssse3_ai_epx8_instructions,  &ssse3_ai_epx8_bm_thread,  &ssse3_ai_epx8_cpu_bm_thread );
		bmu_threads( SINGLE_THREAD, ssse3_ai_epx16_cnt, (char**)ssse3_ai_epx16_instructions, &ssse3_ai_epx16_bm_thread, &ssse3_ai_epx16_cpu_bm_thread );
		bmu_threads( SINGLE_THREAD, ssse3_ai_epx32_cnt, (char**)ssse3_ai_epx32_instructions, &ssse3_ai_epx32_bm_thread, &ssse3_ai_epx32_cpu_bm_thread );
	} else make_unsupported_mode_title( "SSSE3" );
#endif // __SSSE3__

#ifdef __SSE4_1__
	if (__builtin_cpu_supports("sse4.1")) {
		make_title( "SSE4.1" );
		make_cpu_warmup( SINGLE_THREAD, _SSE4_1_ );
		bmu_threads( SINGLE_THREAD, sse4_1_ai_epx8_cnt,  (char**)sse4_1_ai_epx8_instructions,  &sse4_1_ai_epx8_bm_thread,  &sse4_1_ai_epx8_cpu_bm_thread );
		bmu_threads( SINGLE_THREAD, sse4_1_ai_epx32_cnt, (char**)sse4_1_ai_epx32_instructions, &sse4_1_ai_epx32_bm_thread, &sse4_1_ai_epx32_cpu_bm_thread );
		bmu_threads( SINGLE_THREAD, sse4_1_ai_ps32_cnt,  (char**)sse4_1_ai_ps32_instructions,  &sse4_1_ai_ps32_bm_thread,  &sse4_1_ai_ps32_cpu_bm_thread );
		bmu_threads( SINGLE_THREAD, sse4_1_ai_pd64_cnt,  (char**)sse4_1_ai_pd64_instructions,  &sse4_1_ai_pd64_bm_thread,  &sse4_1_ai_pd64_cpu_bm_thread );
	} else make_unsupported_mode_title( "SSE4.1" );
#endif // __SSE4_1__

#ifdef __AVX__
	if (__builtin_cpu_supports("avx")) {
		make_title( "AVX" );
		make_cpu_warmup( SINGLE_THREAD, _AVX_ );
		bmu_threads( SINGLE_THREAD, avx_ai_ps32_cnt, (char**)avx_ai_ps32_instructions, &avx_ai_ps32_bm_thread, &avx_ai_ps32_cpu_bm_thread );
		bmu_threads( SINGLE_THREAD, avx_ai_pd64_cnt, (char**)avx_ai_pd64_instructions, &avx_ai_pd64_bm_thread, &avx_ai_pd64_cpu_bm_thread );
	} else make_unsupported_mode_title( "AVX" );
#endif // __AVX__

#ifdef __AVX2__
	if (__builtin_cpu_supports("avx2")) {
		make_title( "AVX2" );
		make_cpu_warmup( SINGLE_THREAD, _AVX2_ );
		bmu_threads( SINGLE_THREAD, avx2_ai_epx8_cnt,  (char**)avx2_ai_epx8_instructions,  &avx2_ai_epx8_bm_thread,  &avx2_ai_epx8_cpu_bm_thread  );
		bmu_threads( SINGLE_THREAD, avx2_ai_epx16_cnt, (char**)avx2_ai_epx16_instructions, &avx2_ai_epx16_bm_thread, &avx2_ai_epx16_cpu_bm_thread );
		bmu_threads( SINGLE_THREAD, avx2_ai_epx32_cnt, (char**)avx2_ai_epx32_instructions, &avx2_ai_epx32_bm_thread, &avx2_ai_epx32_cpu_bm_thread );
		bmu_threads( SINGLE_THREAD, avx2_ai_epx64_cnt, (char**)avx2_ai_epx64_instructions, &avx2_ai_epx64_bm_thread, &avx2_ai_epx64_cpu_bm_thread );
	} else make_unsupported_mode_title( "AVX2" );
#endif // __AVX2__

#ifdef __FMA__
	if (__builtin_cpu_supports("fma")) {
		make_title( "FMA3" );
		make_cpu_warmup( SINGLE_THREAD, _FMA3_ );
		bmu_threads( SINGLE_THREAD, fma3_ai_ps32_cnt, (char**)fma3_ai_ps32_instructions, &fma3_ai_ps32_bm_thread, &fma3_ai_ps32_cpu_bm_thread );
		bmu_threads( SINGLE_THREAD, fma3_ai_pd64_cnt, (char**)fma3_ai_pd64_instructions, &fma3_ai_pd64_bm_thread, &fma3_ai_pd64_cpu_bm_thread );
	} else make_unsupported_mode_title( "FMA3" );
#endif // __FMA__

	make_message( _ST_BM_FINAL_MSG_ );

	return;
}

// multi-threaded benchmarks execution
inline void make_mt_banchmarks() {

	make_message( _MT_BM_START_MSG_ );

	if (__builtin_cpu_supports("mmx")) {
		make_title( "MMX" );
		make_cpu_warmup( MULTIPLE_THREADS, _MMX_ );
		bmu_threads( MULTIPLE_THREADS, mmx_ai_epx8_cnt,  (char**)mmx_ai_epx8_instructions,  &mmx_ai_epx8_bm_thread,  &mmx_ai_epx8_cpu_bm_thread );
		bmu_threads( MULTIPLE_THREADS, mmx_ai_epx16_cnt, (char**)mmx_ai_epx16_instructions, &mmx_ai_epx16_bm_thread, &mmx_ai_epx16_cpu_bm_thread );
		bmu_threads( MULTIPLE_THREADS, mmx_ai_epx32_cnt, (char**)mmx_ai_epx32_instructions, &mmx_ai_epx32_bm_thread, &mmx_ai_epx32_cpu_bm_thread );
	} else make_unsupported_mode_title( "MMX" );

	if (__builtin_cpu_supports("sse")) {
		make_title( "SSE" );
		make_cpu_warmup( MULTIPLE_THREADS, _SSE_ );
		bmu_threads( MULTIPLE_THREADS, sse_ai_epx8_cnt,  (char**)sse_ai_epx8_instructions,  &sse_ai_epx8_bm_thread,  &sse_ai_epx8_cpu_bm_thread );
		bmu_threads( MULTIPLE_THREADS, sse_ai_epx16_cnt, (char**)sse_ai_epx16_instructions, &sse_ai_epx16_bm_thread, &sse_ai_epx16_cpu_bm_thread );
		bmu_threads( MULTIPLE_THREADS, sse_ai_ps32_cnt,  (char**)sse_ai_ps32_instructions,  &sse_ai_ps32_bm_thread,  &sse_ai_ps32_cpu_bm_thread );
	} else make_unsupported_mode_title( "SSE" );

	if (__builtin_cpu_supports("sse2")) {
		make_title( "SSE2" );
		make_cpu_warmup( MULTIPLE_THREADS, _SSE2_ );
		bmu_threads( MULTIPLE_THREADS, sse2_ai_epx8_cnt,  (char**)sse2_ai_epx8_instructions,  &sse2_ai_epx8_bm_thread,  &sse2_ai_epx8_cpu_bm_thread );
		bmu_threads( MULTIPLE_THREADS, sse2_ai_epx16_cnt, (char**)sse2_ai_epx16_instructions, &sse2_ai_epx16_bm_thread, &sse2_ai_epx16_cpu_bm_thread );
		bmu_threads( MULTIPLE_THREADS, sse2_ai_epx32_cnt, (char**)sse2_ai_epx32_instructions, &sse2_ai_epx32_bm_thread, &sse2_ai_epx32_cpu_bm_thread );
		bmu_threads( MULTIPLE_THREADS, sse2_ai_epx64_cnt, (char**)sse2_ai_epx64_instructions, &sse2_ai_epx64_bm_thread, &sse2_ai_epx64_cpu_bm_thread );
		bmu_threads( MULTIPLE_THREADS, sse2_ai_pd64_cnt,  (char**)sse2_ai_pd64_instructions,  &sse2_ai_pd64_bm_thread,  &sse2_ai_pd64_cpu_bm_thread );
	} else make_unsupported_mode_title( "SSE2" );

	if (__builtin_cpu_supports("sse3")) {
		make_title( "SSE3" );
		make_cpu_warmup( MULTIPLE_THREADS, _SSE3_ );
		bmu_threads( MULTIPLE_THREADS, sse3_ai_ps32_cnt, (char**)sse3_ai_ps32_instructions, &sse3_ai_ps32_bm_thread, &sse3_ai_ps32_cpu_bm_thread );
		bmu_threads( MULTIPLE_THREADS, sse3_ai_pd64_cnt, (char**)sse3_ai_pd64_instructions, &sse3_ai_pd64_bm_thread, &sse3_ai_pd64_cpu_bm_thread );
	} else make_unsupported_mode_title( "SSE3" );

	if (__builtin_cpu_supports("ssse3")) {
		make_title( "SSSE3" );
		make_cpu_warmup( MULTIPLE_THREADS, _SSSE3_ );
		bmu_threads( MULTIPLE_THREADS, ssse3_ai_epx8_cnt,  (char**)ssse3_ai_epx8_instructions,  &ssse3_ai_epx8_bm_thread,  &ssse3_ai_epx8_cpu_bm_thread );
		bmu_threads( MULTIPLE_THREADS, ssse3_ai_epx16_cnt, (char**)ssse3_ai_epx16_instructions, &ssse3_ai_epx16_bm_thread, &ssse3_ai_epx16_cpu_bm_thread );
		bmu_threads( MULTIPLE_THREADS, ssse3_ai_epx32_cnt, (char**)ssse3_ai_epx32_instructions, &ssse3_ai_epx32_bm_thread, &ssse3_ai_epx32_cpu_bm_thread );
	} else make_unsupported_mode_title( "SSSE3" );

	if (__builtin_cpu_supports("sse4.1")) {
		make_title( "SSE4.1" );
		make_cpu_warmup( MULTIPLE_THREADS, _SSE4_1_ );
		bmu_threads( MULTIPLE_THREADS, sse4_1_ai_epx8_cnt,  (char**)sse4_1_ai_epx8_instructions,  &sse4_1_ai_epx8_bm_thread,  &sse4_1_ai_epx8_cpu_bm_thread );
		bmu_threads( MULTIPLE_THREADS, sse4_1_ai_epx32_cnt, (char**)sse4_1_ai_epx32_instructions, &sse4_1_ai_epx32_bm_thread, &sse4_1_ai_epx32_cpu_bm_thread );
		bmu_threads( MULTIPLE_THREADS, sse4_1_ai_ps32_cnt,  (char**)sse4_1_ai_ps32_instructions,  &sse4_1_ai_ps32_bm_thread,  &sse4_1_ai_ps32_cpu_bm_thread );
		bmu_threads( MULTIPLE_THREADS, sse4_1_ai_pd64_cnt,  (char**)sse4_1_ai_pd64_instructions,  &sse4_1_ai_pd64_bm_thread,  &sse4_1_ai_pd64_cpu_bm_thread );
	} else make_unsupported_mode_title( "SSE4.1" );

#ifdef __AVX__
	if (__builtin_cpu_supports("avx")) {
		make_title( "AVX" );
		make_cpu_warmup( MULTIPLE_THREADS, _AVX_ );
		bmu_threads( MULTIPLE_THREADS, avx_ai_ps32_cnt, (char**)avx_ai_ps32_instructions, &avx_ai_ps32_bm_thread, &avx_ai_ps32_cpu_bm_thread );
		bmu_threads( MULTIPLE_THREADS, avx_ai_pd64_cnt, (char**)avx_ai_pd64_instructions, &avx_ai_pd64_bm_thread, &avx_ai_pd64_cpu_bm_thread );
	} else make_unsupported_mode_title( "AVX" );
#endif // __AVX__

#ifdef __AVX2__
	if (__builtin_cpu_supports("avx2")) {
		make_title( "AVX2" );
		make_cpu_warmup( MULTIPLE_THREADS, _AVX2_ );
		bmu_threads( MULTIPLE_THREADS, avx2_ai_epx8_cnt,  (char**)avx2_ai_epx8_instructions,  &avx2_ai_epx8_bm_thread,  &avx2_ai_epx8_cpu_bm_thread  );
		bmu_threads( MULTIPLE_THREADS, avx2_ai_epx16_cnt, (char**)avx2_ai_epx16_instructions, &avx2_ai_epx16_bm_thread, &avx2_ai_epx16_cpu_bm_thread );
		bmu_threads( MULTIPLE_THREADS, avx2_ai_epx32_cnt, (char**)avx2_ai_epx32_instructions, &avx2_ai_epx32_bm_thread, &avx2_ai_epx32_cpu_bm_thread );
		bmu_threads( MULTIPLE_THREADS, avx2_ai_epx64_cnt, (char**)avx2_ai_epx64_instructions, &avx2_ai_epx64_bm_thread, &avx2_ai_epx64_cpu_bm_thread );
	} else make_unsupported_mode_title( "AVX2" );
#endif // __AVX2__

#ifdef __FMA__
	if (__builtin_cpu_supports("fma")) {
		make_title( "FMA3" );
		make_cpu_warmup( MULTIPLE_THREADS, _FMA3_ );
		bmu_threads( MULTIPLE_THREADS, fma3_ai_ps32_cnt, (char**)fma3_ai_ps32_instructions, &fma3_ai_ps32_bm_thread, &fma3_ai_ps32_cpu_bm_thread );
		bmu_threads( MULTIPLE_THREADS, fma3_ai_pd64_cnt, (char**)fma3_ai_pd64_instructions, &fma3_ai_pd64_bm_thread, &fma3_ai_pd64_cpu_bm_thread );
	} else make_unsupported_mode_title( "FMA3" );
#endif // __FMA__

	make_message( _MT_BM_FINAL_MSG_ );

	return;
}

#endif // !__BENCHMARKS_H__