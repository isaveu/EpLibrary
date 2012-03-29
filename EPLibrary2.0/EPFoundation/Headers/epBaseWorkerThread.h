/*! 
@file epBaseWorkerThread.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
@date July 07, 2010
@brief A Base Worker Thread Class Interface.
@version 2.0

@section LICENSE

Copyright (C) 2012  Woong Gyu La <juhgiyo@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

@section DESCRIPTION

A Interface for Base Worker Thread Class.

*/
#ifndef __EP_BASE_WORKER_THREAD_H__
#define __EP_BASE_WORKER_THREAD_H__
#include "epJobScheduleQueue.h"
#include "epThread.h"
#include "epBaseJob.h"

namespace epl
{
	/*! 
	@class BaseWorkerThread epBaseWorkerThread.h
	@brief A class that implements Base Worker Thread Class.
	*/
	class EP_FOUNDATION BaseWorkerThread :public Thread
	{
	public:
		/// Enumerator for Thread Life Policy
		enum ThreadLifePolicy
		{
			/// The thread is infinitely looping.
			THREAD_LIFE_INFINITE=0,
			/// The thread suspends if work pool is empty.
			THREAD_LIFE_SUSPEND_AFTER_WORK,
			/// The thread terminates if work pool is empty.
			THREAD_LIFE_TERMINATE_AFTER_WORK,
			/// Thread Life Policy Count
			THREAD_LIFE_COUNT,
		};

		/*!
		Default Constructor

		Initializes the thread class
		@param[in] policy the life policy of this worker thread.
		*/
		BaseWorkerThread(const ThreadLifePolicy policy);
		
		/*!
		Default Destructor

		Destroy the Thread Class
		*/
		virtual ~BaseWorkerThread();

		/*!
		Assignment operator overloading
		@param[in] b the second object
		@return the new copied object
		*/
		BaseWorkerThread &operator=(const BaseWorkerThread & b)
		{
			if(this!=&b)
			{
				m_workPool=b.m_workPool;
				m_lifePolicy=b.m_lifePolicy;
				m_callBackClass=b.m_callBackClass;
				Thread::operator =(b);
			}
			return *this;
		}
		/*!
		Push in the new work to the work pool.
		@param[in] work the new work to put into the work pool.
		*/
		void Push(BaseJob * const  work);

		/*!
		Pop a work from the work pool.
		*/
		void Pop();

		/*!
		Get First Job in the Job Queue.
		*/
		BaseJob * &Front();

		/*!
		Erase the given work from the work pool.
		@param[in] work the work to erase from the work pool
		@return true if successful, otherwise false.
		*/
		bool Erase(BaseJob *const work);

		
		/*!
		Return the life policy of this worker thread.
		@return the life policy of this worker thread.
		*/
		ThreadLifePolicy GetLifePolicy() const
		{
			return m_lifePolicy;
		}

		/*!
		Set new Job Processor.
		@param[in] a set new Job Processor for this thread.
		*/
		virtual void SetArg(void* a);

		/*!
		Set call back class to call when work is done.
		@param[in] callBackClass the call back class.
		*/
		virtual void SetCallBackClass(void *callBackClass);

		/*!
		Get job count in work pool.
		@return the job count in work pool.
		*/
		int GetJobCount() const;

	protected:
		/*!
		Pure Worker Thread Code.
		*/
		virtual void execute()=0;

		/*!
		Call the Call Back Class if callback class is assigned.
		*/
		void callCallBack();

		/// the work list
		JobScheduleQueue m_workPool;
		/// the life policy of the thread
		ThreadLifePolicy m_lifePolicy;
		/// the call back class
		void *m_callBackClass;

	private:
		/*!
		Default Copy Constructor

		*Cannot be Used.
		*/
		BaseWorkerThread(const BaseWorkerThread & b){EP_ASSERT(0);}
	};
}
#endif //__EP_BASE_WORKER_THREAD_H__