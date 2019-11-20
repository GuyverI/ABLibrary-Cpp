#include "Randomizer.h"

namespace AB
{
	static const Randomizer::Seed DEFAULT_SEED = 1;

	Randomizer::Randomizer()
		: _generator(DEFAULT_SEED)
		, _seed(DEFAULT_SEED)
	{}

	bool Randomizer::GenerateBool()
	{
		return GenerateInt(0, 1) == 1;
	}

	Randomizer::Seed Randomizer::GetSeed() const
	{
		return _seed;
	}

	void Randomizer::SetSeed(const Randomizer::Seed seed)
	{
		_seed = seed;
		_generator.seed(seed);
	}
}