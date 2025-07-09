#ifndef INVENTORY_WINDOW_CPP
#define INVENTORY_WINDOW_CPP

#include "inventory_window.h"
#include "item.h"
#include "player.h"

bool InventoryWindow::exists = false;

InventoryWindow::InventoryWindow() : Window(Window::TYPES::INVENTORY) {
	identity = "Inventory Window";
	title = "Inventory Window";
	page = 0;

	std::function<void()> b_update;
	b_update = update;
	update = [this, b_update]() {
		total_mass = 0;
		total_volume = 0;
		text = "ITEMS:\n";
		for (unsigned int i = 0; i < Player::player_ptr->inventory.size(); i++) {
			Item* current_item = &(Player::player_ptr->inventory[i]);
			text += current_item->getName() + std::format(": {:.1f} kg", current_item->getMass()) + ", VOLUME: ";
			if (current_item->getVolume() < 0.05) {
				text += std::format("{:.1f} LITERS", current_item->getVolume() * 1000);
			}
			else {
				text += std::format("{:.1f} CUBIC METERS", current_item->getVolume());
			}
			text += "\n";
			total_mass += current_item->getMass();
			total_volume += current_item->getVolume();
		}
		text += std::format("TOTAL MASS: {:.1f} kg, TOTAL VOLUME: {:.1f} CUBIC METERS", total_mass, total_volume);
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