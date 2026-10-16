#pragma once

#include <vector>

#include "raylib.h"
#include "Geometry.h"
#include "Polyhedron.h"

namespace ReyesCuadra
{
    struct CollisionGrid
    {
        Vector3 minCorner;
        float pointSpacing;
        int pointsPerAxis;
    };

    struct CollisionResult
    {
        bool areBoxesOverlapping;
        bool areModelsColliding;
        Vector3 sharedGridPoint;
    };

    CollisionGrid CreateCollisionGrid(Vector3 centerPoint, float sideLength, float pointSpacing);

    Vector3 GetGridPoint(const CollisionGrid& grid, int indexX, int indexY, int indexZ);

    AxisAlignedBox GetGridBounds(const CollisionGrid& grid);

    CollisionResult CheckPolyhedronCollision(const Polyhedron& firstPolyhedron, const Polyhedron& secondPolyhedron, const CollisionGrid& grid);

    void CollectSharedGridPoints(const Polyhedron& firstPolyhedron, const Polyhedron& secondPolyhedron, const CollisionGrid& grid, std::vector<Vector3>& sharedPoints, int maxPointCount);
}
