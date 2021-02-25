#pragma once

#include <KraisEngine/Core/Core.h>

/// <summary>
///  ласс дл€ фиксации периодов обновлени€
/// (Ќапример, используетс€ дл€ фиксации периодов обновлени€ и рендера приложени€)
/// </summary>
class KE_API CThrottler
{
public:
	using Time = std::chrono::nanoseconds;
private:
	/// <summary>
	/// “екущее врем€ тротлинга
	/// </summary>
	Time m_time;
	/// <summary>
	/// ѕериод тротлинга
	/// </summary>
	Time m_period;
	/// <summary>
	/// “екущее врем€ тротлинга в секундах с плавающей точкой
	/// </summary>
	float m_timeF;
public:
	CThrottler(Time period) : m_time(0), m_timeF(0), m_period(period) {
	}

	Time GetPeriod() const { return m_period; }
	void SetPeriod(Time val) { m_period = val; }

	/// <summary>
	/// “екущее врем€ тротлинга в секундах
	/// </summary>
	float GetThrottle() const { return m_timeF; }

	/// <summary>
	/// ƒобавл€ет к m_time продолжительность dt
	/// </summary>
	/// <param name="dt">прошедший промежуток времени</param>
	/// <returns>true - если m_time перешел промежуток m_period, иначе - false</returns>
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