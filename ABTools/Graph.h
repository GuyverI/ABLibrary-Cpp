#pragma once

#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>

#include "../2DArray/2DArray.h"

namespace AB
{
	template<class EdgeWeight, class Id>
	class Graph final
	{
	public:
		using EdgeWeightType = EdgeWeight;
		using NodeIdType = Id;

		using IdGeneretionFunc = std::function<NodeIdType(const size_t)>;

		struct Edge
		{
			EdgeWeightType weight = DISTANCE_INFINITY;
			NodeIdType destId = NodeIdType();
		};

		struct Node
		{
			NodeIdType id = NodeIdType();
			std::vector<Edge> neighbours;
		};

		struct AdjacencyMatrix
		{
			TwoDArray<EdgeWeightType> matrix;

			explicit AdjacencyMatrix(const size_t nodeCount) : matrix(nodeCount, nodeCount, DISTANCE_INFINITY) {}
		};

	public:
		static const auto DISTANCE_INFINITY = std::numeric_limits<EdgeWeightType>::max();

		static NodeIdType GenerateNodeId(const size_t matrixIndex)
		{
			return static_cast<NodeIdType>(matrixIndex);
		}

		Graph(const AdjacencyMatrix& adjMatrix, const IdGeneretionFunc& generateId)
			: _nodes()
		{
			//TODO: AB add asserts
			const auto nodeCount = adjMatrix.matrix.GetColCount();
			if (nodeCount == adjMatrix.matrix.GetRowCount())
			{
				for (size_t row = 0; row < nodeCount; ++row)
				{
					_nodes.push_back({ generateId(row), std::vector<Edge>() });

					for (size_t col = 0; col < nodeCount; ++col)
					{
						const auto& edgeWeight = adjMatrix.matrix.At(row, col);
						if (edgeWeight != DISTANCE_INFINITY)
						{
							_nodes.back().neighbours.push_back({ edgeWeight, generateId(col) });
						}
					}
				}
			}
		}

		size_t GetNodeCount() const
		{
			return _nodes.size();
		}

		const std::vector<Node>& GetNodes() const
		{
			return _nodes;
		}

		bool DoesNodeExist(const NodeIdType& id) const
		{
			return FindNode(id) != nullptr;
		}

		const Node* FindNode(const NodeIdType& id) const
		{
			const auto it = std::find_if(_nodes.cbegin(), _nodes.cend(), [&id](const Node& node)
			{
				return node.id == id;
			});
			if (it != _nodes.cend())
			{
				return &(*it);
			}

			return nullptr;
		}

	private:
		std::vector<Node> _nodes;
	};

	template<class Id>
	using PositiveEdgeGraph = Graph<size_t, Id>;
}