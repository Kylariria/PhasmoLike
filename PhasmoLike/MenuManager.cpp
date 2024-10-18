#include "MenuManager.h"
#include "ActionMap.h"
#include "Entity.h"
#include "UIButton.h"
#include "UIText.h"
#include "WindowManager.h"
#include "UIImage.h"

std::vector<sf::Drawable*> MenuManager::GetDrawables()
{
	vector<Drawable*> _drawables;
	int _currentZIndex = 0;
	bool _shouldContinue;

	do
	{
		_shouldContinue = false;
		for (Menu* _menu : GetAllValues())
		{
			int _zIndex = _menu->GetZIndex();
			if (_zIndex == _currentZIndex)
			{
				vector<Drawable*> _tempDrawables;

				if (!_menu->IsOpened()) continue;

				else
				{
					_tempDrawables = _menu->GetDrawables();
				}
				_drawables.insert(_drawables.end(), _tempDrawables.begin(), _tempDrawables.end());
			}
			else if (_zIndex == _currentZIndex + 1)
			{
				_shouldContinue = true;
			}
		}

		_currentZIndex++;
	} while (_shouldContinue);

	return _drawables;
}

float* MenuManager::GetIndex()
{
    return nullptr;
}

MenuManager::MenuManager()
{
	window = new CustomWindow("Menu","DefaultMenu", 1500, 900,Vector2i(50,50), false);
	index = new float(10.0f);
}

void MenuManager::ClickAction()
{
	for (Menu* _menu : GetAllValues())
	{
		if (_menu->IsOpened())
		{
			if (_menu->ClickAction())
			{
				return;
			}
		}
	}
}

void MenuManager::Update()
{
	for (Menu* _menu : GetAllValues())
	{
		if (_menu->IsOpened())
		{
			_menu->Update(window);
		}
	}
}

void MenuManager::InitMenu()
{
	new ActionMap("GamePaused",
		{ ActionData("Escape", [this]()
			{
				WindowManager::GetInstance().GetMainWindow()->SetHidden(true); //TODO fermer Inventory si ouvert/fermer item si ouvert/fermer mainWindow
				MenuManager::GetInstance().Get("GamePause")->Open();
			},
			{Event::KeyPressed, Keyboard::K}), //TODO change
		ActionData("Select", [this]()
			{
				MenuManager::GetInstance().ClickAction();
			},
			{Event::MouseButtonPressed, Mouse::Left}) });

	function<void()> _callbackContinue = [this]() {
		Get("GamePause")->Toggle();
		};
	//function<void()> _callbackOptions = [this]() { Get("GamePause")->Toggle(); OptionsMenu(); };
	//function<void()> _credit = [this]() { Get("GamePause")->Toggle(); ToggleCredits(); };
	function<void()> _callbackEchap = [this]() { Get("GamePause")->Toggle(); CloseMenu(); };

	float _x = static_cast<float>(window->getSize().x / 2);
	unsigned int _windowY = window->getSize().y;

	new Menu("GamePause", {
		new UIButton("ResumeButton", Vector2f(_x, static_cast<float>(_windowY / 5)),Color::Black, Color::White, "Resume", 50, "", PATH_TEXT_FONT, _callbackContinue),
		//new UIButton("OptionsButton", Vector2f(_x, static_cast<float>(_windowY / 2.7)), WHITE_COLOR, CYAN_COLOR, "Options", 50, FONT, SOUND_START, _callbackOptions),

		/*new UIButton("credit", Vector2f(static_cast<float>(window->getSize().x / 1.3), static_cast<float>(_windowY / 1.2)), Color(119,136,153), WHITE_COLOR, {
			new UIImage("credit", Vector2f(static_cast<float>(window->getSize().x / 1.3), static_cast<float>(_windowY / 1.2)), Vector2f(150.0f, 48.0f), CREDIT_BUTTON),
		}, SOUND_START, _credit, FloatRect(static_cast<float>(window->getSize().x / 1.3), static_cast<float>(_windowY / 1.2), 150.0f, 48.0f)),*/

		new UIButton("Exit", Vector2f(_x, static_cast<float>(_windowY / 1.2)),Color::Black, Color::White, "Exit Game", 50, "", PATH_TEXT_FONT, _callbackEchap),
		new UIImage("1", Vector2f(0.f,0.f), Vector2f((float)window->getSize().x, (float)_windowY), PATH_BACKGROUNDJOURNAL), }, 1);
}

void MenuManager::CloseMenu()
{
}

void MenuManager::GameOverMenu()
{
}

void MenuManager::Toggle()
{
}

void MenuManager::InitMenuPause()
{
}

void MenuManager::InitMenuClose()
{
}

void MenuManager::InitGameOver()
{
}

void MenuManager::WarningSeizure()
{
}
