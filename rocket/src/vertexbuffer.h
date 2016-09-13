#pragma once
#ifndef ROCKET_VERTEXBUFFER
#define ROCKET_VERTEXVUFFER

namespace Rocket
{
	class VertexBuffer
	{
	public:
		enum MapUsage
		{
			READ_ONLY,
			WRITE_ONLY,
			READ_AND_WRITE
		};

		virtual void UpdateData(void* data, size_t size, size_t offset = 0) = 0;
		virtual size_t Size() const = 0;
		
		virtual void* Map(MapUsage usage) = 0;
		virtual void Unmap() = 0;

		virtual ~VertexBuffer();
	};
}

#endif