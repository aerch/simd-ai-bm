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
	for ( i = 0; i < threads_count; i++ ) {
		td[i].tid = i;
		td[i].instruction = 0;
		td[i].thread_active = true;
		td[i].cycles_count = cycles_count / threads_count;
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

	if ( simd_ai )
		make_simd_title( simd_ai[ 0 ] );

	// starting current threaded benchmark
	for ( c = 1; c <= simd_ai_count; c++ ) {
		pthread_mutex_lock( &lock );
		for ( i = 0; i < threads_count; i++ ) {
			td[i].instruction = c;
			SET_BIT( active_threads_flag, i, 1 );
		}
		pthread_cond_broadcast( &start );
		_BMARK_ON_;
		while ( active_threads_flag )
			pthread_cond_wait( &stop, &lock );
		_BMARK_OFF( total_time );
		pthread_mutex_unlock( &lock );
		if ( simd_ai )
			print_results( simd_ai[ c ], vector_capacity, cycles_count, total_time );
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

void* cpu_warmup_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	char name[ 25 ];
	uint64_t i;

	sprintf( name, "cpu_warmup%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 4;
	int64_t alloc_size = td->cycles_count * vector_capacity * sizeof( double );
	double *pd64 __attribute__((aligned(32))) = (double*)aligned_alloc( 32, alloc_size );
	if ( !pd64 ) perror( "aligned_alloc() error" );

	ad = _mm256_set_pd( 1.0f, 2.0f, 3.0f, 4.0f );

	while ( td->thread_active ) {

		pthread_mutex_lock( &lock );
		while ( (td->instruction == 0) && td->thread_active )
			pthread_cond_wait( &start, &lock );
		pthread_mutex_unlock( &lock );

		if ( !td->thread_active ) break;

		for ( i = 0; i < td->cycles_count * 100; i++ ) {
			vd = _mm256_load_pd( (const double *)pd64 );
			vd = _mm256_add_pd( vd, ad );
			_mm256_store_pd( (double *)pd64, vd );
		}

		pthread_mutex_lock( &lock );
		td->instruction = 0;
		SET_BIT( active_threads_flag, td->tid, 0 );
		if ( !active_threads_flag )
			pthread_cond_signal( &stop );
		pthread_mutex_unlock( &lock );

	}

	if ( pd64 )
		free( pd64 );

	return NULL;
}
inline void make_cpu_warmup( uint8_t th_cnt ) {
	fprintf( stdout, BLUE "Central Processing Unit Warm Up (in %d thread(s)) ..." OFF, th_cnt ); fflush( stdout );
	bmu_threads( th_cnt, 1, NULL, &cpu_warmup_thread );
	printf( BLUE " Done." OFF "\n\n" );
	return;
}

#endif // !__BENCHMARK_UNIVERSAL_THREADS_H__