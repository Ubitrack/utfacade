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
* Simple datatypes for the \c SimpleFacade
*
* @author Ulrich Eck <ueck@net-labs.de>
*/
#ifndef __UBITRACK_FACADE_BASICFACADECOMPONENTSPRIVATE_H_INCLUDED__
#define __UBITRACK_FACADE_BASICFACADECOMPONENTSPRIVATE_H_INCLUDED__

#include "BasicFacadeTypesPrivate.h"
#include "BasicFacadeComponents.h"
#include "BasicFacadePrivate.h"

#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>

// not nice having a relative include here ...
// should deal with CMAKE and include the appropriate directory
#include "../utComponents/ApplicationPullSink.h"
#include "../utComponents/ApplicationPushSink.h"
#include "../utComponents/ApplicationPullSource.h"
#include "../utComponents/ApplicationPushSource.h"
#include "AdvancedFacade.h"


namespace Ubitrack { namespace Facade {

        /*
        * ApplicationPullSink wrapper
        */
        template< typename BMT >
        class BasicPullSinkPrivate {
        public:
            typedef typename BasicMeasurementTypeTrait< BMT >::ubitrack_measurement_type measurement_type;
            typedef typename Components::ApplicationPullSink< measurement_type > component_type;

            BasicPullSinkPrivate(basic_facade_string_type& name, BasicFacadePrivate* facade)
            : m_component(facade->componentByName< component_type >(name)) {}

            ~BasicPullSinkPrivate() {
                m_component.clear();
            }

            std::shared_ptr<BMT> get(unsigned long long int const ts) {
                std::shared_ptr<BMT> bm;
                if (m_component) {
                    auto m = new typename BasicMeasurementTypeTrait< BMT >::private_measurement_type(m_component->get(ts));
                    bm = std::make_shared<BMT>(ts, m);
                }
                return bm;
            }

            boost::shared_ptr< component_type >  m_component;
        };

        /*
        * ApplicationPushSink wrapper
        */
        template< typename BMT >
        class BasicPushSinkPrivate {
        public:
            typedef typename BasicMeasurementTypeTrait< BMT >::ubitrack_measurement_type measurement_type;
            typedef typename Components::ApplicationPushSink< measurement_type > component_type;

            BasicPushSinkPrivate(basic_facade_string_type& name, BasicFacadePrivate* facade)
                    : m_component(facade->componentByName< component_type >(name)) {}

            ~BasicPushSinkPrivate() {
                m_component.clear();
            }

            void registerCallback(typename BasicPushSink< BMT >::CallbackType cb) {
                m_slot = cb;
                m_component->setCallback(boost::bind( &BasicPushSinkPrivate::pushHandler, this, _1 ) );
            }

            void unregisterCallback() {
                if (m_component) {
                    m_component->setCallback(NULL);
                    m_slot = NULL;
                }
            }

            void pushHandler(const measurement_type& m) {
                if (m_slot) {
                    BMT bm = BMT(m.time(), new typename BasicMeasurementTypeTrait< BMT >::private_measurement_type(m));
                    m_slot( bm );
                }
            }

            boost::shared_ptr< component_type >  m_component;
            typename BasicPushSink< BMT >::CallbackType m_slot;
        };

        /*
        * ApplicationPullSource wrapper
        */
        template< typename BMT >
        class BasicPullSourcePrivate {
        public:
            typedef typename BasicMeasurementTypeTrait< BMT >::ubitrack_measurement_type measurement_type;
            typedef typename Components::ApplicationPullSource< measurement_type > component_type;

            BasicPullSourcePrivate(basic_facade_string_type& name, BasicFacadePrivate* facade)
                    : m_component(facade->componentByName< component_type >(name)) {}

            ~BasicPullSourcePrivate() {
                m_component.clear();
            }

            void registerCallback(typename BasicPullSource< BMT >::CallbackType cb) {
                m_slot = cb;
                m_component->setCallback(boost::bind( &BasicPullSourcePrivate::pullHandler, this, _1 ) );
            }

            void unregisterCallback() {
                if (m_component) {
                    m_component->setCallback(NULL);
                    m_slot = NULL;
                }
            }

            const measurement_type pullHandler(unsigned long long int const ts) {
                if (m_slot) {
                    BMT* bm = m_slot(ts);
                    if (bm->isValid()) {
                        // demeters law ...
                        measurement_type m = bm->m_pPrivate->m_measurement;
                        return m;
                    }
                }
                UBITRACK_THROW( "ApplicationPullSource has no producer connected" );
            }

            boost::shared_ptr< component_type >  m_component;
            typename BasicPullSource< BMT >::CallbackType m_slot;
        };

        /*
        * ApplicationPushSource wrapper
        */
        template< typename BMT >
        class BasicPushSourcePrivate {
        public:
            typedef typename BasicMeasurementTypeTrait< BMT >::ubitrack_measurement_type measurement_type;
            typedef typename Components::ApplicationPushSource< measurement_type > component_type;

            BasicPushSourcePrivate(basic_facade_string_type& name, BasicFacadePrivate* facade)
                    : m_component(facade->componentByName< component_type >(name)) {}

            ~BasicPushSourcePrivate() {
                m_component.clear();
            }

            void send(const BMT& bm) {
                if (m_component) {
                    if (bm.isValid()) {
                        // demeters law ...
                        measurement_type m = bm.m_pPrivate->m_measurement;
                        m_component->send( m );
                    }
                }
            }

            boost::shared_ptr< component_type >  m_component;
        };


    }
} // namespace Ubitrack::Facade

#endif
