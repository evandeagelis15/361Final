#include "SLL.hpp"
#include "Job.hpp"

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
using namespace std;

int Time = 0;
int MainMemory;
int TotalDevices;
int increment;
int availableMem;
int availableDev;
int quit = 0;
int read=1;
int CPUtime=0;

Job* runProc = NULL;

SLL* hq1 = new SLL;
SLL* hq2 = new SLL;
SLL* rq = new SLL;
SLL* wq = new SLL;
SLL* devList = new SLL;
SLL* jList = new SLL;

int checkReq(int d, int j);
void run();
void deviceInterrupt(int d, int j);
void Lcommand(char* line);

void Ccommand(char* line)
{
    //cout<<"dick"<<endl;
    int time = 0;
    int i = 2;
    int num = line[2] - '0';
    int mult = 10;
    while (num <= 9 && num >= 0)
    {
        time = mult * time + num;
        i++;
        num = line[i] - '0';
         //cout<<time<<endl;
    }
    if (time == Time)
    {
       
        i = i + 3;
        num = line[i] - '0';
        while (num <= 9 && num >= 0)
        {
            MainMemory = mult * MainMemory + num;
            i++;
            num = line[i] - '0';

        }
        i = i + 3;
        num = line[i] - '0';
        while (num <= 9 && num >= 0)
        {
            TotalDevices = mult * TotalDevices + num;
            i++;
            num = line[i] - '0';
        }
        i = i + 3;
        num = line[i] - '0';
        while (num <= 9 && num >= 0)
        {
            increment = mult * increment + num;
            i++;
            num = line[i] - '0';
        }
        availableMem = MainMemory;
        availableDev = TotalDevices;
        cout << "C" << endl;
        cout << "Time:" << Time << endl;
        cout << "MainMemory:" << MainMemory << endl;
        cout << "Devices:" << TotalDevices << endl;
        cout << "increment:" << increment << endl;
        cout << endl;
        //MainMemory = line[4];
        //TotalDevices = line[];*/
        read=1;
    }
    else
    {
        read=0;
    }

}

void Acommand(const char* line)
{
    int time = 0;
    int j = 0;
    int m = 0;
    int s = 0;
    int r = 0;
    int p = 0;

    int i = 2;
    int num = line[2] - '0';
    int mult = 10;
    while (num <= 9 && num >= 0)
    {
        time = mult * time + num;
        i++;
        num = line[i] - '0';
    }
    if (time == Time)
    {
        i = i + 3;
        num = line[i] - '0';
        while (num <= 9 && num >= 0)
        {
            j = mult * j + num;
            i++;
            num = line[i] - '0';

        }
        i = i + 3;
        num = line[i] - '0';
        while (num <= 9 && num >= 0)
        {
            m = mult * m + num;
            i++;
            num = line[i] - '0';
        }
        i = i + 3;
        num = line[i] - '0';
        while (num <= 9 && num >= 0)
        {
            s = mult * s + num;
            i++;
            num = line[i] - '0';
        }
        i = i + 3;
        num = line[i] - '0';
        while (num <= 9 && num >= 0)
        {
            r = mult * r + num;
            i++;
            num = line[i] - '0';
        }
        i = i + 3;
        num = line[i] - '0';
        while (num <= 9 && num >= 0)
        {
            p = mult * p + num;
            i++;
            num = line[i] - '0';
        }
        if (m < MainMemory && s < TotalDevices)
        {
            Job *job = new Job(j, time, m, s, r, p);
            jList->push3(job);
            
            if (m < availableMem)
            {
                job->setState(1);
                rq->push2(job);
                
            } else
            {
                if (job->getPriority() == 1)
                {
                    hq1->push1(job);
                    
                } else
                {
                    hq2->push1(job);
                    
                }
            }
            cout << "A" << endl;
            job->printJob();
            
        }
        read=1;
    }
    else
        read=0;
}

void Qcommand(char* line)
{
    int time = 0;
    int j = 0;
    int d = 0;

    int i = 2;
    int num = line[2] - '0';
    int mult = 10;
    while (num <= 9 && num >= 0)
    {
        time = mult * time + num;
        i++;
        num = line[i] - '0';
    }
    if (time == Time)
    {
        i = i + 3;
        num = line[i] - '0';
        while (num <= 9 && num >= 0)
        {
            j = mult * j + num;
            i++;
            num = line[i] - '0';

        }
        i = i + 3;
        num = line[i] - '0';
        while (num <= 9 && num >= 0)
        {
            d = mult * d + num;
            i++;
            num = line[i] - '0';
        }
        cout << "Q" << endl;
        cout << "Time:" << time << endl;
        cout << "job:" << j << endl;
        cout << "devices:" << d << endl;
        cout << endl;
        read=1;
        if (d<=TotalDevices && runProc->getNum()==j)
        {
            
            deviceInterrupt(d,j);
            
        } else{
            cout<<"fj"<<endl;
            rq->findJob(j)->setWaitQ(1);
            cout<<"giri"<<endl;
            rq->findJob(j)->setRequest(d);
        }
        
    }
    else
        read=0;
}

