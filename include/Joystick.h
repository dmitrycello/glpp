#pragma once
#include "glfw3pp.h"
namespace glfw {
/*GLFW gamepad axis enumerator*/
enum class GamepadAxis : int
{
	/*Gamepad left X axis*/
	GamepadAxisLeftX = GLFW_GAMEPAD_AXIS_LEFT_X,

	/*Gamepad left Y axis*/
	GamepadAxisLeftY = GLFW_GAMEPAD_AXIS_LEFT_Y,

	/*Gamepad right X axis*/
	GamepadAxisRightX = GLFW_GAMEPAD_AXIS_RIGHT_X,

	/*Gamepad right Y axis*/
	GamepadAxisRightY = GLFW_GAMEPAD_AXIS_RIGHT_Y,

	/*Gamepad left trigger axis*/
	GamepadAxisLeftTrigger = GLFW_GAMEPAD_AXIS_LEFT_TRIGGER,

	/*Gamepad right trigger axis*/
	GamepadAxisRightTrigger = GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER,

	/*Gamepad last axis*/
	GamepadAxisLast = GLFW_GAMEPAD_AXIS_LAST,
};

/*GLFW gamepad button enumerator*/
enum class GamepadButton : int
{
	/*Gamepad A button*/
	GamepadButtonA = GLFW_GAMEPAD_BUTTON_A,

	/*Gamepad B button*/
	GamepadButtonB = GLFW_GAMEPAD_BUTTON_B,

	/*Gamepad X button*/
	GamepadButtonX = GLFW_GAMEPAD_BUTTON_X,

	/*Gamepad Y button*/
	GamepadButtonY = GLFW_GAMEPAD_BUTTON_Y,

	/*Gamepad cross button*/
	GamepadButtonCross = GLFW_GAMEPAD_BUTTON_CROSS,

	/*Gamepad circle button*/
	GamepadButtonCircle = GLFW_GAMEPAD_BUTTON_CIRCLE,

	/*Gamepad square button*/
	GamepadButtonSquare = GLFW_GAMEPAD_BUTTON_SQUARE,

	/*Gamepad triangle button*/
	GamepadButtonTriangle = GLFW_GAMEPAD_BUTTON_TRIANGLE,

	/*Gamepad left bumper button*/
	GamepadButtonLeftBumper = GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,

	/*Gamepad right bumper button*/
	GamepadButtonRightBumper = GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,

	/*Gamepad back button*/
	GamepadButtonBack = GLFW_GAMEPAD_BUTTON_BACK,

	/*Gamepad start button*/
	GamepadButtonStart = GLFW_GAMEPAD_BUTTON_START,

	/*Gamepad guide button*/
	GamepadButtonGuide = GLFW_GAMEPAD_BUTTON_GUIDE,

	/*Gamepad left thumb button*/
	GamepadButtonLeftThumb = GLFW_GAMEPAD_BUTTON_LEFT_THUMB,

	/*Gamepad right thumb button*/
	GamepadButtonRightThumb = GLFW_GAMEPAD_BUTTON_RIGHT_THUMB,

	/*Gamepad d-pad up button*/
	GamepadButtonDpadUp = GLFW_GAMEPAD_BUTTON_DPAD_UP,

	/*Gamepad d-pad right button*/
	GamepadButtonDpadRight = GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,

	/*Gamepad d-pad down button*/
	GamepadButtonDpadDown = GLFW_GAMEPAD_BUTTON_DPAD_DOWN,

	/*Gamepad d-pad left button*/
	GamepadButtonDpadLeft = GLFW_GAMEPAD_BUTTON_DPAD_LEFT,

	/*Gamepad last button*/
	GamepadButtonLast = GLFW_GAMEPAD_BUTTON_LAST,
};

/*GLFW joystick hat enumerator*/
enum class JoystickHat : unsigned char
{
	/*No joystick hat pressed*/
	HatCentered = GLFW_HAT_CENTERED,

	/*Up joystick hat pressed*/
	HatUp = GLFW_HAT_UP,

	/*Right joystick hat pressed*/
	HatRight = GLFW_HAT_RIGHT,

	/*Down joystick hat pressed*/
	HatDown = GLFW_HAT_DOWN,

	/*Left joystick hat pressed*/
	HatLeft = GLFW_HAT_LEFT,

	/*Right and up joystick hats pressed*/
	HatRightUp = GLFW_HAT_RIGHT_UP,

	/*Right and down joystick hats pressed*/
	HatRightDown = GLFW_HAT_RIGHT_DOWN,

	/*Left and up joystick hats pressed*/
	HatLeftUp = GLFW_HAT_LEFT_UP,

