#pragma once

#include <stdexcept>
#include <string>
#include <optional>

namespace haflsl {
    template <typename T>
    struct Result {
        std::optional<T> value = {};
        std::string message = {};

        explicit Result(T &&_value)
            : value{std::move(_value)} {
        }

        explicit Result(T const &_value)
            : value{_value} {
        }

        explicit Result(std::optional<T> &&opt)
            : value{std::move(opt)}, message{opt.has_value() ? "" : "default error message"} {
        }

        explicit Result(std::optional<T> const &opt)
            : value{opt}, message{opt.has_value() ? "" : "default error message"} {
        }

        explicit Result(std::string_view _message)
            : value{std::nullopt}, message{_message} {
        }

        [[nodiscard]] 
        auto is_ok() const -> bool {
            return value.has_value();
        }

        [[nodiscard]] 
        auto is_err() const -> bool {
            return !value.has_value();
        }

        auto get_value() const -> T const & {
            return value.value();
        }

        auto get_value() -> T & {
            if(!value.has_value()) { throw std::runtime_error(!message.empty() ? message : "tried getting value of empty Result"); } 
            return value.value();
        }

        [[nodiscard]] 
        auto get_message() const -> std::string const & {
            return message;
        }

        [[nodiscard]] 
        auto to_string() const -> std::string {
            if (value.has_value()) {
                return "Result OK";
            } else {
                return std::string("Result Err: ") + message;
            }
        }

        operator bool() const {
            return value.has_value();
        }

        auto operator!() const -> bool {
            return !value.has_value();
        }
    };
} // namespace haflsl