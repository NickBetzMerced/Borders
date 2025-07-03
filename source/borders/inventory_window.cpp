#ifndef INVENTORY_WINDOW_CPP
#define INVENTORY_WINDOW_CPP

#include "inventory_window.h"
#include "item.h"
#include "player.h"

bool InventoryWindow::exists = false;

InventoryWindow::InventoryWindow() : Window(Window::TYPES::INVENTORY) {
	identity = "Inventory Window";
	page = 0;

	std::function<void()> b_update;
	b_update = update;
	update = [this, b_update]() {
		text = "ITEMS:\n";
		for (unsigned int i = 0; i < Player::player_ptr->inventory.size(); i++) {
			Item* current_item = &(Player::player_ptr->inventory[i]);
			text += current_item->getName() + std::format(": {:.1f} kg", current_item->getMass()) + "\n";
		}
	};

	std::function<void()> b_drawGUI;
	b_drawGUI = drawGUI;
	drawGUI = [this, b_drawGUI]() {
		b_drawGUI();
		DrawTextEx(engine::body_font, text.c_str(), Vector2(x + 20, y + 100), engine::m_font, engine::spacing, WHITE);
	};
}

InventoryWindow::~InventoryWindow() {
	exists = false;
}

InventoryWindow* InventoryWindow::makeInventoryWindow() {
	std::unique_ptr<InventoryWindow> window = std::make_unique<InventoryWindow>();
	InventoryWindow* window_ptr = window.get();
	engine::GameObject::objects.push_back(std::move(window));
	exists = true;
	return window_ptr;
}

#endif