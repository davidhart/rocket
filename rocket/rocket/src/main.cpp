#include "gameview.h"

int main(char** argv, int argc)
{
	GameView* view = GameView::Create("test application");



	GameView::Release(view);

	return 0;
}
