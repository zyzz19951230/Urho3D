#pragma once

#include "../Container/Ptr.h"
#include "../Container/Str.h"

#include <kaguya.hpp>

#define ADD_OVERLOADED_FUNCTIONS_2(Class, Name) \
.addOverloadedFunctions(#Name, &Class##Name##0, &Class##Name##1)

#define ADD_OVERLOADED_FUNCTIONS_3(Class, Name) \
.addOverloadedFunctions(#Name, &Class##Name##0, &Class##Name##1, &Class##Name##2)

#define ADD_OVERLOADED_FUNCTIONS_4(Class, Name) \
.addOverloadedFunctions(#Name, &Class##Name##0, &Class##Name##1, &Class##Name##2, &Class##Name##3)

#define ADD_OVERLOADED_FUNCTIONS_5(Class, Name) \
.addOverloadedFunctions(#Name, &Class##Name##0, &Class##Name##1, &Class##Name##2, &Class##Name##3, &Class##Name##4)

#define ADD_OVERLOADED_FUNCTIONS_6(Class, Name) \
.addOverloadedFunctions(#Name, &Class##Name##0, &Class##Name##1, &Class##Name##2, &Class##Name##3, &Class##Name##4, &Class##Name##5)

namespace Urho3D
{
    class Context;
    extern Context* globalContext;

    /// Create object.
    template<typename T>
    SharedPtr<T> CreateObject()
    {
        SharedPtr<T> tPtr(new T(globalContext));
        return tPtr;
    }

    /// Get subsystem.
    template<typename T>
    T* GetSubsystem()
    {
        return globalContext->GetSubsystem<T>();
    }
}

namespace kaguya
{
    /// Urho3D shared ptr wrapper.
    template<class T>
    struct Urho3DSharedPtrWrapper : ObjectWrapperBase
    {
        Urho3DSharedPtrWrapper(T* ptr) : object_(ptr)
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
            Urho3D::Object* object = dynamic_cast<Urho3D::Object*>(object_);
            if (object)
            {
                return object->GetStdTypeInfo();
            }
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

    // SharedPtr<T> type traits.
    template<typename T>
    struct lua_type_traits<Urho3D::SharedPtr<T>>
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

                T* o = p;
                new(storage) wrapper_type(o);

                Urho3D::Object* object = dynamic_cast<Urho3D::Object*>(o);
                if (object)
                {
                    class_userdata::setmetatable(l, object->GetStdTypeInfo());
                }
                else
                {
                    class_userdata::setmetatable<T>(l);
                }
            }
            return 1;
        }
    };

    // Urho3D::String type traits.
    template<>
    struct lua_type_traits<Urho3D::String>
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

    // PODVector<T> type traits.
    template<typename T>
    struct lua_type_traits<Urho3D::PODVector<T>>
    {
        typedef Urho3D::PODVector<T> get_type;
        typedef const Urho3D::PODVector<T>& push_type;

        static bool checkType(lua_State* l, int index)
        {
            return lua_type_traits<std::vector<T>>::checkType(l, index);
        }
        static bool strictCheckType(lua_State* l, int index)
        {
            return lua_type_traits<std::vector<T>>::strictCheckType(l, index);
        }
        static get_type get(lua_State* l, int index)
        {
            std::vector<T> std_res = lua_type_traits<std::vector<T>>::get(l, index);

            get_type res;
            res.Resize(std_res.size());

            for (size_t i = 0; i < std_res.size(); ++i)
                res[i] = std_res[i];

            return res;
        }
        static int push(lua_State* l, push_type p)
        {
            std::vector<T> std_p;
            std_p.resize(p.Size());

            for (unsigned i = 0; i < p.Size(); ++i)
                std_p[i] = p[i];

            return lua_type_traits<std::vector<T>>::push(l, std_p);
        }
    };

    // Vector<T> type traits.
    template<typename T>
    struct lua_type_traits<Urho3D::Vector<T>>
    {
        typedef Urho3D::Vector<T> get_type;
        typedef const Urho3D::Vector<T>& push_type;

        static bool checkType(lua_State* l, int index)
        {
            return lua_type_traits<std::vector<T>>::checkType(l, index);
        }
        static bool strictCheckType(lua_State* l, int index)
        {
            return lua_type_traits<std::vector<T>>::strictCheckType(l, index);
        }
        static get_type get(lua_State* l, int index)
        {
            std::vector<T> std_res = lua_type_traits<std::vector<T>>::get(l, index);
            
            get_type res;
            res.Resize(std_res.size());

            for (size_t i = 0; i < std_res.size(); ++i)
                res[i] = std_res[i];

            return res;
        }
        static int push(lua_State* l, push_type p)
        {
            std::vector<T> std_p;
            std_p.resize(p.Size());

            for (unsigned i = 0; i < p.Size(); ++i)
                std_p[i] = p[i];

            return lua_type_traits<std::vector<T>>::push(l, std_p);
        }
    };
}
