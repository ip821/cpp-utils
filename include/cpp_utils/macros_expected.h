#pragma once

#define RETURN_IF_ERROR(expr) \
    if (const auto result = expr; \
        !result) \
        return std::unexpected(result.error());

#define UNWRAP_OR_RETURN_ERROR(result, expr) \
    const auto result = expr; \
    if (!result) \
        return std::unexpected(result.error());
