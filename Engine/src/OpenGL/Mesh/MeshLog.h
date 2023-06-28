#pragma once

#include <typeinfo>
#include <memory>
#include <string>

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
			s_MeshLogger->set_level(spdlog::level::trace);
			return s_MeshLogger; 
		}

	private:

		static std::shared_ptr<spdlog::logger>& initializedLogger()
		{
			std::shared_ptr<spdlog::logger>logger = spdlog::stdout_color_mt("Mesh Log");
			logger->set_pattern("%^%v%$");
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

#define KRM_MESH_STRIP_CLASS_NAME(class_name) \
	[](const char* name) { \
		std::string result(name); \
		size_t colons = result.find("::"); \
		if (colons != std::string::npos) \
			result = result.substr(colons + 2); \
		size_t ampersand = result.find("&"); \
		if (ampersand != std::string::npos) \
			result = result.substr(0, ampersand); \
		return result; \
	}(typeid(class_name).name())

#define KRM_MESH_TRACE(...) ::krm::MeshLog::getMeshLog()->trace("[{}] : {}", KRM_MESH_STRIP_CLASS_NAME(*this), fmt::format(__VA_ARGS__))
#define KRM_TRACE_MESSAGE(...) KRM_MESH_TRACE(__VA_ARGS__)

#define KRM_MESH_INFO(...) ::krm::MeshLog::getMeshLog()->info("[{}] : {}", KRM_MESH_STRIP_CLASS_NAME(*this), fmt::format(__VA_ARGS__))
#define KRM_INFO_MESSAGE(...) KRM_MESH_INFO(__VA_ARGS__)

#define KRM_MESH_ERROR(...) ::krm::MeshLog::getMeshLog()->error("[{}] : {}", KRM_MESH_STRIP_CLASS_NAME(*this), fmt::format(__VA_ARGS__))
#define KRM_ERROR_MESSAGE(...) KRM_MESH_ERROR(__VA_ARGS__)

#define KRM_MESH_WARN(...) ::krm::MeshLog::getMeshLog()->warn("[{}] : {}", KRM_MESH_STRIP_CLASS_NAME(*this), fmt::format(__VA_ARGS__))
#define KRM_WARN_MESSAGE(...) KRM_MESH_WARN(__VA_ARGS__)

#define KRM_MESH_ASSERT(x, ...) if(!(x)) { KRM_MESH_ERROR("[{}] : {}", KRM_MESH_STRIP_CLASS_NAME(*this), fmt::format(__VA_ARGS__)); __debugbreak(); }


#endif //ENABLE_MESH_LOG