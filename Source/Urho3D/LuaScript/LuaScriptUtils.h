#pragma once

#include "../Container/Ptr.h"
#include "../Container/Str.h"

#include <kaguya.hpp>

namespace kaguya
{
	template<class T>
    struct Urho3DSharedPtrWrapper : ObjectWrapperBase
    {
        Urho3DSharedPtrWrapper(T* ptr) :object_(ptr)
        {
            if (object_)
            {
                object_->AddRef();
            }
        }
        
        ~Urho3DSharedPtrWrapper()
        {
            if (object_)
            {
                object_->ReleaseRef();
            }
        }
        
        virtual const std::type_info& type()
        {
            return metatableType<T>();
        }

        virtual void* get()
        {
            if (traits::is_const<T>::value)
            {
                return 0;
            }
            return const_cast<void*>(static_cast<const void*>(object_));
        }

        virtual const void* cget()
        {
            return object_;
        }

    private:
        T* object_;
    };

    // Urho3D::SharedPtr<T>
    template<typename T> struct lua_type_traits<Urho3D::SharedPtr<T>>
    {
        typedef const Urho3D::SharedPtr<T>& push_type;

        static int push(lua_State* l, push_type p)
        {
            if (!p)
            {
                lua_pushnil(l);
            }
            else
            {
                typedef Urho3DSharedPtrWrapper<T> wrapper_type;
                void *storage = lua_newuserdata(l, sizeof(wrapper_type));
                new(storage) wrapper_type(p);
                class_userdata::setmetatable<T>(l);
            }

            return 1;
        }
    };

	// Urho3D::String
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
}

namespace Urho3D
{
    class Context;    
    
	extern Context* globalContext;

	template<typename T>
    SharedPtr<T> KCreateObject()
	{
		SharedPtr<T> tPtr(new T(globalContext));
		return tPtr;
	}

    template<typename T>
    SharedPtr<T> KGetSubsystem()
    {
        return SharedPtr<T>(globalContext->GetSubsystem<T>());
    }
}
