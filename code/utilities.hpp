#pragma once

#include <memory>
#include <functional>
#include <utility>

#define let auto const&
#define cref const&

#define ND [[nodiscard]]

template<typename T>
using uniq = std::unique_ptr<T>;

template<typename T, typename...Params>
auto mk_uniq(Params &&...args) {
    return std::make_unique<T>(std::forward<Params>(args)...);
}

template<typename T>
using Ref = std::reference_wrapper<T> const;

template<typename T>
using MutRef = std::reference_wrapper<T>;
