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

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../IO/VectorBuffer.h"
#include "../Graphics/Camera.h"
#include "../Graphics/DebugRenderer.h"
#include "../Graphics/Geometry.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/GraphicsDefs.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/Material.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/RenderPath.h"
#include "../Graphics/RenderSurface.h"
#include "../Graphics/Technique.h"
#include "../Graphics/Texture.h"
#include "../Graphics/Texture2D.h"
#include "../Graphics/Texture2DArray.h"
#include "../Graphics/Texture3D.h"
#include "../Graphics/TextureCube.h"
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/Viewport.h"
#include "../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

extern Context* globalContext;

static void RegisterCamera(kaguya::State& lua)
{
    using namespace kaguya;

    lua["DEFAULT_NEARCLIP"] = DEFAULT_NEARCLIP;
    lua["DEFAULT_FARCLIP"] = DEFAULT_FARCLIP;
    lua["DEFAULT_CAMERA_FOV"] = DEFAULT_CAMERA_FOV;
    lua["DEFAULT_ORTHOSIZE"] = DEFAULT_ORTHOSIZE;

    lua["VO_NONE"] = VO_NONE;
    lua["VO_LOW_MATERIAL_QUALITY"] = VO_LOW_MATERIAL_QUALITY;
    lua["VO_DISABLE_SHADOWS"] = VO_DISABLE_SHADOWS;
    lua["VO_DISABLE_OCCLUSION"] = VO_DISABLE_OCCLUSION;

    lua["Camera"].setClass(UserdataMetatable<Camera, Component>()
        .addStaticFunction("new", &CreateObject<Camera>)
        
        .addFunction("SetNearClip", &Camera::SetNearClip)
        .addFunction("SetFarClip", &Camera::SetFarClip)
        .addFunction("SetFov", &Camera::SetFov)

        .addOverloadedFunctions("SetOrthoSize",
            static_cast<void(Camera::*)(float)>(&Camera::SetOrthoSize),
            static_cast<void(Camera::*)(const Vector2&)>(&Camera::SetOrthoSize))

        .addFunction("SetAspectRatio", &Camera::SetAspectRatio)
        .addFunction("SetFillMode", &Camera::SetFillMode)
        .addFunction("SetZoom", &Camera::SetZoom)
        .addFunction("SetLodBias", &Camera::SetLodBias)
        .addFunction("SetViewMask", &Camera::SetViewMask)
        .addFunction("SetViewOverrideFlags", &Camera::SetViewOverrideFlags)
        .addFunction("SetOrthographic", &Camera::SetOrthographic)
        .addFunction("SetAutoAspectRatio", &Camera::SetAutoAspectRatio)
        .addFunction("SetProjectionOffset", &Camera::SetProjectionOffset)
        .addFunction("SetUseReflection", &Camera::SetUseReflection)
        .addFunction("SetReflectionPlane", &Camera::SetReflectionPlane)
        .addFunction("SetUseClipping", &Camera::SetUseClipping)
        .addFunction("SetClipPlane", &Camera::SetClipPlane)
        .addFunction("SetFlipVertical", &Camera::SetFlipVertical)

        .addFunction("GetFarClip", &Camera::GetFarClip)
        .addFunction("GetNearClip", &Camera::GetNearClip)
        .addFunction("GetFov", &Camera::GetFov)
        .addFunction("GetOrthoSize", &Camera::GetOrthoSize)
        .addFunction("GetAspectRatio", &Camera::GetAspectRatio)
        .addFunction("GetZoom", &Camera::GetZoom)
        .addFunction("GetLodBias", &Camera::GetLodBias)
        .addFunction("GetViewMask", &Camera::GetViewMask)
        .addFunction("GetViewOverrideFlags", &Camera::GetViewOverrideFlags)
        .addFunction("GetFillMode", &Camera::GetFillMode)
        .addFunction("IsOrthographic", &Camera::IsOrthographic)
        .addFunction("GetAutoAspectRatio", &Camera::GetAutoAspectRatio)
        .addFunction("GetFrustum", &Camera::GetFrustum)

        .addOverloadedFunctions("GetProjection",
            static_cast<const Matrix4&(Camera::*)() const>(&Camera::GetProjection),
            static_cast<Matrix4(Camera::*)(bool) const>(&Camera::GetProjection))

        .addFunction("GetView", &Camera::GetView)
        .addFunction("GetFrustumSize", &Camera::GetFrustumSize)
        .addFunction("GetHalfViewSize", &Camera::GetHalfViewSize)
        
        .addFunction("GetSplitFrustum", &Camera::GetSplitFrustum)
        .addFunction("GetViewSpaceFrustum", &Camera::GetViewSpaceFrustum)
        .addFunction("GetViewSpaceSplitFrustum", &Camera::GetViewSpaceSplitFrustum)

        .addFunction("GetScreenRay", &Camera::GetScreenRay)
        .addFunction("WorldToScreenPoint", &Camera::WorldToScreenPoint)
        .addFunction("ScreenToWorldPoint", &Camera::ScreenToWorldPoint)
        .addFunction("GetProjectionOffset", &Camera::GetProjectionOffset)
        .addFunction("GetUseReflection", &Camera::GetUseReflection)
        .addFunction("GetReflectionPlane", &Camera::GetReflectionPlane)
        .addFunction("GetUseClipping", &Camera::GetUseClipping)
        .addFunction("GetClipPlane", &Camera::GetClipPlane)
        .addFunction("GetFlipVertical", &Camera::GetFlipVertical)
        
        .addFunction("GetDistance", &Camera::GetDistance)
        .addFunction("GetDistanceSquared", &Camera::GetDistanceSquared)
        .addFunction("GetLodDistance", &Camera::GetLodDistance)
        .addFunction("IsProjectionValid", &Camera::IsProjectionValid)
        .addFunction("GetEffectiveWorldTransform", &Camera::GetEffectiveWorldTransform)

        .addProperty("farClip", &Camera::GetFarClip, &Camera::SetFarClip)
        .addProperty("nearClip", &Camera::GetNearClip, &Camera::SetNearClip)
        .addProperty("fov", &Camera::GetFov, &Camera::SetFov)
        .addProperty("orthoSize", &Camera::GetOrthoSize, static_cast<void(Camera::*)(float)>(&Camera::SetOrthoSize))
        .addProperty("aspectRatio", &Camera::GetAspectRatio, &Camera::SetAspectRatio)
        .addProperty("zoom", &Camera::GetZoom, &Camera::SetZoom)
        .addProperty("lodBias", &Camera::GetLodBias, &Camera::SetLodBias)
        .addProperty("viewMask", &Camera::GetViewMask, &Camera::SetViewMask)
        .addProperty("viewOverrideFlags", &Camera::GetViewOverrideFlags, &Camera::SetViewOverrideFlags)
        .addProperty("fillMode", &Camera::GetFillMode, &Camera::SetFillMode)
        .addProperty("orthographic", &Camera::IsOrthographic, &Camera::SetOrthographic)
        .addProperty("autoAspectRatio", &Camera::GetAutoAspectRatio, &Camera::SetAutoAspectRatio)
        .addProperty("frustum", &Camera::GetFrustum)
        .addProperty("view", &Camera::GetView)
        .addProperty("halfViewSize", &Camera::GetHalfViewSize)
        .addProperty("viewSpaceFrustum", &Camera::GetViewSpaceFrustum)
        .addProperty("projectionOffset", &Camera::GetProjectionOffset, &Camera::SetProjectionOffset)
        .addProperty("useReflection", &Camera::GetUseReflection, &Camera::SetUseReflection)
        .addProperty("reflectionPlane", &Camera::GetReflectionPlane, &Camera::SetReflectionPlane)
        .addProperty("useClipping", &Camera::GetUseClipping, &Camera::SetUseClipping)
        .addProperty("clipPlane", &Camera::GetClipPlane, &Camera::SetClipPlane)
        .addProperty("flipVertical", &Camera::GetFlipVertical, &Camera::SetFlipVertical)
        .addProperty("projectionValid", &Camera::IsProjectionValid)
    );
}

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(DebugRendererAddLine, DebugRenderer, AddLine, 3, 4, void(DebugRenderer::*)(const Vector3&, const Vector3&, const Color&, bool));
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(DebugRendererAddTriangle, DebugRenderer, AddTriangle, 4, 5, void(DebugRenderer::*)(const Vector3&, const Vector3&, const Vector3&, const Color&, bool));
KAGUYA_MEMBER_FUNCTION_OVERLOADS(DebugRendererAddNode, DebugRenderer, AddNode, 1, 3);

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(DebugRendererAddBoundingBox0, DebugRenderer, AddBoundingBox, 2, 3, void(DebugRenderer::*)(const BoundingBox&, const Color&, bool));
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(DebugRendererAddBoundingBox1, DebugRenderer, AddBoundingBox, 3, 4, void(DebugRenderer::*)(const BoundingBox&, const Matrix3x4&, const Color&, bool));

KAGUYA_MEMBER_FUNCTION_OVERLOADS(DebugRendererAddFrustum, DebugRenderer, AddFrustum, 2, 3);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(DebugRendererAddPolyhedron, DebugRenderer, AddPolyhedron, 2, 3);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(DebugRendererAddSphere, DebugRenderer, AddSphere, 2, 3);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(DebugRendererAddCylinder, DebugRenderer, AddCylinder, 4, 5);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(DebugRendererAddSkeleton, DebugRenderer, AddSkeleton, 2, 3);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(DebugRendererAddTriangleMesh, DebugRenderer, AddTriangleMesh, 8, 9);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(DebugRendererAddCircle, DebugRenderer, AddCircle, 4, 6);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(DebugRendererAddCross, DebugRenderer, AddCross, 3, 4);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(DebugRendererAddQuad, DebugRenderer, AddQuad, 4, 5);

