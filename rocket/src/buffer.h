#pragma once
#ifndef ROCKET_INCLUDED_VERTEXBUFFER
#define ROCKET_INCLUDED_VERTEXVUFFER

namespace Rocket
{
	class Buffer
	{
	protected:
		Buffer();

	public:
		enum MapUsage
		{
			MAP_READ_ONLY,
			MAP_WRITE_ONLY,
			MAP_READ_AND_WRITE
		};

		virtual ~Buffer();

		virtual void UpdateData(void* data, size_t size, size_t offset = 0) = 0;
		virtual size_t Size() const = 0;
		
		virtual void* Map(MapUsage usage) = 0;
		virtual void Unmap() = 0;

	private:
		Buffer(const Buffer&);
	};
}

#endif