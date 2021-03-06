#include "MessageHandler.h"
#include "ErrorMsgBox.h"
#include "debuglog.h"
#include "master.h"


UpdateFilesStart* process1;
BehaviorStart* process2;
DummyLog* process3;

extern void (*interMsgPtr)(std::string);

void exterMsg(std::string input)
{
	if (process1)
	{
		process1->message(input);
	}
	else if (process2)
	{
		process2->message(input);
	}
	else if (process3)
	{
		process3->message(input);
	}
	else
	{
		DebugLogging("Non-captured message: " + input);
		CEMsgBox* msgbox = new CEMsgBox;
		msgbox->setWindowTitle("CRITICAL ERROR");
		msgbox->setText("Access process violtion. Running process not found. Report to Nemesis' author immediately.");
		msgbox->show();
		error = true;
	}
}

void initializeHandler()
{
	interMsgPtr = &exterMsg;
}

void connectProcess(UpdateFilesStart* newProcess)
{
	process1 = newProcess;
}

void connectProcess(BehaviorStart* newProcess)
{
	process2 = newProcess;
}

void connectProcess(DummyLog* newProcess)
{
	process3 = newProcess;
}

void disconnectProcess()
{
	DebugLogging("Standard log disconnected");
	process1 = nullptr;
	process2 = nullptr;
	process3 = nullptr;
}
