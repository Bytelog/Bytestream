#include "logging.h"

#define _GNU_SOURCE
#include <errno.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum {
	LEVEL_DEBUG = (1 << 0),
	LEVEL_INFO  = (1 << 1),
	LEVEL_WARN  = (1 << 2),
	LEVEL_ERROR = (1 << 3),
	LEVEL_ERRNO = (1 << 4)
} log_level_t;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static inline void log_timestring(char *buffer, size_t length) {
	time_t raw_time;
	struct tm *local_time;

	time(&raw_time);
	local_time = localtime(&raw_time);
	strftime(buffer, length, "%T", local_time);
}

static inline void log_severity(log_level_t level, char *buffer, size_t len) {
	switch (level) {
		case LEVEL_DEBUG:
			strncpy(buffer, "DEBUG: ", len);
			break;
		case LEVEL_INFO:
			strncpy(buffer, "INFO: ", len);
			break;
		case LEVEL_WARN:
			strncpy(buffer, "WARN: ", len);
			break;
		case LEVEL_ERROR:
			strncpy(buffer, "ERROR: ", len);
			break;
		default:
			strncpy(buffer, "", len);
	}
}

#ifndef DEBUG
static void log_write(log_level_t level, const char *fmt, va_list values)
#else
static void log_write(const char *file, const char *function, int line,
	log_level_t level, const char *fmt, va_list values)
#endif
{
	int error_number = errno;

	if (pthread_mutex_lock(&mutex) < 0)
		perror("pthread_mutex_lock");

	FILE *stream = stdout;
	if (level & LEVEL_WARN || level & LEVEL_ERROR)
		stream = stderr;

	char *message = 0;
	if (vasprintf(&message, fmt, values) < 0)
		perror("sprintf failed");

	char timestamp[40] = {0};
	log_timestring(timestamp, sizeof(timestamp) - 1);

	char *error = "";
	if (level & LEVEL_ERRNO) {
		char buffer[128] = {0};
		error = strerror_r(error_number, buffer, sizeof(buffer) - 1);
	}

	char severity[16];
	log_severity(level, severity, sizeof(severity) - 1);

	fprintf(stream, "[%s] %s%s %s\n", timestamp, severity, message, error);

	if (pthread_mutex_unlock(&mutex) < 0)
		perror("pthread_mutex_unlock");

	free(message);
}

#ifndef DEBUG
#define CREATE_FUNCTION(function, level)															\
	void log_##function(const char *fmt, ...)  {													\
		va_list values;																				\
		va_start(values, fmt);																		\
		log_write(level, fmt, values);																\
		va_end(values);																				\
		if ((level) & LEVEL_ERROR) exit(1);															\
	}
#else
#define CREATE_FUNCTION(function, level)															\
	void log_##function##_debug(const char *file, const char *func, int line,						\
								const char *fmt, ...) {												\
		va_list values;																				\
		va_start(values, fmt);																		\
		log_write(file, func, line, level, fmt, values);											\
		va_end(values);																				\
		if ((level) & LEVEL_ERROR) abort();															\
	}

CREATE_FUNCTION(debug, LEVEL_DEBUG)
#endif

CREATE_FUNCTION(info, LEVEL_INFO)
CREATE_FUNCTION(warn, LEVEL_WARN)
CREATE_FUNCTION(pwarn, LEVEL_WARN | LEVEL_ERRNO)
CREATE_FUNCTION(error, LEVEL_ERROR)
CREATE_FUNCTION(perror, LEVEL_ERROR | LEVEL_ERRNO)

#undef CREATE_FUNCTION
