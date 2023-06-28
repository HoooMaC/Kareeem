#pragma once
#include "KRMpch.h"


#include "spdlog\spdlog.h"
#include "spdlog\sinks\stdout_color_sinks.h"
#include "spdlog\fmt\ostr.h"

#ifdef KRM_ENABLE_LOG

namespace krm {

    class Log
    {
    public:
        Log() {}

        static std::shared_ptr<spdlog::logger>&  initializedLogger(const std::string& name);
    public:
        static std::shared_ptr<spdlog::logger> s_LogCore;
        static std::shared_ptr<spdlog::logger> s_LogClient;
    };

}

#define KRM_LOG_CORE_TRACE(...) ::krm::Log::s_LogCore->trace(__VA_ARGS__);
#define KRM_LOG_CORE_INFO(...)  ::krm::Log::s_LogCore->info(__VA_ARGS__);
#define KRM_LOG_CORE_WARN(...)  ::krm::Log::s_LogCore->warn(__VA_ARGS__);
#define KRM_LOG_CORE_ERROR(...) ::krm::Log::s_LogCore->error(__VA_ARGS__);

#define KRM_LOG_CLIENT_TRACE(...) ::krm::Log::s_LogClient->trace(__VA_ARGS__);
#define KRM_LOG_CLIENT_INFO(...)  ::krm::Log::s_LogClient->info(__VA_ARGS__);
#define KRM_LOG_CLIENT_WARN(...)  ::krm::Log::s_LogClient->warn(__VA_ARGS__);
#define KRM_LOG_CLIENT_ERROR(...) ::krm::Log::s_LogClient->error(__VA_ARGS__);

#else

namespace krm {

    class Log
    {
    public:
        static void Init() {}
    };
}
#define KRM_LOG_CORE_TRACE(...)
#define KRM_LOG_CORE_INFO(...)
#define KRM_LOG_CORE_WARN(...)
#define KRM_LOG_CORE_ERROR(...)


#define KRM_LOG_CLIENT_TRACE(...) 
#define KRM_LOG_CLIENT_INFO(...) 
#define KRM_LOG_CLIENT_WARN(...) 
#define KRM_LOG_CLIENT_ERROR(...) 

#endif // KRM_ENABLE_LOG