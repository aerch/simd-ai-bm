#ifndef __SIMD_SSSE3_AI_EPX16_BM_H__
#define __SIMD_SSSE3_AI_EPX16_BM_H__

const uint8_t ssse3_ai_epx16_cnt = 17;

char ssse3_ai_epx16_instructions[ ssse3_ai_epx16_cnt + 1 ][ 100 ] = {
	"SSSE3 16-bit Integer Arithmetic Instructions",
	"vpaddw\t_mm_add_epi16()",
	"vpaddsw\t_mm_adds_epi16()",
	"vpaddusw\t_mm_adds_epu16()",
	"vphaddw\t_mm_hadd_epi16()",
	"vphaddsw\t_mm_hadds_epi16()",
	"vpmaddwd\t_mm_madd_epi16()",
	"vpmaddubsw\t_mm_maddubs_epi16()",
	"vpsubw\t_mm_sub_epi16()",
	"vpsubsw\t_mm_subs_epi16()",
	"vpsubusw\t_mm_subs_epu16()",
	"vphsubw\t_mm_hsub_epi16()",
	"vphsubsw\t_mm_hsubs_epi16()",
	"vpmulhw\t_mm_mulhi_epi16()",
	"vpmullw\t_mm_mullo_epi16()",
	"vpmulhrsw\t_mm_mulhrs_epi16()",
	"vpmulhuw\t_mm_mulhi_epu16()",
	"vpsignw\t_mm_sign_epi16()"
};

void* ssse3_ai_epx16_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	// printf( "ssse3_ai_epx16_bm_thread%u started\n", td->tid );

	uint64_t i;
	// uint32_t cx = 0;

	char name[ 25 ];
	sprintf( name, "ssse3aiep16th%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 8;
	int16_t ALIGN32 wi[ vector_capacity ] = { 8, 7, 6, 5, 4, 3, 2, 1 };
	int16_t ALIGN32 wa[ vector_capacity ] = { 1, 2, 3, 4, 5, 6, 7, 8 };

	while ( td->thread_active ) {

		pthread_mutex_lock( &lock );
		while ( (td->instruction == 0) && td->thread_active )
			pthread_cond_wait( &start, &lock );
		pthread_mutex_unlock( &lock );

		if ( !td->thread_active ) break;

		ai = _mm_load_si128( (const __m128i *)wa );

		switch ( td->instruction ) {

			case 1: // add vectors of 8 16-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm_load_si128( (const __m128i *)wi );
					vi = _mm_add_epi16( vi, ai );
					_mm_store_si128( (__m128i *)wi, vi );
				}
				break;

			case 2: // adds vectors of 8 16-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm_load_si128( (const __m128i *)wi );
					vi = _mm_adds_epi16( vi, ai );
					_mm_store_si128( (__m128i *)wi, vi );
				}
				break;

			case 3: // adds vectors of 8 16-bit unsigned integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm_load_si128( (const __m128i *)wi );
					vi = _mm_adds_epu16( vi, ai );
					_mm_store_si128( (__m128i *)wi, vi );
				}
				break;

			case 4: // hadd vectors of 8 16-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm_load_si128( (const __m128i *)wi );
					vi = _mm_hadd_epi16( vi, ai );
					_mm_store_si128( (__m128i *)wi, vi );
				}
				break;

			case 5: // hadds vectors of 8 16-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm_load_si128( (const __m128i *)wi );
					vi = _mm_hadds_epi16( vi, ai );
					_mm_store_si128( (__m128i *)wi, vi );
				}
				break;

			case 6: // madd vectors of 8 16-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm_load_si128( (const __m128i *)wi );
					vi = _mm_madd_epi16( vi, ai );
					_mm_store_si128( (__m128i *)wi, vi );
				}
				break;

			case 7: // maddubs vectors of 8 16-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm_load_si128( (const __m128i *)wi );
					vi = _mm_maddubs_epi16( vi, ai );
					_mm_store_si128( (__m128i *)wi, vi );
				}
				break;

			case 8: // sub vectors of 8 16-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm_load_si128( (const __m128i *)wi );
					vi = _mm_sub_epi16( vi, ai );
					_mm_store_si128( (__m128i *)wi, vi );
				}
				break;

			case 9: // subs vectors of 8 16-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm_load_si128( (const __m128i *)wi );
					vi = _mm_subs_epi16( vi, ai );
					_mm_store_si128( (__m128i *)wi, vi );
				}
				break;

			case 10:// subs vectors of 8 16-bit unsigned integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm_load_si128( (const __m128i *)wi );
					vi = _mm_subs_epu16( vi, ai );
					_mm_store_si128( (__m128i *)wi, vi );
				}
				break;

			case 11:// hsub vectors of 8 16-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm_load_si128( (const __m128i *)wi );
					vi = _mm_hsub_epi16( vi, ai );
					_mm_store_si128( (__m128i *)wi, vi );
				}
				break;

			case 12:// hsubs vectors of 8 16-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm_load_si128( (const __m128i *)wi );
					vi = _mm_hsubs_epi16( vi, ai );
					_mm_store_si128( (__m128i *)wi, vi );
				}
				break;

			case 13:// mulhi vectors of 8 16-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm_load_si128( (const __m128i *)wi );
					vi = _mm_mulhi_epi16( vi, ai );
					_mm_store_si128( (__m128i *)wi, vi );
				}
				break;

			case 14:// mullo vectors of 8 16-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm_load_si128( (const __m128i *)wi );
					vi = _mm_mullo_epi16( vi, ai );
					_mm_store_si128( (__m128i *)wi, vi );
				}
				break;

			case 15:// mulhrs vectors of 8 16-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm_load_si128( (const __m128i *)wi );
					vi = _mm_mulhrs_epi16( vi, ai );
					_mm_store_si128( (__m128i *)wi, vi );
				}
				break;

			case 16:// mulhi vectors of 8 16-bit unsigned integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm_load_si128( (const __m128i *)wi );
					vi = _mm_mulhi_epu16( vi, ai );
					_mm_store_si128( (__m128i *)wi, vi );
				}
				break;

			case 17:// sign vectors of 8 16-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm_load_si128( (const __m128i *)wi );
					vi = _mm_sign_epi16( vi, ai );
					_mm_store_si128( (__m128i *)wi, vi );
				}
				break;

			default:
				printf( "ssse3_ai_epx16_bm_thread%u havn't instruction\n", td->tid );

		}

		pthread_mutex_lock( &lock );
		td->instruction = 0;
		SET_BIT( active_threads_flag, td->tid, 0 );
		if ( !active_threads_flag )
			pthread_cond_signal( &stop );
		// printf( "ssse3_ai_epx16_bm_thread%u finish cycle #%u\n", td->tid, ++cx );
		pthread_mutex_unlock( &lock );

	}

	// printf( "ssse3_ai_epx16_bm_thread%u stopped\n", td->tid );
	return NULL;
}

