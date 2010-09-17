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

#include "GU/GU_PrimPoly.h"

#include "ToHoudiniPolygonsConverter.h"

using namespace IECore;
using namespace IECoreHoudini;

IE_CORE_DEFINERUNTIMETYPED( ToHoudiniPolygonsConverter );

ToHoudiniGeometryConverter::Description<ToHoudiniPolygonsConverter> ToHoudiniPolygonsConverter::m_description( MeshPrimitiveTypeId );

ToHoudiniPolygonsConverter::ToHoudiniPolygonsConverter( const Primitive *primitive ) :
	ToHoudiniGeometryConverter( primitive, "Converts an IECore::MeshPrimitive to a Houdini GU_Detail." )
{
}

ToHoudiniPolygonsConverter::~ToHoudiniPolygonsConverter()
{
}

bool ToHoudiniPolygonsConverter::doPrimitiveConversion( const Primitive *primitive, GU_Detail *geo, IECore::ConstCompoundObjectPtr operands ) const
{
	const MeshPrimitive *mesh = static_cast<const MeshPrimitive *>( primitive );
	if ( !mesh )
	{
		return false;
	}
	
	GEO_PointList newPoints = appendPoints( geo, mesh->variableData<V3fVectorData>( "P" ) );
	if ( !newPoints.entries() )
	{
		return false;
	}
	
	GEO_PrimList newPrims;
	const std::vector<int> &vertexIds = mesh->vertexIds()->readable();
	const std::vector<int> &verticesPerFace = mesh->verticesPerFace()->readable();
	
	size_t vertCount = 0;
	for ( size_t f=0; f < verticesPerFace.size(); f++ )
	{
		GU_PrimPoly *poly = GU_PrimPoly::build( geo, 0, GU_POLY_CLOSED, 0 );
		newPrims.append( poly );
		
		for ( size_t v=0; v < verticesPerFace[f]; v++ )
		{
			poly->appendVertex( newPoints[ vertexIds[ vertCount + verticesPerFace[f] - 1 - v ] ] );
		}
		
		vertCount += verticesPerFace[f];
	}
	
	transferAttribs( mesh, geo, &newPoints, &newPrims );
	
	return true;
}
