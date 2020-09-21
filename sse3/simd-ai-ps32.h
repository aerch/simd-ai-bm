#ifndef __SIMD_SSE3_AI_PS32_BM_H__
#define __SIMD_SSE3_AI_PS32_BM_H__

const uint8_t sse3_ai_ps32_cnt = 3;

const char *sse3_ai_ps32_instructions[ sse3_ai_ps32_cnt + 1 ] = {
	"SIMD SSE3 32-bit Single-Precision Arithmetic Instructions with 128-bit vectors ...",
	"addsubps\t_mm_addsub_ps()  ",
	"haddps  \t_mm_hadd_ps()    ",
	"hsubps  \t_mm_hsub_ps()    "
};

void* sse3_ai_ps32_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	char name[ 25 ];
	uint64_t i;

	sprintf( name, "sse3_aips32th%u", td->tid );
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

			case 1: // add vectors of 4 32-bit singles at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					ws = _mm_load_ps( (const float *)si );
					ws = _mm_addsub_ps( ws, bs );
					_mm_store_ps( (float *)si, ws );
				}
				break;

			case 2: // hadd vectors of 4 32-bit singles at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					ws = _mm_load_ps( (const float *)si );
					ws = _mm_hadd_ps( ws, bs );
					_mm_store_ps( (float *)si, ws );
				}
				break;

			case 3: // hsub vectors of 4 32-bit singles at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					ws = _mm_load_ps( (const float *)si );
					ws = _mm_hsub_ps( ws, bs );
					_mm_store_ps( (float *)si, ws );
				}
				break;

			default:
				printf( "sse3_ai_ps32_bm_thread%u havn't instruction\n", td->tid );

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

#endif // !__SIMD_SSE3_AI_PS32_BM_H__