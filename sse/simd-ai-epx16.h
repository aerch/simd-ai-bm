#ifndef __SIMD_SSE_AI_EPX16_BM_H__
#define __SIMD_SSE_AI_EPX16_BM_H__

const uint8_t sse_ai_epx16_cnt = 2;

const char *sse_ai_epx16_instructions[ sse_ai_epx16_cnt + 1 ] = {
	"SIMD SSE 16-bit Integer Arithmetic Instructions with 64-bit vectors ...",
	"pmulhuw\t_m_pmulhuw()      ",
	"pmulhuw\t_mm_mulhi_pu16()  "
};

inline void sse_ai_epx16_bm( thread_data_t *td,  pc_data_t *pc, int16_t *si16, int32_t vector_offset ) {
	int64_t i;
	int16_t *p __attribute__((aligned(16)));
	__m64 xi;
	__m64 ci = _mm_set_si64_epi16( 4, 3, 2, 1 );

	while ( td->thread_active ) {

		p = si16;

		pc_get( pc, td->cycles_count );

		if ( !td->thread_active ) break;

		pthread_mutex_lock( &lock );
		evaluating_threads++;
		pthread_mutex_unlock( &lock );

		switch ( td->instruction ) {

			case 1: // pmulhuw vectors of 4 16-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					xi = *((const __m64*)p);
					xi = _m_pmulhuw( xi, ci );
					*((__m64 *)p) = xi;
				}
				break;

			case 2: // mulhi vectors of 4 16-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					xi = *((const __m64*)p);
					xi = _mm_mulhi_pu16( xi, ci );
					*((__m64 *)p) = xi;
				}
				break;

			default:
				printf( "sse_ai_epx16_bm_thread%u havn't instruction\n", td->tid );

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

void* sse_ai_epx16_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 4;

	sprintf( td->name, "sse_aiep16th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	uint64_t alloc_length = ( ST_BM_CYCLES_PER_TIME > MT_BM_CYCLES_PER_TIME ? ST_BM_CYCLES_PER_TIME : MT_BM_CYCLES_PER_TIME ) * td->vector_offset;
	uint64_t alloc_size = alloc_length * sizeof( int16_t );
	int16_t *si16 __attribute__((aligned(16))) = (int16_t*)aligned_alloc( 16, alloc_size );
	if ( !si16 ) perror( "aligned_alloc() error" );

	sse_ai_epx16_bm( td, &pc[ DSP_PC ], si16, 4 );

	if ( si16 ) free( si16 );

	return NULL;
}

void* sse_ai_epx16_cpu_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 0;

	sprintf( td->name, "ssecaiep16th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	int16_t si16[ 4 ] __attribute__((aligned(16))) = { 8, 6, 4, 2 };

	sse_ai_epx16_bm( td, &pc[ CPU_PC ], si16, 0 );

	return NULL;
}

#endif // !__SIMD_SSE_AI_EPX16_BM_H__