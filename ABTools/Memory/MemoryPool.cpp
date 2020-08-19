#include "MemoryPool.h"

#include <cassert>
#include <cstdlib>

namespace AB
{
	using ChunkHeader = std::uint8_t*;

	static const size_t CHUNK_HEADER_SIZE = sizeof(ChunkHeader);

	ChunkHeader& GetHeaderRef(MemoryPool::ChunkPtr chunk)
	{
		auto headerPtr = reinterpret_cast<ChunkHeader*>(chunk);
		return headerPtr[0];
	}

	MemoryPool::ChunkPtr GetNext(MemoryPool::ChunkPtr chunk)
	{
		return GetHeaderRef(chunk);
	}

	void SetNext(MemoryPool::ChunkPtr chunkToChange, MemoryPool::ChunkPtr nextChunk)
	{
		GetHeaderRef(chunkToChange) = nextChunk;
	}

	MemoryPool::MemoryPool()
		: _memoryBlocks(nullptr)
		, _blockCount(0)
		, _chunkSize(0)
		, _chunkCount(0)
		, _head(nullptr)
		, _isResizeAllowed(true)
	{}

	MemoryPool::~MemoryPool()
	{
		Destroy();
	}
	
	bool MemoryPool::IsInitialized() const
	{
		return GetChunkSize() != 0;
	}
	
	bool MemoryPool::Init(const size_t chunkSize, const size_t chunkCount)
	{
		if (_memoryBlocks)
		{
			Destroy();
		}

		_chunkSize = chunkSize;
		_chunkCount = chunkCount;

		return GrowMemory();
	}

	void MemoryPool::Destroy()
	{
		for (size_t i = 0; i < _blockCount; ++i)
		{
			std::free(_memoryBlocks[i]);
		}
		std::free(_memoryBlocks);
		_memoryBlocks = nullptr;
		_blockCount = 0;

		_chunkSize = 0;
		_chunkCount = 0;

		_head = nullptr;
	}

	bool MemoryPool::IsResizeAllowed() const
	{
		return _isResizeAllowed;
	}

	void MemoryPool::AllowResize(const bool val)
	{
		_isResizeAllowed = val;
	}

	size_t MemoryPool::GetChunkSize() const
	{
		return _chunkSize;
	}

	void* MemoryPool::Alloc()
	{
		if (!_head && (!IsResizeAllowed() || !GrowMemory()))
		{
			return nullptr;
		}

		auto result = _head;
		_head = GetNext(_head);

#ifdef _DEBUG
		++_allocationCount;
#endif //_DEBUG

		return reinterpret_cast<void*>(result + CHUNK_HEADER_SIZE);
	}

	void MemoryPool::Free(void* memoryPtr)
	{
		if (memoryPtr)
		{
			auto ptrWithChankHeader = reinterpret_cast<ChunkPtr>(memoryPtr) - CHUNK_HEADER_SIZE;
			SetNext(ptrWithChankHeader, _head);
			_head = ptrWithChankHeader;

#ifdef _DEBUG
			assert(_allocationCount > 0);
			--_allocationCount;
#endif //_DEBUG
		}
	}

#ifdef _DEBUG
	std::string MemoryPool::GetName() const
	{
		return _name;
	}

	void MemoryPool::SetName(std::string name)
	{
		_name = std::move(name);
	}
#endif //_DEBUG

	bool MemoryPool::GrowMemory()
	{
		//TODO: AB - implement a simple dynamic array class
		auto newBlockArray = reinterpret_cast<MemoryBlockArray>(std::malloc(sizeof(MemoryBlockPtr) *(_blockCount + 1)));
		if (newBlockArray)
		{
			auto newBlock = AllocateBlock();
			if (newBlock)
			{
				for (size_t i = 0; i < _blockCount; ++i)
				{
					newBlockArray[i] = _memoryBlocks[i];
				}
				newBlockArray[_blockCount] = newBlock;

				if (_head)
				{
					auto currChunk = _head;
					auto nextChunk = GetNext(currChunk);
					while (nextChunk)
					{
						currChunk = nextChunk;
						nextChunk = GetNext(currChunk);
					}
					SetNext(currChunk, newBlockArray[_blockCount]);
				}
				else
				{
					_head = newBlockArray[_blockCount];
				}

				if (_memoryBlocks)
				{
					std::free(_memoryBlocks);
				}

				_memoryBlocks = newBlockArray;
				++_blockCount;

				return true;
			}

			std::free(newBlockArray);

			return false;
		}

		return false;
	}

	MemoryPool::MemoryBlockPtr MemoryPool::AllocateBlock()
	{
		const size_t realChunkSize = _chunkSize + CHUNK_HEADER_SIZE;
		const size_t blockSize = realChunkSize * _chunkCount;
		auto block = reinterpret_cast<MemoryBlockPtr>(std::malloc(blockSize));
		if (block)
		{
			const auto endPtr = block + blockSize;
			for (auto curPtr = block; curPtr < endPtr; curPtr += realChunkSize)
			{
				auto nextPtr = curPtr + realChunkSize;
				auto headerPtr = reinterpret_cast<ChunkPtr*>(curPtr);
				if (nextPtr < endPtr)
				{
					headerPtr[0] = nextPtr;
				}
				else
				{
					headerPtr[0] = nullptr;
				}
			}
		}

		return block;
	}
}