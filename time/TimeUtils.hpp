#pragma once

#include <string>
#include <vector>
#include <ostream>
#include <boost/utility.hpp>
#include <ace/Time_Value.h>

namespace time_utils
{
#ifdef ENABLE_SCOPED_TIMER
//���þֲ�ʱ��ͳ��
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
//�رվֲ�ʱ��ͳ��
class ScopedTimer : boost::noncopyable {
public:
	ScopedTimer(const std::string &);
};
#define SCOPED_TIMER(name) (void)0

#endif // ENABLE_SCOPED_TIME

/**
 * ͨ��ʱ��ͳ����
 * �ṩ����ʱ��ͳ�Ʒ�����
 * 1. ͳ�ƴ�start��finish��ʱ��;
 * 2. ͳ������ʱ�����֮���ʱ��
 * ʹ������:
 * TimeState ts;
 * ts.start(); //������ʼʱ�����ʼ���㣬���캯����Ҳ�����start
 * ......code 1......
 * ts.updateCheckpoint(); //����ʱ����㣬ͬʱ������һ��
 * 						  //ʱ����㵽��ǰ�������õ�ʱ�����diff,
 *						  //�˴�Ϊcode 1�����ѵ�ʱ��
 * ts.printDiff(); 		  //���diff��ʱ��
 * ......code 2......
 * ts.updateCheckpoint(); //diff��Ϊcode 2�����ѵ�ʱ��
 * ts.printDiff();
 * ts.finish(); //��start��finish��ʱ��
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
