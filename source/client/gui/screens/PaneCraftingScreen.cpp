/********************************************************************
	Minecraft: Pocket Edition - Decompilation Project
	Copyright (C) 2023 iProgramInCpp
	
	The following code is licensed under the BSD 1 clause license.
	SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#include "PaneCraftingScreen.hpp"
#include "OptionsScreen.hpp"
#include "IngameBlockSelectionScreen.hpp"
#include "server/ServerSideNetworkHandler.hpp"
#include "client/app/Minecraft.hpp"


PaneCraftingScreen::PaneCraftingScreen() :
	//field_3C(0),
	field_40(0),	
	m_btnBack(0, "X"),
	m_btnCategory1(6, "Blocks"),
	m_btnCategory2(7, "Tools"),
	m_btnCategory3(8, "Armor"),
	m_btnCategory4(9, "Decor"),
	m_btnCraft(50, "CraftButton")
{

}

PaneCraftingScreen::~PaneCraftingScreen() {
	SAFE_DELETE(m_pRecipeList);

}

void PaneCraftingScreen::init()
{
	bool bAddVisibleButton = m_pMinecraft->m_pRakNetInstance && m_pMinecraft->m_pRakNetInstance->m_bIsHost;
	
	int nButtons = 2;

	int currY = 48, inc = 32;

	bool cramped = m_height < currY + inc * nButtons + 10; // also add some padding
	if (cramped)
		inc = 25;

	m_btnBack.m_width = m_btnBack.m_height = 19;

	m_btnBack.m_yPos = 2;
	m_btnBack.m_xPos = m_width-21;


	currY += inc;

	// add the buttons to the screen:
	m_buttons.push_back(&m_btnBack);


	int btnsWidth = (54.f / 240) * m_height, btnsSpacing = (2.f / 240) * m_height;
	m_btnCategory1.m_yPos = 9.f / 240 * m_height;
	m_btnCategory1.m_bHovered = true;


	m_btnCategory1.m_xPos = 10.f / 240 * m_height;
	m_btnCategory2.m_xPos = 10.f / 240 * m_height;
	m_btnCategory3.m_xPos = 10.f / 240 * m_height;
	m_btnCategory4.m_xPos = 10.f / 240 * m_height;

	m_btnCategory1.m_width = m_btnCategory1.m_height = btnsWidth;
	m_btnCategory2.m_width = m_btnCategory2.m_height = btnsWidth;
	m_btnCategory3.m_width = m_btnCategory3.m_height = btnsWidth;
	m_btnCategory4.m_width = m_btnCategory4.m_height = btnsWidth;

	m_btnCategory2.m_yPos = m_btnCategory1.m_yPos + m_btnCategory1.m_height + btnsSpacing;
	m_btnCategory3.m_yPos = m_btnCategory2.m_yPos + m_btnCategory1.m_height + btnsSpacing;
	m_btnCategory4.m_yPos = m_btnCategory3.m_yPos + m_btnCategory1.m_height + btnsSpacing;

	int C_ITEM_WIDTH = m_btnCategory1.m_xPos*2+btnsWidth + Minecraft::width * Gui::InvGuiScale - 0.75f*Minecraft::height* Gui::InvGuiScale;


	m_btnCraft.m_width = Minecraft::width * Gui::InvGuiScale - C_ITEM_WIDTH - 12;
	m_btnCraft.m_height = btnsWidth*1.25f;
	m_btnCraft.m_xPos = C_ITEM_WIDTH + 5;
	m_btnCraft.m_yPos = 21;

	// order is very important here, do not rearrange
	m_buttons.push_back(&m_btnCategory1);
	m_buttons.push_back(&m_btnCategory2);
	m_buttons.push_back(&m_btnCategory3);
	m_buttons.push_back(&m_btnCategory4);

	m_buttons.push_back(&m_btnCraft);
	
	for (int i = 0; i < int(m_buttons.size()); i++)
		m_buttonTabList.push_back(m_buttons[i]);

	m_pRecipeList = new RecipeList(m_pMinecraft, m_btnCategory1.m_xPos*1.5+btnsWidth, m_height, 24, m_height - 30, 24);//();

}

void PaneCraftingScreen::updateServerVisibilityText()
{
}

void PaneCraftingScreen::tick()
{
	field_40++;
}

void PaneCraftingScreen::render(int a, int b, float c)
{

	Textures* pTexs = m_pMinecraft->m_pTextures;

	pTexs->loadAndBindTexture("gui/spritesheet.png");

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    
		int texSize = 12;
		
        blit(0, 0, 8, 8, m_width, m_height, 24-8,  24-8);

        blit(0, 0, 15, 0, m_width, texSize, 1,16);
        blit(0, m_height-texSize, 15,16, m_width, texSize, 1,16);
        blit(0, 0, 0, 8, texSize, m_height, 16,  16);
        blit(m_width-texSize, 0, 16, 8, texSize, m_height, 16,  16);


        blit(0, 0, 0, 0, texSize, texSize, 16,16);
        blit(m_width-texSize, 0, 16, 0, texSize, texSize, 16,  16);


        blit(0, m_height-texSize, 0, 16, texSize, texSize, 16,  16);
        blit(m_width-texSize, m_height-texSize, 16, 16, texSize, texSize, 16,  16);

	drawString(*m_pMinecraft->m_pFont, "I18N Item description goes here", m_width - 300, 300, 0xffffff);

		



	m_pRecipeList->render(a,b,c);


	Screen::render(a, b, c);
}

void PaneCraftingScreen::buttonClicked(Button* pButton)
{
	if (pButton->m_buttonId == m_btnBack.m_buttonId)
		m_pMinecraft->setScreen(new IngameBlockSelectionScreen);

	for (int i = 1; i < 5; i++) {
		m_buttons[i]->m_bHovered = false;
		if (pButton->m_buttonId == m_buttons[i]->m_buttonId) {
			m_buttons[i]->m_bHovered = true;
		}
	}
}
