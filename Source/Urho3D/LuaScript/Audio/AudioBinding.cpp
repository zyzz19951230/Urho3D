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

    // [Class] Audio : Object
    lua["Audio"].setClass(UserdataMetatable<Audio, Object>()
        // [Method] bool SetMode(int bufferLengthMSec, int mixRate, bool stereo, bool interpolation = true)
        .addFunction("SetMode", AudioSetMode())

        // [Method] bool Play()
        .addFunction("Play", &Audio::Play)
        // [Method] void Stop()
        .addFunction("Stop", &Audio::Stop)
        // [Method] void SetMasterGain(const String& type, float gain)
        .addFunction("SetMasterGain", &Audio::SetMasterGain)
        // [Method] void PauseSoundType(const String& type)
        .addFunction("PauseSoundType", &Audio::PauseSoundType)
        // [Method] void ResumeSoundType(const String& type)
        .addFunction("ResumeSoundType", &Audio::ResumeSoundType)
        // [Method] void ResumeAll()
        .addFunction("ResumeAll", &Audio::ResumeAll)
        // [Method] void SetListener(SoundListener* listener)
        .addFunction("SetListener", &Audio::SetListener)
        // [Method] void StopSound(Sound* sound)
        .addFunction("StopSound", &Audio::StopSound)

        // [Method] unsigned GetSampleSize() const
        .addFunction("GetSampleSize", &Audio::GetSampleSize)
        // [Method] int GetMixRate() const
        .addFunction("GetMixRate", &Audio::GetMixRate)
        // [Method] bool GetInterpolation() const
        .addFunction("GetInterpolation", &Audio::GetInterpolation)
        // [Method] bool IsStereo() const
        .addFunction("IsStereo", &Audio::IsStereo)
        // [Method] bool IsPlaying() const
        .addFunction("IsPlaying", &Audio::IsPlaying)
        // [Method] bool IsInitialized() const
        .addFunction("IsInitialized", &Audio::IsInitialized)
        // [Method] float GetMasterGain(const String& type) const
        .addFunction("GetMasterGain", &Audio::GetMasterGain)
        // [Method] bool IsSoundTypePaused(const String& type) const
        .addFunction("IsSoundTypePaused", &Audio::IsSoundTypePaused)
        // [Method] SoundListener* GetListener() const
        .addFunction("GetListener", &Audio::GetListener)
        // [Method] const PODVector<SoundSource*>& GetSoundSources() const
        .addFunction("GetSoundSources", &Audio::GetSoundSources)
        // [Method] bool HasMasterGain(const String& type) const
        .addFunction("HasMasterGain", &Audio::HasMasterGain)
        // [Method] void AddSoundSource(SoundSource* soundSource)
        .addFunction("AddSoundSource", &Audio::AddSoundSource)
        // [Method] void RemoveSoundSource(SoundSource* soundSource)
        .addFunction("RemoveSoundSource", &Audio::RemoveSoundSource)        
        
        // [Property(Readonly)] unsigned sampleSize
        .addProperty("sampleSize", &Audio::GetSampleSize)
        // [Property(Readonly)] int mixRate
        .addProperty("mixRate", &Audio::GetMixRate)
        // [Property(Readonly)] bool interpolation
        .addProperty("interpolation", &Audio::GetInterpolation)
        // [Property(Readonly)] bool stereo
        .addProperty("stereo", &Audio::IsStereo)
        // [Property(Readonly)] bool playing
        .addProperty("playing", &Audio::IsPlaying)
        // [Property(Readonly)] bool initialized
        .addProperty("initialized", &Audio::IsInitialized)
        // [Property] SoundListener* listener
        .addProperty("listener", &Audio::GetListener, &Audio::SetListener)        
        );

    // [Variable] Audio* audio
    lua["audio"] = GetSubsystem<Audio>();
    // [Function] Audio* GetAudio()
    lua["GetAudio"] = static_cast<Audio*(*)()>(&GetSubsystem<Audio>);
}
}

