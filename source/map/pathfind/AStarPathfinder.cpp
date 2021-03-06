#include "map/pathfind/AStarPathfinder.h"
#include <glm/gtc/constants.hpp>

namespace Seed {

AStarPathfinder::AStarPathfinder(bool isDiagonalAllowed, bool isCornerCrossable, u32 weight, u32 colliderTileId, MapLayerTiled *mapBackground)
	: pStartNode(nullptr)
{
	bIsDiagonalAllowed = isDiagonalAllowed;
	bIsCornerCrossable = isCornerCrossable;
	iWeight = weight;
	iColliderTileId = colliderTileId;
	pMapBackground = mapBackground;
}

AStarPathfinder::~AStarPathfinder()
{
	this->Destroy();
}

void AStarPathfinder::Destroy()
{
	for (auto obj : vOpen)
		sdDelete(obj);

	for (auto obj : vClose)
		sdDelete(obj);

	TileNodeVector().swap(vOpen);
	TileNodeVector().swap(vClose);

	pStartNode = nullptr;
}

Path &AStarPathfinder::FindPath(const vec3 &start, const vec3 &end, Path &path)
{
	// The initial node must be zero for g and f
	pStartNode = sdNew(TileNode);
	pStartNode->cPos = start;

	// Push the start node into the open list
	vOpen.push_back(pStartNode);

	// While the open list is not empty
	while (!vOpen.empty())
	{
		// Get the current tilenode (the minimum 'f' value)
		auto current = *vOpen.begin();

		// Remove from open list and add to the close list
		vOpen.erase(vOpen.begin());
		vClose.push_back(current);

		// If reached the end position, construct the path and return it
		if ( ((ceil(current->cPos.x) <= end.x + iWeight/2) && (ceil(current->cPos.x) >= end.x - iWeight/2))
			&& ((ceil(current->cPos.y) <= end.y + iWeight/2) && (ceil(current->cPos.y) >= end.y - iWeight/2)) )
		{
			auto step = current;

			// Push each tile pos into the steps stack
			while (step->cPos.x != start.x || step->cPos.y != start.y)
			{
				path.AppendPositionStep(step->cPos);
				path.AppendDirectionStep(step->cDir);
				step = step->parent;
			}
			path.AppendPositionStep(start);

			vOpen.clear();
			vClose.clear();
			return path;
		}

		// Get neigbours of the current node
		this->GetNeigboursAtTile(*current);

		for (u32 i = 0; i < vNeighbors.size(); ++i)
		{
			auto neighbor = vNeighbors.at(i);

			if (this->CheckCloseNeighborByTilePos(neighbor->cPos))
				continue;

			// Get the distance between current node and the neighbor
			// and calculate the next g score
			auto ng = current->uG;
			if ((neighbor->cPos.x - current->cPos.x == iWeight) && neighbor->cPos.y - current->cPos.y == iWeight)
				ng = current->uG + glm::root_two<f32>();
			else
				ng = current->uG + 1;

			// Check if the neighbor has not been inspected yet, or
			// can be reached with smaller cost from the current node
			if (!this->CheckOpenNeighborByTilePos(neighbor->cPos) || ng < neighbor->uG)
			{
				neighbor->uG = ng;
				neighbor->uH = 1 * Heuristic::Manhattan(abs(ceil(neighbor->cPos.x - end.x)), abs(ceil(neighbor->cPos.y - end.y)));
				neighbor->uF = neighbor->uG + neighbor->uH;
				neighbor->parent = current;

				if (!this->CheckOpenNeighborByTilePos(neighbor->cPos))
				{
					vOpen.push_back(neighbor);
				}
				else
				{
					// the neighbor can be reached with smaller cost.
					// Since its f value has been updated, we have to
					// update its position in the open list
					auto f = FindNeighborByTilePos(neighbor->cPos);
					auto it = std::find_if(vOpen.begin(), vOpen.end(), [&f](const TileNode *t) { return f(t); }); // HACK thanks VS2013, best compiler evarrr!!
					auto &newNeighbor = *it;
					newNeighbor = neighbor;
				}
			}
		}
		// Sort based on 'f' value
		std::sort(vOpen.begin(), vOpen.end(), TileNodeAscendingPrioritySort());
	}

	// Fail to find the path
	return path;
}

bool AStarPathfinder::CheckOpenNeighborByTilePos(const vec3 &pos)
{
	auto f = FindNeighborByTilePos(pos);
	TileNodeVectorIterator it = std::find_if (vOpen.begin(), vOpen.end(), [&f](const TileNode *t) { return f(t); }); // HACK thanks VS2013, I reaally love you _|_ !!
	return (it != vOpen.end());
}

bool AStarPathfinder::CheckCloseNeighborByTilePos(const vec3 &pos)
{
	auto f = FindNeighborByTilePos(pos);
	TileNodeVectorIterator it = std::find_if (vClose.begin(), vClose.end(), [&f](const TileNode *t) { return f(t); }); // HACK thanks VS2013, forevar!!
	return (it != vClose.end());
}

}
