#pragma once

#include <algorithm>

namespace ABTools
{
	template<class Container, class T>
	auto Find(Container& container, const T& val)
	{
		return std::find(std::begin(container), std::end(container), val);
	}

	template<class Container, class Predicate>
	auto FindIf(Container& container, Predicate&& predicate)
	{
		return std::find_if(std::begin(container), std::end(container), std::forward<Predicate>(predicate));
	}

	template<class Container, class T>
	bool Contains(const Container& container, const T& val)
	{
		return Find(container, val) != std::end(container);
	}

	template<class Container, class Predicate>
	bool ContainsIf(const Container& container, Predicate&& predicate)
	{
		return FindIf(container, std::forward<Predicate>(predicate)) != std::end(container);
	}
}