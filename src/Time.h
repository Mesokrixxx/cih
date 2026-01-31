#ifndef TIME_H
# define TIME_H

# include <stdint.h>

typedef uint64_t Time;

# define SEC_TO_NS(_s) ((_s) * 1000000000.0)
# define NS_TO_SEC(_ns) ((_ns) / 1000000000.0)

// Return elapsed time in ns since the very first call of time_now()
Time time_now(void);

#endif // TIME_H
