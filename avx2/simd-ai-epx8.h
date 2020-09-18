#ifndef __SIMD_AI_EPX8_BM_H__
#define __SIMD_AI_EPX8_BM_H__

const uint8_t avx2_ai_epx8_cnt = 8;

char avx2_ai_epx8_instructions[ avx2_ai_epx8_cnt + 1 ][ 100 ] = {
	"AVX2 8-bit Integer Arithmetic Instructions",
	"vpaddb\t_mm256_add_epi8()",
	"vpaddsb\t_mm256_adds_epi8()",
	"vpaddusb\t_mm256_adds_epu8()",
	"vpsubb\t_mm256_sub_epi8()",
	"vpsubsb\t_mm256_adds_epi8()",
	"vpsubusb\t_mm256_adds_epu8()",
	"vpsignb\t_mm256_sign_epi8()",
	"vpsadbw\t_mm256_sad_epu8()"
};

void* avx2_ai_epx8_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	// printf( "avx2_ai_epx8_bm_thread%u started\n", td->tid );

	uint64_t i;
	// uint32_t cx = 0;

	char name[ 25 ];
	sprintf( name, "avx2aiep8th%u", td->tid );
	prctl( PR_SET_NAME, name );

	int8_t ALIGN32 bi[ 32 ] = { 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1 };
	int8_t ALIGN32 ba[ 32 ] = { 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8 };

	while ( td->thread_active ) {

		pthread_mutex_lock( &lock );
		while ( (td->instruction == 0) && td->thread_active )
			pthread_cond_wait( &start, &lock );
		pthread_mutex_unlock( &lock );

		if ( !td->thread_active ) break;

		ai = _mm256_load_si256( (const __m256i *)ba );

		switch ( td->instruction ) {

			case 1: // add vectors of 32 8-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm256_load_si256( (const __m256i *)bi );
					vi = _mm256_add_epi8( vi, ai );
					_mm256_store_si256( (__m256i *)bi, vi );
				}
				break;

			case 2: // adds vectors of 32 8-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm256_load_si256( (const __m256i *)bi );
					vi = _mm256_adds_epi8( vi, ai );
					_mm256_store_si256( (__m256i *)bi, vi );
				}
				break;

			case 3: // adds vectors of 32 8-bit unsigned integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm256_load_si256( (const __m256i *)bi );
					vi = _mm256_adds_epu8( vi, ai );
					_mm256_store_si256( (__m256i *)bi, vi );
				}
				break;

			case 4: // sub vectors of 32 8-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm256_load_si256( (const __m256i *)bi );
					vi = _mm256_sub_epi8( vi, ai );
					_mm256_store_si256( (__m256i *)bi, vi );
				}
				break;

			case 5: // subs vectors of 32 8-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm256_load_si256( (const __m256i *)bi );
					vi = _mm256_subs_epi8( vi, ai );
					_mm256_store_si256( (__m256i *)bi, vi );
				}
				break;

			case 6: // subs vectors of 32 8-bit unsigned integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm256_load_si256( (const __m256i *)bi );
					vi = _mm256_subs_epu8( vi, ai );
					_mm256_store_si256( (__m256i *)bi, vi );
				}
				break;

			case 7: // sign vectors of 32 8-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm256_load_si256( (const __m256i *)bi );
					vi = _mm256_sign_epi8( vi, ai );
					_mm256_store_si256( (__m256i *)bi, vi );
				}
				break;

			case 8: // subs vectors of 32 8-bit unsigned integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm256_load_si256( (const __m256i *)bi );
					vi = _mm256_sad_epu8( vi, ai );
					_mm256_store_si256( (__m256i *)bi, vi );
				}
				break;

			default:
				printf( "avx2_ai_epx8_bm_thread%u havn't instruction\n", td->tid );
				break;

		}

		pthread_mutex_lock( &lock );
		td->instruction = 0;
		SET_BIT( active_threads_flag, td->tid, 0 );
		if ( !active_threads_flag )
			pthread_cond_signal( &stop );
		// printf( "avx2_ai_epx8_bm_thread%u finish cycle #%u\n", td->tid, ++cx );
		pthread_mutex_unlock( &lock );

	}

	// printf( "avx2_ai_epx8_bm_thread%u stopped\n", td->tid );
	return NULL;
}

inline void avx2_ai_epx8_bm_threads_init( int32_t th_cnt ) {
	threads_count = th_cnt;
	if ( threads_count > MAX_THR_CNT ) threads_count = MAX_THR_CNT;

	uint32_t i;

	fprintf( stream, "\n      SIMD Arithmetic instructions with 256-bit vectors of  8-bit integers (measured by %6i MCycles)\n", (int32_t)(cycles_count/1e6) );
	printf( BLUE "      SIMD Arithmetic instructions with 256-bit vectors of  8-bit integers (measured by %6i MCycles)\n" OFF, (int32_t)(cycles_count/1e6) );

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
		result = pthread_create( &td[i].th, &attr, avx2_ai_epx8_bm_thread, &td[i] );
		if ( result != 0 ) perror( "pthread_create() error" );
	}

	// destroy thread attribute object
	result = pthread_attr_destroy( &attr );
	if ( result != 0 ) perror( "pthread_attr_destroy() error" );

	return;
}

inline void avx2_ai_epx8_bm_threads_start() {
	uint32_t i, c;

	// starting current threaded benchmark
	for ( c = 1; c <= avx2_ai_epx8_cnt; c++ ) {
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
		print_results( avx2_ai_epx8_instructions[ c ], 32, cycles_count*threads_count, total_time );
	}

	return;
}

inline void avx2_ai_epx8_bm_threads_finit() {
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

inline void avx2_ai_epx8_st_bm() {
	avx2_ai_epx8_bm_threads_init( 1 );
	avx2_ai_epx8_bm_threads_start();
	avx2_ai_epx8_bm_threads_finit();
	return;
}

inline void avx2_ai_epx8_mt_bm( int32_t th_cnt ) {
	avx2_ai_epx8_bm_threads_init( th_cnt );
	avx2_ai_epx8_bm_threads_start();
	avx2_ai_epx8_bm_threads_finit();
	return;
}

#endif // !__SIMD_AI_EPX8_BM_H__