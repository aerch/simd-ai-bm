#ifndef __SIMD_SSE4_1_AI_EPX32_BM_H__
#define __SIMD_SSE4_1_AI_EPX32_BM_H__

const uint8_t sse4_1_ai_epx32_cnt = 2;

const char *sse4_1_ai_epx32_instructions[ sse4_1_ai_epx32_cnt + 1 ] = {
	"SIMD SSE4.1 32-bit Integer Arithmetic Instructions with 128-bit vectors ...",
	"pmuldq \t_mm_mul_epi32()    ",
	"pmulld \t_mm_mullo_epi32()    "
};

void* sse4_1_ai_epx32_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	uint64_t i, _vi_;
	char name[ 25 ];

	sprintf( name, "sse4.1_aiep32th%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 4;
	uint64_t alloc_length = MT_BM_CYCLES_PER_TIME * vector_capacity;
	uint64_t alloc_size = alloc_length * sizeof( int32_t );
	int32_t *si32 __attribute__((aligned(16))) = (int32_t*)aligned_alloc( 16, alloc_size );
	if ( !si32 ) perror( "aligned_alloc() error" );

	bi = _mm_set_epi32( 4, 3, 2, 1 );

	pthread_mutex_lock( &lock );
	while ( (td->instruction == 0) && td->thread_active )
		pthread_cond_wait( &start, &lock );
	pthread_mutex_unlock( &lock );

	while ( td->thread_active ) {

		pc_get( td->cycles_count );

		if ( !td->thread_active ) break;

		switch ( td->instruction ) {

			case 1: // add vectors of 8 32-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wi = _mm_load_si128( (const __m128i *)&si32[_vi_] );
					wi = _mm_mul_epi32( wi, bi );
					_mm_store_si128( (__m128i *)&si32[_vi_], wi );
				}
				break;

			case 2: // hadd vectors of 8 32-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wi = _mm_load_si128( (const __m128i *)&si32[_vi_] );
					wi = _mm_mullo_epi32( wi, bi );
					_mm_store_si128( (__m128i *)&si32[_vi_], wi );
				}
				break;

			default:
				printf( "sse4_1_ai_epx32_bm_thread%u havn't instruction\n", td->tid );

		}

		pthread_mutex_lock( &lock );
		pthread_cond_signal( &stop );
		pthread_mutex_unlock( &lock );

	}

	pthread_mutex_lock( &lock );
	active_threads--;
	pthread_cond_signal( &finish );
	pthread_mutex_unlock( &lock );

	if ( si32 )
		free( si32 );

	return NULL;
}

#endif // !__SIMD_SSE4_1_AI_EPX32_BM_H__