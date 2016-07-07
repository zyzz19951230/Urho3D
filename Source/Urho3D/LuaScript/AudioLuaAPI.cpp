#include "../Audio/Audio.h"
#include "../Audio/AudioDefs.h"
#include "../Audio/AudioEvents.h"
#include "../Audio/BufferedSoundStream.h"
#include "../Audio/OggVorbisSoundStream.h"
#include "../Audio/Sound.h"
#include "../Audio/SoundListener.h"
#include "../Audio/SoundSource.h"
#include "../Audio/SoundSource3D.h"
#include "../Audio/SoundStream.h"
#include "../Core/Context.h"
#include "../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{
static void RegisterAudio(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Audio"].setClass(UserdataMetatable<Audio, Object>()

        .addFunction("SetMode", &Audio::SetMode)
        .addFunction("Update", &Audio::Update)
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
        .addFunction("GetMutex", &Audio::GetMutex)
        .addFunction("GetSoundSourceMasterGain", &Audio::GetSoundSourceMasterGain)
        .addFunction("MixOutput", &Audio::MixOutput)

        .addProperty("sampleSize", &Audio::GetSampleSize)
        .addProperty("mixRate", &Audio::GetMixRate)
        .addProperty("interpolation", &Audio::GetInterpolation)
        .addProperty("stereo", &Audio::IsStereo)
        .addProperty("playing", &Audio::IsPlaying)
        .addProperty("initialized", &Audio::IsInitialized)
        .addProperty("listener", &Audio::GetListener, &Audio::SetListener)
        .addProperty("soundSources", &Audio::GetSoundSources)
        .addProperty("mutex", &Audio::GetMutex)
        .addStaticField("SAMPLESIZEMUL", &Audio::SAMPLE_SIZE_MUL)
    );
}

static void RegisterAudioDefs(kaguya::State& lua)
{
    lua["SOUND_MASTER"] = SOUND_MASTER;
    lua["SOUND_EFFECT"] = SOUND_EFFECT;
    lua["SOUND_AMBIENT"] = SOUND_AMBIENT;
    lua["SOUND_VOICE"] = SOUND_VOICE;
    lua["SOUND_MUSIC"] = SOUND_MUSIC;
}

static void RegisterAudioEvents(kaguya::State& lua)
{
    lua["E_SOUNDFINISHED"] = E_SOUNDFINISHED;
}

static void RegisterBufferedSoundStream(kaguya::State& lua)
{
    using namespace kaguya;

    lua["BufferedSoundStream"].setClass(UserdataMetatable<BufferedSoundStream, SoundStream>()
        .setConstructors<BufferedSoundStream()>()
        
        .addFunction("Clear", &BufferedSoundStream::Clear)
        .addFunction("GetBufferNumBytes", &BufferedSoundStream::GetBufferNumBytes)
        .addFunction("GetBufferLength", &BufferedSoundStream::GetBufferLength)

        .addProperty("bufferNumBytes", &BufferedSoundStream::GetBufferNumBytes)
        .addProperty("bufferLength", &BufferedSoundStream::GetBufferLength)
    );
}

static void RegisterOggVorbisSoundStream(kaguya::State& lua)
{
    using namespace kaguya;

    lua["OggVorbisSoundStream"].setClass(UserdataMetatable<OggVorbisSoundStream, SoundStream>()
        .setConstructors<OggVorbisSoundStream(const Sound*)>()
        );        
}

static void RegisterSound(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Sound"].setClass(UserdataMetatable<Sound, Resource>()
        .addStaticFunction("new", &KCreateObject<Sound>)
        
        .addFunction("SetSize", &Sound::SetSize)

        .addFunction("SetFormat", &Sound::SetFormat)
        .addFunction("SetLooped", &Sound::SetLooped)
        .addFunction("SetLoop", &Sound::SetLoop)
        .addFunction("GetDecoderStream", &Sound::GetDecoderStream)
        .addFunction("GetStart", &Sound::GetStart)
        .addFunction("GetRepeat", &Sound::GetRepeat)
        .addFunction("GetEnd", &Sound::GetEnd)
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

        .addProperty("decoderStream", &Sound::GetDecoderStream)
        .addProperty("start", &Sound::GetStart)
        .addProperty("repeat", &Sound::GetRepeat)
        .addProperty("end", &Sound::GetEnd)
        .addProperty("length", &Sound::GetLength)
        .addProperty("dataSize", &Sound::GetDataSize)
        .addProperty("sampleSize", &Sound::GetSampleSize)
        .addProperty("frequency", &Sound::GetFrequency)
        .addProperty("intFrequency", &Sound::GetIntFrequency)
        .addProperty("looped", &Sound::IsLooped, &Sound::SetLooped)
        .addProperty("sixteenBit", &Sound::IsSixteenBit)
        .addProperty("stereo", &Sound::IsStereo)
        .addProperty("compressed", &Sound::IsCompressed)
        .addProperty("size", &Sound::SetSize)
    );
}

static void RegisterSoundListener(kaguya::State& lua)
{
    using namespace kaguya;

    lua["SoundListener"].setClass(UserdataMetatable<SoundListener, Component>()
        .addStaticFunction("new", &KCreateObject<SoundListener>)
        );
}

