#include "Debug.h"
MessageType Debug::currentSeverity = MessageType::TYPE_NONE;

void Debug::DebugInit()
{
	std::ofstream out;
	out.open("Engine_ErrorLog.txt", std::ios::out);
	out.close();

	currentSeverity = MessageType::TYPE_FATAL_ERROR;
}

void Debug::SetSeverity(MessageType type_)
{
	currentSeverity = type_;
}

void Debug::FatalError(const std::string& message_, const std::string& fileName_, const int line_)
{
	Log(MessageType::TYPE_FATAL_ERROR, "[FATAL ERROR]" + message_, fileName_, line_);
	std::cout << "FATAL ERRORS Produced" << std::endl;
}

void Debug::Error(const std::string& message_, const std::string& fileName_, const int line_)
{
	Log(MessageType::TYPE_ERROR, "[ERROR]" + message_, fileName_, line_);
	std::cout << "ERRORS Produced" << std::endl;
}

void Debug::Warning(const std::string& message_, const std::string& fileName_, const int line_)
{
	Log(MessageType::TYPE_WARNING, "[WARNING]" + message_, fileName_, line_);
	std::cout << "WARNINGS Produced" << std::endl;
}

void Debug::Trace(const std::string& message_, const std::string& fileName_, const int line_)
{
	Log(MessageType::TYPE_TRACE, "[TRACE]" + message_, fileName_, line_);
}

void Debug::Info(const std::string& message_, const std::string& fileName_, const int line_)
{
	Log(MessageType::TYPE_INFO, "[INFO]" + message_, fileName_, line_);
}

void Debug::Log(const MessageType type_, const std::string& message_, const std::string& fileName_, const int line_)
{
	if (type_ <= currentSeverity && currentSeverity > MessageType::TYPE_NONE)
	{
		std::ofstream file;
		file.open("Engine_ErrorLog.txt", std::ios::out | std::ios::app);
		file << message_ << " in file: " << fileName_ << " on line: " << line_ << std::endl;
		file.flush();
		file.close();
	}
	std::cout << "Debug info in Engine_ErrorLog.txt" << std::endl;
}
