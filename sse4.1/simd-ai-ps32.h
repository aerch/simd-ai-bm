#ifndef __SIMD_SSE4_1_AI_PS32_BM_H__
#define __SIMD_SSE4_1_AI_PS32_BM_H__

const uint8_t sse4_1_ai_ps32_cnt = 1;

const char *sse4_1_ai_ps32_instructions[ sse4_1_ai_ps32_cnt + 1 ] = {
	"SIMD SSE4.1 32-bit Single-Precision Arithmetic Instructions with 128-bit vectors ...",
	"dpps   \t_mm_dp_ps()         "
};

void* sse4_1_ai_ps32_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	char name[ 25 ];
	uint64_t i;

	sprintf( name, "sse4.1_aips32th%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 4;
	float ALIGN16 si[ vector_capacity ] = { 8, 7, 6, 5 };
	float ALIGN16 sa[ vector_capacity ] = { 1, 2, 3, 4 };

	while ( td->thread_active ) {

		pthread_mutex_lock( &lock );
		while ( (td->instruction == 0) && td->thread_active )
			pthread_cond_wait( &start, &lock );
		pthread_mutex_unlock( &lock );

		if ( !td->thread_active ) break;

		bs = _mm_load_ps( (const float *)sa );

		switch ( td->instruction ) {

			case 1: // pd vectors of 2 32-bit singles at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					ws = _mm_load_ps( (const float *)si );
					ws = _mm_dp_ps( ws, bs, 0x0f );
					_mm_store_ps( (float *)si, ws );
				}
				break;

			default:
				printf( "sse4_1_ai_ps32_bm_thread%u havn't instruction\n", td->tid );

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

#endif // !__SIMD_SSE4_1_AI_PS32_BM_H__