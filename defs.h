
#define BLACK		"\033[30;1m"
#define BGBLACK		"\033[37;1;40m"
#define RED		"\033[31;1m"
#define BGRED		"\033[37;1;41m"
#define GREEN		"\033[32;1m"
#define BGGREEN		"\033[37;1;42m"
#define YELLOW		"\033[33;1m"
#define BGYELLOW	"\033[30;1;43m"
#define BLUE		"\033[34;1m"
#define BGBLUE		"\033[37;1;44m"
#define PURPLE		"\033[35;1m"
#define BGPURPLE	"\033[37;1;45m"
#define CYAN		"\033[36;1m"
#define BGCYAN		"\033[37;1;46m"
#define WHITE		"\033[37;1m"
#define THINW		"\033[38;1m"
#define WHITE_		"\033[39;1m"
#define BBLACK		"\033[40;1m"
#define BRED		"\033[41;1m"
#define BGREEN		"\033[42;1m"
#define BYELLOW		"\033[43;1m"
#define BBLUE		"\033[44;1m"
#define BPURPLE		"\033[45;1m"
#define BCYAN		"\033[46;1m"
#define BWHITE		"\033[47;1m"
#define BTHINW		"\033[48;1m"
#define BWHITE_		"\033[49;1m"
#define OFF		"\033[0m"

#define ALIGN32 __attribute__((aligned(32)))	// to simplify the alignment declaration on variables

double 		diff;
struct timespec t1, t2;
#define _BMARK_ON_ clock_gettime(CLOCK_REALTIME, &t1);
#define _BMARK_OFF(cycle) clock_gettime(CLOCK_REALTIME, &t2); \
	diff = (double)((double)t2.tv_sec + (double)t2.tv_nsec/1.0e9) - ((double)t1.tv_sec + (double)t1.tv_nsec/1.0e9); \
	cycle = (double)diff;

#define _BIT(b) (1<<(b))					///< битовый сдвиг влево на b позиций
#define TEST(n,b) (((n)&_BIT(b))!=0)				///< проверка, что b-ый бит числа n - ненулевой
#define SET_BIT(n,b,value) (n) ^= ((-value)^(n)) & (_BIT(b))	///< установка бита из позиции n в позицию b числа value
#define CHECK(n,b) (((n)&_BIT(b))!=0)				///< проверка, что b-ый бит числа n - ненулевой

int32_t		result;
FILE		*stream;
char		_str_[ 1024 ];
char		current_path[ PATH_MAX ];

const uint64_t	cycles_count = 1000000000;	// 1,000,000,000 - 10,000,000,000

double		total_time = 0.0;
double		total_tps;

__m256i		a, v;
__uint128_t	active_threads_flag;
pthread_mutex_t	lock;
pthread_cond_t	start;
pthread_cond_t	stop;

