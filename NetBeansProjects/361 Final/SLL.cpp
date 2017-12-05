
#include "SLL.hpp"
#include "Job.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

SLL::SLL()
{
    first = NULL;
    last = NULL;
    size = 0;
}

SLL::~SLL()
{
    Job *tmp = first;
    while (first != NULL)
    {
        tmp = first->next;
        delete first;
        first = tmp;
        size--;
    }
    first = NULL;
    last = NULL;
}

void SLL::printSLL()
{
    Job *tmp = first;
    while (tmp != NULL)
    {
        tmp->printJob();
        tmp = tmp->next;
    }

    cout << endl;
}

void SLL::push2(Job *j)
{
    if (first == NULL)//|| first->priority > j->priority)
    {
        size++;
        j->next=first;
        first = j;
    } else
    {
        Job *tmp= first;
        while (tmp->next!=NULL)// && tmp->next->priority <= j->priority)
        {
            tmp = tmp->next;
        }
        j->next = tmp->next;
        tmp->next = j;
        size++;
    }
}

void SLL::push1(Job *j)
{ 
    if (first == NULL|| first->runtime > j->runtime)
    {
        size++;
        j->next=first;
        first = j;
    } else
    {
        Job *tmp= first;
        while (tmp->next!=NULL && tmp->next->runtime < j->runtime)
        {
             tmp = tmp->next;
        }
        j->next = tmp->next;
        tmp->next = j;
        size++;
    }
}

int SLL::pop()
{
    if (size > 0)
    {
        Job *x = last;
        if (first != last)
        {
            Job *tmp = first;
            for (int i = 0; i < size - 1; i++)
            {
                tmp = tmp->next;
            }
            delete last;
            last = tmp;
            last->next = NULL;
        } else
        {
            delete last;
            first = NULL;
            last = NULL;
        }
        size--;
        return 1;
    } else
    {
        return -1;
    }
}

Job *SLL::remFirst()
{ 
    Job *tmp = first->next;
    Job *j = first;
    first = tmp;
    size--;
    return j;
}

int SLL::getSize()
{
    return size;
}

int SLL::findK(int k) 
{
	Job *tmp = first;
	int ind = 0;
	while (tmp != NULL && tmp->jobNum != k) {
		tmp = tmp->next;
		ind++;
	}
	if (ind < size) {
		return ind;
	}
	else {
		return -1;
	}
}

void SLL::remKth(int x)
{
    int k = findK(x);
    if (k < size && k > 0)
    {
        Job *tmp = first;
        for (int i = 0; i < k - 1; i++)
        {
            tmp = tmp->next;
        }
        Job *tmp2 = tmp->next;
        tmp->next = tmp->next->next;
        delete tmp2;
        
    }
    else if (k==0)
    {
        remFirst();
    }
}

Job *SLL::findJob(int k)
{
    Job *tmp = first;
    while(tmp->jobNum != k && tmp!=NULL)
    {
        tmp = tmp->next;
    }
    return tmp;
}

Job* SLL::getFirst(){
    return first;
}

void SLL::addAtK(Job* x, int k)
{
    Job *tmp = first;
    if (k == 0)
    {
        push2(x);
    }
    if (k < size && k >= 0)
    {
        for (int i = 0; i < k - 1; i++)
        {
            tmp = tmp->next;
        }
        Job *tmp2 = tmp->next;
        tmp->next = x;
        tmp->next->next = tmp2;
        size++;
    }
}

void SLL::push3(Job* j)
{
    Job* newJ = new Job (j->jobNum, j->arrTime, j->m, j->dev, j->runtime, j->priority);
    newJ->devHold=j->devHold;
     if (first == NULL)//|| first->priority > j->priority)
    {
        size++;
        newJ->next=first;
        first = newJ;
    } else
    {
        Job *tmp= first;
        while (tmp->next!=NULL)// && tmp->next->priority <= j->priority)
        {
            tmp = tmp->next;
        }
        newJ->next = tmp->next;
        tmp->next = newJ;
        size++;
    }
}