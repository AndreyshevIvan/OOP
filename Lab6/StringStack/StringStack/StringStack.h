#pragma once
#include "stdafx.h"

class CStack
{
public:
	CStack() = default;

	CStack(CStack const& stack)
	{
		CopyNodes(stack);
	}

	CStack(CStack && cloneStack)
	{
		m_top = cloneStack.m_top;
		m_stackSize = cloneStack.m_stackSize;
		cloneStack.m_top = nullptr;
		cloneStack.m_stackSize = 0;
	}

	void Push(std::string const& element)
	{
		auto newNode = std::make_shared<Node>(element, m_top);
		m_top = newNode;
		m_stackSize++;
	}

	std::string GetTop() const
	{
		if (Empty())
		{
			throw std::logic_error("Imposible return content from empty stack");
		}

		return m_top->content;
	}

	void Pop()
	{
		if (!Empty())
		{
			m_top->content.~basic_string();
			m_top = m_top->next;
			m_stackSize--;
		}
	}

	CStack& operator=(CStack const& cloneStack)
	{
		if (this != &cloneStack)
		{
			Clear();
			CopyNodes(cloneStack);
		}

		return *this;
	}

	CStack& operator=(CStack && moveStack)
	{
		if (this != &moveStack)
		{
			m_stackSize = moveStack.m_stackSize;
			m_top = moveStack.m_top;
			moveStack.m_top = nullptr;
			moveStack.m_stackSize = 0;
		}

		return *this;
	}

	bool Empty() const
	{
		return (m_stackSize == 0);
	}

	void Clear()
	{
		while (!Empty())
		{
			m_top->content.~basic_string();
			Pop();
		}
	}

	~CStack()
	{
		Clear();
	}

private:
	struct Node
	{
		Node(std::string const& str, std::shared_ptr<Node> const& nextNode)
			:content(str)
			,next(nextNode)
		{
		}
		std::string content;
		std::shared_ptr<Node> next = nullptr;
	};

	void CopyNodes(CStack const& stack)
	{
		if (!stack.Empty())
		{
			std::shared_ptr<Node> pCopiedNode = stack.m_top;

			m_top = std::make_shared<Node>(*pCopiedNode);
			auto pPasteNode = m_top;

			pPasteNode->content = pCopiedNode->content;

			while (pCopiedNode->next != nullptr)
			{
				pPasteNode->next = std::make_shared<Node>(*pCopiedNode->next);

				pCopiedNode = pCopiedNode->next;
				pPasteNode = pPasteNode->next;
			}

			m_stackSize = stack.m_stackSize;
		}
	}

	size_t m_stackSize = 0;
	std::shared_ptr<Node> m_top = nullptr;
};