static void RegisterDebugRenderer(kaguya::State& lua)
{
    using namespace kaguya;

    lua["DebugRenderer"].setClass(UserdataMetatable<DebugRenderer, Component>()
        .addStaticFunction("new", &CreateObject<DebugRenderer>)
        
        .addFunction("SetView", &DebugRenderer::SetView)

        .addFunction("AddLine", DebugRendererAddLine())
        .addFunction("AddTriangle", DebugRendererAddTriangle())
        .addFunction("AddNode", DebugRendererAddNode())
        
        .addOverloadedFunctions("AddBoundingBox", 
            DebugRendererAddBoundingBox0(),
            DebugRendererAddBoundingBox1())

        .addFunction("AddFrustum", DebugRendererAddFrustum())
        .addFunction("AddPolyhedron", DebugRendererAddPolyhedron())
        .addFunction("AddSphere", DebugRendererAddSphere())
        .addFunction("AddCylinder", DebugRendererAddCylinder())
        .addFunction("AddSkeleton", DebugRendererAddSkeleton())
        .addFunction("AddTriangleMesh", DebugRendererAddTriangleMesh())
        .addFunction("AddCircle", DebugRendererAddCircle())
        .addFunction("AddCross", DebugRendererAddCross())
        .addFunction("AddQuad", DebugRendererAddQuad())

        .addFunction("Render", &DebugRenderer::Render)
        .addFunction("GetView", &DebugRenderer::GetView)
        .addFunction("GetProjection", &DebugRenderer::GetProjection)
        .addFunction("GetFrustum", &DebugRenderer::GetFrustum)
        .addFunction("IsInside", &DebugRenderer::IsInside)

        .addProperty("view", &DebugRenderer::GetView)
        .addProperty("projection", &DebugRenderer::GetProjection)
        .addProperty("frustum", &DebugRenderer::GetFrustum)
    );
}

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(GeometrySetDrawRange0, Geometry, SetDrawRange, 3, 4, bool(Geometry::*)(PrimitiveType, unsigned, unsigned, bool));
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(GeometrySetDrawRange1, Geometry, SetDrawRange, 5, 6, bool(Geometry::*)(PrimitiveType, unsigned, unsigned, unsigned, unsigned, bool));

static void RegisterGeometry(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Geometry"].setClass(UserdataMetatable<Geometry, Object>()
        .addStaticFunction("new", &CreateObject<Geometry>)
        
        .addFunction("SetNumVertexBuffers", &Geometry::SetNumVertexBuffers)
        .addFunction("SetVertexBuffer", &Geometry::SetVertexBuffer)
        .addFunction("SetIndexBuffer", &Geometry::SetIndexBuffer)

        .addOverloadedFunctions("SetDrawRange", 
            GeometrySetDrawRange0(),
            GeometrySetDrawRange1())

        .addFunction("SetLodDistance", &Geometry::SetLodDistance)

        .addFunction("GetNumVertexBuffers", &Geometry::GetNumVertexBuffers)
        .addFunction("GetVertexBuffer", &Geometry::GetVertexBuffer)
        .addFunction("GetIndexBuffer", &Geometry::GetIndexBuffer)        
        .addFunction("GetPrimitiveType", &Geometry::GetPrimitiveType)

        .addFunction("GetIndexStart", &Geometry::GetIndexStart)
        .addFunction("GetIndexCount", &Geometry::GetIndexCount)
        .addFunction("GetVertexStart", &Geometry::GetVertexStart)
        .addFunction("GetVertexCount", &Geometry::GetVertexCount)
        .addFunction("GetLodDistance", &Geometry::GetLodDistance)
        .addFunction("IsEmpty", &Geometry::IsEmpty)

        .addProperty("numVertexBuffers", &Geometry::GetNumVertexBuffers)

        .addProperty("indexBuffer", &Geometry::GetIndexBuffer, &Geometry::SetIndexBuffer)
        .addProperty("primitiveType", &Geometry::GetPrimitiveType)
        .addProperty("indexStart", &Geometry::GetIndexStart)
        .addProperty("indexCount", &Geometry::GetIndexCount)
        .addProperty("vertexStart", &Geometry::GetVertexStart)
        .addProperty("vertexCount", &Geometry::GetVertexCount)
        .addProperty("lodDistance", &Geometry::GetLodDistance, &Geometry::SetLodDistance)
        .addProperty("empty", &Geometry::IsEmpty)
    );
}

static void RegisterGraphics(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Graphics"].setClass(UserdataMetatable<Graphics, Object>()

        .addFunction("SetWindowIcon", &Graphics::SetWindowIcon)
        .addFunction("SetWindowTitle", &Graphics::SetWindowTitle)

        .addOverloadedFunctions("SetWindowPosition",
            static_cast<void(Graphics::*)(const IntVector2&)>(&Graphics::SetWindowPosition),
            static_cast<void(Graphics::*)(int, int)>(&Graphics::SetWindowPosition))

        .addOverloadedFunctions("SetMode",
            static_cast<bool(Graphics::*)(int, int, bool, bool, bool, bool, bool, bool, int)>(&Graphics::SetMode),
            static_cast<bool(Graphics::*)(int, int)>(&Graphics::SetMode))

        .addFunction("SetSRGB", &Graphics::SetSRGB)
        .addFunction("SetFlushGPU", &Graphics::SetFlushGPU)
        .addFunction("SetOrientations", &Graphics::SetOrientations)
        .addFunction("ToggleFullscreen", &Graphics::ToggleFullscreen)

        .addFunction("Maximize", &Graphics::Maximize)
        .addFunction("Minimize", &Graphics::Minimize)
        .addFunction("Close", &Graphics::Close)
        
        .addFunction("TakeScreenShot", &Graphics::TakeScreenShot)        

        .addFunction("BeginDumpShaders", &Graphics::BeginDumpShaders)
        .addFunction("EndDumpShaders", &Graphics::EndDumpShaders)

        .addFunction("PrecacheShaders", &Graphics::PrecacheShaders)

        .addFunction("IsInitialized", &Graphics::IsInitialized)
        .addFunction("GetWindowTitle", &Graphics::GetWindowTitle)
        .addFunction("GetApiName", &Graphics::GetApiName)
        .addFunction("GetWindowPosition", &Graphics::GetWindowPosition)
        .addFunction("GetWidth", &Graphics::GetWidth)
        .addFunction("GetHeight", &Graphics::GetHeight)
        .addFunction("GetMultiSample", &Graphics::GetMultiSample)
        .addFunction("GetFullscreen", &Graphics::GetFullscreen)
        .addFunction("GetBorderless", &Graphics::GetBorderless)
        .addFunction("GetResizable", &Graphics::GetResizable)
        // .addFunction("GetHighDPI", &Graphics::GetHighDPI)
        .addFunction("GetVSync", &Graphics::GetVSync)
        .addFunction("GetTripleBuffer", &Graphics::GetTripleBuffer)
        .addFunction("GetSRGB", &Graphics::GetSRGB)
        .addFunction("GetFlushGPU", &Graphics::GetFlushGPU)
        .addFunction("GetOrientations", &Graphics::GetOrientations)

        .addFunction("GetNumPrimitives", &Graphics::GetNumPrimitives)
        .addFunction("GetNumBatches", &Graphics::GetNumBatches)

        .addFunction("GetDummyColorFormat", &Graphics::GetDummyColorFormat)
        .addFunction("GetShadowMapFormat", &Graphics::GetShadowMapFormat)
        .addFunction("GetHiresShadowMapFormat", &Graphics::GetHiresShadowMapFormat)
        
        .addFunction("GetInstancingSupport", &Graphics::GetInstancingSupport)
        .addFunction("GetLightPrepassSupport", &Graphics::GetLightPrepassSupport)
        .addFunction("GetDeferredSupport", &Graphics::GetDeferredSupport)        
        .addFunction("GetHardwareShadowSupport", &Graphics::GetHardwareShadowSupport)
        .addFunction("GetReadableDepthSupport", &Graphics::GetReadableDepthSupport)
        .addFunction("GetSRGBSupport", &Graphics::GetSRGBSupport)
        .addFunction("GetSRGBWriteSupport", &Graphics::GetSRGBWriteSupport)
        
        .addFunction("GetDesktopResolution", &Graphics::GetDesktopResolution)

        .addStaticFunction("GetAlphaFormat", &Graphics::GetAlphaFormat)
        .addStaticFunction("GetLuminanceFormat", &Graphics::GetLuminanceFormat)
        .addStaticFunction("GetLuminanceAlphaFormat", &Graphics::GetLuminanceAlphaFormat)
        .addStaticFunction("GetRGBFormat", &Graphics::GetRGBFormat)
        .addStaticFunction("GetRGBAFormat", &Graphics::GetRGBAFormat)
        .addStaticFunction("GetRGBA16Format", &Graphics::GetRGBA16Format)
        .addStaticFunction("GetRGBAFloat16Format", &Graphics::GetRGBAFloat16Format)
        .addStaticFunction("GetRGBAFloat32Format", &Graphics::GetRGBAFloat32Format)
        .addStaticFunction("GetRG16Format", &Graphics::GetRG16Format)
        .addStaticFunction("GetRGFloat16Format", &Graphics::GetRGFloat16Format)
        .addStaticFunction("GetRGFloat32Format", &Graphics::GetRGFloat32Format)
        .addStaticFunction("GetFloat16Format", &Graphics::GetFloat16Format)
        .addStaticFunction("GetFloat32Format", &Graphics::GetFloat32Format)
        .addStaticFunction("GetLinearDepthFormat", &Graphics::GetLinearDepthFormat)
        .addStaticFunction("GetDepthStencilFormat", &Graphics::GetDepthStencilFormat)
        .addStaticFunction("GetReadableDepthFormat", &Graphics::GetReadableDepthFormat)
        .addStaticFunction("GetPixelUVOffset", &Graphics::GetPixelUVOffset)
        .addStaticFunction("GetMaxBones", &Graphics::GetMaxBones)
        
        .addProperty("initialized", &Graphics::IsInitialized)
        .addProperty("windowTitle", &Graphics::GetWindowTitle, &Graphics::SetWindowTitle)
        .addProperty("apiName", &Graphics::GetApiName)
        .addProperty("windowPosition", &Graphics::GetWindowPosition, static_cast<void(Graphics::*)(const IntVector2&)>(&Graphics::SetWindowPosition))
        .addProperty("width", &Graphics::GetWidth)
        .addProperty("height", &Graphics::GetHeight)
        .addProperty("multiSample", &Graphics::GetMultiSample)

        .addProperty("fullscreen", &Graphics::GetFullscreen)
        .addProperty("borderless", &Graphics::GetBorderless)
        .addProperty("resizable", &Graphics::GetResizable)

        // .addProperty("highDPI", &Graphics::GetHighDPI)
        .addProperty("vSync", &Graphics::GetVSync)
        .addProperty("tripleBuffer", &Graphics::GetTripleBuffer)
        .addProperty("sRGB", &Graphics::GetSRGB, &Graphics::SetSRGB)
        .addProperty("flushGPU", &Graphics::GetFlushGPU, &Graphics::SetFlushGPU)
        .addProperty("orientations", &Graphics::GetOrientations, &Graphics::SetOrientations)

        .addProperty("deviceLost", &Graphics::IsDeviceLost)

        .addProperty("numPrimitives", &Graphics::GetNumPrimitives)
        .addProperty("numBatches", &Graphics::GetNumBatches)
        .addProperty("dummyColorFormat", &Graphics::GetDummyColorFormat)
        .addProperty("shadowMapFormat", &Graphics::GetShadowMapFormat)
        .addProperty("hiresShadowMapFormat", &Graphics::GetHiresShadowMapFormat)
        .addProperty("instancingSupport", &Graphics::GetInstancingSupport)
        .addProperty("lightPrepassSupport", &Graphics::GetLightPrepassSupport)
        .addProperty("deferredSupport", &Graphics::GetDeferredSupport)
        .addProperty("hardwareShadowSupport", &Graphics::GetHardwareShadowSupport)
        .addProperty("readableDepthSupport", &Graphics::GetReadableDepthSupport)
        .addProperty("sRGBSupport", &Graphics::GetSRGBSupport)
        .addProperty("sRGBWriteSupport", &Graphics::GetSRGBWriteSupport)
        .addProperty("desktopResolution", &Graphics::GetDesktopResolution)
    );
}

