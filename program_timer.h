#ifndef __PROGRAM_TIMER_H__
#define __PROGRAM_TIMER_H__

class Program_timer
{
	public:
	Program_timer();
	~Program_timer();
	void Start();
	void Stop();
	void Check();
	private:
		enum Status
		{
			Status_timer_off,
			Status_timer_runs,
			Status_timer_hold,
			Status_timer_finished
		};
		uint32_t ticks;	
};

#endif //__PROGRAM_TIMER_H__