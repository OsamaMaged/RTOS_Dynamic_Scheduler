# RTOS_Dynamic_Scheduler

Nearly all programs have some alternating processes of crunching the CPU and some form of waiting for (I/O).
Even a small memory fetch can take a long time compared to the speed of core processers.
The time spent waiting for (I/O) operations are wasted on a simple machine running a single processer core and those cycles are wasted forever.
So When a process is waiting (expecting) an (I/O) operation or being idle for some time ,
the scheduler allows another process to be executed in this time performing a context switch , making more efficient use of the CPU cycles .
Before we go into the definition of the rate mono atomic algorithm we should know some basic information and concepts related the CPU scheduling and
then we will see different real time CPU scheduling Algorithms and the most important optimal algorithm the “RMA”.

First,
the CPU scheduler’s job is selecting a process from the ready queue to run while another is idle (wasting CPU time).
The algorithms used to select the processes from the “Ready” queues need not to be a “FIFO” queues. There are a lot of other algorithms we can pick and adjust them.  

Second,
There are 4 conditions from which scheduling is decided:

1. Process switching from the “Running” state to the “Waiting” state, as for an I/O request.
2. Switching from “Running” state to “Ready” state, as in response of an interrupt.
3. Switching from “Waiting” state to “Ready” state, as when an I/O operation is Completed or when returning  from a wait( ) statement.
4. Process terminating (ending of a process normally).

Note:
A Selection for a new process is a must in the first and the fourth conditions ,
but in the second and the third conditions , the scheduler can either continue the current process or switching and selecting a different one.


There are two types of scheduling:

1.	Non Preemptive: As the first and fourth conditions where a process starts and keep running until it finishes or blocks voluntarily.

2.	Preemptive: As the second and the third conditions where scheduler decides to force a context switch while a process is running according to some algorithm.

Here we are using the dynamic one.

Note:
One of the problems preemptive scheduling can cause is that when 2 processes are sharing data ,processes can get interrupted while others are updating the shared data.
Another problem is when the system is executing a system call and the preemption happens ,
here most of the systems deal with it by blocking the process until the system call finishes or gets blocked before the preemption.
But this is still a problem when it comes to Real time Systems as the response time can’t be guaranteed in this case.

