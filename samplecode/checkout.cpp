/* 
 * File: checkout.cpp 
 * ------------------ 
 * This program simulates a checkout line, such as one you 
 * might encounter in a grocery store.  Customers arrive at 
 * the checkout stand and get in line.  Those customers wait 
 * in the line until the cashier is free, at which point 
 * they are served and occupy the cashier for a randomly 
 * chosen period of time.  After the service time is complete, 
 * the cashier is free to serve the next customer in the line. 
 * 
 * The waiting line is represented by a Queue<int> in which the 
 * integer value stored in the queue is the time unit in which 
 * that customer arrived.  Storing this time makes it possible 
 * to determine the average waiting time for each customer. 
 * 
 * In each unit of time, up to the parameter SIMULATION_TIME, 
 * the following operations are performed: 
 * 
 * 1. Determine whether a new customer has arrived. 
 *    New customers arrive randomly, with a probability 
 *    determined by the parameter ARRIVAL_PROBABILITY. 
 * 
 * 2. If the cashier is busy, note that the cashier has 
 *    spent another minute with that customer.  Eventually, 
 *    the customer's time request is satisfied, which frees 
 *    the cashier. 
 * 
 * 3. If the cashier is free, serve the next customer in line. 
 *    The service time is taken to be a random period between 
 *    MIN_SERVICE_TIME and MAX_SERVICE_TIME. 
 * 
 * At the end of the simulation, the program displays the 
 * parameters and the following computed results: 
 * 
 * o  The number of customers served 
 * o  The average time spent in line 
 * o  The average number of customers in the line 
 */

#include "genlib.h"
#include "random.h"
#include "queue.h"
#include <iostream>
#include <iomanip>

/* Simulation parameters */
const int SIMULATION_TIME = 2000;
const double ARRIVAL_PROBABILITY = 0.10;
const int MIN_SERVICE_TIME =  5;
const int MAX_SERVICE_TIME = 15;

/* Private function prototypes */
void RunSimulation();
void ReportResults(int nServed, long totalWait, long totalLength);

/* Main program */
int main() {
    Randomize();
    RunSimulation();
    return 0;
}

/* 
 * Function: RunSimulation 
 * Usage: RunSimulation(); 
 * ----------------------- 
 * This function runs the actual simulation.  In each time unit, 
 * the program first checks to see whether a new customer arrives. 
 * Then, if the cashier is busy (indicated by a nonzero value for 
 * serviceTimeRemaining), the program decrements that variable to 
 * indicate that one more time unit has passed.  Finally, if the 
 * cashier is free, the simulation serves another customer from 
 * the queue after recording the waiting time for that customer. 
 */
void RunSimulation() {
    Queue<int> queue;
    int serviceTimeRemaining = 0;
    int nServed = 0;
    long totalWait = 0;
    long totalLength = 0;
    for (int t = 0; t < SIMULATION_TIME; t++) {
        if (RandomChance(ARRIVAL_PROBABILITY)) {
            queue.enqueue(t);
        }
        if (serviceTimeRemaining > 0) {
            serviceTimeRemaining--;
            if (serviceTimeRemaining == 0) nServed++;
        } else if (!queue.isEmpty()) {
            totalWait += t - queue.dequeue();
            serviceTimeRemaining = RandomInteger(MIN_SERVICE_TIME, MAX_SERVICE_TIME);
        }
        totalLength += queue.size();
    }
    ReportResults(nServed, totalWait, totalLength);
}

/* 
 * Function: ReportResults 
 * Usage: ReportResults(nServed, totalWait, totalLength); 
 * ------------------------------------------------------ 
 * This function reports the results of the simulation. 
 */
void ReportResults(int nServed, long totalWait, long totalLength) {
    cout << "Simulation results given the following parameters:" << endl;
    cout << fixed << setprecision(2);
    cout << "  SIMULATION_TIME:     " << setw(4) << SIMULATION_TIME << endl;
    cout << "  ARRIVAL_PROBABILITY: " << setw(7) << ARRIVAL_PROBABILITY << endl;
    cout << "  MIN_SERVICE_TIME:    " << setw(4) << MIN_SERVICE_TIME << endl;
    cout << "  MAX_SERVICE_TIME:    " << setw(4) << MAX_SERVICE_TIME << endl;
    cout << endl;
    cout << "Customers served:      " << setw(4) << nServed << endl;
    cout << "Average waiting time:  " << setw(7) << double(totalWait) / nServed << endl;
    cout << "Average queue length:  " << setw(7) << double(totalLength) / SIMULATION_TIME << endl;
}