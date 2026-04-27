#pragma once

#include <concepts>
#include <expected>
#include <functional>
#include <type_traits>
#include <utility>

namespace ip {
    template<typename Exp, typename OnValue>
    using on_value_return_t = std::invoke_result_t<OnValue, decltype(*std::declval<Exp>())>;

    template<typename Exp, typename OnError>
    using on_error_return_t = std::invoke_result_t<OnError, decltype(std::declval<Exp>().error())>;

    template<typename Exp, typename OnValue, typename OnError>
    using match_return_t = std::expected<
        on_value_return_t<Exp, OnValue>,
        on_error_return_t<Exp, OnError>
    >;

    template<typename Exp, typename OnValue, typename OnError>
    concept MatchExpectedNonVoidHandlers =
            std::invocable<OnValue, decltype(*std::declval<Exp>())> &&
            std::invocable<OnError, decltype(std::declval<Exp>().error())> &&
            !std::same_as<on_value_return_t<Exp, OnValue>, void> &&
            !std::same_as<on_error_return_t<Exp, OnError>, void>;

    template<typename Exp, typename OnValue, typename OnError>
    concept MatchExpectedVoidHandlers =
            std::invocable<OnValue, decltype(*std::declval<Exp>())> &&
            std::invocable<OnError, decltype(std::declval<Exp>().error())> &&
            std::same_as<on_value_return_t<Exp, OnValue>, void> &&
            std::same_as<on_error_return_t<Exp, OnError>, void>;

    template<typename Exp, typename OnValue, typename OnError>
        requires MatchExpectedNonVoidHandlers<Exp &&, OnValue &&, OnError &&>
    auto match_expected(Exp &&exp, OnValue &&on_value, OnError &&on_error)
        -> match_return_t<Exp &&, OnValue &&, OnError &&> {
        using R = match_return_t<Exp &&, OnValue &&, OnError &&>;

        if (exp.has_value()) {
            return R(std::in_place, std::invoke(std::forward<OnValue>(on_value), *std::forward<Exp>(exp)));
        } else {
            return R(std::unexpect, std::invoke(std::forward<OnError>(on_error), std::forward<Exp>(exp).error()));
        }
    }

    template<typename Exp, typename OnValue, typename OnError>
        requires MatchExpectedVoidHandlers<Exp &&, OnValue &&, OnError &&>
    void match_expected(Exp &&exp, OnValue &&on_value, OnError &&on_error) {
        if (exp.has_value()) {
            std::invoke(std::forward<OnValue>(on_value), *std::forward<Exp>(exp));
        } else {
            std::invoke(std::forward<OnError>(on_error), std::forward<Exp>(exp).error());
        }
    }

    template<typename Exp, typename OnValue, typename OnError>
    concept MapExpectedToOptionalHandlers =
        std::invocable<OnValue, decltype(*std::declval<Exp>())> &&
        std::invocable<OnError, decltype(std::declval<Exp>().error())> &&
        !std::same_as<on_value_return_t<Exp, OnValue>, void> &&
        std::same_as<on_error_return_t<Exp, OnError>, void>;

    template<typename Exp, typename OnValue, typename OnError>
        requires MapExpectedToOptionalHandlers<Exp&&, OnValue&&, OnError&&>
    auto map_expected_to_optional(Exp&& exp, OnValue&& on_value, OnError&& on_error)
    {
        using Result = std::remove_cvref_t<on_value_return_t<Exp &&, OnValue &&> >;

        if (exp.has_value())
        {
            return std::optional<Result>{std::invoke(std::forward<OnValue>(on_value), *std::forward<Exp>(exp))};
        }
        else
        {
            std::invoke(std::forward<OnError>(on_error), std::forward<Exp>(exp).error());
            return std::optional<Result>{std::nullopt};
        }
    }
}
