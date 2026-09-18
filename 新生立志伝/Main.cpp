# include <Siv3D.hpp>
# include "Game.hpp"

void Main()
{
	s3d::Window::Resize(800, 600);
	s3d::Window::SetTitle(U"戦国行脚");

	Game game;

	while (s3d::System::Update())
	{
		game.update();
		game.draw();
	}
}
