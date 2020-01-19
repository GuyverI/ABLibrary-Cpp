#pragma once

#include <random>

namespace ABTools
{
	class Randomizer
	{
	public:
		using Generator = std::mt19937;
		using Seed = std::mt19937::result_type;

	public:
		Randomizer();

		template<class T>
		T GenerateFloat(const T min, const T max)
		{
			return GenerateRandom<T, std::uniform_real_distribution<T>>(min, max);
		}

		template<class T>
		T GenerateInt(const T min, const T max)
		{
			return GenerateRandom<T, std::uniform_int_distribution<T>>(min, max);
		}

		bool GenerateBool();

		Seed GetSeed() const;
		void SetSeed(const Seed seed);

	private:
		template<class T, class RandomNumberDistribution>
		T GenerateRandom(T min, T max)
		{
			if (min > max)
			{
				std::swap(min, max);
			}

			if (min != max)
			{
				auto distr = RandomNumberDistribution(min, max);
				return distr(_generator);
			}
			else
			{
				return min;
			}
		}

	private:
		Generator _generator;
		Seed _seed;
	};
}