static void RegisterGraphicsDefs(kaguya::State& lua)
{
    using namespace kaguya;

    // enum PrimitiveType;
    lua["TRIANGLE_LIST"] = TRIANGLE_LIST;
    lua["LINE_LIST"] = LINE_LIST;
    lua["POINT_LIST"] = POINT_LIST;
    lua["TRIANGLE_STRIP"] = TRIANGLE_STRIP;
    lua["LINE_STRIP"] = LINE_STRIP;
    lua["TRIANGLE_FAN"] = TRIANGLE_FAN;

    // enum GeometryType;
    lua["GEOM_STATIC"] = GEOM_STATIC;
    lua["GEOM_SKINNED"] = GEOM_SKINNED;
    lua["GEOM_INSTANCED"] = GEOM_INSTANCED;
    lua["GEOM_BILLBOARD"] = GEOM_BILLBOARD;
    lua["GEOM_DIRBILLBOARD"] = GEOM_DIRBILLBOARD;
    lua["GEOM_TRAIL_FACE_CAMERA"] = GEOM_TRAIL_FACE_CAMERA;
    lua["GEOM_TRAIL_BONE"] = GEOM_TRAIL_BONE;
    lua["GEOM_STATIC_NOINSTANCING"] = GEOM_STATIC_NOINSTANCING;
    lua["MAX_GEOMETRYTYPES"] = MAX_GEOMETRYTYPES;

    // enum BlendMode;
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

    // enum CompareMode;
    lua["CMP_ALWAYS"] = CMP_ALWAYS;
    lua["CMP_EQUAL"] = CMP_EQUAL;
    lua["CMP_NOTEQUAL"] = CMP_NOTEQUAL;
    lua["CMP_LESS"] = CMP_LESS;
    lua["CMP_LESSEQUAL"] = CMP_LESSEQUAL;
    lua["CMP_GREATER"] = CMP_GREATER;
    lua["CMP_GREATEREQUAL"] = CMP_GREATEREQUAL;
    lua["MAX_COMPAREMODES"] = MAX_COMPAREMODES;

    // enum CullMode;
    lua["CULL_NONE"] = CULL_NONE;
    lua["CULL_CCW"] = CULL_CCW;
    lua["CULL_CW"] = CULL_CW;
    lua["MAX_CULLMODES"] = MAX_CULLMODES;

    // enum FillMode;
    lua["FILL_SOLID"] = FILL_SOLID;
    lua["FILL_WIREFRAME"] = FILL_WIREFRAME;
    lua["FILL_POINT"] = FILL_POINT;

    // enum StencilOp;
    lua["OP_KEEP"] = OP_KEEP;
    lua["OP_ZERO"] = OP_ZERO;
    lua["OP_REF"] = OP_REF;
    lua["OP_INCR"] = OP_INCR;
    lua["OP_DECR"] = OP_DECR;

    // enum LockState;
    lua["LOCK_NONE"] = LOCK_NONE;
    lua["LOCK_HARDWARE"] = LOCK_HARDWARE;
    lua["LOCK_SHADOW"] = LOCK_SHADOW;
    lua["LOCK_SCRATCH"] = LOCK_SCRATCH;

    // enum LegacyVertexElement;
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

    // enum VertexElementType;
    lua["TYPE_INT"] = TYPE_INT;
    lua["TYPE_FLOAT"] = TYPE_FLOAT;
    lua["TYPE_VECTOR2"] = TYPE_VECTOR2;
    lua["TYPE_VECTOR3"] = TYPE_VECTOR3;
    lua["TYPE_VECTOR4"] = TYPE_VECTOR4;
    lua["TYPE_UBYTE4"] = TYPE_UBYTE4;
    lua["TYPE_UBYTE4_NORM"] = TYPE_UBYTE4_NORM;
    lua["MAX_VERTEX_ELEMENT_TYPES"] = MAX_VERTEX_ELEMENT_TYPES;

    // enum VertexElementSemantic;
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

    // enum TextureFilterMode;
    lua["FILTER_NEAREST"] = FILTER_NEAREST;
    lua["FILTER_BILINEAR"] = FILTER_BILINEAR;
    lua["FILTER_TRILINEAR"] = FILTER_TRILINEAR;
    lua["FILTER_ANISOTROPIC"] = FILTER_ANISOTROPIC;
    lua["FILTER_DEFAULT"] = FILTER_DEFAULT;
    lua["MAX_FILTERMODES"] = MAX_FILTERMODES;

    // enum TextureAddressMode;
    lua["ADDRESS_WRAP"] = ADDRESS_WRAP;
    lua["ADDRESS_MIRROR"] = ADDRESS_MIRROR;
    lua["ADDRESS_CLAMP"] = ADDRESS_CLAMP;
    lua["ADDRESS_BORDER"] = ADDRESS_BORDER;
    lua["MAX_ADDRESSMODES"] = MAX_ADDRESSMODES;

    // enum TextureCoordinate;
    lua["COORD_U"] = COORD_U;
    lua["COORD_V"] = COORD_V;
    lua["COORD_W"] = COORD_W;
    lua["MAX_COORDS"] = MAX_COORDS;

    // enum TextureUsage;
    lua["TEXTURE_STATIC"] = TEXTURE_STATIC;
    lua["TEXTURE_DYNAMIC"] = TEXTURE_DYNAMIC;
    lua["TEXTURE_RENDERTARGET"] = TEXTURE_RENDERTARGET;
    lua["TEXTURE_DEPTHSTENCIL"] = TEXTURE_DEPTHSTENCIL;

    // enum CubeMapFace;
    lua["FACE_POSITIVE_X"] = FACE_POSITIVE_X;
    lua["FACE_NEGATIVE_X"] = FACE_NEGATIVE_X;
    lua["FACE_POSITIVE_Y"] = FACE_POSITIVE_Y;
    lua["FACE_NEGATIVE_Y"] = FACE_NEGATIVE_Y;
    lua["FACE_POSITIVE_Z"] = FACE_POSITIVE_Z;
    lua["FACE_NEGATIVE_Z"] = FACE_NEGATIVE_Z;
    lua["MAX_CUBEMAP_FACES"] = MAX_CUBEMAP_FACES;

    // enum CubeMapLayout;
    lua["CML_HORIZONTAL"] = CML_HORIZONTAL;
    lua["CML_HORIZONTALNVIDIA"] = CML_HORIZONTALNVIDIA;
    lua["CML_HORIZONTALCROSS"] = CML_HORIZONTALCROSS;
    lua["CML_VERTICALCROSS"] = CML_VERTICALCROSS;
    lua["CML_BLENDER"] = CML_BLENDER;

    // enum RenderSurfaceUpdateMode;
    lua["SURFACE_MANUALUPDATE"] = SURFACE_MANUALUPDATE;
    lua["SURFACE_UPDATEVISIBLE"] = SURFACE_UPDATEVISIBLE;
    lua["SURFACE_UPDATEALWAYS"] = SURFACE_UPDATEALWAYS;

    // enum ShaderType;
    lua["VS"] = VS;
    lua["PS"] = PS;

    // enum TextureUnit;
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

    // enum FaceCameraMode;
    lua["FC_NONE"] = FC_NONE;
    lua["FC_ROTATE_XYZ"] = FC_ROTATE_XYZ;
    lua["FC_ROTATE_Y"] = FC_ROTATE_Y;
    lua["FC_LOOKAT_XYZ"] = FC_LOOKAT_XYZ;
    lua["FC_LOOKAT_Y"] = FC_LOOKAT_Y;
    lua["FC_DIRECTION"] = FC_DIRECTION;

    // enum ShadowQuality;
    lua["SHADOWQUALITY_SIMPLE_16BIT"] = SHADOWQUALITY_SIMPLE_16BIT;
    lua["SHADOWQUALITY_SIMPLE_24BIT"] = SHADOWQUALITY_SIMPLE_24BIT;
    lua["SHADOWQUALITY_PCF_16BIT"] = SHADOWQUALITY_PCF_16BIT;
    lua["SHADOWQUALITY_PCF_24BIT"] = SHADOWQUALITY_PCF_24BIT;
    lua["SHADOWQUALITY_VSM"] = SHADOWQUALITY_VSM;
    lua["SHADOWQUALITY_BLUR_VSM"] = SHADOWQUALITY_BLUR_VSM;

    lua["QUALITY_LOW"] = QUALITY_LOW;
    lua["QUALITY_MEDIUM"] = QUALITY_MEDIUM;
    lua["QUALITY_HIGH"] = QUALITY_HIGH;
    lua["QUALITY_MAX"] = QUALITY_MAX;

    lua["CLEAR_COLOR"] = CLEAR_COLOR;
    lua["CLEAR_DEPTH"] = CLEAR_DEPTH;
    lua["CLEAR_STENCIL"] = CLEAR_STENCIL;

    lua["MASK_NONE"] = MASK_NONE;
    lua["MASK_POSITION"] = MASK_POSITION;
    lua["MASK_NORMAL"] = MASK_NORMAL;
    lua["MASK_COLOR"] = MASK_COLOR;
    lua["MASK_TEXCOORD1"] = MASK_TEXCOORD1;
    lua["MASK_TEXCOORD2"] = MASK_TEXCOORD2;
    lua["MASK_CUBETEXCOORD1"] = MASK_CUBETEXCOORD1;
    lua["MASK_CUBETEXCOORD2"] = MASK_CUBETEXCOORD2;
    lua["MASK_TANGENT"] = MASK_TANGENT;
    lua["MASK_BLENDWEIGHTS"] = MASK_BLENDWEIGHTS;
    lua["MASK_BLENDINDICES"] = MASK_BLENDINDICES;
    lua["MASK_INSTANCEMATRIX1"] = MASK_INSTANCEMATRIX1;
    lua["MASK_INSTANCEMATRIX2"] = MASK_INSTANCEMATRIX2;
    lua["MASK_INSTANCEMATRIX3"] = MASK_INSTANCEMATRIX3;
    lua["MASK_OBJECTINDEX"] = MASK_OBJECTINDEX;
}