static void RegisterSoundSource(kaguya::State& lua)
{
    using namespace kaguya;

    lua["STREAM_BUFFER_LENGTH"] = STREAM_BUFFER_LENGTH;
    lua["SoundSource"].setClass(UserdataMetatable<SoundSource, Component>()
        .addStaticFunction("new", &KCreateObject<SoundSource>)
        
        .addOverloadedFunctions("Play",
            static_cast<void(SoundSource::*)(Sound*)>(&SoundSource::Play),
            static_cast<void(SoundSource::*)(Sound*, float)>(&SoundSource::Play),
            static_cast<void(SoundSource::*)(Sound*, float, float)>(&SoundSource::Play),
            static_cast<void(SoundSource::*)(Sound*, float, float, float)>(&SoundSource::Play),
            static_cast<void(SoundSource::*)(SoundStream*)>(&SoundSource::Play))

        .addFunction("Stop", &SoundSource::Stop)
        .addFunction("SetSoundType", &SoundSource::SetSoundType)
        .addFunction("SetFrequency", &SoundSource::SetFrequency)
        .addFunction("SetGain", &SoundSource::SetGain)
        .addFunction("SetAttenuation", &SoundSource::SetAttenuation)
        .addFunction("SetPanning", &SoundSource::SetPanning)
        .addFunction("SetPlayPosition", &SoundSource::SetPlayPosition)
        .addFunction("GetSound", &SoundSource::GetSound)
        // .addFunction("GetPlayPosition", &SoundSource::GetPlayPosition)
        .addFunction("GetSoundType", &SoundSource::GetSoundType)
        .addFunction("GetTimePosition", &SoundSource::GetTimePosition)
        .addFunction("GetFrequency", &SoundSource::GetFrequency)
        .addFunction("GetGain", &SoundSource::GetGain)
        .addFunction("GetAttenuation", &SoundSource::GetAttenuation)
        .addFunction("GetPanning", &SoundSource::GetPanning)
        .addFunction("IsPlaying", &SoundSource::IsPlaying)
        .addFunction("UpdateMasterGain", &SoundSource::UpdateMasterGain)

        .addProperty("sound", &SoundSource::GetSound)
        // .addProperty("playPosition", &SoundSource::GetPlayPosition, &SoundSource::SetPlayPosition)
        .addProperty("soundType", &SoundSource::GetSoundType, &SoundSource::SetSoundType)
        .addProperty("timePosition", &SoundSource::GetTimePosition)
        .addProperty("frequency", &SoundSource::GetFrequency, &SoundSource::SetFrequency)
        .addProperty("gain", &SoundSource::GetGain, &SoundSource::SetGain)
        .addProperty("attenuation", &SoundSource::GetAttenuation, &SoundSource::SetAttenuation)
        .addProperty("panning", &SoundSource::GetPanning, &SoundSource::SetPanning)
        .addProperty("playing", &SoundSource::IsPlaying)
    );
}

static void RegisterSoundSource3D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["SoundSource3D"].setClass(UserdataMetatable<SoundSource3D, SoundSource>()
        .addStaticFunction("new", &KCreateObject<SoundSource3D>)
        
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

static void RegisterSoundStream(kaguya::State& lua)
{
    using namespace kaguya;

    lua["SoundStream"].setClass(UserdataMetatable<SoundStream, RefCounted>()

        .addFunction("GetData", &SoundStream::GetData)
        .addFunction("SetFormat", &SoundStream::SetFormat)
        .addFunction("SetStopAtEnd", &SoundStream::SetStopAtEnd)
        .addFunction("GetSampleSize", &SoundStream::GetSampleSize)
        .addFunction("GetFrequency", &SoundStream::GetFrequency)
        .addFunction("GetIntFrequency", &SoundStream::GetIntFrequency)
        .addFunction("GetStopAtEnd", &SoundStream::GetStopAtEnd)
        .addFunction("IsSixteenBit", &SoundStream::IsSixteenBit)
        .addFunction("IsStereo", &SoundStream::IsStereo)

        .addProperty("sampleSize", &SoundStream::GetSampleSize)
        .addProperty("frequency", &SoundStream::GetFrequency)
        .addProperty("intFrequency", &SoundStream::GetIntFrequency)
        .addProperty("stopAtEnd", &SoundStream::GetStopAtEnd, &SoundStream::SetStopAtEnd)
        .addProperty("sixteenBit", &SoundStream::IsSixteenBit)
        .addProperty("stereo", &SoundStream::IsStereo)
    );
}

void RegisterAudioLuaAPI(kaguya::State& lua)
{
    RegisterSoundStream(lua);

    RegisterAudio(lua);
    RegisterAudioDefs(lua);
    RegisterAudioEvents(lua);
    RegisterBufferedSoundStream(lua);
    RegisterOggVorbisSoundStream(lua);
    RegisterSound(lua);
    RegisterSoundListener(lua);
    RegisterSoundSource(lua);
    RegisterSoundSource3D(lua);

    lua["audio"] = KGetSubsystem<Audio>();
    lua["GetAudio"] = KGetSubsystem<Audio>;
}
}
