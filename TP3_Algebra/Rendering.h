#pragma once

#include "raylib.h"
#include "Geometry.h"
#include "Polyhedron.h"

namespace ReyesCuadra
{
    void DrawPolyhedron(const Polyhedron& polyhedron, bool isSelected);

    void DrawPolyhedronNormals(const Polyhedron& polyhedron);

    void DrawAxisAlignedBox(const AxisAlignedBox& box, Color lineColor);
}
