#include <dlfcn.h>

class Z3Loader
{
public:
	static Z3Loader const& get();
	void* loadSymbol(char const* _name) const;
	bool available() const;
private:
	Z3Loader();
	~Z3Loader();
	void* m_handle = nullptr;
};