	/*Left and down joystick hats pressed*/
	HatLeftDown = GLFW_HAT_LEFT_DOWN,
};

/*GLWF type of joystick connected callback routine
@param The UTF-8 encoded GUID of the joystick
@param The UTF-8 encoded name of the joystick
@param The UTF-8 encoded name of the gamepad, or NULL if the joystick does not have a mapping*/
typedef void (WINAPI JoystickConnectedCallback)(const char* guid, const char* name, const char* gamepad);

/*Sets the function for the joystick connected callback routine
@param GLWF type of joystick connected callback routine*/
void setJoystickConnectedCallback(JoystickConnectedCallback callback);

/*GLFW joystick object root class*/
class Joystick
{
private:
	static struct _SDATA {
		int m_iJcount;
		int m_pJoysticks[GLFW_JOYSTICK_LAST + 1];
		JoystickConnectedCallback* m_pConnected = nullptr;
		_SDATA();
		void getJoysticks();
	} s_Data;
	int m_iJid = -1;							// Joystick id
	int m_iAxes = 0;							// Axes count
	int m_iHats = 0;							// Hat count
	int m_iButtons = 0;							// Button count
	const char* m_pGuid = nullptr;				// Joystick GUID
	const char* m_pName = nullptr;				// Joystick name
	const float* m_pAxes = nullptr;				// Axe array
	const char* m_pGamepad = nullptr;			// Gamepad name
	const unsigned char* m_pHats = nullptr;		// Hat array
	const unsigned char* m_pButtons = nullptr;	// Button array
	GLFWgamepadstate m_Gamepad = { 0 };			// Gamepad state
	int _jid() const;
	static void _joystickCallback(int jid, int event);
	void _select(int jid);

protected:
	/*Joystick disconnected event handler*/
	virtual void onDisconnect() {}

public:
	/*(1) Constructs an empty joystick object*/
	Joystick() {}

	/*(2) Constructs joystick object with <selectJoystick>, 0u selects first joystick in the system*/
	Joystick(unsigned int jindex)
	{
		selectJoystick(jindex);
	}

	/*(3) Constructs joystick object with <selectJoystick>*/
	Joystick(_In_z_ const char* name)
	{
		selectJoystick(name);
	}

	/*Cleans up the valid joystick object*/
	~Joystick()
	{
		if (isJoystick())
		{
			deselectJoystick();
		}
	}

	/*Unconditionally deselects specified joystick*/
	void deselectJoystick();

	/*Returns the joystick axis count after <getJoystickAxes> call
	@return The number of axes, or 0 prior to mentionned calls*/
	int getAxisCount() const
	{
		return m_iAxes;
	}

	/*Returns the joystick button count after <getJoystickButtons> call
	@return The number of buttons, or 0 prior to mentionned calls*/
	int getButtonCount() const
	{
		return m_iButtons;
	}

	/*Gets specified gamepad axis state retrieved by <getGamepadState> call
	@param The gamepad axis
	@return The specified gamepad axis state value, must be between -1.0 and 1.0*/
	float getGamepadAxis(GamepadAxis axis) const
	{
		return m_Gamepad.axes[(int)axis];
	}

	/*Gets specified gamepad button state retrieved by <getGamepadState> call
	@param The gamepad button
	@return True if specified gamepad button is pressed, false otherwise*/
	bool getGamepadButton(GamepadButton button) const
	{
		return (bool)m_Gamepad.buttons[(int)button];
	}

	/*Returns the human-readable name of the gamepad from the gamepad mapping assigned to the specified joystick
	@return The UTF-8 encoded name of the gamepad, or NULL if the joystick does not have a mapping*/
	_Ret_maybenull_ const char* getGamepadName() const;

	/*Scans the gamepad states, and triggers the appropriate events if any changes occured since the last scan. The first scan is always skipped
	@return True if the gamepad state was loaded successfully, false otherwise*/
	bool getGamepadState()
	{
		return (bool)glfwGetGamepadState(_jid(), &m_Gamepad);
	}

	/*Returns the joystick hat count after <getJoystickHats> call
	@return The number of hats, or 0 prior to mentionned calls*/
	int getHatCount() const
	{
		return m_iHats;
	}

	/*Scans the axes states, and triggers the appropriate events if any changes occured since the last scan. The first scan is always skipped*/
	void getJoystickAxes()
	{
		m_pAxes = glfwGetJoystickAxes(_jid(), &m_iAxes);
	}

	/*Gets current joystick axis state retrieved by <getJoystickAxes> call
	@param The joystick axis index
	@return The joystick axis state value, must be between -1.0 and 1.0*/
	float getJoystickAxis(unsigned int index) const;

