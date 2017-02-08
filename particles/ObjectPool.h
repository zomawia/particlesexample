#pragma once

#include "particles.h"

class ObjectPool {
	struct _intern {
		particle data;
		bool open;
		size_t next;
	};

	_intern *m_data;
	size_t m_size;
	size_t openHead;
	size_t fillHead;

public:
	ObjectPool(size_t a_size) : m_size(a_size), openHead(0), fillHead(m_size) {
		m_data = new _intern[m_size];

		for (size_t i = 0; i < m_size; ++i) {
			m_data[i].open = true;
			m_data[i].next = i + 1;
		}
	}

	class iterator {	//faux pointer
		ObjectPool *m_ref;
		size_t m_idx;

		friend class ObjectPool;

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
			!m_ref->m_data[m_idx].open; return this;
		}
		
	};

	//push the value into the pool and generate an iterator
	iterator push(const particle &val = particle()) {
		if (openHead >= m_size) return iterator();

		size_t idx = openHead;

		m_data[idx].data = val;
		m_data[idx].open = false;

		openHead = m_data[openHead].next;

		if (idx < fillHead) {	// if inserted before the head, become the head
			m_data[idx].next = fillHead;
			fillHead = idx;
		}
		else {					// otherwise there must be something filled to our left

			size_t left = idx;
			while (m_data[--left].open);

			m_data[idx].next = m_data[left].next;
			m_data[left].next = idx;

			m_data[openHead];
		}
		return iterator(this, idx);
	}

	iterator pop(iterator it) {
		if (!(it && it.m_ref == this)) return iterator();

		size_t idx = it.m_idx;
		++it;

		// if popping the closed head, update the close list
		// if popping left of the vacant head, update the vacant head
		// if there was a closed next pointing to this indx, update it
		
		m_data[idx].open = true;
		
		//////////////////////////////////////
		// for fixing the filled list pointers
		if (idx == fillHead) {fillHead = m_data[idx].next;}
		else { //there must be a closed index pointing to it
			size_t left = idx;
			while (m_data[--left].open);	//walk left until it hit the thing pointing at it
			m_data[left].next = m_data[idx].next; //tell it to point at what it was prev pointing to
		}

		///////////////////////////////
		// For inserting the open space
		if (idx < openHead) {
			m_data[idx].next = openHead;
			openHead = idx;
		}

		// if vacancy to the left
		else {
			size_t left = idx;
			while (!m_data[--left].open);

			m_data[idx].next = m_data[left].next;
			m_data[left].next = idx;
		}
		return it;
	}

	iterator begin() { return iterator(this, fillHead); }
	iterator end() { return iterator(this, m_size); }
};
