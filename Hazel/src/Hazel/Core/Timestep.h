#pragma once
namespace Hazel {
	class Timestep {
	public:
		Timestep(float time) :m_Time(time) {

		}

		operator float() const {
			return m_Time;
		}

		inline float GetSeconds()const { return m_Time; }
		inline float GetMileSeconds() const { return m_Time * 1000; }
	private:
		float m_Time;
	};
}