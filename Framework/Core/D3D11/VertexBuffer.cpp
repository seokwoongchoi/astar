#include "stdafx.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(Graphics * graphics)
	: graphics(graphics)
	, vbuffer(nullptr)
	, stride(0)
	, offset(0)
{
}

VertexBuffer::~VertexBuffer()
{
	Clear();
}

void VertexBuffer::Clear()
{
	SAFE_RELEASE(vbuffer);
	stride = 0;
	offset = 0;
}

void * VertexBuffer::Map()
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT hr = graphics->GetDeviceContext()->Map
	(
		vbuffer,
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&mappedResource
	);
	assert(SUCCEEDED(hr));

	return mappedResource.pData;
}

void VertexBuffer::Unmap()
{
	graphics->GetDeviceContext()->Unmap(vbuffer, 0);
}

void VertexBuffer::BindPipeline()
{
	graphics->GetDeviceContext()->IASetVertexBuffers(0, 1, &vbuffer, &stride, &offset);
}
