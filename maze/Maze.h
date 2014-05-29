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

#ifndef MAZE
#define MAZE

#include "Cell.h"
#include "Point.h"

#include <string>
#include <vector>
#include <memory>

namespace maze
{

struct RawMaze
{
  std::vector<std::vector<int>> raw_maze;
  Point start;
  Point finish;
};

class Maze
{
public:
  typedef std::shared_ptr<Maze> Ptr;

  Maze (int width, int height);

  int Columns() const;
  int Rows() const;

  void OpenPassage(Point p, Cell::Direction dir);
  void SetWall(Point p, Cell::Direction dir);

  void SetStart(Point const& start);

  Point GetStart() const;
  Point GetFinish() const;

  bool DirOpen  (Point const& point, Cell::Direction const& dir);
  bool RightOpen(Point const& point);
  bool DownOpen (Point const& point);
  bool LeftOpen (Point const& point);
  bool UpOpen   (Point const& point);

  bool InBounds(Point const& pos) const;

  void SetParent(Point const& current, Point const& parent);
  bool ParentEqualPoint(Point const& parent, Point const& point);

  virtual void Generate() = 0;

  virtual void GenerateNext() = 0;
  virtual bool HasNext() const = 0;

  virtual std::string GetName() const = 0;

  Cell::Direction GetValidRandomDirection(Point& current);
  Cell::Direction OppositeDirection(Cell::Direction dir) const;

  RawMaze GetRawMaze() const;

  /* FIXME remove me later, debuging function */
  void PrintMaze();

protected:
  Point start_;
  Point finish_;

private:
  std::vector<std::vector<Cell::Ptr> > maze_;

  Cell::Ptr Get(Point pos) const;
};

} // namespace maze

#endif // MAZE