	/*Gets current joystick button state retrieved by <getJoystickButtons> call
	@param The joystick button index
	@return True if specified button is pressed, false otherwise*/
	bool getJoystickButton(unsigned int index) const;

	/*Scans the buttons states, and triggers the appropriate events if any changes occured since the last scan. The first scan is always skipped*/
	void getJoystickButtons()
	{
		m_pButtons = glfwGetJoystickButtons(_jid(), &m_iButtons);
	}

	/*Retrieves number of joysticks available in the system
	@return The number of available joysticks*/
	static int getJoystickCount()
	{
		return s_Data.m_iJcount;
	}

	/*Returns the SDL compatible GUID, as a UTF-8 encoded hexadecimal string, of the specified joystick
	@return The UTF-8 encoded GUID of the joystick*/
	_Ret_z_ const char* getJoystickGUID() const;

	/*Gets current joystick hat state retrieved by <getJoystickHats> call
	@param The joystick hat index
	@return The joystick hat state value*/
	JoystickHat getJoystickHat(unsigned int index) const;

	/*Scans the hats states, and triggers the appropriate events if any changes occured since the last scan. The first scan is always skipped*/
	void getJoystickHats()
	{
		m_pHats = glfwGetJoystickHats(_jid(), &m_iHats);
	}

	/*This function returns the name, encoded as UTF-8, of the specified joystick
	@return The UTF-8 encoded name of the joystick*/
	_Ret_z_ const char* getJoystickName() const;

	/*Checks if valid joystick object, must be called prior to any other calls. Validate the object (<3.3)
	@return True if valid joystick object, false otherwise*/
	bool isJoystick() const
	{
		return m_iJid > -1;
	}

	/*Returns whether the specified joystick is both present and has a gamepad mapping
	@return True if a joystick is both present and has a gamepad mapping, false otherwise*/
	bool joystickIsGamepad()
	{
		return (bool)glfwJoystickIsGamepad(_jid());
	}

	/*(1) Loads the binary resource and updates the internal list with any gamepad mappings it finds
	@param The binary resource id
	@return True if successful, false otherwise*/
	static bool loadGamepadMappings(int rcid);

	/*(2) Loads the file and updates the internal list with any gamepad mappings it finds
	@param [in] The path to the file
	@return True if successful, false otherwise*/
	static bool loadGamepadMappings(_In_z_ const char* file);

	/*(1) Selects joystick by its index. The index 0u selects first joystick in the system
	@param [in] The joystick index, default 0u*/
	void selectJoystick(unsigned int jindex = 0u);

	/*(2) Selects joystick by its name in the system
	@param [in] The joystick name*/
	void selectJoystick(_In_z_ const char* jname);

	/*Selects joystick by its GUID
	@param [in] The joystick GUID*/
	void selectJoystickGUID(_In_z_ const char* jname);

	/*Sets the function for the joystick connected callback routine
	@param GLWF type of joystick connected callback routine*/
	static void setJoystickConnectedCallback(JoystickConnectedCallback callback)
	{
		s_Data.m_pConnected = callback;
	}

	/*Parses the specified ASCII encoded string and updates the internal list with any gamepad mappings it finds
	@param [in]	The string containing the gamepad mappings
	@return True if successful, false otherwise*/
	static bool updateGamepadMappings(_In_z_ const char* string)
	{
		return (bool)glfwUpdateGamepadMappings(string);
	}
}; // class Joystick

inline void setJoystickConnectedCallback(JoystickConnectedCallback callback)
{
	Joystick::setJoystickConnectedCallback(callback);
}

#ifndef _DEBUG
inline int Joystick::_jid() const
{
	return m_iJid;
}

_Ret_maybenull_ inline const char* Joystick::getGamepadName() const
{
	return m_pGamepad;
}

inline float Joystick::getJoystickAxis(unsigned int index) const
{
	return m_pAxes[index];
}

inline bool Joystick::getJoystickButton(unsigned int index) const
{
	return m_pButtons[index] == GLFW_PRESS;
}

_Ret_z_ inline const char* Joystick::getJoystickGUID() const
{
	return m_pGuid;
}

inline JoystickHat Joystick::getJoystickHat(unsigned int index) const
{
	return (JoystickHat)m_pHats[index];
}

_Ret_z_ inline const char* Joystick::getJoystickName() const
{
	return m_pName;
}

inline void Joystick::selectJoystick(unsigned int jindex)
{
	_select(s_Data.m_pJoysticks[jindex]);
}
#endif // #ifndef _DEBUG
} // namespace glfw
