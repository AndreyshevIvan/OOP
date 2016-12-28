#pragma once
#include "stdafx.h"

template <typename T>
class CStack
{
public:
	CStack() = default;

	CStack(CStack<T> const& stack)
	{
		CopyNodes(stack.m_top);
	}

	CStack(CStack<T> && cloneStack)
	{
		if (this == &cloneStack)
		{
			throw std::logic_error("Self move assigment");
		}

		m_top = std::move(cloneStack.m_top);
		m_stackSize = std::move(cloneStack.m_stackSize);

		cloneStack.m_top = nullptr;
		cloneStack.m_stackSize = 0;
	}

	void Push(T const& element)
	{
		std::shared_ptr<Node> newNode(new Node);
		newNode->content = element;
		if (!Empty())
		{
			newNode->next = m_top;
		}

		m_top = newNode;
		m_stackSize++;
	}

	T GetTop()
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

		std::shared_ptr<Node> newNode(new Node);
		newNode = m_top->next;
		m_top.reset();
		m_top = newNode;
		m_stackSize--;
	}

	CStack<T>& operator=(CStack<T> const& assigmentStack)
	{
		if (this == &assigmentStack)
		{
			throw std::logic_error("Self assigment");
		}

		CopyNodes(assigmentStack.m_top);

		return *this;
	}

	CStack<T>& operator=(CStack<T> && cloneStack)
	{
		if (this == &cloneStack)
		{
			throw std::logic_error("Self move assigment");
		}

		m_stackSize = std::move(cloneStack.stackSize);
		m_top = std::move(cloneStack.m_top);

		return *this;
	}

	bool Empty()
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

	void CopyNodes(std::shared_ptr<Node> const& copiedNode)
	{
		if (copiedNode->next)
		{
			CopyNodes(copiedNode->next);
		}

		Push(copiedNode->content);
	}

	size_t m_stackSize = 0;
	std::shared_ptr<Node> m_top = nullptr;
};
