#include "TimeUtils.hpp"
#include <ace/Date_Time.h> 

using namespace std;

namespace time_utils
{
#ifdef ENABLE_SCOPED_TIMER

ScopedTimer::ScopedTimer(const string &name) : name_(name) 
{
	init_time_ = ACE_OS::gettimeofday();
}

ScopedTimer::~ScopedTimer() 
{
	destroy_time_ = ACE_OS::gettimeofday();
	ACE_Time_Value diff = destroy_time_ - init_time_;
	printf("[ScopedTimer: %s Time: %ld.%03ldms]\n",
				name_.c_str(),
				diff.sec() * 1000 + diff.usec() / 1000,
				diff.usec() % 1000);
}

#else // ENABLE_SCOPED_TIMER

ScopedTimer::ScopedTimer(const string &) 
{}

#endif // ENABLE_SCOPED_TIME

TimeStat::TimeStat() 
{
	new (this)TimeStat("TimeStat");
}
TimeStat::TimeStat(const string &name) : name_(name) 
{
	start();
}
TimeStat::~TimeStat() 
{}

void TimeStat::start()
{
	start_ = ACE_OS::gettimeofday();
	checkport_ = start_;
	end_ = start_;
	diff_ = 0;
}

void TimeStat::updateCheckpoint() 
{
	ACE_Time_Value tv = ACE_OS::gettimeofday();
	diff_ = tv - checkport_;
	checkport_ = tv;
}
void TimeStat::finish() 
{
	end_ = ACE_OS::gettimeofday();
	diff_ = end_ - start_;
}

void TimeStat::printDiff() 
{
	printf("[TimeStat: %s Time: %ld.%03ldms]\n",
				name_.c_str(),
				diff_.sec() * 1000 + diff_.usec() / 1000,
				diff_.usec() % 1000);
}

const string& TimeStat::diffToString()
{
	char buf[512];
	snprintf(buf, 512, "[TimeStat: %s Time: %ld.%03ldms]\n",
				name_.c_str(),
				diff_.sec() * 1000 + diff_.usec() / 1000,
				diff_.usec() % 1000);
	return buf;
}

}; 	// end namespace time_utils
