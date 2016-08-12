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

#include "../../Graphics/Animation.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(AnimationClone, Animation, Clone, 0, 1);

void RegisterAnimation(kaguya::State& lua)
{
    using namespace kaguya;

    // [Constant] unsigned char CHANNEL_POSITION
    lua["CHANNEL_POSITION"] = CHANNEL_POSITION;
    // [Constant] unsigned char CHANNEL_ROTATION
    lua["CHANNEL_ROTATION"] = CHANNEL_ROTATION;
    // [Constant] unsigned char CHANNEL_SCALE
    lua["CHANNEL_SCALE"] = CHANNEL_SCALE;

    // [Class] AnimationKeyFrame
    lua["AnimationKeyFrame"].setClass(UserdataMetatable<AnimationKeyFrame>()
        
        // [Field] float time
        .addProperty("time", &AnimationKeyFrame::time_)
        // [Field] Vector3 position
        .addProperty("position", &AnimationKeyFrame::position_)
        // [Field] Quaternion rotation
        .addProperty("rotation", &AnimationKeyFrame::rotation_)
        // [Field] Vector3 scale
        .addProperty("scale", &AnimationKeyFrame::scale_)
        );

    // [Class] AnimationTrack
    lua["AnimationTrack"].setClass(UserdataMetatable<AnimationTrack>()
        
        // [Method] void SetKeyFrame(unsigned index, const AnimationKeyFrame& command)
        .addFunction("SetKeyFrame", &AnimationTrack::SetKeyFrame)
        // [Method] void AddKeyFrame(const AnimationKeyFrame& keyFrame)
        .addFunction("AddKeyFrame", &AnimationTrack::AddKeyFrame)
        // [Method] void InsertKeyFrame(unsigned index, const AnimationKeyFrame& keyFrame)
        .addFunction("InsertKeyFrame", &AnimationTrack::InsertKeyFrame)
        // [Method] void RemoveKeyFrame(unsigned index)
        .addFunction("RemoveKeyFrame", &AnimationTrack::RemoveKeyFrame)
        // [Method] void RemoveAllKeyFrames()
        .addFunction("RemoveAllKeyFrames", &AnimationTrack::RemoveAllKeyFrames)
        // [Method] AnimationKeyFrame* GetKeyFrame(unsigned index)
        .addFunction("GetKeyFrame", &AnimationTrack::GetKeyFrame)
        // [Method] unsigned GetNumKeyFrames() const
        .addFunction("GetNumKeyFrames", &AnimationTrack::GetNumKeyFrames)

        // [Field] String name
        .addProperty("name", &AnimationTrack::name_)
        // [Field] StringHash nameHash
        .addProperty("nameHash", &AnimationTrack::nameHash_)
        // [Field] unsigned char channelMask
        .addProperty("channelMask", &AnimationTrack::channelMask_)
        // [Field] Vector<AnimationKeyFrame> keyFrames
        .addProperty("keyFrames", &AnimationTrack::keyFrames_)
        // [Property(Readonly)] unsigned numKeyFrames
        .addProperty("numKeyFrames", &AnimationTrack::GetNumKeyFrames)
        );

    // [Class] AnimationTriggerPoint
    lua["AnimationTriggerPoint"].setClass(UserdataMetatable<AnimationTriggerPoint>()
        // [Constructor] AnimationTriggerPoint()
        .setConstructors<AnimationTriggerPoint()>()

        // [Field] float time
        .addProperty("time", &AnimationTriggerPoint::time_)
        // [Field] Variant data
        .addProperty("data", &AnimationTriggerPoint::data_)
        );

    // [Class] Animation : Resource
    lua["Animation"].setClass(UserdataMetatable<Animation, Resource>()
        // [Constructor] Animation()
        .addStaticFunction("new", &CreateObject<Animation>)

        // [Method] void SetAnimationName(const String& name)
        .addFunction("SetAnimationName", &Animation::SetAnimationName)
        // [Method] void SetLength(float length)
        .addFunction("SetLength", &Animation::SetLength)

        // [Method] AnimationTrack* CreateTrack(const String& name)
        .addFunction("CreateTrack", &Animation::CreateTrack)
        // [Method] bool RemoveTrack(const String& name)
        .addFunction("RemoveTrack", &Animation::RemoveTrack)
        // [Method] void RemoveAllTracks()
        .addFunction("RemoveAllTracks", &Animation::RemoveAllTracks)

        // [Method] void SetTrigger(unsigned index, const AnimationTriggerPoint& trigger)
        .addFunction("SetTrigger", &Animation::SetTrigger)

        .addOverloadedFunctions("AddTrigger", 
            // [Method] void AddTrigger(const AnimationTriggerPoint& trigger)
            static_cast<void(Animation::*)(const AnimationTriggerPoint&)>(&Animation::AddTrigger),
            // [Method] void void AddTrigger(float time, bool timeIsNormalized, const Variant& data)
            static_cast<void(Animation::*)(float, bool, const Variant&)>(&Animation::AddTrigger))
        
        // [Method] void RemoveTrigger(unsigned index)
        .addFunction("RemoveTrigger", &Animation::RemoveTrigger)
        // [Method] void RemoveAllTriggers()
        .addFunction("RemoveAllTriggers", &Animation::RemoveAllTriggers)
        
        // [Method] SharedPtr<Animation> Clone(const String& cloneName = String::EMPTY) const
        .addFunction("Clone", AnimationClone())

        // [Method] const String& GetAnimationName() const
        .addFunction("GetAnimationName", &Animation::GetAnimationName)
        // [Method] StringHash GetAnimationNameHash() const
        .addFunction("GetAnimationNameHash", &Animation::GetAnimationNameHash)
        // [Method] float GetLength() const
        .addFunction("GetLength", &Animation::GetLength)
        // [Method] unsigned GetNumTracks() const
        .addFunction("GetNumTracks", &Animation::GetNumTracks)
        
        // [Method] AnimationTrack* GetTrack(const String& name)
        .addFunction("GetTrack", static_cast<AnimationTrack*(Animation::*)(const String&)>(&Animation::GetTrack))

        // [Method] unsigned GetNumTriggers() const
        .addFunction("GetNumTriggers", &Animation::GetNumTriggers)

        // [Method] AnimationTriggerPoint* GetTrigger(unsigned index)
        .addFunction("GetTrigger", &Animation::GetTrigger)
        
        // [Property] const String& animationName
        .addProperty("animationName", &Animation::GetAnimationName, &Animation::SetAnimationName)
        // [Property(Readonly)] StringHash animationNameHash
        .addProperty("animationNameHash", &Animation::GetAnimationNameHash)
        // [Property] float length
        .addProperty("length", &Animation::GetLength, &Animation::SetLength)
        // [Property(Readonly)] unsigned numTracks
        .addProperty("numTracks", &Animation::GetNumTracks)
        // [Property] unsigned numTriggers
        .addProperty("numTriggers", &Animation::GetNumTriggers, &Animation::SetNumTriggers)
        );
}
}

