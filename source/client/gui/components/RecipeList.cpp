/********************************************************************
	Minecraft: Pocket Edition - Decompilation Project
	Copyright (C) 2023 iProgramInCpp
	
	The following code is licensed under the BSD 1 clause license.
	SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#include "RecipeList.hpp"

#define C_ITEM_WIDTH 110

RecipeList::RecipeList(Minecraft* a, int b, int c, int d, int e, int f) :
    ScrolledSelectionList(a, b, c, d, e, f)
{
}

int RecipeList::getNumberOfItems()
{
    return 999; //int(m_recipe.size());
}

bool RecipeList::isSelectedItem(int i)
{
    return m_selectedIndex == i;
}

void RecipeList::renderBackground(float f)
{
}

void RecipeList::renderItem(int idx, int x, int y, int width, Tesselator& t)
{
 //   drawString(m_pMinecraft->m_pFont, std::string(m_recipe[idx].m_name.C_String()),    x, y + 2,  0xFFFFA0);
 //   drawString(m_pMinecraft->m_pFont, std::string(m_recipe[idx].m_address.ToString()), x, y + 16, 0xFFFFA0);

 drawString(m_pMinecraft->m_pFont, "Super awesome scroller item", x, y + 16, 0xFFFFA0);
}

void RecipeList::selectItem(int index, bool b)
{
    m_selectedIndex = index;
}


void RecipeList::render(int mouseX, int mouseY, float f) 
{
	renderBackground(0);

        

	int nItems = getNumberOfItems();
	Tesselator& t = Tesselator::instance;

    if (!(mouseX < field_18 || mouseX > field_18 + C_ITEM_WIDTH))
	    checkInput(mouseX, mouseY);

	field_30 = float(mouseY);
	field_38 *= 0.75f;
	capYPosition();

	glDisable(GL_LIGHTING);
	glDisable(GL_FOG);

	m_pMinecraft->m_pTextures->loadAndBindTexture("gui/spritesheet.png");
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	//renderScrollBackground();

	int itemX = field_18;
	int scrollY = int(field_C + 4 - float(int(field_34)));

	if (field_45)
		renderHeader(itemX, scrollY, t);

	// Note, X/Y are the lower left's X/Y coordinates, not the upper left's.
	int lowerY = Minecraft::height - int(field_10 / Gui::InvGuiScale);
	int upperY = Minecraft::height - int(field_C  / Gui::InvGuiScale);
	glScissor(0, 10/240.f*m_pMinecraft->height, Minecraft::width, Minecraft::height - (10/240.f*Minecraft::height)*2);
	glEnable(GL_SCISSOR_TEST);

	for (int i = 0; i < nItems; i++)
	{
		float itemY = float(field_48 + scrollY + i * m_itemHeight);
		float lowerY = itemY + m_itemHeight - 4;
		if (m_pMinecraft->height < itemY)
			continue;

		if (lowerY < 0)
			continue;

        m_pMinecraft->m_pTextures->loadAndBindTexture("gui/spritesheet.png");
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        int thick = 14;
		if (m_bRenderSelection && isSelectedItem(i))
		{
		//	glDisable(GL_TEXTURE_2D);
		//	t.begin();
		//	t.color(0x808080);
		//	t.vertexUV(field_18, lowerY + 2.0f, 0.0f, 0.0f, 1.0f);
		//	t.vertexUV(field_18, lowerY + 2.0f, 0.0f, 1.0f, 1.0f);
		//	t.vertexUV(field_18, itemY  - 2.0f, 0.0f, 1.0f, 0.0f);
		//	t.vertexUV(field_18, itemY  - 2.0f, 0.0f, 0.0f, 0.0f);
		//	t.draw();
		//	glEnable(GL_TEXTURE_2D);
          //  blit(field_18, itemY, 60, 64, field_18+C_ITEM_WIDTH, m_itemHeight, 10,  16); fullsz

            blit(field_18, itemY, 60, 64, field_18+C_ITEM_WIDTH, thick, 10,  16);
            blit(field_18, itemY+m_itemHeight-thick, 60, 64, field_18+C_ITEM_WIDTH, thick, 10,  16);
            blit(field_18, itemY+thick/2, 60, 68, field_18+C_ITEM_WIDTH, m_itemHeight-thick, 10,  8);
            //blit(field_18, itemY, 56, 64, field_18+C_ITEM_WIDTH, m_itemHeight, 16,  16);
		} else { 
            blit(field_18, itemY, 44, 64, field_18+C_ITEM_WIDTH, thick, 10,  16);
            blit(field_18, itemY+m_itemHeight-thick, 44, 64, field_18+C_ITEM_WIDTH, thick, 10,  16);
            blit(field_18, itemY+thick/2, 44, 68, field_18+C_ITEM_WIDTH, m_itemHeight-thick, 10,  8);
        }

		renderItem(i, itemX, int(itemY), int(m_itemHeight - 4.0f), t);
	}
	
	glDisable(GL_SCISSOR_TEST);
	glDisable(GL_DEPTH_TEST);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
	glEnable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
}

