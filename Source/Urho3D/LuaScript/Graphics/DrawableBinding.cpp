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

#include "../../Graphics/Drawable.h"
#include "../../Graphics/Zone.h"
#include "../../Graphics/Camera.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterDrawable(kaguya::State& lua)
{
    using namespace kaguya;

    // [Constant] unsigned DRAWABLE_GEOMETRY
    lua["DRAWABLE_GEOMETRY"] = DRAWABLE_GEOMETRY;
    // [Constant] unsigned DRAWABLE_LIGHT
    lua["DRAWABLE_LIGHT"] = DRAWABLE_LIGHT;
    // [Constant] unsigned DRAWABLE_ZONE
    lua["DRAWABLE_ZONE"] = DRAWABLE_ZONE;
    // [Constant] unsigned DRAWABLE_GEOMETRY2D
    lua["DRAWABLE_GEOMETRY2D"] = DRAWABLE_GEOMETRY2D;
    // [Constant] unsigned DRAWABLE_ANY
    lua["DRAWABLE_ANY"] = DRAWABLE_ANY;
    // [Constant] unsigned DEFAULT_VIEWMASK
    lua["DEFAULT_VIEWMASK"] = DEFAULT_VIEWMASK;
    // [Constant] unsigned DEFAULT_LIGHTMASK
    lua["DEFAULT_LIGHTMASK"] = DEFAULT_LIGHTMASK;
    // [Constant] unsigned DEFAULT_SHADOWMASK
    lua["DEFAULT_SHADOWMASK"] = DEFAULT_SHADOWMASK;
    // [Constant] unsigned DEFAULT_ZONEMASK
    lua["DEFAULT_ZONEMASK"] = DEFAULT_ZONEMASK;
    // [Constant] int MAX_VERTEX_LIGHTS
    lua["MAX_VERTEX_LIGHTS"] = MAX_VERTEX_LIGHTS;
    // [Constant] float ANIMATION_LOD_BASESCALE
    lua["ANIMATION_LOD_BASESCALE"] = ANIMATION_LOD_BASESCALE;

    // [Class] Drawable : Component
    lua["Drawable"].setClass(UserdataMetatable<Drawable, Component>()

        // [Method] void SetDrawDistance(float distance)
        .addFunction("SetDrawDistance", &Drawable::SetDrawDistance)
        // [Method] void SetShadowDistance(float distance)
        .addFunction("SetShadowDistance", &Drawable::SetShadowDistance)
        // [Method] void SetLodBias(float bias)
        .addFunction("SetLodBias", &Drawable::SetLodBias)
        // [Method] void SetViewMask(unsigned mask)
        .addFunction("SetViewMask", &Drawable::SetViewMask)
        // [Method] void SetLightMask(unsigned mask)
        .addFunction("SetLightMask", &Drawable::SetLightMask)
        // [Method] void SetShadowMask(unsigned mask)
        .addFunction("SetShadowMask", &Drawable::SetShadowMask)
        // [Method] void SetZoneMask(unsigned mask)
        .addFunction("SetZoneMask", &Drawable::SetZoneMask)
        // [Method] void SetMaxLights(unsigned num)
        .addFunction("SetMaxLights", &Drawable::SetMaxLights)
        // [Method] void SetCastShadows(bool enable)
        .addFunction("SetCastShadows", &Drawable::SetCastShadows)
        // [Method] void SetOccluder(bool enable)
        .addFunction("SetOccluder", &Drawable::SetOccluder)
        // [Method] void SetOccludee(bool enable)
        .addFunction("SetOccludee", &Drawable::SetOccludee)

        // [Method] void MarkForUpdate()
        .addFunction("MarkForUpdate", &Drawable::MarkForUpdate)

        // [Method] const BoundingBox& GetBoundingBox() const
        .addFunction("GetBoundingBox", &Drawable::GetBoundingBox)
        // [Method] const BoundingBox& GetWorldBoundingBox()
        .addFunction("GetWorldBoundingBox", &Drawable::GetWorldBoundingBox)
        
        // [Method] unsigned char GetDrawableFlags() const
        .addFunction("GetDrawableFlags", &Drawable::GetDrawableFlags)

        // [Method] float GetDrawDistance() const
        .addFunction("GetDrawDistance", &Drawable::GetDrawDistance)
        // [Method] float GetShadowDistance() const
        .addFunction("GetShadowDistance", &Drawable::GetShadowDistance)
        // [Method] float GetLodBias() const
        .addFunction("GetLodBias", &Drawable::GetLodBias)
        // [Method] unsigned GetViewMask() const
        .addFunction("GetViewMask", &Drawable::GetViewMask)
        // [Method] unsigned GetLightMask() const
        .addFunction("GetLightMask", &Drawable::GetLightMask)
        // [Method] unsigned GetShadowMask() const
        .addFunction("GetShadowMask", &Drawable::GetShadowMask)
        // [Method] unsigned GetZoneMask() const
        .addFunction("GetZoneMask", &Drawable::GetZoneMask)
        // [Method] unsigned GetMaxLights() const
        .addFunction("GetMaxLights", &Drawable::GetMaxLights)
        // [Method] bool GetCastShadows() const
        .addFunction("GetCastShadows", &Drawable::GetCastShadows)
        // [Method] bool IsOccluder() const
        .addFunction("IsOccluder", &Drawable::IsOccluder)
        // [Method] bool IsOccludee() const
        .addFunction("IsOccludee", &Drawable::IsOccludee)

        .addOverloadedFunctions("IsInView",
            // [Method] bool IsInView() const
            static_cast<bool(Drawable::*)() const>(&Drawable::IsInView),
            // [Method] bool IsInView(Camera* camera) const
            static_cast<bool(Drawable::*)(Camera*) const>(&Drawable::IsInView))

        // [Property(Readonly)] const BoundingBox& boundingBox
        .addProperty("boundingBox", &Drawable::GetBoundingBox)
        // [Property(Readonly)] unsigned char drawableFlags
        .addProperty("drawableFlags", &Drawable::GetDrawableFlags)
        // [Property] float drawDistance
        .addProperty("drawDistance", &Drawable::GetDrawDistance, &Drawable::SetDrawDistance)
        // [Property] float shadowDistance
        .addProperty("shadowDistance", &Drawable::GetShadowDistance, &Drawable::SetShadowDistance)
        // [Property] float lodBias
        .addProperty("lodBias", &Drawable::GetLodBias, &Drawable::SetLodBias)
        // [Property] unsigned viewMask
        .addProperty("viewMask", &Drawable::GetViewMask, &Drawable::SetViewMask)
        // [Property] unsigned lightMask
        .addProperty("lightMask", &Drawable::GetLightMask, &Drawable::SetLightMask)
        // [Property] unsigned shadowMask
        .addProperty("shadowMask", &Drawable::GetShadowMask, &Drawable::SetShadowMask)
        // [Property] unsigned zoneMask
        .addProperty("zoneMask", &Drawable::GetZoneMask, &Drawable::SetZoneMask)
        // [Property] unsigned maxLights
        .addProperty("maxLights", &Drawable::GetMaxLights, &Drawable::SetMaxLights)
        // [Property] bool castShadows
        .addProperty("castShadows", &Drawable::GetCastShadows, &Drawable::SetCastShadows)
        // [Property] bool occluder
        .addProperty("occluder", &Drawable::IsOccluder, &Drawable::SetOccluder)
        // [Property] bool occludee
        .addProperty("occludee", &Drawable::IsOccludee, &Drawable::SetOccludee)

        // [Property] bool inView
        .addProperty("inView", static_cast<bool(Drawable::*)() const>(&Drawable::IsInView))
        // [Property(Readonly)] Zone* zone
        .addProperty("zone", &Drawable::GetZone)
        );
}
}

