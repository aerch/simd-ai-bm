#ifndef __CPU_WARM_UP_THREAD_H__
#define __CPU_WARM_UP_THREAD_H__

uint32_t best_cpt;

#ifdef __MMX__
void* mmx_calibrating_and_warmup_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 8;
	int64_t i;
	int8_t *p __attribute__((aligned(16)));
	__m64 xi;
	__m64 ci = _mm_set_si64_epi8( 8, 7, 6, 5, 4, 3, 2, 1 );

	sprintf( td->name, "mmx_ai_bm_warmup%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	uint64_t alloc_length = ( st_bm_cpt > mt_bm_cpt ? st_bm_cpt : mt_bm_cpt ) * td->vector_offset;
	uint64_t alloc_size = alloc_length * sizeof( int8_t );
	int8_t *si8 __attribute__((aligned(16))) = (int8_t*)aligned_alloc( 16, alloc_size );
	if ( !si8 ) perror( "aligned_alloc() error" );

	while ( td->thread_active ) {

		p = si8;

		pc_get( &pc[ DSP_PC ], td->cycles_count );

		if ( !td->thread_active ) break;

		pthread_mutex_lock( &lock );
		evaluating_threads++;
		pthread_mutex_unlock( &lock );

		// paddb vectors of 8 8-bit signed integers at cycle
		for ( i = 0; i < td->cycles_count; i++, p += td->vector_offset ) {
			xi = *((const __m64*)p);
			xi = _mm_add_pi8( xi, ci );
			*((__m64 *)p) = xi;
		}

		pthread_mutex_lock( &lock );
		evaluating_threads--;
		pthread_cond_signal( &stop );
		pthread_mutex_unlock( &lock );

	}

	pthread_mutex_lock( &lock );
	active_threads--;
	pthread_cond_signal( &finish );
	pthread_mutex_unlock( &lock );

	if ( si8 ) free( si8 );

	return NULL;
}
#endif // __MMX__

#ifdef __SSE__
void* sse_calibrating_and_warmup_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 4;
	int64_t i;
	float *p __attribute__((aligned(16)));
	__m128 ws;
	__m128 bs = _mm_set_ps( 1.11111f, 2.22222f, 3.33333f, 4.44444f );

	sprintf( td->name, "sse_ai_bm_warmup%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	uint64_t alloc_length = ( st_bm_cpt > mt_bm_cpt ? st_bm_cpt : mt_bm_cpt ) * td->vector_offset;
	uint64_t alloc_size = alloc_length * sizeof( float );
	float *ps32 __attribute__((aligned(16))) = (float*)aligned_alloc( 16, alloc_size );
	if ( !ps32 ) perror( "aligned_alloc() error" );

	while ( td->thread_active ) {

		p = ps32;

		pc_get( &pc[ DSP_PC ], td->cycles_count );

		if ( !td->thread_active ) break;

		pthread_mutex_lock( &lock );
		evaluating_threads++;
		pthread_mutex_unlock( &lock );

		// add vectors of 4 32-bit singles at cycle
		for ( i = 0; i < td->cycles_count; i++, p += td->vector_offset ) {
			ws = _mm_load_ps( (const float *)p );
			ws = _mm_add_ps( ws, bs );
			_mm_store_ps( (float *)p, ws );
		}

		pthread_mutex_lock( &lock );
		evaluating_threads--;
		pthread_cond_signal( &stop );
		pthread_mutex_unlock( &lock );

	}

	pthread_mutex_lock( &lock );
	active_threads--;
	pthread_cond_signal( &finish );
	pthread_mutex_unlock( &lock );

	if ( ps32 ) free( ps32 );

	return NULL;
}
#endif // __SSE__

