#pragma once
#include "hy3d_math.h"

typedef int32_t triangle_index;

static inline vec2 ConvertSkinToTextureCoord(f32 u, f32 v)
{
    return {u / 3.0f, v / 4.0f};
}

struct orientation
{
    f32 thetaX;
    f32 thetaY;
    f32 thetaZ;
};

struct mesh
{
    i32 nVertices;
    i32 nIndices;
    vertex *vertices;
    triangle_index *indices;
};

struct object
{
    vertex *vertices;
    i32 nVertices;
    bool hasNormals;
    loaded_bitmap *texture;
    material mat;
    orientation orientation;
    vec3 pos;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
// NOTE:  MY MODELS
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

struct cube
{
    mesh *mesh;
    orientation orientation;
    vec3 pos;
    f32 side;
};

struct square_plane
{
    mesh *mesh;
    orientation orientation;
    vec3 pos;
    f32 side;
    i32 divisions;
};

struct axis3d
{
    mesh *mesh;
    orientation orientation;
    vec3 pos;
    f32 length;
    i8 nLinesVertices = 6;
    i8 lines[6] = {
        0, 1,
        0, 2,
        0, 3};
    color colors[3] = {
        {255, 0, 0},
        {0, 255, 0},
        {0, 0, 255}};
};

static void LoadUnfoldedCubeMesh(mesh *mesh, f32 side)
{
    mesh->nVertices = 14;
    mesh->nIndices = 36;
    side /= 2.0f;

    mesh->vertices[0].pos = {-side, -side, -side}; // 0
    mesh->vertices[0].texCoord = {ConvertSkinToTextureCoord(1.0f, 3.0f)};
    mesh->vertices[1].pos = {side, -side, -side}; // 1
    mesh->vertices[1].texCoord = {ConvertSkinToTextureCoord(2.0f, 3.0f)};
    mesh->vertices[2].pos = {-side, side, -side}; // 2
    mesh->vertices[2].texCoord = {ConvertSkinToTextureCoord(1.0f, 4.0f)};
    mesh->vertices[3].pos = {side, side, -side}; // 3
    mesh->vertices[3].texCoord = {ConvertSkinToTextureCoord(2.0f, 4.0f)};
    mesh->vertices[4].pos = {-side, -side, side}; // 4
    mesh->vertices[4].texCoord = {ConvertSkinToTextureCoord(1.0f, 2.0f)};
    mesh->vertices[5].pos = {side, -side, side}; // 5
    mesh->vertices[5].texCoord = {ConvertSkinToTextureCoord(2.0f, 2.0f)};
    mesh->vertices[6].pos = {-side, side, side}; // 6
    mesh->vertices[6].texCoord = {ConvertSkinToTextureCoord(1.0f, 1.0f)};
    mesh->vertices[7].pos = {side, side, side}; // 7
    mesh->vertices[7].texCoord = {ConvertSkinToTextureCoord(2.0f, 1.0f)};
    mesh->vertices[8].pos = {-side, side, -side}; // 8
    mesh->vertices[8].texCoord = {ConvertSkinToTextureCoord(1.0f, 0.0f)};
    mesh->vertices[9].pos = {side, side, -side}; // 9
    mesh->vertices[9].texCoord = {ConvertSkinToTextureCoord(2.0f, 0.0f)};
    mesh->vertices[10].pos = {-side, side, side}; // 10
    mesh->vertices[10].texCoord = {ConvertSkinToTextureCoord(0.0f, 2.0f)};
    mesh->vertices[11].pos = {-side, side, -side}; // 11
    mesh->vertices[11].texCoord = {ConvertSkinToTextureCoord(0.0f, 3.0f)};
    mesh->vertices[12].pos = {side, side, side}; // 12
    mesh->vertices[12].texCoord = {ConvertSkinToTextureCoord(3.0f, 2.0f)};
    mesh->vertices[13].pos = {side, side, -side}; // 13
    mesh->vertices[13].texCoord = {ConvertSkinToTextureCoord(3.0f, 3.0f)};

    mesh->indices[0] = 0;
    mesh->indices[1] = 2;
    mesh->indices[2] = 1;
    mesh->indices[3] = 2;
    mesh->indices[4] = 3;
    mesh->indices[5] = 1;
    mesh->indices[6] = 4;
    mesh->indices[7] = 0;
    mesh->indices[8] = 5;
    mesh->indices[9] = 0;
    mesh->indices[10] = 1;
    mesh->indices[11] = 5;
    mesh->indices[12] = 6;
    mesh->indices[13] = 4;
    mesh->indices[14] = 7;
    mesh->indices[15] = 4;
    mesh->indices[16] = 5;
    mesh->indices[17] = 7;
    mesh->indices[18] = 8;
    mesh->indices[19] = 6;
    mesh->indices[20] = 9;
    mesh->indices[21] = 6;
    mesh->indices[22] = 7;
    mesh->indices[23] = 9;
    mesh->indices[24] = 10;
    mesh->indices[25] = 11;
    mesh->indices[26] = 4;
    mesh->indices[27] = 11;
    mesh->indices[28] = 0;
    mesh->indices[29] = 4;
    mesh->indices[30] = 5;
    mesh->indices[31] = 1;
    mesh->indices[32] = 12;
    mesh->indices[33] = 1;
    mesh->indices[34] = 13;
    mesh->indices[35] = 12;

    /*i8 lines[24] = {
        0, 1, 1, 3, 3, 2, 2, 0,
        0, 4, 1, 5, 3, 7, 2, 6,
        4, 5, 5, 7, 7, 6, 6, 4};*/
}

static cube MakeCubeUnfolded(mesh *mesh, orientation orientation, vec3 pos, f32 side)
{
    cube result;
    result.mesh = mesh;
    result.orientation = orientation;
    result.pos = pos;
    result.side = side;
    return result;
}

static void LoadSquarePlaneMesh(mesh *mesh, f32 side, i32 divisions)
{
    f32 posStep = side / (f32)(divisions);
    f32 texStep = 1.0f / (f32)(divisions);

    // Start at bottom left and map texture to vertices
    vec3 pos = {-side / 2.0f, -side / 2.0f, 0.0f};
    vec2 texCoord = {};
    for (i32 row = 0; row <= divisions; row++)
    {
        for (i32 col = 0; col <= divisions; col++)
        {
            u32 i = row * divisions + row + col;
            mesh->vertices[i].pos = pos;
            mesh->vertices[i].texCoord = texCoord;
            mesh->vertices[i].normal = {0.0f, 0.0f, -1.0f};
            pos.x += posStep;
            texCoord.x += texStep;
        }
        pos.x = -side / 2.0f;
        pos.y = (f32)(row + 1) * posStep - side / 2.0f;

        texCoord.x = 0.0f;
        texCoord.y = (f32)(row + 1) * texStep;
    }

    // Initialize triangle index list
    i32 ti = 0;
    i32 vi = 0;
    i32 row = 0;
    while ((ti + 5 < mesh->nIndices) && (vi + divisions + 2 < mesh->nVertices))
    {
        mesh->indices[ti] = vi;
        mesh->indices[ti + 1] = vi + divisions + 1;
        mesh->indices[ti + 2] = vi + 1;
        ti += 3;

        mesh->indices[ti] = vi + divisions + 1;
        mesh->indices[ti + 1] = vi + divisions + 2;
        mesh->indices[ti + 2] = vi + 1;
        ti += 3;
        vi++;
        if (vi % divisions == row)
        {
            vi++;
            row++;
        }
    }
}

static square_plane MakeSquarePlane(mesh *mesh, orientation orientation, vec3 pos, f32 side, i32 divisions)
{
    square_plane result;
    result.mesh = mesh;
    result.orientation = orientation;
    result.pos = pos;
    result.side = side;
    result.divisions = divisions;
    return result;
}

static void LoadAxis3DMesh(mesh *mesh, f32 length)
{
    mesh->vertices[0].pos = {};
    mesh->vertices[1].pos = {length, 0.0f, 0.0f};
    mesh->vertices[2].pos = {0.0f, length, 0.0f};
    mesh->vertices[3].pos = {0.0f, 0.0f, length};
}
