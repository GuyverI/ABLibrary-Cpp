#pragma once

#include <memory>
#include <optional>

#include "Randomizer.h"

namespace AB
{
	class PrimeSearch
	{
	public:
		PrimeSearch(const size_t count, Randomizer& randomizer);

		void Reset();

		bool IsDone() const;

		std::optional<size_t> GetNext(const bool shouldReset = false);

	private:
		size_t _skip;
		size_t _currentPosition;
		size_t _elementCount;
		size_t* _currentPrime;
		size_t _searchCount;
	};
}