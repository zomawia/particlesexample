#pragma once

#include "particles.h"

class ObjectPool {
	struct _intern {
		particle data;
		bool open;
		size_t next;
	};

	_intern *m_data;

	////////////////// 3 separate arrays
	//size_t *m_next;
	//particle *m_data;
	//bool *m_open;

	size_t m_size;

public:
	ObjectPool(size_t a_size) : m_size(a_size) {
		m_data = new _intern[m_size];

		for (size_t i = 0; i < m_size; ++i) {
			m_data[i].open = true;
			m_data[i].next = i + 1;
		}
	}

	class iterator {	//faux pointer
		ObjectPool *m_ref;
		size_t m_idx;

		iterator(ObjectPool *a_ref, size_t a_idx) :	m_ref(a_ref), m_idx(a_idx) {}

	public:
		iterator() : m_ref(nullptr), m_idx(0) {};

		particle &operator*() { return m_ref->m_data[m_idx].data; }		//*this	(deref operator)
		particle *operator->() { return &m_ref->m_data[m_idx].data; }	//this->(indirection oper)

		const particle &operator*() const { return m_ref->m_data[m_idx].data; }		//*this(const deref)
		const particle *operator->() const { return &m_ref->m_data[m_idx].data; }	//this->(const indirect)

		iterator &operator++() { m_idx = m_ref->m_data[m_idx].next; return *this; }	// (prefix increment)
		iterator operator++(int) { auto that = *this; operator++(); return that; }	// (postix increment)

		bool operator==(const iterator &O) const { return m_ref == O.m_ref && m_idx == O.m_idx; }
		bool operator!=(const iterator &O) const { return !(*this == O); }

		operator bool() const { m_ref != nullptr && 
			m_idx < m_ref->m_size && 
			!m_ref->m_data[m_idx].open; }
		
	};

};
