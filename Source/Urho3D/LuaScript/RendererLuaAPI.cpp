#include "../Core/Context.h"
#include "../Graphics/Camera.h"
#include "../Graphics/DebugRenderer.h"
#include "../Graphics/Geometry.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/GraphicsDefs.h"
#include "../Graphics/GraphicsEvents.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/Material.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/RenderPath.h"
#include "../Graphics/RenderSurface.h"
#include "../Graphics/Shader.h"
#include "../Graphics/ShaderVariation.h"
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

static Graphics* GetGraphics()
{
    return globalContext->GetSubsystem<Graphics>();
}

static Renderer* GetRenderer()
{
    return globalContext->GetSubsystem<Renderer>();
}


static void RegisterCamera(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KDEFAULT_NEARCLIP"] = DEFAULT_NEARCLIP;
    lua["KDEFAULT_FARCLIP"] = DEFAULT_FARCLIP;
    lua["KDEFAULT_CAMERA_FOV"] = DEFAULT_CAMERA_FOV;
    lua["KDEFAULT_ORTHOSIZE"] = DEFAULT_ORTHOSIZE;
    lua["KVO_NONE"] = VO_NONE;
    lua["KVO_LOW_MATERIAL_QUALITY"] = VO_LOW_MATERIAL_QUALITY;
    lua["KVO_DISABLE_SHADOWS"] = VO_DISABLE_SHADOWS;
    lua["KVO_DISABLE_OCCLUSION"] = VO_DISABLE_OCCLUSION;

    lua["KCamera"].setClass(UserdataMetatable<Camera, Component>(false)
        .addStaticFunction("new", &KCreateObject<Camera>)
        .addStaticFunction("__gc", &KReleaseObject<Camera>)

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
        .addFunction("GetReverseCulling", &Camera::GetReverseCulling)
        .addFunction("GetDistance", &Camera::GetDistance)
        .addFunction("GetDistanceSquared", &Camera::GetDistanceSquared)
        .addFunction("GetLodDistance", &Camera::GetLodDistance)
        .addFunction("GetFaceCameraRotation", &Camera::GetFaceCameraRotation)
        .addFunction("GetEffectiveWorldTransform", &Camera::GetEffectiveWorldTransform)
        .addFunction("IsProjectionValid", &Camera::IsProjectionValid)
        .addFunction("SetAspectRatioInternal", &Camera::SetAspectRatioInternal)

        .addProperty("farClip", &Camera::GetFarClip, &Camera::SetFarClip)
        .addProperty("nearClip", &Camera::GetNearClip, &Camera::SetNearClip)
        .addProperty("fov", &Camera::GetFov, &Camera::SetFov)
        .addProperty("orthoSize", &Camera::GetOrthoSize)
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
        .addProperty("reverseCulling", &Camera::GetReverseCulling)
        .addProperty("effectiveWorldTransform", &Camera::GetEffectiveWorldTransform)
        .addProperty("projectionValid", &Camera::IsProjectionValid)
        .addProperty("aspectRatioInternal", &Camera::SetAspectRatioInternal)
    );
}


static void RegisterDebugRenderer(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KDebugRenderer"].setClass(UserdataMetatable<DebugRenderer, Component>(false)
        .addStaticFunction("new", &KCreateObject<DebugRenderer>)
        .addStaticFunction("__gc", &KReleaseObject<DebugRenderer>)

        .addFunction("SetView", &DebugRenderer::SetView)

        .addOverloadedFunctions("AddLine",
            static_cast<void(DebugRenderer::*)(const Vector3&, const Vector3&, const Color&, bool)>(&DebugRenderer::AddLine),
            static_cast<void(DebugRenderer::*)(const Vector3&, const Vector3&, unsigned, bool)>(&DebugRenderer::AddLine))


        .addOverloadedFunctions("AddTriangle",
            static_cast<void(DebugRenderer::*)(const Vector3&, const Vector3&, const Vector3&, const Color&, bool)>(&DebugRenderer::AddTriangle),
            static_cast<void(DebugRenderer::*)(const Vector3&, const Vector3&, const Vector3&, unsigned, bool)>(&DebugRenderer::AddTriangle))

        .addFunction("AddNode", &DebugRenderer::AddNode)

        .addOverloadedFunctions("AddBoundingBox",
            static_cast<void(DebugRenderer::*)(const BoundingBox&, const Color&, bool)>(&DebugRenderer::AddBoundingBox),
            static_cast<void(DebugRenderer::*)(const BoundingBox&, const Matrix3x4&, const Color&, bool)>(&DebugRenderer::AddBoundingBox))

        .addFunction("AddFrustum", &DebugRenderer::AddFrustum)
        .addFunction("AddPolyhedron", &DebugRenderer::AddPolyhedron)
        .addFunction("AddSphere", &DebugRenderer::AddSphere)
        .addFunction("AddCylinder", &DebugRenderer::AddCylinder)
        .addFunction("AddSkeleton", &DebugRenderer::AddSkeleton)
        .addFunction("AddTriangleMesh", &DebugRenderer::AddTriangleMesh)
        .addFunction("AddCircle", &DebugRenderer::AddCircle)
        .addFunction("AddCross", &DebugRenderer::AddCross)
        .addFunction("AddQuad", &DebugRenderer::AddQuad)
        .addFunction("Render", &DebugRenderer::Render)
        .addFunction("GetView", &DebugRenderer::GetView)
        .addFunction("GetProjection", &DebugRenderer::GetProjection)
        .addFunction("GetFrustum", &DebugRenderer::GetFrustum)
        .addFunction("IsInside", &DebugRenderer::IsInside)
        .addFunction("HasContent", &DebugRenderer::HasContent)

        .addProperty("view", &DebugRenderer::GetView, &DebugRenderer::SetView)
        .addProperty("projection", &DebugRenderer::GetProjection)
        .addProperty("frustum", &DebugRenderer::GetFrustum)
    );
}

