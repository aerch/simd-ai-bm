#ifndef __BENCHMARKS_H__
#define __BENCHMARKS_H__

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

inline void make_title( const char *title ) {
	fprintf( stream, "\n%s:\t   ASM INSTR\tINTRINSIC FUNC CALL\tTOTAL EVALUATE TIME\tPER ONE CYCLE\tOPERATING SPEED\n", title );
	printf( BLUE "\n%s:" OFF WHITE "\t   ASM INSTR\tINTRINSIC FUNC CALL\tTOTAL EVALUATE TIME\tPER ONE CYCLE\tOPERATING SPEED\n\n" OFF, title );
	return;
}

inline void make_st_banchmarks() {
	total_tps = 0.0;
	cycles_count = CYCLES_COUNT;

	// single thread benchmarks execution
	fprintf( stream, "SIMD Arithmetic Instructions Single-Threaded Benchmark start ...\n" );
	printf( BLUE "SIMD Arithmetic Instructions Single-Threaded Benchmark start ..." OFF "\n" );

	make_title( "MMX" );
	make_title( "SSE" );
	make_title( "SSE2" );
	make_title( "SSE3" );
	make_title( "SSSE3" );

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

	fprintf( stream, "\nSIMD Arithmetic Instructions Single-Threaded Benchmark value\t\t[ SIMD-AI-ST-BM      %8i ]\n\n", (int32_t)round( total_tps ) );
	printf( BLUE "SIMD Arithmetic Instructions Single-Threaded Benchmark value            [ SIMD-AI-ST-BM      %8i ]" OFF "\n\n", (int32_t)round( total_tps ) );

	return;
}

inline void make_mt_banchmarks() {
	total_tps = 0.0;
	cycles_count = CYCLES_COUNT / 10;
	uint8_t threads = 128;

	// multi-threaded benchmarks execution
	fprintf( stream, "SIMD Arithmetic Instructions Multi-Threaded Benchmark start ...\n" );
	printf( BLUE "SIMD Arithmetic Instructions Multi-Threaded Benchmark start ..." OFF "\n" );

	make_title( "MMX" );
	make_title( "SSE" );
	make_title( "SSE2" );
	make_title( "SSE3" );
	make_title( "SSSE3" );

	make_title( "SSE4.1" );
	sse4_1_ai_epx8_mt_bm( threads );
	sse4_1_ai_epx32_mt_bm( threads );
	sse4_1_ai_ps32_mt_bm( threads );
	sse4_1_ai_pd64_mt_bm( threads );

	make_title( "AVX" );
	avx_ai_ps32_mt_bm( threads );
	avx_ai_pd64_mt_bm( threads );

	make_title( "AVX2" );
	avx2_ai_epx8_mt_bm( threads );
	avx2_ai_epx16_mt_bm( threads );
	avx2_ai_epx32_mt_bm( threads );
	avx2_ai_epx64_mt_bm( threads );

	make_title( "FMA" );

	fprintf( stream, "\nSIMD Arithmetic Instructions Multi-Threaded Benchmark value\t\t[ SIMD-AI-MT-BM      %8i ]\n\n", (int32_t)round( total_tps ) );
	printf( BLUE "SIMD Arithmetic Instructions Multi-Threaded Benchmark value             [ SIMD-AI-MT-BM      %8i ]" OFF "\n\n", (int32_t)round( total_tps ) );

	return;
}

#endif // !__BENCHMARKS_H__