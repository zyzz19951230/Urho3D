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
        .addFunction("GetReverseCulling", &Camera::GetReverseCulling)
        .addFunction("GetDistance", &Camera::GetDistance)
        .addFunction("GetDistanceSquared", &Camera::GetDistanceSquared)
        .addFunction("GetLodDistance", &Camera::GetLodDistance)
        .addFunction("GetFaceCameraRotation", &Camera::GetFaceCameraRotation)
        .addFunction("GetEffectiveWorldTransform", &Camera::GetEffectiveWorldTransform)
        .addFunction("IsProjectionValid", &Camera::IsProjectionValid)
        
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
    );
}

static void RegisterDebugRenderer(kaguya::State& lua)
{
    using namespace kaguya;

    lua["DebugRenderer"].setClass(UserdataMetatable<DebugRenderer, Component>()
        .addStaticFunction("new", &CreateObject<DebugRenderer>)
        
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

        .addFunction("GetView", &DebugRenderer::GetView)
        .addFunction("GetProjection", &DebugRenderer::GetProjection)
        .addFunction("GetFrustum", &DebugRenderer::GetFrustum)
        
        .addProperty("view", &DebugRenderer::GetView, &DebugRenderer::SetView)
        .addProperty("projection", &DebugRenderer::GetProjection)
        .addProperty("frustum", &DebugRenderer::GetFrustum)
    );
}

static void RegisterGeometry(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Geometry"].setClass(UserdataMetatable<Geometry, Object>()
        .addStaticFunction("new", &CreateObject<Geometry>)
        
        .addFunction("SetNumVertexBuffers", &Geometry::SetNumVertexBuffers)
        .addFunction("SetVertexBuffer", &Geometry::SetVertexBuffer)
        .addFunction("SetIndexBuffer", &Geometry::SetIndexBuffer)

        .addOverloadedFunctions("SetDrawRange",
            static_cast<bool(Geometry::*)(PrimitiveType, unsigned, unsigned, bool)>(&Geometry::SetDrawRange),
            static_cast<bool(Geometry::*)(PrimitiveType, unsigned, unsigned, unsigned, unsigned, bool)>(&Geometry::SetDrawRange))

        // .addFunction("GetVertexBuffers", &Geometry::GetVertexBuffers)
        .addFunction("GetNumVertexBuffers", &Geometry::GetNumVertexBuffers)
        .addFunction("GetVertexBuffer", &Geometry::GetVertexBuffer)
        .addFunction("GetIndexBuffer", &Geometry::GetIndexBuffer)
        
        .addFunction("GetPrimitiveType", &Geometry::GetPrimitiveType)
        .addFunction("GetIndexStart", &Geometry::GetIndexStart)
        .addFunction("GetIndexCount", &Geometry::GetIndexCount)
        .addFunction("GetVertexStart", &Geometry::GetVertexStart)
        .addFunction("GetVertexCount", &Geometry::GetVertexCount)
        
        .addProperty("indexBuffer", &Geometry::GetIndexBuffer, &Geometry::SetIndexBuffer)
        .addProperty("primitiveType", &Geometry::GetPrimitiveType)
        .addProperty("indexStart", &Geometry::GetIndexStart)
        .addProperty("indexCount", &Geometry::GetIndexCount)
        .addProperty("vertexStart", &Geometry::GetVertexStart)
        .addProperty("vertexCount", &Geometry::GetVertexCount)
    );
}

