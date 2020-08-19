#pragma once

/// <summary>
/// Односвязный список
/// Оперирует классами Element(Elem), хранящие shared_ptr на данные T(Data) и weak_ptr на следующий элемент
/// Содержит указатель на последний элемент для O(1) при вставке в конец
/// </summary>
/// <typeparam name="T">Тип хранимых данных</typeparam>
template <typename T>
class LinkedList
{
public:
	template <typename T> class Element;

	using Data = T;						// хранимый тип данных
	using Elem = Element<T>;			// елемент хранящий данные
	using wp_elem = std::weak_ptr<T>;	// слабая ссылка на элемент

	using sp_data = std::shared_ptr<T>; // расшаренный указатель на данные
	using wp_data = std::weak_ptr<T>;	// слабая ссылка на данные
	using cp_data = T* const;			// константный указатель на константный объект

	using func_find_elem = std::function<bool(const Elem&, int)>; // делегат функции поиска элемента
	using func_find_data = std::function<bool(const Data&, int)>; // делегат функции поиска данных

private:


	/// <summary>
	/// Класс элемента для хранения ссылки на данные и на следующий элемент
	/// </summary>
	/// <typeparam name="T">тип данных</typeparam>
	template <typename T>
	class Element
	{
	private:
		sp_data m_data;
		Elem* m_next;
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
		cp_data GetDataPtr() const {
			return (cp_data) & *m_data;
		}

		void SetNext(Elem* next) { m_next = next; }
		Elem* GetNext() { return m_next; }
	};

	Elem* m_first;
	Elem* m_last;
	int m_size;

public:

	LinkedList() : m_first(nullptr), m_last(nullptr), m_size(0) {}

	virtual ~LinkedList() {
		Clear();
	}

	sp_data& operator[] (int index) const { return this->GetByIndex(index); }

	int GetSize() const { return m_size; }
	Data& GetFirst() const { return *m_first->GetData(); }
	Data& GetLast() const { return *m_last->GetData(); }

	sp_data& GetByIndex(int index) {
		return GetElemByIndex(index)->GetData();
	}

	Elem* GetElemByIndex(int index) {
		CheckIndexWithThrow(index);

		Elem* cur = m_first;
		for (int i = 0; i < index; i++)
			cur = cur->GetNext();
		return cur;
	}

	bool CheckIndex(int index) const {
		return index >= 0 && index < m_size;
	}

	void CheckIndexWithThrow(int index) {
		if (!CheckIndex(index))
			throw std::out_of_range("wrong index");
	}

	sp_data& Push(sp_data& spdata) {
		auto* el = new Elem(spdata);
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

	sp_data& Insert(Data&& data, int index) {
		sp_data newdata = sp_data(new Data(std::move(data)));
		return Insert(newdata, index);
	}

	/// <summary>
	/// Вставка data в позицию index. 
	/// Старый элемент с позицией index будет смешен вперед.
	/// </summary>
	sp_data& Insert(sp_data& data, int index) {
		CheckIndexWithThrow(index);
		Elem* newElem = new Elem(data);

		/* Найти родительский элемент (индекс == index-1) и вставить data после него */
		/* Соответственно index == 0 обрабатывается отдельно */

		if (index == 0) {
			newElem->SetNext(m_first);
			m_first = newElem;
		}
		else {
			/* Найдем родительский элемент (index - 1) и произведем вставку после него */
			Elem* parent = GetElemByIndex(index - 1);
			newElem->SetNext(parent->GetNext());
			parent->SetNext(newElem);
		}
		m_size++;
		return newElem->GetData();
	}

	bool Remove(Data& data) {
		Elem* prev = nullptr;
		Elem* del = nullptr;
		Elem* next = nullptr;

		if (!FindElemByData(data, prev, del, next))
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

	bool FindElemByFunc(func_find_elem find_func, Elem*& out_prev, Elem*& out_cur, Elem*& out_next) const {

		int i = 0;
		while (!(out_cur == nullptr || find_func(*out_cur, i))) {
			if (out_cur != m_first)
				out_prev = out_cur;

			out_cur = out_cur->GetNext();
			i++;
		}

		out_next = out_cur != nullptr ? out_cur->GetNext() : nullptr;
		return out_cur != nullptr;
	}
	bool FindElemByDataFunc(func_find_data find_func, Elem*& out_prev, Elem*& out_cur, Elem*& out_next) const {
		return FindElemByFunc([&find_func](const Elem& elem, int index) { return find_func(elem->GetDataPtr(), index) }, out_prev, out_cur, out_next);
	}

	bool FindElemByIndex(int index, Elem*& out_prev, Elem*& out_cur, Elem*& out_next) const {
		CheckIndexWithThrow(index);
		return FindElemByDataFunc([index](const Data& d, int i) {return i == index}, out_prev, out_cur, out_next);
	}

	bool FindElemByData(const Data& data, Elem*& out_prev, Elem*& out_cur, Elem*& out_next) const {
		return FindElemByDataFunc([&data](const Data& d, int i) {return &d == &data}, out_prev, out_cur, out_next);
	}

	cp_data FindDataByElemFunc(func_find_elem find_func, Elem*& prev) const {
		Elem* cur = m_first;
		int i = 0;
		while (!(cur == nullptr || find_func(*cur, i))) {
			if (cur != m_first)
				prev = cur;

			cur = cur->GetNext();
			i++;
		}
		return cur != nullptr ? cur->GetDataPtr() : nullptr;
	}

	cp_data FindDataByElemFunc(func_find_elem find_func) const {
		Elem* prev;
		return FindDataByElemFunc(find_func, prev);
	}

	cp_data FindDataByFunc(func_find_data find_func, Elem*& prev) const
	{
		return FindDataByElemFunc([&find_func](const Elem& el, int index) { return find_func(*el.GetDataPtr(), index); }, prev);
	}

	cp_data FindDataByFunc(func_find_data find_func) const
	{
		Elem* prev;
		return FindDataByFunc(find_func, prev);
	}

	bool Exists(func_find_data find_func) const
	{
		return FindDataByFunc(find_func) != nullptr;
	}

	bool Exists(const Data& data) const
	{
		return FindDataByFunc([&data](const Data& ddd, int index) { return &ddd == &data; }) != nullptr;
	}

	bool Exists(Data&& data) const
	{
		return FindDataByFunc([data](const Data& ddd, int index) { return ddd == data; }) != nullptr;
	}
};

