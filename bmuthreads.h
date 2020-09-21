#ifndef __BENCHMARK_UNIVERSAL_THREADS_H__
#define __BENCHMARK_UNIVERSAL_THREADS_H__

inline void bmu_threads_init( uint8_t th_cnt, void *(*bm_thread)(void *) ) {
	uint8_t i;
	threads_count = th_cnt;
	if ( threads_count > MAX_THR_CNT ) threads_count = MAX_THR_CNT;

	active_threads_flag = 0;

	// threads attributes initialization
	pthread_attr_t attr;

	result = pthread_attr_init( &attr );
	if ( result != 0 ) perror( "pthread_attr_init() error" );

	#ifdef PTHREAD_SCHED_FIFO
	struct sched_param param;
	int fifo_max_prio;
	pthread_attr_setinheritsched( &attr, PTHREAD_EXPLICIT_SCHED );
	pthread_attr_setschedpolicy( &attr, SCHED_FIFO );
	fifo_max_prio = sched_get_priority_max( SCHED_FIFO );
	param.sched_priority = fifo_max_prio;
	pthread_attr_setschedparam( &attr, &param );
	#endif

	#ifdef PTHREAD_STACK_SIZE
	// size_t stack_size = 0;
	// pthread_attr_getstacksize( &attr, &stack_size );
	// pthread_attr_setstacksize( &attr, stack_size * 4 );
	pthread_attr_setstacksize( &attr, PTHREAD_STACK_SIZE );
	#endif

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
		result = pthread_create( &td[i].th, &attr, bm_thread, &td[i] );
		if ( result != 0 ) perror( "pthread_create() error" );
	}

	// destroy thread attribute object
	result = pthread_attr_destroy( &attr );
	if ( result != 0 ) perror( "pthread_attr_destroy() error" );

	return;
}

inline void bmu_threads_start( uint8_t simd_ai_count, char **simd_ai ) {
	uint8_t i, c;

	make_simd_title( simd_ai[ 0 ] );

	// starting current threaded benchmark
	for ( c = 1; c <= simd_ai_count; c++ ) {
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
		print_results( simd_ai[ c ], vector_capacity, cycles_count*threads_count, total_time );
	}

	return;
}

inline void bmu_threads_finit() {
	uint8_t i;

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

inline void bmu_threads( uint8_t th_cnt, uint8_t simd_ai_count, char **simd_ai, void *(*bm_thread)(void *) ) {
	bmu_threads_init( th_cnt, bm_thread );
	bmu_threads_start( simd_ai_count, simd_ai );
	bmu_threads_finit();
	return;
}

#endif // !__BENCHMARK_UNIVERSAL_THREADS_H__