//////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007-2012, Image Engine Design Inc. All rights reserved.
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

#include "boost/format.hpp"

#include "IECore/DespatchTypedData.h"
#include "IECore/VectorTypedData.h"
#include "IECore/TypeTraits.h"
#include "IECore/MessageHandler.h"

#include "IECoreGL/Primitive.h"
#include "IECoreGL/State.h"
#include "IECoreGL/Exception.h"
#include "IECoreGL/TypedStateComponent.h"
#include "IECoreGL/ShaderStateComponent.h"
#include "IECoreGL/Shader.h"
#include "IECoreGL/TextureUnits.h"
#include "IECoreGL/NumericTraits.h"
#include "IECoreGL/UniformFunctions.h"
#include "IECoreGL/CachedConverter.h"
#include "IECoreGL/Buffer.h"

using namespace IECoreGL;
using namespace std;
using namespace boost;
using namespace Imath;

//////////////////////////////////////////////////////////////////////////
// StateComponents
//////////////////////////////////////////////////////////////////////////

namespace IECoreGL
{

IECOREGL_TYPEDSTATECOMPONENT_SPECIALISEANDINSTANTIATE( Primitive::DrawBound, PrimitiveBoundTypeId, bool, false );
IECOREGL_TYPEDSTATECOMPONENT_SPECIALISEANDINSTANTIATE( Primitive::DrawWireframe, PrimitiveWireframeTypeId, bool, false );
IECOREGL_TYPEDSTATECOMPONENT_SPECIALISEANDINSTANTIATE( Primitive::WireframeWidth, PrimitiveWireframeWidthTypeId, float, 1.0f );
IECOREGL_TYPEDSTATECOMPONENT_SPECIALISEANDINSTANTIATE( Primitive::DrawSolid, PrimitiveSolidTypeId, bool, true );
IECOREGL_TYPEDSTATECOMPONENT_SPECIALISEANDINSTANTIATE( Primitive::DrawOutline, PrimitiveOutlineTypeId, bool, false );
IECOREGL_TYPEDSTATECOMPONENT_SPECIALISEANDINSTANTIATE( Primitive::OutlineWidth, PrimitiveOutlineWidthTypeId, float, 1.0f );
IECOREGL_TYPEDSTATECOMPONENT_SPECIALISEANDINSTANTIATE( Primitive::DrawPoints, PrimitivePointsTypeId, bool, false );
IECOREGL_TYPEDSTATECOMPONENT_SPECIALISEANDINSTANTIATE( Primitive::PointWidth, PrimitivePointWidthTypeId, float, 1.0f );
IECOREGL_TYPEDSTATECOMPONENT_SPECIALISEANDINSTANTIATE( Primitive::TransparencySort, PrimitiveTransparencySortStateComponentTypeId, bool, true );

}

//////////////////////////////////////////////////////////////////////////
// Primitive implementation
//////////////////////////////////////////////////////////////////////////

IE_CORE_DEFINERUNTIMETYPED( Primitive );

Primitive::Primitive()
{
}

Primitive::~Primitive()
{
}

void Primitive::addPrimitiveVariable( const std::string &name, const IECore::PrimitiveVariable &primVar )
{
	if ( primVar.interpolation == IECore::PrimitiveVariable::Constant )
	{
		addUniformAttribute( name, primVar.data );
	}
	else
	{
		addVertexAttribute( name, primVar.data );
	}
}

