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
#ifndef __UBITRACK_FACADE_BASICFACADECOMPONENTS_H_INCLUDED__
#define __UBITRACK_FACADE_BASICFACADECOMPONENTS_H_INCLUDED__

#include "BasicFacadeTypes.h"
#include <functional>
#include <memory>

namespace Ubitrack { namespace Facade {

        // forward declarations
        class BasicFacadePrivate;

        template< typename BMT >
        class BasicPullSinkPrivate;

        template< typename BMT >
        class BasicPushSinkPrivate;

        template< typename BMT >
        class BasicPullSourcePrivate;

        template< typename BMT >
        class BasicPushSourcePrivate;

        template< typename BMT >
        class BasicPullSink {

        public:
            typedef BMT MeasurementType;

            BasicPullSink(basic_facade_string_type& name, BasicFacadePrivate* _private);
            ~BasicPullSink();
            std::shared_ptr<BMT> get(unsigned long long int const ts);

        private:
            BasicPullSinkPrivate<BMT>* m_pPrivate;
        };

        template< typename BMT >
        class BasicPushSink {

        public:
            typedef BMT MeasurementType;
            typedef std::function<void(MeasurementType&)> CallbackType;

            BasicPushSink(basic_facade_string_type& name, BasicFacadePrivate* _private);
            ~BasicPushSink();
            void registerCallback(CallbackType cb);
            void unregisterCallback();

        private:
            BasicPushSinkPrivate<BMT>* m_pPrivate;
        };

        template< typename BMT >
        class BasicPullSource {

        public:
            typedef BMT MeasurementType;
            typedef std::function< MeasurementType* (unsigned long long int const)> CallbackType;

            BasicPullSource(basic_facade_string_type& name, BasicFacadePrivate* _private);
            ~BasicPullSource();
            void registerCallback(CallbackType cb);
            void unregisterCallback();

        private:
            BasicPullSourcePrivate<BMT>* m_pPrivate;
        };

        template< typename BMT >
        class BasicPushSource {

        public:
            typedef BMT MeasurementType;

            BasicPushSource(basic_facade_string_type& name, BasicFacadePrivate* _private);
            ~BasicPushSource();
            void send(const BMT &measurement);

        private:
            BasicPushSourcePrivate<BMT>* m_pPrivate;
        };

    }
} // namespace Ubitrack::Facade

#endif
