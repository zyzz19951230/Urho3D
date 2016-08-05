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

#include "../../Audio/Audio.h"
#include "../../Audio/Sound.h"
#include "../../Audio/SoundListener.h"
#include "../../Audio/SoundSource.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

extern Context* globalContext;

KAGUYA_MEMBER_FUNCTION_OVERLOADS(AudioSetMode, Audio, SetMode, 3, 4);

void RegisterAudio(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Audio"].setClass(UserdataMetatable<Audio, Object>()
        .addFunction("SetMode", AudioSetMode())

        .addFunction("Play", &Audio::Play)
        .addFunction("Stop", &Audio::Stop)
        .addFunction("SetMasterGain", &Audio::SetMasterGain)
        .addFunction("PauseSoundType", &Audio::PauseSoundType)
        .addFunction("ResumeSoundType", &Audio::ResumeSoundType)
        .addFunction("ResumeAll", &Audio::ResumeAll)
        .addFunction("SetListener", &Audio::SetListener)
        .addFunction("StopSound", &Audio::StopSound)

        .addFunction("GetSampleSize", &Audio::GetSampleSize)
        .addFunction("GetMixRate", &Audio::GetMixRate)
        .addFunction("GetInterpolation", &Audio::GetInterpolation)
        .addFunction("IsStereo", &Audio::IsStereo)
        .addFunction("IsPlaying", &Audio::IsPlaying)
        .addFunction("IsInitialized", &Audio::IsInitialized)
        .addFunction("GetMasterGain", &Audio::GetMasterGain)
        .addFunction("IsSoundTypePaused", &Audio::IsSoundTypePaused)
        .addFunction("GetListener", &Audio::GetListener)
        .addFunction("GetSoundSources", &Audio::GetSoundSources)
        .addFunction("HasMasterGain", &Audio::HasMasterGain)
        .addFunction("AddSoundSource", &Audio::AddSoundSource)
        .addFunction("RemoveSoundSource", &Audio::RemoveSoundSource)        
        
        // .addFunction("MixOutput", &Audio::MixOutput)

        .addProperty("sampleSize", &Audio::GetSampleSize)
        .addProperty("mixRate", &Audio::GetMixRate)
        .addProperty("interpolation", &Audio::GetInterpolation)
        .addProperty("stereo", &Audio::IsStereo)
        .addProperty("playing", &Audio::IsPlaying)
        .addProperty("initialized", &Audio::IsInitialized)
        .addProperty("listener", &Audio::GetListener, &Audio::SetListener)        
        );
}
}

