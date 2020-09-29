#ifndef __BENCHMARK_UNIVERSAL_THREADS_H__
#define __BENCHMARK_UNIVERSAL_THREADS_H__

inline void bmu_threads_init( uint16_t th_cnt, void *(*bm_thread)(void *), void *(*cpu_bm_thread)(void *) ) {
	uint16_t i;
	pthread_attr_t attr;

	threads_count = th_cnt;
	if ( threads_count > MAX_THR_CNT ) threads_count = MAX_THR_CNT;

	// threads attributes initialization
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

	pc_init( &pc[ DSP_PC ], 4096 );
	pc_init( &pc[ CPU_PC ], 4096 );

	pthread_mutex_init( &lock, NULL );
	pthread_cond_init( &stop, NULL );
	pthread_cond_init( &finish, NULL );

	// init threads data
	memset( td[ DSP_PC ], 0x00, threads_count * sizeof(thread_data_t) );
	memset( td[ CPU_PC ], 0x00, threads_count * sizeof(thread_data_t) );
	pthread_mutex_lock( &lock );
	for ( i = 0; i < threads_count; i++ ) {
		td[ DSP_PC ][i].tid = i;
		td[ DSP_PC ][i].instruction = 0;
		td[ DSP_PC ][i].thread_active = true;
		td[ CPU_PC ][i].tid = i;
		td[ CPU_PC ][i].instruction = 0;
		td[ CPU_PC ][i].thread_active = true;
	}
	if ( cpu_bm_thread )
		active_threads = 2 * threads_count;
	else
		active_threads = threads_count;
	pthread_mutex_unlock( &lock );

	// create threads
	for ( i = 0; i < threads_count; i++ ) {
		result = pthread_create( &td[ DSP_PC ][i].th, &attr, bm_thread, &td[ DSP_PC ][i] );
		if ( result != 0 ) perror( "pthread_create( bm ) error" );
		if ( cpu_bm_thread ) {
			result = pthread_create( &td[ CPU_PC ][i].th, &attr, cpu_bm_thread, &td[ CPU_PC ][i] );
			if ( result != 0 ) perror( "pthread_create( cpu_bm ) error" );
		}
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
		for ( i = 0; i < threads_count; i++ ) {
			td[ DSP_PC ][i].instruction = c;
			td[ CPU_PC ][i].instruction = c;
		}
		pthread_mutex_unlock( &lock );

		portion = ( threads_count > 1 ? MT_BM_CYCLES_PER_TIME : ST_BM_CYCLES_PER_TIME );

		_BMARK_ON_;

		cc = cycles_count;
		while ( cc ) {
			if ( cc < portion ) len = cc;
			else len = portion;
			pc_put( &pc[ DSP_PC ], len );
			cc -= len;
		}

		pthread_mutex_lock( &lock );
		while ( evaluating_threads && pc_count( &pc[ DSP_PC ] ) )
			pthread_cond_wait( &stop, &lock );
		pthread_mutex_unlock( &lock );

		_BMARK_OFF( total_time );

		if ( simd_ai ) {

			portion = ( threads_count > 1 ? cycles_count / threads_count : cycles_count );

			_BMARK_ON_;

			cc = cycles_count;
			while ( cc ) {
				if ( cc < portion ) len = cc;
				else len = portion;
				pc_put( &pc[ CPU_PC ], len );
				cc -= len;
			}

			pthread_mutex_lock( &lock );
			while ( evaluating_threads && pc_count( &pc[ CPU_PC ] ) )
				pthread_cond_wait( &stop, &lock );
			pthread_mutex_unlock( &lock );

			_BMARK_OFF( cpu_time );

			print_results( simd_ai[ c ], vector_capacity, cycles_count, total_time, cpu_time );

		}

	}

	return;
}

inline void bmu_threads_finit() {
	uint16_t i;

	// finish threads
	pthread_mutex_lock( &lock );
	for ( i = 0; i < threads_count; i++ ) {
		td[ DSP_PC ][i].instruction = 0;
		td[ DSP_PC ][i].thread_active = false;
		td[ CPU_PC ][i].instruction = 0;
		td[ CPU_PC ][i].thread_active = false;
	}
	pthread_mutex_unlock( &lock );

	pc_stop( &pc[ DSP_PC ] );
	pc_stop( &pc[ CPU_PC ] );

	pthread_mutex_lock( &lock );
	while ( active_threads )
		pthread_cond_wait( &finish, &lock );
	pthread_mutex_unlock( &lock );

	pc_finit( &pc[ DSP_PC ] );
	pc_finit( &pc[ CPU_PC ] );

	// wait for thread finish
	for ( i = 0; i < threads_count; i++ ) {
		result = pthread_join( td[ DSP_PC ][i].th, NULL );
		if ( result != 0 ) perror( "pthread_join( bm ) error" );

		if ( td[ CPU_PC ][i].th ) {
			result = pthread_join( td[ CPU_PC ][i].th, NULL );
			if ( result != 0 ) perror( "pthread_join( cpu_bm ) error" );
		}
	}

	return;
}

inline void bmu_threads( uint16_t th_cnt, uint8_t simd_ai_count, char **simd_ai, void *(*bm_thread)(void *), void *(*cpu_bm_thread)(void *) ) {

	bmu_threads_init( th_cnt, bm_thread, cpu_bm_thread );
	bmu_threads_start( simd_ai_count, simd_ai );
	bmu_threads_finit();

	return;
}

#endif // !__BENCHMARK_UNIVERSAL_THREADS_H__