void Primitive::render( State *state ) const
{
	if( !state->isComplete() )
	{
		throw Exception( "Primitive::render called with incomplete state object." );
	}

	/// \todo Figure out how we'll do selection properly.
	GLint renderMode = 0;
	glGetIntegerv(GL_RENDER_MODE, &renderMode);
	if( renderMode == GL_SELECT )
	{
		return;
	}
	
	if( state->get<Primitive::DrawSolid>()->value() )
	{
		// the state itself will have a shader with some nice uniform parameter
		// values. we are responsible for binding this setup.
		Shader::Setup *uniformSetup = state->get<ShaderStateComponent>()->shaderSetup();
		Shader::Setup::ScopedBinding uniformBinding( *uniformSetup );
		// we then bind our own setup on top, adding in the parameters
		// stored on the primitive itself.
		const Shader *shader = uniformSetup->shader();
		const Shader::Setup *primitiveSetup = shaderSetup( shader );
		Shader::Setup::ScopedBinding primitiveBinding( *primitiveSetup );
		// then we defer to the derived class to perform the draw call.
		render( state, Primitive::DrawSolid::staticTypeId() );
	}
	
	/*if(	state->get<Primitive::DrawOutline>()->value() || state->get<Primitive::DrawWireframe>()->value() ||
		state->get<Primitive::DrawPoints>()->value() || state->get<Primitive::DrawBound>()->value() )
	{
		Shader *shader = Shader::constant();
	}*/
	
/*	Shader *shader = 0;

	GLint renderMode = 0;
	glGetIntegerv(GL_RENDER_MODE, &renderMode);
	// if GL is in select mode we don't draw the geometry with the 
	// regular shader. We use the constant shader native from GL for fast drawing.
	bool selectMode = ( renderMode == GL_SELECT );

	if( !selectMode && state->get<Primitive::DrawSolid>()->value() )
	{
		shader = state->get<ShaderStateComponent>()->shader();

		// get ready in case the derived class calls setVertexAttributesAsUniforms or setVertexAttributes.
		setupVertexAttributes( shader );

		// set constant primVars on the uniform shader parameters
		for ( AttributeMap::const_iterator it = m_uniformAttributes.begin(); it != m_uniformAttributes.end(); it++ )
		{
			try
			{
				shader->setUniformParameter( it->first, it->second );
			}
			catch( ... )
			{
			}
		}
	}

	// \todo: consider binding at the end the whole original state. Check if that is enough to eliminate these push/pop calls.
	glPushAttrib( GL_CURRENT_BIT | GL_DEPTH_BUFFER_BIT | GL_POLYGON_BIT | GL_LINE_BIT | GL_LIGHTING_BIT );

		if( depthSortRequested( state ) )
		{
			glDepthMask( false );
		}
		if( !selectMode && state->get<Primitive::DrawSolid>()->value() )
		{
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			glEnable( GL_LIGHTING );
			glDisable( GL_POLYGON_OFFSET_FILL );
			render( state, Primitive::DrawSolid::staticTypeId() );
		}

		glDisable( GL_LIGHTING );
		glActiveTexture( textureUnits()[0] );
		glDisable( GL_TEXTURE_2D );

		if( selectMode || state->get<Primitive::DrawOutline>()->value() || state->get<Primitive::DrawWireframe>()->value() ||
			state->get<Primitive::DrawPoints>()->value() || state->get<Primitive::DrawBound>()->value() )
		{
			// turn off current shader and use constant shader.
			Shader *constantShader = Shader::constant();
			constantShader->bind();
			GLint CsIndex = constantShader->uniformParameterIndex( "Cs" );

			AttributeMap::const_iterator itP = m_vertexAttributes.find( "P" );
			if ( itP != m_vertexAttributes.end() )
			{
				constantShader->setVertexParameter( "P", itP->second );
			}

			if ( selectMode )
			{
				// we use wireframe draw mode because we are not interested on binding
				// additional vertex buffers from the primitive
				render( state, Primitive::DrawWireframe::staticTypeId() );
			}
			else
			{
				if( state->get<Primitive::DrawOutline>()->value() )
				{
					glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
					glEnable( GL_POLYGON_OFFSET_LINE );
					float width = 2 * state->get<Primitive::OutlineWidth>()->value();
					glPolygonOffset( 2 * width, 1 );
					glLineWidth( width );
					constantShader->setUniformParameter( CsIndex, state->get<OutlineColorStateComponent>()->value() );
					render( state, Primitive::DrawOutline::staticTypeId() );
				}
	
				if( state->get<Primitive::DrawWireframe>()->value() )
				{
					glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
					float width = state->get<Primitive::WireframeWidth>()->value();
					glEnable( GL_POLYGON_OFFSET_LINE );
					glPolygonOffset( -1 * width, -1 );
					constantShader->setUniformParameter( CsIndex, state->get<WireframeColorStateComponent>()->value() );
					glLineWidth( width );
					render( state, Primitive::DrawWireframe::staticTypeId() );
				}
	
				if( state->get<Primitive::DrawPoints>()->value() )
				{
					glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );
					float width = state->get<Primitive::PointWidth>()->value();
					glEnable( GL_POLYGON_OFFSET_POINT );
					glPolygonOffset( -2 * width, -1 );
						glPointSize( width );
					constantShader->setUniformParameter( CsIndex, state->get<PointColorStateComponent>()->value() );
					render( state, Primitive::DrawPoints::staticTypeId() );
				}
	
				if( state->get<Primitive::DrawBound>()->value() )
				{
					Box3f b = bound();
					constantShader->setUniformParameter( CsIndex, state->get<BoundColorStateComponent>()->value() );
					glLineWidth( 1 );
					glBegin( GL_LINE_LOOP );
						glVertex3f( b.min.x, b.min.y, b.min.z );
						glVertex3f( b.max.x, b.min.y, b.min.z );
						glVertex3f( b.max.x, b.max.y, b.min.z );
						glVertex3f( b.min.x, b.max.y, b.min.z );
						glEnd();
					glBegin( GL_LINE_LOOP );
						glVertex3f( b.min.x, b.min.y, b.max.z );
						glVertex3f( b.max.x, b.min.y, b.max.z );
						glVertex3f( b.max.x, b.max.y, b.max.z );
						glVertex3f( b.min.x, b.max.y, b.max.z );
					glEnd();
						glBegin( GL_LINES );
						glVertex3f( b.min.x, b.min.y, b.min.z );
						glVertex3f( b.min.x, b.min.y, b.max.z );
						glVertex3f( b.max.x, b.min.y, b.min.z );
						glVertex3f( b.max.x, b.min.y, b.max.z );
						glVertex3f( b.max.x, b.max.y, b.min.z );
						glVertex3f( b.max.x, b.max.y, b.max.z );
						glVertex3f( b.min.x, b.max.y, b.min.z );
						glVertex3f( b.min.x, b.max.y, b.max.z );
					glEnd();
				}	
			}
		}

	glPopAttrib();
	}*/
}

