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
    lua["TRIANGLE_LIST"] = TRIANGLE_LIST;
    lua["LINE_LIST"] = LINE_LIST;
    lua["POINT_LIST"] = POINT_LIST;
    lua["TRIANGLE_STRIP"] = TRIANGLE_STRIP;
    lua["LINE_STRIP"] = LINE_STRIP;
    lua["TRIANGLE_FAN"] = TRIANGLE_FAN;

    // [Enum] GeometryType
    lua["GEOM_STATIC"] = GEOM_STATIC;
    lua["GEOM_SKINNED"] = GEOM_SKINNED;
    lua["GEOM_INSTANCED"] = GEOM_INSTANCED;
    lua["GEOM_BILLBOARD"] = GEOM_BILLBOARD;
    lua["GEOM_DIRBILLBOARD"] = GEOM_DIRBILLBOARD;
    lua["GEOM_TRAIL_FACE_CAMERA"] = GEOM_TRAIL_FACE_CAMERA;
    lua["GEOM_TRAIL_BONE"] = GEOM_TRAIL_BONE;
    lua["GEOM_STATIC_NOINSTANCING"] = GEOM_STATIC_NOINSTANCING;
    lua["MAX_GEOMETRYTYPES"] = MAX_GEOMETRYTYPES;

    // [Enum] BlendMode
    lua["BLEND_REPLACE"] = BLEND_REPLACE;
    lua["BLEND_ADD"] = BLEND_ADD;
    lua["BLEND_MULTIPLY"] = BLEND_MULTIPLY;
    lua["BLEND_ALPHA"] = BLEND_ALPHA;
    lua["BLEND_ADDALPHA"] = BLEND_ADDALPHA;
    lua["BLEND_PREMULALPHA"] = BLEND_PREMULALPHA;
    lua["BLEND_INVDESTALPHA"] = BLEND_INVDESTALPHA;
    lua["BLEND_SUBTRACT"] = BLEND_SUBTRACT;
    lua["BLEND_SUBTRACTALPHA"] = BLEND_SUBTRACTALPHA;
    lua["MAX_BLENDMODES"] = MAX_BLENDMODES;

    // [Enum] CompareMode
    lua["CMP_ALWAYS"] = CMP_ALWAYS;
    lua["CMP_EQUAL"] = CMP_EQUAL;
    lua["CMP_NOTEQUAL"] = CMP_NOTEQUAL;
    lua["CMP_LESS"] = CMP_LESS;
    lua["CMP_LESSEQUAL"] = CMP_LESSEQUAL;
    lua["CMP_GREATER"] = CMP_GREATER;
    lua["CMP_GREATEREQUAL"] = CMP_GREATEREQUAL;
    lua["MAX_COMPAREMODES"] = MAX_COMPAREMODES;

    // [Enum] CullMode
    lua["CULL_NONE"] = CULL_NONE;
    lua["CULL_CCW"] = CULL_CCW;
    lua["CULL_CW"] = CULL_CW;
    lua["MAX_CULLMODES"] = MAX_CULLMODES;

    // [Enum] FillMode
    lua["FILL_SOLID"] = FILL_SOLID;
    lua["FILL_WIREFRAME"] = FILL_WIREFRAME;
    lua["FILL_POINT"] = FILL_POINT;

    // [Enum] StencilOp
    lua["OP_KEEP"] = OP_KEEP;
    lua["OP_ZERO"] = OP_ZERO;
    lua["OP_REF"] = OP_REF;
    lua["OP_INCR"] = OP_INCR;
    lua["OP_DECR"] = OP_DECR;

    // [Enum] LockState
    lua["LOCK_NONE"] = LOCK_NONE;
    lua["LOCK_HARDWARE"] = LOCK_HARDWARE;
    lua["LOCK_SHADOW"] = LOCK_SHADOW;
    lua["LOCK_SCRATCH"] = LOCK_SCRATCH;

    // [Enum] LegacyVertexElement
    lua["ELEMENT_POSITION"] = ELEMENT_POSITION;
    lua["ELEMENT_NORMAL"] = ELEMENT_NORMAL;
    lua["ELEMENT_COLOR"] = ELEMENT_COLOR;
    lua["ELEMENT_TEXCOORD1"] = ELEMENT_TEXCOORD1;
    lua["ELEMENT_TEXCOORD2"] = ELEMENT_TEXCOORD2;
    lua["ELEMENT_CUBETEXCOORD1"] = ELEMENT_CUBETEXCOORD1;
    lua["ELEMENT_CUBETEXCOORD2"] = ELEMENT_CUBETEXCOORD2;
    lua["ELEMENT_TANGENT"] = ELEMENT_TANGENT;
    lua["ELEMENT_BLENDWEIGHTS"] = ELEMENT_BLENDWEIGHTS;
    lua["ELEMENT_BLENDINDICES"] = ELEMENT_BLENDINDICES;
    lua["ELEMENT_INSTANCEMATRIX1"] = ELEMENT_INSTANCEMATRIX1;
    lua["ELEMENT_INSTANCEMATRIX2"] = ELEMENT_INSTANCEMATRIX2;
    lua["ELEMENT_INSTANCEMATRIX3"] = ELEMENT_INSTANCEMATRIX3;
    lua["ELEMENT_OBJECTINDEX"] = ELEMENT_OBJECTINDEX;
    lua["MAX_LEGACY_VERTEX_ELEMENTS"] = MAX_LEGACY_VERTEX_ELEMENTS;

    // [Enum] VertexElementType
    lua["TYPE_INT"] = TYPE_INT;
    lua["TYPE_FLOAT"] = TYPE_FLOAT;
    lua["TYPE_VECTOR2"] = TYPE_VECTOR2;
    lua["TYPE_VECTOR3"] = TYPE_VECTOR3;
    lua["TYPE_VECTOR4"] = TYPE_VECTOR4;
    lua["TYPE_UBYTE4"] = TYPE_UBYTE4;
    lua["TYPE_UBYTE4_NORM"] = TYPE_UBYTE4_NORM;
    lua["MAX_VERTEX_ELEMENT_TYPES"] = MAX_VERTEX_ELEMENT_TYPES;

    // [Enum] VertexElementSemantic
    lua["SEM_POSITION"] = SEM_POSITION;
    lua["SEM_NORMAL"] = SEM_NORMAL;
    lua["SEM_BINORMAL"] = SEM_BINORMAL;
    lua["SEM_TANGENT"] = SEM_TANGENT;
    lua["SEM_TEXCOORD"] = SEM_TEXCOORD;
    lua["SEM_COLOR"] = SEM_COLOR;
    lua["SEM_BLENDWEIGHTS"] = SEM_BLENDWEIGHTS;
    lua["SEM_BLENDINDICES"] = SEM_BLENDINDICES;
    lua["SEM_OBJECTINDEX"] = SEM_OBJECTINDEX;
    lua["MAX_VERTEX_ELEMENT_SEMANTICS"] = MAX_VERTEX_ELEMENT_SEMANTICS;

    // [Class] VertexElement
    lua["VertexElement"].setClass(UserdataMetatable<VertexElement>()
        // [Constructor] VertexElement()
        .setConstructors<VertexElement(),
        // [Constructor] VertexElement(VertexElementType type, VertexElementSemantic semantic, unsigned char index = 0, bool perInstance = false)
        VertexElement(VertexElementType, VertexElementSemantic), 
        VertexElement(VertexElementType, VertexElementSemantic, unsigned char), 
        VertexElement(VertexElementType, VertexElementSemantic, unsigned char, bool)>()

        // [Method] bool operator==(const VertexElement& rhs) const
        .addFunction("__eq", &VertexElement::operator==)

        // [Field] VertexElementType type
        .addProperty("type", &VertexElement::type_)
        // [Field]  VertexElementSemantic semantic
        .addProperty("semantic", &VertexElement::semantic_)
        // [Field]  unsigned char index
        .addProperty("index", &VertexElement::index_)
        // [Field]  bool perInstance
        .addProperty("perInstance", &VertexElement::perInstance_)
        // [Field] unsigned offset
        .addProperty("offset", &VertexElement::offset_)
    );

    // [Enum] TextureFilterMode
    lua["FILTER_NEAREST"] = FILTER_NEAREST;
    lua["FILTER_BILINEAR"] = FILTER_BILINEAR;
    lua["FILTER_TRILINEAR"] = FILTER_TRILINEAR;
    lua["FILTER_ANISOTROPIC"] = FILTER_ANISOTROPIC;
    lua["FILTER_DEFAULT"] = FILTER_DEFAULT;
    lua["MAX_FILTERMODES"] = MAX_FILTERMODES;

    // [Enum] TextureAddressMode
    lua["ADDRESS_WRAP"] = ADDRESS_WRAP;
    lua["ADDRESS_MIRROR"] = ADDRESS_MIRROR;
    lua["ADDRESS_CLAMP"] = ADDRESS_CLAMP;
    lua["ADDRESS_BORDER"] = ADDRESS_BORDER;
    lua["MAX_ADDRESSMODES"] = MAX_ADDRESSMODES;

    // [Enum] TextureCoordinate
    lua["COORD_U"] = COORD_U;
    lua["COORD_V"] = COORD_V;
    lua["COORD_W"] = COORD_W;
    lua["MAX_COORDS"] = MAX_COORDS;

    // [Enum] TextureUsage
    lua["TEXTURE_STATIC"] = TEXTURE_STATIC;
    lua["TEXTURE_DYNAMIC"] = TEXTURE_DYNAMIC;
    lua["TEXTURE_RENDERTARGET"] = TEXTURE_RENDERTARGET;
    lua["TEXTURE_DEPTHSTENCIL"] = TEXTURE_DEPTHSTENCIL;

    // [Enum] CubeMapFace
    lua["FACE_POSITIVE_X"] = FACE_POSITIVE_X;
    lua["FACE_NEGATIVE_X"] = FACE_NEGATIVE_X;
    lua["FACE_POSITIVE_Y"] = FACE_POSITIVE_Y;
    lua["FACE_NEGATIVE_Y"] = FACE_NEGATIVE_Y;
    lua["FACE_POSITIVE_Z"] = FACE_POSITIVE_Z;
    lua["FACE_NEGATIVE_Z"] = FACE_NEGATIVE_Z;
    lua["MAX_CUBEMAP_FACES"] = MAX_CUBEMAP_FACES;

    // [Enum] CubeMapLayout
    lua["CML_HORIZONTAL"] = CML_HORIZONTAL;
    lua["CML_HORIZONTALNVIDIA"] = CML_HORIZONTALNVIDIA;
    lua["CML_HORIZONTALCROSS"] = CML_HORIZONTALCROSS;
    lua["CML_VERTICALCROSS"] = CML_VERTICALCROSS;
    lua["CML_BLENDER"] = CML_BLENDER;

    // [Enum] RenderSurfaceUpdateMode
    lua["SURFACE_MANUALUPDATE"] = SURFACE_MANUALUPDATE;
    lua["SURFACE_UPDATEVISIBLE"] = SURFACE_UPDATEVISIBLE;
    lua["SURFACE_UPDATEALWAYS"] = SURFACE_UPDATEALWAYS;

    // [Enum] ShaderType
    lua["VS"] = VS;
    lua["PS"] = PS;

    // [Enum] TextureUnit
    lua["TU_DIFFUSE"] = TU_DIFFUSE;
    lua["TU_ALBEDOBUFFER"] = TU_ALBEDOBUFFER;
    lua["TU_NORMAL"] = TU_NORMAL;
    lua["TU_NORMALBUFFER"] = TU_NORMALBUFFER;
    lua["TU_SPECULAR"] = TU_SPECULAR;
    lua["TU_EMISSIVE"] = TU_EMISSIVE;
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
    lua["FC_NONE"] = FC_NONE;
    lua["FC_ROTATE_XYZ"] = FC_ROTATE_XYZ;
    lua["FC_ROTATE_Y"] = FC_ROTATE_Y;
    lua["FC_LOOKAT_XYZ"] = FC_LOOKAT_XYZ;
    lua["FC_LOOKAT_Y"] = FC_LOOKAT_Y;
    lua["FC_DIRECTION"] = FC_DIRECTION;

    // [Enum] ShadowQuality
    lua["SHADOWQUALITY_SIMPLE_16BIT"] = SHADOWQUALITY_SIMPLE_16BIT;
    lua["SHADOWQUALITY_SIMPLE_24BIT"] = SHADOWQUALITY_SIMPLE_24BIT;
    lua["SHADOWQUALITY_PCF_16BIT"] = SHADOWQUALITY_PCF_16BIT;
    lua["SHADOWQUALITY_PCF_24BIT"] = SHADOWQUALITY_PCF_24BIT;
    lua["SHADOWQUALITY_VSM"] = SHADOWQUALITY_VSM;
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

