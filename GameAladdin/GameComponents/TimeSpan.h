#ifndef __TIMESPAN_H__
#define	__TIMESPAN_H__

#include "define.h"
#include <windows.h>

class TimeSpan
{
public:
	static const UINT64 TicksPerSecond = 10000000;
	static const UINT64 TicksPerMilisecond = 10000;

	TimeSpan(void);
	TimeSpan(UINT64);

	float		getMiliSeconds();
	UINT64	getTicks();

	~TimeSpan(void);

	TimeSpan operator + (TimeSpan);
	TimeSpan operator + (UINT64);

private:
	UINT64 _ticks;
};

#endif // !__TIMESPAN_H__


