#pragma once

#include "../Container/Ptr.h"
#include "../Container/Str.h"

#include <kaguya.hpp>

namespace Urho3D
{
    class Context;
    extern Context* globalContext;

    template<typename T>
    T* KCreateObject()
    {
        return new T(globalContext);
    }

    template<typename T>
    void KReleaseObject(T* object)
    {
        if (object)
            object->ReleaseRef();
    }
}

namespace kaguya
{
    template<> struct lua_type_traits<Urho3D::String>
    {
        typedef Urho3D::String get_type;
        typedef const Urho3D::String& push_type;

        static bool strictCheckType(lua_State* l, int index)
        {
            return lua_type(l, index) == LUA_TSTRING;
        }

        static bool checkType(lua_State* l, int index)
        {
            return lua_isstring(l, index) != 0;
        }

        static get_type get(lua_State* l, int index)
        {
            size_t size = 0;
            const char* buffer = lua_tolstring(l, index, &size);
            return Urho3D::String(buffer, size);
        }

        static int push(lua_State* l, push_type s)
        {
            lua_pushlstring(l, s.CString(), s.Length());
            return 1;
        }
    };

    template<typename T> struct lua_type_traits<Urho3D::SharedPtr<T>>
    {
        typedef const Urho3D::SharedPtr<T>& push_type;

        static int push(lua_State* l, push_type p)
        {
            T* o = p;
            o->AddRef();

            return util::push_args(l, o);
        }
    };
}
