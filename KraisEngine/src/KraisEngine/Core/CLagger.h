#pragma once

class CLagger
{
private:
	std::chrono::nanoseconds m_time;
	std::chrono::nanoseconds m_period;

	float m_timeF;
public:
	CLagger(std::chrono::nanoseconds period) : m_time(0), m_period(period) {
	}

	bool Update(std::chrono::nanoseconds dt) {
		m_time += dt;
		if (m_time > m_period) {
			m_timeF = 1.0f * m_time.count() / 1000000000.0f;
			m_time = std::chrono::nanoseconds(0);
			return true;
		}
		return false;
	}

	bool Reset() {
		m_time = std::chrono::nanoseconds(0);
	}

	float GetTimeFloat() { return m_timeF; }
};