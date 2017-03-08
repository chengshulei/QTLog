#include "Log.h"
#include <QDir>
#include <QDateTime>
#include <QFile>
#include <QCoreApplication>


Log* Log::p = new Log;
QString Log::file_path = "";
QTextStream* Log::out = NULL;
bool Log::init_flag = false;
bool Log::falg_exist = false;
QMutex* Log::file_mutex = new QMutex;

Log* Log::initance()//初始化日志类
{
	file_mutex->lock();
	if (!init_flag)//是否已经初始化，文件名字只确定一次
	{
		
		QString temp_path = QCoreApplication::applicationDirPath();

		QDir *temp_dir = new QDir;

		QString dir_whole_path = temp_path + "\\" + QStringLiteral("日志");
		if (temp_dir->exists(dir_whole_path))
		{
			QString temp_filename = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".log";
			QString file_whole_path = dir_whole_path + "\\" + temp_filename;

			file_path = file_whole_path;
		}
		else
		{
			if (temp_dir->mkdir(dir_whole_path))
			{
				QString temp_filename = QDateTime::currentDateTime().toString("yyMMdd_hhmmss") + ".log";
				QString file_whole_path = dir_whole_path + "\\" + temp_filename;
				file_path = file_whole_path;
			}
		}
		
		init_flag = true;
	}
	file_mutex->unlock();
	return p;
}
