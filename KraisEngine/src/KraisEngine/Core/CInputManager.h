#pragma once

#include <ke_pch.h>
#include <KraisEngine.h>

namespace KE {
	/// <summary>
	/// Причина создания - хранение промежуточных состояний ввода
	/// </summary>
	class CInputManager
	{
	private:

		std::unordered_map<KeyCode, int> m_KeyboardKeys;
		std::unordered_map<MouseCode, int> m_MouseKeys;

		float m_LastMX = 0.0f;
		float m_LastMY = 0.0f;

	public:

		void EnsureKeyboardKey(KeyCode key, int defValue = -1) {
			if (m_KeyboardKeys.find(key) != m_KeyboardKeys.end())
				return;
			m_KeyboardKeys[key] = defValue;
		}

		void Initialize() { return; }

		bool IsKeyPressed(KeyCode key) {}
		bool IsKeyReleased(KeyCode key) {}
		bool IsKeyRepeated(KeyCode key) {}

		int GetKeyState(KeyCode key)
		{
			EnsureKeyboardKey(key);
			return m_KeyboardKeys[key];
		}


		void UpdateKeyboardEventcallback(KeyCode key, int action) { 
			EnsureKeyboardKey(key);

		}

		void UpdateMouseCursor(float mx, float my) {

		}

		void UpdateMouseButtons(MouseCode btn, int action) {
		}

		void Update() {

		}

	};
}


