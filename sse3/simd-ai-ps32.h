#ifndef __SIMD_SSE3_AI_PS32_BM_H__
#define __SIMD_SSE3_AI_PS32_BM_H__

const uint8_t sse3_ai_ps32_cnt = 3;

char sse3_ai_ps32_instructions[ sse3_ai_ps32_cnt + 1 ][ 100 ] = {
	"SSE3 32-bit Single-Precision Arithmetic Instructions",
	"addsubps\t_mm_addsub_ps()  ",
	"haddps  \t_mm_hadd_ps()    ",
	"hsubps  \t_mm_hsub_ps()    "
};

void* sse3_ai_ps32_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	// printf( "sse3_ai_ps32_bm_thread%u started\n", td->tid );

	uint64_t i;
	// uint32_t cx = 0;

	char name[ 25 ];
	sprintf( name, "sse3aips32th%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 8;
	float ALIGN32 si[ vector_capacity ] = { 8, 7, 6, 5, 4, 3, 2, 1 };
	float ALIGN32 sa[ vector_capacity ] = { 1, 2, 3, 4, 5, 6, 7, 8 };

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
		// printf( "sse3_ai_ps32_bm_thread%u finish cycle #%u\n", td->tid, ++cx );
		pthread_mutex_unlock( &lock );

	}

	// printf( "sse3_ai_ps32_bm_thread%u stopped\n", td->tid );
	return NULL;
}

inline void sse3_ai_ps32_bm_threads_init( int32_t th_cnt ) {
	threads_count = th_cnt;
	if ( threads_count > MAX_THR_CNT ) threads_count = MAX_THR_CNT;

	uint32_t i;

	fprintf( stream, "\n      SIMD Arithmetic instructions with 128-bit vectors of single-precision\n" );
	printf( BLUE "      SIMD Arithmetic instructions with 128-bit vectors of single-precision\n" OFF );

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
		result = pthread_create( &td[i].th, &attr, sse3_ai_ps32_bm_thread, &td[i] );
		if ( result != 0 ) perror( "pthread_create() error" );
	}

	// destroy thread attribute object
	result = pthread_attr_destroy( &attr );
	if ( result != 0 ) perror( "pthread_attr_destroy() error" );

	return;
}

inline void sse3_ai_ps32_bm_threads_start() {
	uint32_t i, c;

	// starting current threaded benchmark
	for ( c = 1; c <= sse3_ai_ps32_cnt; c++ ) {
		pthread_mutex_lock( &lock );
		for ( i = 0; i < threads_count; i++ ) {
			td[i].instruction = c;
			SET_BIT( active_threads_flag, i, 1 );
		}
		_BMARK_ON_;
		pthread_cond_broadcast( &start );
		while ( active_threads_flag )
			pthread_cond_wait( &stop, &lock );
		_BMARK_OFF( total_time );
		pthread_mutex_unlock( &lock );
		print_results( sse3_ai_ps32_instructions[ c ], vector_capacity, cycles_count*threads_count, total_time );
	}

	return;
}

inline void sse3_ai_ps32_bm_threads_finit() {
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

inline void sse3_ai_ps32_st_bm() {
	sse3_ai_ps32_bm_threads_init( 1 );
	sse3_ai_ps32_bm_threads_start();
	sse3_ai_ps32_bm_threads_finit();
	return;
}

inline void sse3_ai_ps32_mt_bm( int32_t th_cnt ) {
	sse3_ai_ps32_bm_threads_init( th_cnt );
	sse3_ai_ps32_bm_threads_start();
	sse3_ai_ps32_bm_threads_finit();
	return;
}

#endif // !__SIMD_SSE3_AI_PS32_BM_H__