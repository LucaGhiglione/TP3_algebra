#pragma once

#include "raylib.h"

namespace ReyesCuadra
{
    Vector3 AddVectors(Vector3 firstVector, Vector3 secondVector);

    Vector3 SubtractVectors(Vector3 firstVector, Vector3 secondVector);

    Vector3 ScaleVector(Vector3 vector, float scalar);

    Vector3 MultiplyComponents(Vector3 firstVector, Vector3 secondVector);

    float DotProduct(Vector3 firstVector, Vector3 secondVector);

    Vector3 CrossProduct(Vector3 firstVector, Vector3 secondVector);

    float VectorLength(Vector3 vector);

    Vector3 NormalizeVector(Vector3 vector);

    Vector3 RotateAroundX(Vector3 point, float angleRadians);
    Vector3 RotateAroundY(Vector3 point, float angleRadians);
    Vector3 RotateAroundZ(Vector3 point, float angleRadians);

    struct FacePlane
    {
        Vector3 normal;
        float distance;
    };

    FacePlane CreatePlaneFromPoints(Vector3 pointA, Vector3 pointB, Vector3 pointC);

    float SignedDistanceToPlane(const FacePlane& plane, Vector3 point);

    void FlipPlane(FacePlane& plane);

    struct AxisAlignedBox
    {
        Vector3 minCorner;
        Vector3 maxCorner;
    };

    bool AreBoxesOverlapping(const AxisAlignedBox& firstBox, const AxisAlignedBox& secondBox);

    AxisAlignedBox GetBoxIntersection(const AxisAlignedBox& firstBox, const AxisAlignedBox& secondBox);

    bool IsPointInsideBox(const AxisAlignedBox& box, Vector3 point);
}
