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

#ifdef URHO3D_NETWORK

#include "../../Precompiled.h"

#include "../../IO/VectorBuffer.h"
#include "../../Network/HttpRequest.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static VectorBuffer HttpRequestRead(HttpRequest* self, unsigned size)
{
    unsigned char* data = new unsigned char[size];
    self->Read(data, size);
    VectorBuffer buffer(data, size);
    delete[] data;
    return buffer;
}

void RegisterHttpRequest(kaguya::State& lua)
{
    using namespace kaguya;

    // [Enum] HttpRequestState
    lua["HTTP_INITIALIZING"] = HTTP_INITIALIZING;
    lua["HTTP_ERROR"] = HTTP_ERROR;
    lua["HTTP_OPEN"] = HTTP_OPEN;
    lua["HTTP_CLOSED"] = HTTP_CLOSED;

    // [Class] HttpRequest : RefCounted
    lua["HttpRequest"].setClass(UserdataMetatable<HttpRequest, RefCounted>()
        // [Constructor] HttpRequest(const String& url, const String& verb, const Vector<String>& headers, const String& postData)
        .setConstructors<HttpRequest(const String&, const String&, const Vector<String>&, const String&)>()

        // [Method] const String& GetURL() const
        .addFunction("GetURL", &HttpRequest::GetURL)
        // [Method] const String& GetVerb() const
        .addFunction("GetVerb", &HttpRequest::GetVerb)
        // [Method] String GetError() const
        .addFunction("GetError", &HttpRequest::GetError)
        // [Method] HttpRequestState GetState() const
        .addFunction("GetState", &HttpRequest::GetState)
        // [Method] unsigned GetAvailableSize() const
        .addFunction("GetAvailableSize", &HttpRequest::GetAvailableSize)
        // [Method] bool IsOpen() const
        .addFunction("IsOpen", &HttpRequest::IsOpen)

        // [Method] VectorBuffer Read(unsigned size)
        .addStaticFunction("Read", &HttpRequestRead)

        // [Property(ReadOnly)] const String& URL
        .addProperty("URL", &HttpRequest::GetURL)
        // [Property(ReadOnly)] const String& verb
        .addProperty("verb", &HttpRequest::GetVerb)
        // [Property(ReadOnly)] String error
        .addProperty("error", &HttpRequest::GetError)
        // [Property(ReadOnly)] HttpRequestState state
        .addProperty("state", &HttpRequest::GetState)
        // [Property(ReadOnly)] unsigned availableSize
        .addProperty("availableSize", &HttpRequest::GetAvailableSize)
        // [Property(ReadOnly)] bool open
        .addProperty("open", &HttpRequest::IsOpen)
        );
}
}

#endif
