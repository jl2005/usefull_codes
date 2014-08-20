#pragma once

#include <string>
#include <vector>
#include <ostream>
#include <boost/utility.hpp>
#include <ace/Time_Value.h>

namespace time_utils
{
#ifdef ENABLE_SCOPED_TIMER
//启用局部时间统计
class ScopedTimer : boost::noncopyable {
public:
	ScopedTimer(const std::string &name);
	~ScopedTimer();

private:
	std::string name_;
	ACE_Time_Value init_time_, destroy_time_;
};
#define SCOPED_TIMER(name) time_utils::ScopedTimer scoped_timer_ ## __func__ ## __LINE__(name)

#else // not ENABLE_SCOPED_TIMER
//关闭局部时间统计
class ScopedTimer : boost::noncopyable {
public:
	ScopedTimer(const std::string &);
};
#define SCOPED_TIMER(name) (void)0

#endif // ENABLE_SCOPED_TIME

/**
 * 通用时间统计类
 * 提供两种时间统计方法：
 * 1. 统计从start到finish的时间;
 * 2. 统计两个时间检查点之间的时间
 * 使用样例:
 * TimeState ts;
 * ts.start(); //设置起始时间和起始检查点，构造函数中也会调用start
 * ......code 1......
 * ts.updateCheckpoint(); //更新时间检查点，同时将从上一次
 * 						  //时间检查点到当前检查点所用的时间存入diff,
 *						  //此处为code 1所花费的时间
 * ts.printDiff(); 		  //输出diff的时间
 * ......code 2......
 * ts.updateCheckpoint(); //diff中为code 2所花费的时间
 * ts.printDiff();
 * ts.finish(); //从start到finish的时间
 * ts.printDiff();
 */
class TimeStat 
{
public:
	TimeStat(); 
	TimeStat(const std::string &name);
	virtual ~TimeStat();

	void start();
	void updateCheckpoint();
	void finish();
	void printDiff();
	const std::string& diffToString();
	
private:
	std::string name_;
	ACE_Time_Value start_, checkport_, end_, diff_;
};

};
