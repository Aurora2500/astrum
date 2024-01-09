#include "file_watch.hpp"

#include <iostream>
#ifdef __linux__

#include <sys/inotify.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#else

#error FileWatcher not implemented for this platform

#endif


FileWatcher::FileWatcher()
{
	m_fd = inotify_init1(IN_NONBLOCK);
	if (m_fd < 0)
	{
		std::cerr << "Failed to initialize inotify: " << strerror(errno) << std::endl;
		return;
	}
}

FileWatcher::~FileWatcher()
{
	for (int m_wd : m_wds)
	{
		if (m_wd >= 0)
			inotify_rm_watch(m_fd, m_wd);
	}
	if (m_fd >= 0)
		close(m_fd);
}

void FileWatcher::set_callback(callback_t callback)
{
	m_callback = callback;
}

void FileWatcher::add_watch(const std::string &path)
{
	int wd = inotify_add_watch(m_fd, path.c_str(), IN_CLOSE_WRITE);
	if (wd < 0)
	{
		std::cerr << "Failed to add watch for " << path << ": " << strerror(errno) << std::endl;
		return;
	}
	m_wds.push_back(wd);
}

void FileWatcher::poll()
{
	if (m_fd < 0)
		return;

	char buf[4096];
	ssize_t len = read(m_fd, buf, sizeof(buf));
	if (len < 0)
	{
		if (errno != EAGAIN) // EAGAIN means no events
			std::cerr << "Failed to read from inotify: " << strerror(errno) << std::endl;
		return;
	}

	for (char *ptr = buf; ptr < buf + len;)
	{
		struct inotify_event *event = (struct inotify_event *)ptr;
		ptr += sizeof(struct inotify_event) + event->len;
		std::string event_name = event->name;
		if (event->mask & IN_CLOSE_WRITE)
			m_callback(event_name);
	}
}