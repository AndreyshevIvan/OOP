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

	CStack(CStack<T> && otherStack)
	{
		if (this == &otherStack)
		{
			throw std::logic_error("Self moveing");
		}

		m_top = otherStack.m_top;
		m_stackSize = otherStack.m_stackSize;

		otherStack.m_top = nullptr;
		otherStack.m_stackSize = 0;
	}

	void Push(T const& element)
	{
		std::shared_ptr<Node> newNode(new Node);
		newNode->content = element;
		if (m_top)
		{
			newNode->next = m_top;
		}

		m_top = newNode;
		m_stackSize++;
	}

	T GetTop()
	{
		if (!m_top)
		{
			throw std::logic_error("Imposible return content from empty stack");
		}

		return m_top->content;
	}

	void Pop()
	{
		if (!m_top)
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

	CStack<T>& operator=(CStack<T> && assigmentStack)
	{
		if (this == &assigmentStack)
		{
			throw std::logic_error("Self move assigment");
		}

		m_stackSize = assigmentStack.stackSize;
		m_top = assigmentStack.m_top;
		assigmentStack.m_top = nullptr;

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