#ifdef __SSE2__
void* sse2_calibrating_and_warmup_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 16;
	int64_t i;
	int8_t *p __attribute__((aligned(16)));
	__m128i wi;
	__m128i bi = _mm_set_epi8( 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1 );

	sprintf( td->name, "sse2_ai_bm_warmup%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	uint64_t alloc_length = ( st_bm_cpt > mt_bm_cpt ? st_bm_cpt : mt_bm_cpt ) * td->vector_offset;
	uint64_t alloc_size = alloc_length * sizeof( int8_t );
	int8_t *si8 __attribute__((aligned(16))) = (int8_t*)aligned_alloc( 16, alloc_size );
	if ( !si8 ) perror( "aligned_alloc() error" );

	while ( td->thread_active ) {

		p = si8;

		pc_get( &pc[ DSP_PC ], td->cycles_count );

		if ( !td->thread_active ) break;

		pthread_mutex_lock( &lock );
		evaluating_threads++;
		pthread_mutex_unlock( &lock );

		// add vectors of 16 8-bit signed integers at cycle
		for ( i = 0; i < td->cycles_count; i++, p += td->vector_offset ) {
			wi = _mm_load_si128( (const __m128i *)p );
			wi = _mm_add_epi8( wi, bi );
			_mm_store_si128( (__m128i *)p, wi );
		}

		pthread_mutex_lock( &lock );
		evaluating_threads--;
		pthread_cond_signal( &stop );
		pthread_mutex_unlock( &lock );

	}

	pthread_mutex_lock( &lock );
	active_threads--;
	pthread_cond_signal( &finish );
	pthread_mutex_unlock( &lock );

	if ( si8 ) free( si8 );

	return NULL;
}
#endif // __SSE2__

#ifdef __SSE3__
void* sse3_calibrating_and_warmup_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 4;
	int64_t i;
	float *p __attribute__((aligned(16)));
	__m128 ws;
	__m128 bs = _mm_set_ps( 1.11111f, 2.22222f, 3.33333f, 4.44444f );

	sprintf( td->name, "sse3_ai_bm_warmup%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	uint64_t alloc_length = ( st_bm_cpt > mt_bm_cpt ? st_bm_cpt : mt_bm_cpt ) * td->vector_offset;
	uint64_t alloc_size = alloc_length * sizeof( float );
	float *ps32 __attribute__((aligned(16))) = (float*)aligned_alloc( 16, alloc_size );
	if ( !ps32 ) perror( "aligned_alloc() error" );

	while ( td->thread_active ) {

		p = ps32;

		pc_get( &pc[ DSP_PC ], td->cycles_count );

		if ( !td->thread_active ) break;

		pthread_mutex_lock( &lock );
		evaluating_threads++;
		pthread_mutex_unlock( &lock );

		// add vectors of 4 32-bit singles at cycle
		for ( i = 0; i < td->cycles_count; i++, p += td->vector_offset ) {
			ws = _mm_load_ps( (const float *)p );
			ws = _mm_addsub_ps( ws, bs );
			_mm_store_ps( (float *)p, ws );
		}

		pthread_mutex_lock( &lock );
		evaluating_threads--;
		pthread_cond_signal( &stop );
		pthread_mutex_unlock( &lock );

	}

	pthread_mutex_lock( &lock );
	active_threads--;
	pthread_cond_signal( &finish );
	pthread_mutex_unlock( &lock );

	if ( ps32 ) free( ps32 );

	return NULL;
}
#endif // __SSE3__

