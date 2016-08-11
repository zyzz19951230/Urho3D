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

#include "../Precompiled.h"

#include <kaguya.hpp>

namespace Urho3D
{

extern void RegisterNavigationMesh(kaguya::State& lua);
extern void RegisterCrowdAgent(kaguya::State& lua);
extern void RegisterCrowdManager(kaguya::State& lua);
extern void RegisterDynamicNavigationMesh(kaguya::State& lua);
extern void RegisterNavArea(kaguya::State& lua);
extern void RegisterNavigable(kaguya::State& lua);
extern void RegisterObstacle(kaguya::State& lua);
extern void RegisterOffMeshConnection(kaguya::State& lua);

void RegisterNavigationLuaAPI(kaguya::State& lua)
{
    RegisterNavigationMesh(lua);

    RegisterCrowdAgent(lua);
    RegisterCrowdManager(lua);
    RegisterDynamicNavigationMesh(lua);
    RegisterNavArea(lua);
    RegisterNavigable(lua);    
    RegisterObstacle(lua);
    RegisterOffMeshConnection(lua);
}
}

#endif