static void RegisterGeometry(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KGeometry"].setClass(UserdataMetatable<Geometry, Object>(false)
        .addStaticFunction("new", &KCreateObject<Geometry>)
        .addStaticFunction("__gc", &KReleaseObject<Geometry>)

        .addFunction("SetNumVertexBuffers", &Geometry::SetNumVertexBuffers)
        .addFunction("SetVertexBuffer", &Geometry::SetVertexBuffer)
        .addFunction("SetIndexBuffer", &Geometry::SetIndexBuffer)

        .addOverloadedFunctions("SetDrawRange",
            static_cast<bool(Geometry::*)(PrimitiveType, unsigned, unsigned, bool)>(&Geometry::SetDrawRange),
            static_cast<bool(Geometry::*)(PrimitiveType, unsigned, unsigned, unsigned, unsigned, bool)>(&Geometry::SetDrawRange))

        .addFunction("SetLodDistance", &Geometry::SetLodDistance)

        .addFunction("GetVertexBuffers", &Geometry::GetVertexBuffers)
        .addFunction("GetNumVertexBuffers", &Geometry::GetNumVertexBuffers)
        .addFunction("GetVertexBuffer", &Geometry::GetVertexBuffer)
        .addFunction("GetIndexBuffer", &Geometry::GetIndexBuffer)
        .addFunction("GetPrimitiveType", &Geometry::GetPrimitiveType)
        .addFunction("GetIndexStart", &Geometry::GetIndexStart)
        .addFunction("GetIndexCount", &Geometry::GetIndexCount)
        .addFunction("GetVertexStart", &Geometry::GetVertexStart)
        .addFunction("GetVertexCount", &Geometry::GetVertexCount)
        .addFunction("GetLodDistance", &Geometry::GetLodDistance)
        .addFunction("GetBufferHash", &Geometry::GetBufferHash)

        .addFunction("GetHitDistance", &Geometry::GetHitDistance)
        .addFunction("IsInside", &Geometry::IsInside)
        .addFunction("IsEmpty", &Geometry::IsEmpty)


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

    // GC is disable for subsystem object
    lua["KGraphics"].setClass(UserdataMetatable<Graphics, Object>(false)

        .addFunction("SetExternalWindow", &Graphics::SetExternalWindow)
        .addFunction("SetWindowIcon", &Graphics::SetWindowIcon)
        .addFunction("SetWindowTitle", &Graphics::SetWindowTitle)

        .addOverloadedFunctions("SetWindowPosition",
            static_cast<void(Graphics::*)(const IntVector2&)>(&Graphics::SetWindowPosition),
            static_cast<void(Graphics::*)(int, int)>(&Graphics::SetWindowPosition))

        .addOverloadedFunctions("SetMode",
            static_cast<bool(Graphics::*)(int, int, bool, bool, bool, bool, bool, bool, int)>(&Graphics::SetMode),
            static_cast<bool(Graphics::*)(int, int)>(&Graphics::SetMode))

        .addFunction("SetSRGB", &Graphics::SetSRGB)
        .addFunction("SetOrientations", &Graphics::SetOrientations)
        .addFunction("ToggleFullscreen", &Graphics::ToggleFullscreen)
        .addFunction("Close", &Graphics::Close)
        .addFunction("TakeScreenShot", &Graphics::TakeScreenShot)

        .addFunction("SetViewport", &Graphics::SetViewport)

        .addFunction("IsInitialized", &Graphics::IsInitialized)
        .addFunction("GetExternalWindow", &Graphics::GetExternalWindow)
        .addFunction("GetWindowTitle", &Graphics::GetWindowTitle)
        .addFunction("GetApiName", &Graphics::GetApiName)
        .addFunction("GetWindowPosition", &Graphics::GetWindowPosition)
        .addFunction("GetWidth", &Graphics::GetWidth)
        .addFunction("GetHeight", &Graphics::GetHeight)
        .addFunction("GetMultiSample", &Graphics::GetMultiSample)
        .addFunction("GetFullscreen", &Graphics::GetFullscreen)
        .addFunction("GetBorderless", &Graphics::GetBorderless)
        .addFunction("GetResizable", &Graphics::GetResizable)
        .addFunction("GetHighDPI", &Graphics::GetHighDPI)
        .addFunction("GetVSync", &Graphics::GetVSync)
        .addFunction("GetTripleBuffer", &Graphics::GetTripleBuffer)
        .addFunction("GetSRGB", &Graphics::GetSRGB)
        .addFunction("GetOrientations", &Graphics::GetOrientations)

        .addFunction("GetNumPrimitives", &Graphics::GetNumPrimitives)
        .addFunction("GetNumBatches", &Graphics::GetNumBatches)
        .addFunction("GetDummyColorFormat", &Graphics::GetDummyColorFormat)
        .addFunction("GetShadowMapFormat", &Graphics::GetShadowMapFormat)
        .addFunction("GetHiresShadowMapFormat", &Graphics::GetHiresShadowMapFormat)
        .addFunction("GetInstancingSupport", &Graphics::GetInstancingSupport)
        .addFunction("GetLightPrepassSupport", &Graphics::GetLightPrepassSupport)
        .addFunction("GetDeferredSupport", &Graphics::GetDeferredSupport)
        // .addFunction("GetAnisotropySupport", &Graphics::GetAnisotropySupport)
        .addFunction("GetHardwareShadowSupport", &Graphics::GetHardwareShadowSupport)
        .addFunction("GetReadableDepthSupport", &Graphics::GetReadableDepthSupport)
        .addFunction("GetSRGBSupport", &Graphics::GetSRGBSupport)
        .addFunction("GetSRGBWriteSupport", &Graphics::GetSRGBWriteSupport)
        .addFunction("GetResolutions", &Graphics::GetResolutions)
        .addFunction("GetMultiSampleLevels", &Graphics::GetMultiSampleLevels)
        .addFunction("GetDesktopResolution", &Graphics::GetDesktopResolution)

        .addFunction("GetDefaultTextureFilterMode", &Graphics::GetDefaultTextureFilterMode)

        .addFunction("GetViewport", &Graphics::GetViewport)
        .addFunction("GetTextureAnisotropy", &Graphics::GetTextureAnisotropy)

        .addFunction("GetStencilCompareMask", &Graphics::GetStencilCompareMask)
        .addFunction("GetStencilWriteMask", &Graphics::GetStencilWriteMask)
        .addFunction("GetUseClipPlane", &Graphics::GetUseClipPlane)
        .addFunction("GetRenderTargetDimensions", &Graphics::GetRenderTargetDimensions)

        // .addFunction("Restore", &Graphics::Restore)
        .addFunction("Maximize", &Graphics::Maximize)
        .addFunction("Minimize", &Graphics::Minimize)

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
        // .addStaticFunction("GetGL3Support", &Graphics::GetGL3Support)

        .addProperty("type", &Graphics::GetType)
        .addProperty("initialized", &Graphics::IsInitialized)
        .addProperty("externalWindow", &Graphics::GetExternalWindow, &Graphics::SetExternalWindow)
        .addProperty("windowTitle", &Graphics::GetWindowTitle, &Graphics::SetWindowTitle)
        .addProperty("apiName", &Graphics::GetApiName)
        .addProperty("windowPosition", &Graphics::GetWindowPosition)
        .addProperty("width", &Graphics::GetWidth)
        .addProperty("height", &Graphics::GetHeight)
        .addProperty("multiSample", &Graphics::GetMultiSample)

        .addProperty("fullscreen", &Graphics::GetFullscreen)
        .addProperty("borderless", &Graphics::GetBorderless)
        .addProperty("resizable", &Graphics::GetResizable)

        .addProperty("highDPI", &Graphics::GetHighDPI)
        .addProperty("vSync", &Graphics::GetVSync)
        .addProperty("tripleBuffer", &Graphics::GetTripleBuffer)
        .addProperty("sRGB", &Graphics::GetSRGB, &Graphics::SetSRGB)
        .addProperty("orientations", &Graphics::GetOrientations, &Graphics::SetOrientations)

        .addProperty("numPrimitives", &Graphics::GetNumPrimitives)
        .addProperty("numBatches", &Graphics::GetNumBatches)
        .addProperty("dummyColorFormat", &Graphics::GetDummyColorFormat)
        .addProperty("shadowMapFormat", &Graphics::GetShadowMapFormat)
        .addProperty("hiresShadowMapFormat", &Graphics::GetHiresShadowMapFormat)
        .addProperty("instancingSupport", &Graphics::GetInstancingSupport)
        .addProperty("lightPrepassSupport", &Graphics::GetLightPrepassSupport)
        .addProperty("deferredSupport", &Graphics::GetDeferredSupport)
        // .addProperty("anisotropySupport", &Graphics::GetAnisotropySupport)
        .addProperty("hardwareShadowSupport", &Graphics::GetHardwareShadowSupport)
        .addProperty("readableDepthSupport", &Graphics::GetReadableDepthSupport)
        .addProperty("sRGBSupport", &Graphics::GetSRGBSupport)
        .addProperty("sRGBWriteSupport", &Graphics::GetSRGBWriteSupport)
        .addProperty("resolutions", &Graphics::GetResolutions)
        .addProperty("multiSampleLevels", &Graphics::GetMultiSampleLevels)
        .addProperty("desktopResolution", &Graphics::GetDesktopResolution)

        .addProperty("defaultTextureFilterMode", &Graphics::GetDefaultTextureFilterMode, &Graphics::SetDefaultTextureFilterMode)

        .addProperty("viewport", &Graphics::GetViewport, &Graphics::SetViewport)
        .addProperty("textureAnisotropy", &Graphics::GetTextureAnisotropy, &Graphics::SetTextureAnisotropy)

        .addProperty("useClipPlane", &Graphics::GetUseClipPlane)
        .addProperty("renderTargetDimensions", &Graphics::GetRenderTargetDimensions)
        .addProperty("windowIcon", &Graphics::SetWindowIcon)
    );
}

