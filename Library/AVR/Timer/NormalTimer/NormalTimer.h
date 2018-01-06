
#pragma once

typedef enum
{
	TIMER_NUM_0 = 0,
	TIMER_NUM_1 = 1,
	TIMER_NUM_2 = 2,
	TIMER_NUM_3 = 3,
	TIMER_NUM_4 = 4
}
TimerNum;

typedef DataBit16 uSecond;

//Timer0
namespace ShortTimer
{

void Initialize();

void Set_counter(Clock _clock, CountValue _count_value);

void Set_counter_us(uSecond _time_us);

void Set_counter_ms(mSecond _time_ms);

void Start();

void Start(Clock _clock, CountValue _count_value);

YesNo Is_count_finshed();

void Stop();

};

//Timer1
namespace LongTimer
{

void Set(Clock );

void Start();

void Start(Clock , CountValue );

void Stop();

};
