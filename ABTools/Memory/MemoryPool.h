#pragma once

#include <cstdint>

#ifdef _DEBUG
#include <string>
#endif //_DEBUG

namespace AB
{
	class MemoryPool
	{
	public:
		using ChunkPtr = std::uint8_t*;

	public:
		MemoryPool(const MemoryPool&) = delete;
		MemoryPool(const MemoryPool&&) = delete;
		MemoryPool& operator=(const MemoryPool&) = delete;
		MemoryPool& operator=(const MemoryPool&&) = delete;

		MemoryPool();
		~MemoryPool();

		bool IsInitialized() const;
		bool Init(const size_t chunkSize, const size_t chunkCount);
		void Destroy();

		bool IsResizeAllowed() const;
		void AllowResize(const bool val);

		size_t GetChunkSize() const;
		void* Alloc();
		void Free(void* memoryPtr);

#ifdef _DEBUG
		std::string GetName() const;
		void SetName(std::string name);
#endif //_DEBUG

	private:
		using MemoryBlockPtr = std::uint8_t*;
		using MemoryBlockArray = MemoryBlockPtr*;

	private:
		bool GrowMemory();
		MemoryBlockPtr AllocateBlock();

	private:
		MemoryBlockArray _memoryBlocks;
		size_t _blockCount;

		size_t _chunkSize;
		size_t _chunkCount;

		ChunkPtr _head;

		bool _isResizeAllowed;

#ifdef _DEBUG
		std::string _name;
		size_t _allocationCount;
#endif //_DEBUG
	};
}