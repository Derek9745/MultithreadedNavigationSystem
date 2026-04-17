#pragma once

typedef void* GraphHandle;

struct Job
{
    GraphHandle graphHandle;
    int start;
    int end;
};

struct JobBatch
{
    Job* jobs;
    int count;
};