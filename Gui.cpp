#include "stdafx.h"
#include "Gui.h"

std::map<std::string, sf::Texture> Panel::textures;

void Panel::loadTextures()
{
	textures["Panel"].loadFromFile("Images/GUI/Panel.png");
	textures["Intro"].loadFromFile("Images/GUI/Intro.png");
	textures["Standard_Standard"].loadFromFile("Images/GUI/Standard_Standard.png");
	textures["Standard_Inducted"].loadFromFile("Images/GUI/Standard_Inducted.png");
	textures["Standard_Pressed"].loadFromFile("Images/GUI/Standard_Pressed.png");
	textures["Checkbox_Unchecked"].loadFromFile("Images/GUI/Checkbox_Unchecked.png");
	textures["Checkbox_Checked"].loadFromFile("Images/GUI/Checkbox_Checked.png");
	textures["Button_Left"].loadFromFile("Images/GUI/Button_Left.png");
	textures["Button_Right"].loadFromFile("Images/GUI/Button_Right.png");
}

Panel::Panel(float x, float y, float w, float h, const char* textureName) : x(x), y(y), w(w), h(h)
{
	rect.setTexture(&textures[textureName]);
	if (!rect.getTexture()) std::cout << "!No_texture_" << textureName;
}

void Panel::prepareToDraw(sf::RenderWindow* window)
{
	rect.setPosition(window->mapPixelToCoords(sf::Vector2i(x, y)));
	rect.setSize(window->mapPixelToCoords(sf::Vector2i(x + w, y + h)) - window->mapPixelToCoords(sf::Vector2i(x, y)));
}

void Panel::draw(sf::RenderWindow* window)
{
	prepareToDraw(window);
	window->draw(rect);
}

//----------------------------
//LABEL-----------------------
//----------------------------

sf::Font Label::font;

void Label::loadFont(const char* name)
{
	if (!font.loadFromFile(name)) std::cout << "!No_font_" << name;
}

Label::Label(float x, float y, const char* textString, int charSize, sf::Vector2f origin) : x(x), y(y), charSize(charSize), origin(origin)
{
	text.setFont(font);
	if (textString)
		setString(textString);
}

void Label::setString(std::string textString)
{
	this->textString = textString;
	sf::String str(textString, std::locale(setlocale(LC_CTYPE, nullptr)));
	text.setString(str);
}

void Label::prepareToDraw(sf::RenderWindow* window)
{
	//charSize = 20;                     //”ƒ¿À»“‹  ŒÃÃ≈Õ“¿–»» œŒ«∆≈
	text.setCharacterSize(charSize);
	sf::FloatRect rect = text.getLocalBounds();
	//text.setOrigin(sf::Vector2f(rect.left + rect.width * origin.x, rect.top + rect.height * origin.y));
	//std::cout << text.getCharacterSize() << "\n";
	text.setCharacterSize((window->mapPixelToCoords(sf::Vector2i(x + rect.width / 2, y + charSize / 2)) - window->mapPixelToCoords(sf::Vector2i(x - rect.width / 2, y - charSize / 2))).y);
	//std::cout << text.getCharacterSize() << "\n";
	rect = text.getLocalBounds();
	text.setOrigin((sf::Vector2f)sf::Vector2i(rect.left + rect.width * origin.x, rect.top + rect.height * origin.y));
	text.setPosition(window->mapPixelToCoords(sf::Vector2i(x, y)));
}

void Label::draw(sf::RenderWindow* window)
{
	prepareToDraw(window);
	window->draw(text);
}

//----------------------------
//BUTTON----------------------
//----------------------------

std::map<std::string, Button> Button::buttonPrototypes;

void Button::setButtonPrototypes()
{
	buttonPrototypes["Standard"] = Button(0, 0, 200, 50, "Standard_Standard", "Standard_Inducted", "Standard_Pressed");
	buttonPrototypes["Checkbox_Unchecked"] = Button(0, 0, 25, 25, "Checkbox_Unchecked", "Checkbox_Unchecked", "Checkbox_Unchecked");
	buttonPrototypes["Checkbox_Checked"] = Button(0, 0, 25, 25, "Checkbox_Checked", "Checkbox_Checked", "Checkbox_Checked");
	buttonPrototypes["Button_Left"] = Button(0, 0, 25, 25, "Button_Left", "Button_Left", "Button_Left");
	buttonPrototypes["Button_Right"] = Button(0, 0, 25, 25, "Button_Right", "Button_Right", "Button_Right");
}

