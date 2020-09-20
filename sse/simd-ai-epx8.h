#ifndef __SIMD_SSE_AI_EPX8_BM_H__
#define __SIMD_SSE_AI_EPX8_BM_H__

const uint8_t sse_ai_epx8_cnt = 2;

const char *sse_ai_epx8_instructions[ sse_ai_epx8_cnt + 1 ] = {
	"SIMD SSE 8-bit Integer Arithmetic Instructions with 64-bit vectors ...",
	"psadbw\t_m_psadbw()        ",
	"psadbw\t_mm_sad_pu8()      "
};

void* sse_ai_epx8_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	char name[ 25 ];
	uint64_t i;

	sprintf( name, "sse_aiep8th%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 8;
	int8_t ALIGN16 _bi[ vector_capacity ] = { 8, 7, 6, 5, 4, 3, 2, 1 };
	int8_t ALIGN16 _ba[ vector_capacity ] = { 1, 2, 3, 4, 5, 6, 7, 8 };

	while ( td->thread_active ) {

		pthread_mutex_lock( &lock );
		while ( (td->instruction == 0) && td->thread_active )
			pthread_cond_wait( &start, &lock );
		pthread_mutex_unlock( &lock );

		if ( !td->thread_active ) break;

		ci = _mm_load_si64( (const __m64 *)_ba );

		switch ( td->instruction ) {

			case 1: // add vectors of 8 8-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					xi = _mm_load_si64( (const __m64 *)_bi );
					xi = _m_psadbw( xi, ci );
					_mm_store_si64( (__m64 *)_bi, xi );
				}
				break;

			case 2: // adds vectors of 8 8-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					xi = _mm_load_si64( (const __m64 *)_bi );
					xi = _mm_sad_pu8( xi, ci );
					_mm_store_si64( (__m64 *)_bi, xi );
				}
				break;

			default:
				printf( "sse_ai_epx8_bm_thread%u havn't instruction\n", td->tid );

		}

		pthread_mutex_lock( &lock );
		td->instruction = 0;
		SET_BIT( active_threads_flag, td->tid, 0 );
		if ( !active_threads_flag )
			pthread_cond_signal( &stop );
		pthread_mutex_unlock( &lock );

	}

	return NULL;
}

#endif // !__SIMD_SSE_AI_EPX8_BM_H__