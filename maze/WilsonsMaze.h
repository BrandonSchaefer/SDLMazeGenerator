//-*- Mode: C++; indent-tabs-mode: nil; tab-width: 2 -*-
/* * Copyright (C) 2013-2014 Brandon Schaefer
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

#ifndef WILSONSMAZE
#define WILSONSMAZE

#include "Marked.h"
#include "Maze.h"

namespace maze
{

class WilsonsMaze : public Maze
{
public:
  WilsonsMaze(int x, int y);

  void Generate();

  void GenerateNext();
  bool HasNext() const;

  std::string GetName() const;

private:
  Marked marked_;
  std::vector<Point> outside_cells_;
  std::vector<std::vector<Cell::Direction>> paths_;
};

} // namespace maze

#endif // WILSONSMAZE
