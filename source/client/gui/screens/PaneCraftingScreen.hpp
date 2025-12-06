/********************************************************************
	Minecraft: Pocket Edition - Decompilation Project
	Copyright (C) 2023 iProgramInCpp
	
	The following code is licensed under the BSD 1 clause license.
	SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#pragma once

#include "../Screen.hpp"
//#include "../components/ImageButton.hpp"
#include "../components/RecipeList.hpp"


class PaneCraftingScreen : public Screen
{
public:
	PaneCraftingScreen();
	~PaneCraftingScreen();
	virtual void init() override;
	virtual void tick() override;
	virtual void render(int a, int b, float c) override;
	virtual void buttonClicked(Button*) override;
	
	void updateServerVisibilityText();

private:
	//int field_3C;
	int field_40;
	Button m_btnBack;
	Button m_btnCategory1;
	Button m_btnCategory2;
	Button m_btnCategory3;
	Button m_btnCategory4;
	Button m_btnCraft;
	RecipeList* m_pRecipeList;
};

