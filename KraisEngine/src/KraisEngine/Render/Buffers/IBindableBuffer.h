#pragma once

namespace KE
{
	class IBindableBuffer {
	protected:
		using id_t = unsigned int;
		bool m_IsInitialized = false;
		id_t m_ID = 0;
	public:
		virtual void Bind() = 0;
		virtual void Init() = 0;
		const id_t& GetID() const { return m_ID; }
	};


}