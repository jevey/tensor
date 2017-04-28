﻿#pragma once

#include <matazure/config.hpp>
#include <array>

namespace matazure {
namespace meta {

template <int_t _V>
using int_t_c = std::integral_constant<int_t, _V>;

template <int_t ..._Values0>
struct array{
	MATAZURE_GENERAL static constexpr int_t size() {
		return sizeof...(_Values0);
	}
};

template <int_t _Idx, int_t ..._Values>
inline MATAZURE_GENERAL constexpr int_t at_c(array<_Values...> a) {
	return std::array<int_t, sizeof...(_Values)>{_Values...}[_Idx];
}

#define MATAZURE_META_BINARY_FUNC(name, op)																						\
template <int_t... _Values0, int_t... _Values1>																					\
inline MATAZURE_GENERAL constexpr auto name##_c(array<_Values0 ...>, array<_Values1 ...>)->array<_Values0 op _Values1 ...> {	\
	return array<_Values0 op _Values1 ...>{};																					\
}																																\
																																\
template <int_t ..._Values, int_t _V>																							\
inline MATAZURE_GENERAL constexpr auto name##_c(array<_Values ...>, int_t_c<_V>)->array<_Values op _V ...> {					\
	return array<_Values op _V ...>{};																							\
}																																\
																																\
template <int_t _V, int_t ..._Values>																							\
inline MATAZURE_GENERAL constexpr auto name##_c(int_t_c<_V>, array<_Values ...>)->array<_V op _Values ...> {					\
	return array<_V op _Values ...>{};																							\
}

MATAZURE_META_BINARY_FUNC(add, +)
MATAZURE_META_BINARY_FUNC(sub, -)
MATAZURE_META_BINARY_FUNC(mul, *)
MATAZURE_META_BINARY_FUNC(div, /)
MATAZURE_META_BINARY_FUNC(mod, %)

}
}
