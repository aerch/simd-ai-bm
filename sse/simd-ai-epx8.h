#ifndef __SIMD_SSE_AI_EPX8_BM_H__
#define __SIMD_SSE_AI_EPX8_BM_H__

const uint8_t sse_ai_epx8_cnt = 2;

const char *sse_ai_epx8_instructions[ sse_ai_epx8_cnt + 1 ] = {
	"SIMD SSE 8-bit Integer Arithmetic Instructions with 64-bit vectors ...",
	"psadbw\t_m_psadbw()        ",
	"psadbw\t_mm_sad_pu8()      "
};

inline void sse_ai_epx8_bm( thread_data_t *td,  pc_data_t *pc, int8_t *si8 ) {
	int64_t i;
	int8_t *si8_start __attribute__((aligned(16))) = si8;
	__m64 xi;
	__m64 ci = _mm_set_si64_epi8( 8, 7, 6, 5, 4, 3, 2, 1 );

	while ( td->thread_active ) {

		pc_get( pc, td->cycles_count );

		if ( !td->thread_active ) break;

		pthread_mutex_lock( &lock );
		evaluating_threads++;
		pthread_mutex_unlock( &lock );

		si8 = si8_start;

		switch ( td->instruction ) {

			case 1: // add vectors of 8 8-bit signed integers at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, si8 += td->vector_offset ) {
					xi = _mm_load_si64( (const __m64 *)si8 );
					xi = _m_psadbw( xi, ci );
					_mm_store_si64( (__m64 *)si8, xi );
				}
				break;

			case 2: // adds vectors of 8 8-bit signed integers at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, si8 += td->vector_offset ) {
					xi = _mm_load_si64( (const __m64 *)si8 );
					xi = _mm_sad_pu8( xi, ci );
					_mm_store_si64( (__m64 *)si8, xi );
				}
				break;

			default:
				printf( "sse_ai_epx8_bm_thread%u havn't instruction\n", td->tid );

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

void* sse_ai_epx8_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 8;

	sprintf( td->name, "sse_aiep8th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	uint64_t alloc_length = ( ST_BM_CYCLES_PER_TIME > MT_BM_CYCLES_PER_TIME ? ST_BM_CYCLES_PER_TIME : MT_BM_CYCLES_PER_TIME ) * td->vector_offset;
	uint64_t alloc_size = alloc_length * sizeof( int8_t );
	int8_t *si8 __attribute__((aligned(16))) = (int8_t*)aligned_alloc( 16, alloc_size );
	if ( !si8 ) perror( "aligned_alloc() error" );

	sse_ai_epx8_bm( td, &pc[ DSP_PC ], si8 );

	if ( si8 ) free( si8 );

	return NULL;
}

void* sse_ai_epx8_cpu_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 0;

	sprintf( td->name, "ssecaiep8th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	int8_t si8[ 8 ] __attribute__((aligned(16))) = { 8, 7, 6, 5, 4, 3, 2, 1 };

	sse_ai_epx8_bm( td, &pc[ CPU_PC ], si8 );

	return NULL;
}

#endif // !__SIMD_SSE_AI_EPX8_BM_H__