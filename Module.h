#ifndef __MODULE_H__
#define __MODULE_H__

class Application;
class Collider;

enum COLISION_STATE;

class Module
{
public:

	Module(bool active = true) : active(active)
	{}

	~Module()
	{}

	bool IsEnabled() const
	{
		return active;
	}

	 bool Enable()
	{
		if(active == false)
			return active = Start();

		return true;
	}

	bool Disable()
	{
		if(active == true)
			return active = !Stop();

		return true;
	}

	virtual bool Start()
	{
		return true;
	}

	virtual bool Resume() 
	{
		return true; 
	}

	virtual update_status PreUpdate()
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status Update()
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status PostUpdate()
	{
		return UPDATE_CONTINUE;
	}

	virtual bool Stop()
	{
		return true;
	}

	virtual bool OnColision(Collider* a, Collider *b, COLISION_STATE status)
	{
		//LOG("Collision not controled between: %s and  %s\n", (char)a->type, (char)b->type);
		return true;
	}

private:
	bool active = true;
};

#endif // __MODULE_H__