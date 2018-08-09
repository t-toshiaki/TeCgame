#include "UseOperator.h"
#include"Action.h"
#include"GameSystem.h"

Action::Action() :
	map(),
	player(map.Pworld),
	camera(player.pos),
	time_speed(1.0),
	ui(){

}

void Action::init() {
}

//void Action::updateFadeIn() {
//
//}

void Action::update() {
	if (GameSystem::get().openMenu) {
		GameSystem::get().updateMenu();
	}
	else {
		UseOperator::get().checkUsing(player.pos);

		player.update(UseOperator::get().useEnemies, UseOperator::get().useBlocks, time_speed);
		map.update(time_speed);
		UseOperator::get().update(player, time_speed);
		ui.update(player, time_speed);

		camera.update(player.pos);
	}

	if (GameSystem::get().toTitle) {
		GameSystem::get().toTitle = false;
		//player.init();
		map.init();
		UseOperator::get().init();
		changeScene(L"Title");
	}
}

void Action::draw() const {

	{
		//座標変換
		const Transformer2D transformer(Mat3x2::Translate(-camera.pos + Window::Center()).scale(100.0 * camera.scale, { 640, 360 }), true);

		if (GameSystem::get().debug) {
			Println(L"Action");
			Print(L"time_speed");
			Println(time_speed);
			Print(L"CameraPos:");
			Println(camera.pos);
		}

		map.draw(camera.pos);
		UseOperator::get().draw();
		//落下用
		RectF(Vec2(player.pos.x - 15, 5), Vec2(30, 100)).draw(Palette::Black);
		player.draw();

	}
	ui.draw();
	if (GameSystem::get().openMenu) {
		GameSystem::get().drawMenu();
	}
}
