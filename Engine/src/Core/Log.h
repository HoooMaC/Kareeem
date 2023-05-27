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
        inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_LogCore; }
        inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_LogClient; }

        static void Init() {
            spdlog::set_pattern("%^[%T] %n: %v%$");
            s_LogCore = spdlog::stdout_color_mt("CORE");
            getCoreLogger()->set_level(spdlog::level::trace);

            s_LogClient = spdlog::stdout_color_mt("APP");
            getClientLogger()->set_level(spdlog::level::trace);
        }
    private:
        static std::shared_ptr<spdlog::logger> s_LogCore;
        static std::shared_ptr<spdlog::logger> s_LogClient;
    };

}

#define KRM_LOG_CORE_TRACE(...) ::krm::Log::getCoreLogger()->trace(__VA_ARGS__);
#define KRM_LOG_CORE_INFO(...)  ::krm::Log::getCoreLogger()->info(__VA_ARGS__);
#define KRM_LOG_CORE_WARN(...)  ::krm::Log::getCoreLogger()->warn(__VA_ARGS__);
#define KRM_LOG_CORE_ERROR(...) ::krm::Log::getCoreLogger()->error(__VA_ARGS__);

#define KRM_LOG_CLIENT_TRACE(...) ::krm::Log::getClientLogger()->trace(__VA_ARGS__);
#define KRM_LOG_CLIENT_INFO(...)  ::krm::Log::getClientLogger()->info(__VA_ARGS__);
#define KRM_LOG_CLIENT_WARN(...)  ::krm::Log::getClientLogger()->warn(__VA_ARGS__);
#define KRM_LOG_CLIENT_ERROR(...) ::krm::Log::getClientLogger()->error(__VA_ARGS__);

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