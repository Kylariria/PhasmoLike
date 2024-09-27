#pragma once

class TextureManager;
class EntityManager;

template<typename ID>
class IManagable
{
	bool toDestroy;
protected:
	ID id;

public:
	void SetID(const ID& _id)
	{
		id = _id;
	}
	ID GetID() const
	{
		return id;
	}
	bool IsBeingDestroyed() const
	{
		return toDestroy;
	}
	void Destroy()
	{
		toDestroy = true;
	}

public:
	IManagable(const ID& _id)
	{
		id = _id;
		toDestroy = false;
	}

private:
	virtual void Register() = 0;
};