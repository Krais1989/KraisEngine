#pragma once

/// <summary>
/// ����� ��� �������� �������� ����������
/// (��������, ������������ ��� �������� �������� ���������� � ������� ����������)
/// </summary>
class CThrottler
{
public:
	using Time = std::chrono::nanoseconds;
private:
	/// <summary>
	/// ������� ����� ���������
	/// </summary>
	Time m_time;
	/// <summary>
	/// ������ ���������
	/// </summary>
	Time m_period;
	/// <summary>
	/// ������� ����� ��������� � �������� � ��������� ������
	/// </summary>
	float m_timeF;
public:
	CThrottler(Time period) : m_time(0), m_timeF(0), m_period(period) {
	}

	Time GetPeriod() const { return m_period; }
	void SetPeriod(Time val) { m_period = val; }

	/// <summary>
	///  � �������� � ��������� ������
	/// </summary>
	float GetTimeFloat() const { return m_timeF; }

	bool Update(Time dt) {
		m_time += dt;
		if (m_time > m_period) {
			m_timeF = 1.0f * m_time.count() / 1000000000.0f;
			m_time = Time(0);
			return true;
		}
		return false;
	}

	bool Reset() {
		m_time = Time(0);
	}
};