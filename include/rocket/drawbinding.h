#pragma once
#ifndef ROCKET_DRAWBINDING_INCLUDED
#define ROCKET_DRAWBINDING_INCLUDED

namespace Rocket
{
	class Buffer;

	enum DrawBindingType
	{
		DB_TYPE_FLOAT,
		DB_TYPE_DOUBLE,

		DB_TYPE_INT8,
		DB_TYPE_UINT8,
		DB_TYPE_INT16,
		DB_TYPE_UINT16,
		DB_TYPE_INT32,
		DB_TYPE_UINT32
	};

	enum DrawBindingComponents
	{
		DB_COMPONETNS_1 = 1,
		DB_COMPONENTS_2 = 2,
		DB_COMPONENTS_3 = 3,
		DB_COMPONENTS_4 = 4
	};

	struct VertexBinding
	{
		int index;
		DrawBindingType type;
		DrawBindingComponents components;
		Buffer* buffer;
        unsigned offset;
        unsigned stride;
		// TODO: instancing
	};

	struct IndexBinding
	{
		DrawBindingType type;
		Buffer* buffer;
        unsigned offet;
	};

	struct DrawBindingDef
	{
		VertexBinding* vertexAttributes;
        unsigned numVertexAttributes;

		IndexBinding* indexAttributes;

        unsigned length;
	};

	class DrawBinding
	{
	protected:
		DrawBinding();

	public:
		virtual ~DrawBinding();

	private:
		DrawBinding(const DrawBinding&);
	};
}

#endif