void deviceInterrupt(int d, int j)
{
    if (d <= TotalDevices )
    {
        cout<<"IIGIJG"<<endl;
        runProc->setRequest(d);
        if (devList->findK(j) == -1)
        {
            devList->push3(runProc);
            cout<<"234"<< endl;
        }
        if (checkReq(d, j))
        {
            cout << 8 << endl;
            availableDev -= d;
            runProc->setDev(d);
            devList->findJob(j)->setDev(d);
            // added to runtime subtracted cputime
            runProc->setRuntime(runProc->getRuntime() + 1);
            CPUtime--;
            runProc->setState(1);
            runProc->setRequest(0);
            rq->push2(runProc);
            runProc = NULL;
            cout << 10 << endl;
        } else
        {
            runProc->setState(4);
            wq->push2(runProc);
            runProc = NULL;
        }
    }
}

void Lcommand(char* line)
{
    int time = 0;
    int j = 0;
    int d = 0;

    int i = 2;
    int num = line[2] - '0';
    int mult = 10;
    while (num <= 9 && num >= 0)
    {
        time = mult * time + num;
        i++;
        num = line[i] - '0';
    }
    if (time == Time)
    {
        i = i + 3;
        num = line[i] - '0';
        while (num <= 9 && num >= 0)
        {
            j = mult * j + num;
            i++;
            num = line[i] - '0';

        }
        i = i + 3;
        num = line[i] - '0';
        while (num <= 9 && num >= 0)
        {
            d = mult * d + num;
            i++;
            num = line[i] - '0';
        }
        
        availableDev+=d;
        rq->findJob(j)->setDev(-d);
        devList->findJob(j)->setDev(-d);
        if (devList->findJob(j)->getDev()==0)
        {
            devList->remKth(j);
        }
        Job *tmp =wq->getFirst();
        while(tmp!=NULL)
        {
            if(checkReq(tmp->getRequest(), tmp->getNum()))
            {
                cout<<"NIP"<<endl;
                availableDev-=tmp->getRequest();
                tmp->setDev(tmp->getRequest());
                devList->findJob(tmp->getNum())->setDev(tmp->getRequest());
                cout << "nap"<< endl;
                devList->findJob(tmp->getNum())->setRequest(0);
                tmp->setRequest(0);
                cout<<"nike" << endl;
                rq->push2(wq->findJob(tmp->getNum()));
                wq->remKth(tmp->getNum());
            }
            
            tmp=tmp->getNext();
        }
        
        cout << "L" << endl;
        cout << "Time:" << time << endl;
        cout << "job:" << j << endl;
        cout << "devices:" << d << endl;
        cout << endl;
        read =1;
    }
    else
        read=0;
}

void Dcommand(char* line)
{
    int time = 0;
    int i = 2;
    int num = line[2] - '0';
    int mult = 10;
    while (num <= 9 && num >= 0)
    {
        time = mult * time + num;
        i++;
        num = line[i] - '0';
    }
    if (time ==Time)
    {
        cout << "D" << endl;
        cout << "Time:" << time << endl;
        cout << endl;
        read=1;
    }
    else if (time == 9999)
    {
        cout << "D" << endl;
        cout << "Time:" << time << endl;
        jList->printSLL();
        cout << endl;
        read=1;
        quit =1;
    }
    else
    {
        read=0;
    }
        
}

void complete(Job *j)
{  
    if (j->getRequest() == 0 && !j->getWaitQ())
    {
        j->setState(3);
        availableMem += j->getM();
        availableDev += j->getDev();
        devList->remKth(j->getNum());
    }
}

