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

#include "../../Core/Variant.h"
#include "../../Graphics/RenderPath.h"
#include "../../Resource/XMLElement.h"
#include "../../Resource/XMLFile.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(RenderPathCommandSetOutput, RenderPathCommand, SetOutput, 2, 3);

void RegisterRenderPath(kaguya::State& lua)
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
}

