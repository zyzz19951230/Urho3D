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

#include "../Precompiled.h"

#include "../Audio/Audio.h"
#include "../Audio/Sound.h"
#include "../Audio/SoundListener.h"
#include "../Audio/SoundSource.h"
#include "../Audio/SoundSource3D.h"
#include "../IO/File.h"
#include "../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

extern Context* globalContext;

KAGUYA_MEMBER_FUNCTION_OVERLOADS(AudioSetMode, Audio, SetMode, 3, 4);

static void RegisterAudio(kaguya::State& lua)
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

static bool SoundLoadRaw(Sound* sound, const char* filepath)
{
    SharedPtr<File> file(new File(globalContext, filepath));
    if (!file->IsOpen())
        return false;
    return sound->LoadRaw(*file);
}

static bool SoundLoadWav(Sound* sound, const char* filepath)
{
    SharedPtr<File> file(new File(globalContext, filepath));
    if (!file->IsOpen())
        return false;
    return sound->LoadWav(*file);
}

static bool SoundLoadOggVorbis(Sound* sound, const char* filepath)
{
    SharedPtr<File> file(new File(globalContext, filepath));
    if (!file->IsOpen())
        return false;
    return sound->LoadOggVorbis(*file);
}

static void RegisterSound(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Sound"].setClass(UserdataMetatable<Sound, Resource>()
        .addStaticFunction("new", &CreateObject<Sound>)

        .addOverloadedFunctions("LoadRaw", 
            &Sound::LoadRaw,
            &SoundLoadRaw)

        .addOverloadedFunctions("LoadWav", 
            &Sound::LoadWav,
            &SoundLoadWav)

        .addOverloadedFunctions("LoadOggVorbis", 
            &Sound::LoadOggVorbis,
            &SoundLoadOggVorbis)

        .addFunction("SetSize", &Sound::SetSize)
        .addFunction("SetData", &Sound::SetData)
        .addFunction("SetFormat", &Sound::SetFormat)
        .addFunction("SetLooped", &Sound::SetLooped)
        .addFunction("SetLoop", &Sound::SetLoop)

        .addFunction("GetLength", &Sound::GetLength)
        .addFunction("GetDataSize", &Sound::GetDataSize)
        .addFunction("GetSampleSize", &Sound::GetSampleSize)
        .addFunction("GetFrequency", &Sound::GetFrequency)
        .addFunction("GetIntFrequency", &Sound::GetIntFrequency)
        .addFunction("IsLooped", &Sound::IsLooped)
        .addFunction("IsSixteenBit", &Sound::IsSixteenBit)
        .addFunction("IsStereo", &Sound::IsStereo)
        .addFunction("IsCompressed", &Sound::IsCompressed)
        .addFunction("FixInterpolation", &Sound::FixInterpolation)

        .addProperty("length", &Sound::GetLength)
        .addProperty("dataSize", &Sound::GetDataSize)
        .addProperty("sampleSize", &Sound::GetSampleSize)
        .addProperty("frequency", &Sound::GetFrequency)
        .addProperty("intFrequency", &Sound::GetIntFrequency)
        .addProperty("looped", &Sound::IsLooped, &Sound::SetLooped)
        .addProperty("sixteenBit", &Sound::IsSixteenBit)
        .addProperty("stereo", &Sound::IsStereo)
        .addProperty("compressed", &Sound::IsCompressed)
        );
}

static void RegisterSoundListener(kaguya::State& lua)
{
    using namespace kaguya;

    lua["SoundListener"].setClass(UserdataMetatable<SoundListener, Component>()
        .addStaticFunction("new", &CreateObject<SoundListener>)
        );
}

static void RegisterSoundSource(kaguya::State& lua)
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

static void RegisterSoundSource3D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["SoundSource3D"].setClass(UserdataMetatable<SoundSource3D, SoundSource>()
        .addStaticFunction("new", &CreateObject<SoundSource3D>)

        .addFunction("SetDistanceAttenuation", &SoundSource3D::SetDistanceAttenuation)
        .addFunction("SetAngleAttenuation", &SoundSource3D::SetAngleAttenuation)
        .addFunction("SetNearDistance", &SoundSource3D::SetNearDistance)
        .addFunction("SetFarDistance", &SoundSource3D::SetFarDistance)
        .addFunction("SetInnerAngle", &SoundSource3D::SetInnerAngle)
        .addFunction("SetOuterAngle", &SoundSource3D::SetOuterAngle)
        .addFunction("SetRolloffFactor", &SoundSource3D::SetRolloffFactor)
        .addFunction("CalculateAttenuation", &SoundSource3D::CalculateAttenuation)

        .addFunction("GetNearDistance", &SoundSource3D::GetNearDistance)
        .addFunction("GetFarDistance", &SoundSource3D::GetFarDistance)
        .addFunction("GetInnerAngle", &SoundSource3D::GetInnerAngle)
        .addFunction("GetOuterAngle", &SoundSource3D::GetOuterAngle)
        .addFunction("RollAngleoffFactor", &SoundSource3D::RollAngleoffFactor)

        .addProperty("nearDistance", &SoundSource3D::GetNearDistance, &SoundSource3D::SetNearDistance)
        .addProperty("farDistance", &SoundSource3D::GetFarDistance, &SoundSource3D::SetFarDistance)
        .addProperty("innerAngle", &SoundSource3D::GetInnerAngle, &SoundSource3D::SetInnerAngle)
        .addProperty("outerAngle", &SoundSource3D::GetOuterAngle, &SoundSource3D::SetOuterAngle)
        .addProperty("rolloffFactor", &SoundSource3D::SetRolloffFactor)
        );
}

void RegisterAudioLuaAPI(kaguya::State& lua)
{
    RegisterAudio(lua);
    RegisterSound(lua);
    RegisterSoundListener(lua);
    RegisterSoundSource(lua);
    RegisterSoundSource3D(lua);

    lua["audio"] = GetSubsystem<Audio>();
    lua["GetAudio"] = GetSubsystem<Audio>;
}
}
