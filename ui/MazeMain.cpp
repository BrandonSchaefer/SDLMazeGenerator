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

#include <SDL2/SDL_image.h>

#include "MazeMain.h"

#include <sdl_backend/Color.h>
#include <sdl_backend/EntityCreator.h>

namespace sdl_maze
{

namespace
{
  int const Y_OFFSET = 50;

  // FIXME Make this dynamic later...
  //sbe::Size GRID_SIZE(304, 209);
  //sbe::Size GRID_SIZE(250, 200);
  sbe::Size GRID_SIZE(200, 136);
  //sbe::Size GRID_SIZE(100, 68);
  //sbe::Size GRID_SIZE(70, 47);
  //sbe::Size GRID_SIZE(32, 22);
  //sbe::Size GRID_SIZE(16, 11);
}

MazeMain::MazeMain(unsigned id, sbe::MainLoop::Ptr const& main_loop)
  : Entity(id)
  , main_loop_(main_loop)
  , game_layer_(std::make_shared<sbe::EntityLayer>())
{
  sbe::Rect const& bound = main_loop_->world()->Boundary();
  main_loop_->world()->SetBoundary({0, Y_OFFSET, bound.width(), bound.height()});

  key_up.connect([this] (int keysym, int state, int repeat) {
    switch (keysym)
    {
      case SDLK_ESCAPE:
        main_loop_->Quit();
        break;
      default:
        break;
    }
  });

  SetupGame();

  main_loop_->world()->AddLayerToMiddle(game_layer_);
}

MazeMain::~MazeMain()
{
  game_layer_->Clear();
}

void MazeMain::SetupGame()
{
  sbe::EntityCreator ec;
  sbe::Rect const& bound = main_loop_->world()->Boundary();

  maze_controller_ = std::make_shared<MazeGridController>(ec.GetUniqueId(), main_loop_->Renderer(), GRID_SIZE);
  maze_controller_->SetRect(bound);

  top_menu_ = std::make_shared<TopMenu>(ec.GetUniqueId(), main_loop_->Renderer());
  top_menu_->SetRect({0, 0, bound.width(), Y_OFFSET});
  top_menu_->SetCurrentMazeName(maze_controller_->CurrentMazeName());

  maze_controller_->maze_changed.connect([this] (std::string const& name) {
    top_menu_->SetCurrentMazeName(name);
  });

  game_layer_->AddEntity(maze_controller_);
  game_layer_->AddEntity(top_menu_);
}

void MazeMain::UpdatePosition(sbe::World::Ptr const& world)
{
}

void MazeMain::Update(float delta_time)
{
}

void MazeMain::Draw(sbe::GraphicsRenderer* graphics)
{
  graphics->SetRenderColor(sbe::color::WHITE);
  SDL_Rect dest = {0, 0, graphics->Width(), graphics->Height()};
  SDL_RenderFillRect(graphics->Renderer(), &dest);
}

} // namespace sdl_maze
