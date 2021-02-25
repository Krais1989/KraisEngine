#pragma once

#include "CLayer.h"

namespace KE {

	/// <summary>
	/// Стек слоёв для обхода
	/// Overlay всегда находятся после обычных слоёв, даже если слои добавлены после
	/// </summary>
	class CLayerStack
	{
	public:

		CLayerStack() = default;
		~CLayerStack();

		void PushLayer(CLayer* layer);
		void PopLayer(CLayer* layer);

		void PushOverlay(CLayer* layer);
		void PopOverlay(CLayer* layer);

		std::vector<CLayer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<CLayer*>::iterator end() { return m_Layers.end(); }
		std::vector<CLayer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<CLayer*>::reverse_iterator rend() { return m_Layers.rend(); }

		std::vector<CLayer*>::const_iterator cbegin() const { return m_Layers.cbegin(); }
		std::vector<CLayer*>::const_iterator cend() const { return m_Layers.cend(); }
		std::vector<CLayer*>::const_reverse_iterator crbegin() const { return m_Layers.crbegin(); }
		std::vector<CLayer*>::const_reverse_iterator crend() const { return m_Layers.crend(); }

	protected:

		std::vector<CLayer*> m_Layers;
		unsigned int m_LastLayerIndex = 0; // Индекс последнего слоя
	};
}