static void RegisterGraphicsDefs(kaguya::State& lua)
{
    using namespace kaguya;

    // enum PrimitiveType;
    lua["KTRIANGLE_LIST"] = TRIANGLE_LIST;
    lua["KLINE_LIST"] = LINE_LIST;
    lua["KPOINT_LIST"] = POINT_LIST;
    lua["KTRIANGLE_STRIP"] = TRIANGLE_STRIP;
    lua["KLINE_STRIP"] = LINE_STRIP;
    lua["KTRIANGLE_FAN"] = TRIANGLE_FAN;

    // enum GeometryType;
    lua["KGEOM_STATIC"] = GEOM_STATIC;
    lua["KGEOM_SKINNED"] = GEOM_SKINNED;
    lua["KGEOM_INSTANCED"] = GEOM_INSTANCED;
    lua["KGEOM_BILLBOARD"] = GEOM_BILLBOARD;
    lua["KGEOM_DIRBILLBOARD"] = GEOM_DIRBILLBOARD;
    lua["KGEOM_TRAIL_FACE_CAMERA"] = GEOM_TRAIL_FACE_CAMERA;
    lua["KGEOM_TRAIL_BONE"] = GEOM_TRAIL_BONE;
    lua["KGEOM_STATIC_NOINSTANCING"] = GEOM_STATIC_NOINSTANCING;
    lua["KMAX_GEOMETRYTYPES"] = MAX_GEOMETRYTYPES;

    // enum BlendMode;
    lua["KBLEND_REPLACE"] = BLEND_REPLACE;
    lua["KBLEND_ADD"] = BLEND_ADD;
    lua["KBLEND_MULTIPLY"] = BLEND_MULTIPLY;
    lua["KBLEND_ALPHA"] = BLEND_ALPHA;
    lua["KBLEND_ADDALPHA"] = BLEND_ADDALPHA;
    lua["KBLEND_PREMULALPHA"] = BLEND_PREMULALPHA;
    lua["KBLEND_INVDESTALPHA"] = BLEND_INVDESTALPHA;
    lua["KBLEND_SUBTRACT"] = BLEND_SUBTRACT;
    lua["KBLEND_SUBTRACTALPHA"] = BLEND_SUBTRACTALPHA;
    lua["KMAX_BLENDMODES"] = MAX_BLENDMODES;

    // enum CompareMode;
    lua["KCMP_ALWAYS"] = CMP_ALWAYS;
    lua["KCMP_EQUAL"] = CMP_EQUAL;
    lua["KCMP_NOTEQUAL"] = CMP_NOTEQUAL;
    lua["KCMP_LESS"] = CMP_LESS;
    lua["KCMP_LESSEQUAL"] = CMP_LESSEQUAL;
    lua["KCMP_GREATER"] = CMP_GREATER;
    lua["KCMP_GREATEREQUAL"] = CMP_GREATEREQUAL;
    lua["KMAX_COMPAREMODES"] = MAX_COMPAREMODES;

    // enum CullMode;
    lua["KCULL_NONE"] = CULL_NONE;
    lua["KCULL_CCW"] = CULL_CCW;
    lua["KCULL_CW"] = CULL_CW;
    lua["KMAX_CULLMODES"] = MAX_CULLMODES;

    // enum FillMode;
    lua["KFILL_SOLID"] = FILL_SOLID;
    lua["KFILL_WIREFRAME"] = FILL_WIREFRAME;
    lua["KFILL_POINT"] = FILL_POINT;

    // enum StencilOp;
    lua["KOP_KEEP"] = OP_KEEP;
    lua["KOP_ZERO"] = OP_ZERO;
    lua["KOP_REF"] = OP_REF;
    lua["KOP_INCR"] = OP_INCR;
    lua["KOP_DECR"] = OP_DECR;

    // enum LockState;
    lua["KLOCK_NONE"] = LOCK_NONE;
    lua["KLOCK_HARDWARE"] = LOCK_HARDWARE;
    lua["KLOCK_SHADOW"] = LOCK_SHADOW;
    lua["KLOCK_SCRATCH"] = LOCK_SCRATCH;

    // enum LegacyVertexElement;
    lua["KELEMENT_POSITION"] = ELEMENT_POSITION;
    lua["KELEMENT_NORMAL"] = ELEMENT_NORMAL;
    lua["KELEMENT_COLOR"] = ELEMENT_COLOR;
    lua["KELEMENT_TEXCOORD1"] = ELEMENT_TEXCOORD1;
    lua["KELEMENT_TEXCOORD2"] = ELEMENT_TEXCOORD2;
    lua["KELEMENT_CUBETEXCOORD1"] = ELEMENT_CUBETEXCOORD1;
    lua["KELEMENT_CUBETEXCOORD2"] = ELEMENT_CUBETEXCOORD2;
    lua["KELEMENT_TANGENT"] = ELEMENT_TANGENT;
    lua["KELEMENT_BLENDWEIGHTS"] = ELEMENT_BLENDWEIGHTS;
    lua["KELEMENT_BLENDINDICES"] = ELEMENT_BLENDINDICES;
    lua["KELEMENT_INSTANCEMATRIX1"] = ELEMENT_INSTANCEMATRIX1;
    lua["KELEMENT_INSTANCEMATRIX2"] = ELEMENT_INSTANCEMATRIX2;
    lua["KELEMENT_INSTANCEMATRIX3"] = ELEMENT_INSTANCEMATRIX3;
    lua["KELEMENT_OBJECTINDEX"] = ELEMENT_OBJECTINDEX;
    lua["KMAX_LEGACY_VERTEX_ELEMENTS"] = MAX_LEGACY_VERTEX_ELEMENTS;

    // enum VertexElementType;
    lua["KTYPE_INT"] = TYPE_INT;
    lua["KTYPE_FLOAT"] = TYPE_FLOAT;
    lua["KTYPE_VECTOR2"] = TYPE_VECTOR2;
    lua["KTYPE_VECTOR3"] = TYPE_VECTOR3;
    lua["KTYPE_VECTOR4"] = TYPE_VECTOR4;
    lua["KTYPE_UBYTE4"] = TYPE_UBYTE4;
    lua["KTYPE_UBYTE4_NORM"] = TYPE_UBYTE4_NORM;
    lua["KMAX_VERTEX_ELEMENT_TYPES"] = MAX_VERTEX_ELEMENT_TYPES;

    // enum VertexElementSemantic;
    lua["KSEM_POSITION"] = SEM_POSITION;
    lua["KSEM_NORMAL"] = SEM_NORMAL;
    lua["KSEM_BINORMAL"] = SEM_BINORMAL;
    lua["KSEM_TANGENT"] = SEM_TANGENT;
    lua["KSEM_TEXCOORD"] = SEM_TEXCOORD;
    lua["KSEM_COLOR"] = SEM_COLOR;
    lua["KSEM_BLENDWEIGHTS"] = SEM_BLENDWEIGHTS;
    lua["KSEM_BLENDINDICES"] = SEM_BLENDINDICES;
    lua["KSEM_OBJECTINDEX"] = SEM_OBJECTINDEX;
    lua["KMAX_VERTEX_ELEMENT_SEMANTICS"] = MAX_VERTEX_ELEMENT_SEMANTICS;

    lua["KVertexElement"].setClass(UserdataMetatable<VertexElement>()
        .setConstructors<VertexElement(),
        VertexElement(VertexElementType, VertexElementSemantic, unsigned char, bool)>()

        .addFunction("__eq", &VertexElement::operator==)

        .addProperty("type", &VertexElement::type_)
        .addProperty("semantic", &VertexElement::semantic_)
        .addProperty("index", &VertexElement::index_)
        .addProperty("perInstance", &VertexElement::perInstance_)
        .addProperty("offset", &VertexElement::offset_)
    );

    // enum TextureFilterMode;
    lua["KFILTER_NEAREST"] = FILTER_NEAREST;
    lua["KFILTER_BILINEAR"] = FILTER_BILINEAR;
    lua["KFILTER_TRILINEAR"] = FILTER_TRILINEAR;
    lua["KFILTER_ANISOTROPIC"] = FILTER_ANISOTROPIC;
    lua["KFILTER_DEFAULT"] = FILTER_DEFAULT;
    lua["KMAX_FILTERMODES"] = MAX_FILTERMODES;

    // enum TextureAddressMode;
    lua["KADDRESS_WRAP"] = ADDRESS_WRAP;
    lua["KADDRESS_MIRROR"] = ADDRESS_MIRROR;
    lua["KADDRESS_CLAMP"] = ADDRESS_CLAMP;
    lua["KADDRESS_BORDER"] = ADDRESS_BORDER;
    lua["KMAX_ADDRESSMODES"] = MAX_ADDRESSMODES;

    // enum TextureCoordinate;
    lua["KCOORD_U"] = COORD_U;
    lua["KCOORD_V"] = COORD_V;
    lua["KCOORD_W"] = COORD_W;
    lua["KMAX_COORDS"] = MAX_COORDS;

    // enum TextureUsage;
    lua["KTEXTURE_STATIC"] = TEXTURE_STATIC;
    lua["KTEXTURE_DYNAMIC"] = TEXTURE_DYNAMIC;
    lua["KTEXTURE_RENDERTARGET"] = TEXTURE_RENDERTARGET;
    lua["KTEXTURE_DEPTHSTENCIL"] = TEXTURE_DEPTHSTENCIL;

    // enum CubeMapFace;
    lua["KFACE_POSITIVE_X"] = FACE_POSITIVE_X;
    lua["KFACE_NEGATIVE_X"] = FACE_NEGATIVE_X;
    lua["KFACE_POSITIVE_Y"] = FACE_POSITIVE_Y;
    lua["KFACE_NEGATIVE_Y"] = FACE_NEGATIVE_Y;
    lua["KFACE_POSITIVE_Z"] = FACE_POSITIVE_Z;
    lua["KFACE_NEGATIVE_Z"] = FACE_NEGATIVE_Z;
    lua["KMAX_CUBEMAP_FACES"] = MAX_CUBEMAP_FACES;

    // enum CubeMapLayout;
    lua["KCML_HORIZONTAL"] = CML_HORIZONTAL;
    lua["KCML_HORIZONTALNVIDIA"] = CML_HORIZONTALNVIDIA;
    lua["KCML_HORIZONTALCROSS"] = CML_HORIZONTALCROSS;
    lua["KCML_VERTICALCROSS"] = CML_VERTICALCROSS;
    lua["KCML_BLENDER"] = CML_BLENDER;

    // enum RenderSurfaceUpdateMode;
    lua["KSURFACE_MANUALUPDATE"] = SURFACE_MANUALUPDATE;
    lua["KSURFACE_UPDATEVISIBLE"] = SURFACE_UPDATEVISIBLE;
    lua["KSURFACE_UPDATEALWAYS"] = SURFACE_UPDATEALWAYS;

    // enum ShaderType;
    lua["KVS"] = VS;
    lua["KPS"] = PS;

    // enum ShaderParameterGroup;
    lua["KSP_FRAME"] = SP_FRAME;
    lua["KSP_CAMERA"] = SP_CAMERA;
    lua["KSP_ZONE"] = SP_ZONE;
    lua["KSP_LIGHT"] = SP_LIGHT;
    lua["KSP_MATERIAL"] = SP_MATERIAL;
    lua["KSP_OBJECT"] = SP_OBJECT;
    lua["KSP_CUSTOM"] = SP_CUSTOM;
    lua["KMAX_SHADER_PARAMETER_GROUPS"] = MAX_SHADER_PARAMETER_GROUPS;

    // enum TextureUnit;
    lua["KTU_DIFFUSE"] = TU_DIFFUSE;
    lua["KTU_ALBEDOBUFFER"] = TU_ALBEDOBUFFER;
    lua["KTU_NORMAL"] = TU_NORMAL;
    lua["KTU_NORMALBUFFER"] = TU_NORMALBUFFER;
    lua["KTU_SPECULAR"] = TU_SPECULAR;
    lua["KTU_EMISSIVE"] = TU_EMISSIVE;
    lua["KTU_ENVIRONMENT"] = TU_ENVIRONMENT;
    lua["KTU_VOLUMEMAP"] = TU_VOLUMEMAP;
    lua["KTU_CUSTOM1"] = TU_CUSTOM1;
    lua["KTU_CUSTOM2"] = TU_CUSTOM2;
    lua["KTU_LIGHTRAMP"] = TU_LIGHTRAMP;
    lua["KTU_LIGHTSHAPE"] = TU_LIGHTSHAPE;
    lua["KTU_SHADOWMAP"] = TU_SHADOWMAP;
    lua["KTU_FACESELECT"] = TU_FACESELECT;
    lua["KTU_INDIRECTION"] = TU_INDIRECTION;
    lua["KTU_DEPTHBUFFER"] = TU_DEPTHBUFFER;
    lua["KTU_LIGHTBUFFER"] = TU_LIGHTBUFFER;
    lua["KTU_ZONE"] = TU_ZONE;
    lua["KMAX_MATERIAL_TEXTURE_UNITS"] = MAX_MATERIAL_TEXTURE_UNITS;
    lua["KMAX_TEXTURE_UNITS"] = MAX_TEXTURE_UNITS;

    // enum FaceCameraMode;
    lua["KFC_NONE"] = FC_NONE;
    lua["KFC_ROTATE_XYZ"] = FC_ROTATE_XYZ;
    lua["KFC_ROTATE_Y"] = FC_ROTATE_Y;
    lua["KFC_LOOKAT_XYZ"] = FC_LOOKAT_XYZ;
    lua["KFC_LOOKAT_Y"] = FC_LOOKAT_Y;
    lua["KFC_DIRECTION"] = FC_DIRECTION;

    // enum ShadowQuality;
    lua["KSHADOWQUALITY_SIMPLE_16BIT"] = SHADOWQUALITY_SIMPLE_16BIT;
    lua["KSHADOWQUALITY_SIMPLE_24BIT"] = SHADOWQUALITY_SIMPLE_24BIT;
    lua["KSHADOWQUALITY_PCF_16BIT"] = SHADOWQUALITY_PCF_16BIT;
    lua["KSHADOWQUALITY_PCF_24BIT"] = SHADOWQUALITY_PCF_24BIT;
    lua["KSHADOWQUALITY_VSM"] = SHADOWQUALITY_VSM;
    lua["KSHADOWQUALITY_BLUR_VSM"] = SHADOWQUALITY_BLUR_VSM;

    /*
    lua["KVSP_AMBIENTSTARTCOLOR"] = VSP_AMBIENTSTARTCOLOR;
    lua["KVSP_AMBIENTENDCOLOR"] = VSP_AMBIENTENDCOLOR;
    lua["KVSP_BILLBOARDROT"] = VSP_BILLBOARDROT;
    lua["KVSP_CAMERAPOS"] = VSP_CAMERAPOS;
    lua["KVSP_CLIPPLANE"] = VSP_CLIPPLANE;
    lua["KVSP_NEARCLIP"] = VSP_NEARCLIP;
    lua["KVSP_FARCLIP"] = VSP_FARCLIP;
    lua["KVSP_DEPTHMODE"] = VSP_DEPTHMODE;
    lua["KVSP_DELTATIME"] = VSP_DELTATIME;
    lua["KVSP_ELAPSEDTIME"] = VSP_ELAPSEDTIME;
    lua["KVSP_FRUSTUMSIZE"] = VSP_FRUSTUMSIZE;
    lua["KVSP_GBUFFEROFFSETS"] = VSP_GBUFFEROFFSETS;
    lua["KVSP_LIGHTDIR"] = VSP_LIGHTDIR;
    lua["KVSP_LIGHTPOS"] = VSP_LIGHTPOS;
    lua["KVSP_NORMALOFFSETSCALE"] = VSP_NORMALOFFSETSCALE;
    lua["KVSP_MODEL"] = VSP_MODEL;
    lua["KVSP_VIEW"] = VSP_VIEW;
    lua["KVSP_VIEWINV"] = VSP_VIEWINV;
    lua["KVSP_VIEWPROJ"] = VSP_VIEWPROJ;
    lua["KVSP_UOFFSET"] = VSP_UOFFSET;
    lua["KVSP_VOFFSET"] = VSP_VOFFSET;
    lua["KVSP_ZONE"] = VSP_ZONE;
    lua["KVSP_LIGHTMATRICES"] = VSP_LIGHTMATRICES;
    lua["KVSP_SKINMATRICES"] = VSP_SKINMATRICES;
    lua["KVSP_VERTEXLIGHTS"] = VSP_VERTEXLIGHTS;
    lua["KPSP_AMBIENTCOLOR"] = PSP_AMBIENTCOLOR;
    lua["KPSP_CAMERAPOS"] = PSP_CAMERAPOS;
    lua["KPSP_DELTATIME"] = PSP_DELTATIME;
    lua["KPSP_DEPTHRECONSTRUCT"] = PSP_DEPTHRECONSTRUCT;
    lua["KPSP_ELAPSEDTIME"] = PSP_ELAPSEDTIME;
    lua["KPSP_FOGCOLOR"] = PSP_FOGCOLOR;
    lua["KPSP_FOGPARAMS"] = PSP_FOGPARAMS;
    lua["KPSP_GBUFFERINVSIZE"] = PSP_GBUFFERINVSIZE;
    lua["KPSP_LIGHTCOLOR"] = PSP_LIGHTCOLOR;
    lua["KPSP_LIGHTDIR"] = PSP_LIGHTDIR;
    lua["KPSP_LIGHTPOS"] = PSP_LIGHTPOS;
    lua["KPSP_NORMALOFFSETSCALE"] = PSP_NORMALOFFSETSCALE;
    lua["KPSP_MATDIFFCOLOR"] = PSP_MATDIFFCOLOR;
    lua["KPSP_MATEMISSIVECOLOR"] = PSP_MATEMISSIVECOLOR;
    lua["KPSP_MATENVMAPCOLOR"] = PSP_MATENVMAPCOLOR;
    lua["KPSP_MATSPECCOLOR"] = PSP_MATSPECCOLOR;
    lua["KPSP_NEARCLIP"] = PSP_NEARCLIP;
    lua["KPSP_FARCLIP"] = PSP_FARCLIP;
    lua["KPSP_SHADOWCUBEADJUST"] = PSP_SHADOWCUBEADJUST;
    lua["KPSP_SHADOWDEPTHFADE"] = PSP_SHADOWDEPTHFADE;
    lua["KPSP_SHADOWINTENSITY"] = PSP_SHADOWINTENSITY;
    lua["KPSP_SHADOWMAPINVSIZE"] = PSP_SHADOWMAPINVSIZE;
    lua["KPSP_SHADOWSPLITS"] = PSP_SHADOWSPLITS;
    lua["KPSP_LIGHTMATRICES"] = PSP_LIGHTMATRICES;
    lua["KPSP_VSMSHADOWPARAMS"] = PSP_VSMSHADOWPARAMS;
    lua["KPSP_ROUGHNESS"] = PSP_ROUGHNESS;
    lua["KPSP_METALLIC"] = PSP_METALLIC;
    */

    lua["KDOT_SCALE"] = DOT_SCALE;
    lua["KQUALITY_LOW"] = QUALITY_LOW;
    lua["KQUALITY_MEDIUM"] = QUALITY_MEDIUM;
    lua["KQUALITY_HIGH"] = QUALITY_HIGH;
    lua["KQUALITY_MAX"] = QUALITY_MAX;
    lua["KCLEAR_COLOR"] = CLEAR_COLOR;
    lua["KCLEAR_DEPTH"] = CLEAR_DEPTH;
    lua["KCLEAR_STENCIL"] = CLEAR_STENCIL;
    lua["KMASK_NONE"] = MASK_NONE;
    lua["KMASK_POSITION"] = MASK_POSITION;
    lua["KMASK_NORMAL"] = MASK_NORMAL;
    lua["KMASK_COLOR"] = MASK_COLOR;
    lua["KMASK_TEXCOORD1"] = MASK_TEXCOORD1;
    lua["KMASK_TEXCOORD2"] = MASK_TEXCOORD2;
    lua["KMASK_CUBETEXCOORD1"] = MASK_CUBETEXCOORD1;
    lua["KMASK_CUBETEXCOORD2"] = MASK_CUBETEXCOORD2;
    lua["KMASK_TANGENT"] = MASK_TANGENT;
    lua["KMASK_BLENDWEIGHTS"] = MASK_BLENDWEIGHTS;
    lua["KMASK_BLENDINDICES"] = MASK_BLENDINDICES;
    lua["KMASK_INSTANCEMATRIX1"] = MASK_INSTANCEMATRIX1;
    lua["KMASK_INSTANCEMATRIX2"] = MASK_INSTANCEMATRIX2;
    lua["KMASK_INSTANCEMATRIX3"] = MASK_INSTANCEMATRIX3;
    lua["KMASK_OBJECTINDEX"] = MASK_OBJECTINDEX;
    lua["KMAX_RENDERTARGETS"] = MAX_RENDERTARGETS;
    lua["KMAX_VERTEX_STREAMS"] = MAX_VERTEX_STREAMS;
    lua["KMAX_CONSTANT_REGISTERS"] = MAX_CONSTANT_REGISTERS;
    lua["KBITS_PER_COMPONENT"] = BITS_PER_COMPONENT;
}

