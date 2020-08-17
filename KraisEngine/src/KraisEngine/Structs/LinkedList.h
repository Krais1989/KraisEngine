#pragma once
template <typename T>
class LinkedList
{
	template <typename T>
	class Element;

	using Data = T;
	using Elem = Element<T>;

	template <typename T>
	class Element
	{
	private:
		Data* m_data;
		Elem* m_next;
	public:
		Element(Data* data) : m_data(data), m_next(nullptr) {}
		virtual ~Element() {
			m_data = nullptr;
			m_next = nullptr;
		}

		Data& GetData() const {
			return *m_data;
		}
		void SetNext(Elem* next) { m_next = (Elem*)next; }
		Elem* GetNext() const { return m_next; }
	};

	Elem* m_first;
	Elem* m_last;

	int m_size;

public:
	LinkedList() : m_first(nullptr), m_last(nullptr), m_size(0) {}

	int GetSize() const { return m_size; }

	virtual ~LinkedList() {
		Clear();
	}

	void Clear() {
		Elem* cur = m_first;
		Elem* nxt = nullptr;

		while (cur != nullptr) {
			nxt = cur->GetNext();
			delete cur;
			cur = nxt;
		}

		m_first = nullptr;
		m_last = nullptr;

		m_size = 0;
	}

	void Push(T* data) {
		auto* elem = new Elem(data);
		if (m_first == nullptr) m_first = elem;

		if (m_last != nullptr)
			m_last->SetNext(elem);
		m_last = elem;

		m_size++;
	}

	Data& Push(Data&& data) {
		Data* ndata = new Data();
		memcpy(ndata, (const void*)&data, sizeof(Data));
		Push(ndata);
		return *ndata;
	}

	bool Remove(Data& data) {
		Elem* prev = nullptr;
		Elem* del = nullptr;
		Elem* next = nullptr;

		if (!Find(data, prev, del, next))
			return false;

		if (prev == nullptr)
			m_first = next;
		else
			prev->SetNext(next);

		if (m_last == del)
			m_last = prev;

		delete del;
		m_size--;
	}

	/// <summary>
	/// Поиск elem
	/// </summary>
	bool Find(Data& data, Elem*& out_prev, Elem*& out_cur, Elem*& out_next) const {
		Elem* prev = nullptr;
		Elem* cur = m_first;

		/*for (Elem* c = m_first; c != nullptr || &c->GetData() != &data; c = c->GetNext()) { }*/

		while (cur != nullptr && &(cur->GetData()) != &data) {
			prev = cur;
			cur = prev->GetNext();
		}

		out_prev = prev;
		out_cur = cur;
		out_next = out_cur != nullptr ? out_cur->GetNext() : nullptr;
		return out_cur != nullptr;
	}

	bool Find(Data& data) const {
		Elem* cur;
		Elem* prev;
		Elem* next;
		return Find(data, prev, cur, next);
	}


	Data& GetFirst() const { return m_first->GetData(); }
	Data& GetLast() const { return m_last->GetData(); }
};

