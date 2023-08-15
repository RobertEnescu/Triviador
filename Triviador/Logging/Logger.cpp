#include "Logger.h"


Logger::Logger(std::ostream& out, Level minLevel) :
	m_minLevel(minLevel),
	m_out(out)
{
	//time(&m_time);
}

void Logger::setLevel(Level level)
{
	m_minLevel = level;
}

