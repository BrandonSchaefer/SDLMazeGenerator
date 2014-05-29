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

#ifndef MAZE_GRID_H
#define MAZE_GRID_H

#include "Cell.h"

#include <sdl_backend/GraphicsRenderer.h>
#include <sdl_backend/RenderableGeometry.h>
#include <sdl_backend/Size.h>

namespace sbe = sdl_backend;

namespace sdl_maze
{

class MazeGrid : public sbe::RenderableGeometry
{
public:
  MazeGrid(SDL_Renderer* renderer, sbe::Size const& size);

  std::vector<sbe::Point> GetPointsToCheckFromDirection(sbe::Direction const& direction);

  void UpdateCellGeometry();

  void AddRandomPiece();

  int Value(sbe::Point const& point) const;
  bool Open(sbe::Point const& point) const;

  void Increment(sbe::Point const& point);
  void Reset(sbe::Point const& point);

  bool InBounds(sbe::Point const& point) const;

  void SwapCells(sbe::Point const& start, sbe::Point const& dest);

  bool CanAnyCellMove() const;
  bool NeighbourSharesValue(sbe::Point const& pos) const;

  void PieceCombined(sbe::Point const& pos);

  void Clear();

  virtual void Update(float delta_time) override;
  virtual void Draw(sbe::GraphicsRenderer* graphics) override;

private:

  std::vector<sbe::Point> GetRightPoints() const;
  std::vector<sbe::Point> GetUpPoints() const;
  std::vector<sbe::Point> GetDownPoints() const;
  std::vector<sbe::Point> GetLeftPoints() const;

  sbe::Size size_;
  std::vector<std::vector<Cell::Ptr>> grid_;
};

} // namespace sdl_maze

#endif // MAZE_GRID_H
