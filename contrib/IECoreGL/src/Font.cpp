//////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2008-2009, Image Engine Design Inc. All rights reserved.
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


#include "IECoreGL/Font.h"
#include "IECoreGL/ToGLMeshConverter.h"
#include "IECoreGL/MeshPrimitive.h"

#include "IECore/MeshPrimitive.h"

using namespace IECoreGL;
using namespace std;
using namespace boost;

IE_CORE_DEFINERUNTIMETYPED( Font );

Font::Font( IECore::FontPtr font )
	:	m_font( font ), m_texture( 0 )
{
}

Font::~Font()
{
}

IECore::FontPtr Font::coreFont()
{
	return m_font;
}
		
ConstMeshPrimitivePtr Font::mesh( char c )
{
	MeshMap::const_iterator it = m_meshes.find( c );
	if( it!=m_meshes.end() )
	{
		return it->second;
	}
	
	ToGLMeshConverter converter( m_font->mesh( c ) );
	ConstMeshPrimitivePtr mesh = boost::static_pointer_cast<const MeshPrimitive>( converter.convert() );
	m_meshes[c] = mesh;
	
	return mesh;
}
		
ConstAlphaTexturePtr Font::texture()
{
	if( m_texture )
	{
		return m_texture;
	}
	
	IECore::ConstImagePrimitivePtr image = m_font->image();
	
	IECore::ConstFloatVectorDataPtr y = image->getChannel<float>( "Y" );
	Imath::V2i s = image->getDataWindow().size() + Imath::V2i( 1 );
	m_texture = new AlphaTexture( s.x, s.y, y );
	return m_texture;
}
