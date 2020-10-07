#ifndef __SIMD_SSE3_AI_PD64_BM_H__
#define __SIMD_SSE3_AI_PD64_BM_H__

const uint8_t sse3_ai_pd64_cnt = 3;

const char *sse3_ai_pd64_instructions[ sse3_ai_pd64_cnt + 1 ] = {
	"SIMD SSE3 64-bit Double-Precision Arithmetic Instructions with 128-bit vectors ...",
	"addsubpd\t_mm_addsub_pd()  ",
	"haddpd  \t_mm_hadd_pd()    ",
	"hsubpd  \t_mm_hsub_pd()    "
};

inline void sse3_ai_pd64_bm( thread_data_t *td,  pc_data_t *pc, double *pd64 ) {
	int64_t i;
	double *pd64_start __attribute__((aligned(16))) = pd64;
	__m128d wd;
	__m128d bd = _mm_set_pd( 1.11111f, 2.22222f );

	while ( td->thread_active ) {

		pc_get( pc, td->cycles_count );

		if ( !td->thread_active ) break;

		pthread_mutex_lock( &lock );
		evaluating_threads++;
		pthread_mutex_unlock( &lock );

		pd64 = pd64_start;

		switch ( td->instruction ) {

			case 1: // add vectors of 2 64-bit doubles at cycle
				for ( i = 0; i < td->cycles_count; i++, pd64 += td->vector_offset ) {
					wd = _mm_load_pd( (const double *)pd64 );
					wd = _mm_addsub_pd( wd, bd );
					_mm_store_pd( (double *)pd64, wd );
				}
				break;

			case 2: // addsub vectors of 2 64-bit doubles at cycle
				for ( i = 0; i < td->cycles_count; i++, pd64 += td->vector_offset ) {
					wd = _mm_load_pd( (const double *)pd64 );
					wd = _mm_hadd_pd( wd, bd );
					_mm_store_pd( (double *)pd64, wd );
				}
				break;


			case 3: // hsub vectors of 2 64-bit doubles at cycle
				for ( i = 0; i < td->cycles_count; i++, pd64 += td->vector_offset ) {
					wd = _mm_load_pd( (const double *)pd64 );
					wd = _mm_hsub_pd( wd, bd );
					_mm_store_pd( (double *)pd64, wd );
				}
				break;

			default:
				printf( "sse3_ai_pd64_bm_thread%u havn't instruction\n", td->tid );

		}

		pthread_mutex_lock( &lock );
		evaluating_threads--;
		pthread_cond_signal( &stop );
		pthread_mutex_unlock( &lock );

	}

	pthread_mutex_lock( &lock );
	active_threads--;
	pthread_cond_signal( &finish );
	pthread_mutex_unlock( &lock );

	return;
}

void* sse3_ai_pd64_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 2;

	sprintf( td->name, "sse3_aipd64th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	uint64_t alloc_length = ( ST_BM_CYCLES_PER_TIME > MT_BM_CYCLES_PER_TIME ? ST_BM_CYCLES_PER_TIME : MT_BM_CYCLES_PER_TIME ) * td->vector_offset;
	uint64_t alloc_size = alloc_length * sizeof( double );
	double *pd64 __attribute__((aligned(16))) = (double*)aligned_alloc( 16, alloc_size );
	if ( !pd64 ) perror( "aligned_alloc() error" );

	sse3_ai_pd64_bm( td, &pc[ DSP_PC ], pd64 );

	if ( pd64 ) free( pd64 );

	return NULL;
}

void* sse3_ai_pd64_cpu_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 0;

	sprintf( td->name, "sse3caipd64th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	double pd64[ 2 ] __attribute__((aligned(16))) = { 8, 6 };

	sse3_ai_pd64_bm( td, &pc[ CPU_PC ], pd64 );

	return NULL;
}

#endif // !__SIMD_SSE3_AI_PD64_BM_H__