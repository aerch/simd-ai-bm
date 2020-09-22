#ifndef __PRODUCER_CONSUMER_H__
#define __PRODUCER_CONSUMER_H__

/// Структура данных продконс-буфера
typedef struct th_data {
	uint64_t	xlen;		///< длина буфера x
} th_data_t;

#define PC_STATE_ACTIVE 0
#define PC_STATE_STOP   1

/// Класс буфера по классической схеме "поставщик-потребитель"
class prodcons {
private:
	pthread_mutex_t	lock;		///< мутекс обеспечивающий ексклюзивный доступ к буферу
	pthread_cond_t	notempty;	///< сигнал состояния - буфер непуст
	pthread_cond_t	notfull;	///< сигнал состояния - буфер неполон
	int32_t 	readpos;	///< индекс чтения из буфера
	int32_t 	writepos;	///< индекс запсиси в буфер
	int32_t 	num;		///< колличество блоков буфера
	int32_t		state;		///< текущее состояние буфера
	int32_t		r_state;	///< текущее состояние чтения из буфера
	int32_t		w_state;	///< текущее состояние записи в буфер

public:
	th_data_t **td;			///< массив из продконс-буферов

	/// Конструктор класса
	prodcons( int32_t n ) {
		if ( n <= 0 ) printf("ProdCons ERROR: class has incorrect input values at %s:%i\n", __FILE__, __LINE__);
		pthread_mutex_init( &lock, NULL );
		pthread_cond_init( &notempty, NULL );
		pthread_cond_init( &notfull, NULL );
		readpos = 0;
		writepos = 0;
		num = n;
		td = (th_data_t**)malloc( num * sizeof(th_data_t*) );
		if ( !td ) printf("ProdCons ERROR: dynamic memory allocation ( %lu bytes ) error: at %s:%i\n", num * sizeof(th_data_t*), __FILE__, __LINE__);
		for ( int32_t i = 0; i < num; i++ ) {
			td[ i ] = (th_data_t*)malloc( sizeof(th_data_t) );
			if ( !td[ i ] ) printf("ProdCons ERROR: dynamic memory allocation ( %lu bytes ) error: at %s:%i\n", sizeof(th_data_t), __FILE__, __LINE__);
			td[ i ]->xlen = 0;
		}
		state = PC_STATE_ACTIVE;
		r_state = PC_STATE_ACTIVE;
		w_state = PC_STATE_ACTIVE;
		return;
	};

	/// Функция останова буфера
	void stop() {
		// printf("ProdCons: stopping ...\n");
		state = PC_STATE_STOP;
		pthread_cond_broadcast(&notempty);
		pthread_cond_broadcast(&notfull);
		return;
	};

	/// Деструктор класса
	~prodcons() {
		stop();
		for ( int32_t i = 0; i < num; i++ )
			free( td[ i ] );
		free( td ); td = NULL;
		// printf("ProdCons: stopped.\n");
		return;
	};

	/// Функция получения индекса следующего буфера
	int32_t get() {
		if (w_state == PC_STATE_STOP) return 0;
		pthread_mutex_lock(&lock);
		while (((writepos + 1) % num == readpos) && (state != PC_STATE_STOP))
			pthread_cond_wait(&notfull, &lock);
		if (state == PC_STATE_STOP)
			w_state = PC_STATE_STOP;
		int32_t index = writepos;
		writepos++;
		if (writepos >= num)
			writepos = 0;
		pthread_cond_signal(&notempty);
		pthread_mutex_unlock(&lock);
		return index;
	};

	/// Функция освобождения очередного занятого буфера
	void put() {
		if (r_state == PC_STATE_STOP) return;
		pthread_mutex_lock(&lock);
		while ((writepos == readpos) && (state != PC_STATE_STOP))
			pthread_cond_wait(&notempty, &lock);
		if (state == PC_STATE_STOP)
			r_state = PC_STATE_STOP;
		readpos++;
		if (readpos >= num)
			readpos = 0;
		pthread_cond_signal(&notfull);
		pthread_mutex_unlock(&lock);
		return;
	};

	/// Функция записи нового буфера
	void write( uint64_t buf_len ) {
		if (w_state == PC_STATE_STOP) return;
		pthread_mutex_lock(&lock);
		while (((writepos + 1) % num == readpos) && (state != PC_STATE_STOP))
			pthread_cond_wait(&notfull, &lock);
		if (state == PC_STATE_STOP)
			w_state = PC_STATE_STOP;
		td[ writepos ]->xlen = buf_len;
		writepos++;
		if (writepos >= num)
			writepos = 0;
		pthread_cond_broadcast(&notempty);
		pthread_mutex_unlock(&lock);
		return;
	};

	/// Функция чтения очередного буфера
	void read( uint64_t &buf_len ) {
		if (r_state == PC_STATE_STOP) { buf_len = 0; return; }
		pthread_mutex_lock(&lock);
		while ((writepos == readpos) && (state != PC_STATE_STOP))
			pthread_cond_wait(&notempty, &lock);
		if (state == PC_STATE_STOP)
			r_state = PC_STATE_STOP;
		buf_len = td[ readpos ]->xlen;
		readpos++;
		if (readpos >= num)
			readpos = 0;
		pthread_cond_broadcast(&notfull);
		pthread_mutex_unlock(&lock);
		return;
	};

	/// Функция подсчёта занятых буферов
	int32_t count() { return (writepos - readpos + num) % num; };

};

#endif // !__PRODUCER_CONSUMER_H__