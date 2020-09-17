#ifndef __PRINT_H__
#define __PRINT_H__

inline void print_results( const char* str, int8_t vecsz, uint64_t cycles_count, double total_time ) {
	double tpc = total_time / (double)cycles_count;
	double tps = (double)vecsz / (tpc * 1.0e9);
	total_tps += tps;
	fprintf( stream, "\t   %s\t%15.12lf sec\t%9.2e sec\t%8.1lf GT/sec\n", str, total_time, tpc, tps );
	printf("\t   %s\t%15.12lf sec\t%9.2e sec\t%8.1lf GT/sec\n", str, total_time, tpc, tps );
	return;
}

#endif // !__PRINT_H__