void run()
{
    if(rq->getSize()!=0)
    {
        if (runProc == NULL)
        {
            runProc=rq->remFirst();
            runProc->setState(2);
            //runProc->setRuntime(runProc->getRuntime() - 1);
//            CPUtime++;
        } 
        else if (CPUtime == increment-1)
        {
            runProc->setState(1);
            rq->push2(runProc);
            runProc=rq->remFirst();
            runProc->setState(2);
            CPUtime = 0;
//            runProc->setRuntime(runProc->getRuntime() - 1);
//            CPUtime++;
        } else if(runProc->getWaitQ()==1){
            cout<<"HGGHG"<<endl;
            runProc->setWaitQ(0);
            deviceInterrupt(runProc->getRequest(),runProc->getNum());
            runProc=rq->remFirst();
            runProc->setState(2);
        }
        runProc->setRuntime(runProc->getRuntime() - 1);
        CPUtime++;

//        if (runProc->getRuntime()==0)
//        {
//           complete(runProc);
//            runProc=rq->remFirst();
//            runProc->setState(2);
//        }
    }   
}

int checkReq(int d, int j)
{
    cout<<35<<endl;
    int work = availableDev;
    int finish[devList->getSize()];
    int tmpDev[devList->getSize()];
    Job* tmp = devList->getFirst();
    SLL* tmpList =devList;
    int flag = 1;
    cout<<0<<endl;
    devList->printSLL();
    cout<<devList->getSize()<<endl;
    for(int i =0; i< devList->getSize(); i++)
    {
        finish[i] = 0;
        cout<<59000<<endl;
        tmpDev[i]=tmp->getDev();
        cout<< "Need: "<< tmp->getNeed()<< endl;
        if(finish[i] == 0 & tmp->getNeed()<=work)
        {
            work+=tmpDev[i];
            finish[i]=1;
        }
        else
        {
            flag=0;
        }
        cout<< "Flag: " << flag<< endl;
        tmp=tmp->getNext();
        cout<<1<<endl;
    }
    cout<<9<<endl;
    tmp=devList->findJob(j);
    cout<<2<<endl;
    if (flag)
    {
        cout<<3<<endl;
        if (d<=tmp->getNeed() && d <= availableDev)
        {
            work -= d;
            tmpDev[devList->findK(j)]+=d;

//            int index = tmpList->findK(j);
//            tmpList->remKth(index);
//            tmpList->addAtK(tmp, index);
            cout<<4<<endl;
        }
        else
        {
            flag=0;
        }
        
        tmp = tmpList->getFirst();
        
        cout<<5<<endl;
        cout<<tmpList->getSize()<<endl;
        for (int i = 0; i < tmpList->getSize(); i++)
        {
            finish[i] = 0;
            if (finish[i] == 0 & tmp->getNeed()-d <= work)
            {
                work += tmpDev[i];
                finish[i] = 1;
            } else
            {
                flag = 0;
            }
            tmp = tmp->getNext();
            cout<<6<<endl;
        }
    }
    
    cout<<7<<endl;
    return flag;
    
}


int main(int argc, char** argv)
{
    // loop through file
    // if line starts with C
    // Send line to C method
    // if line starts with A
    // Send line to A method
    // if line starts with Q
    // Send line to Q method
    // if line starts with L
    // Send line to L method
    // if line starts with D
    // Send line to D method

    FILE *pToFile = fopen("input.txt", "r");
    int line = 0;
    char input[512];
    char file[40][512];
    while (fgets(input, 512, pToFile)&& read)
    {
        //cout<<input<<endl;
        for (int i =0;i<512;i++){
            file[line][i]=input[i];
        }
        line++;
    }

    int line2 = 0;
    cout<< "poop: "<< file[line2]<< endl;
    while(line2 < line && quit ==0){
        cout << "Time: " << Time << endl;
        cout<<"CPU BEFORE "<<endl;
        if (runProc)
            runProc->printJob();
        cout<< endl;
        run();
        cout<<"CPU"<<endl;
        if (runProc)
            runProc->printJob();
        cout<< endl;
        if (file[line2][0] == 'C')
        {
            //cout << "a" << endl;
            Ccommand(file[line2]);
        } else if (file[line2][0] == 'Q')
        {
            Qcommand(file[line2]);
        } else if (file[line2][0] == 'A')
        {
            Acommand(file[line2]);
        } else if (file[line2][0] == 'L')
        {
            Lcommand(file[line2]);
        } else if (file[line2][0] == 'D')
        {
            Dcommand(file[line2]);
        }
        if(read){
            line2++;
        }
        
        Time++;
        cout<< "Available devices: " <<availableDev<< endl;
        cout<< "print RQ"<<endl;
        rq->printSLL();
        cout<< "wait queue"<< endl;
        wq->printSLL();
        cout<<"DEVICE LIST"<<endl;
        devList->printSLL();
        
        
    }
    //rq->printSLL();
    cout<< "TIME: "<< Time << endl;

    cout << "done" << endl;
    cout << "countRQ:" << rq->getSize() << endl;
    cout << endl;
    //hq2->printSLL();

    return (EXIT_SUCCESS);
}
