#ifndef __SIMD_SSE_AI_EPX16_BM_H__
#define __SIMD_SSE_AI_EPX16_BM_H__

const uint8_t sse_ai_epx16_cnt = 2;

const char *sse_ai_epx16_instructions[ sse_ai_epx16_cnt + 1 ] = {
	"SIMD SSE 16-bit Integer Arithmetic Instructions with 64-bit vectors ...",
	"pmulhuw\t_m_pmulhuw()      ",
	"pmulhuw\t_mm_mulhi_pu16()  "
};

void* sse_ai_epx16_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	uint64_t i, _vi_;
	char name[ 25 ];

	sprintf( name, "sse_aiep16th%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 4;
	uint64_t alloc_length = MT_BM_CYCLES_PER_TIME * vector_capacity;
	uint64_t alloc_size = alloc_length * sizeof( int16_t );
	int16_t *si16 __attribute__((aligned(16))) = (int16_t*)aligned_alloc( 16, alloc_size );
	if ( !si16 ) perror( "aligned_alloc() error" );

	ci = _mm_set_si64_epi16( 4, 3, 2, 1 );

	pthread_mutex_lock( &lock );
	while ( (td->instruction == 0) && td->thread_active )
		pthread_cond_wait( &start, &lock );
	pthread_mutex_unlock( &lock );

	while ( td->thread_active ) {

		pc_get( td->cycles_count );

		if ( !td->thread_active ) break;

		switch ( td->instruction ) {

			case 1: // pmulhuw vectors of 4 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si16[_vi_] );
					xi = _m_pmulhuw( xi, ci );
					_mm_store_si64( (__m64 *)&si16[_vi_], xi );
				}
				break;

			case 2: // mulhi vectors of 4 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si16[_vi_] );
					xi = _mm_mulhi_pu16( xi, ci );
					_mm_store_si64( (__m64 *)&si16[_vi_], xi );
				}
				break;

			default:
				printf( "sse_ai_epx16_bm_thread%u havn't instruction\n", td->tid );

		}

		pthread_mutex_lock( &lock );
		pthread_cond_signal( &stop );
		pthread_mutex_unlock( &lock );

	}

	pthread_mutex_lock( &lock );
	active_threads--;
	pthread_cond_signal( &finish );
	pthread_mutex_unlock( &lock );

	if ( si16 )
		free( si16 );

	return NULL;
}

#endif // !__SIMD_SSE_AI_EPX16_BM_H__