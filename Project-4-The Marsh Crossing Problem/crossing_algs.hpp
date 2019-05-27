///////////////////////////////////////////////////////////////////////////////
// crossing_algs.hpp
//
// Algorithms that solve the marsh crossing problem.
//
// All of the TODO sections for this project reside in this file.
//
// This file builds on crossing_types.hpp, so you should familiarize yourself
// with that file before working on this file.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cassert>
#include <iostream>


#include "crossing_types.hpp"

namespace crossing {
// Solve the marsh crossing problem for the given grid, using an exhaustive
// optimization algorithm.
//
// This algorithm is expected to run in exponential time, so the grid's
// width+height must be small enough to fit in a 64-bit int; this is enforced
// with an assertion.
//
// The grid must be non-empty.
unsigned int marsh_crossing_exhaustive(const grid& setting) {

  // grid must be non-empty.
  assert(setting.rows() > 0);
  assert(setting.columns() > 0);

  // Compute the path length, and check that it is legal.
  const size_t steps = setting.rows() + setting.columns() - 2;
  assert(steps < 64);

  bool valid_candidate = true;
  unsigned int count_paths = 0;
  
  for (unsigned int bits = 0; bits <= pow(2, steps)-1; bits++)
  {
	  path candidate(setting);
	  for (unsigned int k = 0; k <= steps - 1; k++)
	  {
		  auto bit = (bits >> k) & 1;
		  step_direction dir;
		  // set direction
		  if (bit == 1)
		  {
			  dir = STEP_DIRECTION_RIGHT;
		  }
		  else
		  {
			  dir = STEP_DIRECTION_DOWN;
		  }
		  // test is direction valid
		  if (candidate.is_step_valid(dir))
		  {
			  candidate.add_step(dir);
			  valid_candidate = true;
		  }
		  // if invalid step then path invalid
		  // exit inner loop
		  else
		  {
			  valid_candidate = false;
			  break;
		  }

	  }
	  // incrament only if valid path
	  if (valid_candidate)
	  {
		  count_paths++;
	  }
	  
	  
  }
  return count_paths;
}

// Solve the marsh crossing problem for the given grid, using a dynamic
// programming algorithm.
//
// The grid must be non-empty.
unsigned int marsh_crossing_dyn_prog(const grid& setting) {

  // grid must be non-empty.
  assert(setting.rows() > 0);
  assert(setting.columns() > 0);

  // TODO: implement the dynamic programming algorithm, then delete this
  // comment.
 

  unsigned int A[100][100];
  // base case
  A[0][0] = 1;
  unsigned int from_a, from_l;

  for (unsigned int i = 0; i <= setting.rows() - 1; i++)
  {
	  for (unsigned int j = 0; j <= setting.columns() - 1; j++)
	  {
		 //skips base case because A[0][0] already initialized
		  if(!i && !j) continue;
		  
		  if (setting.get(i, j) == CELL_THICKET)
		  {
			  A[i][j] = 0;
			  continue;
		  }
		  
		  from_a = from_l = 0;
		   
		  if (i > 0 && A[i - 1][j] ) 
		  {
		          from_a = A[i - 1][j];
		  }
		  if (j > 0 && A[i][j - 1])
		  {
		          from_l = A[i][j - 1];
		  }
       
		  A[i][j] = from_a + from_l;
		    		
	  }
  }
  return A[setting.rows()-1][setting.columns()-1];
}

}
