#ifndef __PRODUCER_CONSUMER_H__
#define __PRODUCER_CONSUMER_H__

#define PC_STATE_ACTIVE 0
#define PC_STATE_STOP   1

// Буфер по классической схеме "поставщик-потребитель"
pthread_mutex_t	pc_lock;	// мутекс обеспечивающий ексклюзивный доступ к буферу
pthread_cond_t	pc_notempty;	// сигнал состояния - буфер непуст
pthread_cond_t	pc_notfull;	// сигнал состояния - буфер неполон
int32_t 	pc_readpos;	// индекс чтения из буфера
int32_t 	pc_writepos;	// индекс запсиси в буфер
int32_t 	pc_num;		// колличество блоков буфера
int32_t		pc_state;	// текущее состояние буфера
int32_t		pc_r_state;	// текущее состояние чтения из буфера
int32_t		pc_w_state;	// текущее состояние записи в буфер
uint64_t 	*cycles;	// массив из продконс-буферов

// Конструктор класса
inline void pc_init( int32_t n ) {
	if ( n <= 0 ) perror("pc_init(): error, buffer's number less or equal 0\n");
	pthread_mutex_init( &pc_lock, NULL );
	pthread_cond_init( &pc_notempty, NULL );
	pthread_cond_init( &pc_notfull, NULL );
	pc_readpos = 0;
	pc_writepos = 0;
	pc_num = n;
	cycles = (uint64_t*)malloc( pc_num * sizeof(uint64_t) );
	if ( !cycles ) perror("pc_init(): malloc() error\n");
	pc_state = PC_STATE_ACTIVE;
	pc_r_state = PC_STATE_ACTIVE;
	pc_w_state = PC_STATE_ACTIVE;
	return;
}

// Функция останова буфера
inline void pc_stop() {
	pc_state = PC_STATE_STOP;
	pthread_cond_broadcast(&pc_notempty);
	pthread_cond_broadcast(&pc_notfull);
	return;
}

// Деструктор класса
inline void pc_finit() {
	pc_stop();
	free( cycles );
	return;
}

// Функция записи нового буфера
inline void pc_put( uint64_t _cycles_ ) {
	if (pc_w_state == PC_STATE_STOP) return;
	pthread_mutex_lock(&pc_lock);
	while (((pc_writepos + 1) % pc_num == pc_readpos) && (pc_state != PC_STATE_STOP))
		pthread_cond_wait(&pc_notfull, &pc_lock);
	if (pc_state == PC_STATE_STOP)
		pc_w_state = PC_STATE_STOP;
	cycles[ pc_writepos ] = _cycles_;
	pc_writepos++;
	if (pc_writepos >= pc_num)
		pc_writepos = 0;
	pthread_cond_broadcast(&pc_notempty);
	pthread_mutex_unlock(&pc_lock);
	return;
}

// Функция чтения очередного буфера
inline void pc_get( uint64_t &_cycles_ ) {
	if (pc_r_state == PC_STATE_STOP) { _cycles_ = 0; return; }
	pthread_mutex_lock(&pc_lock);
	while ((pc_writepos == pc_readpos) && (pc_state != PC_STATE_STOP))
		pthread_cond_wait(&pc_notempty, &pc_lock);
	if (pc_state == PC_STATE_STOP)
		pc_r_state = PC_STATE_STOP;
	_cycles_ = cycles[ pc_readpos ];
	pc_readpos++;
	if (pc_readpos >= pc_num)
		pc_readpos = 0;
	pthread_cond_signal(&pc_notfull);
	pthread_mutex_unlock(&pc_lock);
	return;
}

// Функция подсчёта занятых буферов
inline int32_t pc_count() { return (pc_writepos - pc_readpos + pc_num) % pc_num; }

#endif // !__PRODUCER_CONSUMER_H__