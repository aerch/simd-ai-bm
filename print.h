#ifndef __PRINT_H__
#define __PRINT_H__

#define _ST_BM_START_MSG_ 0
#define _ST_BM_FINAL_MSG_ 1

#define _MT_BM_START_MSG_ 2
#define _MT_BM_FINAL_MSG_ 3

inline void make_message( uint8_t id ) {

	switch ( id ) {

		case _ST_BM_START_MSG_:
			fprintf( stream, "SIMD Arithmetic Instructions Single-Threaded Benchmark start (measure by %i MCycles) ...\n", (int32_t)(cycles_count/1e6) );
			printf( BLUE "SIMD Arithmetic Instructions Single-Threaded Benchmark start (measure by %i MCycles) ..." OFF "\n", (int32_t)(cycles_count/1e6) );
			break;

		case _ST_BM_FINAL_MSG_:
			fprintf( stream, "\nSIMD Arithmetic Instructions Single-Threaded Benchmark finished\t\t\t\t\t\t[ SIMD-AI-ST-BM      %8i ]\n\n", (int32_t)round( total_tps ) );
			printf( BLUE "SIMD Arithmetic Instructions Single-Threaded Benchmark finished\t\t\t\t\t\t[" WHITE " SIMD-AI-ST-BM      %8i " OFF BLUE "]" OFF "\n\n", (int32_t)round( total_tps ) );
			break;

		case _MT_BM_START_MSG_:
			fprintf( stream, "SIMD Arithmetic Instructions Multi-Threaded Benchmark start (measure by %i MCycles) ...\n", (int32_t)(cycles_count/1e6) );
			printf( BLUE "SIMD Arithmetic Instructions Multi-Threaded Benchmark start (measure by %i MCycles) ..." OFF "\n", (int32_t)(cycles_count/1e6) );
			break;

		case _MT_BM_FINAL_MSG_:
			fprintf( stream, "\nSIMD Arithmetic Instructions Multi-Threaded Benchmark finished\t\t\t\t\t\t[ SIMD-AI-MT-BM      %8i ]\n\n", (int32_t)round( total_tps ) );
			printf( BLUE "SIMD Arithmetic Instructions Multi-Threaded Benchmark finished\t\t\t\t\t\t[" WHITE " SIMD-AI-MT-BM      %8i " OFF BLUE "]" OFF "\n\n", (int32_t)round( total_tps ) );
			break;

		default:
			printf( "make_message() error: unknown identificator\n" );

	}

	return;
}

inline void make_title( const char *title ) {

	fprintf( stream, "\n%s:\t   ASM INSTR\tINTRINSIC FUNC CALL\tTOTAL EVALUATE TIME\tPER ONE CYCLE\tPER GIGACYCLE\tSIMD CAPACITY\tOPERATING SPEED\n", title );
	printf( BLUE "\n%s:" OFF WHITE "\t   ASM INSTR\tINTRINSIC FUNC CALL\tTOTAL EVALUATE TIME\tPER ONE CYCLE\tPER GIGACYCLE\tSIMD CAPACITY\tOPERATING SPEED\n\n" OFF, title );

	return;
}

inline void make_simd_title( const char *simd_title ) {

	fprintf( stream, "\n      %s\n", simd_title );
	printf( BLUE "      %s\n" OFF, simd_title );

	return;
}

inline void print_results( const char *str, int8_t vecsz, uint64_t cycles_count, double total_time ) {
	const double gigacycle = 1.0e+9;
	double time_per_cycle = total_time / (double)cycles_count;
	double time_per_gigacycle = time_per_cycle * gigacycle;
	double transactions_per_second = (double)vecsz / time_per_gigacycle;

	total_tps += transactions_per_second;

	fprintf( stream, "\t   %s\t%15.12lf sec\t%9.2e sec\t%9.6lf sec\t  %3d values\t%8.1lf GT/sec\n", str, total_time, time_per_cycle, time_per_gigacycle, vecsz, transactions_per_second );
	printf("\t   %s\t%15.12lf sec\t%9.2e sec\t%9.6lf sec\t  %3d values\t%8.1lf GT/sec\n", str, total_time, time_per_cycle, time_per_gigacycle, vecsz, transactions_per_second );

	return;
}

#endif // !__PRINT_H__