static SharedPtr<IndexBuffer> CreateIndexBuffer(bool forceHeadless = false)
{
    return SharedPtr<IndexBuffer>(new IndexBuffer(globalContext, forceHeadless));
}

KAGUYA_FUNCTION_OVERLOADS(CreateIndexBufferOverloads, CreateIndexBuffer, 0, 1);

KAGUYA_MEMBER_FUNCTION_OVERLOADS(IndexBufferSetSize, IndexBuffer, SetSize, 2, 3);

static bool IndexBufferSetData(IndexBuffer* self, VectorBuffer& src)
{
    // Make sure there is enough data
    if (self->GetIndexCount() && src.GetSize() >= self->GetIndexCount() * self->GetIndexSize())
        return self->SetData(&src.GetBuffer()[0]);
    else
        return false;
}

static VectorBuffer IndexBufferGetData(IndexBuffer* self)
{
    VectorBuffer ret;
    
    void* data = self->Lock(0, self->GetIndexCount(), false);
    if (data)
    {
        ret.Write(data, self->GetIndexCount() * self->GetIndexSize());
        ret.Seek(0);
        self->Unlock();
    }

    return ret;
}

static void RegisterIndexBuffer(kaguya::State& lua)
{
    using namespace kaguya;

    lua["IndexBuffer"].setClass(UserdataMetatable<IndexBuffer, Object>()
        .addStaticFunction("new", 
            CreateIndexBufferOverloads())
        
        .addFunction("SetShadowed", &IndexBuffer::SetShadowed)
        
        .addFunction("SetSize", IndexBufferSetSize())
        
        .addStaticFunction("SetData", &IndexBufferSetData)
        .addStaticFunction("GetData", &IndexBufferGetData)

        .addFunction("IsShadowed", &IndexBuffer::IsShadowed)
        .addFunction("IsDynamic", &IndexBuffer::IsDynamic)
        .addFunction("GetIndexCount", &IndexBuffer::GetIndexCount)
        .addFunction("GetIndexSize", &IndexBuffer::GetIndexSize)
                
        .addProperty("shadowed", &IndexBuffer::IsShadowed, &IndexBuffer::SetShadowed)
        .addProperty("dynamic", &IndexBuffer::IsDynamic)
        .addProperty("indexCount", &IndexBuffer::GetIndexCount)
        .addProperty("indexSize", &IndexBuffer::GetIndexSize)
    );
}

KAGUYA_MEMBER_FUNCTION_OVERLOADS(MaterialSetTechnique, Material, SetTechnique, 2, 4);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(MaterialSetShaderParameterAnimation, Material, SetShaderParameterAnimation, 2, 4);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(MaterialClone, Material, Clone, 0, 1);

static void RegisterMaterial(kaguya::State& lua)
{
    using namespace kaguya;

    lua["DEFAULT_RENDER_ORDER"] = DEFAULT_RENDER_ORDER;

    lua["Material"].setClass(UserdataMetatable<Material, Resource>()
        .addStaticFunction("new", &CreateObject<Material>)
        
        .addFunction("SetNumTechniques", &Material::SetNumTechniques)        
        .addFunction("SetTechnique", MaterialSetTechnique())        
        .addFunction("SetShaderParameter", &Material::SetShaderParameter)        
        .addFunction("SetShaderParameterAnimation", MaterialSetShaderParameterAnimation())

        .addFunction("SetShaderParameterAnimationWrapMode", &Material::SetShaderParameterAnimationWrapMode)
        .addFunction("SetShaderParameterAnimationSpeed", &Material::SetShaderParameterAnimationSpeed)
        .addFunction("SetTexture", &Material::SetTexture)

        .addOverloadedFunctions("SetUVTransform",
            static_cast<void(Material::*)(const Vector2&, float, const Vector2&)>(&Material::SetUVTransform),
            static_cast<void(Material::*)(const Vector2&, float, float)>(&Material::SetUVTransform))

        .addFunction("SetCullMode", &Material::SetCullMode)
        .addFunction("SetShadowCullMode", &Material::SetShadowCullMode)
        .addFunction("SetFillMode", &Material::SetFillMode)
        .addFunction("SetDepthBias", &Material::SetDepthBias)
        .addFunction("SetRenderOrder", &Material::SetRenderOrder)
        .addFunction("SetScene", &Material::SetScene)
        .addFunction("RemoveShaderParameter", &Material::RemoveShaderParameter)
        .addFunction("ReleaseShaders", &Material::ReleaseShaders)
        
        .addFunction("Clone", MaterialClone())

        .addFunction("SortTechniques", &Material::SortTechniques)
        .addFunction("MarkForAuxView", &Material::MarkForAuxView)
        .addFunction("GetNumTechniques", &Material::GetNumTechniques)
        .addFunction("GetTechniques", &Material::GetTechniques)
        .addFunction("GetTechnique", &Material::GetTechnique)
        .addFunction("GetPass", &Material::GetPass)
        
        .addFunction("GetTexture", &Material::GetTexture)
        .addFunction("GetShaderParameter", &Material::GetShaderParameter)
        .addFunction("GetShaderParameterAnimation", &Material::GetShaderParameterAnimation)
        .addFunction("GetShaderParameterAnimationWrapMode", &Material::GetShaderParameterAnimationWrapMode)
        .addFunction("GetShaderParameterAnimationSpeed", &Material::GetShaderParameterAnimationSpeed)
        
        .addFunction("GetCullMode", &Material::GetCullMode)
        .addFunction("GetShadowCullMode", &Material::GetShadowCullMode)
        .addFunction("GetFillMode", &Material::GetFillMode)
        .addFunction("GetDepthBias", &Material::GetDepthBias)
        .addFunction("GetRenderOrder", &Material::GetRenderOrder)
        .addFunction("GetAuxViewFrameNumber", &Material::GetAuxViewFrameNumber)
        .addFunction("GetOcclusion", &Material::GetOcclusion)
        .addFunction("GetSpecular", &Material::GetSpecular)
        .addFunction("GetScene", &Material::GetScene)
        
        .addProperty("cullMode", &Material::GetCullMode, &Material::SetCullMode)
        .addProperty("shadowCullMode", &Material::GetShadowCullMode, &Material::SetShadowCullMode)
        .addProperty("fillMode", &Material::GetFillMode, &Material::SetFillMode)
        .addProperty("depthBias", &Material::GetDepthBias, &Material::SetDepthBias)
        .addProperty("renderOrder", &Material::GetRenderOrder, &Material::SetRenderOrder)
        .addProperty("occlusion", &Material::GetOcclusion)
        .addProperty("specular", &Material::GetSpecular)
        .addProperty("scene", &Material::GetScene, &Material::SetScene)
    );
}

KAGUYA_MEMBER_FUNCTION_OVERLOADS(RendererGetNumGeometries, Renderer, GetNumGeometries, 0, 1);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(RendererGetNumLights, Renderer, GetNumLights, 0, 1);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(RendererGetNumShadowMaps, Renderer, GetNumShadowMaps, 0, 1);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(RendererGetNumOccluders, Renderer, GetNumOccluders, 0, 1);
// KAGUYA_MEMBER_FUNCTION_OVERLOADS(RendererGetScreenBuffer, Renderer, GetScreenBuffer, 6, 7);
// KAGUYA_MEMBER_FUNCTION_OVERLOADS(RendererSetBatchShaders, Renderer, SetBatchShaders, 2, 3);

