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

  void SetOpen();

  void Reset();

  void Start();
  void Finish();
  void Mark();
  
  void Update(float delta_time) override;
  void Draw(sbe::GraphicsRenderer* graphics) override;

private:
  SDL_Color color_;

};

} // namespace sdl_maze

#endif // CELL_H
