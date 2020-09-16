#ifndef __SIMD_AI_EPX64_BM_H__
#define __SIMD_AI_EPX64_BM_H__

const uint8_t avx2_ai_epx64_cnt = 2;

char avx2_ai_epx64_instructions[ avx2_ai_epx64_cnt + 1 ][ 100 ] = {
	"AVX2 64-bit Integer Arithmetic Instructions",
	"vpaddq\t_mm256_add_epi64()",
	"vpsubq\t_mm256_sub_epi64()"
};

void* avx2_ai_epx64_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	// printf( "avx2_ai_epx64_bm_thread%u started\n", td->tid );

	uint32_t i;
	// uint32_t cx = 0;

	char name[ 25 ];
	sprintf( name, "avx2aiep64th%u", td->tid );
	prctl( PR_SET_NAME, name );

	int64_t ALIGN32 qi[ 4 ] = { 8, 7, 6, 5 };
	int64_t ALIGN32 qa[ 4 ] = { 1, 2, 3, 4 };

	while ( td->thread_active ) {

		pthread_mutex_lock( &lock );
		while ( (td->instruction == 0) && td->thread_active )
			pthread_cond_wait( &start, &lock );
		pthread_mutex_unlock( &lock );

		if ( !td->thread_active ) break;

		a = _mm256_load_si256( (const __m256i *)qa );

		switch ( td->instruction ) {

			case 1: // add vectors of 4 64-bit signed integers at a cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					v = _mm256_load_si256( (const __m256i *)qi );
					v = _mm256_add_epi64( v, a );
					_mm256_store_si256( (__m256i *)qi, v );
				}
				break;

			case 2: // sub vectors of 4 64-bit signed integers at a cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					v = _mm256_load_si256( (const __m256i *)qi );
					v = _mm256_sub_epi64( v, a );
					_mm256_store_si256( (__m256i *)qi, v );
				}
				break;

			default:
				printf( "avx2_ai_epx64_bm_thread%u havn't instruction\n", td->tid );
				break;

		}

		pthread_mutex_lock( &lock );
		td->instruction = 0;
		SET_BIT( active_threads_flag, td->tid, 0 );
		pthread_cond_signal( &stop );
		// printf( "avx2_ai_epx64_bm_thread%u finish cycle #%u\n", td->tid, ++cx );
		pthread_mutex_unlock( &lock );

	}

	// printf( "avx2_ai_epx64_bm_thread%u stopped\n", td->tid );
	return NULL;
}

inline void avx2_ai_epx64_bm_threads_init( int32_t th_cnt ) {
	threads_count = th_cnt;
	if ( threads_count > MAX_THR_CNT ) threads_count = MAX_THR_CNT;

	uint32_t i;

	fprintf( stream, "\n\tSIMD Arithmetic instructions with 256-bit vectors of 64-bit integers (measured by %i MCycles)\n", (int32_t)(cycles_count/1e6) );
	printf( BLUE "      SIMD Arithmetic instructions with 256-bit vectors of 64-bit integers (measured by %i MCycles)\n" OFF, (int32_t)(cycles_count/1e6) );

	active_threads_flag = 0;

	// threads attributes initialization
	pthread_attr_t attr;

	result = pthread_attr_init( &attr );
	if ( result != 0 ) perror( "pthread_attr_init() error" );

	// struct sched_param param;
	// int fifo_max_prio;
	// pthread_attr_setinheritsched( &attr, PTHREAD_EXPLICIT_SCHED );
	// pthread_attr_setschedpolicy( &attr, SCHED_FIFO );
	// fifo_max_prio = sched_get_priority_max( SCHED_FIFO );
	// param.sched_priority = fifo_max_prio;
	// pthread_attr_setschedparam( &attr, &param );

	// size_t stack_size = 0;
	// pthread_attr_getstacksize( &attr, &stack_size );
	// pthread_attr_setstacksize( &attr, stack_size * 16 );

	pthread_mutex_init( &lock, NULL );
	pthread_cond_init( &start, NULL );
	pthread_cond_init( &stop, NULL );

	// init threads data
	memset( td, 0x00, threads_count * sizeof(thread_data_t) );
	for ( i = 0; i < threads_count; i++ )	{
		td[i].tid = i;
		td[i].cycles_count = cycles_count;
		td[i].thread_active = true;
		td[i].instruction = 0;
	}

	// create threads
	for ( i = 0; i < threads_count; i++ ) {
		result = pthread_create( &td[i].th, &attr, avx2_ai_epx64_bm_thread, &td[i] );
		if ( result != 0 ) perror( "pthread_create() error" );
	}

	// destroy thread attribute object
	result = pthread_attr_destroy( &attr );
	if ( result != 0 ) perror( "pthread_attr_destroy() error" );

	return;
}

inline void avx2_ai_epx64_bm_threads_start() {
	uint32_t i, c;

	// starting current threaded benchmark
	for ( c = 1; c <= avx2_ai_epx64_cnt; c++ ) {
		_BMARK_ON_;
		pthread_mutex_lock( &lock );
		for ( i = 0; i < threads_count; i++ ) {
			td[i].instruction = c;
			SET_BIT( active_threads_flag, i, 1 );
		}
		pthread_cond_broadcast( &start );
		while ( active_threads_flag )
			pthread_cond_wait( &stop, &lock );
		pthread_mutex_unlock( &lock );
		_BMARK_OFF( total_time );
		print_results( avx2_ai_epx64_instructions[ c ], 4, cycles_count*threads_count, total_time );
	}

	return;
}

inline void avx2_ai_epx64_bm_threads_finit() {
	uint32_t i;

	// finish threads
	pthread_mutex_lock( &lock );
	for ( i = 0; i < threads_count; i++ ) {
		td[i].thread_active = false;
		td[i].instruction = 0;
	}
	pthread_cond_broadcast( &start );
	pthread_mutex_unlock( &lock );

	// wait for thread finish
	for ( i = 0; i < threads_count; i++ ) {
		result = pthread_join( td[i].th, NULL );
		if ( result != 0 ) perror( "pthread_join() error" );
	}

	return;
}

inline void avx2_ai_epx64_st_bm() {
	avx2_ai_epx64_bm_threads_init( 1 );
	avx2_ai_epx64_bm_threads_start();
	avx2_ai_epx64_bm_threads_finit();
	return;
}

inline void avx2_ai_epx64_mt_bm( int32_t th_cnt ) {
	avx2_ai_epx64_bm_threads_init( th_cnt );
	avx2_ai_epx64_bm_threads_start();
	avx2_ai_epx64_bm_threads_finit();
	return;
}

#endif // !__SIMD_AI_EPX64_BM_H__