static void RegisterRenderer(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Renderer"].setClass(UserdataMetatable<Renderer, Object>()

        .addFunction("SetNumViewports", &Renderer::SetNumViewports)
        .addFunction("SetViewport", &Renderer::SetViewport)

        .addOverloadedFunctions("SetDefaultRenderPath",
            static_cast<void(Renderer::*)(RenderPath*)>(&Renderer::SetDefaultRenderPath),
            static_cast<void(Renderer::*)(XMLFile*)>(&Renderer::SetDefaultRenderPath))

        .addFunction("SetDefaultTechnique", &Renderer::SetDefaultTechnique)
        .addFunction("SetHDRRendering", &Renderer::SetHDRRendering)
        .addFunction("SetSpecularLighting", &Renderer::SetSpecularLighting)
        .addFunction("SetTextureAnisotropy", &Renderer::SetTextureAnisotropy)
        .addFunction("SetTextureFilterMode", &Renderer::SetTextureFilterMode)
        .addFunction("SetTextureQuality", &Renderer::SetTextureQuality)
        .addFunction("SetMaterialQuality", &Renderer::SetMaterialQuality)
        .addFunction("SetDrawShadows", &Renderer::SetDrawShadows)
        .addFunction("SetShadowMapSize", &Renderer::SetShadowMapSize)
        .addFunction("SetShadowQuality", &Renderer::SetShadowQuality)
        .addFunction("SetShadowSoftness", &Renderer::SetShadowSoftness)
        .addFunction("SetShadowMapFilter", &Renderer::SetShadowMapFilter)
        .addFunction("SetReuseShadowMaps", &Renderer::SetReuseShadowMaps)
        .addFunction("SetMaxShadowMaps", &Renderer::SetMaxShadowMaps)
        .addFunction("SetDynamicInstancing", &Renderer::SetDynamicInstancing)
        .addFunction("SetNumExtraInstancingBufferElements", &Renderer::SetNumExtraInstancingBufferElements)
        .addFunction("SetMinInstances", &Renderer::SetMinInstances)
        .addFunction("SetMaxSortedInstances", &Renderer::SetMaxSortedInstances)
        .addFunction("SetMaxOccluderTriangles", &Renderer::SetMaxOccluderTriangles)
        .addFunction("SetOcclusionBufferSize", &Renderer::SetOcclusionBufferSize)
        .addFunction("SetOccluderSizeThreshold", &Renderer::SetOccluderSizeThreshold)
        .addFunction("SetThreadedOcclusion", &Renderer::SetThreadedOcclusion)
        .addFunction("SetMobileShadowBiasMul", &Renderer::SetMobileShadowBiasMul)
        .addFunction("SetMobileShadowBiasAdd", &Renderer::SetMobileShadowBiasAdd)
        .addFunction("SetMobileNormalOffsetMul", &Renderer::SetMobileNormalOffsetMul)
        
        .addFunction("ReloadShaders", &Renderer::ReloadShaders)
        
        .addFunction("GetNumViewports", &Renderer::GetNumViewports)
        .addFunction("GetViewport", &Renderer::GetViewport)
        .addFunction("GetDefaultRenderPath", &Renderer::GetDefaultRenderPath)
        .addFunction("GetDefaultTechnique", &Renderer::GetDefaultTechnique)
        .addFunction("GetHDRRendering", &Renderer::GetHDRRendering)
        .addFunction("GetSpecularLighting", &Renderer::GetSpecularLighting)
        .addFunction("GetDrawShadows", &Renderer::GetDrawShadows)
        .addFunction("GetTextureAnisotropy", &Renderer::GetTextureAnisotropy)
        .addFunction("GetTextureFilterMode", &Renderer::GetTextureFilterMode)
        .addFunction("GetTextureQuality", &Renderer::GetTextureQuality)
        .addFunction("GetMaterialQuality", &Renderer::GetMaterialQuality)
        .addFunction("GetShadowMapSize", &Renderer::GetShadowMapSize)
        .addFunction("GetShadowQuality", &Renderer::GetShadowQuality)
        .addFunction("GetShadowSoftness", &Renderer::GetShadowSoftness)
        .addFunction("GetReuseShadowMaps", &Renderer::GetReuseShadowMaps)
        .addFunction("GetMaxShadowMaps", &Renderer::GetMaxShadowMaps)
        .addFunction("GetDynamicInstancing", &Renderer::GetDynamicInstancing)
        .addFunction("GetNumExtraInstancingBufferElements", &Renderer::GetNumExtraInstancingBufferElements)
        .addFunction("GetMinInstances", &Renderer::GetMinInstances)
        .addFunction("GetMaxSortedInstances", &Renderer::GetMaxSortedInstances)
        .addFunction("GetMaxOccluderTriangles", &Renderer::GetMaxOccluderTriangles)
        .addFunction("GetOcclusionBufferSize", &Renderer::GetOcclusionBufferSize)
        .addFunction("GetOccluderSizeThreshold", &Renderer::GetOccluderSizeThreshold)
        .addFunction("GetThreadedOcclusion", &Renderer::GetThreadedOcclusion)
        .addFunction("GetMobileShadowBiasMul", &Renderer::GetMobileShadowBiasMul)
        .addFunction("GetMobileShadowBiasAdd", &Renderer::GetMobileShadowBiasAdd)
        .addFunction("GetMobileNormalOffsetMul", &Renderer::GetMobileNormalOffsetMul)
        .addFunction("GetNumViews", &Renderer::GetNumViews)
        .addFunction("GetNumPrimitives", &Renderer::GetNumPrimitives)
        .addFunction("GetNumBatches", &Renderer::GetNumBatches)
        
        .addFunction("GetNumGeometries", RendererGetNumGeometries())
        .addFunction("GetNumLights", RendererGetNumLights())
        .addFunction("GetNumShadowMaps", RendererGetNumShadowMaps())
        .addFunction("GetNumOccluders", RendererGetNumOccluders())

        // .addFunction("GetScreenBuffer", RendererGetScreenBuffer())
        // .addFunction("SetBatchShaders", RendererSetBatchShaders())
        
        .addFunction("GetDefaultZone", &Renderer::GetDefaultZone)
        .addFunction("GetDefaultMaterial", &Renderer::GetDefaultMaterial)
        .addFunction("GetDefaultLightRamp", &Renderer::GetDefaultLightRamp)
        .addFunction("GetDefaultLightSpot", &Renderer::GetDefaultLightSpot)
        
        .addFunction("DrawDebugGeometry", &Renderer::DrawDebugGeometry)
        
        .addProperty("numViewports", &Renderer::GetNumViewports, &Renderer::SetNumViewports)
        .addProperty("defaultRenderPath", &Renderer::GetDefaultRenderPath, static_cast<void(Renderer::*)(RenderPath*)>(&Renderer::SetDefaultRenderPath))
        .addProperty("defaultTechnique", &Renderer::GetDefaultTechnique, &Renderer::SetDefaultTechnique)
        .addProperty("hdrRendering", &Renderer::GetHDRRendering, &Renderer::SetHDRRendering)
        .addProperty("specularLighting", &Renderer::GetSpecularLighting, &Renderer::SetSpecularLighting)
        .addProperty("drawShadows", &Renderer::GetDrawShadows, &Renderer::SetDrawShadows)
        .addProperty("textureAnisotropy", &Renderer::GetTextureAnisotropy, &Renderer::SetTextureAnisotropy)
        .addProperty("textureFilterMode", &Renderer::GetTextureFilterMode, &Renderer::SetTextureFilterMode)
        .addProperty("textureQuality", &Renderer::GetTextureQuality, &Renderer::SetTextureQuality)
        .addProperty("materialQuality", &Renderer::GetMaterialQuality, &Renderer::SetMaterialQuality)
        .addProperty("shadowMapSize", &Renderer::GetShadowMapSize, &Renderer::SetShadowMapSize)
        .addProperty("shadowQuality", &Renderer::GetShadowQuality, &Renderer::SetShadowQuality)
        .addProperty("shadowSoftness", &Renderer::GetShadowSoftness, &Renderer::SetShadowSoftness)
        
        .addProperty("reuseShadowMaps", &Renderer::GetReuseShadowMaps, &Renderer::SetReuseShadowMaps)
        .addProperty("maxShadowMaps", &Renderer::GetMaxShadowMaps, &Renderer::SetMaxShadowMaps)
        .addProperty("dynamicInstancing", &Renderer::GetDynamicInstancing, &Renderer::SetDynamicInstancing)
        .addProperty("numExtraInstancingBufferElements", &Renderer::GetNumExtraInstancingBufferElements, &Renderer::SetNumExtraInstancingBufferElements)
        .addProperty("minInstances", &Renderer::GetMinInstances, &Renderer::SetMinInstances)
        .addProperty("maxSortedInstances", &Renderer::GetMaxSortedInstances, &Renderer::SetMaxSortedInstances)
        .addProperty("maxOccluderTriangles", &Renderer::GetMaxOccluderTriangles, &Renderer::SetMaxOccluderTriangles)
        .addProperty("occlusionBufferSize", &Renderer::GetOcclusionBufferSize, &Renderer::SetOcclusionBufferSize)
        .addProperty("occluderSizeThreshold", &Renderer::GetOccluderSizeThreshold, &Renderer::SetOccluderSizeThreshold)
        .addProperty("threadedOcclusion", &Renderer::GetThreadedOcclusion, &Renderer::SetThreadedOcclusion)
        .addProperty("mobileShadowBiasMul", &Renderer::GetMobileShadowBiasMul, &Renderer::SetMobileShadowBiasMul)
        .addProperty("mobileShadowBiasAdd", &Renderer::GetMobileShadowBiasAdd, &Renderer::SetMobileShadowBiasAdd)
        .addProperty("mobileNormalOffsetMul", &Renderer::GetMobileNormalOffsetMul, &Renderer::SetMobileNormalOffsetMul)
        
        .addProperty("numViews", &Renderer::GetNumViews)
        .addProperty("numPrimitives", &Renderer::GetNumPrimitives)
        .addProperty("numBatches", &Renderer::GetNumBatches)
        .addProperty("defaultZone", &Renderer::GetDefaultZone)
        .addProperty("defaultMaterial", &Renderer::GetDefaultMaterial)
        .addProperty("defaultLightRamp", &Renderer::GetDefaultLightRamp)
        .addProperty("defaultLightSpot", &Renderer::GetDefaultLightSpot)        
    );
}

