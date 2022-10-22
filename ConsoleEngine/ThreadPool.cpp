#include "ThreadPool.h"

ThreadPool* ThreadPool::m_Instance = nullptr;
ThreadPool::ThreadPool() {
	SYSTEM_INFO SysInfo;
	GetSystemInfo(&SysInfo);
	MAX_THREADS = SysInfo.dwNumberOfProcessors;

	isStopAll = false;

	m_worker.reserve(MAX_THREADS);
	for (size_t i = 0; i < MAX_THREADS; ++i) {
		m_worker.emplace_back([this]() { this->WorkerThread(); });
	}
}
ThreadPool::~ThreadPool() {
	isStopAll = true;

	m_condition.notify_all();

	for (auto& th : m_worker) { th.join(); }
}
void ThreadPool::WorkerThread() {
	while (true) {
		unique_lock<mutex> lock(m_mutex);

		m_condition.wait(lock, [this]() { return !this->m_jobs.empty() || isStopAll; });

		if (isStopAll && m_jobs.empty()) { return; }

		function<void()> job = move(m_jobs.front());
		m_jobs.pop();
		lock.unlock();

		job();
	}
}
void ThreadPool::EnqueueJob(function<void()> job) {
	if (isStopAll) { throw runtime_error("ThreadPool »ç¿ë ÁßÁöµÊ"); }
	{
		lock_guard<mutex> lock(m_mutex);
		m_jobs.push(move(job));
	}
	
	m_condition.notify_one();
}
ThreadPool* ThreadPool::GetInstance() {
	if (!m_Instance) { m_Instance = new ThreadPool; }
	return m_Instance;
}
void ThreadPool::Release() {
	if (m_Instance) { delete m_Instance; }
}
