#pragma once

#include <memory>
#include <stack>

namespace AB
{
	namespace Command
	{
		class Reciever
		{
		public:
			using Ptr = std::shared_ptr<Reciever>;
			using WeakPtr = std::weak_ptr<Reciever>;

		public:
			virtual ~Reciever() = default;
		};

		class Command
		{
		public:
			using Ptr = std::shared_ptr<Command>;

		public:
			Command(const Reciever::Ptr reciever);
			virtual ~Command() = default;
			
			virtual void Execute() = 0;
			virtual void UnExecute();

		protected:
			Reciever::WeakPtr GetReciever();

		private:
			Reciever::WeakPtr _reciever;
		};

		class Invoker
		{
		public:
			virtual ~Invoker() = default;

		protected:
			void DoCommand(const Command::Ptr command);
			void UndoLastCommand();

		private:
			std::stack<Command::Ptr> _redoStack;
			std::stack<Command::Ptr> _undoStack;
		};
	}
}