static void RegisterGraphicsEvents(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KE_SCREENMODE"] = E_SCREENMODE;
    lua["KE_WINDOWPOS"] = E_WINDOWPOS;
    lua["KE_RENDERSURFACEUPDATE"] = E_RENDERSURFACEUPDATE;
    lua["KE_BEGINRENDERING"] = E_BEGINRENDERING;
    lua["KE_ENDRENDERING"] = E_ENDRENDERING;
    lua["KE_BEGINVIEWUPDATE"] = E_BEGINVIEWUPDATE;
    lua["KE_ENDVIEWUPDATE"] = E_ENDVIEWUPDATE;
    lua["KE_BEGINVIEWRENDER"] = E_BEGINVIEWRENDER;
    lua["KE_ENDVIEWRENDER"] = E_ENDVIEWRENDER;
    lua["KE_RENDERPATHEVENT"] = E_RENDERPATHEVENT;
    lua["KE_DEVICELOST"] = E_DEVICELOST;
    lua["KE_DEVICERESET"] = E_DEVICERESET;
}

static void RegisterIndexBuffer(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KIndexBuffer"].setClass(UserdataMetatable<IndexBuffer, Object>(false)
        .addStaticFunction("new", &KCreateObject<IndexBuffer>)
        .addStaticFunction("__gc", &KReleaseObject<IndexBuffer>)

        .addFunction("SetShadowed", &IndexBuffer::SetShadowed)
        .addFunction("SetSize", &IndexBuffer::SetSize)
        .addFunction("SetDataRange", &IndexBuffer::SetDataRange)

        .addFunction("IsShadowed", &IndexBuffer::IsShadowed)
        .addFunction("IsDynamic", &IndexBuffer::IsDynamic)
        .addFunction("IsLocked", &IndexBuffer::IsLocked)

        .addFunction("GetIndexCount", &IndexBuffer::GetIndexCount)
        .addFunction("GetIndexSize", &IndexBuffer::GetIndexSize)
        .addFunction("GetUsedVertexRange", &IndexBuffer::GetUsedVertexRange)


        .addProperty("shadowed", &IndexBuffer::IsShadowed, &IndexBuffer::SetShadowed)
        .addProperty("dynamic", &IndexBuffer::IsDynamic)
        .addProperty("locked", &IndexBuffer::IsLocked)
        .addProperty("indexCount", &IndexBuffer::GetIndexCount)
        .addProperty("indexSize", &IndexBuffer::GetIndexSize)
    );
}