KAGUYA_MEMBER_FUNCTION_OVERLOADS(RenderPathCommandSetOutput, RenderPathCommand, SetOutput, 2, 3);

static void RegisterRenderPath(kaguya::State& lua)
{
    using namespace kaguya;

    // enum RenderCommandType;
    lua["CMD_NONE"] = CMD_NONE;
    lua["CMD_CLEAR"] = CMD_CLEAR;
    lua["CMD_SCENEPASS"] = CMD_SCENEPASS;
    lua["CMD_QUAD"] = CMD_QUAD;
    lua["CMD_FORWARDLIGHTS"] = CMD_FORWARDLIGHTS;
    lua["CMD_LIGHTVOLUMES"] = CMD_LIGHTVOLUMES;
    lua["CMD_RENDERUI"] = CMD_RENDERUI;
    lua["CMD_SENDEVENT"] = CMD_SENDEVENT;

    // enum RenderCommandSortMode;
    lua["SORT_FRONTTOBACK"] = SORT_FRONTTOBACK;
    lua["SORT_BACKTOFRONT"] = SORT_BACKTOFRONT;

    // enum RenderTargetSizeMode;
    lua["SIZE_ABSOLUTE"] = SIZE_ABSOLUTE;
    lua["SIZE_VIEWPORTDIVISOR"] = SIZE_VIEWPORTDIVISOR;
    lua["SIZE_VIEWPORTMULTIPLIER"] = SIZE_VIEWPORTMULTIPLIER;

    lua["RenderTargetInfo"].setClass(UserdataMetatable<RenderTargetInfo>()
        .setConstructors<RenderTargetInfo()>()

        .addFunction("Load", &RenderTargetInfo::Load)
        
        .addProperty("name", &RenderTargetInfo::name_)
        .addProperty("tag", &RenderTargetInfo::tag_)
        .addProperty("format", &RenderTargetInfo::format_)
        .addProperty("size", &RenderTargetInfo::size_)
        .addProperty("sizeMode", &RenderTargetInfo::sizeMode_)
        .addProperty("enabled", &RenderTargetInfo::enabled_)
        .addProperty("cubemap", &RenderTargetInfo::cubemap_)
        .addProperty("filtered", &RenderTargetInfo::filtered_)
        .addProperty("sRGB", &RenderTargetInfo::sRGB_)
        .addProperty("persistent", &RenderTargetInfo::persistent_)
    );

    lua["RenderPathCommand"].setClass(UserdataMetatable<RenderPathCommand>()
        .setConstructors<RenderPathCommand()>()

        .addFunction("Load", &RenderPathCommand::Load)

        .addFunction("SetTextureName", &RenderPathCommand::SetTextureName)
        .addFunction("SetShaderParameter", &RenderPathCommand::SetShaderParameter)
        .addFunction("RemoveShaderParameter", &RenderPathCommand::RemoveShaderParameter)
        .addFunction("SetNumOutputs", &RenderPathCommand::SetNumOutputs)
        
        .addFunction("SetOutput", RenderPathCommandSetOutput())

        .addFunction("SetOutputName", &RenderPathCommand::SetOutputName)
        .addFunction("SetOutputFace", &RenderPathCommand::SetOutputFace)
        .addFunction("SetDepthStencilName", &RenderPathCommand::SetDepthStencilName)
        .addFunction("GetTextureName", &RenderPathCommand::GetTextureName)
        .addFunction("GetShaderParameter", &RenderPathCommand::GetShaderParameter)
        .addFunction("GetNumOutputs", &RenderPathCommand::GetNumOutputs)
        .addFunction("GetOutputName", &RenderPathCommand::GetOutputName)
        .addFunction("GetOutputFace", &RenderPathCommand::GetOutputFace)
        .addFunction("GetDepthStencilName", &RenderPathCommand::GetDepthStencilName)
        
        .addProperty("tag", &RenderPathCommand::tag_)
        .addProperty("type", &RenderPathCommand::type_)
        .addProperty("sortMode", &RenderPathCommand::sortMode_)
        .addProperty("pass", &RenderPathCommand::pass_)
        .addProperty("passIndex", &RenderPathCommand::passIndex_)
        .addProperty("metadata", &RenderPathCommand::metadata_)
        .addProperty("vertexShaderName", &RenderPathCommand::vertexShaderName_)
        .addProperty("pixelShaderName", &RenderPathCommand::pixelShaderName_)
        .addProperty("vertexShaderDefines", &RenderPathCommand::vertexShaderDefines_)
        .addProperty("pixelShaderDefines", &RenderPathCommand::pixelShaderDefines_)
        .addProperty("clearFlags", &RenderPathCommand::clearFlags_)
        .addProperty("clearColor", &RenderPathCommand::clearColor_)
        .addProperty("clearDepth", &RenderPathCommand::clearDepth_)
        .addProperty("clearStencil", &RenderPathCommand::clearStencil_)
        .addProperty("blendMode", &RenderPathCommand::blendMode_)
        .addProperty("enabled", &RenderPathCommand::enabled_)
        .addProperty("useFogColor", &RenderPathCommand::useFogColor_)
        .addProperty("markToStencil", &RenderPathCommand::markToStencil_)
        .addProperty("useLitBase", &RenderPathCommand::useLitBase_)
        .addProperty("vertexLights", &RenderPathCommand::vertexLights_)
        .addProperty("eventName", &RenderPathCommand::eventName_)
    );

    lua["RenderPath"].setClass(UserdataMetatable<RenderPath, RefCounted>()
        .setConstructors<RenderPath()>()

        .addFunction("Clone", &RenderPath::Clone)

		.addFunction("Load", &RenderPath::Load)
        .addFunction("Append", &RenderPath::Append)
        
        .addFunction("SetEnabled", &RenderPath::SetEnabled)
        .addFunction("ToggleEnabled", &RenderPath::ToggleEnabled)
        .addFunction("SetRenderTarget", &RenderPath::SetRenderTarget)
        .addFunction("AddRenderTarget", &RenderPath::AddRenderTarget)

        .addOverloadedFunctions("RemoveRenderTarget",
            static_cast<void(RenderPath::*)(unsigned)>(&RenderPath::RemoveRenderTarget),
            static_cast<void(RenderPath::*)(const String&)>(&RenderPath::RemoveRenderTarget))

        .addFunction("RemoveRenderTargets", &RenderPath::RemoveRenderTargets)

        .addFunction("SetCommand", &RenderPath::SetCommand)
        .addFunction("AddCommand", &RenderPath::AddCommand)
        .addFunction("InsertCommand", &RenderPath::InsertCommand)
        .addFunction("RemoveCommand", &RenderPath::RemoveCommand)
        .addFunction("RemoveCommands", &RenderPath::RemoveCommands)

        .addFunction("SetShaderParameter", &RenderPath::SetShaderParameter)
        
        .addFunction("GetNumRenderTargets", &RenderPath::GetNumRenderTargets)
        .addFunction("GetNumCommands", &RenderPath::GetNumCommands)
        .addFunction("GetCommand", &RenderPath::GetCommand)
        .addFunction("GetShaderParameter", &RenderPath::GetShaderParameter)
    );
}

static void RegisterRenderSurface(kaguya::State& lua)
{
    using namespace kaguya;

    lua["RenderSurface"].setClass(UserdataMetatable<RenderSurface, RefCounted>()
        .setConstructors<RenderSurface(Texture*)>()
        
        .addFunction("SetNumViewports", &RenderSurface::SetNumViewports)
        .addFunction("SetViewport", &RenderSurface::SetViewport)
        .addFunction("SetUpdateMode", &RenderSurface::SetUpdateMode)
        .addFunction("SetLinkedRenderTarget", &RenderSurface::SetLinkedRenderTarget)
        .addFunction("SetLinkedDepthStencil", &RenderSurface::SetLinkedDepthStencil)
        .addFunction("QueueUpdate", &RenderSurface::QueueUpdate)
        .addFunction("Release", &RenderSurface::Release)
        
        .addFunction("GetParentTexture", &RenderSurface::GetParentTexture)
        .addFunction("GetWidth", &RenderSurface::GetWidth)
        .addFunction("GetHeight", &RenderSurface::GetHeight)
        .addFunction("GetUsage", &RenderSurface::GetUsage)
        .addFunction("GetNumViewports", &RenderSurface::GetNumViewports)
        .addFunction("GetViewport", &RenderSurface::GetViewport)
        .addFunction("GetUpdateMode", &RenderSurface::GetUpdateMode)
        .addFunction("GetLinkedRenderTarget", &RenderSurface::GetLinkedRenderTarget)
        .addFunction("GetLinkedDepthStencil", &RenderSurface::GetLinkedDepthStencil)
        
        .addProperty("parentTexture", &RenderSurface::GetParentTexture)
        .addProperty("width", &RenderSurface::GetWidth)
        .addProperty("height", &RenderSurface::GetHeight)
        .addProperty("usage", &RenderSurface::GetUsage)
        .addProperty("numViewports", &RenderSurface::GetNumViewports, &RenderSurface::SetNumViewports)
        .addProperty("updateMode", &RenderSurface::GetUpdateMode, &RenderSurface::SetUpdateMode)
        .addProperty("linkedRenderTarget", &RenderSurface::GetLinkedRenderTarget, &RenderSurface::SetLinkedRenderTarget)
        .addProperty("linkedDepthStencil", &RenderSurface::GetLinkedDepthStencil, &RenderSurface::SetLinkedDepthStencil)
    );
}

