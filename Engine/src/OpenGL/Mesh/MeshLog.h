#pragma once

#include <typeinfo>
#include <memory>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace krm {

	class MeshLog
	{
	public:
		MeshLog(const MeshLog&) = delete;

		static std::shared_ptr<spdlog::logger>& getMeshLog()
		{
			//static std::shared_ptr<spdlog::logger>& s_MeshLogger = initializedLogger();
			s_MeshLogger->set_level(spdlog::level::trace);
			return s_MeshLogger; 
		}

	private:

		static std::shared_ptr<spdlog::logger>& initializedLogger()
		{
			std::shared_ptr<spdlog::logger>logger = spdlog::stdout_color_mt("Mesh Log");
			logger->set_pattern("%^[%T] %n: %v%$");
			logger->set_level(spdlog::level::trace);
			return logger;
		}

	private:
		static std::shared_ptr<spdlog::logger> s_MeshLogger;
		MeshLog() = default;
	};

}

#define ENABLE_MESH_LOG

#ifdef ENABLE_MESH_LOG
#define KRM_MESH_TRACE(...) ::krm::MeshLog::getMeshLog()->trace(__VA_ARGS__);
#define KRM_TRACE_MESSAGE(message, ...) KRM_MESH_TRACE("[{}] : " #message, typeid(*this).name(), __VA_ARGS__)

#define KRM_MESH_INFO(...) ::krm::MeshLog::getMeshLog()->info(__VA_ARGS__);
#define KRM_INFO_MESSAGE(message, ...) KRM_MESH_INFO("[{}] : " #message, typeid(*this).name(), __VA_ARGS__)

#define KRM_MESH_ERROR(...) ::krm::MeshLog::getMeshLog()->error(__VA_ARGS__);
#define KRM_ERROR_MESSAGE(message, ...) KRM_MESH_ERROR("[{}] : " #message, typeid(*this).name(), __VA_ARGS__)

#define KRM_MESH_WARN(...) ::krm::MeshLog::getMeshLog()->warn(__VA_ARGS__);
#define KRM_WARN_MESSAGE(message, ...) KRM_MESH_WARN("[{}] : " #message, typeid(*this).name(), __VA_ARGS__)




#endif //ENABLE_MESH_LOG