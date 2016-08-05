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

    lua["DRAWABLE_GEOMETRY"] = DRAWABLE_GEOMETRY;
    lua["DRAWABLE_LIGHT"] = DRAWABLE_LIGHT;
    lua["DRAWABLE_ZONE"] = DRAWABLE_ZONE;
    lua["DRAWABLE_GEOMETRY2D"] = DRAWABLE_GEOMETRY2D;
    lua["DRAWABLE_ANY"] = DRAWABLE_ANY;
    lua["DEFAULT_VIEWMASK"] = DEFAULT_VIEWMASK;
    lua["DEFAULT_LIGHTMASK"] = DEFAULT_LIGHTMASK;
    lua["DEFAULT_SHADOWMASK"] = DEFAULT_SHADOWMASK;
    lua["DEFAULT_ZONEMASK"] = DEFAULT_ZONEMASK;
    lua["MAX_VERTEX_LIGHTS"] = MAX_VERTEX_LIGHTS;
    lua["ANIMATION_LOD_BASESCALE"] = ANIMATION_LOD_BASESCALE;

    lua["Drawable"].setClass(UserdataMetatable<Drawable, Component>()

        .addFunction("SetDrawDistance", &Drawable::SetDrawDistance)
        .addFunction("SetShadowDistance", &Drawable::SetShadowDistance)
        .addFunction("SetLodBias", &Drawable::SetLodBias)
        .addFunction("SetViewMask", &Drawable::SetViewMask)
        .addFunction("SetLightMask", &Drawable::SetLightMask)
        .addFunction("SetShadowMask", &Drawable::SetShadowMask)
        .addFunction("SetZoneMask", &Drawable::SetZoneMask)
        .addFunction("SetMaxLights", &Drawable::SetMaxLights)
        .addFunction("SetCastShadows", &Drawable::SetCastShadows)
        .addFunction("SetOccluder", &Drawable::SetOccluder)
        .addFunction("SetOccludee", &Drawable::SetOccludee)

        .addFunction("MarkForUpdate", &Drawable::MarkForUpdate)

        .addFunction("GetBoundingBox", &Drawable::GetBoundingBox)
        .addFunction("GetWorldBoundingBox", &Drawable::GetWorldBoundingBox)
        
        .addFunction("GetDrawableFlags", &Drawable::GetDrawableFlags)

        .addFunction("GetDrawDistance", &Drawable::GetDrawDistance)
        .addFunction("GetShadowDistance", &Drawable::GetShadowDistance)
        .addFunction("GetLodBias", &Drawable::GetLodBias)
        .addFunction("GetViewMask", &Drawable::GetViewMask)
        .addFunction("GetLightMask", &Drawable::GetLightMask)
        .addFunction("GetShadowMask", &Drawable::GetShadowMask)
        .addFunction("GetZoneMask", &Drawable::GetZoneMask)
        .addFunction("GetMaxLights", &Drawable::GetMaxLights)
        .addFunction("GetCastShadows", &Drawable::GetCastShadows)
        .addFunction("IsOccluder", &Drawable::IsOccluder)
        .addFunction("IsOccludee", &Drawable::IsOccludee)

        .addOverloadedFunctions("IsInView",
            static_cast<bool(Drawable::*)() const>(&Drawable::IsInView),
            static_cast<bool(Drawable::*)(Camera*) const>(&Drawable::IsInView))

        .addProperty("boundingBox", &Drawable::GetBoundingBox)
        .addProperty("drawableFlags", &Drawable::GetDrawableFlags)
        .addProperty("drawDistance", &Drawable::GetDrawDistance, &Drawable::SetDrawDistance)
        .addProperty("shadowDistance", &Drawable::GetShadowDistance, &Drawable::SetShadowDistance)
        .addProperty("lodBias", &Drawable::GetLodBias, &Drawable::SetLodBias)
        .addProperty("viewMask", &Drawable::GetViewMask, &Drawable::SetViewMask)
        .addProperty("lightMask", &Drawable::GetLightMask, &Drawable::SetLightMask)
        .addProperty("shadowMask", &Drawable::GetShadowMask, &Drawable::SetShadowMask)
        .addProperty("zoneMask", &Drawable::GetZoneMask, &Drawable::SetZoneMask)
        .addProperty("maxLights", &Drawable::GetMaxLights, &Drawable::SetMaxLights)
        .addProperty("castShadows", &Drawable::GetCastShadows, &Drawable::SetCastShadows)
        .addProperty("occluder", &Drawable::IsOccluder, &Drawable::SetOccluder)
        .addProperty("occludee", &Drawable::IsOccludee, &Drawable::SetOccludee)

        .addProperty("inView", static_cast<bool(Drawable::*)() const>(&Drawable::IsInView))
        .addProperty("zone", &Drawable::GetZone)
        );
}
}

