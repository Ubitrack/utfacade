/*
 * Ubitrack - Library for Ubiquitous Tracking
 * Copyright 2006, Technische Universitaet Muenchen, and individual
 * contributors as indicated by the @authors tag. See the
 * copyright.txt in the distribution for a full listing of individual
 * contributors.
 *
 * This is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this software; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA, or see the FSF site: http://www.fsf.org.
 */

/**
* @ingroup api
* @file
* Implements a basic interface to the ubitrack dataflow network.
*
* @author Ulrich Eck <ueck@net-labs.de
*/
#include <utFacade/Config.h>
#ifdef ENABLE_BASICFACADE

#include "BasicFacadeComponentsPrivate.h"

namespace Ubitrack {
    namespace Facade {


        // BasicPullSink

        template< typename BMT >
        BasicPullSink< BMT >::BasicPullSink(basic_facade_string_type& name, BasicFacadePrivate* _private)
                : m_pPrivate(new BasicPullSinkPrivate< BMT >(name, _private))
        {

        }

        template< typename BMT >
        BasicPullSink< BMT >::~BasicPullSink() {
            if (m_pPrivate) {
                free(m_pPrivate);
            }
        }

        template< typename BMT >
        BMT* BasicPullSink< BMT >::get(unsigned long long int const ts) {
            if (m_pPrivate) {
                return m_pPrivate->get(ts);
            }
            return NULL;
        }

        // BasicPushSink

        template< typename BMT >
        BasicPushSink< BMT >::BasicPushSink(basic_facade_string_type& name, BasicFacadePrivate* _private)
                : m_pPrivate(new BasicPushSinkPrivate< BMT >(name, _private)) {

        }

        template< typename BMT >
        BasicPushSink< BMT >::~BasicPushSink() {
            if (m_pPrivate) {
                free(m_pPrivate);
            }
        }

        template< typename BMT >
        void BasicPushSink< BMT >::registerCallback(CallbackType cb) {
            if (m_pPrivate) {
                m_pPrivate->registerCallback(cb);
            }
        }

        template< typename BMT >
        void BasicPushSink< BMT >::unregisterCallback() {
            if (m_pPrivate) {
                m_pPrivate->unregisterCallback();
            }
        }

        // BasicPullSource

        template< typename BMT >
        BasicPullSource< BMT >::BasicPullSource(basic_facade_string_type& name, BasicFacadePrivate* _private)
                : m_pPrivate(new BasicPullSourcePrivate< BMT >(name, _private)) {

        }

        template< typename BMT >
        BasicPullSource< BMT >::~BasicPullSource() {
            if (m_pPrivate) {
                free(m_pPrivate);
            }
        }

        template< typename BMT >
        void BasicPullSource< BMT >::registerCallback(CallbackType cb) {
            if (m_pPrivate) {
                m_pPrivate->registerCallback(cb);
            }
        }

        template< typename BMT >
        void BasicPullSource< BMT >::unregisterCallback() {
            if (m_pPrivate) {
                m_pPrivate->unregisterCallback();
            }
        }

        // BasicPushSource

        template< typename BMT >
        BasicPushSource< BMT >::BasicPushSource(basic_facade_string_type& name, BasicFacadePrivate* _private)
                : m_pPrivate(new BasicPushSourcePrivate< BMT >(name, _private)) {

        }

        template< typename BMT >
        BasicPushSource< BMT >::~BasicPushSource() {
            if (m_pPrivate) {
                free(m_pPrivate);
            }
        }

        template< typename BMT >
        void BasicPushSource< BMT >::send(const BMT &bm) {
            if (m_pPrivate) {
                m_pPrivate->send(bm);
            }
        }

        template class BasicPullSink<BasicScalarIntMeasurement>;

        template class BasicPushSink<BasicScalarIntMeasurement>;

        template class BasicPullSource<BasicScalarIntMeasurement>;

        template class BasicPushSource<BasicScalarIntMeasurement>;
    }
}
#endif // ENABLE_BASICFACADE