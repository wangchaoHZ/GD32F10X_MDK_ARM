/**
MIT License

Copyright (c) 2019 R. Dunbar Poor <rdpoor@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * \file
 *
 * \brief uLog: lightweight logging for embedded systems
 *
 *     // To use uLog, you must define a function to process logging messages.
 *     // It can write the messages to a console, to a file, to an in-memory
 *     // buffer: the choice is yours.  And you get to choose the format of
 *     // the message.  This example prints to the console.  One caveat: msg
 *     // is a static string and will be over-written at the next call to ULOG.
 *     // You may print it or copy it, but saving a pointer to it will lead to
 *     // confusion and astonishment.
 *     //
 */

#ifndef ULOG_H_
#define ULOG_H_

#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum
    {
        ULOG_TRACE_LEVEL = 100,
        ULOG_DEBUG_LEVEL,
        ULOG_INFO_LEVEL,
        ULOG_WARNING_LEVEL,
        ULOG_ERROR_LEVEL,
        ULOG_CRITICAL_LEVEL,
        ULOG_ALWAYS_LEVEL
    } ulog_level_t;

// The following macros enable or disable uLog.  If `ULOG_ENABLED` is
// defined at compile time, a macro such as `ulog_info(...)` expands
// into `ulog_message(ulog_info_LEVEL, ...)`.  If `ULOG_ENABLED` is not
// defined, then the same macro expands into `do {} while(0)` and will
// not generate any code at all.
//
// There are two ways to enable uLog: you can uncomment the following
// line, or -- if it is commented out -- you can add -DULOG_ENABLED to
// your compiler switches.
#define ULOG_ENABLED

#ifdef ULOG_ENABLED
#define ulog(...) ulog_message(__VA_ARGS__)
#define ulog_trace(...) ulog_message(ULOG_TRACE_LEVEL, __VA_ARGS__)
#define ulog_debug(...) ulog_message(ULOG_DEBUG_LEVEL, __VA_ARGS__)
#define ulog_info(...) ulog_message(ULOG_INFO_LEVEL, __VA_ARGS__)
#define ulog_warning(...) ulog_message(ULOG_WARNING_LEVEL, __VA_ARGS__)
#define ulog_error(...) ulog_message(ULOG_ERROR_LEVEL, __VA_ARGS__)
#define ulog_critical(...) ulog_message(ULOG_CRITICAL_LEVEL, __VA_ARGS__)
#define ulog_always(...) ulog_message(ULOG_ALWAYS_LEVEL, __VA_ARGS__)
#else
// uLog vanishes when disabled at compile time...
#define ulog_init() \
    do              \
    {               \
    } while (0)
#define ulog_subscribe(a, b) \
    do                       \
    {                        \
    } while (0)
#define ulog_unsubscribe(a) \
    do                      \
    {                       \
    } while (0)
#define ulog_level_name(a) \
    do                     \
    {                      \
    } while (0)
#define ulog(s, f, ...) \
    do                  \
    {                   \
    } while (0)
#define ulog_trace(f, ...) \
    do                     \
    {                      \
    } while (0)
#define ulog_debug(f, ...) \
    do                     \
    {                      \
    } while (0)
#define ulog_info(f, ...) \
    do                    \
    {                     \
    } while (0)
#define ulog_warning(f, ...) \
    do                       \
    {                        \
    } while (0)
#define ulog_error(f, ...) \
    do                     \
    {                      \
    } while (0)
#define ulog_critical(f, ...) \
    do                        \
    {                         \
    } while (0)
#define ulog_always(f, ...) \
    do                      \
    {                       \
    } while (0)
#endif

    typedef enum
    {
        ULOG_ERR_NONE = 0,
        ULOG_ERR_SUBSCRIBERS_EXCEEDED,
        ULOG_ERR_NOT_SUBSCRIBED,
    } ulog_err_t;

// define the maximum number of concurrent subscribers
#ifndef ULOG_MAX_SUBSCRIBERS
#define ULOG_MAX_SUBSCRIBERS 6
#endif
// maximum length of formatted log message
#ifndef ULOG_MAX_MESSAGE_LENGTH
#define ULOG_MAX_MESSAGE_LENGTH 120
#endif
    /**
     * @brief: prototype for uLog subscribers.
     */
    typedef void (*ulog_function_t)(ulog_level_t severity, char *msg);

    void ulog_init(void);
    ulog_err_t ulog_subscribe(ulog_function_t fn, ulog_level_t threshold);
    ulog_err_t ulog_unsubscribe(ulog_function_t fn);
    const char *ulog_level_name(ulog_level_t level);
    void ulog_message(ulog_level_t severity, const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* ULOG_H_ */