static void RegisterMaterial(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KDEFAULT_RENDER_ORDER"] = DEFAULT_RENDER_ORDER;

    lua["KMaterial"].setClass(UserdataMetatable<Material, Resource>(false)
        .addStaticFunction("new", &KCreateObject<Material>)
        .addStaticFunction("__gc", &KReleaseObject<Material>)

        .addFunction("SetNumTechniques", &Material::SetNumTechniques)
        .addFunction("SetTechnique", &Material::SetTechnique)
        .addFunction("SetShaderParameter", &Material::SetShaderParameter)
        .addFunction("SetShaderParameterAnimation", &Material::SetShaderParameterAnimation)
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
        .addFunction("Clone", &Material::Clone)
        .addFunction("SortTechniques", &Material::SortTechniques)
        .addFunction("MarkForAuxView", &Material::MarkForAuxView)
        .addFunction("GetNumTechniques", &Material::GetNumTechniques)
        .addFunction("GetTechniques", &Material::GetTechniques)
        .addFunction("GetTechniqueEntry", &Material::GetTechniqueEntry)
        .addFunction("GetTechnique", &Material::GetTechnique)
        .addFunction("GetPass", &Material::GetPass)
        .addFunction("GetTexture", &Material::GetTexture)
        .addFunction("GetTextures", &Material::GetTextures)
        .addFunction("GetShaderParameter", &Material::GetShaderParameter)
        .addFunction("GetShaderParameterAnimation", &Material::GetShaderParameterAnimation)
        .addFunction("GetShaderParameterAnimationWrapMode", &Material::GetShaderParameterAnimationWrapMode)
        .addFunction("GetShaderParameterAnimationSpeed", &Material::GetShaderParameterAnimationSpeed)
        .addFunction("GetShaderParameters", &Material::GetShaderParameters)
        .addFunction("GetCullMode", &Material::GetCullMode)
        .addFunction("GetShadowCullMode", &Material::GetShadowCullMode)
        .addFunction("GetFillMode", &Material::GetFillMode)
        .addFunction("GetDepthBias", &Material::GetDepthBias)
        .addFunction("GetRenderOrder", &Material::GetRenderOrder)
        .addFunction("GetAuxViewFrameNumber", &Material::GetAuxViewFrameNumber)
        .addFunction("GetOcclusion", &Material::GetOcclusion)
        .addFunction("GetSpecular", &Material::GetSpecular)
        .addFunction("GetScene", &Material::GetScene)
        .addFunction("GetShaderParameterHash", &Material::GetShaderParameterHash)
        .addStaticFunction("GetTextureUnitName", &Material::GetTextureUnitName)
        .addStaticFunction("ParseShaderParameterValue", &Material::ParseShaderParameterValue)

        .addProperty("numTechniques", &Material::GetNumTechniques, &Material::SetNumTechniques)
        .addProperty("techniques", &Material::GetTechniques)
        .addProperty("textures", &Material::GetTextures)
        .addProperty("shaderParameters", &Material::GetShaderParameters)
        .addProperty("cullMode", &Material::GetCullMode, &Material::SetCullMode)
        .addProperty("shadowCullMode", &Material::GetShadowCullMode, &Material::SetShadowCullMode)
        .addProperty("fillMode", &Material::GetFillMode, &Material::SetFillMode)
        .addProperty("depthBias", &Material::GetDepthBias, &Material::SetDepthBias)
        .addProperty("renderOrder", &Material::GetRenderOrder, &Material::SetRenderOrder)
        .addProperty("auxViewFrameNumber", &Material::GetAuxViewFrameNumber)
        .addProperty("occlusion", &Material::GetOcclusion)
        .addProperty("specular", &Material::GetSpecular)
        .addProperty("scene", &Material::GetScene, &Material::SetScene)
        .addProperty("shaderParameterHash", &Material::GetShaderParameterHash)
    );
}

