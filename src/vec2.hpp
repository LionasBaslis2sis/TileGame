#pragma once

template <class T>
class vec2 {

public:
	T x, y;
	// constructors
	constexpr vec2() noexcept : x(0), y(0) { }
	constexpr vec2(T x, T y) noexcept : x(x), y(y) { }
	constexpr vec2(const vec2<T>& rhs) noexcept : x(rhs.x), y(rhs.y) { }
	// operators + - * / with other vectors
	template<typename U>
	constexpr auto operator + (const vec2<U>& rhs) const noexcept -> vec2<decltype(x + rhs.x)> {
		return vec2(x + rhs.x, y + rhs.y);
	}

	template<typename U>
	constexpr auto operator - (const vec2<U>& rhs) const noexcept -> vec2<decltype(x - rhs.x)> {
		return vec2(x - rhs.x, y - rhs.y);
	}

	template<typename U>
	constexpr auto operator * (const vec2<U>& rhs) const noexcept -> vec2<decltype(x * rhs.x)> {
		return vec2(x * rhs.x, y * rhs.y);
	}

	template<typename U>
	constexpr auto operator / (const vec2<U>& rhs) const noexcept -> vec2<double> {
		return vec2(x / (double) rhs.x, y / (double)rhs.y);
	}
	// operators * / with scalars

	template<typename U>
	constexpr auto operator * (U scalar) const noexcept -> vec2<decltype(x * scalar)> {
		return vec2(x * scalar, y * scalar);
	}

	template<typename U>
	constexpr auto operator / (U scalar) const noexcept -> vec2<double> {
		return vec2(x / (double) scalar, y / (double) scalar);
	}

	// operators += -= *= /= with other vectors

};

//

template <typename T, typename U>
constexpr auto operator * (T lhs, const vec2<U>& rhs) noexcept -> decltype(rhs * lhs) {
	return rhs * lhs;
}

typedef vec2<int> vec2i;
typedef vec2<float> vec2f;
typedef vec2<double> vec2d;
typedef vec2<unsigned int> vec2u;