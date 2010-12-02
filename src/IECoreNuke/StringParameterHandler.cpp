//////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2010, Image Engine Design Inc. All rights reserved.
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

#include "DDImage/Knobs.h"

#include "IECore/SimpleTypedParameter.h"

#include "IECoreNuke/StringParameterHandler.h"

using namespace IECore;
using namespace IECoreNuke;

ParameterHandler::Description<StringParameterHandler> StringParameterHandler::g_description( StringParameter::staticTypeId() );

StringParameterHandler::StringParameterHandler( IECore::ParameterPtr parameter, const std::string &knobName )
	:	ParameterHandler( parameter, knobName ), m_storage( 0 ), m_knob( 0 )
{
}
		
void StringParameterHandler::knobs( DD::Image::Knob_Callback f )
{
	if( f.makeKnobs() )
	{
		m_storage = static_cast<StringParameter *>( parameter() )->typedDefaultValue().c_str();
	}

	m_knob = String_knob( f, &m_storage, knobName(), knobLabel() );
	Tooltip( f, parameter()->description() );
}

void StringParameterHandler::setParameterValue( IECore::Parameter *parameter, ValueSource valueSource )
{
	StringParameter *stringParameter = static_cast<StringParameter *>( parameter );
	if( valueSource==Storage )
	{
		stringParameter->setTypedValue( m_storage );
	}
	else
	{
		std::ostringstream s;
		m_knob->to_script( s, 0, false );
		stringParameter->setTypedValue( s.str() );
	}
}
