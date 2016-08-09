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

    // [Enum] RenderCommandType
    // [Variable] CMD_NONE
    lua["CMD_NONE"] = CMD_NONE;
    // [Variable] CMD_CLEAR,
    lua["CMD_CLEAR"] = CMD_CLEAR;
    // [Variable] CMD_SCENEPASS,
    lua["CMD_SCENEPASS"] = CMD_SCENEPASS;
    // [Variable] CMD_QUAD,
    lua["CMD_QUAD"] = CMD_QUAD;
    // [Variable] CMD_FORWARDLIGHTS,
    lua["CMD_FORWARDLIGHTS"] = CMD_FORWARDLIGHTS;
    // [Variable] CMD_LIGHTVOLUMES,
    lua["CMD_LIGHTVOLUMES"] = CMD_LIGHTVOLUMES;
    // [Variable] CMD_RENDERUI,
    lua["CMD_RENDERUI"] = CMD_RENDERUI;
    // [Variable] CMD_SENDEVENT
    lua["CMD_SENDEVENT"] = CMD_SENDEVENT;

    // [Enum] RenderCommandSortMode
    // [Variable] SORT_FRONTTOBACK
    lua["SORT_FRONTTOBACK"] = SORT_FRONTTOBACK;
    // [Variable] SORT_BACKTOFRONT
    lua["SORT_BACKTOFRONT"] = SORT_BACKTOFRONT;

    // [Enum] RenderTargetSizeMode
    // [Variable] SIZE_ABSOLUTE
    lua["SIZE_ABSOLUTE"] = SIZE_ABSOLUTE;
    // [Variable] SIZE_VIEWPORTDIVISOR,
    lua["SIZE_VIEWPORTDIVISOR"] = SIZE_VIEWPORTDIVISOR;
    // [Variable] SIZE_VIEWPORTMULTIPLIER
    lua["SIZE_VIEWPORTMULTIPLIER"] = SIZE_VIEWPORTMULTIPLIER;

    // [Class] RenderTargetInfo
    lua["RenderTargetInfo"].setClass(UserdataMetatable<RenderTargetInfo>()
        .setConstructors<RenderTargetInfo()>()

        // [Method] void Load(const XMLElement& element)
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

    // [Class] RenderPathCommand
    lua["RenderPathCommand"].setClass(UserdataMetatable<RenderPathCommand>()
        .setConstructors<RenderPathCommand()>()

        // [Method] void Load(const XMLElement& element)
        .addFunction("Load", &RenderPathCommand::Load)

        // [Method] void SetTextureName(TextureUnit unit, const String& name)
        .addFunction("SetTextureName", &RenderPathCommand::SetTextureName)
        // [Method] void SetShaderParameter(const String& name, const Variant& value)
        .addFunction("SetShaderParameter", &RenderPathCommand::SetShaderParameter)
        // [Method] void RemoveShaderParameter(const String& name)
        .addFunction("RemoveShaderParameter", &RenderPathCommand::RemoveShaderParameter)
        // [Method] void SetNumOutputs(unsigned num)
        .addFunction("SetNumOutputs", &RenderPathCommand::SetNumOutputs)
        
        // [Method] void SetOutput(unsigned index, const String& name, CubeMapFace face = FACE_POSITIVE_X)
        .addFunction("SetOutput", RenderPathCommandSetOutput())

        // [Method] void SetOutputName(unsigned index, const String& name)
        .addFunction("SetOutputName", &RenderPathCommand::SetOutputName)
        // [Method] void SetOutputFace(unsigned index, CubeMapFace face)
        .addFunction("SetOutputFace", &RenderPathCommand::SetOutputFace)
        // [Method] void SetDepthStencilName(const String& name)
        .addFunction("SetDepthStencilName", &RenderPathCommand::SetDepthStencilName)
        // [Method] const String& GetTextureName(TextureUnit unit) const
        .addFunction("GetTextureName", &RenderPathCommand::GetTextureName)
        // [Method] const Variant& GetShaderParameter(const String& name) const
        .addFunction("GetShaderParameter", &RenderPathCommand::GetShaderParameter)
        // [Method] unsigned GetNumOutputs() const
        .addFunction("GetNumOutputs", &RenderPathCommand::GetNumOutputs)
        // [Method] const String& GetOutputName(unsigned index) const
        .addFunction("GetOutputName", &RenderPathCommand::GetOutputName)
        // [Method] CubeMapFace GetOutputFace(unsigned index) const
        .addFunction("GetOutputFace", &RenderPathCommand::GetOutputFace)
        // [Method] const String& GetDepthStencilName() const
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

    // [Class] RenderPath : RefCounted
    lua["RenderPath"].setClass(UserdataMetatable<RenderPath, RefCounted>()
        .setConstructors<RenderPath()>()

        // [Method] SharedPtr<RenderPath> Clone()
        .addFunction("Clone", &RenderPath::Clone)

        // [Method] void Load(const XMLElement& element)
		.addFunction("Load", &RenderPath::Load)
        // [Method] bool Append(XMLFile* file)
        .addFunction("Append", &RenderPath::Append)
        
        // [Method] void SetEnabled(const String& tag, bool active)
        .addFunction("SetEnabled", &RenderPath::SetEnabled)
        // [Method] void ToggleEnabled(const String& tag)
        .addFunction("ToggleEnabled", &RenderPath::ToggleEnabled)
        // [Method] void SetRenderTarget(unsigned index, const RenderTargetInfo& info)
        .addFunction("SetRenderTarget", &RenderPath::SetRenderTarget)
        // [Method] void AddRenderTarget(const RenderTargetInfo& info)
        .addFunction("AddRenderTarget", &RenderPath::AddRenderTarget)

        .addOverloadedFunctions("RemoveRenderTarget",
            static_cast<void(RenderPath::*)(unsigned)>(&RenderPath::RemoveRenderTarget),
            static_cast<void(RenderPath::*)(const String&)>(&RenderPath::RemoveRenderTarget))

        // [Method] void RemoveRenderTargets(const String& tag)
        .addFunction("RemoveRenderTargets", &RenderPath::RemoveRenderTargets)

        // [Method] void SetCommand(unsigned index, const RenderPathCommand& command)
        .addFunction("SetCommand", &RenderPath::SetCommand)
        // [Method] void AddCommand(const RenderPathCommand& command)
        .addFunction("AddCommand", &RenderPath::AddCommand)
        // [Method] void InsertCommand(unsigned index, const RenderPathCommand& command)
        .addFunction("InsertCommand", &RenderPath::InsertCommand)
        // [Method] void RemoveCommand(unsigned index)
        .addFunction("RemoveCommand", &RenderPath::RemoveCommand)
        // [Method] void RemoveCommands(const String& tag)
        .addFunction("RemoveCommands", &RenderPath::RemoveCommands)

        // [Method] void SetShaderParameter(const String& name, const Variant& value)
        .addFunction("SetShaderParameter", &RenderPath::SetShaderParameter)
        
        // [Method] unsigned GetNumRenderTargets() const
        .addFunction("GetNumRenderTargets", &RenderPath::GetNumRenderTargets)
        // [Method] unsigned GetNumCommands() const
        .addFunction("GetNumCommands", &RenderPath::GetNumCommands)
        // [Method] RenderPathCommand* GetCommand(unsigned index)
        .addFunction("GetCommand", &RenderPath::GetCommand)
        // [Method] const Variant& GetShaderParameter(const String& name) const
        .addFunction("GetShaderParameter", &RenderPath::GetShaderParameter)
    );
}
}