#ifdef __SSSE3__
void* ssse3_calibrating_and_warmup_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 16;
	int64_t i;
	int8_t *p __attribute__((aligned(16)));
	__m128i wi;
	__m128i bi = _mm_set_epi8( 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1 );

	sprintf( td->name, "ssse3_ai_bm_warmup%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	uint64_t alloc_length = ( st_bm_cpt > mt_bm_cpt ? st_bm_cpt : mt_bm_cpt ) * td->vector_offset;
	uint64_t alloc_size = alloc_length * sizeof( int8_t );
	int8_t *si8 __attribute__((aligned(16))) = (int8_t*)aligned_alloc( 16, alloc_size );
	if ( !si8 ) perror( "aligned_alloc() error" );

	while ( td->thread_active ) {

		p = si8;

		pc_get( &pc[ DSP_PC ], td->cycles_count );

		if ( !td->thread_active ) break;

		pthread_mutex_lock( &lock );
		evaluating_threads++;
		pthread_mutex_unlock( &lock );

		// add vectors of 16 8-bit signed integers at cycle
		for ( i = 0; i < td->cycles_count; i++, p += td->vector_offset ) {
			wi = _mm_load_si128( (const __m128i *)p );
			wi = _mm_sign_epi8( wi, bi );
			_mm_store_si128( (__m128i *)p, wi );
		}

		pthread_mutex_lock( &lock );
		evaluating_threads--;
		pthread_cond_signal( &stop );
		pthread_mutex_unlock( &lock );

	}

	pthread_mutex_lock( &lock );
	active_threads--;
	pthread_cond_signal( &finish );
	pthread_mutex_unlock( &lock );

	if ( si8 ) free( si8 );

	return NULL;
}
#endif // __SSSE3__

#ifdef __SSE4_1__
void* sse4_1_calibrating_and_warmup_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 4;
	int64_t i;
	float *p __attribute__((aligned(16)));
	__m128 ws;
	__m128 bs = _mm_set_ps( 1.11111f, 2.22222f, 3.33333f, 4.44444f );

	sprintf( td->name, "sse4_1_ai_bm_warmup%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	uint64_t alloc_length = ( st_bm_cpt > mt_bm_cpt ? st_bm_cpt : mt_bm_cpt ) * td->vector_offset;
	uint64_t alloc_size = alloc_length * sizeof( float );
	float *ps32 __attribute__((aligned(16))) = (float*)aligned_alloc( 16, alloc_size );
	if ( !ps32 ) perror( "aligned_alloc() error" );

	while ( td->thread_active ) {

		p = ps32;

		pc_get( &pc[ DSP_PC ], td->cycles_count );

		if ( !td->thread_active ) break;

		pthread_mutex_lock( &lock );
		evaluating_threads++;
		pthread_mutex_unlock( &lock );

		// pd vectors of 4 32-bit singles at cycle
		for ( i = 0; i < td->cycles_count; i++, p += td->vector_offset ) {
			ws = _mm_load_ps( (const float *)p );
			ws = _mm_dp_ps( ws, bs, 0x0f );
			_mm_store_ps( (float *)p, ws );
		}

		pthread_mutex_lock( &lock );
		evaluating_threads--;
		pthread_cond_signal( &stop );
		pthread_mutex_unlock( &lock );

	}

	pthread_mutex_lock( &lock );
	active_threads--;
	pthread_cond_signal( &finish );
	pthread_mutex_unlock( &lock );

	if ( ps32 ) free( ps32 );

	return NULL;
}
#endif // __SSE4_1__

