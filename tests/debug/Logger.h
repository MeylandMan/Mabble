#pragma once

#include "Core/Base.h"
#include <filesystem>

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

class Logger
{
public:
	static void Init();

	inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }

private:
	static std::shared_ptr<spdlog::logger> s_Logger;
};

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
	return os << glm::to_string(quaternion);
}

namespace fmt {

	template <>
	struct formatter<std::filesystem::path> : formatter<std::string> {

		template <typename FormatContext>
		auto format(const std::filesystem::path& path, FormatContext& ctx) const {
			return formatter<std::string>::format(path.string(), ctx);
		}

	};

	template <>
	struct formatter<std::vector<std::string>> {
		constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
			return ctx.begin();
		}

		template <typename FormatContext>
		auto format(const std::vector<std::string>& vec, FormatContext& ctx) const -> decltype(ctx.out()) {
			fmt::format_to(ctx.out(), "{{");
			for (size_t i = 0; i < vec.size(); ++i) {
				fmt::format_to(ctx.out(), "{}", vec[i]);
				if (i < vec.size() - 1) {
					fmt::format_to(ctx.out(), ", ");
				}
			}
			return fmt::format_to(ctx.out(), "}}");
		}

	};
}

#ifdef MABBLE_DEBUG

#define LOGGER_TRACE(...)		Logger::GetLogger()->trace(__VA_ARGS__)
#define LOGGER_INFO(...)		Logger::GetLogger()->info(__VA_ARGS__)
#define LOGGER_DEBUG(...)		Logger::GetLogger()->debug(__VA_ARGS__)
#define LOGGER_WARN(...)		Logger::GetLogger()->warn(__VA_ARGS__)
#define LOGGER_ERROR(...)		Logger::GetLogger()->error(__VA_ARGS__)
#define LOGGER_CRITICAL(...)	Logger::GetLogger()->critical(__VA_ARGS__)

#endif