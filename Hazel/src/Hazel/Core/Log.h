#pragma once
#include "Base.h"
#pragma warning(push, 0)
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <spdlog/sinks/basic_file_sink.h>
#include "spdlog/fmt/ostr.h"
#pragma warning(pop)
namespace Hazel {
	class Log
	{
	public:
		Log();
		~Log() = default;
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;


	};

}
//core log macros
#define HZ_CORE_ERROR(...) \
    do { \
        Hazel::Log::GetCoreLogger()->error(__VA_ARGS__); \
        Hazel::Log::GetCoreLogger()->error("File: {}, Line: {}", __FILE__, __LINE__); \
    } while (0)


#define HZ_CORE_WARN(...)\
	do { \
		Hazel::Log::GetCoreLogger()->warn(__VA_ARGS__);\
		Hazel::Log::GetCoreLogger()->warn("File: {}, Line: {}", __FILE__, __LINE__);\
	} while (0)

#define HZ_CORE_INFO(...)	::Hazel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HZ_CORE_TRACE(...)	::Hazel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HZ_CORE_CRITICAL(...)  ::Hazel::Log::GetCoreLogger()->critical(__VA_ARGS__)

//core log macros
#define HZ_ERROR(...)\
	do { \
		Hazel::Log::GetClientLogger()->error(__VA_ARGS__);\
		Hazel::Log::GetClientLogger()->error("File: {}, Line: {}", __FILE__, __LINE__);\
	} while (0)

#define HZ_WARN(...)\
	do { \
		Hazel::Log::GetClientLogger()->warn(__VA_ARGS__);\
		Hazel::Log::GetClientLogger()->warn("File: {}, Line: {}", __FILE__, __LINE__);\
	} while (0)

#define HZ_INFO(...)	::Hazel::Log::GetClientLogger()->info(__VA_ARGS__)
#define HZ_TRACE(...)	::Hazel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HZ_CRITICAL(...)      ::Hazel::Log::GetClientLogger()->critical(__VA_ARGS__)

