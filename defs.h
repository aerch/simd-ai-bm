
#define ALIGN __attribute__((aligned(32)))	// to simplify the alignment declaration on variables

double diff;
struct timespec t1, t2;
#define _BMARK_ON_ clock_gettime(CLOCK_REALTIME, &t1);
#define _BMARK_OFF(cycle) clock_gettime(CLOCK_REALTIME, &t2); \
	diff = (double)((double)t2.tv_sec + (double)t2.tv_nsec/1.0e9) - ((double)t1.tv_sec + (double)t1.tv_nsec/1.0e9); \
	cycle = (double)diff;

FILE *stream;
char _str_[ 1024 ];
char current_path[ PATH_MAX ];

const uint64_t cycles_count = 500000000; // 2,000,000,000 - 10,000,000,000

double total_time = 0.0;
double total_tps = 0.0;

__m256i a, v;
