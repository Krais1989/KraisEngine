#include "CLayerStack.h"

namespace KE
{
	CLayerStack::~CLayerStack()
	{
		for (CLayer* it : m_Layers) {
			it->OnDetach();
			delete it;
		}
		m_Layers.clear();
	}

	void CLayerStack::PushLayer(CLayer* layer)
	{
		m_Layers.emplace(begin() + m_LastLayerIndex, layer);
		m_LastLayerIndex++;
		layer->OnAttach();
	}

	void CLayerStack::PopLayer(CLayer* layer)
	{
		auto find = std::find(begin(), begin() + m_LastLayerIndex, layer);
		if (find != begin() + m_LastLayerIndex) {
			layer->OnDetach();
			m_Layers.erase(find);
			m_LastLayerIndex--;
		}
	}

	void CLayerStack::PushOverlay(CLayer* layer)
	{
		m_Layers.emplace_back(layer);
		layer->OnAttach();
	}

	void CLayerStack::PopOverlay(CLayer* layer)
	{
		auto find = std::find(begin() + m_LastLayerIndex, end(), layer);
		if (find != end()) {
			layer->OnDetach();
			m_Layers.erase(find);
		}
	}
}
