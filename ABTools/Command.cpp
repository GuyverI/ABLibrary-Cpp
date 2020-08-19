#include "Command.h"

namespace AB
{
	namespace Command
	{
		Command::Command(Reciever::Ptr reciever)
			: _reciever(reciever)
		{}

		void Command::UnExecute()
		{}

		Reciever::WeakPtr Command::GetReciever()
		{
			return _reciever;
		}




		void Invoker::DoCommand(const Command::Ptr command)
		{
			if (command)
			{
				command->Execute();

				_redoStack = std::stack<Command::Ptr>();
				_undoStack.push(command);
			}
		}

		void Invoker::UndoLastCommand()
		{
			auto command = _undoStack.top();
			command->UnExecute();

			_undoStack.pop();
			_redoStack.push(command);
		}
	}
}


