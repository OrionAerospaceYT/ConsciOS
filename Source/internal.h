#pragma once


//-----Internals------
#include "./Libraries/common.h"
#include "sidekick.h"
#include "task_flow.h"
//-----Internals------

namespace sm{
	//------INTERNAL-----
	// DO NOT TOUCH
	void SM_UPDATE_LOOP(){
		taskSchedule();
		//const auto& task = TaskFlow[state_info.current_task];
		//task();
		END_LOG;
	}

	void SM_INIT(){
		SideKick();
	}
//------INTERNAL-----
}//ns sm
