/*
 *      $Id$
 *
 *      Author  Jeffrey O. Hill
 *              johill@lanl.gov
 *              505 665 1831
 *
 *      Experimental Physics and Industrial Control System (EPICS)
 *
 *      Copyright 1991, the Regents of the University of California,
 *      and the University of Chicago Board of Governors.
 *
 *      This software was produced under  U.S. Government contracts:
 *      (W-7405-ENG-36) at the Los Alamos National Laboratory,
 *      and (W-31-109-ENG-38) at Argonne National Laboratory.
 *
 *      Initial development by:
 *              The Controls and Automation Group (AT-8)
 *              Ground Test Accelerator
 *              Accelerator Technology Division
 *              Los Alamos National Laboratory
 *
 *      Co-developed with
 *              The Controls and Computing Group
 *              Accelerator Systems Division
 *              Advanced Photon Source
 *              Argonne National Laboratory
 *
 */


#ifndef caServerIIL_h
#define caServerIIL_h

#ifdef epicsExportSharedSymbols
#define caServerIIL_h_epicsExportSharedSymbols
#undef epicsExportSharedSymbols
#endif

#include "epicsGuard.h"

#ifdef caServerIIL_h_epicsExportSharedSymbols
#define epicsExportSharedSymbols
#endif

//
// caServerI::getAdapter()
//
inline caServer *caServerI::getAdapter()
{
	return &this->adapter;
}

//
// call virtual function in the interface class
//
inline caServer * caServerI::operator -> ()
{
	return this->getAdapter();
}

//
// caServerI::lookupRes()
//
inline casRes *caServerI::lookupRes(const caResId &idIn, casResType type)
{
    chronIntId      tmpId (idIn);

	epicsGuard < epicsMutex > locker ( this->mutex );
    casRes *pRes = this->chronIntIdResTable<casRes>::lookup ( tmpId );
	if ( pRes ) {
		if ( pRes->resourceType() != type ) {
			pRes = NULL;
		}
	}
	return pRes;
}

//
// find the channel associated with a resource id
//
inline casChannelI *caServerI::resIdToChannel(const caResId &idIn)
{
    casRes *pRes;

    pRes = this->lookupRes(idIn, casChanT);

    //
    // safe to cast because we have checked the type code above
    // (and we know that casChannelI derived from casRes)
    //
    return (casChannelI *) pRes;
}

//
// caServerI::installItem()
//
inline void caServerI::installItem(casRes &res)
{
    this->chronIntIdResTable<casRes>::add(res);
}

//
// caServerI::removeItem()
//
inline casRes *caServerI::removeItem(casRes &res)
{
	return this->chronIntIdResTable<casRes>::remove(res);
}

//
// caServerI::setDebugLevel()
//
inline void caServerI::setDebugLevel(unsigned debugLevelIn)
{
	this->debugLevel = debugLevelIn;
}

//
// casEventMask caServerI::valueEventMask()
//
inline casEventMask caServerI::valueEventMask() const
{
    return this->valueEvent;
}

//
// caServerI::logEventMask()
//
inline casEventMask caServerI::logEventMask() const
{
    return this->logEvent;
}

//
// caServerI::alarmEventMask()
//
inline casEventMask caServerI::alarmEventMask() const
{
    return this->alarmEvent;
}

//
// caServerI::readEventsProcessedCounter (void) const
//
inline unsigned caServerI::readEventsProcessedCounter (void) const
{
    return this->nEventsProcessed;
}

//
// caServerI::incEventsProcessedCounter (void)
//
inline void caServerI::incrEventsProcessedCounter (void)
{
    this->nEventsProcessed++;
}

//
// caServerI::clearEventsProcessedCounter (void)
//
inline void caServerI::clearEventsProcessedCounter (void)
{
    this->nEventsProcessed = 0u;
}

//
// caServerI::readEventsPostedCounter (void) const
//
inline unsigned caServerI::readEventsPostedCounter (void) const
{
    return this->nEventsPosted;
}

//
// caServerI::incEventsPostedCounter (void)
//
inline void caServerI::incrEventsPostedCounter (void)
{
    this->nEventsPosted++;
}

//
// caServerI::clearEventsPostedCounter (void)
//
inline void caServerI::clearEventsPostedCounter (void)
{
    this->nEventsPosted = 0u;
}

inline void caServerI::lock () const
{
    this->mutex.lock ();
}

inline void caServerI::unlock () const
{
    this->mutex.unlock ();
}


#endif // caServerIIL_h

