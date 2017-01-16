#pragma once
#include "stdafx.h"

class StringStack
{
public:
	StringStack() = default;

	StringStack(StringStack const& stack);
	StringStack(StringStack && cloneStack);

	void Push(std::string const& element);
	void Pop();
	std::string GetTop() const;

	StringStack& operator=(StringStack const& cloneStack);
	StringStack& operator=(StringStack && moveStack);

	bool Empty() const;

	void Clear();

	~StringStack()
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

	void CopyNodes(StringStack const& stack);

	size_t m_stackSize = 0;
	std::shared_ptr<Node> m_top = nullptr;
};