void Primitive::addUniformAttribute( const std::string &name, IECore::ConstDataPtr data )
{
	m_uniformAttributes[name] = data->copy();
}

void Primitive::addVertexAttribute( const std::string &name, IECore::ConstDataPtr data )
{
	m_vertexAttributes[name] = data->copy();
}

bool Primitive::depthSortRequested( const State * state ) const
{
	return state->get<Primitive::TransparencySort>()->value() &&
		state->get<TransparentShadingStateComponent>()->value();
}

const Shader::Setup *Primitive::shaderSetup( const Shader *shader ) const
{
	for( ShaderSetupVector::const_iterator it = m_shaderSetups.begin(), eIt = m_shaderSetups.end(); it != eIt; it++ )
	{
		if( (*it)->shader() == shader )
		{
			return it->get();
		}
	}

	Shader::SetupPtr setup = new Shader::Setup( shader );
	for( AttributeMap::const_iterator it = m_vertexAttributes.begin(), eIt = m_vertexAttributes.end(); it != eIt; it++ )
	{
		setup->addVertexAttribute( it->first, it->second );
	}
	for( AttributeMap::const_iterator it = m_uniformAttributes.begin(), eIt = m_uniformAttributes.end(); it != eIt; it++ )
	{
		setup->addUniformParameter( it->first, it->second );
	}
	
	m_shaderSetups.push_back( setup );
	return setup.get();
}