static void RegisterGraphics(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Graphics"].setClass(UserdataMetatable<Graphics, Object>()

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
        .addFunction("GetHardwareShadowSupport", &Graphics::GetHardwareShadowSupport)
        .addFunction("GetReadableDepthSupport", &Graphics::GetReadableDepthSupport)
        .addFunction("GetSRGBSupport", &Graphics::GetSRGBSupport)
        .addFunction("GetSRGBWriteSupport", &Graphics::GetSRGBWriteSupport)
        .addFunction("GetResolutions", &Graphics::GetResolutions)
        .addFunction("GetMultiSampleLevels", &Graphics::GetMultiSampleLevels)
        .addFunction("GetDesktopResolution", &Graphics::GetDesktopResolution)

        .addFunction("GetDefaultTextureFilterMode", &Graphics::GetDefaultTextureFilterMode)
        
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
        .addProperty("hardwareShadowSupport", &Graphics::GetHardwareShadowSupport)
        .addProperty("readableDepthSupport", &Graphics::GetReadableDepthSupport)
        .addProperty("sRGBSupport", &Graphics::GetSRGBSupport)
        .addProperty("sRGBWriteSupport", &Graphics::GetSRGBWriteSupport)
        .addProperty("resolutions", &Graphics::GetResolutions)
        .addProperty("multiSampleLevels", &Graphics::GetMultiSampleLevels)
        .addProperty("desktopResolution", &Graphics::GetDesktopResolution)

        .addProperty("defaultTextureFilterMode", &Graphics::GetDefaultTextureFilterMode, &Graphics::SetDefaultTextureFilterMode)

        .addProperty("renderTargetDimensions", &Graphics::GetRenderTargetDimensions)
        .addProperty("windowIcon", &Graphics::SetWindowIcon)
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

    // enum ShaderParameterGroup;
    lua["SP_FRAME"] = SP_FRAME;
    lua["SP_CAMERA"] = SP_CAMERA;
    lua["SP_ZONE"] = SP_ZONE;
    lua["SP_LIGHT"] = SP_LIGHT;
    lua["SP_MATERIAL"] = SP_MATERIAL;
    lua["SP_OBJECT"] = SP_OBJECT;
    lua["SP_CUSTOM"] = SP_CUSTOM;
    lua["MAX_SHADER_PARAMETER_GROUPS"] = MAX_SHADER_PARAMETER_GROUPS;

    // enum TextureUnit;
    lua["TU_DIFFUSE"] = TU_DIFFUSE;
    lua["TU_ALBEDOBUFFER"] = TU_ALBEDOBUFFER;
    lua["TU_NORMAL"] = TU_NORMAL;
    lua["TU_NORMALBUFFER"] = TU_NORMALBUFFER;
    lua["TU_SPECULAR"] = TU_SPECULAR;
    lua["TU_EMISSIVE"] = TU_EMISSIVE;
    lua["TU_ENVIRONMENT"] = TU_ENVIRONMENT;
    lua["TU_VOLUMEMAP"] = TU_VOLUMEMAP;
    lua["TU_CUSTOM1"] = TU_CUSTOM1;
    lua["TU_CUSTOM2"] = TU_CUSTOM2;
    lua["TU_LIGHTRAMP"] = TU_LIGHTRAMP;
    lua["TU_LIGHTSHAPE"] = TU_LIGHTSHAPE;
    lua["TU_SHADOWMAP"] = TU_SHADOWMAP;
    lua["TU_FACESELECT"] = TU_FACESELECT;
    lua["TU_INDIRECTION"] = TU_INDIRECTION;
    lua["TU_DEPTHBUFFER"] = TU_DEPTHBUFFER;
    lua["TU_LIGHTBUFFER"] = TU_LIGHTBUFFER;
    lua["TU_ZONE"] = TU_ZONE;
    lua["MAX_MATERIAL_TEXTURE_UNITS"] = MAX_MATERIAL_TEXTURE_UNITS;
    lua["MAX_TEXTURE_UNITS"] = MAX_TEXTURE_UNITS;

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

    /*
    lua["VSP_AMBIENTSTARTCOLOR"] = VSP_AMBIENTSTARTCOLOR;
    lua["VSP_AMBIENTENDCOLOR"] = VSP_AMBIENTENDCOLOR;
    lua["VSP_BILLBOARDROT"] = VSP_BILLBOARDROT;
    lua["VSP_CAMERAPOS"] = VSP_CAMERAPOS;
    lua["VSP_CLIPPLANE"] = VSP_CLIPPLANE;
    lua["VSP_NEARCLIP"] = VSP_NEARCLIP;
    lua["VSP_FARCLIP"] = VSP_FARCLIP;
    lua["VSP_DEPTHMODE"] = VSP_DEPTHMODE;
    lua["VSP_DELTATIME"] = VSP_DELTATIME;
    lua["VSP_ELAPSEDTIME"] = VSP_ELAPSEDTIME;
    lua["VSP_FRUSTUMSIZE"] = VSP_FRUSTUMSIZE;
    lua["VSP_GBUFFEROFFSETS"] = VSP_GBUFFEROFFSETS;
    lua["VSP_LIGHTDIR"] = VSP_LIGHTDIR;
    lua["VSP_LIGHTPOS"] = VSP_LIGHTPOS;
    lua["VSP_NORMALOFFSETSCALE"] = VSP_NORMALOFFSETSCALE;
    lua["VSP_MODEL"] = VSP_MODEL;
    lua["VSP_VIEW"] = VSP_VIEW;
    lua["VSP_VIEWINV"] = VSP_VIEWINV;
    lua["VSP_VIEWPROJ"] = VSP_VIEWPROJ;
    lua["VSP_UOFFSET"] = VSP_UOFFSET;
    lua["VSP_VOFFSET"] = VSP_VOFFSET;
    lua["VSP_ZONE"] = VSP_ZONE;
    lua["VSP_LIGHTMATRICES"] = VSP_LIGHTMATRICES;
    lua["VSP_SKINMATRICES"] = VSP_SKINMATRICES;
    lua["VSP_VERTEXLIGHTS"] = VSP_VERTEXLIGHTS;
    lua["PSP_AMBIENTCOLOR"] = PSP_AMBIENTCOLOR;
    lua["PSP_CAMERAPOS"] = PSP_CAMERAPOS;
    lua["PSP_DELTATIME"] = PSP_DELTATIME;
    lua["PSP_DEPTHRECONSTRUCT"] = PSP_DEPTHRECONSTRUCT;
    lua["PSP_ELAPSEDTIME"] = PSP_ELAPSEDTIME;
    lua["PSP_FOGCOLOR"] = PSP_FOGCOLOR;
    lua["PSP_FOGPARAMS"] = PSP_FOGPARAMS;
    lua["PSP_GBUFFERINVSIZE"] = PSP_GBUFFERINVSIZE;
    lua["PSP_LIGHTCOLOR"] = PSP_LIGHTCOLOR;
    lua["PSP_LIGHTDIR"] = PSP_LIGHTDIR;
    lua["PSP_LIGHTPOS"] = PSP_LIGHTPOS;
    lua["PSP_NORMALOFFSETSCALE"] = PSP_NORMALOFFSETSCALE;
    lua["PSP_MATDIFFCOLOR"] = PSP_MATDIFFCOLOR;
    lua["PSP_MATEMISSIVECOLOR"] = PSP_MATEMISSIVECOLOR;
    lua["PSP_MATENVMAPCOLOR"] = PSP_MATENVMAPCOLOR;
    lua["PSP_MATSPECCOLOR"] = PSP_MATSPECCOLOR;
    lua["PSP_NEARCLIP"] = PSP_NEARCLIP;
    lua["PSP_FARCLIP"] = PSP_FARCLIP;
    lua["PSP_SHADOWCUBEADJUST"] = PSP_SHADOWCUBEADJUST;
    lua["PSP_SHADOWDEPTHFADE"] = PSP_SHADOWDEPTHFADE;
    lua["PSP_SHADOWINTENSITY"] = PSP_SHADOWINTENSITY;
    lua["PSP_SHADOWMAPINVSIZE"] = PSP_SHADOWMAPINVSIZE;
    lua["PSP_SHADOWSPLITS"] = PSP_SHADOWSPLITS;
    lua["PSP_LIGHTMATRICES"] = PSP_LIGHTMATRICES;
    lua["PSP_VSMSHADOWPARAMS"] = PSP_VSMSHADOWPARAMS;
    lua["PSP_ROUGHNESS"] = PSP_ROUGHNESS;
    lua["PSP_METALLIC"] = PSP_METALLIC;
    */

    lua["DOT_SCALE"] = DOT_SCALE;
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
    lua["MAX_RENDERTARGETS"] = MAX_RENDERTARGETS;
    lua["MAX_VERTEX_STREAMS"] = MAX_VERTEX_STREAMS;
    lua["MAX_CONSTANT_REGISTERS"] = MAX_CONSTANT_REGISTERS;
    lua["BITS_PER_COMPONENT"] = BITS_PER_COMPONENT;
}

