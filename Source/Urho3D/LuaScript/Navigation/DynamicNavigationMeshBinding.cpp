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

#ifdef URHO3D_NAVIGATION

#include "../../Precompiled.h"

#include "../../Navigation/DynamicNavigationMesh.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterDynamicNavigationMesh(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] DynamicNavigationMesh : NavigationMesh
    lua["DynamicNavigationMesh"].setClass(UserdataMetatable<DynamicNavigationMesh, NavigationMesh>()
    	// [Constructor] DynamicNavigationMesh()
        .addStaticFunction("new", &CreateObject<DynamicNavigationMesh>)

        // [Method] void SetMaxObstacles(unsigned maxObstacles)
        .addFunction("SetMaxObstacles", &DynamicNavigationMesh::SetMaxObstacles)
        // [Method] void SetMaxLayers(unsigned maxLayers)
        .addFunction("SetMaxLayers", &DynamicNavigationMesh::SetMaxLayers)
        // [Method] void SetDrawObstacles(bool enable)
        .addFunction("SetDrawObstacles", &DynamicNavigationMesh::SetDrawObstacles)

        // [Method] bool GetDrawObstacles() const
        .addFunction("GetDrawObstacles", &DynamicNavigationMesh::GetDrawObstacles)
        // [Method] unsigned GetMaxLayers() const
        .addFunction("GetMaxLayers", &DynamicNavigationMesh::GetMaxLayers)
        // [Method] unsigned GetMaxObstacles() const
        .addFunction("GetMaxObstacles", &DynamicNavigationMesh::GetMaxObstacles)

        // [Property] unsigned maxObstacles
        .addProperty("maxObstacles", &DynamicNavigationMesh::GetMaxObstacles, &DynamicNavigationMesh::SetMaxObstacles)
        // [Property] unsigned maxLayers
        .addProperty("maxLayers", &DynamicNavigationMesh::GetMaxLayers, &DynamicNavigationMesh::SetMaxLayers)
        // [Property] bool drawObstacles
        .addProperty("drawObstacles", &DynamicNavigationMesh::GetDrawObstacles, &DynamicNavigationMesh::SetDrawObstacles)
        );
}
}

#endif
