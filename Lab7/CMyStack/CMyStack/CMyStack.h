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
			throw std::logic_error("Imposible return content from empty empty");
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
