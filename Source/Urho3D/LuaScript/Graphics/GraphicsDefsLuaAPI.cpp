//
// Copyright (c) 2008-2016 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "../../Precompiled.h"

#include "../../Graphics/GraphicsDefs.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterGraphicsDefs(kaguya::State& lua)
{
    using namespace kaguya;

    // [Enum] PrimitiveType
    // [Variable] TRIANGLE_LIST
    lua["TRIANGLE_LIST"] = TRIANGLE_LIST;
    // [Variable] LINE_LIST,
    lua["LINE_LIST"] = LINE_LIST;
    // [Variable] POINT_LIST,
    lua["POINT_LIST"] = POINT_LIST;
    // [Variable] TRIANGLE_STRIP,
    lua["TRIANGLE_STRIP"] = TRIANGLE_STRIP;
    // [Variable] LINE_STRIP,
    lua["LINE_STRIP"] = LINE_STRIP;
    // [Variable] TRIANGLE_FAN
    lua["TRIANGLE_FAN"] = TRIANGLE_FAN;

    // [Enum] GeometryType
    // [Variable] GEOM_STATIC
    lua["GEOM_STATIC"] = GEOM_STATIC;
    // [Variable] GEOM_SKINNED
    lua["GEOM_SKINNED"] = GEOM_SKINNED;
    // [Variable] GEOM_INSTANCED
    lua["GEOM_INSTANCED"] = GEOM_INSTANCED;
    // [Variable] GEOM_BILLBOARD
    lua["GEOM_BILLBOARD"] = GEOM_BILLBOARD;
    // [Variable] GEOM_DIRBILLBOARD
    lua["GEOM_DIRBILLBOARD"] = GEOM_DIRBILLBOARD;
    // [Variable] GEOM_TRAIL_FACE_CAMERA
    lua["GEOM_TRAIL_FACE_CAMERA"] = GEOM_TRAIL_FACE_CAMERA;
    // [Variable] GEOM_TRAIL_BONE
    lua["GEOM_TRAIL_BONE"] = GEOM_TRAIL_BONE;
    // [Variable] GEOM_STATIC_NOINSTANCING
    lua["GEOM_STATIC_NOINSTANCING"] = GEOM_STATIC_NOINSTANCING;
    // [Variable] MAX_GEOMETRYTYPES
    lua["MAX_GEOMETRYTYPES"] = MAX_GEOMETRYTYPES;

    // [Enum] BlendMode
    // [Variable] BLEND_REPLACE
    lua["BLEND_REPLACE"] = BLEND_REPLACE;
    // [Variable] BLEND_ADD,
    lua["BLEND_ADD"] = BLEND_ADD;
    // [Variable] BLEND_MULTIPLY,
    lua["BLEND_MULTIPLY"] = BLEND_MULTIPLY;
    // [Variable] BLEND_ALPHA,
    lua["BLEND_ALPHA"] = BLEND_ALPHA;
    // [Variable] BLEND_ADDALPHA,
    lua["BLEND_ADDALPHA"] = BLEND_ADDALPHA;
    // [Variable] BLEND_PREMULALPHA,
    lua["BLEND_PREMULALPHA"] = BLEND_PREMULALPHA;
    // [Variable] BLEND_INVDESTALPHA,
    lua["BLEND_INVDESTALPHA"] = BLEND_INVDESTALPHA;
    // [Variable] BLEND_SUBTRACT,
    lua["BLEND_SUBTRACT"] = BLEND_SUBTRACT;
    // [Variable] BLEND_SUBTRACTALPHA,
    lua["BLEND_SUBTRACTALPHA"] = BLEND_SUBTRACTALPHA;
    // [Variable] MAX_BLENDMODES
    lua["MAX_BLENDMODES"] = MAX_BLENDMODES;

    // [Enum] CompareMode
    // [Variable] CMP_ALWAYS
    lua["CMP_ALWAYS"] = CMP_ALWAYS;
    // [Variable] CMP_EQUAL,
    lua["CMP_EQUAL"] = CMP_EQUAL;
    // [Variable] CMP_NOTEQUAL,
    lua["CMP_NOTEQUAL"] = CMP_NOTEQUAL;
    // [Variable] CMP_LESS,
    lua["CMP_LESS"] = CMP_LESS;
    // [Variable] CMP_LESSEQUAL,
    lua["CMP_LESSEQUAL"] = CMP_LESSEQUAL;
    // [Variable] CMP_GREATER,
    lua["CMP_GREATER"] = CMP_GREATER;
    // [Variable] CMP_GREATEREQUAL,
    lua["CMP_GREATEREQUAL"] = CMP_GREATEREQUAL;
    // [Variable] MAX_COMPAREMODES
    lua["MAX_COMPAREMODES"] = MAX_COMPAREMODES;

    // [Enum] CullMode
    // [Variable] CULL_NONE
    lua["CULL_NONE"] = CULL_NONE;
    // [Variable] CULL_CCW,
    lua["CULL_CCW"] = CULL_CCW;
    // [Variable] CULL_CW,
    lua["CULL_CW"] = CULL_CW;
    // [Variable] MAX_CULLMODES
    lua["MAX_CULLMODES"] = MAX_CULLMODES;

    // [Enum] FillMode
    // [Variable] FILL_SOLID
    lua["FILL_SOLID"] = FILL_SOLID;
    // [Variable] FILL_WIREFRAME,
    lua["FILL_WIREFRAME"] = FILL_WIREFRAME;
    // [Variable] FILL_POINT
    lua["FILL_POINT"] = FILL_POINT;

    // [Enum] StencilOp
    // [Variable] OP_KEEP
    lua["OP_KEEP"] = OP_KEEP;
    // [Variable] OP_ZERO,
    lua["OP_ZERO"] = OP_ZERO;
    // [Variable] OP_REF,
    lua["OP_REF"] = OP_REF;
    // [Variable] OP_INCR,
    lua["OP_INCR"] = OP_INCR;
    // [Variable] OP_DECR
    lua["OP_DECR"] = OP_DECR;

    // [Enum] LockState
    // [Variable] LOCK_NONE
    lua["LOCK_NONE"] = LOCK_NONE;
    // [Variable] LOCK_HARDWARE,
    lua["LOCK_HARDWARE"] = LOCK_HARDWARE;
    // [Variable] LOCK_SHADOW,
    lua["LOCK_SHADOW"] = LOCK_SHADOW;
    // [Variable] LOCK_SCRATCH
    lua["LOCK_SCRATCH"] = LOCK_SCRATCH;

    // [Enum] LegacyVertexElement
    // [Variable] ELEMENT_POSITION
    lua["ELEMENT_POSITION"] = ELEMENT_POSITION;
    // [Variable] ELEMENT_NORMAL,
    lua["ELEMENT_NORMAL"] = ELEMENT_NORMAL;
    // [Variable] ELEMENT_COLOR,
    lua["ELEMENT_COLOR"] = ELEMENT_COLOR;
    // [Variable] ELEMENT_TEXCOORD1,
    lua["ELEMENT_TEXCOORD1"] = ELEMENT_TEXCOORD1;
    // [Variable] ELEMENT_TEXCOORD2,
    lua["ELEMENT_TEXCOORD2"] = ELEMENT_TEXCOORD2;
    // [Variable] ELEMENT_CUBETEXCOORD1,
    lua["ELEMENT_CUBETEXCOORD1"] = ELEMENT_CUBETEXCOORD1;
    // [Variable] ELEMENT_CUBETEXCOORD2,
    lua["ELEMENT_CUBETEXCOORD2"] = ELEMENT_CUBETEXCOORD2;
    // [Variable] ELEMENT_TANGENT,
    lua["ELEMENT_TANGENT"] = ELEMENT_TANGENT;
    // [Variable] ELEMENT_BLENDWEIGHTS,
    lua["ELEMENT_BLENDWEIGHTS"] = ELEMENT_BLENDWEIGHTS;
    // [Variable] ELEMENT_BLENDINDICES,
    lua["ELEMENT_BLENDINDICES"] = ELEMENT_BLENDINDICES;
    // [Variable] ELEMENT_INSTANCEMATRIX1,
    lua["ELEMENT_INSTANCEMATRIX1"] = ELEMENT_INSTANCEMATRIX1;
    // [Variable] ELEMENT_INSTANCEMATRIX2,
    lua["ELEMENT_INSTANCEMATRIX2"] = ELEMENT_INSTANCEMATRIX2;
    // [Variable] ELEMENT_INSTANCEMATRIX3,
    lua["ELEMENT_INSTANCEMATRIX3"] = ELEMENT_INSTANCEMATRIX3;
    // [Variable] ELEMENT_OBJECTINDEX,
    lua["ELEMENT_OBJECTINDEX"] = ELEMENT_OBJECTINDEX;
    // [Variable] MAX_LEGACY_VERTEX_ELEMENTS
    lua["MAX_LEGACY_VERTEX_ELEMENTS"] = MAX_LEGACY_VERTEX_ELEMENTS;

    // [Enum] VertexElementType
    // [Variable] TYPE_INT
    lua["TYPE_INT"] = TYPE_INT;
    // [Variable] TYPE_FLOAT,
    lua["TYPE_FLOAT"] = TYPE_FLOAT;
    // [Variable] TYPE_VECTOR2,
    lua["TYPE_VECTOR2"] = TYPE_VECTOR2;
    // [Variable] TYPE_VECTOR3,
    lua["TYPE_VECTOR3"] = TYPE_VECTOR3;
    // [Variable] TYPE_VECTOR4,
    lua["TYPE_VECTOR4"] = TYPE_VECTOR4;
    // [Variable] TYPE_UBYTE4,
    lua["TYPE_UBYTE4"] = TYPE_UBYTE4;
    // [Variable] TYPE_UBYTE4_NORM,
    lua["TYPE_UBYTE4_NORM"] = TYPE_UBYTE4_NORM;
    // [Variable] MAX_VERTEX_ELEMENT_TYPES
    lua["MAX_VERTEX_ELEMENT_TYPES"] = MAX_VERTEX_ELEMENT_TYPES;

    // [Enum] VertexElementSemantic
    // [Variable] SEM_POSITION
    lua["SEM_POSITION"] = SEM_POSITION;
    // [Variable] SEM_NORMAL,
    lua["SEM_NORMAL"] = SEM_NORMAL;
    // [Variable] SEM_BINORMAL,
    lua["SEM_BINORMAL"] = SEM_BINORMAL;
    // [Variable] SEM_TANGENT,
    lua["SEM_TANGENT"] = SEM_TANGENT;
    // [Variable] SEM_TEXCOORD,
    lua["SEM_TEXCOORD"] = SEM_TEXCOORD;
    // [Variable] SEM_COLOR,
    lua["SEM_COLOR"] = SEM_COLOR;
    // [Variable] SEM_BLENDWEIGHTS,
    lua["SEM_BLENDWEIGHTS"] = SEM_BLENDWEIGHTS;
    // [Variable] SEM_BLENDINDICES,
    lua["SEM_BLENDINDICES"] = SEM_BLENDINDICES;
    // [Variable] SEM_OBJECTINDEX,
    lua["SEM_OBJECTINDEX"] = SEM_OBJECTINDEX;
    // [Variable] MAX_VERTEX_ELEMENT_SEMANTICS
    lua["MAX_VERTEX_ELEMENT_SEMANTICS"] = MAX_VERTEX_ELEMENT_SEMANTICS;

    // [Class] VertexElement
    lua["VertexElement"].setClass(UserdataMetatable<VertexElement>()
        .setConstructors<VertexElement(),
        VertexElement(VertexElementType, VertexElementSemantic), 
        VertexElement(VertexElementType, VertexElementSemantic, unsigned char), 
        VertexElement(VertexElementType, VertexElementSemantic, unsigned char, bool)>()

        .addFunction("__eq", &VertexElement::operator==)

        .addProperty("type", &VertexElement::type_)
        .addProperty("semantic", &VertexElement::semantic_)
        .addProperty("index", &VertexElement::index_)
        .addProperty("perInstance", &VertexElement::perInstance_)
        .addProperty("offset", &VertexElement::offset_)
    );

    // [Enum] TextureFilterMode
    // [Variable] FILTER_NEAREST
    lua["FILTER_NEAREST"] = FILTER_NEAREST;
    // [Variable] FILTER_BILINEAR,
    lua["FILTER_BILINEAR"] = FILTER_BILINEAR;
    // [Variable] FILTER_TRILINEAR,
    lua["FILTER_TRILINEAR"] = FILTER_TRILINEAR;
    // [Variable] FILTER_ANISOTROPIC,
    lua["FILTER_ANISOTROPIC"] = FILTER_ANISOTROPIC;
    // [Variable] FILTER_DEFAULT,
    lua["FILTER_DEFAULT"] = FILTER_DEFAULT;
    // [Variable] MAX_FILTERMODES
    lua["MAX_FILTERMODES"] = MAX_FILTERMODES;

    // [Enum] TextureAddressMode
    // [Variable] ADDRESS_WRAP
    lua["ADDRESS_WRAP"] = ADDRESS_WRAP;
    // [Variable] ADDRESS_MIRROR,
    lua["ADDRESS_MIRROR"] = ADDRESS_MIRROR;
    // [Variable] ADDRESS_CLAMP,
    lua["ADDRESS_CLAMP"] = ADDRESS_CLAMP;
    // [Variable] ADDRESS_BORDER,
    lua["ADDRESS_BORDER"] = ADDRESS_BORDER;
    // [Variable] MAX_ADDRESSMODES
    lua["MAX_ADDRESSMODES"] = MAX_ADDRESSMODES;

    // [Enum] TextureCoordinate
    // [Variable] COORD_U
    lua["COORD_U"] = COORD_U;
    // [Variable] COORD_V,
    lua["COORD_V"] = COORD_V;
    // [Variable] COORD_W,
    lua["COORD_W"] = COORD_W;
    // [Variable] MAX_COORDS
    lua["MAX_COORDS"] = MAX_COORDS;

    // [Enum] TextureUsage
    // [Variable] TEXTURE_STATIC
    lua["TEXTURE_STATIC"] = TEXTURE_STATIC;
    // [Variable] TEXTURE_DYNAMIC,
    lua["TEXTURE_DYNAMIC"] = TEXTURE_DYNAMIC;
    // [Variable] TEXTURE_RENDERTARGET,
    lua["TEXTURE_RENDERTARGET"] = TEXTURE_RENDERTARGET;
    // [Variable] TEXTURE_DEPTHSTENCIL
    lua["TEXTURE_DEPTHSTENCIL"] = TEXTURE_DEPTHSTENCIL;

    // [Enum] CubeMapFace
    // [Variable] FACE_POSITIVE_X
    lua["FACE_POSITIVE_X"] = FACE_POSITIVE_X;
    // [Variable] FACE_NEGATIVE_X,
    lua["FACE_NEGATIVE_X"] = FACE_NEGATIVE_X;
    // [Variable] FACE_POSITIVE_Y,
    lua["FACE_POSITIVE_Y"] = FACE_POSITIVE_Y;
    // [Variable] FACE_NEGATIVE_Y,
    lua["FACE_NEGATIVE_Y"] = FACE_NEGATIVE_Y;
    // [Variable] FACE_POSITIVE_Z,
    lua["FACE_POSITIVE_Z"] = FACE_POSITIVE_Z;
    // [Variable] FACE_NEGATIVE_Z,
    lua["FACE_NEGATIVE_Z"] = FACE_NEGATIVE_Z;
    // [Variable] MAX_CUBEMAP_FACES
    lua["MAX_CUBEMAP_FACES"] = MAX_CUBEMAP_FACES;

    // [Enum] CubeMapLayout
    // [Variable] CML_HORIZONTAL
    lua["CML_HORIZONTAL"] = CML_HORIZONTAL;
    // [Variable] CML_HORIZONTALNVIDIA,
    lua["CML_HORIZONTALNVIDIA"] = CML_HORIZONTALNVIDIA;
    // [Variable] CML_HORIZONTALCROSS,
    lua["CML_HORIZONTALCROSS"] = CML_HORIZONTALCROSS;
    // [Variable] CML_VERTICALCROSS,
    lua["CML_VERTICALCROSS"] = CML_VERTICALCROSS;
    // [Variable] CML_BLENDER
    lua["CML_BLENDER"] = CML_BLENDER;

    // [Enum] RenderSurfaceUpdateMode
    // [Variable] SURFACE_MANUALUPDATE
    lua["SURFACE_MANUALUPDATE"] = SURFACE_MANUALUPDATE;
    // [Variable] SURFACE_UPDATEVISIBLE,
    lua["SURFACE_UPDATEVISIBLE"] = SURFACE_UPDATEVISIBLE;
    // [Variable] SURFACE_UPDATEALWAYS
    lua["SURFACE_UPDATEALWAYS"] = SURFACE_UPDATEALWAYS;

    // [Enum] ShaderType
    // [Variable] VS
    lua["VS"] = VS;
    // [Variable] MAX_SHADER_PARAMETER_GROUPS
    lua["PS"] = PS;

    // [Enum] TextureUnit
    // [Variable] TU_DIFFUSE
    lua["TU_DIFFUSE"] = TU_DIFFUSE;
    // [Variable] TU_ALBEDOBUFFER
    lua["TU_ALBEDOBUFFER"] = TU_ALBEDOBUFFER;
    // [Variable] TU_NORMAL
    lua["TU_NORMAL"] = TU_NORMAL;
    // [Variable] TU_NORMALBUFFER
    lua["TU_NORMALBUFFER"] = TU_NORMALBUFFER;
    // [Variable] TU_SPECULAR
    lua["TU_SPECULAR"] = TU_SPECULAR;
    // [Variable] TU_EMISSIVE
    lua["TU_EMISSIVE"] = TU_EMISSIVE;
    // [Variable] TU_ENVIRONMENT
    lua["TU_ENVIRONMENT"] = TU_ENVIRONMENT;
    // lua["TU_VOLUMEMAP"] = TU_VOLUMEMAP;
    // lua["TU_CUSTOM1"] = TU_CUSTOM1;
    // lua["TU_CUSTOM2"] = TU_CUSTOM2;
    // lua["TU_LIGHTRAMP"] = TU_LIGHTRAMP;
    // lua["TU_LIGHTSHAPE"] = TU_LIGHTSHAPE;
    // lua["TU_SHADOWMAP"] = TU_SHADOWMAP;
    // lua["TU_FACESELECT"] = TU_FACESELECT;
    // lua["TU_INDIRECTION"] = TU_INDIRECTION;
    // lua["TU_DEPTHBUFFER"] = TU_DEPTHBUFFER;
    // lua["TU_LIGHTBUFFER"] = TU_LIGHTBUFFER;
    // lua["TU_ZONE"] = TU_ZONE;
    // lua["MAX_MATERIAL_TEXTURE_UNITS"] = MAX_MATERIAL_TEXTURE_UNITS;
    // lua["MAX_TEXTURE_UNITS"] = MAX_TEXTURE_UNITS;

    // [Enum] FaceCameraMode
    // [Variable] FC_NONE
    lua["FC_NONE"] = FC_NONE;
    // [Variable] FC_ROTATE_XYZ,
    lua["FC_ROTATE_XYZ"] = FC_ROTATE_XYZ;
    // [Variable] FC_ROTATE_Y,
    lua["FC_ROTATE_Y"] = FC_ROTATE_Y;
    // [Variable] FC_LOOKAT_XYZ,
    lua["FC_LOOKAT_XYZ"] = FC_LOOKAT_XYZ;
    // [Variable] FC_LOOKAT_Y,
    lua["FC_LOOKAT_Y"] = FC_LOOKAT_Y;
    // [Variable] FC_DIRECTION
    lua["FC_DIRECTION"] = FC_DIRECTION;

    // [Enum] ShadowQuality
    // [Variable] SHADOWQUALITY_SIMPLE_16BIT
    lua["SHADOWQUALITY_SIMPLE_16BIT"] = SHADOWQUALITY_SIMPLE_16BIT;
    // [Variable] SHADOWQUALITY_SIMPLE_24BIT,
    lua["SHADOWQUALITY_SIMPLE_24BIT"] = SHADOWQUALITY_SIMPLE_24BIT;
    // [Variable] SHADOWQUALITY_PCF_16BIT,
    lua["SHADOWQUALITY_PCF_16BIT"] = SHADOWQUALITY_PCF_16BIT;
    // [Variable] SHADOWQUALITY_PCF_24BIT,
    lua["SHADOWQUALITY_PCF_24BIT"] = SHADOWQUALITY_PCF_24BIT;
    // [Variable] SHADOWQUALITY_VSM,
    lua["SHADOWQUALITY_VSM"] = SHADOWQUALITY_VSM;
    // [Variable] SHADOWQUALITY_BLUR_VSM
    lua["SHADOWQUALITY_BLUR_VSM"] = SHADOWQUALITY_BLUR_VSM;

    // [Constant] int QUALITY_LOW
    lua["QUALITY_LOW"] = QUALITY_LOW;
    // [Constant] int QUALITY_MEDIUM
    lua["QUALITY_MEDIUM"] = QUALITY_MEDIUM;
    // [Constant] int QUALITY_HIGH
    lua["QUALITY_HIGH"] = QUALITY_HIGH;
    // [Constant] int QUALITY_MAX
    lua["QUALITY_MAX"] = QUALITY_MAX;

    // [Constant] unsigned CLEAR_COLOR
    lua["CLEAR_COLOR"] = CLEAR_COLOR;
    // [Constant] unsigned CLEAR_DEPTH
    lua["CLEAR_DEPTH"] = CLEAR_DEPTH;
    // [Constant] unsigned CLEAR_STENCIL
    lua["CLEAR_STENCIL"] = CLEAR_STENCIL;

    // [Constant] unsigned MASK_NONE
    lua["MASK_NONE"] = MASK_NONE;
    // [Constant] unsigned MASK_POSITION
    lua["MASK_POSITION"] = MASK_POSITION;
    // [Constant] unsigned MASK_NORMAL
    lua["MASK_NORMAL"] = MASK_NORMAL;
    // [Constant] unsigned MASK_COLOR
    lua["MASK_COLOR"] = MASK_COLOR;
    // [Constant] unsigned MASK_TEXCOORD1
    lua["MASK_TEXCOORD1"] = MASK_TEXCOORD1;
    // [Constant] unsigned MASK_TEXCOORD2
    lua["MASK_TEXCOORD2"] = MASK_TEXCOORD2;
    // [Constant] unsigned MASK_CUBETEXCOORD1
    lua["MASK_CUBETEXCOORD1"] = MASK_CUBETEXCOORD1;
    // [Constant] unsigned MASK_CUBETEXCOORD2
    lua["MASK_CUBETEXCOORD2"] = MASK_CUBETEXCOORD2;
    // [Constant] unsigned MASK_TANGENT
    lua["MASK_TANGENT"] = MASK_TANGENT;
    // [Constant] unsigned MASK_BLENDWEIGHTS
    lua["MASK_BLENDWEIGHTS"] = MASK_BLENDWEIGHTS;
    // [Constant] unsigned MASK_BLENDINDICES
    lua["MASK_BLENDINDICES"] = MASK_BLENDINDICES;
    // [Constant] unsigned MASK_INSTANCEMATRIX1
    lua["MASK_INSTANCEMATRIX1"] = MASK_INSTANCEMATRIX1;
    // [Constant] unsigned MASK_INSTANCEMATRIX2
    lua["MASK_INSTANCEMATRIX2"] = MASK_INSTANCEMATRIX2;
    // [Constant] unsigned MASK_INSTANCEMATRIX3
    lua["MASK_INSTANCEMATRIX3"] = MASK_INSTANCEMATRIX3;
    // [Constant] unsigned MASK_OBJECTINDEX
    lua["MASK_OBJECTINDEX"] = MASK_OBJECTINDEX;
}
}

