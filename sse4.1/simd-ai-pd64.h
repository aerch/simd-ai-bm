#ifndef __SIMD_SSE4_1_AI_PD64_BM_H__
#define __SIMD_SSE4_1_AI_PD64_BM_H__

const uint8_t sse4_1_ai_pd64_cnt = 1;

const char *sse4_1_ai_pd64_instructions[ sse4_1_ai_pd64_cnt + 1 ] = {
	"SIMD SSE4.1 64-bit Double-Precision Arithmetic Instructions with 128-bit vectors ...",
	"dppd   \t_mm_dp_pd()         "
};

void* sse4_1_ai_pd64_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	char name[ 25 ];
	uint64_t i;

	sprintf( name, "sse4.1_aipd64th%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 2;
	double ALIGN16 di[ vector_capacity ] = { 8, 7 };
	double ALIGN16 da[ vector_capacity ] = { 1, 2 };

	while ( td->thread_active ) {

		pthread_mutex_lock( &lock );
		while ( (td->instruction == 0) && td->thread_active )
			pthread_cond_wait( &start, &lock );
		pthread_mutex_unlock( &lock );

		if ( !td->thread_active ) break;

		bd = _mm_load_pd( (const double *)da );

		switch ( td->instruction ) {

			case 1: // pd vectors of 2 64-bit doubles at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					wd = _mm_load_pd( (const double *)di );
					wd = _mm_dp_pd( wd, bd, 0x0f );
					_mm_store_pd( (double *)di, wd );
				}
				break;

			default:
				printf( "sse4_1_ai_pd64_bm_thread%u havn't instruction\n", td->tid );

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

#endif // !__SIMD_SSE4_1_AI_PD64_BM_H__