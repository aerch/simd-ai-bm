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
	char name[ 25 ];
	uint64_t i;

	sprintf( name, "sse_aiep16th%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 4;
	int16_t ALIGN16 _wi[ vector_capacity ] = { 8, 7, 6, 5 };
	int16_t ALIGN16 _wa[ vector_capacity ] = { 1, 2, 3, 4 };

	while ( td->thread_active ) {

		pthread_mutex_lock( &lock );
		while ( (td->instruction == 0) && td->thread_active )
			pthread_cond_wait( &start, &lock );
		pthread_mutex_unlock( &lock );

		if ( !td->thread_active ) break;

		ci = _mm_load_si64( (const __m64 *)_wa );

		switch ( td->instruction ) {

			case 1: // pmulhuw vectors of 4 16-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					xi = _mm_load_si64( (const __m64 *)_wi );
					xi = _m_pmulhuw( xi, ci );
					_mm_store_si64( (__m64 *)_wi, xi );
				}
				break;

			case 2: // mulhi vectors of 4 16-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					xi = _mm_load_si64( (const __m64 *)_wi );
					xi = _mm_mulhi_pu16( xi, ci );
					_mm_store_si64( (__m64 *)_wi, xi );
				}
				break;

			default:
				printf( "sse_ai_epx16_bm_thread%u havn't instruction\n", td->tid );

		}

		pthread_mutex_lock( &lock );
		td->instruction = 0;
		SET_BIT( active_threads, td->tid, 0 );
		if ( !active_threads )
			pthread_cond_signal( &stop );
		pthread_mutex_unlock( &lock );

	}

	return NULL;
}

#endif // !__SIMD_SSE_AI_EPX16_BM_H__