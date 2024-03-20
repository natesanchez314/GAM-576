#ifndef DLINK_H
#define DLINK_H

class DLink
{
public:
	DLink* next;
	DLink* prev;

public:
	DLink();
	virtual ~DLink() = default;
	virtual void Clear();

	virtual void Wash();
	virtual char* GetName();
	virtual bool Compare(DLink* pTargetNode);
	virtual void Dump();
};

#endif // !DLINK_H