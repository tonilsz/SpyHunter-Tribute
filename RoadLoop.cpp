#include "RoadLoop.h"


RoadLoop::RoadLoop(vector<SEGMENT_TYPE>* loop_template, SEGMENT_AMBIENT ambient):
pos(0)
{
	GenerateLoop(loop_template, ambient);
}

RoadLoop::~RoadLoop(){
	CleanLoop();
}

//Generate specific Road Loop
void RoadLoop::GenerateLoop(vector<SEGMENT_TYPE>* loop_template, const SEGMENT_AMBIENT &ambient){
	this->ambient = ambient;
	CleanLoop();
	for (vector<SEGMENT_TYPE>::iterator it = loop_template->begin(); it != loop_template->end(); ++it)
		loop.push_back(new RoadSegment(*it));
}

int RoadLoop::GetSize(){
	return loop.size();
}

void RoadLoop::CleanLoop(){
	for (vector<RoadSegment*>::iterator it = loop.begin(); it != loop.end(); ++it){
		(*it)->CleanSegment();
		RELEASE(*it);
	}

	loop.clear();
}