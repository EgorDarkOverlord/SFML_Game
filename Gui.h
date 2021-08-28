#pragma once
enum buttonState { BTN_STANDARD, BTN_INDUCTED, BTN_PRESSED, BTN_ACTIVE };

class Button;

class Panel
{
private:
	static std::map<std::string, sf::Texture> textures;
	sf::RectangleShape rect;
public:
	float x, y, w, h;
	static void loadTextures();
	Panel() {}
	Panel(float x, float y, float w, float h, const char* textureName = NULL);
	void prepareToDraw(sf::RenderWindow* window);
	void draw(sf::RenderWindow* window);
	friend class Button;
};

class Label
{
private:
	static sf::Font font;
	std::string textString;
	sf::Text text;
public:
	float x, y;
	int charSize;
	sf::Vector2f origin;
	static void loadFont(const char* name);
	Label() {}
	Label(float x, float y, const char* textString = NULL, int charSize = 20, sf::Vector2f origin = { 0,0 });
	void setString(std::string textString);
	void prepareToDraw(sf::RenderWindow* window);
	void draw(sf::RenderWindow* window);
};

class Button
{
private:
	static std::map<std::string, Button> buttonPrototypes;
	sf::Texture* standardTexture, * inductedTexture, * pressedTexture;
	buttonState btnState;
	Panel panel;
	Label label;
	std::string command;
public:
	static void setButtonPrototypes();
	Button() {}
	Button(float x, float y, float w, float h, const char* standardTextureName, const char* inductedTextureName, const char* pressedTextureName, const char* textString = NULL, const char* command = NULL, int charSize = 20);
	Button(float x, float y, const char* buttonPrototypeName, const char* textString = NULL, const char* command = NULL);
	void updateState(const sf::Vector2f& mousePos);
	bool isActive();
	const std::string& getCommand();
	void draw(sf::RenderWindow* window);
};

class Menu
{
public:
	bool active = false;
	std::vector<Panel> panels;
	std::vector<Label> labels;
	std::vector<Button> buttons;
	const std::string getActiveButton();
	void updateButtons(const sf::Vector2f& mousePos);
	void draw(sf::RenderWindow* window);
};

class GUI
{
private:
	std::map<std::string, Menu> menu;
public:
	void setMenuActive(const char* name);
	const std::string getActiveButton();
	void emplace(const char* name, Panel&& panel);
	void emplace(const char* name, Label&& label);
	void emplace(const char* name, Button&& button);
	void updateButtons(const sf::Vector2f& mousePos);
	void draw(sf::RenderWindow* window);
};
