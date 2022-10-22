#ifndef ___THREADPOOL___
#define ___THREADPOOL___

#pragma warning(disable:4996)
#include "stdafx.h"

using namespace std;

class ThreadPool {
private:
	ThreadPool();

	size_t MAX_THREADS;
	vector<thread> m_worker;
	queue<function<void()>> m_jobs;

	condition_variable m_condition;
	mutex m_mutex;

	bool isStopAll;

	void WorkerThread();

	static ThreadPool* m_Instance;

public:
	~ThreadPool();

	static ThreadPool* GetInstance();
	static void Release();
	void EnqueueJob(function<void()> job);
	template<typename Func, typename... Args>
	future<typename result_of<Func(Args...)>::type> EmplaceJobAndGetFutrue(Func&& f, Args&&... args);
};

template<typename Func, typename ...Args>
inline future<typename result_of<Func(Args...)>::type> ThreadPool::EmplaceJobAndGetFutrue(Func&& f, Args && ...args) {
	using return_type = typename result_of<Func(Args...)>::type;
	auto callable = bind(forward<Func>(f), forward<Args>(args)...);

	using job_type = packaged_task<return_type()>;
	auto job = make_shared<job_type>(move(callable));
	auto result_future = job->get_future();
	{
		lock_guard<mutex> lock(m_mutex);
		m_jobs.push([job]() { (*job)(); });
	}
	m_condition.notify_one();

	return result_future;
}

#endif // !___THREADPOOL___

