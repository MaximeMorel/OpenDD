//
//


//! \file physcis.h
//! \brief Physics module
//!
//! Collisions checks


#ifndef PHYSICS_H
#define PHYSICS_H


// system includes

// user includes
#include "car.h"
#include "particle.h"
#include "vector.h"
#include "level.h"


//! \fn bool checkCollisionWorld( SCar* c )
//! \brief Simple collision check.
//!
//! Make a simple and imprecise collision check with walls,
//! and after call checkCollisionWorldAdv for a more precise check.
extern p_Vector2f checkCollisionWorld( SCar* c, SLevel* l );


//! \fn checkCollisionCar( SCar* c1, SCar* c2 )
//! \brief Simple collision check between 2 cars.
//!
//! Make a simple and imprecise collision check between 2 cars,
//! and after call checkCollisionCarAdv for a more precise check.
extern p_Vector2f checkCollisionCar( SCar* c1, SCar* c2 );


#endif // PHYSICS_H
