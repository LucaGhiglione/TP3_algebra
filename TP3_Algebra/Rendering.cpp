#include "Rendering.h"

namespace ReyesCuadra
{
    const Vector3 LIGHT_DIRECTION = { 0.4f, 0.8f, 0.3f };

    const float NORMAL_DRAW_LENGTH = 0.35f;

    static const Color COLLIDING_COLOR = { 230, 60, 60, 255 };
    static const Color EDGE_COLOR = { 30, 30, 30, 255 };
    static const Color SELECTED_EDGE_COLOR = { 255, 220, 40, 255 };
    static const Color NORMAL_COLOR = { 90, 200, 255, 255 };

    static Color ApplyBrightness(Color originalColor, float brightness)
    {
        return
        {
            static_cast<unsigned char>(originalColor.r * brightness),
            static_cast<unsigned char>(originalColor.g * brightness),
            static_cast<unsigned char>(originalColor.b * brightness),
            originalColor.a
        };
    }

    void DrawPolyhedron(const Polyhedron& polyhedron, bool isSelected)
    {
        Color faceColor = polyhedron.isColliding ? COLLIDING_COLOR : polyhedron.baseColor;
        Vector3 lightDirection = NormalizeVector(LIGHT_DIRECTION);

        int faceCount = static_cast<int>(polyhedron.faces.size());

        for (int faceIndex = 0; faceIndex < faceCount; faceIndex++)
        {
            const PolygonFace& face = polyhedron.faces[faceIndex];

            bool hasFacePlane = faceIndex < static_cast<int>(polyhedron.facePlanes.size());
            Vector3 outwardNormal = { 0.0f, 0.0f, 0.0f };

            if (hasFacePlane)
            {
                outwardNormal = ScaleVector(polyhedron.facePlanes[faceIndex].normal, -1.0f);
            }

            float lightAmount = DotProduct(outwardNormal, lightDirection);
            if (lightAmount < 0.0f) lightAmount = 0.0f;

            float brightness = 0.35f + 0.65f * lightAmount;

            Color shadedColor = ApplyBrightness(faceColor, brightness);

            Vector3 fanOrigin = polyhedron.worldVertices[face.vertexIndices[0]];
            int faceVertexCount = static_cast<int>(face.vertexIndices.size());

            for (int fanIndex = 1; fanIndex < faceVertexCount - 1; fanIndex++)
            {
                Vector3 secondVertex = polyhedron.worldVertices[face.vertexIndices[fanIndex]];
                Vector3 thirdVertex = polyhedron.worldVertices[face.vertexIndices[fanIndex + 1]];

                Vector3 triangleNormal = CrossProduct(SubtractVectors(secondVertex, fanOrigin), SubtractVectors(thirdVertex, fanOrigin));

                if (!hasFacePlane)
                {
                    DrawTriangle3D(fanOrigin, secondVertex, thirdVertex, shadedColor);
                    DrawTriangle3D(fanOrigin, thirdVertex, secondVertex, shadedColor);
                }
                else if (DotProduct(triangleNormal, outwardNormal) < 0.0f)
                {
                    DrawTriangle3D(fanOrigin, thirdVertex, secondVertex, shadedColor);
                }
                else
                {
                    DrawTriangle3D(fanOrigin, secondVertex, thirdVertex, shadedColor);
                }
            }

            Color edgeColor = isSelected ? SELECTED_EDGE_COLOR : EDGE_COLOR;

            for (int edgeIndex = 0; edgeIndex < faceVertexCount; edgeIndex++)
            {
                Vector3 edgeStart = polyhedron.worldVertices[face.vertexIndices[edgeIndex]];
                Vector3 edgeEnd = polyhedron.worldVertices[face.vertexIndices[(edgeIndex + 1) % faceVertexCount]];
                DrawLine3D(edgeStart, edgeEnd, edgeColor);
            }
        }
    }

    void DrawPolyhedronNormals(const Polyhedron& polyhedron)
    {
        int faceCount = static_cast<int>(polyhedron.facePlanes.size());

        for (int faceIndex = 0; faceIndex < faceCount; faceIndex++)
        {
            Vector3 faceCenter = GetFaceCenter(polyhedron, faceIndex);
            Vector3 normalTip = AddVectors(faceCenter, ScaleVector(polyhedron.facePlanes[faceIndex].normal, NORMAL_DRAW_LENGTH));

            DrawLine3D(faceCenter, normalTip, NORMAL_COLOR);
            DrawCube(normalTip, 0.04f, 0.04f, 0.04f, NORMAL_COLOR);
        }

        DrawCube(polyhedron.worldCenter, 0.08f, 0.08f, 0.08f, NORMAL_COLOR);
    }

    void DrawAxisAlignedBox(const AxisAlignedBox& box, Color lineColor)
    {
        Vector3 minCorner = box.minCorner;
        Vector3 maxCorner = box.maxCorner;

        Vector3 corner000 = { minCorner.x, minCorner.y, minCorner.z };
        Vector3 corner100 = { maxCorner.x, minCorner.y, minCorner.z };
        Vector3 corner010 = { minCorner.x, maxCorner.y, minCorner.z };
        Vector3 corner110 = { maxCorner.x, maxCorner.y, minCorner.z };
        Vector3 corner001 = { minCorner.x, minCorner.y, maxCorner.z };
        Vector3 corner101 = { maxCorner.x, minCorner.y, maxCorner.z };
        Vector3 corner011 = { minCorner.x, maxCorner.y, maxCorner.z };
        Vector3 corner111 = { maxCorner.x, maxCorner.y, maxCorner.z };

        DrawLine3D(corner000, corner100, lineColor);
        DrawLine3D(corner100, corner101, lineColor);
        DrawLine3D(corner101, corner001, lineColor);
        DrawLine3D(corner001, corner000, lineColor);

        DrawLine3D(corner010, corner110, lineColor);
        DrawLine3D(corner110, corner111, lineColor);
        DrawLine3D(corner111, corner011, lineColor);
        DrawLine3D(corner011, corner010, lineColor);

        DrawLine3D(corner000, corner010, lineColor);
        DrawLine3D(corner100, corner110, lineColor);
        DrawLine3D(corner101, corner111, lineColor);
        DrawLine3D(corner001, corner011, lineColor);
    }
}