static void RegisterRenderer(kaguya::State& lua)
{
    using namespace kaguya;

    // GC is disable for subsystem object
    lua["KRenderer"].setClass(UserdataMetatable<Renderer, Object>(false)

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
        .addFunction("SetVSMShadowParameters", &Renderer::SetVSMShadowParameters)
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
        .addFunction("ApplyShadowMapFilter", &Renderer::ApplyShadowMapFilter)
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
        .addFunction("GetVSMShadowParameters", &Renderer::GetVSMShadowParameters)
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
        .addFunction("GetNumGeometries", &Renderer::GetNumGeometries)
        .addFunction("GetNumLights", &Renderer::GetNumLights)
        .addFunction("GetNumShadowMaps", &Renderer::GetNumShadowMaps)
        .addFunction("GetNumOccluders", &Renderer::GetNumOccluders)
        .addFunction("GetDefaultZone", &Renderer::GetDefaultZone)
        .addFunction("GetDefaultMaterial", &Renderer::GetDefaultMaterial)
        .addFunction("GetDefaultLightRamp", &Renderer::GetDefaultLightRamp)
        .addFunction("GetDefaultLightSpot", &Renderer::GetDefaultLightSpot)
        .addFunction("GetFaceSelectCubeMap", &Renderer::GetFaceSelectCubeMap)
        .addFunction("GetIndirectionCubeMap", &Renderer::GetIndirectionCubeMap)
        .addFunction("GetInstancingBuffer", &Renderer::GetInstancingBuffer)
        .addFunction("GetFrameInfo", &Renderer::GetFrameInfo)
        .addFunction("Update", &Renderer::Update)
        .addFunction("Render", &Renderer::Render)
        .addFunction("DrawDebugGeometry", &Renderer::DrawDebugGeometry)
        .addFunction("QueueRenderSurface", &Renderer::QueueRenderSurface)
        .addFunction("QueueViewport", &Renderer::QueueViewport)
        .addFunction("GetLightGeometry", &Renderer::GetLightGeometry)
        .addFunction("GetQuadGeometry", &Renderer::GetQuadGeometry)
        .addFunction("GetShadowMap", &Renderer::GetShadowMap)
        .addFunction("GetScreenBuffer", &Renderer::GetScreenBuffer)
        .addFunction("GetDepthStencil", &Renderer::GetDepthStencil)
        .addFunction("GetOcclusionBuffer", &Renderer::GetOcclusionBuffer)
        .addFunction("GetShadowCamera", &Renderer::GetShadowCamera)
        .addFunction("StorePreparedView", &Renderer::StorePreparedView)
        .addFunction("GetPreparedView", &Renderer::GetPreparedView)
        .addFunction("SetBatchShaders", &Renderer::SetBatchShaders)
        .addFunction("SetLightVolumeBatchShaders", &Renderer::SetLightVolumeBatchShaders)
        .addFunction("SetCullMode", &Renderer::SetCullMode)
        .addFunction("ResizeInstancingBuffer", &Renderer::ResizeInstancingBuffer)
        .addFunction("SaveScreenBufferAllocations", &Renderer::SaveScreenBufferAllocations)
        .addFunction("RestoreScreenBufferAllocations", &Renderer::RestoreScreenBufferAllocations)
        .addFunction("OptimizeLightByScissor", &Renderer::OptimizeLightByScissor)
        .addFunction("OptimizeLightByStencil", &Renderer::OptimizeLightByStencil)
        .addFunction("GetLightScissor", &Renderer::GetLightScissor)
        .addStaticFunction("GetActualView", &Renderer::GetActualView)

        .addProperty("numViewports", &Renderer::GetNumViewports, &Renderer::SetNumViewports)
        .addProperty("defaultRenderPath", &Renderer::GetDefaultRenderPath)
        .addProperty("defaultTechnique", &Renderer::GetDefaultTechnique, &Renderer::SetDefaultTechnique)
        .addProperty("hDRRendering", &Renderer::GetHDRRendering, &Renderer::SetHDRRendering)
        .addProperty("specularLighting", &Renderer::GetSpecularLighting, &Renderer::SetSpecularLighting)
        .addProperty("drawShadows", &Renderer::GetDrawShadows, &Renderer::SetDrawShadows)
        .addProperty("textureAnisotropy", &Renderer::GetTextureAnisotropy, &Renderer::SetTextureAnisotropy)
        .addProperty("textureFilterMode", &Renderer::GetTextureFilterMode, &Renderer::SetTextureFilterMode)
        .addProperty("textureQuality", &Renderer::GetTextureQuality, &Renderer::SetTextureQuality)
        .addProperty("materialQuality", &Renderer::GetMaterialQuality, &Renderer::SetMaterialQuality)
        .addProperty("shadowMapSize", &Renderer::GetShadowMapSize, &Renderer::SetShadowMapSize)
        .addProperty("shadowQuality", &Renderer::GetShadowQuality, &Renderer::SetShadowQuality)
        .addProperty("shadowSoftness", &Renderer::GetShadowSoftness, &Renderer::SetShadowSoftness)
        .addProperty("vSMShadowParameters", &Renderer::GetVSMShadowParameters)
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
        .addProperty("faceSelectCubeMap", &Renderer::GetFaceSelectCubeMap)
        .addProperty("indirectionCubeMap", &Renderer::GetIndirectionCubeMap)
        .addProperty("instancingBuffer", &Renderer::GetInstancingBuffer)
        .addProperty("frameInfo", &Renderer::GetFrameInfo)
        .addProperty("quadGeometry", &Renderer::GetQuadGeometry)
        .addProperty("shadowCamera", &Renderer::GetShadowCamera)
    );
}

