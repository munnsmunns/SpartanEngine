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

//= INCLUDES ====================================
#include "Widget.h"
#include <memory>
#include "../WidgetsDeferred/ButtonColorPicker.h"
//===============================================

namespace Spartan
{
    class Entity;
    class Transform;
    class Light;
    class Renderable;
    class PhysicsBody;
    class Collider;
    class Constraint;
    class Material;
    class Camera;
    class AudioSource;
    class AudioListener;
    class Script;
    class Terrain;
    class ReflectionProbe;
    class Component;
}

class Properties : public Widget
{
public:
    Properties(Editor* editor);

    void OnTickVisible() override;

    static void Inspect(const std::shared_ptr<Spartan::Entity> entity);
    static void Inspect(const std::shared_ptr<Spartan::Material> material);

    // Inspected resources
    static std::weak_ptr<Spartan::Entity> m_inspected_entity;
    static std::weak_ptr<Spartan::Material> m_inspected_material;

private:
    void ShowTransform(std::shared_ptr<Spartan::Transform> transform) const;
    void ShowLight(std::shared_ptr<Spartan::Light> light) const;
    void ShowRenderable(std::shared_ptr<Spartan::Renderable> renderable) const;
    void ShowPhysicsBody(std::shared_ptr<Spartan::PhysicsBody> rigid_body) const;
    void ShowConstraint(std::shared_ptr<Spartan::Constraint> constraint) const;
    void ShowMaterial(Spartan::Material* material) const;
    void ShowCamera(std::shared_ptr<Spartan::Camera> camera) const;
    void ShowTerrain(std::shared_ptr<Spartan::Terrain> terrain) const;
    void ShowAudioSource(std::shared_ptr<Spartan::AudioSource> audio_source) const;
    void ShowAudioListener(std::shared_ptr<Spartan::AudioListener> audio_listener) const;
    void ShowReflectionProbe(std::shared_ptr<Spartan::ReflectionProbe> reflection_probe) const;

    void ShowAddComponentButton() const;
    void ComponentContextMenu_Add() const;

    // Color pickers
    std::unique_ptr<ButtonColorPicker> m_material_color_picker;
    std::unique_ptr<ButtonColorPicker> m_colorPicker_light;
    std::unique_ptr<ButtonColorPicker> m_colorPicker_camera;
};
