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

    // [Constant] int STREAM_BUFFER_LENGTH
    lua["STREAM_BUFFER_LENGTH"] = STREAM_BUFFER_LENGTH;

    // [Class] SoundSource : Component
    lua["SoundSource"].setClass(UserdataMetatable<SoundSource, Component>()
        // [Constructor] SoundSource()
        .addStaticFunction("new", &CreateObject<SoundSource>)

        .addOverloadedFunctions("Play",
            // [Method] void Play(Sound* sound)
            static_cast<void(SoundSource::*)(Sound*)>(&SoundSource::Play),
            // [Method] void Play(Sound* sound, float frequency)
            static_cast<void(SoundSource::*)(Sound*, float)>(&SoundSource::Play),
            // [Method] void Play(Sound* sound, float frequency, float gain)
            static_cast<void(SoundSource::*)(Sound*, float, float)>(&SoundSource::Play),
            // [Method] void Play(Sound* sound, float frequency, float gain, float panning)
            static_cast<void(SoundSource::*)(Sound*, float, float, float)>(&SoundSource::Play))

        // [Method] void Stop()
        .addFunction("Stop", &SoundSource::Stop)
        // [Method] void SetSoundType(const String& type)
        .addFunction("SetSoundType", &SoundSource::SetSoundType)
        // [Method] void SetFrequency(float frequency)
        .addFunction("SetFrequency", &SoundSource::SetFrequency)
        // [Method] void SetGain(float gain)
        .addFunction("SetGain", &SoundSource::SetGain)
        // [Method] void SetAttenuation(float attenuation)
        .addFunction("SetAttenuation", &SoundSource::SetAttenuation)
        // [Method] void SetPanning(float panning)
        .addFunction("SetPanning", &SoundSource::SetPanning)
        // [Method] Sound* GetSound() const
        .addFunction("GetSound", &SoundSource::GetSound)
        // [Method] String GetSoundType() const
        .addFunction("GetSoundType", &SoundSource::GetSoundType)
        // [Method] float GetTimePosition() const
        .addFunction("GetTimePosition", &SoundSource::GetTimePosition)
        // [Method] float GetFrequency() const
        .addFunction("GetFrequency", &SoundSource::GetFrequency)
        // [Method] float GetGain() const
        .addFunction("GetGain", &SoundSource::GetGain)
        // [Method] float GetAttenuation() const
        .addFunction("GetAttenuation", &SoundSource::GetAttenuation)
        // [Method] float GetPanning() const
        .addFunction("GetPanning", &SoundSource::GetPanning)
        // [Method] bool IsPlaying() const
        .addFunction("IsPlaying", &SoundSource::IsPlaying)
        
        // [Property(Readonly)] Sound* sound
        .addProperty("sound", &SoundSource::GetSound)
        // [Property] String soundType
        .addProperty("soundType", &SoundSource::GetSoundType, &SoundSource::SetSoundType)
        // [Property(Readonly)] float timePosition
        .addProperty("timePosition", &SoundSource::GetTimePosition)
        // [Property] float frequency
        .addProperty("frequency", &SoundSource::GetFrequency, &SoundSource::SetFrequency)
        // [Property] float gain
        .addProperty("gain", &SoundSource::GetGain, &SoundSource::SetGain)
        // [Property] float attenuation
        .addProperty("attenuation", &SoundSource::GetAttenuation, &SoundSource::SetAttenuation)
        // [Property] float panning
        .addProperty("panning", &SoundSource::GetPanning, &SoundSource::SetPanning)
        // [Property(Readonly)] bool playing
        .addProperty("playing", &SoundSource::IsPlaying)
        );
}
}