inline void ssse3_ai_epx16_bm_threads_init( int32_t th_cnt ) {
	threads_count = th_cnt;
	if ( threads_count > MAX_THR_CNT ) threads_count = MAX_THR_CNT;

	uint32_t i;

	fprintf( stream, "\n      SIMD Arithmetic instructions with 128-bit vectors of 16-bit integers\n" );
	printf( BLUE "      SIMD Arithmetic instructions with 128-bit vectors of 16-bit integers\n" OFF );

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
		result = pthread_create( &td[i].th, &attr, ssse3_ai_epx16_bm_thread, &td[i] );
		if ( result != 0 ) perror( "pthread_create() error" );
	}

	// destroy thread attribute object
	result = pthread_attr_destroy( &attr );
	if ( result != 0 ) perror( "pthread_attr_destroy() error" );

	return;
}

inline void ssse3_ai_epx16_bm_threads_start() {
	uint32_t i, c;

	// starting current threaded benchmark
	for ( c = 1; c <= ssse3_ai_epx16_cnt; c++ ) {
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
		print_results( ssse3_ai_epx16_instructions[ c ], vector_capacity, cycles_count*threads_count, total_time );
	}

	return;
}

inline void ssse3_ai_epx16_bm_threads_finit() {
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

inline void ssse3_ai_epx16_st_bm() {
	ssse3_ai_epx16_bm_threads_init( 1 );
	ssse3_ai_epx16_bm_threads_start();
	ssse3_ai_epx16_bm_threads_finit();
	return;
}

inline void ssse3_ai_epx16_mt_bm( int32_t th_cnt ) {
	ssse3_ai_epx16_bm_threads_init( th_cnt );
	ssse3_ai_epx16_bm_threads_start();
	ssse3_ai_epx16_bm_threads_finit();
	return;
}

#endif // !__SIMD_SSSE3_AI_EPX16_BM_H__