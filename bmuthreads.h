#ifndef __BENCHMARK_UNIVERSAL_THREADS_H__
#define __BENCHMARK_UNIVERSAL_THREADS_H__

inline void bmu_threads_init( uint16_t th_cnt, void *(*bm_thread)(void *) ) {
	uint16_t i;
	threads_count = th_cnt;
	if ( threads_count > MAX_THR_CNT ) threads_count = MAX_THR_CNT;

	active_threads = 0;

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
	pthread_attr_setstacksize( &attr, PTHREAD_STACK_SIZE );
	#endif

	pc_init( 8192 );

	pthread_mutex_init( &lock, NULL );
	pthread_cond_init( &start, NULL );
	pthread_cond_init( &stop, NULL );
	pthread_cond_init( &finish, NULL );

	// init threads data
	memset( td, 0x00, threads_count * sizeof(thread_data_t) );
	pthread_mutex_lock( &lock );
	for ( i = 0; i < threads_count; i++ ) {
		td[i].tid = i;
		td[i].instruction = 0;
		td[i].thread_active = true;
	}
	active_threads = threads_count;
	pthread_mutex_unlock( &lock );

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
	uint16_t i, c;
	uint64_t cc, portion, len;

	if ( simd_ai )
		make_simd_title( simd_ai[ 0 ] );

	// starting current threaded benchmark
	for ( c = 1; c <= simd_ai_count; c++ ) {

		pthread_mutex_lock( &lock );
		for ( i = 0; i < threads_count; i++ )
			td[i].instruction = c;
		pthread_cond_broadcast( &start );
		pthread_mutex_unlock( &lock );

		if ( threads_count > 1 ) portion = MT_BM_CYCLES_PER_TIME;
		else portion = ST_BM_CYCLES_PER_TIME;
		cc = cycles_count;

		_BMARK_ON_;

		while ( cc ) {
			if ( cc < portion ) len = cc;
			else len = portion;
			pc_put( len );
			cc -= len;
		}

		pthread_mutex_lock( &lock );
		while ( pc_count() )
			pthread_cond_wait( &stop, &lock );
		pthread_mutex_unlock( &lock );

		_BMARK_OFF( total_time );

		if ( simd_ai )
			print_results( simd_ai[ c ], vector_capacity, cycles_count, total_time );

	}

	return;
}

inline void bmu_threads_finit() {
	uint16_t i;

	// finish threads
	pthread_mutex_lock( &lock );
	for ( i = 0; i < threads_count; i++ ) {
		td[i].thread_active = false;
		td[i].instruction = 0;
	}
	pthread_cond_broadcast( &start );
	pthread_mutex_unlock( &lock );

	pc_stop();

	pthread_mutex_lock( &lock );
	while ( active_threads )
		pthread_cond_wait( &finish, &lock );
	pthread_mutex_unlock( &lock );

	pc_finit();

	// wait for thread finish
	for ( i = 0; i < threads_count; i++ ) {
		result = pthread_join( td[i].th, NULL );
		if ( result != 0 ) perror( "pthread_join() error" );
	}

	return;
}

inline void bmu_threads( uint16_t th_cnt, uint8_t simd_ai_count, char **simd_ai, void *(*bm_thread)(void *) ) {

	bmu_threads_init( th_cnt, bm_thread );
	bmu_threads_start( simd_ai_count, simd_ai );
	bmu_threads_finit();

	return;
}

#endif // !__BENCHMARK_UNIVERSAL_THREADS_H__