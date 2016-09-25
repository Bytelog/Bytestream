#pragma once

#ifndef DEBUG
#define CREATE_LOG_PROTOTYPE(level_, ...)															\
	void log_##level_(const char *fmt, ...)															\
							__attribute__((format(printf, 1, 2)))									\
							__VA_ARGS__;

#define log_debug(fmt, ...)
#else
#define CREATE_LOG_PROTOTYPE(level_, ...)															\
	void log_##level_##_debug(const char *file, const char *fun, int line, const char *fmt, ...)	\
							__attribute__((format(printf, 4, 5)))									\
							__VA_ARGS__

#define log_debug(fmt, ...)																			\
	log_debug_debug(__FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define log_info(fmt, ...)																			\
	log_info_debug(__FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define log_pwarn(fmt, ...)																			\
	log_warn_debug(__FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define log_perror(fmt, ...)																		\
	log_pwarn_debug(__FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define log_error(fmt, ...)																			\
	log_error_debug(__FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define log_perror(fmt, ...)																		\
	log_perror_debug(__FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)

CREATE_LOG_PROTOTYPE(debug)
#endif

CREATE_LOG_PROTOTYPE(info, __attribute__((unused)))
CREATE_LOG_PROTOTYPE(warn, __attribute__((unused)))
CREATE_LOG_PROTOTYPE(pwarn, __attribute__((unused)))
CREATE_LOG_PROTOTYPE(error, __attribute__((noreturn)))
CREATE_LOG_PROTOTYPE(perror, __attribute__((noreturn)))

#undef CREATE_LOG_PROTOTYPE
