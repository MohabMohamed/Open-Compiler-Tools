#pragma once

#include "Chalcedony/Defines.h"
#include <iostream>
#include <memory>
#include <cstdlib>

namespace CT
{
	namespace details
	{
		struct MemoryBlock
		{
			void* ptr;
			u64 size;

			MemoryBlock()
			{
				ptr = nullptr;
				size = 0;
			}

			MemoryBlock(void* _ptr, u64 _size)
			{
				ptr = _ptr;
				size = _size;
			}
		};

		struct MemorySlot
		{
			MemoryBlock block;
			u64 ref_count;
			MemorySlot* next;

			MemorySlot()
			{
				ref_count = 0;
				next = nullptr;
			}

			~MemorySlot()
			{
				ref_count = 0;
				//if(next)
					//delete next;
			}
		};
	}

	template<typename T>
	class MemoryPool;

	template<typename T>
	class Handle {
		details::MemorySlot* m_object = nullptr;
		MemoryPool<T>* m_allocator = nullptr;
	public:
		Handle(details::MemorySlot* object = nullptr, MemoryPool<T>* allocator = nullptr)
		{
			m_object = object;
			m_allocator = allocator;
		}

		Handle(const Handle<T>& copy_handle)
		{
			this->~Handle();
			m_object = copy_handle.m_object;
			m_allocator = copy_handle.m_allocator;
			if (m_allocator && m_object)
				m_object->ref_count++;
		}

		Handle(Handle<T>&& move_handle)
		{
			this->~Handle();
			m_object = move_handle.m_object;
			m_allocator = move_handle.m_allocator;
			if (m_allocator && m_object)
				m_object->ref_count++;
		}

		Handle<T>& operator=(const Handle<T>& copy_handle)
		{
			this->~Handle();
			m_object = copy_handle.m_object;
			m_allocator = copy_handle.m_allocator;
			if (m_allocator && m_object)
				m_object->ref_count++;
			return *this;
		}

		Handle<T>& operator=(Handle<T>&& move_handle)
		{
			this->~Handle();
			m_object = move_handle.m_object;
			m_allocator = move_handle.m_allocator;
			if (m_allocator && m_object)
				m_object->ref_count++;
			return *this;
		}

		~Handle()
		{
			if (isVaild())
			{
				if (m_object->ref_count == 0) {
					m_allocator->deallocate(m_object);
					m_object = nullptr;
					m_allocator = nullptr;
				}
				else {
					m_object->ref_count--;
					if (m_object->ref_count == 0) {
						m_allocator->deallocate(m_object);
						m_object = nullptr;
						m_allocator = nullptr;
					}
				}
			}
		}

		operator T*()
		{
			return reinterpret_cast<T*>(m_object->block.ptr);
		}

		T* operator->()
		{
			return reinterpret_cast<T*>(m_object->block.ptr);
		}

		bool isVaild()
		{
			return m_object != nullptr && m_allocator != nullptr;
		}

		T* getObject()
		{
			return reinterpret_cast<T*>(m_object->block.ptr);
		}

		MemoryPool<T>* getAllocator()
		{
			return m_allocator;
		}

		void ref() {
			if (isVaild())
				m_object->ref_count++;
		}
	};

	template<typename T>
	class MemoryPool
	{
	public:
		MemoryPool(u64 poolCount = 4096)
		{
			m_rawMemory.size = poolCount * sizeof(T);
			m_rawMemory.ptr = std::malloc(m_rawMemory.size);
			m_usedSlots = nullptr;
			m_freeSlots = nullptr;
			u8* ptr = static_cast<u8*>(m_rawMemory.ptr);
			for(int i=0;i<poolCount;i++)
			{
				details::MemorySlot* free_slot = static_cast<details::MemorySlot*>(std::malloc(sizeof(details::MemorySlot)));
				free_slot->ref_count = 0;
				free_slot->block.ptr = ptr;
				free_slot->block.size = sizeof(T);
				free_slot->next = m_freeSlots;
				m_freeSlots = free_slot;
				ptr += sizeof(T);
			}
			free_amount = poolCount;
		}

		~MemoryPool()
		{
			std::free(m_rawMemory.ptr);
			delete m_usedSlots;
			delete m_freeSlots;
		}

		template<typename ...Args>
		Handle<T> allocate(Args&&... args)
		{
			free_amount--;
			auto free_slot = getFreeSlot();
			if(free_slot != nullptr)
			{
				new(free_slot->block.ptr) T(std::forward<Args>(args)...);
				return Handle<T>(free_slot, this);
			}
			return Handle<T>();
		}

		void deallocate(Handle<T>* handle)
		{
			if(!handle)
				return;

			details::MemorySlot** slot_it = &m_usedSlots;
			while(*slot_it != nullptr && (*slot_it)->block.ptr != handle->getObject())
			{
				slot_it = &(*slot_it)->next;
			}

			if(*slot_it == nullptr)
				return;

			(*slot_it)->ref_count--;
			if((*slot_it)->ref_count == 0){
				free_amount++;
				details::MemorySlot* free_slot = *slot_it;
				*slot_it = free_slot->next;

				free_slot->ref_count = 0;
				free_slot->next = m_freeSlots;
				m_freeSlots = free_slot;
			}
		}

		void deallocate(details::MemorySlot* slot)
		{
			if (!slot)
				return;
			details::MemorySlot* slot_it = m_usedSlots, *prev_it = nullptr;
			while (slot_it != nullptr && slot_it != slot)
			{
				prev_it = slot_it;
				slot_it = slot_it->next;
			}

			if (slot_it == nullptr)
				return;

			free_amount++;

			//it's the head node
			if (prev_it == nullptr)
			{
				m_usedSlots = slot_it->next;
				slot_it->ref_count = 0;
				slot_it->next = m_freeSlots;
				m_freeSlots = slot_it;
			}
			else {
				prev_it->next = slot_it->next;
				slot_it->ref_count = 0;
				slot_it->next = m_freeSlots;
				m_freeSlots = slot_it;
			}
		}

		void increment(Handle<T>* handle)
		{
			if(!handle || !handle->isVaild())
				return;

			details::MemorySlot** slot_it = &m_usedSlots;
			while(*slot_it != nullptr && (*slot_it)->block.ptr != handle->getObject())
			{
				slot_it = &(*slot_it)->next;
			}

			if(*slot_it == nullptr)
				return;

			(*slot_it)->ref_count++;
		}

	private:

		details::MemorySlot* getFreeSlot()
		{
			if(m_freeSlots != nullptr)
			{
				auto result_free_node = m_freeSlots;
				m_freeSlots = m_freeSlots->next;
				result_free_node->ref_count++;
				result_free_node->next = m_usedSlots;
				m_usedSlots = result_free_node;
				return result_free_node;
			}
			std::cout << "out of memory" << std::endl;
			return nullptr;
		}

		details::MemoryBlock m_rawMemory;
		details::MemorySlot* m_usedSlots;
		details::MemorySlot* m_freeSlots;
		s64 free_amount;
	};
}