#ifdef __AVX__
void* avx_calibrating_and_warmup_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 4;
	int64_t i;
	double *p __attribute__((aligned(32)));
	__m256d vd;
	__m256d ad = _mm256_set_pd( 1.11111f, 2.22222f, 3.33333f, 4.44444f );

	sprintf( td->name, "avx_ai_bm_warmup%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	uint64_t alloc_length = ( st_bm_cpt > mt_bm_cpt ? st_bm_cpt : mt_bm_cpt ) * td->vector_offset;
	uint64_t alloc_size = alloc_length * sizeof( double );
	double *pd64 __attribute__((aligned(32))) = (double*)aligned_alloc( 32, alloc_size );
	if ( !pd64 ) perror( "aligned_alloc() error" );

	while ( td->thread_active ) {

		p = pd64;

		pc_get( &pc[ DSP_PC ], td->cycles_count );

		if ( !td->thread_active ) break;

		pthread_mutex_lock( &lock );
		evaluating_threads++;
		pthread_mutex_unlock( &lock );

		// add vectors of 4 64-bit doubles at cycle
		for ( i = 0; i < td->cycles_count; i++, p += td->vector_offset ) {
			vd = _mm256_load_pd( (const double *)p );
			vd = _mm256_add_pd( vd, ad );
			_mm256_store_pd( (double *)p, vd );
		}

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
#endif // __AVX__

#ifdef __AVX2__
void* avx2_calibrating_and_warmup_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 32;
	int64_t i;
	int8_t *p __attribute__((aligned(32)));
	__m256i vi;
	__m256i ai = _mm256_set_epi8( 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1 );

	sprintf( td->name, "avx2_ai_bm_warmup%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	uint64_t alloc_length = ( st_bm_cpt > mt_bm_cpt ? st_bm_cpt : mt_bm_cpt ) * td->vector_offset;
	uint64_t alloc_size = alloc_length * sizeof( int8_t );
	int8_t *si8 __attribute__((aligned(32))) = (int8_t*)aligned_alloc( 32, alloc_size );
	if ( !si8 ) perror( "aligned_alloc() error" );

	while ( td->thread_active ) {

		p = si8;

		pc_get( &pc[ DSP_PC ], td->cycles_count );

		if ( !td->thread_active ) break;

		pthread_mutex_lock( &lock );
		evaluating_threads++;
		pthread_mutex_unlock( &lock );

		// add vectors of 32 8-bit signed integers at cycle
		for ( i = 0; i < td->cycles_count; i++, p += td->vector_offset ) {
			vi = _mm256_load_si256( (const __m256i *)p );
			vi = _mm256_add_epi8( vi, ai );
			_mm256_store_si256( (__m256i *)p, vi );
		}

		pthread_mutex_lock( &lock );
		evaluating_threads--;
		pthread_cond_signal( &stop );
		pthread_mutex_unlock( &lock );

	}

	pthread_mutex_lock( &lock );
	active_threads--;
	pthread_cond_signal( &finish );
	pthread_mutex_unlock( &lock );

	if ( si8 ) free( si8 );

	return NULL;
}
#endif // __AVX2__

#ifdef __FMA__
void* fma3_calibrating_and_warmup_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 8;
	int64_t i;
	float *p __attribute__((aligned(32)));
	__m256 vs;
	__m256 as = _mm256_set_ps( 1.11111f, 2.22222f, 3.33333f, 4.44444f, 5.55555f, 6.66666f, 7.77777f, 8.88888f );
	__m256 ys = _mm256_set_ps( 5.55555f, 6.66666f, 7.77777f, 8.88888f, 1.11111f, 2.22222f, 3.33333f, 4.44444f );

	sprintf( td->name, "fma3_ai_bm_warmup%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	uint64_t alloc_length = ( st_bm_cpt > mt_bm_cpt ? st_bm_cpt : mt_bm_cpt ) * td->vector_offset;
	uint64_t alloc_size = alloc_length * sizeof( float );
	float *ps32 __attribute__((aligned(32))) = (float*)aligned_alloc( 32, alloc_size );
	if ( !ps32 ) perror( "aligned_alloc() error" );

	while ( td->thread_active ) {

		p = ps32;

		pc_get( &pc[ DSP_PC ], td->cycles_count );

		if ( !td->thread_active ) break;

		pthread_mutex_lock( &lock );
		evaluating_threads++;
		pthread_mutex_unlock( &lock );

		// vfmadd132ps vectors of 8 32-bit singles at cycle
		for ( i = 0; i < td->cycles_count; i++, p += td->vector_offset ) {
			vs = _mm256_load_ps( (const float *)p );
			vs = _mm256_fmadd_ps( vs, as, ys );
			_mm256_store_ps( (float *)p, vs );
		}

		pthread_mutex_lock( &lock );
		evaluating_threads--;
		pthread_cond_signal( &stop );
		pthread_mutex_unlock( &lock );

	}

	pthread_mutex_lock( &lock );
	active_threads--;
	pthread_cond_signal( &finish );
	pthread_mutex_unlock( &lock );

	if ( ps32 ) free( ps32 );

	return NULL;
}
#endif // __FMA__

inline void make_cpu_warmup( uint16_t th_cnt, instructions_e instr ) {
	double best_total_time = 1000.0;

	fprintf( stdout, BLUE "\t   cpu, cache, memory calibrating & warming up for %s instructions (%d thread(s)) ... " OFF, instructions_s[ instr ], th_cnt ); fflush( stdout );
	fprintf( stream, "\t   cpu, cache, memory calibrating & warming up for %s instructions (%d thread(s)) ... ", instructions_s[ instr ], th_cnt );

	if ( th_cnt >> 1 ) {
		mt_bm_cpt = 128;
		best_cpt = mt_bm_cpt;
	} else {
		st_bm_cpt = 128;
		best_cpt = st_bm_cpt;
	}

	for ( int32_t i = 0; i < 14; i++ ) {

		switch ( instr ) {
			case _MMX_:
#ifdef __MMX__
				bmu_threads( th_cnt, 1, NULL, &mmx_calibrating_and_warmup_thread, NULL );
#endif // __MMX__
				break;
			case _SSE_:
#ifdef __SSE__
				bmu_threads( th_cnt, 1, NULL, &sse_calibrating_and_warmup_thread, NULL );
#endif // __SSE__
				break;
			case _SSE2_:
#ifdef __SSE2__
				bmu_threads( th_cnt, 1, NULL, &sse2_calibrating_and_warmup_thread, NULL );
#endif // __SSE2__
				break;
			case _SSE3_:
#ifdef __SSE3__
				bmu_threads( th_cnt, 1, NULL, &sse3_calibrating_and_warmup_thread, NULL );
#endif // __SSE3__
				break;
			case _SSSE3_:
#ifdef __SSSE3__
				bmu_threads( th_cnt, 1, NULL, &ssse3_calibrating_and_warmup_thread, NULL );
#endif // __SSSE3__
				break;
			case _SSE4_1_:
#ifdef __SSE4_1__
				bmu_threads( th_cnt, 1, NULL, &sse4_1_calibrating_and_warmup_thread, NULL );
#endif // __SSE4_1__
				break;
			case _AVX_:
#ifdef __AVX__
				bmu_threads( th_cnt, 1, NULL, &avx_calibrating_and_warmup_thread, NULL );
#endif // __AVX__
				break;
			case _AVX2_:
#ifdef __AVX2__
				bmu_threads( th_cnt, 1, NULL, &avx2_calibrating_and_warmup_thread, NULL );
#endif // __AVX2__
				break;
			case _FMA3_:
#ifdef __FMA__
				bmu_threads( th_cnt, 1, NULL, &fma3_calibrating_and_warmup_thread, NULL );
#endif // __FMA__
				break;
		}

		if ( th_cnt >> 1 ) {
			if (best_total_time > total_time) { best_total_time = total_time; best_cpt = mt_bm_cpt; }
			mt_bm_cpt <<= 1;
		} else {
			if (best_total_time > total_time) { best_total_time = total_time; best_cpt = st_bm_cpt; }
			st_bm_cpt <<= 1;
		}
	}

	if ( th_cnt >> 1 ) {
		mt_bm_cpt = best_cpt;
		printf( BLUE "mt_bm_cpt = %u choosed, calibration done." OFF "\n\n", mt_bm_cpt );
		fprintf( stream, "mt_bm_cpt = %u choosed, calibration done.\n\n", mt_bm_cpt );
	} else {
		st_bm_cpt = best_cpt;
		printf( BLUE "st_bm_cpt = %u choosed, calibration done." OFF "\n\n", st_bm_cpt );
		fprintf( stream, "st_bm_cpt = %u choosed, calibration done.\n\n", st_bm_cpt );
	}

	return;
}

#endif // !__CPU_WARM_UP_THREAD_H__