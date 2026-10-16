#include "CollisionGrid.h"

#include <cmath>

namespace ReyesCuadra
{
    CollisionGrid CreateCollisionGrid(Vector3 centerPoint, float sideLength, float pointSpacing)
    {
        CollisionGrid grid;
        grid.minCorner = { 0.0f, 0.0f, 0.0f };
        grid.pointSpacing = pointSpacing;
        grid.pointsPerAxis = 0;

        return grid;
    }

    Vector3 GetGridPoint(const CollisionGrid& grid, int indexX, int indexY, int indexZ)
    {
        return { 0.0f, 0.0f, 0.0f };
    }

    AxisAlignedBox GetGridBounds(const CollisionGrid& grid)
    {
        AxisAlignedBox gridBounds;
        gridBounds.minCorner = { 0.0f, 0.0f, 0.0f };
        gridBounds.maxCorner = { 0.0f, 0.0f, 0.0f };

        return gridBounds;
    }

    CollisionResult CheckPolyhedronCollision(const Polyhedron& firstPolyhedron, const Polyhedron& secondPolyhedron, const CollisionGrid& grid)
    {
        CollisionResult collisionResult;
        collisionResult.areBoxesOverlapping = false;
        collisionResult.areModelsColliding = false;
        collisionResult.sharedGridPoint = { 0.0f, 0.0f, 0.0f };

        return collisionResult;
    }

    void CollectSharedGridPoints(const Polyhedron& firstPolyhedron, const Polyhedron& secondPolyhedron, const CollisionGrid& grid, std::vector<Vector3>& sharedPoints, int maxPointCount)
    {
    }
}
