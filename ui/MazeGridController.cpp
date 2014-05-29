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

#include "MazeGridController.h"

#include <sdl_backend/Color.h>

#include <maze/Point.h>

namespace sdl_maze
{

namespace
{
}

MazeGridController::MazeGridController(unsigned id, SDL_Renderer* renderer, sbe::Size const& size)
  : Entity(id)
  , current_type_(maze::ALDOUS_BRODER)
  , size_(size)
  , maze_grid_(renderer, maze_factory_.CreateMaze(maze::MazeType(current_type_), size_.width - 2, size_.height - 2))
{
  geometry_changed.connect([this] {
    maze_grid_.SetRect(rect());
    maze_grid_.UpdateCellGeometry();
  });

  key_up.connect([this] (int keysym, int state, int repeat) {
    switch (keysym)
    {
      case SDLK_UP:
        maze_grid_.IncreaseGenSpeed();
        break;
      case SDLK_DOWN:
        maze_grid_.DecreaseGenSpeed();
        break;
      case SDLK_LEFT:
        current_type_ = maze::MazeType((current_type_ - 1 + maze::MazeType::Size) % maze::MazeType::Size);
        CreateNewMaze();
        break;
      case SDLK_RIGHT:
        current_type_ = maze::MazeType((current_type_ + 1) % maze::MazeType::Size);
        CreateNewMaze();
        break;
      case SDLK_s:
        maze_grid_.SolveMaze();
        break;
      case SDLK_g:
        CreateNewMaze();
        break;
      default:
        break;
    }
  });

  CreateNewMaze();
}

void MazeGridController::CreateNewMaze()
{
  maze_grid_.Clear();
  maze_grid_.SetNewMaze(maze_factory_.CreateMaze(maze::MazeType(current_type_), size_.width - 2, size_.height - 2));
  maze_changed.emit(maze_grid_.CurrentMazeName());
}

std::string MazeGridController::CurrentMazeName() const
{
  return maze_grid_.CurrentMazeName();
}

void MazeGridController::Update(float delta_time)
{
  maze_grid_.Update(delta_time);
}

void MazeGridController::UpdatePosition(sbe::World::Ptr const& world)
{
}

void MazeGridController::Draw(sbe::GraphicsRenderer* graphics)
{
  graphics->SetRenderColor(sbe::color::DARK_GREY);
  SDL_Rect dest = rect().sdl_rect();
  SDL_RenderFillRect(graphics->Renderer(), &dest);

  maze_grid_.Draw(graphics);
}

} // namespace sdl_maze