static void RegisterGraphicsEvents(kaguya::State& lua)
{
    using namespace kaguya;

    lua["E_SCREENMODE"] = E_SCREENMODE;
    lua["E_WINDOWPOS"] = E_WINDOWPOS;
    lua["E_RENDERSURFACEUPDATE"] = E_RENDERSURFACEUPDATE;
    lua["E_BEGINRENDERING"] = E_BEGINRENDERING;
    lua["E_ENDRENDERING"] = E_ENDRENDERING;
    lua["E_BEGINVIEWUPDATE"] = E_BEGINVIEWUPDATE;
    lua["E_ENDVIEWUPDATE"] = E_ENDVIEWUPDATE;
    lua["E_BEGINVIEWRENDER"] = E_BEGINVIEWRENDER;
    lua["E_ENDVIEWRENDER"] = E_ENDVIEWRENDER;
    lua["E_RENDERPATHEVENT"] = E_RENDERPATHEVENT;
    lua["E_DEVICELOST"] = E_DEVICELOST;
    lua["E_DEVICERESET"] = E_DEVICERESET;
}

static void RegisterIndexBuffer(kaguya::State& lua)
{
    using namespace kaguya;

    lua["IndexBuffer"].setClass(UserdataMetatable<IndexBuffer, Object>()
        .addStaticFunction("new", &CreateObject<IndexBuffer>)
        
        .addFunction("SetShadowed", &IndexBuffer::SetShadowed)
        .addFunction("SetSize", &IndexBuffer::SetSize)
        
        .addFunction("IsShadowed", &IndexBuffer::IsShadowed)
        .addFunction("IsDynamic", &IndexBuffer::IsDynamic)
        .addFunction("IsLocked", &IndexBuffer::IsLocked)
        .addFunction("GetIndexCount", &IndexBuffer::GetIndexCount)
        .addFunction("GetIndexSize", &IndexBuffer::GetIndexSize)
                
        .addProperty("shadowed", &IndexBuffer::IsShadowed, &IndexBuffer::SetShadowed)
        .addProperty("dynamic", &IndexBuffer::IsDynamic)
        .addProperty("locked", &IndexBuffer::IsLocked)
        .addProperty("indexCount", &IndexBuffer::GetIndexCount)
        .addProperty("indexSize", &IndexBuffer::GetIndexSize)
    );
}

