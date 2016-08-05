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

#include "../../Audio/Sound.h"
#include "../../Audio/SoundSource.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterSoundSource(kaguya::State& lua)
{
    using namespace kaguya;

    lua["STREAM_BUFFER_LENGTH"] = STREAM_BUFFER_LENGTH;

    lua["SoundSource"].setClass(UserdataMetatable<SoundSource, Component>()
        .addStaticFunction("new", &CreateObject<SoundSource>)

        .addOverloadedFunctions("Play",
            static_cast<void(SoundSource::*)(Sound*)>(&SoundSource::Play),
            static_cast<void(SoundSource::*)(Sound*, float)>(&SoundSource::Play),
            static_cast<void(SoundSource::*)(Sound*, float, float)>(&SoundSource::Play),
            static_cast<void(SoundSource::*)(Sound*, float, float, float)>(&SoundSource::Play))

        .addFunction("Stop", &SoundSource::Stop)
        .addFunction("SetSoundType", &SoundSource::SetSoundType)
        .addFunction("SetFrequency", &SoundSource::SetFrequency)
        .addFunction("SetGain", &SoundSource::SetGain)
        .addFunction("SetAttenuation", &SoundSource::SetAttenuation)
        .addFunction("SetPanning", &SoundSource::SetPanning)
        // .addFunction("SetAutoRemove", &SoundSource::SetAutoRemove)
        
        .addFunction("GetSound", &SoundSource::GetSound)
        .addFunction("GetSoundType", &SoundSource::GetSoundType)
        .addFunction("GetTimePosition", &SoundSource::GetTimePosition)
        .addFunction("GetFrequency", &SoundSource::GetFrequency)
        .addFunction("GetGain", &SoundSource::GetGain)
        .addFunction("GetAttenuation", &SoundSource::GetAttenuation)
        .addFunction("GetPanning", &SoundSource::GetPanning)
        // .addFunction("GetAutoRemove", &SoundSource::GetAutoRemove)
        .addFunction("IsPlaying", &SoundSource::IsPlaying)
        
        .addProperty("sound", &SoundSource::GetSound)
        .addProperty("soundType", &SoundSource::GetSoundType, &SoundSource::SetSoundType)
        .addProperty("timePosition", &SoundSource::GetTimePosition)
        .addProperty("frequency", &SoundSource::GetFrequency, &SoundSource::SetFrequency)
        .addProperty("gain", &SoundSource::GetGain, &SoundSource::SetGain)
        .addProperty("attenuation", &SoundSource::GetAttenuation, &SoundSource::SetAttenuation)
        .addProperty("panning", &SoundSource::GetPanning, &SoundSource::SetPanning)
        // .addProperty("autoRemove", &SoundSource::GetAutoRemove, &SoundSource::SetAutoRemove)
        .addProperty("playing", &SoundSource::IsPlaying)
        );
}
}

