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

#include <maze/Cell.h>
#include <gtest/gtest.h>

class MockCell : public testing::Test
{
public:
  MockCell()
  {}

  maze::Cell cell;
};

TEST_F(MockCell, TestCellEmpty)
{
  EXPECT_TRUE(cell.Empty());
}

TEST_F(MockCell, TestAddDirectionRight)
{
  cell.AddDirection(maze::Cell::Direction::RIGHT);

  EXPECT_FALSE(cell.Empty());
  EXPECT_TRUE(cell.RightOpen());
}

TEST_F(MockCell, TestAddDirectionLeft)
{
  cell.AddDirection(maze::Cell::Direction::LEFT);

  EXPECT_FALSE(cell.Empty());
  EXPECT_TRUE(cell.LeftOpen());
}

TEST_F(MockCell, TestAddDirectionDown)
{
  cell.AddDirection(maze::Cell::Direction::DOWN);

  EXPECT_FALSE(cell.Empty());
  EXPECT_TRUE(cell.DownOpen());
}

TEST_F(MockCell, TestAddDirectionUp)
{
  cell.AddDirection(maze::Cell::Direction::UP);

  EXPECT_FALSE(cell.Empty());
  EXPECT_TRUE(cell.UpOpen());
}

TEST_F(MockCell, TestRemoveDirectionRight)
{
  cell.AddDirection(maze::Cell::Direction::RIGHT);
  cell.RemoveDirection(maze::Cell::Direction::RIGHT);

  EXPECT_TRUE(cell.Empty());
  EXPECT_FALSE(cell.RightOpen());
}

TEST_F(MockCell, TestRemoveDirectionLeft)
{
  cell.AddDirection(maze::Cell::Direction::LEFT);
  cell.RemoveDirection(maze::Cell::Direction::LEFT);

  EXPECT_TRUE(cell.Empty());
  EXPECT_FALSE(cell.LeftOpen());
}

TEST_F(MockCell, TestRemoveDirectionDown)
{
  cell.AddDirection(maze::Cell::Direction::DOWN);
  cell.RemoveDirection(maze::Cell::Direction::DOWN);

  EXPECT_TRUE(cell.Empty());
  EXPECT_FALSE(cell.DownOpen());
}

TEST_F(MockCell, TestRemoveDirectionUp)
{
  cell.AddDirection(maze::Cell::Direction::UP);
  cell.RemoveDirection(maze::Cell::Direction::UP);

  EXPECT_TRUE(cell.Empty());
  EXPECT_FALSE(cell.UpOpen());
}

TEST_F(MockCell, TestSetParent)
{
  maze::Cell::Ptr tmp = std::make_shared<maze::Cell>();
  cell.SetParent(tmp);

  EXPECT_EQ(cell.GetParent(), tmp);
}

TEST_F(MockCell, TestNoParentIsNull)
{
  EXPECT_EQ(cell.GetParent(), nullptr);
}
