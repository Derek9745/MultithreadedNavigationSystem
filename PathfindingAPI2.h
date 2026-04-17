#pragma once

#include "../PathfindingDLL/Job.h"

#ifdef PATHFINDINGDLL_EXPORTS
#define API __declspec(dllexport)
#else
#define API __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C" {
#endif


	typedef void* GraphHandle;
	
	//process a single job
	API int GetShortestPath(Job job, int start, int end);

	API GraphHandle CreateGraph(int numOfVertices);

	API void DestroyGraph(GraphHandle graph);

	API void AddEdge(GraphHandle graph, int from, int to, float cost);

	API void SetNodePosition(GraphHandle graph, int id, int x, int y);

	//call this method to begin processing a batch of jobs in parallel
	API void ProcessJobsParallel(JobBatch batch, int* outPaths);

	//non-parallelized processing of a batch of jobs
	API void ProcessJobs(JobBatch batch, int* outPaths);

	

#ifdef __cplusplus
}
#endif


