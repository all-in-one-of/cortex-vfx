//////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2012, Image Engine Design Inc. All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are
//  met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//
//     * Neither the name of Image Engine Design nor the names of any
//       other contributors to this software may be used to endorse or
//       promote products derived from this software without specific prior
//       written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
//  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
//  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
//  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//////////////////////////////////////////////////////////////////////////

#ifndef IECOREHOUDINI_MESSAGEHANDLER_H
#define IECOREHOUDINI_MESSAGEHANDLER_H

#include "boost/function.hpp"

#include "IECore/MessageHandler.h"

namespace IECoreHoudini
{

/// A generic MessageHandler for Houdini.
/// \todo: make this threadsafe
class MessageHandler : public IECore::MessageHandler
{

	public :

		IE_CORE_DECLAREMEMBERPTR( MessageHandler );
		
		typedef boost::function<void ( const char *m )> HandlerFn;
		
		MessageHandler( HandlerFn errorFn = 0, HandlerFn warningFn = 0, HandlerFn infoFn = 0, HandlerFn debugFn = 0 );
		virtual ~MessageHandler();
		
		virtual void handle( Level level, const std::string &context, const std::string &message );
		
	private :
		
		HandlerFn m_errorFn;
		HandlerFn m_warningFn;
		HandlerFn m_infoFn;
		HandlerFn m_debugFn;

};

IE_CORE_DECLAREPTR( MessageHandler );

} // namespace IECoreHoudini

#endif // IECOREHOUDINI_MESSAGEHANDLER_H
