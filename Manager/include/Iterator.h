#ifndef ITERATOR_H
#define ITERATOR_H

class DLink;

class Iterator
{
public:
	virtual DLink* First() = 0;
	virtual DLink* Next() = 0;
	virtual DLink* Curr() = 0;
	virtual bool IsDone() = 0;
};

#endif // !ITERATOR_H
