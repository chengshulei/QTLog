
#pragma once

#pragma execution_character_set("utf-8")//support chinese

#include <QString>
#include <QTextStream>
#include <QFile>
#include <QMutex>
using namespace std;

#define NORMAL_FLAG    "NORMAL: "//4 types of Log grade
#define ERROR_FLAG     "ERROR: "
#define WARNING_FLAG   "WARNING: "
#define BACKUP_FLAG    "BACKUP: "


#define LOG         HandLog::GetLogHandle(NORMAL_FLAG)
#define LOG_E       HandLog::GetLogHandle(ERROR_FLAG)
#define LOG_W       HandLog::GetLogHandle(WARNING_FLAG)
#define LOG_B       HandLog::GetLogHandle(BACKUP_FLAG)


class Log //use Singleton pattern
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
	inline QTextStream& operator<<(const QString &str) //overload <<
	{
		file_mutex->lock();//lock,avoid write at same time
		QFile file(file_path);
		if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) 
		{
			out = new QTextStream(&file);
			if (!falg_exist)
			{
				if (str == NORMAL_FLAG || str == ERROR_FLAG || str == WARNING_FLAG || str == BACKUP_FLAG)
				{
					falg_exist = true;//avoid output log mark more times
					*out << str;
				}
			}
			else
			{
				if (str != NORMAL_FLAG && str != ERROR_FLAG && str != WARNING_FLAG && str != BACKUP_FLAG)
				{
					*out << str << endl;//here add wrap
					falg_exist = false;
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

	static Log GetLogHandle(QString temp_str)//output log mark
	{
		Log * log_system = Log::initance();
		*log_system << temp_str;
		return *log_system;
	}

};