static void MaterialSetTechnique0(Material* material, unsigned index, Technique* tech)
{
    material->SetTechnique(index, tech);
}

static void MaterialSetTechnique1(Material* material, unsigned index, Technique* tech, unsigned qualityLevel)
{
    material->SetTechnique(index, tech, qualityLevel);
}

static void MaterialSetTechnique2(Material* material, unsigned index, Technique* tech, unsigned qualityLevel, float lodDistance)
{
    material->SetTechnique(index, tech, qualityLevel, lodDistance);
}

static void RegisterMaterial(kaguya::State& lua)
{
    using namespace kaguya;

    lua["DEFAULT_RENDER_ORDER"] = DEFAULT_RENDER_ORDER;

    lua["Material"].setClass(UserdataMetatable<Material, Resource>()
        .addStaticFunction("new", &CreateObject<Material>)
        
        .addFunction("SetNumTechniques", &Material::SetNumTechniques)
        
        ADD_OVERLOADED_FUNCTIONS_3(Material, SetTechnique)

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
        // .addFunction("GetTextures", &Material::GetTextures)
        .addFunction("GetShaderParameter", &Material::GetShaderParameter)
        .addFunction("GetShaderParameterAnimation", &Material::GetShaderParameterAnimation)
        .addFunction("GetShaderParameterAnimationWrapMode", &Material::GetShaderParameterAnimationWrapMode)
        .addFunction("GetShaderParameterAnimationSpeed", &Material::GetShaderParameterAnimationSpeed)
        // .addFunction("GetShaderParameters", &Material::GetShaderParameters)
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
        // .addProperty("textures", &Material::GetTextures)
        // .addProperty("shaderParameters", &Material::GetShaderParameters)
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

        .addProperty("numRenderTargets", &RenderPath::GetNumRenderTargets)
        .addProperty("numCommands", &RenderPath::GetNumCommands)
        .addProperty("renderTargets", &RenderPath::renderTargets_)
        .addProperty("commands", &RenderPath::commands_)
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

    lua["Shader"].setClass(UserdataMetatable<Shader, Resource>()
        .addStaticFunction("new", &CreateObject<Shader>)
        
        // .addFunction("GetVariation", &Shader::GetVariation)
        // .addFunction("GetSourceCode", &Shader::GetSourceCode)
        // .addFunction("GetTimeStamp", &Shader::GetTimeStamp)

        // .addProperty("timeStamp", &Shader::GetTimeStamp)
    );
}

static void RegisterShaderVariation(kaguya::State& lua)
{
    using namespace kaguya;

    lua["ShaderVariation"].setClass(UserdataMetatable<ShaderVariation, RefCounted>()
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

    lua["Technique"].setClass(UserdataMetatable<Technique, Resource>()
        .addStaticFunction("new", &CreateObject<Technique>)
        
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

    lua["MAX_TEXTURE_QUALITY_LEVELS"] = MAX_TEXTURE_QUALITY_LEVELS;

    lua["Texture"].setClass(UserdataMetatable<Texture, Resource>()
        .addStaticFunction("new", &CreateObject<Texture>)
        
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

    lua["Texture2D"].setClass(UserdataMetatable<Texture2D, Texture>()
        .addStaticFunction("new", &CreateObject<Texture2D>)
        
        .addFunction("SetSize", &Texture2D::SetSize)
        .addFunction("SetData", static_cast<bool(Texture2D::*)(Image*, bool)>(&Texture2D::SetData))

        .addFunction("GetRenderSurface", &Texture2D::GetRenderSurface)
        .addProperty("renderSurface", &Texture2D::GetRenderSurface)
    );
}

static void RegisterTexture2DArray(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Texture2DArray"].setClass(UserdataMetatable<Texture2DArray, Texture>()
        .addStaticFunction("new", &CreateObject<Texture2DArray>)
        
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

    lua["Texture3D"].setClass(UserdataMetatable<Texture3D, Texture>()
        .addStaticFunction("new", &CreateObject<Texture3D>)
        
        .addFunction("SetSize", &Texture3D::SetSize)
        .addFunction("SetData", static_cast<bool(Texture3D::*)(Image*, bool)>(&Texture3D::SetData))
    );
}

static void RegisterTextureCube(kaguya::State& lua)
{
    using namespace kaguya;

    lua["TextureCube"].setClass(UserdataMetatable<TextureCube, Texture>()
        .addStaticFunction("new", &CreateObject<TextureCube>)
        
        .addFunction("SetSize", &TextureCube::SetSize)
        .addFunction("SetData", static_cast<bool(TextureCube::*)(CubeMapFace, Image*, bool)>(&TextureCube::SetData))

    );
}

static void RegisterVertexBuffer(kaguya::State& lua)
{
    using namespace kaguya;

    lua["VertexBuffer"].setClass(UserdataMetatable<VertexBuffer, GPUObject>()
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

    lua["graphics"] = GetSubsystem<Graphics>();
    lua["GetGraphics"] = GetSubsystem<Graphics>();

    lua["renderer"] = GetSubsystem<Renderer>();
    lua["GetRenderer"] = GetSubsystem<Renderer>;

    kaguya::LuaTable metatable = lua["__CALLABLE__"];

    lua["Pass"].setMetatable(metatable);
    lua["RenderPath"].setMetatable(metatable);
    lua["RenderPathCommand"].setMetatable(metatable);
    lua["RenderSurface"].setMetatable(metatable);
    lua["RenderTargetInfo"].setMetatable(metatable);
    lua["ShaderVariation"].setMetatable(metatable);
    lua["VertexElement"].setMetatable(metatable);
}
}
