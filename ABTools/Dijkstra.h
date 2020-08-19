#pragma once

#include <algorithm>
#include <map>
#include <vector>

#include "../../Structures/Graph/Graph.h"

namespace AB
{
	namespace Dijkstra
	{
		template<class Id>
		std::map<Id, Id> GetShortestPathsFromNode(const PositiveEdgeGraph<Id>& graph, const Id& srcNodeId)
		{
			auto shortestPath = std::map<Id, Id>();

			if (graph.DoesNodeExist(srcNodeId))
			{
				shortestPath[srcNodeId] = srcNodeId;

				struct DistToSrcInfo
				{
					Id nodeId;
					typename PositiveEdgeGraph<Id>::EdgeWeightType dist;
				};
				auto nodesToCheck = std::vector<DistToSrcInfo>();
				for (const auto& node : graph.GetNodes())
				{
					auto distance = PositiveEdgeGraph<Id>::DISTANCE_INFINITY;
					if (node.id == srcNodeId)
					{
						distance = 0;
					}

					nodesToCheck.push_back({ node.id, distance });
				}

				while (!nodesToCheck.empty())
				{
					std::sort(nodesToCheck.begin(), nodesToCheck.end(), [](const DistToSrcInfo& node1, const DistToSrcInfo& node2)
					{
						return node1.dist > node2.dist;
					});

					const auto& currNode = nodesToCheck.back();
					if (currNode.dist == PositiveEdgeGraph<Id>::DISTANCE_INFINITY)
					{
						break;
					}

					const auto* node = graph.FindNode(currNode.nodeId);
					if (node)
					{
						for (const auto& neighb : node->neighbours)
						{
							const auto it = std::find_if(nodesToCheck.begin(), nodesToCheck.end(), [&neighb](const DistToSrcInfo& item)
							{
								return item.nodeId == neighb.destId;
							});
							if (it != nodesToCheck.end())
							{
								const auto newNeighbDist = currNode.dist + neighb.weight;
								if (it->dist > newNeighbDist)
								{
									it->dist = newNeighbDist;

									shortestPath[neighb.destId] = currNode.nodeId;
								}
							}
						}
					}

					nodesToCheck.pop_back();
				}
			}

			return shortestPath;
		}

		template<class Id>
		std::vector<Id> GetShortestPath(const PositiveEdgeGraph<Id>& graph, const Id& srcNodeId, const Id& destNodeId)
		{
			auto result = std::vector<Id>();

			const auto paths = GetShortestPathsFromNode(graph, srcNodeId);

			if (!paths.empty() && paths.find(srcNodeId) != paths.cend() && paths.find(destNodeId) != paths.cend())
			{
				result.push_back(destNodeId);

				if (srcNodeId != destNodeId)
				{
					auto currNodeId = paths.at(destNodeId);

					while (currNodeId != srcNodeId && currNodeId != destNodeId)
					{
						result.push_back(currNodeId);
						currNodeId = paths.at(currNodeId);
					}

					if (currNodeId == srcNodeId)
					{
						result.push_back(srcNodeId);
						std::reverse(result.begin(), result.end());
					}
					else
					{
						result.clear();
					}
				}
			}

			return result;
		}
	}
}