static void RegisterRenderPath(kaguya::State& lua)
{
    using namespace kaguya;

    // enum RenderCommandType;
    lua["KCMD_NONE"] = CMD_NONE;
    lua["KCMD_CLEAR"] = CMD_CLEAR;
    lua["KCMD_SCENEPASS"] = CMD_SCENEPASS;
    lua["KCMD_QUAD"] = CMD_QUAD;
    lua["KCMD_FORWARDLIGHTS"] = CMD_FORWARDLIGHTS;
    lua["KCMD_LIGHTVOLUMES"] = CMD_LIGHTVOLUMES;
    lua["KCMD_RENDERUI"] = CMD_RENDERUI;
    lua["KCMD_SENDEVENT"] = CMD_SENDEVENT;

    // enum RenderCommandSortMode;
    lua["KSORT_FRONTTOBACK"] = SORT_FRONTTOBACK;
    lua["KSORT_BACKTOFRONT"] = SORT_BACKTOFRONT;

    // enum RenderTargetSizeMode;
    lua["KSIZE_ABSOLUTE"] = SIZE_ABSOLUTE;
    lua["KSIZE_VIEWPORTDIVISOR"] = SIZE_VIEWPORTDIVISOR;
    lua["KSIZE_VIEWPORTMULTIPLIER"] = SIZE_VIEWPORTMULTIPLIER;

    lua["KRenderTargetInfo"].setClass(UserdataMetatable<RenderTargetInfo>()
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

    lua["KRenderPathCommand"].setClass(UserdataMetatable<RenderPathCommand>()
        .setConstructors<RenderPathCommand()>()

        .addFunction("Load", &RenderPathCommand::Load)
        .addFunction("SetTextureName", &RenderPathCommand::SetTextureName)
        .addFunction("SetShaderParameter", &RenderPathCommand::SetShaderParameter)
        .addFunction("RemoveShaderParameter", &RenderPathCommand::RemoveShaderParameter)
        .addFunction("SetNumOutputs", &RenderPathCommand::SetNumOutputs)
        .addFunction("SetOutput", &RenderPathCommand::SetOutput)
        .addFunction("SetOutputName", &RenderPathCommand::SetOutputName)
        .addFunction("SetOutputFace", &RenderPathCommand::SetOutputFace)
        .addFunction("SetDepthStencilName", &RenderPathCommand::SetDepthStencilName)
        .addFunction("GetTextureName", &RenderPathCommand::GetTextureName)
        .addFunction("GetShaderParameter", &RenderPathCommand::GetShaderParameter)
        .addFunction("GetNumOutputs", &RenderPathCommand::GetNumOutputs)
        .addFunction("GetOutputName", &RenderPathCommand::GetOutputName)
        .addFunction("GetOutputFace", &RenderPathCommand::GetOutputFace)
        .addFunction("GetDepthStencilName", &RenderPathCommand::GetDepthStencilName)
        
        .addProperty("numOutputs", &RenderPathCommand::GetNumOutputs, &RenderPathCommand::SetNumOutputs)
        .addProperty("depthStencilName", &RenderPathCommand::GetDepthStencilName, &RenderPathCommand::SetDepthStencilName)

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

    lua["KRenderPath"].setClass(UserdataMetatable<RenderPath, RefCounted>()
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

        .addProperty("numRenderTargets", &RenderPath::GetNumRenderTargets)
        .addProperty("numCommands", &RenderPath::GetNumCommands)
        .addProperty("renderTargets", &RenderPath::renderTargets_)
        .addProperty("commands", &RenderPath::commands_)
    );
}

static void RegisterRenderSurface(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KRenderSurface"].setClass(UserdataMetatable<RenderSurface, RefCounted>(false)
        .setConstructors<RenderSurface(Texture*)>()
        .addStaticFunction("__gc", &KReleaseObject<RenderSurface>)

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
        .addFunction("IsUpdateQueued", &RenderSurface::IsUpdateQueued)
        .addFunction("ResetUpdateQueued", &RenderSurface::ResetUpdateQueued)

        .addProperty("parentTexture", &RenderSurface::GetParentTexture)
        .addProperty("width", &RenderSurface::GetWidth)
        .addProperty("height", &RenderSurface::GetHeight)
        .addProperty("usage", &RenderSurface::GetUsage)
        .addProperty("numViewports", &RenderSurface::GetNumViewports, &RenderSurface::SetNumViewports)
        .addProperty("updateMode", &RenderSurface::GetUpdateMode, &RenderSurface::SetUpdateMode)
        .addProperty("linkedRenderTarget", &RenderSurface::GetLinkedRenderTarget, &RenderSurface::SetLinkedRenderTarget)
        .addProperty("linkedDepthStencil", &RenderSurface::GetLinkedDepthStencil, &RenderSurface::SetLinkedDepthStencil)
        .addProperty("updateQueued", &RenderSurface::IsUpdateQueued)
    );
}

static void RegisterShader(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KShader"].setClass(UserdataMetatable<Shader, Resource>(false)
        .addStaticFunction("new", &KCreateObject<Shader>)
        .addStaticFunction("__gc", &KReleaseObject<Shader>)

        // .addFunction("GetVariation", &Shader::GetVariation)
        // .addFunction("GetSourceCode", &Shader::GetSourceCode)
        // .addFunction("GetTimeStamp", &Shader::GetTimeStamp)

        // .addProperty("timeStamp", &Shader::GetTimeStamp)
    );
}

static void RegisterShaderVariation(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KShaderVariation"].setClass(UserdataMetatable<ShaderVariation, RefCounted>()
        .setConstructors<ShaderVariation(Shader*, ShaderType)>()

        .addFunction("Create", &ShaderVariation::Create)
        .addFunction("SetName", &ShaderVariation::SetName)
        .addFunction("SetDefines", &ShaderVariation::SetDefines)
        .addFunction("GetOwner", &ShaderVariation::GetOwner)
        .addFunction("GetShaderType", &ShaderVariation::GetShaderType)
        .addFunction("GetName", &ShaderVariation::GetName)
        .addFunction("GetDefines", &ShaderVariation::GetDefines)
        .addFunction("GetFullName", &ShaderVariation::GetFullName)
        .addFunction("GetCompilerOutput", &ShaderVariation::GetCompilerOutput)

        .addProperty("owner", &ShaderVariation::GetOwner)
        .addProperty("shaderType", &ShaderVariation::GetShaderType)
        .addProperty("name", &ShaderVariation::GetName, &ShaderVariation::SetName)
        .addProperty("defines", &ShaderVariation::GetDefines, &ShaderVariation::SetDefines)
        .addProperty("fullName", &ShaderVariation::GetFullName)
        .addProperty("compilerOutput", &ShaderVariation::GetCompilerOutput)
    );
}

static void RegisterTechnique(kaguya::State& lua)
{
    using namespace kaguya;

    // enum PassLightingMode;
    lua["KLIGHTING_UNLIT"] = LIGHTING_UNLIT;
    lua["KLIGHTING_PERVERTEX"] = LIGHTING_PERVERTEX;
    lua["KLIGHTING_PERPIXEL"] = LIGHTING_PERPIXEL;

    lua["KPass"].setClass(UserdataMetatable<Pass, RefCounted>(false)
        .setConstructors<Pass(const String&)>()
        .addStaticFunction("__gc", &KReleaseObject<Pass>)

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
        .addFunction("MarkShadersLoaded", &Pass::MarkShadersLoaded)
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
        .addFunction("GetVertexShaders", &Pass::GetVertexShaders)
        .addFunction("GetPixelShaders", &Pass::GetPixelShaders)

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
        .addProperty("vertexShaders", &Pass::GetVertexShaders)
        .addProperty("pixelShaders", &Pass::GetPixelShaders)
        .addProperty("isDesktop", &Pass::SetIsDesktop)
    );

    lua["KTechnique"].setClass(UserdataMetatable<Technique, Resource>(false)
        .addStaticFunction("new", &KCreateObject<Technique>)
        .addStaticFunction("__gc", &KReleaseObject<Technique>)

        .addFunction("BeginLoad", &Technique::BeginLoad)
        .addFunction("SetIsDesktop", &Technique::SetIsDesktop)
        .addFunction("CreatePass", &Technique::CreatePass)
        .addFunction("RemovePass", &Technique::RemovePass)
        .addFunction("ReleaseShaders", &Technique::ReleaseShaders)
        .addFunction("Clone", &Technique::Clone)
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
        .addStaticFunction("GetPassIndex", &Technique::GetPassIndex)

        .addProperty("desktop", &Technique::IsDesktop)
        .addProperty("supported", &Technique::IsSupported)
        .addProperty("numPasses", &Technique::GetNumPasses)
        .addProperty("passNames", &Technique::GetPassNames)
        .addProperty("passes", &Technique::GetPasses)
        .addProperty("isDesktop", &Technique::SetIsDesktop)

        .addStaticField("basePassIndex", &Technique::basePassIndex)
        .addStaticField("alphaPassIndex", &Technique::alphaPassIndex)
        .addStaticField("materialPassIndex", &Technique::materialPassIndex)
        .addStaticField("deferredPassIndex", &Technique::deferredPassIndex)
        .addStaticField("lightPassIndex", &Technique::lightPassIndex)
        .addStaticField("litBasePassIndex", &Technique::litBasePassIndex)
        .addStaticField("litAlphaPassIndex", &Technique::litAlphaPassIndex)
        .addStaticField("shadowPassIndex", &Technique::shadowPassIndex)
    );
}

