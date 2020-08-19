#pragma once

#include <map>

namespace AB
{
	class MemoryDistributor
	{
	public:
		void* Alloc(const size_t size);
		void Free(void* memoryPtr);

	private:
		std::map<void*, size_t> _allocated;
	};
}