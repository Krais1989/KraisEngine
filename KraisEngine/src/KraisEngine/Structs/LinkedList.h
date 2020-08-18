#pragma once
template <typename T>
class LinkedList
{
	template <typename T>
	class Element;

	using Data = T;						// хранимый тип данных
	using elem = Element<T>;			// елемент хранящий данные
	using wp_elem = std::weak_ptr<T>;

	using sp_data = std::shared_ptr<T>; // расшаренный указатель на данные
	using wp_data = std::weak_ptr<T>;	// слабый указатель на данные
	using cp_cdata = const T* const;	// константный указатель на константный объект

	/// <summary>
	/// Класс элемента для хранения ссылки на данные и на следующий элемент
	/// </summary>
	/// <typeparam name="T">тип данных</typeparam>
	template <typename T>
	class Element
	{
	private:
		sp_data m_data;
		elem* m_next;
	public:
		Element(sp_data& data) : m_data(data), m_next(nullptr) {}

		virtual ~Element() {
			KE_INFO("Element destroyed");
		}

		/// <summary>
		/// Умный указатель на данные
		/// </summary>
		sp_data& GetData() {
			return m_data;
		}

		/// <summary>
		/// Константный указатель на данные
		/// </summary>
		cp_cdata GetDataPtr() const {
			return (cp_cdata) & *m_data;
		}

		void SetNext(elem* next) { m_next = next; }
		elem* GetNext() { return m_next; }
	};

	elem* m_first;
	elem* m_last;
	int m_size;

public:

	LinkedList() : m_first(nullptr), m_last(nullptr), m_size(0) {}

	int GetSize() const { return m_size; }

	virtual ~LinkedList() {
		Clear();
	}

	void Clear() {
		elem* cur = m_first;
		elem* nxt = nullptr;

		while (cur != nullptr) {
			nxt = cur->GetNext();
			delete cur;
			cur = nxt;
		}

		m_first = nullptr;
		m_last = nullptr;
		m_size = 0;
	}

	sp_data& operator[] (int index) const { return this->GetByIndex(index); }

	sp_data& GetByIndex(int index) const {
		if (index < 0 || index >= m_size)
			throw std::out_of_range("wrong index");

		elem* cur = m_first;
		for (int i = 0; i < index; i++)
		{
			cur = cur->GetNext();
		}
		return cur->GetData();
	}

	sp_data& Push(sp_data& spdata) {
		auto* el = new elem(spdata);
		if (m_first == nullptr) m_first = el;
		if (m_last != nullptr)
			m_last->SetNext(el);
		m_last = el;
		m_size++;
		return el->GetData();
	}

	/// <summary>
	/// Пуш r-value
	/// </summary>
	sp_data& Push(Data&& data) {
		sp_data newdata = sp_data(new Data(std::move(data)));
		return Push(newdata);
	}


	bool Remove(Data& data) {
		elem* prev = nullptr;
		elem* del = nullptr;
		elem* next = nullptr;

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
		return true;
	}

	/// <summary>
	/// Поиск elem
	/// </summary>
	bool Find(Data& data, elem*& out_prev, elem*& out_cur, elem*& out_next) const {
		elem* prev = nullptr;
		elem* cur = m_first;

		/*for (Elem* c = m_first; c != nullptr || &c->GetData() != &data; c = c->GetNext()) { }*/

		while (!(cur == nullptr || cur->GetDataPtr() == &data)) {
			prev = cur;
			cur = prev->GetNext();
		}

		out_prev = prev;
		out_cur = cur;
		out_next = cur != nullptr ? cur->GetNext() : nullptr;
		//out_next = out_cur != nullptr ? *out_cur->GetNext() : nullptr;
		return out_cur != nullptr;
	}

	bool Exists(Data& data) const {
		elem* cur;
		elem* prev;
		elem* next;
		return Find(data, prev, cur, next);
	}


	Data& GetFirst() const { return *m_first->GetData(); }
	Data& GetLast() const { return *m_last->GetData(); }
};

