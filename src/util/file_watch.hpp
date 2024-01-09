#include <string>
#include <vector>
#include <functional>

class FileWatcher
{
	using callback_t = std::function<void(std::string const&)>;
private:
	int m_fd;
	std::vector<int> m_wds;
	callback_t m_callback;

public:
	FileWatcher();
	~FileWatcher();

	void set_callback(callback_t callback);

	void add_watch(const std::string &path);

	void poll();
};