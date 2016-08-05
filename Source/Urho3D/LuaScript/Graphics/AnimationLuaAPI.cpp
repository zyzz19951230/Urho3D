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

    lua["CHANNEL_POSITION"] = CHANNEL_POSITION;
    lua["CHANNEL_ROTATION"] = CHANNEL_ROTATION;
    lua["CHANNEL_SCALE"] = CHANNEL_SCALE;

    lua["AnimationKeyFrame"].setClass(UserdataMetatable<AnimationKeyFrame>()
    	
        .addProperty("time", &AnimationKeyFrame::time_)
    	.addProperty("position", &AnimationKeyFrame::position_)
    	.addProperty("rotation", &AnimationKeyFrame::rotation_)
    	.addProperty("scale", &AnimationKeyFrame::scale_)
    	);

	lua["AnimationTrack"].setClass(UserdataMetatable<AnimationTrack>()
    	
        .addFunction("SetKeyFrame", &AnimationTrack::SetKeyFrame)
    	.addFunction("AddKeyFrame", &AnimationTrack::AddKeyFrame)
    	.addFunction("InsertKeyFrame", &AnimationTrack::InsertKeyFrame)
    	.addFunction("RemoveKeyFrame", &AnimationTrack::RemoveKeyFrame)
    	.addFunction("RemoveAllKeyFrames", &AnimationTrack::RemoveAllKeyFrames)
    	.addFunction("GetKeyFrame", &AnimationTrack::GetKeyFrame)
    	.addFunction("GetNumKeyFrames", &AnimationTrack::GetNumKeyFrames)

    	.addProperty("name", &AnimationTrack::name_)
    	.addProperty("nameHash", &AnimationTrack::nameHash_)
    	.addProperty("channelMask", &AnimationTrack::channelMask_)
    	.addProperty("keyFrames", &AnimationTrack::keyFrames_)
    	.addProperty("numKeyFrames", &AnimationTrack::GetNumKeyFrames)
    	);

	lua["AnimationTriggerPoint"].setClass(UserdataMetatable<AnimationTriggerPoint>()
		.setConstructors<AnimationTriggerPoint()>()

		.addProperty("time", &AnimationTriggerPoint::time_)
    	.addProperty("data", &AnimationTriggerPoint::data_)
    	);

    lua["Animation"].setClass(UserdataMetatable<Animation, Resource>()
        .addStaticFunction("new", &CreateObject<Animation>)

        .addFunction("SetAnimationName", &Animation::SetAnimationName)
        .addFunction("SetLength", &Animation::SetLength)

        .addFunction("CreateTrack", &Animation::CreateTrack)
        .addFunction("RemoveTrack", &Animation::RemoveTrack)
        .addFunction("RemoveAllTracks", &Animation::RemoveAllTracks)

		.addFunction("SetTrigger", &Animation::SetTrigger)

        .addOverloadedFunctions("AddTrigger", 
        	static_cast<void(Animation::*)(const AnimationTriggerPoint&)>(&Animation::AddTrigger),
        	static_cast<void(Animation::*)(float, bool, const Variant&)>(&Animation::AddTrigger))
        
        .addFunction("RemoveTrigger", &Animation::RemoveTrigger)
        .addFunction("RemoveAllTriggers", &Animation::RemoveAllTriggers)
        
        .addFunction("Clone", AnimationClone())

        .addFunction("GetAnimationName", &Animation::GetAnimationName)
        .addFunction("GetAnimationNameHash", &Animation::GetAnimationNameHash)
        .addFunction("GetLength", &Animation::GetLength)
        .addFunction("GetNumTracks", &Animation::GetNumTracks)
        
        .addFunction("GetTrack", static_cast<AnimationTrack*(Animation::*)(const String&)>(&Animation::GetTrack))

        .addFunction("GetNumTriggers", &Animation::GetNumTriggers)

        .addFunction("GetTrigger", &Animation::GetTrigger)
        
        .addProperty("animationName", &Animation::GetAnimationName, &Animation::SetAnimationName)
        .addProperty("animationNameHash", &Animation::GetAnimationNameHash)
        .addProperty("length", &Animation::GetLength, &Animation::SetLength)
        .addProperty("numTracks", &Animation::GetNumTracks)
        .addProperty("numTriggers", &Animation::GetNumTriggers, &Animation::SetNumTriggers)
        );
}
}

