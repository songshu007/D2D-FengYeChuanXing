#include "InputKey.h"

shu::InputKey* shu::InputKey::ptr = nullptr;

shu::InputKey::InputKey()
{
	ptr = this;
}

shu::InputKey::~InputKey()
{
}

void shu::InputKey::UpdataKeyStatus(uint32_t key, bool status)
{
	ptr->m_KeyNewState[key] = status;
}

void shu::InputKey::Updata()
{
	// ¸üÐÂ°´¼ü×´Ì¬
	for (auto i = 0; i < 256; i++)
	{
		if (ptr->m_KeyNewState[i] != ptr->m_KeyOldState[i])
		{
			if (ptr->m_KeyNewState[i] == true)
			{
				ptr->m_KeyboardState[i].isHold = true;
				ptr->m_KeyboardState[i].isPress = true;
			}
			else
			{
				ptr->m_KeyboardState[i].isHold = false;
				ptr->m_KeyboardState[i].isRelease = true;
			}
			ptr->m_KeyOldState[i] = ptr->m_KeyNewState[i];
		}
		else
		{
			if (ptr->m_KeyboardState[i].isPress == true) ptr->m_KeyboardState[i].isPress = false;
			if (ptr->m_KeyboardState[i].isRelease == true) ptr->m_KeyboardState[i].isRelease = false;
		}
	}
}

shu::KeyStatus& shu::InputKey::GetKeyStatus(Key key)
{
	return ptr->m_KeyboardState[(uint32_t)key];
}