KAGUYA_MEMBER_FUNCTION_OVERLOADS(TechniqueClone, Technique, Clone, 0, 1);

static void RegisterTechnique(kaguya::State& lua)
{
    using namespace kaguya;

    // enum PassLightingMode;
    lua["LIGHTING_UNLIT"] = LIGHTING_UNLIT;
    lua["LIGHTING_PERVERTEX"] = LIGHTING_PERVERTEX;
    lua["LIGHTING_PERPIXEL"] = LIGHTING_PERPIXEL;

    lua["Pass"].setClass(UserdataMetatable<Pass, RefCounted>()
        .setConstructors<Pass(const String&)>()
        
        .addFunction("SetBlendMode", &Pass::SetBlendMode)
        .addFunction("SetCullMode", &Pass::SetCullMode)
        .addFunction("SetDepthTestMode", &Pass::SetDepthTestMode)
        .addFunction("SetLightingMode", &Pass::SetLightingMode)
        .addFunction("SetDepthWrite", &Pass::SetDepthWrite)
        .addFunction("SetAlphaMask", &Pass::SetAlphaMask)
        .addFunction("SetIsDesktop", &Pass::SetIsDesktop)
        .addFunction("SetVertexShader", &Pass::SetVertexShader)
        .addFunction("SetPixelShader", &Pass::SetPixelShader)
        .addFunction("SetVertexShaderDefines", &Pass::SetVertexShaderDefines)
        .addFunction("SetPixelShaderDefines", &Pass::SetPixelShaderDefines)
        .addFunction("ReleaseShaders", &Pass::ReleaseShaders)
        

        .addFunction("GetName", &Pass::GetName)
        .addFunction("GetIndex", &Pass::GetIndex)
        .addFunction("GetBlendMode", &Pass::GetBlendMode)
        .addFunction("GetCullMode", &Pass::GetCullMode)
        .addFunction("GetDepthTestMode", &Pass::GetDepthTestMode)
        .addFunction("GetLightingMode", &Pass::GetLightingMode)
        .addFunction("GetShadersLoadedFrameNumber", &Pass::GetShadersLoadedFrameNumber)
        .addFunction("GetDepthWrite", &Pass::GetDepthWrite)
        .addFunction("GetAlphaMask", &Pass::GetAlphaMask)
        .addFunction("IsDesktop", &Pass::IsDesktop)
        .addFunction("GetVertexShader", &Pass::GetVertexShader)
        .addFunction("GetPixelShader", &Pass::GetPixelShader)
        .addFunction("GetVertexShaderDefines", &Pass::GetVertexShaderDefines)
        .addFunction("GetPixelShaderDefines", &Pass::GetPixelShaderDefines)

        .addProperty("name", &Pass::GetName)
        .addProperty("index", &Pass::GetIndex)
        .addProperty("blendMode", &Pass::GetBlendMode, &Pass::SetBlendMode)
        .addProperty("cullMode", &Pass::GetCullMode, &Pass::SetCullMode)
        .addProperty("depthTestMode", &Pass::GetDepthTestMode, &Pass::SetDepthTestMode)
        .addProperty("lightingMode", &Pass::GetLightingMode, &Pass::SetLightingMode)
        .addProperty("shadersLoadedFrameNumber", &Pass::GetShadersLoadedFrameNumber)
        .addProperty("depthWrite", &Pass::GetDepthWrite, &Pass::SetDepthWrite)
        .addProperty("alphaMask", &Pass::GetAlphaMask, &Pass::SetAlphaMask)
        .addProperty("desktop", &Pass::IsDesktop)
        .addProperty("vertexShader", &Pass::GetVertexShader, &Pass::SetVertexShader)
        .addProperty("pixelShader", &Pass::GetPixelShader, &Pass::SetPixelShader)
        .addProperty("vertexShaderDefines", &Pass::GetVertexShaderDefines, &Pass::SetVertexShaderDefines)
        .addProperty("pixelShaderDefines", &Pass::GetPixelShaderDefines, &Pass::SetPixelShaderDefines)        
    );

    lua["Technique"].setClass(UserdataMetatable<Technique, Resource>()
        .addStaticFunction("new", &CreateObject<Technique>)
        
        .addFunction("SetIsDesktop", &Technique::SetIsDesktop)
        .addFunction("CreatePass", &Technique::CreatePass)
        .addFunction("RemovePass", &Technique::RemovePass)
        .addFunction("ReleaseShaders", &Technique::ReleaseShaders)
        
        .addFunction("Clone", TechniqueClone())

        .addFunction("IsDesktop", &Technique::IsDesktop)
        .addFunction("IsSupported", &Technique::IsSupported)

        .addOverloadedFunctions("HasPass",
            static_cast<bool(Technique::*)(unsigned) const>(&Technique::HasPass),
            static_cast<bool(Technique::*)(const String&) const>(&Technique::HasPass))


        .addOverloadedFunctions("GetPass",
            static_cast<Pass*(Technique::*)(unsigned) const>(&Technique::GetPass),
            static_cast<Pass*(Technique::*)(const String&) const>(&Technique::GetPass))

        .addOverloadedFunctions("GetSupportedPass",
            static_cast<Pass*(Technique::*)(unsigned) const>(&Technique::GetSupportedPass),
            static_cast<Pass*(Technique::*)(const String&) const>(&Technique::GetSupportedPass))

        .addFunction("GetNumPasses", &Technique::GetNumPasses)

        .addFunction("GetPassNames", &Technique::GetPassNames)
        .addFunction("GetPasses", &Technique::GetPasses)

        .addProperty("desktop", &Technique::IsDesktop)
        .addProperty("supported", &Technique::IsSupported)
        .addProperty("numPasses", &Technique::GetNumPasses)        
    );
}

static void RegisterTexture(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Texture"].setClass(UserdataMetatable<Texture, Resource>()
        .addStaticFunction("new", &CreateObject<Texture>)
        
        .addFunction("SetNumLevels", &Texture::SetNumLevels)
        .addFunction("SetFilterMode", &Texture::SetFilterMode)
        .addFunction("SetAddressMode", &Texture::SetAddressMode)
        .addFunction("SetBorderColor", &Texture::SetBorderColor)
        .addFunction("SetSRGB", &Texture::SetSRGB)
        .addFunction("SetBackupTexture", &Texture::SetBackupTexture)
        .addFunction("SetMipsToSkip", &Texture::SetMipsToSkip)

        .addFunction("GetFormat", &Texture::GetFormat)
        .addFunction("IsCompressed", &Texture::IsCompressed)
        .addFunction("GetLevels", &Texture::GetLevels)
        .addFunction("GetWidth", &Texture::GetWidth)
        .addFunction("GetHeight", &Texture::GetHeight)
        .addFunction("GetDepth", &Texture::GetDepth)
        .addFunction("GetFilterMode", &Texture::GetFilterMode)
        .addFunction("GetAddressMode", &Texture::GetAddressMode)
        .addFunction("GetBorderColor", &Texture::GetBorderColor)
        .addFunction("GetSRGB", &Texture::GetSRGB)
        .addFunction("GetBackupTexture", &Texture::GetBackupTexture)
        .addFunction("GetMipsToSkip", &Texture::GetMipsToSkip)
        .addFunction("GetLevelWidth", &Texture::GetLevelWidth)
        .addFunction("GetLevelHeight", &Texture::GetLevelHeight)
        .addFunction("GetLevelDepth", &Texture::GetLevelDepth)
        .addFunction("GetUsage", &Texture::GetUsage)

        .addOverloadedFunctions("GetDataSize",
            static_cast<unsigned(Texture::*)(int, int) const>(&Texture::GetDataSize),
            static_cast<unsigned(Texture::*)(int, int, int) const>(&Texture::GetDataSize))

        .addFunction("GetRowDataSize", &Texture::GetRowDataSize)
        .addFunction("GetComponents", &Texture::GetComponents)

        .addProperty("format", &Texture::GetFormat)
        .addProperty("compressed", &Texture::IsCompressed)
        .addProperty("levels", &Texture::GetLevels)
        .addProperty("width", &Texture::GetWidth)
        .addProperty("height", &Texture::GetHeight)
        .addProperty("depth", &Texture::GetDepth)
        .addProperty("filterMode", &Texture::GetFilterMode, &Texture::SetFilterMode)
        .addProperty("borderColor", &Texture::GetBorderColor, &Texture::SetBorderColor)
        .addProperty("sRGB", &Texture::GetSRGB, &Texture::SetSRGB)
        .addProperty("backupTexture", &Texture::GetBackupTexture, &Texture::SetBackupTexture)
        .addProperty("usage", &Texture::GetUsage)
        .addProperty("components", &Texture::GetComponents)
    );
}

KAGUYA_MEMBER_FUNCTION_OVERLOADS(Texture2DSetSize, Texture2D, SetSize, 3, 4);
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(Texture2DSetData, Texture2D, SetData, 1, 2, bool(Texture2D::*)(Image*, bool));

static void RegisterTexture2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Texture2D"].setClass(UserdataMetatable<Texture2D, Texture>()
        .addStaticFunction("new", &CreateObject<Texture2D>)
        
        .addFunction("SetSize", Texture2DSetSize())
        .addFunction("SetData", Texture2DSetData())

        .addFunction("GetRenderSurface", &Texture2D::GetRenderSurface)

        .addProperty("renderSurface", &Texture2D::GetRenderSurface)
    );
}

KAGUYA_MEMBER_FUNCTION_OVERLOADS(Texture2DArraySetSize, Texture2DArray, SetSize, 4, 5);
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(Texture2DArraySetData, Texture2DArray, SetData, 1, 2, bool(Texture2D::*)(Image*, bool));