Button::Button(float x, float y, float w, float h, const char* standardTextureName, const char* inductedTextureName, const char* pressedTextureName, const char* textString, const char* command, int charSize) :
	panel(x, y, w, h, standardTextureName), label(x + w / 2, y + h / 2, textString, charSize, { 0.5,0.5 })
{
	btnState = BTN_STANDARD;
	standardTexture = &Panel::textures[standardTextureName];
	inductedTexture = &Panel::textures[inductedTextureName];
	pressedTexture = &Panel::textures[pressedTextureName];
	if (command) this->command = command;
}

Button::Button(float x, float y, const char* buttonPrototypeName, const char* textString, const char* command) :
	panel(buttonPrototypes[buttonPrototypeName].panel), label(buttonPrototypes[buttonPrototypeName].label)
{
	panel.x = x;
	panel.y = y;
	label.x = x + panel.w / 2;
	label.y = y + panel.h / 2;
	label.setString(textString);
	this->command = command;
	standardTexture = buttonPrototypes[buttonPrototypeName].standardTexture;
	inductedTexture = buttonPrototypes[buttonPrototypeName].inductedTexture;
	pressedTexture = buttonPrototypes[buttonPrototypeName].pressedTexture;
}

void Button::updateState(const sf::Vector2f& mousePos)
{
	if (sf::FloatRect(panel.x, panel.y, panel.w, panel.h).contains(mousePos))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			btnState = BTN_PRESSED;
		else
			btnState = btnState == BTN_PRESSED ? BTN_ACTIVE : BTN_INDUCTED;
	}
	else
		btnState = BTN_STANDARD;

	switch (btnState)
	{
	case BTN_STANDARD: panel.rect.setTexture(standardTexture); break;
	case BTN_INDUCTED: panel.rect.setTexture(inductedTexture); break;
	case BTN_PRESSED: panel.rect.setTexture(pressedTexture); break;
	case BTN_ACTIVE: panel.rect.setTexture(standardTexture); break;
	}
}

bool Button::isActive()
{
	return btnState == BTN_ACTIVE;
}

const std::string& Button::getCommand()
{
	return command;
}

void Button::draw(sf::RenderWindow* window)
{
	panel.draw(window);
	label.draw(window);
}

//----------------------------
//MENU------------------------
//----------------------------

const std::string Menu::getActiveButton()
{
	if (active)
		for (auto& i : buttons)
			if (i.isActive())
				return i.getCommand();
	return "";
}

void Menu::updateButtons(const sf::Vector2f& mousePos)
{
	if (active)
		for (auto& i : buttons)
			i.updateState(mousePos);
}

void Menu::draw(sf::RenderWindow* window)
{
	if (!active) return;
	for (auto& i : panels) i.draw(window);
	for (auto& i : labels) i.draw(window);
	for (auto& i : buttons) i.draw(window);
}

//----------------------------
//GUI-------------------------
//----------------------------

void GUI::setMenuActive(const char* name)
{
	for (auto& i : menu)
		i.second.active = false;
	menu[name].active = true;
}

const std::string GUI::getActiveButton()
{
	for (auto& i : menu)
		if (i.second.active)
			return i.second.getActiveButton();
	return "";
}

void GUI::emplace(const char* name, Panel&& panel)
{
	menu[name].panels.push_back(panel);
}

void GUI::emplace(const char* name, Label&& label)
{
	menu[name].labels.push_back(label);
}

void GUI::emplace(const char* name, Button&& button)
{
	menu[name].buttons.push_back(button);
}

void GUI::updateButtons(const sf::Vector2f& mousePos)
{
	for (auto& i : menu)
		i.second.updateButtons(mousePos);
}

void GUI::draw(sf::RenderWindow* window)
{
	for (auto& i : menu)
		i.second.draw(window);
}