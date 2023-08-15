#pragma once
#include <ostream>
#include <time.h>
#include <iostream>
#include <Windows.h>

#ifdef LOGGING_EXPORT
#define LOGGING_API _declspec(dllexport)
#else 
#define LOGGING_API _declspec(dllimport)
#endif 


class LOGGING_API Logger
{
public:
	enum class Level
	{
		Info,
		Warning,
		Error
	};
public:
	Logger(std::ostream& out, Level minLevel);

	void setLevel(Level level);

	template<class T>
	void Log(Level level, T message);

	template<class ...Args>
	void Log(Level level, Args&&... parans);

private:
	std::ostream& m_out;
	Level m_minLevel;
	time_t m_time;

};

template<class T>
inline void Logger::Log( Level level, T message)
{
	time(&m_time);
	char time[26];
	ctime_s(time, sizeof time, &m_time);
	time[24] = ' ';
	if (static_cast<int>(level) >= static_cast<int>(m_minLevel))
	{
		if (level == Level::Info)
		{
			m_out << "[Info][ "<<time <<"]" << message << std::endl;
		}
		else if (level == Level::Warning)
		{
			m_out << "[Warning][ " << time << "]" << message << std::endl;
		}
		else
		{
			m_out << "[Error][ " << time << "]" << message << std::endl;
		}
	}
}

template<class ...Args>
inline void Logger::Log(Level level, Args && ...parans)
{
	time(&m_time);
	char time[26];
	ctime_s(time, sizeof time, &m_time);
	time[24] = ' ';
	if (static_cast<int>(level) >= static_cast<int>(m_minLevel))
	{
		if (level == Level::Info)
		{
			m_out << "[Info][ " << time << "]";
		}
		else if (level == Level::Warning)
		{
			m_out << "[Warning][ " << time << "]";
		}
		else
		{
			m_out << "[Error][ " << time << "]";
		}
		((m_out << ' ' << std::forward<Args>(parans)), ...);
		m_out << "\n";
	}
}