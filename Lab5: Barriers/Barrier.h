/*! \mainpage Lab 5 Barriers
    \author Ana Griga , Student Number: C00231441
    \date 19.11.2020
    \version GNU AFFERO GENERAL PUBLIC LICENSE Version 3, 19 November 2007
*/

/* Barrier.h --- Barrier.h
 * 
 * Filename: Barrier.h
 * Description: 
 * Author: Joseph
 * Maintainer: 
 * Created: Tue Jan  8 12:12:03 2019 (+0000)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Tue Jan  8 12:15:54 2019 (+0000)
 *           By: Joseph
 *     Update #: 2
 * URL: 
 * Doc URL: 
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change Log:
 * 
 * 
 */

/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Emacs.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Code: */

/*!
    \fn Barrier 
     \brief Declared mutex and semaphores.....(turnstiles)
*/
#pragma once
#include "Semaphore.h"
class Barrier
{
  int numThreads;
  Semaphore mutex{1};
  Semaphore firstTurnStile{0};
  Semaphore secondTurnStile{1};
  int count = 0;
 public:
  Barrier(int totalThreads):numThreads(totalThreads){};
  virtual ~Barrier();
  void wait(); 
  void phaseOne();
  void phaseTwo(); 
};


/* Barrier.h ends here */