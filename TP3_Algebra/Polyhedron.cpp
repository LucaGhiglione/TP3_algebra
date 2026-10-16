#include "Polyhedron.h"

#include <fstream>
#include <sstream>

namespace ReyesCuadra
{
    const float DEGREES_TO_RADIANS = 3.14159265f / 180.0f;
    const float INSIDE_TOLERANCE = 0.0001f;

    static int ParseVertexIndex(const std::string& faceToken, int loadedVertexCount)
    {
        size_t slashPosition = faceToken.find('/');
        std::string vertexPart = faceToken.substr(0, slashPosition);

        int objIndex = std::stoi(vertexPart);

        if (objIndex < 0)
        {
            return loadedVertexCount + objIndex;
        }

        return objIndex - 1;
    }

    bool LoadPolyhedronFromObj(const std::string& filePath, Polyhedron& polyhedron)
    {
        std::ifstream objFile(filePath);

        if (!objFile.is_open())
        {
            return false;
        }

        polyhedron.localVertices.clear();
        polyhedron.faces.clear();

        std::string fileLine;

        while (std::getline(objFile, fileLine))
        {
            std::istringstream lineStream(fileLine);
            std::string lineType;
            lineStream >> lineType;

            if (lineType == "v")
            {
                Vector3 vertexPosition = { 0.0f, 0.0f, 0.0f };
                lineStream >> vertexPosition.x >> vertexPosition.y >> vertexPosition.z;
                polyhedron.localVertices.push_back(vertexPosition);
            }
            else if (lineType == "f")
            {
                PolygonFace newFace;
                std::string faceToken;

                while (lineStream >> faceToken)
                {
                    int vertexIndex = ParseVertexIndex(faceToken, static_cast<int>(polyhedron.localVertices.size()));
                    newFace.vertexIndices.push_back(vertexIndex);
                }

                if (newFace.vertexIndices.size() >= 3)
                {
                    polyhedron.faces.push_back(newFace);
                }
            }
        }

        int vertexCount = static_cast<int>(polyhedron.localVertices.size());

        for (const PolygonFace& face : polyhedron.faces)
        {
            for (int vertexIndex : face.vertexIndices)
            {
                if (vertexIndex < 0 || vertexIndex >= vertexCount)
                {
                    return false;
                }
            }
        }

        polyhedron.position = { 0.0f, 0.0f, 0.0f };
        polyhedron.rotationDegrees = { 0.0f, 0.0f, 0.0f };
        polyhedron.scale = { 1.0f, 1.0f, 1.0f };
        polyhedron.isColliding = false;

        return vertexCount > 0 && !polyhedron.faces.empty();
    }

    void UpdatePolyhedronWorldData(Polyhedron& polyhedron)
    {
        polyhedron.worldVertices = polyhedron.localVertices;
        polyhedron.worldCenter = { 0.0f, 0.0f, 0.0f };
        polyhedron.boundingBox.minCorner = { 0.0f, 0.0f, 0.0f };
        polyhedron.boundingBox.maxCorner = { 0.0f, 0.0f, 0.0f };
        polyhedron.facePlanes.clear();
    }

    bool IsPointInsidePolyhedron(const Polyhedron& polyhedron, Vector3 point)
    {
        return false;
    }

    bool AreAllNormalsFacingCenter(const Polyhedron& polyhedron)
    {
        return false;
    }

    Vector3 GetFaceCenter(const Polyhedron& polyhedron, int faceIndex)
    {
        const PolygonFace& face = polyhedron.faces[faceIndex];
        Vector3 vertexSum = { 0.0f, 0.0f, 0.0f };

        for (int vertexIndex : face.vertexIndices)
        {
            vertexSum = AddVectors(vertexSum, polyhedron.worldVertices[vertexIndex]);
        }

        return ScaleVector(vertexSum, 1.0f / static_cast<float>(face.vertexIndices.size()));
    }
}
