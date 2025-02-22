/*
Copyright(c) 2016-2023 Panos Karabelas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

//= INCLUDES ====================
#include <memory>
#include <string>
#include <any>
#include <vector>
#include <functional>
#include "../../Core/SpObject.h"
//===============================

namespace Spartan
{
    class Entity;
    class Transform;
    class FileStream;

    enum class ComponentType : uint32_t
    {
        AudioListener,
        AudioSource,
        Camera,
        Constraint,
        Light,
        Renderable,
        PhysicsBody,
        Transform,
        Terrain,
        ReflectionProbe,
        Undefined
    };

    struct Attribute
    {
        std::function<std::any()> getter;
        std::function<void(std::any)> setter;
    };

    class SP_CLASS Component : public SpObject
    {
    public:
        Component(std::weak_ptr<Entity> entity);
        virtual ~Component() = default;

        // Runs when the component gets added
        virtual void OnInitialize() {}

        // Runs every time the simulation starts
        virtual void OnStart() {}

        // Runs every time the simulation stops
        virtual void OnStop() {}

        // Runs when the component is removed
        virtual void OnRemove() {}

        // Runs every frame
        virtual void OnTick() {}

        // Runs when the entity is being saved
        virtual void Serialize(FileStream* stream) {}

        // Runs when the entity is being loaded
        virtual void Deserialize(FileStream* stream) {}

        //= TYPE ===================================
        template <typename T>
        static constexpr ComponentType TypeToEnum();
        //==========================================

        //= PROPERTIES ==============================================================
        std::shared_ptr<Transform> GetTransform() const;
        ComponentType GetType()          const { return m_type; }
        void SetType(ComponentType type)       { m_type = type; }

        const auto& GetAttributes() const { return m_attributes; }
        void SetAttributes(const std::vector<Attribute>& attributes)
        { 
            for (uint32_t i = 0; i < static_cast<uint32_t>(m_attributes.size()); i++)
            {
                m_attributes[i].setter(attributes[i].getter());
            }
        }

        // Entity
        Entity* GetEntityPtr() const { return m_entity_ptr; }
        std::weak_ptr<Entity> GetEntityPtrWeak() { return m_entity_ptr_weak; }
        //===========================================================================
        
    protected:
        #define SP_REGISTER_ATTRIBUTE_GET_SET(getter, setter, type) RegisterAttribute(  \
        [this]()                        { return getter(); },                           \
        [this](const std::any& valueIn) { setter(std::any_cast<type>(valueIn)); });     \

        #define SP_REGISTER_ATTRIBUTE_VALUE_SET(value, setter, type) RegisterAttribute( \
        [this]()                        { return value; },                              \
        [this](const std::any& valueIn) { setter(std::any_cast<type>(valueIn)); });     \

        #define SP_REGISTER_ATTRIBUTE_VALUE_VALUE(value, type) RegisterAttribute(       \
        [this]()                        { return value; },                              \
        [this](const std::any& valueIn) { value = std::any_cast<type>(valueIn); });     \

        // Registers an attribute
        void RegisterAttribute(std::function<std::any()>&& getter, std::function<void(std::any)>&& setter)
        { 
            Attribute attribute;
            attribute.getter = std::move(getter);
            attribute.setter = std::move(setter);
            m_attributes.emplace_back(attribute);
        }

        // The type of the component
        ComponentType m_type = ComponentType::Undefined;
        // The state of the component
        bool m_enabled       = false;
        // The owner of the component
        std::weak_ptr<Entity> m_entity_ptr_weak;
        Entity* m_entity_ptr = nullptr;

    private:
        // The attributes of the component
        std::vector<Attribute> m_attributes;
    };
}