static void RegisterTexture2DArray(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Texture2DArray"].setClass(UserdataMetatable<Texture2DArray, Texture>()
        .addStaticFunction("new", &CreateObject<Texture2DArray>)
        
        .addFunction("SetLayers", &Texture2DArray::SetLayers)
        
        .addFunction("SetSize", Texture2DArraySetSize())
        .addFunction("SetData", Texture2DArraySetData())

        .addFunction("GetLayers", &Texture2DArray::GetLayers)
        .addFunction("GetRenderSurface", &Texture2DArray::GetRenderSurface)

        .addProperty("layers", &Texture2DArray::GetLayers, &Texture2DArray::SetLayers)
        .addProperty("renderSurface", &Texture2DArray::GetRenderSurface)
    );
}

KAGUYA_MEMBER_FUNCTION_OVERLOADS(Texture3DSetSize, Texture3D, SetSize, 4, 5);
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(Texture3DSetData, Texture3D, SetData, 1, 2, bool(Texture3D::*)(Image*, bool));

static void RegisterTexture3D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Texture3D"].setClass(UserdataMetatable<Texture3D, Texture>()
        .addStaticFunction("new", &CreateObject<Texture3D>)
        
        .addFunction("SetSize", Texture3DSetSize())
        .addFunction("SetData", Texture3DSetData())
    );
}

KAGUYA_MEMBER_FUNCTION_OVERLOADS(TextureCubeSetSize, TextureCube, SetSize, 2, 3);
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(TextureCubeSetData, TextureCube, SetData, 2, 3, bool(TextureCube::*)(CubeMapFace, Image*, bool));

static void RegisterTextureCube(kaguya::State& lua)
{
    using namespace kaguya;

    lua["TextureCube"].setClass(UserdataMetatable<TextureCube, Texture>()
        .addStaticFunction("new", &CreateObject<TextureCube>)
        
        .addFunction("SetSize", TextureCubeSetSize())
        .addFunction("SetData", TextureCubeSetData())

        .addFunction("GetRenderSurface", &TextureCube::GetRenderSurface)

        .addProperty("renderSurface", &TextureCube::GetRenderSurface)
    );
}

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(VertexBufferSetSize0, VertexBuffer, SetSize, 2, 3, bool(VertexBuffer::*)(unsigned, const PODVector<VertexElement>&, bool));
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(VertexBufferSetSize1, VertexBuffer, SetSize, 2, 3, bool(VertexBuffer::*)(unsigned, unsigned, bool));

static bool VertexBufferSetData(VertexBuffer* self, VectorBuffer& src)
{
    // Make sure there is enough data
    if (self->GetVertexCount() && src.GetSize() >= self->GetVertexCount() * self->GetVertexSize())
        return self->SetData(&src.GetBuffer()[0]);
    else
        return false;
}

static VectorBuffer VertexBufferGetData(VertexBuffer* self)
{
    VectorBuffer ret;

    void* data = self->Lock(0, self->GetVertexCount(), false);
    if (data)
    {
        ret.Write(data, self->GetVertexCount() * self->GetVertexSize());
        ret.Seek(0);
        self->Unlock();
    }

    return ret;
}

static SharedPtr<VertexBuffer> CreateVertexBuffer(bool forceHeadless = false)
{
    return SharedPtr<VertexBuffer>(new VertexBuffer(globalContext, forceHeadless));
}

KAGUYA_FUNCTION_OVERLOADS(CreateVertexBufferOverloads, CreateVertexBuffer, 0, 1);

KAGUYA_MEMBER_FUNCTION_OVERLOADS(VertexBufferSetDataRange, VertexBuffer, SetDataRange, 3, 4);

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(VertexBufferGetElement0, VertexBuffer, GetElement, 1, 2, const VertexElement*(VertexBuffer::*)(VertexElementSemantic, unsigned char)const);
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(VertexBufferGetElement1, VertexBuffer, GetElement, 2, 3, const VertexElement*(VertexBuffer::*)(VertexElementType, VertexElementSemantic, unsigned char)const);

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(VertexBufferHasElement0, VertexBuffer, HasElement, 1, 2, bool(VertexBuffer::*)(VertexElementSemantic, unsigned char)const);
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(VertexBufferHasElement1, VertexBuffer, HasElement, 2, 3, bool(VertexBuffer::*)(VertexElementType, VertexElementSemantic, unsigned char)const);

static void RegisterVertexBuffer(kaguya::State& lua)
{
    using namespace kaguya;

    lua["VertexBuffer"].setClass(UserdataMetatable<VertexBuffer, GPUObject>()
        .addStaticFunction("new", 
            CreateVertexBufferOverloads())

        .addFunction("SetShadowed", &VertexBuffer::SetShadowed)

        .addOverloadedFunctions("SetSize", 
            VertexBufferSetSize0(), 
            VertexBufferSetSize1())

        .addStaticFunction("SetData", &VertexBufferSetData)
        .addStaticFunction("GetData", &VertexBufferGetData)

        .addFunction("SetDataRange", VertexBufferSetDataRange())

        .addFunction("IsShadowed", &VertexBuffer::IsShadowed)
        .addFunction("IsDynamic", &VertexBuffer::IsDynamic)
        .addFunction("GetVertexCount", &VertexBuffer::GetVertexCount)
        .addFunction("GetVertexSize", &VertexBuffer::GetVertexSize)

        .addOverloadedFunctions("GetElement",
            VertexBufferGetElement0(),
            VertexBufferGetElement1())

        .addOverloadedFunctions("HasElement",
            VertexBufferHasElement0(),
            VertexBufferHasElement1())

        .addFunction("GetElementMask", &VertexBuffer::GetElementMask)

        .addProperty("shadowed", &VertexBuffer::IsShadowed, &VertexBuffer::SetShadowed)
        .addProperty("dynamic", &VertexBuffer::IsDynamic)
        .addProperty("vertexCount", &VertexBuffer::GetVertexCount)
        .addProperty("vertexSize", &VertexBuffer::GetVertexSize)
        .addProperty("elementMask", &VertexBuffer::GetElementMask)
    );
}

static SharedPtr<Viewport> CreateViewport0()
{
    return SharedPtr<Viewport>(new Viewport(globalContext));
}

static SharedPtr<Viewport> CreateViewport1(Scene* scene, Camera* camera)
{
    return SharedPtr<Viewport>(new Viewport(globalContext, scene, camera));
}

static SharedPtr<Viewport> CreateViewport2(Scene* scene, Camera* camera, RenderPath* renderPath)
{
    return SharedPtr<Viewport>(new Viewport(globalContext, scene, camera, renderPath));
}

static SharedPtr<Viewport> CreateViewport3(Scene* scene, Camera* camera, const IntRect& rect)
{
    return SharedPtr<Viewport>(new Viewport(globalContext, scene, camera, rect));
}

static SharedPtr<Viewport> CreateViewport4(Scene* scene, Camera* camera, const IntRect& rect, RenderPath* renderPath)
{
    return SharedPtr<Viewport>(new Viewport(globalContext, scene, camera, rect, renderPath));
}

static void RegisterViewport(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Viewport"].setClass(UserdataMetatable<Viewport, Object>()
        .addOverloadedFunctions("new", &CreateViewport0, &CreateViewport1, &CreateViewport2, &CreateViewport3, &CreateViewport4)

        .addFunction("SetScene", &Viewport::SetScene)
        .addFunction("SetCamera", &Viewport::SetCamera)
        .addFunction("SetRect", &Viewport::SetRect)

        .addOverloadedFunctions("SetRenderPath",
            static_cast<void(Viewport::*)(RenderPath*)>(&Viewport::SetRenderPath),
            static_cast<void(Viewport::*)(XMLFile*)>(&Viewport::SetRenderPath))

        .addFunction("SetDrawDebug", &Viewport::SetDrawDebug)
        .addFunction("SetCullCamera", &Viewport::SetCullCamera)
        
        .addFunction("GetScene", &Viewport::GetScene)
        .addFunction("GetCamera", &Viewport::GetCamera)
        .addFunction("GetRect", &Viewport::GetRect)
        .addFunction("GetRenderPath", &Viewport::GetRenderPath)
        .addFunction("GetDrawDebug", &Viewport::GetDrawDebug)
        .addFunction("GetCullCamera", &Viewport::GetCullCamera)
        
        .addFunction("GetScreenRay", &Viewport::GetScreenRay)
        .addFunction("WorldToScreenPoint", &Viewport::WorldToScreenPoint)
        .addFunction("ScreenToWorldPoint", &Viewport::ScreenToWorldPoint)
        
        .addProperty("scene", &Viewport::GetScene, &Viewport::SetScene)
        .addProperty("camera", &Viewport::GetCamera, &Viewport::SetCamera)
        .addProperty("rect", &Viewport::GetRect, &Viewport::SetRect)
        .addProperty("renderPath", &Viewport::GetRenderPath, static_cast<void (Viewport::*)(RenderPath*)>(&Viewport::SetRenderPath))
        .addProperty("drawDebug", &Viewport::GetDrawDebug, &Viewport::SetDrawDebug)
        .addProperty("cullCamera", &Viewport::GetCullCamera, &Viewport::SetCullCamera)
    );
}

void RegisterRendererLuaAPI(kaguya::State& lua)
{
    RegisterCamera(lua);
    RegisterGeometry(lua);
    RegisterMaterial(lua);
    RegisterDebugRenderer(lua);
    RegisterGraphics(lua);
    RegisterGraphicsDefs(lua);
    RegisterIndexBuffer(lua);
    RegisterRenderer(lua);
    RegisterRenderPath(lua);
    RegisterRenderSurface(lua);
    RegisterTechnique(lua);
    RegisterTexture(lua);
    RegisterTexture2D(lua);
    RegisterTexture2DArray(lua);
    RegisterTexture3D(lua);
    RegisterTextureCube(lua);
    RegisterVertexBuffer(lua);
    RegisterViewport(lua);

    lua["graphics"] = GetSubsystem<Graphics>();
    lua["GetGraphics"] = GetSubsystem<Graphics>();

    lua["renderer"] = GetSubsystem<Renderer>();
    lua["GetRenderer"] = GetSubsystem<Renderer>;
}
}
