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

#include "boost/python.hpp"
#include "boost/format.hpp"

#include "DDImage/Op.h"
#include "DDImage/Knobs.h"
#include "DDImage/Knob.h"

#include "IECore/MessageHandler.h"
#include "IECore/CompoundParameter.h"
#include "IECorePython/ScopedGILLock.h"

#include "IECoreNuke/ParameterisedHolder.h"
#include "IECoreNuke/ParameterHandler.h"

using namespace std;
using namespace boost::python;
using namespace IECore;
using namespace IECoreNuke;

template<typename BaseType>
ParameterisedHolder<BaseType>::ParameterisedHolder( Node *node )
	:	BaseType( node ),
		m_className( 0 ),
		m_classNameKnob( 0 ),
		m_classVersion( -1 ),
		m_classVersionKnob( 0 ),
		m_classSearchPathEnvVar( 0 ),
		m_classSearchPathEnvVarKnob( 0 ),
		m_classLoad( 0 ),
		m_classLoadKnob( 0 ),
		m_classReloadKnob( 0 ),
		m_parameterised( 0 ),
		m_parameterHandler( 0 ),
		m_numParameterKnobs( 0 )
{
	
}

template<typename BaseType>
ParameterisedHolder<BaseType>::~ParameterisedHolder()
{
}

template<typename BaseType>
void ParameterisedHolder<BaseType>::knobs( DD::Image::Knob_Callback f )
{	
	BaseType::knobs( f );
	
	m_classNameKnob = String_knob( f, &m_className, "className", "Class Name" );
	
	m_classVersionKnob = Int_knob( f, &m_classVersion, "classVersion", "Class Version" );
	
	m_classSearchPathEnvVarKnob = String_knob( f, &m_classSearchPathEnvVar, "classSearchPathEnvVar", "SearchPath" );
	
	m_classLoadKnob = Int_knob( f, &m_classLoad, "classLoad" );
	SetFlags( f, DD::Image::Knob::KNOB_CHANGED_ALWAYS /*| DD::Image::Knob::HIDDEN*/ );
	
	m_classReloadKnob = Button( f, "classReload", "Reload" );
		
	BaseType::add_knobs( parameterKnobs, this, f );
}

template<typename BaseType>
int ParameterisedHolder<BaseType>::knob_changed( DD::Image::Knob *knob )
{
	
	if( knob==m_classLoadKnob || knob==m_classReloadKnob )
	{
		// reload the class, or load a new class
	
		m_parameterised = loadClass( m_classNameKnob->get_text(), (int)m_classVersionKnob->get_value(), m_classSearchPathEnvVarKnob->get_text(), knob==m_classReloadKnob );
		
		// get a new ParameterHandler
		
		m_parameterHandler = 0;
		if( m_parameterised )
		{
			ParameterisedInterface *parameterisedInterface = dynamic_cast<ParameterisedInterface *>( m_parameterised.get() );
			if( parameterisedInterface )
			{
				m_parameterHandler = ParameterHandler::create( parameterisedInterface->parameters(), "parm" );
			}
		}
		
		// and regenerate the knobs used to represent the parameters
		
		// in an ideal world, nuke would notice when the new knobs are the same name/type as the old ones,
		// and keep the values and animation and wotnot - they even have a comment in the docs saying how
		// nice that would be. but that doesn't exist right now, so we do it ourselves. we're doing
		// it here rather than complicating the ParameterHandler mechanism in the hope that in the future
		// Nuke will do it for us and we can then just remove this little bit of code rather than rejig
		// the actual API.
		
		std::map<std::string, std::string> knobScripts;
		DD::Image::Knob *pKnob = 0;
		for( int i=0; (pKnob = BaseType::knob( i )); i++ )
		{
			if( pKnob->name().compare( 0, 5, "parm_" ) == 0 )
			{
				ostringstream ss;
				pKnob->to_script( ss, 0, false );
				knobScripts[pKnob->name()] = ss.str();
			}
		}
		
		m_numParameterKnobs = replace_knobs( m_classReloadKnob, m_numParameterKnobs, parameterKnobs, this );
		
		for( int i=0; (pKnob = BaseType::knob( i )); i++ )
		{
			std::map<std::string, std::string>::const_iterator it = knobScripts.find( pKnob->name() );
			if( it!=knobScripts.end() )
			{
				pKnob->from_script( it->second.c_str() );			
			}
		}
		
		return 1;
	}
	
	return BaseType::knob_changed( knob );
}

template<typename BaseType>
IECore::RunTimeTypedPtr ParameterisedHolder<BaseType>::getParameterised()
{
	return m_parameterised;
}

template<typename BaseType>
void ParameterisedHolder<BaseType>::setParameterValues()
{
	if( m_parameterHandler )
	{
		m_parameterHandler->setParameterValue();
	}
}

template<typename BaseType>
void ParameterisedHolder<BaseType>::parameterKnobs( void *that, DD::Image::Knob_Callback f )
{
	ParameterisedHolder *parameterisedHolder = static_cast<ParameterisedHolder *>( that );
	if( parameterisedHolder->m_parameterHandler )
	{
		parameterisedHolder->m_parameterHandler->knobs( f );
	}
}

template<typename BaseType>
IECore::RunTimeTypedPtr ParameterisedHolder<BaseType>::loadClass( const char *className, int classVersion, const char *searchPathEnvVar, bool refreshLoader )
{
	IECorePython::ScopedGILLock gilLock;

	try
	{
		object mainModule = object( handle<>( borrowed( PyImport_AddModule( "__main__" ) ) ) );
		object mainModuleNamespace = mainModule.attr( "__dict__" );
	
		// first make sure IECore is imported, and the loader is refreshed if required
	
		string toExecute = "import IECore\n";
		if( refreshLoader )
		{
			toExecute += ( boost::format( "IECore.ClassLoader.defaultLoader( \"%s\" ).refresh()\n" ) % searchPathEnvVar ).str();
		}
		
		handle<> resultHandle( PyRun_String(
			toExecute.c_str(),
			Py_file_input,
			mainModuleNamespace.ptr(),
			mainModuleNamespace.ptr()
		) );
	
		// then load an instance of the class
	
		toExecute = ( boost::format(
			"IECore.ClassLoader.defaultLoader( \"%s\" ).load( \"%s\", %d )()\n"
			) % searchPathEnvVar % className % classVersion
		).str();
	
		handle<> classHandle( PyRun_String(
			toExecute.c_str(),
			Py_eval_input,
			mainModuleNamespace.ptr(),
			mainModuleNamespace.ptr() )
		);
		
		object result( classHandle );
		return extract<RunTimeTypedPtr>( result )();
	}
	catch( error_already_set & )
	{
		msg( Msg::Error, "ParameterisedHolder::loadClass",
			boost::format( "Unable to load class \"%s\" version %d into node %s." ) % className % classVersion % BaseType::node_name() );

		PyErr_Print();
	}
	catch( ... )
	{
		msg( Msg::Error, "ParameterisedHolder::loadClass",
			boost::format( "Unable to load class \"%s\" version %d into node %s." ) % className % classVersion % BaseType::node_name() );
	}
	return 0;

}

// explicit instantiation

template class ParameterisedHolder<DD::Image::Op>;

