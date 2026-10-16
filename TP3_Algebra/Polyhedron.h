#pragma once

#include <string>
#include <vector>

#include "raylib.h"
#include "Geometry.h"

namespace ReyesCuadra
{
    struct PolygonFace
    {
        std::vector<int> vertexIndices;
    };

    struct Polyhedron
    {
        std::string displayName;

        std::vector<Vector3> localVertices;
        std::vector<PolygonFace> faces;

        Vector3 position;
        Vector3 rotationDegrees;
        Vector3 scale;

        std::vector<Vector3> worldVertices;
        std::vector<FacePlane> facePlanes;
        Vector3 worldCenter;
        AxisAlignedBox boundingBox;

        Color baseColor;
        bool isColliding;
    };

    bool LoadPolyhedronFromObj(const std::string& filePath, Polyhedron& polyhedron);

    void UpdatePolyhedronWorldData(Polyhedron& polyhedron);

    bool IsPointInsidePolyhedron(const Polyhedron& polyhedron, Vector3 point);

    bool AreAllNormalsFacingCenter(const Polyhedron& polyhedron);

    Vector3 GetFaceCenter(const Polyhedron& polyhedron, int faceIndex);
}
