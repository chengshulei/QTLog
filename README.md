# QTLog


该日志库是在QT下面使用的。
支持中文，支持多线程。
日志文件保存在执行文件同目录下：./日志/

日志文件命名方式如下：年月日_时分秒.log

每次打开软件即创建一个日志文件

包含四中日志等级：NORMAL ERROR WARNING BACKUP，分别对应LOG LOG_E LOG_W LOG_B

库使用方法：在任意地方，包含Log.h文件即可，不需要另外设置

使用时如下：LOG<<  ~ LOG_B<<
(日志文件中会在行首自动添加NORMAL ~ BACKUP标记)

缺陷：后面只能跟一个参数（const Qstring），不能跟多个参数，也不能使用endl。每行结尾会自动添加换行。



The log library is used below QT.
Support Chinese, support multithreading.
The log file is saved in the executable files under the same directory: / / log
The following log file name: date of _ when.Log
Create a log file every time you open the software
Contains the fourth grade: NORMAL ERROR WARNING BACKUP log LOG LOG_E LOG_W LOG_B, respectively
Library usage: in any place, including the Log.h file can be, do not need to set
When used as follows: LOG<< ~ LOG_B<<
(log file will be automatically added at the beginning of the NORMAL ~ BACKUP mark)
Defect: can only follow a parameter (const Qstring), not with multiple parameters, can not use endl. At the end of each line will automatically add a newline.
                                                     
