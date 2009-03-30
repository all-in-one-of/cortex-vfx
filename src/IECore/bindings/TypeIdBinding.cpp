//////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007-2009, Image Engine Design Inc. All rights reserved.
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

#include "IECore/TypeIds.h"
#include "IECore/bindings/TypeIdBinding.h"

using namespace boost::python;

namespace IECore
{

void bindTypeId()
{
	enum_<TypeId>("TypeId")
		.value("Invalid", InvalidTypeId )
		.value("Object", ObjectTypeId )
		.value("Data", DataTypeId )
		.value("FloatVectorData", FloatVectorDataTypeId )
		.value("DoubleVectorData", DoubleVectorDataTypeId )
		.value("IntVectorData", IntVectorDataTypeId )
		.value("UIntVectorData", UIntVectorDataTypeId )
		.value("CharVectorData", CharVectorDataTypeId )
		.value("UCharVectorData", UCharVectorDataTypeId )
		.value("V2fVectorData", V2fVectorDataTypeId )
		.value("V2dVectorData", V2dVectorDataTypeId )
		.value("V3fVectorData", V3fVectorDataTypeId )
		.value("V3dVectorData", V3dVectorDataTypeId )
		.value("Box3fVectorData", Box3fVectorDataTypeId )
		.value("Box3dVectorData", Box3dVectorDataTypeId )
		.value("M33fVectorData", M33fVectorDataTypeId )
		.value("M33dVectorData", M33dVectorDataTypeId )
		.value("M44fVectorData", M44fVectorDataTypeId )
		.value("M44dVectorData", M44dVectorDataTypeId )
		.value("QuatfVectorData", QuatfVectorDataTypeId )
		.value("QuatdVectorData", QuatdVectorDataTypeId )
		.value("StringVectorData", StringVectorDataTypeId )
		.value("FloatData", FloatDataTypeId )
		.value("DoubleData", DoubleDataTypeId )
		.value("IntData", IntDataTypeId )
		.value("UIntData", UIntDataTypeId )
		.value("CharData", CharDataTypeId )
		.value("UCharData", UCharDataTypeId )
		.value("StringData",StringDataTypeId )
		.value("CompoundData", CompoundDataTypeId )
		.value("V2iData", V2iDataTypeId )
		.value("V2fData", V2fDataTypeId )
		.value("V3fData", V3fDataTypeId )
		.value("V2dData", V2dDataTypeId )
		.value("V3dData", V3dDataTypeId )
		.value("Box2fData", Box2fDataTypeId )
		.value("Box3fData", Box3fDataTypeId )
		.value("Box2dData", Box2dDataTypeId )
		.value("Box3dData", Box3dDataTypeId )
		.value("M44fData", M44fDataTypeId )
		.value("M44dData", M44dDataTypeId )
		.value("QuatfData", QuatfDataTypeId )
		.value("QuatdData", QuatdDataTypeId )
		.value("Color3fData", Color3fDataTypeId )
		.value("Color4fData", Color4fDataTypeId )
		.value("Color3dData", Color3dDataTypeId )
		.value("Color4dData", Color4dDataTypeId )
		.value("Color3fVectorData", Color3fVectorDataTypeId )
		.value("Color4fVectorData", Color4fVectorDataTypeId )
		.value("Color3dVectorData", Color3dVectorDataTypeId )
		.value("Color4dVectorData", Color4dVectorDataTypeId )
		.value("BlindDataHolder", BlindDataHolderTypeId )
		.value("Renderable", RenderableTypeId )
		.value("CompoundObject", CompoundObjectTypeId )	
		.value("M33fData", M33fDataTypeId )
		.value("M33dData", M33dDataTypeId )
		.value("Box2fVectorData", Box2fVectorDataTypeId )
		.value("Box2dVectorData", Box2dVectorDataTypeId )
		.value("BoolData", BoolDataTypeId )
		.value("Primitive", PrimitiveTypeId )
		.value("PointsPrimitive", PointsPrimitiveTypeId )
		.value("ImagePrimitive", ImagePrimitiveTypeId )
		.value("MeshPrimitive", MeshPrimitiveTypeId )
		.value("Box2iData", Box2iDataTypeId )
		.value("HalfVectorData", HalfVectorDataTypeId )
		.value("Shader", ShaderTypeId )
		.value("RunTimeTyped", RunTimeTypedTypeId )
		.value("Parameter", ParameterTypeId )
		.value("CompoundParameter", CompoundParameterTypeId )
		.value("StringParameter", StringParameterTypeId )
		.value("ValidatedStringParameter", ValidatedStringParameterTypeId )
		.value("FileNameParameter", FileNameParameterTypeId )
		.value("IntParameter", IntParameterTypeId )
		.value("FloatParameter", FloatParameterTypeId )
		.value("DoubleParameter", DoubleParameterTypeId )
		.value("BoolParameter", BoolParameterTypeId )
		.value("V2fParameter", V2fParameterTypeId )
		.value("V3fParameter", V3fParameterTypeId )
		.value("V2dParameter", V2dParameterTypeId )
		.value("V3dParameter", V3dParameterTypeId )
		.value("Color3fParameter", Color3fParameterTypeId )
		.value("Color4fParameter", Color4fParameterTypeId )
		.value("Box2iParameter", Box2iParameterTypeId )
		.value("Box2fParameter", Box2fParameterTypeId )
		.value("Box3fParameter", Box3fParameterTypeId )
		.value("Box2dParameter", Box2dParameterTypeId )
		.value("Box3dParameter", Box3dParameterTypeId )
		.value("M44fParameter",  M44fParameterTypeId )
		.value("M44dParameter",  M44dParameterTypeId )
		.value("IntVectorParameter", IntVectorParameterTypeId )
		.value("FloatVectorParameter", FloatVectorParameterTypeId )
		.value("DoubleVectorParameter", DoubleVectorParameterTypeId )
		.value("StringVectorParameter", StringVectorParameterTypeId )
		.value("V2fVectorParameter", V2fVectorParameterTypeId )
		.value("V3fVectorParameter", V3fVectorParameterTypeId )
		.value("V2dVectorParameter", V2dVectorParameterTypeId )
		.value("V3dVectorParameter", V3dVectorParameterTypeId )
		.value("Box3fVectorParameter", Box3fVectorParameterTypeId )
		.value("Box3dVectorParameter", Box3dVectorParameterTypeId )
		.value("M33fVectorParameter", M33fVectorParameterTypeId )
		.value("M44fVectorParameter", M44fVectorParameterTypeId )
		.value("M33dVectorParameter", M33dVectorParameterTypeId )
		.value("M44dVectorParameter", M44dVectorParameterTypeId )
		.value("QuatfVectorParameter", QuatfVectorParameterTypeId )
		.value("QuatdVectorParameter", QuatdVectorParameterTypeId )
		.value("Color3fVectorParameter", Color3fVectorParameterTypeId )
		.value("Color4fVectorParameter", Color4fVectorParameterTypeId )
		.value("NullObject", NullObjectTypeId )
		.value("Parameterised", ParameterisedTypeId )
		.value("Op", OpTypeId )
		.value("Reader", ReaderTypeId )
		.value("Writer", WriterTypeId )
		.value("ImageReader", ImageReaderTypeId )
		.value("ImageWriter", ImageWriterTypeId )
		.value("CINImageReader", CINImageReaderTypeId )
		.value("CINImageWriter", CINImageWriterTypeId )
		.value("DPXImageReader", DPXImageReaderTypeId )
		.value("DPXImageWriter", DPXImageWriterTypeId )
		.value("EXRImageReader", EXRImageReaderTypeId )
		.value("EXRImageWriter", EXRImageWriterTypeId )
		.value("JPEGImageReader", JPEGImageReaderTypeId )
		.value("JPEGImageWriter", JPEGImageWriterTypeId )
		.value("TIFFImageReader", TIFFImageReaderTypeId )
		.value("TIFFImageWriter", TIFFImageWriterTypeId )
		.value("ObjectReader", ObjectReaderTypeId )
		.value("ObjectWriter", ObjectWriterTypeId )
		.value("PDCParticleReader", PDCParticleReaderTypeId )
		.value("PDCParticleWriter", PDCParticleWriterTypeId )
		.value("PathParameter", PathParameterTypeId )
		.value("DirNameParameter", DirNameParameterTypeId )
		.value("V3iData", V3iDataTypeId )
		.value("Box3iData", Box3iDataTypeId )
		.value("ObjectParameter", ObjectParameterTypeId )
		.value("ModifyOp", ModifyOpTypeId )
		.value("ImageOp", ImageOpTypeId )
		.value("PrimitiveOp", PrimitiveOpTypeId )
		.value("Procedural", ProceduralTypeId )
		.value("Box3iParameter", Box3iParameterTypeId )
		.value("V2iParameter", V2iParameterTypeId )
		.value("V3iParameter", V3iParameterTypeId )
		.value("ParticleReader", ParticleReaderTypeId )
		.value("ParticleWriter", ParticleWriterTypeId )
		.value("MotionPrimitive", MotionPrimitiveTypeId )
		.value("Transform", TransformTypeId )
		.value("MatrixTransform", MatrixTransformTypeId )
		.value("MotionTransform", MotionTransformTypeId )
		.value("MatrixMotionTransform", MatrixMotionTransformTypeId )
		.value("Group", GroupTypeId )
		.value("AttributeState", AttributeStateTypeId )
		.value("VisibleRenderable", VisibleRenderableTypeId )
		.value("StateRenderable", StateRenderableTypeId )
		.value("OBJReader", OBJReaderTypeId)
		.value("TransformationMatrixfData", TransformationMatrixfDataTypeId)
		.value("TransformationMatrixdData", TransformationMatrixdDataTypeId)
		.value("PointNormalsOp", PointNormalsOpTypeId)
		.value("PointDensitiesOp", PointDensitiesOpTypeId)
		.value("BoolVectorData", BoolVectorDataTypeId)
		.value("VectorDataFilterOp", VectorDataFilterOpTypeId)
		.value("RenderableParameter", RenderableParameterTypeId)
		.value("StateRenderableParameter", StateRenderableParameterTypeId)
		.value("AttributeStateParameter", AttributeStateParameterTypeId)
		.value("ShaderParameter", ShaderParameterTypeId)
		.value("TransformParameter", TransformParameterTypeId)
		.value("MatrixMotionTransformParameter", MatrixMotionTransformParameterTypeId)
		.value("MatrixTransformParameter", MatrixTransformParameterTypeId)
		.value("VisibleRenderableParameter", VisibleRenderableParameterTypeId)
		.value("GroupParameter", GroupParameterTypeId)
		.value("MotionPrimitiveParameter", MotionPrimitiveParameterTypeId)
		.value("PrimitiveParameter", PrimitiveParameterTypeId)
		.value("ImagePrimitiveParameter", ImagePrimitiveParameterTypeId)
		.value("MeshPrimitiveParameter", MeshPrimitiveParameterTypeId)
		.value("PointsPrimitiveParameter", PointsPrimitiveParameterTypeId)
		.value("PreWorldRenderable", PreWorldRenderableTypeId)
		.value("Camera", CameraTypeId)
		.value("NURBSPrimitive", NURBSPrimitiveTypeId)
		.value("DataCastOp", DataCastOpTypeId)
		.value("DataPromoteOp", DataPromoteOpTypeId)
		.value("PointBoundsOp", PointBoundsOpTypeId)
		.value("V2iVectorData", V2iVectorDataTypeId)
		.value("V3iVectorData", V3iVectorDataTypeId)
		.value("PointMeshOp", PointMeshOpTypeId)		
		.value("ParticleMeshOp", ParticleMeshOpTypeId)
		.value("HalfData", HalfDataTypeId)
		.value("MeshPrimitiveOp", MeshPrimitiveOpTypeId)
		.value("PrimitiveEvaluator", PrimitiveEvaluatorTypeId)		
		.value("MeshPrimitiveEvaluator", MeshPrimitiveEvaluatorTypeId)		
		.value("MeshPrimitiveImplicitSurfaceOp", MeshPrimitiveImplicitSurfaceOpTypeId)				
		.value("TriangulateOp", TriangulateOpTypeId)						
		.value("SpherePrimitiveEvaluator", SpherePrimitiveEvaluatorTypeId)
		.value("SpherePrimitive", SpherePrimitiveTypeId)
		.value("Converter", ConverterTypeId)		
		.value("ToCoreConverter", ToCoreConverterTypeId)
		.value("ImageCropOp", ImageCropOpTypeId)
		.value("MeshPrimitiveShrinkWrapOp", MeshPrimitiveShrinkWrapOpTypeId)
		.value("ImagePrimitiveEvaluator", ImagePrimitiveEvaluatorTypeId)
		.value("FromCoreConverter", FromCoreConverterTypeId)		
		.value("ShortData", ShortDataTypeId )
		.value("UShortData", UShortDataTypeId )
		.value("ShortVectorData", ShortVectorDataTypeId )
		.value("UShortVectorData", UShortVectorDataTypeId )
		.value("PathVectorParameter", PathVectorParameterTypeId )
		.value("ColorTransformOp", ColorTransformOpTypeId )
		.value("TransformOp", TransformOpTypeId )
		.value("CurvesPrimitive", CurvesPrimitiveTypeId )
		.value("ImageDiffOp", ImageDiffOpTypeId )
		.value("MeshNormalsOp", MeshNormalsOpTypeId )
		.value("Font", FontTypeId )
		.value("MeshMergeOp", MeshMergeOpTypeId )
		.value("UniformRandomPointDistributionOp", UniformRandomPointDistributionOpTypeId )
		.value("Int64Data", Int64DataTypeId )
		.value("UInt64Data", UInt64DataTypeId )
		.value("Int64VectorData", Int64VectorDataTypeId )
		.value("UInt64VectorData", UInt64VectorDataTypeId )
		.value("MappedRandomPointDistributionOp", MappedRandomPointDistributionOpTypeId )
		.value("PointRepulsionOp", PointRepulsionOpTypeId )
		.value("Grade", GradeTypeId )
		.value("LuminanceOp", LuminanceOpTypeId )
		.value("ImagePrimitiveOp", ImagePrimitiveOpTypeId )
		.value("ChannelOp", ChannelOpTypeId )
		.value("SummedAreaOp", SummedAreaOpTypeId )
		.value("Box2iVectorData", Box2iVectorDataTypeId )
		.value("Box3iVectorData", Box3iVectorDataTypeId )
		.value("MedianCutSampler", MedianCutSamplerTypeId )
		.value("EnvMapSampler", EnvMapSamplerTypeId )
		.value("MeshVertexReorderOp", MeshVertexReorderOpTypeId )
		.value("SplineffData", SplineffDataTypeId )
		.value("SplineddData", SplineddDataTypeId )
		.value("SplinefColor3fData", SplinefColor3fDataTypeId )
		.value("SplinefColor4fData", SplinefColor4fDataTypeId )
		.value("SplineffParameter", SplineffParameterTypeId )
		.value("SplineddParameter", SplineddParameterTypeId )
		.value("SplinefColor3fParameter", SplinefColor3fParameterTypeId )
		.value("SplinefColor4fParameter", SplinefColor4fParameterTypeId )
		.value("CompoundObjectParameter", CompoundObjectParameterTypeId )
		.value("DisplayDriver", DisplayDriverTypeId )
		.value("DisplayDriverCreator", DisplayDriverCreatorTypeId )
		.value("ImageDisplayDriver", ImageDisplayDriverTypeId )
		.value("ClientDisplayDriver", ClientDisplayDriverTypeId )
		.value("DisplayDriverServer", DisplayDriverServerTypeId )
		.value("CoordinateSystem", CoordinateSystemTypeId )
		.value("SplineToImage", SplineToImageTypeId )
		.value("Display", DisplayTypeId )
		.value("MeshTangentsOp", MeshTangentsOpTypeId )
		.value("WarpOp", WarpOpTypeId )
		.value("UVDistortOp", UVDistortOpTypeId )
		.value("LinearToSRGBOp", LinearToSRGBOpTypeId )
		.value("SRGBToLinearOp", SRGBToLinearOpTypeId )
		.value("LinearToCineonOp", LinearToCineonOpTypeId )
		.value("CineonToLinearOp", CineonToLinearOpTypeId )
		.value("CubeColorTransformOp",CubeColorTransformOpTypeId )
		.value("CubeColorLookupfData", CubeColorLookupfDataTypeId )
		.value("CubeColorLookupdData", CubeColorLookupdDataTypeId )		
		.value("CubeColorLookupfParameter", CubeColorLookupfParameterTypeId )
		.value("CubeColorLookupdParameter", CubeColorLookupdParameterTypeId )
		.value("BoolVectorParameter", BoolVectorParameterTypeId )				
		.value("LinearToRec709Op", LinearToRec709OpTypeId )
		.value("Rec709ToLinearOp", Rec709ToLinearOpTypeId )
		.value("ObjectVector", ObjectVectorTypeId )
		.value("ObjectVectorParameter", ObjectVectorParameterTypeId )
		.value("YUVImageWriter", YUVImageWriterTypeId )
		.value("ImageCompositeOp", ImageCompositeOpTypeId )
		.value("ImagePremultiplyOp", ImagePremultiplyOpTypeId )
		.value("ImageUnpremultiplyOp", ImageUnpremultiplyOpTypeId )
		.value("DateTimeData", DateTimeDataTypeId )		
		.value("DateTimeParameter", DateTimeParameterTypeId )				
		.value("SGIImageReader", SGIImageReaderTypeId )
		.value("TimeDurationData", TimeDurationDataTypeId )
		.value("TimeDurationParameter", TimeDurationParameterTypeId )
		.value("TimePeriodData", TimePeriodDataTypeId )
		.value("TimePeriodParameter", TimePeriodParameterTypeId )
		.value("PatchMeshPrimitive", PatchMeshPrimitiveTypeId )
		.value("CurvesPrimitiveParameter", CurvesPrimitiveParameterTypeId )
		.value("CurveExtrudeOp", CurveExtrudeOpTypeId )
		.value("FrameList", FrameListTypeId ) 
		.value("EmptyFrameList", EmptyFrameListTypeId )
		.value("FrameRange", FrameRangeTypeId )
		.value("CompoundFrameList", CompoundFrameListTypeId )
		.value("ReorderedFrameList", ReorderedFrameListTypeId )
		.value("BinaryFrameList", BinaryFrameListTypeId )
		.value("ReversedFrameList", ReversedFrameListTypeId )
		.value("ExclusionFrameList", ExclusionFrameListTypeId )
		.value("FrameListParameter", FrameListParameterTypeId )
	;
}

}