static void RegisterTexture(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KMAX_TEXTURE_QUALITY_LEVELS"] = MAX_TEXTURE_QUALITY_LEVELS;

    lua["KTexture"].setClass(UserdataMetatable<Texture, Resource>(false)
        .addStaticFunction("new", &KCreateObject<Texture>)
        .addStaticFunction("__gc", &KReleaseObject<Texture>)

        .addFunction("SetNumLevels", &Texture::SetNumLevels)
        .addFunction("SetFilterMode", &Texture::SetFilterMode)
        .addFunction("SetAddressMode", &Texture::SetAddressMode)
        .addFunction("SetShadowCompare", &Texture::SetShadowCompare)
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
        .addFunction("GetShadowCompare", &Texture::GetShadowCompare)
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

        .addOverloadedFunctions("SetParameters",
            static_cast<void(Texture::*)(XMLFile*)>(&Texture::SetParameters),
            static_cast<void(Texture::*)(const XMLElement&)>(&Texture::SetParameters))

        .addProperty("format", &Texture::GetFormat)
        .addProperty("compressed", &Texture::IsCompressed)
        .addProperty("levels", &Texture::GetLevels)
        .addProperty("width", &Texture::GetWidth)
        .addProperty("height", &Texture::GetHeight)
        .addProperty("depth", &Texture::GetDepth)
        .addProperty("filterMode", &Texture::GetFilterMode, &Texture::SetFilterMode)
        .addProperty("shadowCompare", &Texture::GetShadowCompare, &Texture::SetShadowCompare)
        .addProperty("borderColor", &Texture::GetBorderColor, &Texture::SetBorderColor)
        .addProperty("sRGB", &Texture::GetSRGB, &Texture::SetSRGB)
        .addProperty("backupTexture", &Texture::GetBackupTexture, &Texture::SetBackupTexture)
        .addProperty("usage", &Texture::GetUsage)
        .addProperty("components", &Texture::GetComponents)
        .addProperty("numLevels", &Texture::SetNumLevels)
    );
}

static void RegisterTexture2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KTexture2D"].setClass(UserdataMetatable<Texture2D, Texture>(false)
        .addStaticFunction("new", &KCreateObject<Texture2D>)
        .addStaticFunction("__gc", &KReleaseObject<Texture2D>)

        .addFunction("SetSize", &Texture2D::SetSize)
        .addFunction("SetData", static_cast<bool(Texture2D::*)(Image*, bool)>(&Texture2D::SetData))
    );
}

static void RegisterTexture2DArray(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KTexture2DArray"].setClass(UserdataMetatable<Texture2DArray, Texture>(false)
        .addStaticFunction("new", &KCreateObject<Texture2DArray>)
        .addStaticFunction("__gc", &KReleaseObject<Texture2DArray>)

        .addFunction("SetLayers", &Texture2DArray::SetLayers)
        .addFunction("SetSize", &Texture2DArray::SetSize)
        .addFunction("SetData", static_cast<bool(Texture2DArray::*)(unsigned, Image*, bool)>(&Texture2DArray::SetData))

        .addFunction("GetLayers", &Texture2DArray::GetLayers)

        .addProperty("layers", &Texture2DArray::GetLayers, &Texture2DArray::SetLayers)
    );
}

static void RegisterTexture3D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KTexture3D"].setClass(UserdataMetatable<Texture3D, Texture>(false)
        .addStaticFunction("new", &KCreateObject<Texture3D>)
        .addStaticFunction("__gc", &KReleaseObject<Texture3D>)

        .addFunction("SetSize", &Texture3D::SetSize)
        .addFunction("SetData", static_cast<bool(Texture3D::*)(Image*, bool)>(&Texture3D::SetData))
    );
}

static void RegisterTextureCube(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KTextureCube"].setClass(UserdataMetatable<TextureCube, Texture>(false)
        .addStaticFunction("new", &KCreateObject<TextureCube>)
        .addStaticFunction("__gc", &KReleaseObject<TextureCube>)

        .addFunction("SetSize", &TextureCube::SetSize)
        .addFunction("SetData", static_cast<bool(TextureCube::*)(CubeMapFace, Image*, bool)>(&TextureCube::SetData))

    );
}

static void RegisterVertexBuffer(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KVertexBuffer"].setClass(UserdataMetatable<VertexBuffer, GPUObject>()
        .setConstructors<VertexBuffer(Context*, bool)>()

        .addFunction("SetShadowed", &VertexBuffer::SetShadowed)

        .addOverloadedFunctions("SetSize",
            static_cast<bool(VertexBuffer::*)(unsigned, const PODVector<VertexElement>&, bool)>(&VertexBuffer::SetSize),
            static_cast<bool(VertexBuffer::*)(unsigned, unsigned, bool)>(&VertexBuffer::SetSize))

        .addFunction("IsShadowed", &VertexBuffer::IsShadowed)
        .addFunction("IsDynamic", &VertexBuffer::IsDynamic)
        .addFunction("IsLocked", &VertexBuffer::IsLocked)
        .addFunction("GetVertexCount", &VertexBuffer::GetVertexCount)
        .addFunction("GetElementMask", &VertexBuffer::GetElementMask)

        .addProperty("shadowed", &VertexBuffer::IsShadowed, &VertexBuffer::SetShadowed)
        .addProperty("dynamic", &VertexBuffer::IsDynamic)
        .addProperty("locked", &VertexBuffer::IsLocked)
        .addProperty("vertexCount", &VertexBuffer::GetVertexCount)
        .addProperty("elementMask", &VertexBuffer::GetElementMask)
    );
}

static void RegisterViewport(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KViewport"].setClass(UserdataMetatable<Viewport, Object>(false)
        .addStaticFunction("new", &KCreateObject<Viewport>)
        .addStaticFunction("__gc", &KReleaseObject<Viewport>)

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
        .addFunction("GetView", &Viewport::GetView)
        .addFunction("GetRect", &Viewport::GetRect)
        .addFunction("GetRenderPath", &Viewport::GetRenderPath)
        .addFunction("GetDrawDebug", &Viewport::GetDrawDebug)
        .addFunction("GetCullCamera", &Viewport::GetCullCamera)
        .addFunction("GetScreenRay", &Viewport::GetScreenRay)
        .addFunction("WorldToScreenPoint", &Viewport::WorldToScreenPoint)
        .addFunction("ScreenToWorldPoint", &Viewport::ScreenToWorldPoint)
        .addFunction("AllocateView", &Viewport::AllocateView)

        .addProperty("scene", &Viewport::GetScene, &Viewport::SetScene)
        .addProperty("camera", &Viewport::GetCamera, &Viewport::SetCamera)
        .addProperty("view", &Viewport::GetView)
        .addProperty("rect", &Viewport::GetRect, &Viewport::SetRect)
        .addProperty("renderPath", &Viewport::GetRenderPath)
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
    RegisterGraphicsEvents(lua);
    RegisterIndexBuffer(lua);
    RegisterRenderer(lua);
    RegisterRenderPath(lua);
    RegisterRenderSurface(lua);
    RegisterShader(lua);
    RegisterShaderVariation(lua);
    RegisterTechnique(lua);
    RegisterTexture(lua);
    RegisterTexture2D(lua);
    RegisterTexture2DArray(lua);
    RegisterTexture3D(lua);
    RegisterTextureCube(lua);
    RegisterVertexBuffer(lua);
    RegisterViewport(lua);

    lua["kgraphics"] = GetGraphics();
    lua["KGetGraphics"] = GetGraphics;

    lua["krenderer"] = GetRenderer();
    lua["KGetRenderer"] = GetRenderer;
}
}
