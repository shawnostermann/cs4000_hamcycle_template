#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <mpi.h> 
#include "hamcycle.h"

using namespace std;

// shared global path for efficiency
int *path = NULL;

bool isSafe(int n, int pos) {
   if (g [path[pos-1]][n] == 0) {
      return false;
   }

   for (int i = 0; i < pos; i++) {
      if (path[i] == n)
         return false;
   }
   return true;
}

bool hamiltonianCycle(int pos) {
   //If all vertices are included in Hamiltonian Cycle
   if (pos == dimension) {
      return(g[ path[pos-1] ][ path[0] ] == 1);  // can I get from end of path back to beginning?
   }
   for (int n = 1; n < dimension; n++) {
      if (isSafe(n, pos)) { //Check if this vertex can be added to Hamiltonian Cycle
         path[pos] = n;
         //recur to construct rest of the path
         if (hamiltonianCycle (pos+1) == true)
            return true;
         path[pos] = -1; //remove vertex if it doesn’t lead to the solution
      }
   }
   return false;
}

void displaytheSolution() {
   cout<<"Cycle Exists: ";
   for (int i = 0; i < dimension; i++)
      cout<<path[i]<<" ";
   cout<< path[0]<<endl;
}


void printMatrix() {
   for (int row=0; row < dimension; ++row) {
      for (int col=0; col < dimension; ++col) {
         if (g[row][col])
            cout << row << " <--> " << col << endl;
      }
   }
}


bool hamCycle() {
   path = new int[dimension];
   for (int i = 0; i < dimension; i++) {
      path[i] = -1;
   }
   
   //put vertex 0 as the first vertex in the path. If there is a Hamiltonian Cycle, then the path can be 
   //started from any point
   //of the cycle as the graph is undirected
   path[0] = 0;
   if (debug) printMatrix();

   cout<<proc_rank << "/" << num_procs << ": ";
   if (hamiltonianCycle(1) == false) {
      cout << "Cycle does not exist\n";
      return false;
   } 
   displaytheSolution();
   return true;
}
