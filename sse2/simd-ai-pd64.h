#ifndef __SIMD_SSE2_AI_PD64_BM_H__
#define __SIMD_SSE2_AI_PD64_BM_H__

const uint8_t sse2_ai_pd64_cnt = 8;

const char *sse2_ai_pd64_instructions[ sse2_ai_pd64_cnt + 1 ] = {
	"SIMD SSE2 64-bit Double-Precision Arithmetic Instructions with 128-bit vectors ...",
	"addpd   \t_mm_add_pd()    ",
	"addsd   \t_mm_add_sd()    ",
	"divpd   \t_mm_div_pd()    ",
	"divsd   \t_mm_div_sd()    ",
	"mulpd   \t_mm_mul_pd()    ",
	"mulsd   \t_mm_mul_sd()    ",
	"subpd   \t_mm_sub_pd()    ",
	"subsd   \t_mm_sub_sd()    "
};

inline void sse2_ai_pd64_bm( thread_data_t *td,  pc_data_t *pc, double *pd64, int32_t vector_offset ) {
	int64_t i;
	double *p __attribute__((aligned(16)));
	__m128d wd;
	__m128d bd = _mm_set_pd( 1.11111f, 2.22222f );

	while ( td->thread_active ) {

		p = pd64;

		pc_get( pc, td->cycles_count );

		if ( !td->thread_active ) break;

		pthread_mutex_lock( &lock );
		evaluating_threads++;
		pthread_mutex_unlock( &lock );

		switch ( td->instruction ) {

			case 1: // add vectors of 2 64-bit doubles at cycle
				vector_capacity = 2;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					wd = _mm_load_pd( (const double *)p );
					wd = _mm_add_pd( wd, bd );
					_mm_store_pd( (double *)p, wd );
				}
				break;

			case 2: // add vectors of 2 64-bit doubles at cycle
				vector_capacity = 2;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					wd = _mm_load_pd( (const double *)p );
					wd = _mm_add_sd( wd, bd );
					_mm_store_pd( (double *)p, wd );
				}
				break;

			case 3: // div vectors of 2 64-bit doubles at cycle
				vector_capacity = 2;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					wd = _mm_load_pd( (const double *)p );
					wd = _mm_div_pd( wd, bd );
					_mm_store_pd( (double *)p, wd );
				}
				break;

			case 4: // div vectors of 2 64-bit doubles at cycle
				vector_capacity = 2;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					wd = _mm_load_pd( (const double *)p );
					wd = _mm_div_sd( wd, bd );
					_mm_store_pd( (double *)p, wd );
				}
				break;

			case 5: // mul vectors of 2 64-bit doubles at cycle
				vector_capacity = 2;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					wd = _mm_load_pd( (const double *)p );
					wd = _mm_mul_pd( wd, bd );
					_mm_store_pd( (double *)p, wd );
				}
				break;

			case 6: // mul vectors of 2 64-bit doubles at cycle
				vector_capacity = 2;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					wd = _mm_load_pd( (const double *)p );
					wd = _mm_mul_sd( wd, bd );
					_mm_store_pd( (double *)p, wd );
				}
				break;

			case 7: // sub vectors of 2 64-bit doubles at cycle
				vector_capacity = 2;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					wd = _mm_load_pd( (const double *)p );
					wd = _mm_sub_pd( wd, bd );
					_mm_store_pd( (double *)p, wd );
				}
				break;

			case 8: // sub vectors of 2 64-bit doubles at cycle
				vector_capacity = 2;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					wd = _mm_load_pd( (const double *)p );
					wd = _mm_sub_sd( wd, bd );
					_mm_store_pd( (double *)p, wd );
				}
				break;

			default:
				printf( "sse2_ai_pd64_bm_thread%u havn't instruction\n", td->tid );

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

void* sse2_ai_pd64_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 2;

	sprintf( td->name, "sse2_aipd64th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	uint64_t alloc_length = ( ST_BM_CYCLES_PER_TIME > MT_BM_CYCLES_PER_TIME ? ST_BM_CYCLES_PER_TIME : MT_BM_CYCLES_PER_TIME ) * td->vector_offset;
	uint64_t alloc_size = alloc_length * sizeof( double );
	double *pd64 __attribute__((aligned(16))) = (double*)aligned_alloc( 16, alloc_size );
	if ( !pd64 ) perror( "aligned_alloc() error" );

	sse2_ai_pd64_bm( td, &pc[ DSP_PC ], pd64, 2 );

	if ( pd64 ) free( pd64 );

	return NULL;
}

void* sse2_ai_pd64_cpu_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 0;

	sprintf( td->name, "sse2caipd64th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	double pd64[ 2 ] __attribute__((aligned(16))) = { 8, 4 };

	sse2_ai_pd64_bm( td, &pc[ CPU_PC ], pd64, 0 );

	return NULL;
}

#endif // !__SIMD_SSE2_AI_PD64_BM_H__