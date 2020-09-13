
#define ALIGN __attribute__((aligned(32)))	// to simplify the alignment declaration on variables

int64_t _s, _ns;
struct timespec t1, t2;
#define _BMARK_ON_ clock_gettime(CLOCK_REALTIME, &t1);
#define _BMARK_OFF(cycle) clock_gettime(CLOCK_REALTIME, &t2); \
	_ns  = ((int64_t)(t2.tv_nsec - t1.tv_nsec + 1e9))%1000000000; \
	_s   = ((int64_t)(t2.tv_sec + t2.tv_nsec/1e9) - (t1.tv_sec + t1.tv_nsec/1e9)); \
	cycle = (double)( _s + _ns / 1.0e9f );
