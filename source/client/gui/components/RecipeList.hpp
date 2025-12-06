/********************************************************************
	Minecraft: Pocket Edition - Decompilation Project
	Copyright (C) 2023 iProgramInCpp
	
	The following code is licensed under the BSD 1 clause license.
	SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#pragma once

#include "ScrolledSelectionList.hpp"
class Recipe;

class RecipeList : public ScrolledSelectionList
{
public:
	RecipeList(Minecraft*, int, int, int, int, int);
	int getNumberOfItems() override;
	bool isSelectedItem(int i) override;
	void renderBackground(float f) override;
	void renderItem(int, int, int, int, Tesselator& t) override;
	void selectItem(int, bool) override;
	void renderHeader(int, int, Tesselator&) override {

	};
	void renderHoleBackground(float, float, int, int) override {

	};

	void render(int mouseX, int mouseY, float f) override;

public:
	int m_selectedIndex;
	std::vector<Recipe*> m_recipe;
};

