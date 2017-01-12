#pragma once
#include "stdafx.h"


template <typename T>
class CStack
{
public:
	CStack() = default;

	CStack(CStack<T> const& stack)
	{
		CopyNodes(stack);
	}

	CStack(CStack<T> && cloneStack)
	{
		if (this == &cloneStack)
		{
			throw std::logic_error("Self move assigment");
		}

		m_top = cloneStack.m_top;
		m_stackSize = cloneStack.m_stackSize;
		cloneStack.m_top = nullptr;
		cloneStack.m_stackSize = 0;
	}

	void Push(T const& element)
	{
		auto newNode = std::make_shared<Node>();
		newNode->content = element;

		if (!Empty())
		{
			newNode->next = m_top;
		}

		m_top = newNode;
		m_stackSize++;
	}

	T GetTop() const
	{
		if (Empty())
		{
			throw std::logic_error("Imposible return content from empty stack");
		}

		return m_top->content;
	}

	void Pop()
	{
		if (Empty())
		{
			throw std::logic_error("Imposible pop empty stack");
		}

		auto newNode = std::make_shared<Node>();
		newNode = m_top->next;
		m_top.reset();
		m_top = newNode;
		m_stackSize--;
	}

	CStack<T>& operator=(CStack<T> const& cloneStack)
	{
		if (this == &cloneStack)
		{
			throw std::logic_error("Self assigment");
		}

		CopyNodes(cloneStack);

		return *this;
	}

	CStack<T>& operator=(CStack<T> && moveStack)
	{
		if (this == &moveStack)
		{
			throw std::logic_error("Self move assigment");
		}

		m_stackSize = moveStack.stackSize;
		m_top = moveStack.m_top;
		moveStack.m_top = nullptr;
		moveStack.stackSize = 0;

		return *this;
	}

	bool Empty() const
	{
		return (m_stackSize == 0);
	}

	void Clear()
	{
		while(!Empty())
		{
			Pop();
		}
	}

private:
	struct Node
	{
		T content = T();
		std::shared_ptr<Node> next = nullptr;
	};

	void CopyNodes(CStack<T> const& stack)
	{
		if (!stack.Empty())
		{
			std::shared_ptr<Node> pCopiedNode = stack.m_top;
			
			Push(pCopiedNode->content);
			pCopiedNode = pCopiedNode->next;

			m_top->next = std::make_shared<Node>();
			auto pPasteNode = m_top->next;

			while (pCopiedNode != nullptr)
			{
				pPasteNode->content = pCopiedNode->content;

				pCopiedNode = pCopiedNode->next;

				pPasteNode->next = std::make_shared<Node>();
				pPasteNode = pPasteNode->next;
			}

			m_stackSize = stack.m_stackSize;
		}
	}

	size_t m_stackSize = 0;
	std::shared_ptr<Node> m_top = nullptr;
};