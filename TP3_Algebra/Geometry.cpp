#include "Geometry.h"

#include <cmath>

namespace ReyesCuadra
{
    Vector3 AddVectors(Vector3 firstVector, Vector3 secondVector)
    {
        return { firstVector.x + secondVector.x, firstVector.y + secondVector.y, firstVector.z + secondVector.z };
    }

    Vector3 SubtractVectors(Vector3 firstVector, Vector3 secondVector)
    {
        return { firstVector.x - secondVector.x, firstVector.y - secondVector.y, firstVector.z - secondVector.z };
    }

    Vector3 ScaleVector(Vector3 vector, float scalar)
    {
        return { vector.x * scalar, vector.y * scalar, vector.z * scalar };
    }

    Vector3 MultiplyComponents(Vector3 firstVector, Vector3 secondVector)
    {
        return { firstVector.x * secondVector.x, firstVector.y * secondVector.y, firstVector.z * secondVector.z };
    }

    float DotProduct(Vector3 firstVector, Vector3 secondVector)
    {
        return firstVector.x * secondVector.x + firstVector.y * secondVector.y + firstVector.z * secondVector.z;
    }

    Vector3 CrossProduct(Vector3 firstVector, Vector3 secondVector)
    {
        return
        {
            firstVector.y * secondVector.z - firstVector.z * secondVector.y,
            firstVector.z * secondVector.x - firstVector.x * secondVector.z,
            firstVector.x * secondVector.y - firstVector.y * secondVector.x
        };
    }

    float VectorLength(Vector3 vector)
    {
        return std::sqrt(DotProduct(vector, vector));
    }

    Vector3 NormalizeVector(Vector3 vector)
    {
        float vectorLength = VectorLength(vector);

        if (vectorLength <= 0.0f)
        {
            return { 0.0f, 0.0f, 0.0f };
        }

        return ScaleVector(vector, 1.0f / vectorLength);
    }

    Vector3 RotateAroundX(Vector3 point, float angleRadians)
    {
        float cosine = std::cos(angleRadians);
        float sine = std::sin(angleRadians);

        return { point.x, point.y * cosine - point.z * sine, point.y * sine + point.z * cosine };
    }

    Vector3 RotateAroundY(Vector3 point, float angleRadians)
    {
        float cosine = std::cos(angleRadians);
        float sine = std::sin(angleRadians);

        return { point.x * cosine + point.z * sine, point.y, -point.x * sine + point.z * cosine };
    }

    Vector3 RotateAroundZ(Vector3 point, float angleRadians)
    {
        float cosine = std::cos(angleRadians);
        float sine = std::sin(angleRadians);

        return { point.x * cosine - point.y * sine, point.x * sine + point.y * cosine, point.z };
    }

    FacePlane CreatePlaneFromPoints(Vector3 pointA, Vector3 pointB, Vector3 pointC)
    {
        FacePlane plane;
        plane.normal = { 0.0f, 0.0f, 0.0f };
        plane.distance = 0.0f;

        return plane;
    }

    float SignedDistanceToPlane(const FacePlane& plane, Vector3 point)
    {
        return 0.0f;
    }

    void FlipPlane(FacePlane& plane)
    {
    }

    bool AreBoxesOverlapping(const AxisAlignedBox& firstBox, const AxisAlignedBox& secondBox)
    {
        return false;
    }

    AxisAlignedBox GetBoxIntersection(const AxisAlignedBox& firstBox, const AxisAlignedBox& secondBox)
    {
        AxisAlignedBox intersectionBox;
        intersectionBox.minCorner = { 0.0f, 0.0f, 0.0f };
        intersectionBox.maxCorner = { 0.0f, 0.0f, 0.0f };

        return intersectionBox;
    }

    bool IsPointInsideBox(const AxisAlignedBox& box, Vector3 point)
    {
        return false;
    }
}
