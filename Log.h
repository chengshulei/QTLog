
#pragma once

#pragma execution_character_set("utf-8")//中文支持

#include <QString>
#include <QTextStream>
#include <QFile>
#include <QMutex>
using namespace std;

#define NORMAL_FLAG "NORMAL: "//4种日志输出标志
#define ERROR_FLAG "NORMAL: "
#define WARNING_FLAG "NORMAL: "
#define BACKUP_FLAG "NORMAL: "


#define LOG         HandLog::GetLogHandle(NORMAL_FLAG)
#define LOG_E       HandLog::GetLogHandle(ERROR_FLAG)
#define LOG_W       HandLog::GetLogHandle(WARNING_FLAG)
#define LOG_B       HandLog::GetLogHandle(BACKUP_FLAG)

//使用LOG<<  LOG_E<<  LOG_W<<  LOG_B<<  即可完成输出
//注意：输出不能叠加，智能输出一次，不用添加换行，行尾自动添加

//这里使用了单例模式进行设计，避免重复定义
//程书雷 20170307

class Log 
{
protected:
	Log(){}
private:
	static Log* p;
public:
	static Log* initance();

	static bool init_flag;

	static QString file_path;
	static QTextStream* out;

	static QMutex* file_mutex;
	static bool falg_exist;
	inline QTextStream& operator<<(const QString &str) //定义重载函数,输出
	{
		file_mutex->lock();//加锁，防止同时写入
		QFile file(file_path);
		if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) //以文本文式追加写入
		{
			out = new QTextStream(&file);
			if (!falg_exist)
			{
				if (str == NORMAL_FLAG || str == ERROR_FLAG || str == WARNING_FLAG || str == BACKUP_FLAG)//4种日志输出标志
				{
					falg_exist = true;//避免重复输出4种输出标志
					*out << str;
				}
			}
			else
			{
				if (str != NORMAL_FLAG && str != ERROR_FLAG && str != WARNING_FLAG && str != BACKUP_FLAG)
				{
					//*out << str << endl;//注意这里自动添加换行
					*out << str << endl;//注意这里自动添加换行
					falg_exist = false;//避免重复输出4种输出标志
				}
			}
			file.close();
		}
		else
		{
			file.close();
		}
		file_mutex->unlock();
		return *out;
	}
};

class HandLog
{
public:

	static Log GetLogHandle(QString temp_str)//输出日志标志
	{
		Log * log_system = Log::initance();
		*log_system << temp_str;
		return *log_system;
	}

};
