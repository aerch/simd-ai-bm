#ifndef __BENCHMARKS_H__
#define __BENCHMARKS_H__

#include "avx2/simd-ai-epx8.h"
#include "avx2/simd-ai-epx16.h"
#include "avx2/simd-ai-epx32.h"
#include "avx2/simd-ai-epx64.h"

inline void make_st_banchmarks() {
	total_tps = 0.0;
	cycles_count = CYCLES_COUNT;

	// single thread benchmarks execution
	fprintf( stream, "SIMD Arithmetic Instructions Single-Threaded Benchmark start ...\n\n" );
	printf( BLUE "SIMD Arithmetic Instructions Single-Threaded Benchmark start ..." OFF "\n" );

	fprintf( stream, "AVX2:\t   ASM INSTR\tINTRINSIC FUNC CALL\tTOTAL EVALUATE TIME\tPER ONE CYCLE\tOPERATE SPEED\n" );
	printf( BLUE "AVX2:" OFF WHITE "\t   ASM INSTR\tINTRINSIC FUNC CALL\tTOTAL EVALUATE TIME\tPER ONE CYCLE\tOPERATE SPEED\n" OFF );

	avx2_ai_epx8_st_bm();
	avx2_ai_epx16_st_bm();
	avx2_ai_epx32_st_bm();
	avx2_ai_epx64_st_bm();

	fprintf( stream, "\nSIMD Arithmetic Instructions Single-Threaded Benchmark value\t\t [ SIMD-AI-ST-BM   %8i ]\n\n", (int32_t)round( total_tps ) );
	printf( BLUE "SIMD Arithmetic Instructions Single-Threaded Benchmark value             [ SIMD-AI-ST-BM   %8i ]" OFF "\n\n", (int32_t)round( total_tps ) );

	return;
}

inline void make_mt_banchmarks() {
	total_tps = 0.0;
	cycles_count = CYCLES_COUNT / 20;
	const uint8_t threads = 128;

	// multi-threaded benchmarks execution
	fprintf( stream, "SIMD Arithmetic Instructions Multi-Threaded Benchmark start ...\n\n" );
	printf( BLUE "SIMD Arithmetic Instructions Multi-Threaded Benchmark start ..." OFF "\n" );

	fprintf( stream, "AVX2:\t   ASM INSTR\tINTRINSIC FUNC CALL\tTOTAL EVALUATE TIME\tPER ONE CYCLE\tOPERATE SPEED\n" );
	printf( BLUE "AVX2:" OFF WHITE "\t   ASM INSTR\tINTRINSIC FUNC CALL\tTOTAL EVALUATE TIME\tPER ONE CYCLE\tOPERATE SPEED\n" OFF );

	avx2_ai_epx8_mt_bm( threads );
	avx2_ai_epx16_mt_bm( threads );
	avx2_ai_epx32_mt_bm( threads );
	avx2_ai_epx64_mt_bm( threads );

	fprintf( stream, "\nSIMD Arithmetic Instructions Multi-Threaded Benchmark value\t\t[ SIMD-AI-MT-BM   %8i ]\n\n", (int32_t)round( total_tps ) );
	printf( BLUE "SIMD Arithmetic Instructions Multi-Threaded Benchmark value              [ SIMD-AI-MT-BM   %8i ]" OFF "\n\n", (int32_t)round( total_tps ) );

	return;
}

#endif // !__BENCHMARKS_H__