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

#ifndef CELL_H
#define CELL_H

#include <sdl_backend/RenderableGeometry.h>
#include <sdl_backend/StringTexture.h>

#include <SDL2/SDL_mixer.h>

#include <vector>

#include <memory>

namespace sbe = sdl_backend;

namespace sdl_maze
{

class Cell : public sbe::RenderableGeometry
{
public:
  typedef std::shared_ptr<Cell> Ptr;
  Cell(SDL_Renderer* renderer);
  ~Cell();

  void Update(float delta_time) override;
  void Draw(sbe::GraphicsRenderer* graphics) override;

  void Reset();

  bool Open() const;
  int Value() const;

  void Increment();
  void SetValue(int value);

  void PieceCombined();

private:
  int value_;
  int expand_;
  float total_;

  sbe::StringTexture value_texture_;
};

} // namespace sdl_maze

#endif // CELL_H
