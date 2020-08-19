#include "MemoryDistributor.h"

#include "MemoryPool.h"

namespace AB
{
	static const size_t MAX_SMALL_MEM_CHUNK_SIZE = 500;
	static std::map<size_t, MemoryPool> sMemoryPools;

	void* MemoryDistributor::Alloc(const size_t size)
	{
		if (size <= MAX_SMALL_MEM_CHUNK_SIZE)
		{
			auto& memPool = sMemoryPools[size];
			if (!memPool.IsInitialized())
			{
				const size_t CHUNK_COUNT = 1000;
				if (!memPool.Init(size, CHUNK_COUNT))
				{
					return nullptr;
				}
			}

			auto result = memPool.Alloc();
			if (result)
			{
				_allocated[result] = size;
			}

			return result;
		}

		return ::operator new(size);
	}

	void MemoryDistributor::Free(void* memoryPtr)
	{
		if (memoryPtr)
		{
			auto it = _allocated.find(memoryPtr);
			if (it != _allocated.end() && it->second <= MAX_SMALL_MEM_CHUNK_SIZE)
			{
				sMemoryPools[it->second].Free(memoryPtr);
				_allocated.erase(it);
			}
			else
			{
				::operator delete(memoryPtr);
			}
		}
	}
}