#include <libsmtutil/Z3Loader.h>
#include <libsmtutil/Exceptions.h>
#include <z3.h>
#include <z3_version.h>
#include <vector>

using namespace std;

Z3Loader const& Z3Loader::get()
{
	static Z3Loader z3;
	return z3;
}
void* Z3Loader::loadSymbol(char const* _name) const
{
	using namespace solidity::smtutil;
	smtAssert(m_handle, "Attempted to use dynamically loaded Z3, even though it is not available.");
	void* sym = dlsym(m_handle, _name);
	smtAssert(sym, string("Symbol \"") + _name + "\" not found in libz3.so");
	return sym;
}

bool Z3Loader::available() const
{
	if (m_handle == nullptr)
		return false;
	unsigned major = 0;
	unsigned minor = 0;
	unsigned build = 0;
	unsigned rev = 0;
	Z3_get_version(&major, &minor, &build, &rev);
	return major == 4 && minor >= 6;
}

Z3Loader::Z3Loader()
{
	vector<unsigned> versionParts{Z3_MAJOR_VERSION, Z3_MINOR_VERSION, Z3_BUILD_NUMBER, Z3_REVISION_NUMBER};
	string basename{"libz3.so"};
	while (!m_handle && !versionParts.empty())
	{
		string name = basename;
		for (unsigned part: versionParts)
			name += "." + to_string(part);
		m_handle = dlmopen(LM_ID_NEWLM, name.c_str(), RTLD_NOW);
		versionParts.pop_back();
	}
	if (!m_handle)
		m_handle = dlmopen(LM_ID_NEWLM, basename.c_str(), RTLD_NOW);
}
Z3Loader::~Z3Loader()
{
	if (m_handle)
		dlclose(m_handle);
}
