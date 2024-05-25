#pragma once
#include "Event.h"
#include "Hazel/Core/KeyCodes.h"

namespace Hazel {
	class  KeyEvent: public Event {
	public:
		inline KeyCode GetKeyCode() {
			return m_KeyCode;
		}

		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryKeyboard | EventCategory::EventCategoryInput);

	protected:
		KeyEvent(KeyCode keyCode) :m_KeyCode(keyCode) {}
		KeyCode m_KeyCode;
	};


	class  KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(KeyCode keyCode, int repeatCount) :KeyEvent(keyCode), m_RepeatCount(repeatCount) {}
		EVENT_CLASS_TYPE(KeyPressed)
		inline int GetRepeatCount() { return m_RepeatCount; }
		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

	private:
		int m_RepeatCount;

	};
	
	class  KeyReleasedEvent : public KeyEvent{
	public:
		KeyReleasedEvent(KeyCode keyCode, int repeatCount) :KeyEvent(keyCode){}
		EVENT_CLASS_TYPE(KeyReleased)
		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}


	};

	class  KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(KeyCode keyCode) :KeyEvent(keyCode) {}
		EVENT_CLASS_TYPE(KeyTyped)
			std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}


	};



}