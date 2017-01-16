#include "stdafx.h"
#include "StringStack.h"

StringStack::StringStack(StringStack const& stack)
{
	CopyNodes(stack);
}

StringStack::StringStack(StringStack && cloneStack)
{
	m_top = cloneStack.m_top;
	m_stackSize = cloneStack.m_stackSize;
	cloneStack.m_top = nullptr;
	cloneStack.m_stackSize = 0;
}

void StringStack::Push(std::string const& element)
{
	auto newNode = std::make_shared<Node>(element, m_top);
	m_top = newNode;
	m_stackSize++;
}

std::string StringStack::GetTop() const
{
	if (Empty())
	{
		throw std::logic_error("Imposible return content from empty stack");
	}

	return m_top->content;
}

void StringStack::Pop()
{
	if (!Empty())
	{
		m_top->content.~basic_string();
		m_top = m_top->next;
		m_stackSize--;
	}
}

StringStack& StringStack::operator=(StringStack const& cloneStack)
{
	if (this != &cloneStack)
	{
		Clear();
		CopyNodes(cloneStack);
	}

	return *this;
}

StringStack& StringStack::operator=(StringStack && moveStack)
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

bool StringStack::Empty() const
{
	return (m_stackSize == 0);
}

void StringStack::Clear()
{
	while (!Empty())
	{
		m_top->content.~basic_string();
		Pop();
	}
}

void StringStack::CopyNodes(StringStack const& stack)
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