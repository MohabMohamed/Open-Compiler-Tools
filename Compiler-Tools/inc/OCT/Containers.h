#pragma once

#include "OCT/Defines.h"
#include <cstring>
#include <vector>

namespace OCT
{
	namespace Containers
	{
		template<typename T, u64 size>
		class ring
		{
		protected:
			std::vector<T> m_ring;
			s64 m_index;
			s64 m_size;
			s64 m_front;
			s64 m_back;

			void increment(s64& ix)
			{
				ix++;
				if (ix >= size)
					ix = 0;
			}

			void decrement(s64& ix)
			{
				ix--;
				if (ix < 0)
					ix = size - 1;
			}
		public:
			ring()
			{
				m_ring.resize(size);
				m_index = 0;
				m_front = 0;
				m_back = 0;
				m_size = 0;
			}

			//returns true if overwritting the back
			bool push(const T& element)
			{
				if (m_size < size) {
					increment(m_front);
					m_ring[m_front] = element;
					m_size++;
					return false;
				}else
				{
					increment(m_front);
					if (m_back == m_index)
						increment(m_index);
					increment(m_back);
					m_ring[m_front] = element;
					return true;
				}
			}

			bool push(T&& element)
			{
				if (m_size < size) {
					increment(m_front);
					m_ring[m_front] = element;
					m_size++;
					return false;
				}
				else
				{
					increment(m_front);
					if (m_back == m_index)
						increment(m_index);
					increment(m_back);
					m_ring[m_front] = element;
					return true;
				}
			}

			T rewind()
			{
				if(m_index == m_back)
				{
					throw std::logic_error("[ring::rewind]: cannot rewind past the back head");
				}else
				{
					decrement(m_index);
					return m_ring[m_index];
				}
			}

			T read()
			{
				if(canRead())
				{
					increment(m_index);
					return m_ring[m_index];
				}
				throw std::logic_error("[ring::read]: cannot read ahead of the front head");
			}

			bool canRead()
			{
				if (m_size > 0 && m_index != m_front)
					return true;
				return false;
			}

			void clear()
			{
				m_index = 0;
				m_front = 0;
				m_back = 0;
				m_size = 0;
			}

			s64 getIndex()
			{
				return m_index;
			}

			void moveTo(s64 index)
			{
				m_index = index % size;
			}
		};
	}
}
