#ifndef __CPU_WARM_UP_THREAD_H__
#define __CPU_WARM_UP_THREAD_H__

void* cpu_warmup_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	int64_t i,/* j,*/ _vi_;
	__m256d ad, vd;

	sprintf( td->name, "_aibm_warmup%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	vector_capacity = 4;
	uint64_t alloc_length = ( ST_BM_CYCLES_PER_TIME > MT_BM_CYCLES_PER_TIME ? ST_BM_CYCLES_PER_TIME : MT_BM_CYCLES_PER_TIME ) * vector_capacity;
	uint64_t alloc_size = alloc_length * sizeof( double );
	double *pd64 __attribute__((aligned(32))) = (double*)aligned_alloc( 32, alloc_size );
	if ( !pd64 ) perror( "aligned_alloc() error" );

	ad = _mm256_set_pd( 1.11111f, 2.22222f, 3.33333f, 4.44444f );

	while ( td->thread_active ) {

		pc_get( &pc[ DSP_PC ], td->cycles_count );

		if ( !td->thread_active ) break;

		pthread_mutex_lock( &lock );
		evaluating_threads++;
		pthread_mutex_unlock( &lock );

		// for ( j = 0; j < 1; j++ ) {

			for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
				vd = _mm256_load_pd( (const double *)&pd64[_vi_] );
				vd = _mm256_add_pd( vd, ad );
				_mm256_store_pd( (double *)&pd64[_vi_], vd );
			}

		// }

		pthread_mutex_lock( &lock );
		evaluating_threads--;
		pthread_cond_signal( &stop );
		pthread_mutex_unlock( &lock );

	}

	pthread_mutex_lock( &lock );
	active_threads--;
	pthread_cond_signal( &finish );
	pthread_mutex_unlock( &lock );

	if ( pd64 ) free( pd64 );

	return NULL;
}

inline void make_cpu_warmup() {

	fprintf( stdout, BLUE "Central Processing Unit & Memory Units Warm Up (in %d thread(s)) ..." OFF, MULTIPLE_THREADS ); fflush( stdout );

	bmu_threads( MULTIPLE_THREADS, 1, NULL, &cpu_warmup_thread, NULL );

	printf( BLUE " Done." OFF "\n\n" );

	return;
}

#endif // !__CPU_WARM_UP_THREAD_H__