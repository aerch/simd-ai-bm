#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

inline __m64 _mm_load_si64( const __m64 *v ) {
	static __m64 tmp;
	memcpy( &tmp, v, sizeof(__m64) );
	return tmp;
}

inline void _mm_store_si64( __m64 *d, const __m64 v ) {
	memcpy( d, &v, sizeof(__m64) );
	return;
}

#endif // !__FUNCTIONS_H__