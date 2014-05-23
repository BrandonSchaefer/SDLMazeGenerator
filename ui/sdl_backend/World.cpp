// -*- Mode: C++; indent-tabs-mode: nil; tab-width: 2 -*-
/*
 * Copyright (C) 2014 Brandon Schaefer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Brandon Schaefer <brandontschaefer@gmail.com>
 */

#include "World.h"
#include "GraphicsRenderer.h"

#include <functional>
#include <algorithm>

namespace sdl_backend
{

World::World(Rect const& rect)
  : rect_(rect)
{
}

Rect World::Boundary() const
{
  return rect_;
}

void World::SetBoundary(Rect const& rect)
{
  rect_ = rect;
}

void World::AddLayerToTop(EntityLayer::Ptr const& entity_layer)
{
  top_layers_.push_back(entity_layer);
}

void World::AddLayerToMiddle(EntityLayer::Ptr const& entity_layer)
{
  middle_layers_.push_back(entity_layer);
}

void World::AddLayerToBottom(EntityLayer::Ptr const& entity_layer)
{
  bottom_layers_.push_back(entity_layer);
}

Entity::Ptr FindEntity(std::vector<EntityLayer::Ptr> const& layers, unsigned id)
{
  for (auto& layer : layers)
  {
    Entity::Ptr entity = layer->GetEntity(id);
    if (entity)
    {
      return entity;
    }
  }

  return nullptr;
}

Entity::Ptr World::GetEntity(unsigned id)
{
  Entity::Ptr entity = FindEntity(top_layers_, id);
  if (!entity)
    entity = FindEntity(middle_layers_, id);
  if (!entity)
    entity = FindEntity(bottom_layers_, id);

  return entity;
}

template <typename FUNC>
void EmitSignal(std::vector<EntityLayer::Ptr> const& layers, FUNC const& func)
{
  for (auto const& layer : layers)
    if (layer->Visible())
      for_each(layer->hash_table().begin(), layer->hash_table().end(), func);
}

void update_pos(EntityPair const& e, World::Ptr const& world) { e.second->UpdatePosition(world); }

void World::UpdatePositions(World::Ptr const& world)
{
  auto update_pos_fn = std::bind(update_pos, std::placeholders::_1, world);
  EmitSignal(bottom_layers_, update_pos_fn);
  EmitSignal(middle_layers_, update_pos_fn);
  EmitSignal(top_layers_, update_pos_fn);
}

void update(EntityPair const& e, float delta_time) { e.second->Update(delta_time); }

void World::Update(float delta_time)
{
  auto update_fn = std::bind(update, std::placeholders::_1, delta_time);
  EmitSignal(bottom_layers_, update_fn);
  EmitSignal(middle_layers_, update_fn);
  EmitSignal(top_layers_, update_fn);
}

void draw(EntityPair const& e, GraphicsRenderer* renderer) { e.second->Draw(renderer); }

void World::Draw(GraphicsRenderer* renderer)
{
  auto draw_fn = std::bind(draw, std::placeholders::_1, renderer);
  EmitSignal(bottom_layers_, draw_fn);
  EmitSignal(middle_layers_, draw_fn);
  EmitSignal(top_layers_, draw_fn);
}

void key_down(EntityPair const& e, int keysym, int state, int repeat)
{
  e.second->key_down.emit(keysym, state, repeat);
}

void World::EmitKeyDown(int keysym, int state, int repeat)
{
  auto key_down_fn = std::bind(key_down, std::placeholders::_1, keysym, state, repeat);
  EmitSignal(bottom_layers_, key_down_fn);
  EmitSignal(middle_layers_, key_down_fn);
  EmitSignal(top_layers_, key_down_fn);
}

void key_up(EntityPair const& e, int keysym, int state, int repeat)
{
  e.second->key_up.emit(keysym, state, repeat);
}

void World::EmitKeyUp(int keysym, int state, int repeat)
{
  auto key_up_fn = std::bind(key_up, std::placeholders::_1, keysym, state, repeat);
  EmitSignal(bottom_layers_, key_up_fn);
  EmitSignal(middle_layers_, key_up_fn);
  EmitSignal(top_layers_, key_up_fn);
}

void text_input(EntityPair const& e, std::string text) { e.second->text_input.emit(text); }

void World::EmitTextInput(std::string text)
{
  auto text_input_fn = std::bind(text_input, std::placeholders::_1, text);
  EmitSignal(bottom_layers_, text_input_fn);
  EmitSignal(middle_layers_, text_input_fn);
  EmitSignal(top_layers_, text_input_fn);
}

void mouse_down(EntityPair const& e, int x, int y, int button, int clicks)
{
  e.second->mouse_down.emit(x, y, button, clicks);
}

void World::EmitMouseDown(int x, int y, int button, int clicks)
{
  auto mouse_down_fn = std::bind(mouse_down, std::placeholders::_1, x, y, button, clicks);
  EmitSignal(bottom_layers_, mouse_down_fn);
  EmitSignal(middle_layers_, mouse_down_fn);
  EmitSignal(top_layers_, mouse_down_fn);
}

void mouse_up(EntityPair const& e, int x, int y, int button, int clicks)
{
  e.second->mouse_up.emit(x, y, button, clicks);
}

void World::EmitMouseUp(int x, int y, int button, int clicks)
{
  auto mouse_up_fn = std::bind(mouse_up, std::placeholders::_1, x, y, button, clicks);
  EmitSignal(bottom_layers_, mouse_up_fn);
  EmitSignal(middle_layers_, mouse_up_fn);
  EmitSignal(top_layers_, mouse_up_fn);
}

void mouse_move(EntityPair const& e, int x, int y, int xrel, int yrel, int state)
{
  e.second->mouse_move.emit(x, y, xrel, yrel, state);
}

void World::EmitMouseMove(int x, int y, int xrel, int yrel, int state)
{
  auto mouse_move_fn = std::bind(mouse_move, std::placeholders::_1, x, y, xrel, yrel, state);
  EmitSignal(bottom_layers_, mouse_move_fn);
  EmitSignal(middle_layers_, mouse_move_fn);
  EmitSignal(top_layers_, mouse_move_fn);
}

void mouse_wheel(EntityPair const& e, int x, int y)
{
  e.second->mouse_wheel.emit(x, y);
}

void World::EmitMouseWheel(int x, int y)
{
  auto mouse_wheel_fn = std::bind(mouse_wheel, std::placeholders::_1, x, y);
  EmitSignal(bottom_layers_, mouse_wheel_fn);
  EmitSignal(middle_layers_, mouse_wheel_fn);
  EmitSignal(top_layers_, mouse_wheel_fn);
}

void finger_motion(EntityPair const& e, int x, int y, int dx, int dy)
{
  e.second->finger_motion.emit(x, y, dx, dy);
}

void World::EmitFingerMotion(int x, int y, int dx, int dy)
{
  auto finger_motion_fn = std::bind(finger_motion, std::placeholders::_1, x, y, dx, dy);
  EmitSignal(bottom_layers_, finger_motion_fn);
  EmitSignal(middle_layers_, finger_motion_fn);
  EmitSignal(top_layers_, finger_motion_fn);
}

void finger_down(EntityPair const& e, int x, int y, int dx, int dy)
{
  e.second->finger_down.emit(x, y, dx, dy);
}

void World::EmitFingerDown(int x, int y, int dx, int dy)
{
  auto finger_down_fn = std::bind(finger_down, std::placeholders::_1, x, y, dx, dy);
  EmitSignal(bottom_layers_, finger_down_fn);
  EmitSignal(middle_layers_, finger_down_fn);
  EmitSignal(top_layers_, finger_down_fn);
}

void finger_up(EntityPair const& e, int x, int y, int dx, int dy)
{
  e.second->finger_up.emit(x, y, dx, dy);
}

void World::EmitFingerUp(int x, int y, int dx, int dy)
{
  auto finger_up_fn = std::bind(finger_down, std::placeholders::_1, x, y, dx, dy);
  EmitSignal(bottom_layers_, finger_up_fn);
  EmitSignal(middle_layers_, finger_up_fn);
  EmitSignal(top_layers_, finger_up_fn);
}

void World::SetGameData(void* game_data)
{
  game_data_ = game_data;
}

void* World::GameData()
{
  return game_data_;
}

} // namespace sdl_backend
