#pragma once

#define RETURN_IF_ERROR(expr) \
    if (const auto result = expr; \
        !result) \
        return std::unexpected(result.error());

#define UNWRAP_OR_RETURN_ERROR(result, expr) \
    const auto& expected_##result = expr; \
    if (!expected_##result) \
        return std::unexpected(expected_##result.error()); \
    const auto& result = expected_##result.value();
