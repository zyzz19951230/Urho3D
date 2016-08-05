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
#include "../../IO/File.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

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

void RegisterSound(kaguya::State& lua)
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
}

