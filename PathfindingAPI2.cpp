#pragma once
#include "PathfindingAPI.h"
#include "Graph.h"
#include "AStar.h"
#include <omp.h>
#include <queue>
#include <chrono>


#ifdef __cplusplus
extern "C" {
#endif


//process all jobs within the batch in parallel
API void ProcessJobsParallel(JobBatch batch, int* outResults)
{

auto begin1 = std::chrono::steady_clock::now();
#pragma omp parallel for s
    for (int i = 0; i < batch.count; i++)
    {
        //get a job from the job list
        Job& j = batch.jobs[i];
       
        //create an instance of that job's graph to traverse
        Graph* graph = static_cast<Graph*>(j.graphHandle);

        //perform A* calculation
        AStarResult result = AStar(*graph, j.start, j.end);

        //return results to unity 
        outResults[i] = static_cast<int>(result.distances[j.end]);
    }

    auto end1 = std::chrono::steady_clock::now();
    auto timei = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - begin1).count();
}

//non-parallelized process all jobs within the batch in parallel
API void ProcessJobs(JobBatch batch, int* outResults)
{
    auto begin1 = std::chrono::steady_clock::now();
    for (int i = 0; i < batch.count; i++)
    {
        //get a job from the job list
        Job& j = batch.jobs[i];

        //create an instance of that job's graph to traverse
        Graph* graph = static_cast<Graph*>(j.graphHandle);

        //perform A* calculation
        AStarResult result = AStar(*graph, j.start, j.end);

        //return results to unity 
        outResults[i] = static_cast<int>(result.distances[j.end]);
    }

    auto end1 = std::chrono::steady_clock::now();
    auto timei = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - begin1).count();
}

//calculates a single shortest path to objective
API int GetShortestPath(Job job, int start, int end)
{
    
    if (!job.graphHandle) return -1;

    Graph* graph = static_cast<Graph*>(job.graphHandle);

    AStarResult result = AStar(*graph, start, end);

    //need to rework into output array pointer
    return static_cast<int>(result.distances[end]);
}


//create a graph 
API GraphHandle CreateGraph(int numOfVertices) {
    vector<vector<Edge>> adj(numOfVertices);
    vector<Node> nodes;

    for (int i = 0; i < numOfVertices; i++)
    {
        nodes.push_back({ i, 0, 0 });
    }

    Graph* graph = new Graph(adj, nodes);
    return static_cast<GraphHandle>(graph);

}

//remove a graph
API void DestroyGraph(GraphHandle graph)
{
    if (!graph) return;

    delete static_cast<Graph*>(graph);
}

//add edges to graph
API void AddEdge(GraphHandle graphHandle, int from, int to, float cost)
{
    if (!graphHandle) return;

    Graph* graph = static_cast<Graph*>(graphHandle);
    graph->InsertEdge(from, to, cost);
}

//set physical x,y coordinates of graph nodes
API void SetNodePosition(GraphHandle graphHandle, int id, int x, int y)
{
    if (!graphHandle) return;

    Graph* graph = static_cast<Graph*>(graphHandle);
    graph->SetNode(id, x, y);
}


#ifdef __cplusplus
}
#endif