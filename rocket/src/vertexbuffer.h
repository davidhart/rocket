#pragma once
#ifndef ROCKET_VERTEXBUFFER
#define ROCKET_VERTEXVUFFER

namespace Rocket
{
	class VertexBuffer
	{
	protected:
		VertexBuffer();

	public:
		enum MapUsage
		{
			MAP_READ_ONLY,
			MAP_WRITE_ONLY,
			MAP_READ_AND_WRITE
		};

		virtual ~VertexBuffer();

		virtual void UpdateData(void* data, size_t size, size_t offset = 0) = 0;
		virtual size_t Size() const = 0;
		
		virtual void* Map(MapUsage usage) = 0;
		virtual void Unmap() = 0;

	private:
		VertexBuffer(const VertexBuffer&);
	};
}

#endif