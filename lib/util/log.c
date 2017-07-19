#include "log.h"

#include <errno.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sds/sds.h>

typedef enum {
    LEVEL_DEBUG = (1 << 0),
    LEVEL_INFO  = (1 << 1),
    LEVEL_WARN  = (1 << 2),
    LEVEL_ERROR = (1 << 3),
    LEVEL_ERRNO = (1 << 4)
} log_level_t;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Get log severity as a string
static inline char *log_severity(log_level_t level) {
    if (level & LEVEL_DEBUG)
        return "DEBUG";
    else if (level & LEVEL_INFO)
        return "INFO";
    else if (level & LEVEL_WARN)
        return "WARN";
    else if (level & LEVEL_ERROR)
        return "ERROR";
    else
        return "";
}

#ifndef DEBUG
static void log_write(log_level_t level, const char *fmt, va_list values)
#else
static void log_write(const char *file, const char *function, int line,
    log_level_t level, const char *fmt, va_list values)
#endif
{
    FILE *stream = stdout;
    int error_number = errno;
    char timestamp[9];
    time_t raw_time;
    sds message = sdsempty();

    if (level & LEVEL_WARN || level & LEVEL_ERROR)
        stream = stderr;

    // Mutex lock required for localtime & strerror
    pthread_mutex_lock(&mutex);

    // Get time in HH:MM:SS format
    time(&raw_time);
    strftime(timestamp, sizeof(timestamp), "%T", localtime(&raw_time));

    message = sdscatfmt(message, "[%s]", timestamp);
    message = sdscatfmt(message, " %s: ", log_severity(level));
    message = sdscatvprintf(message, fmt, values);

    // For p- functions, get the message attached to ERRNO
    if (level & LEVEL_ERRNO)
        message = sdscatfmt(message, " (%s)", strerror(error_number));

    #ifdef DEBUG
    message = sdscatfmt(message, " %s:%s:%i", file, function, line);
    #endif

    message = sdscat(message, "\n");
    fwrite(message, sizeof(char), sdslen(message), stream);

    pthread_mutex_unlock(&mutex);
    sdsfree(message);
}

#ifndef DEBUG
#define CREATE_FUNCTION(function, level)                                       \
    void log_##function(const char *fmt, ...)  {                               \
        va_list values;                                                        \
        va_start(values, fmt);                                                 \
        log_write(level, fmt, values);                                         \
        va_end(values);                                                        \
        if ((level) & LEVEL_ERROR) exit(1);                                    \
    }
#else
#define CREATE_FUNCTION(function, level)                                       \
    void log_##function##_debug(const char *file, const char *func, int line,  \
                                const char *fmt, ...) {                        \
        va_list values;                                                        \
        va_start(values, fmt);                                                 \
        log_write(file, func, line, level, fmt, values);                       \
        va_end(values);                                                        \
        if ((level) & LEVEL_ERROR) abort();                                    \
    }

CREATE_FUNCTION(debug, LEVEL_DEBUG)
#endif

CREATE_FUNCTION(info, LEVEL_INFO)
CREATE_FUNCTION(warn, LEVEL_WARN)
CREATE_FUNCTION(pwarn, (log_level_t) (LEVEL_WARN | LEVEL_ERRNO))
CREATE_FUNCTION(error, LEVEL_ERROR)
CREATE_FUNCTION(perror, (log_level_t) (LEVEL_ERROR | LEVEL_ERRNO))

#undef CREATE_FUNCTION
