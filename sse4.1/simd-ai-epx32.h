#ifndef __SIMD_SSE4_1_AI_EPX32_BM_H__
#define __SIMD_SSE4_1_AI_EPX32_BM_H__

const uint8_t sse4_1_ai_epx32_cnt = 2;

const char *sse4_1_ai_epx32_instructions[ sse4_1_ai_epx32_cnt + 1 ] = {
	"SIMD SSE4.1 32-bit Integer Arithmetic Instructions with 128-bit vectors ...",
	"pmuldq \t_mm_mul_epi32()    ",
	"pmulld \t_mm_mullo_epi32()    "
};

inline void sse4_1_ai_epx32_bm( thread_data_t *td,  pc_data_t *pc, int32_t *si32, int32_t vector_offset ) {
	int64_t i;
	int32_t *p __attribute__((aligned(16)));
	__m128i wi;
	__m128i bi = _mm_set_epi32( 4, 3, 2, 1 );

	while ( td->thread_active ) {

		p = si32;

		pc_get( pc, td->cycles_count );

		if ( !td->thread_active ) break;

		pthread_mutex_lock( &lock );
		evaluating_threads++;
		pthread_mutex_unlock( &lock );

		switch ( td->instruction ) {

			case 1: // add vectors of 4 32-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					wi = _mm_load_si128( (const __m128i *)p );
					wi = _mm_mul_epi32( wi, bi );
					_mm_store_si128( (__m128i *)p, wi );
				}
				break;

			case 2: // hadd vectors of 4 32-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					wi = _mm_load_si128( (const __m128i *)p );
					wi = _mm_mullo_epi32( wi, bi );
					_mm_store_si128( (__m128i *)p, wi );
				}
				break;

			default:
				printf( "sse4_1_ai_epx32_bm_thread%u havn't instruction\n", td->tid );

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

void* sse4_1_ai_epx32_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 4;

	sprintf( td->name, "sse4.1_aiep32th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	uint64_t alloc_length = ( st_bm_cpt > mt_bm_cpt ? st_bm_cpt : mt_bm_cpt ) * td->vector_offset;
	uint64_t alloc_size = alloc_length * sizeof( int32_t );
	int32_t *si32 __attribute__((aligned(16))) = (int32_t*)aligned_alloc( 16, alloc_size );
	if ( !si32 ) perror( "aligned_alloc() error" );

	sse4_1_ai_epx32_bm( td, &pc[ DSP_PC ], si32, 4 );

	if ( si32 ) free( si32 );

	return NULL;
}

void* sse4_1_ai_epx32_cpu_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 0;

	sprintf( td->name, "sse4.1caiep32th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	int32_t si32[ 4 ] __attribute__((aligned(16))) = { 8, 7, 6, 5 };

	sse4_1_ai_epx32_bm( td, &pc[ CPU_PC ], si32, 0 );

	return NULL;
}

#endif // !__SIMD_SSE4_1_AI_EPX32_BM_H__