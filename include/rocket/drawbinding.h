#pragma once
#ifndef ROCKET_DRAWBINDING_INCLUDED
#define ROCKET_DRAWBINDING_INCLUDED

namespace Rocket
{
	class Buffer;

	enum VertexBindingType
	{
		VB_TYPE_FLOAT,
		VB_TYPE_DOUBLE,

		VB_TYPE_INT8,
		VB_TYPE_UINT8,
		VB_TYPE_INT16,
		VB_TYPE_UINT16,
		VB_TYPE_INT32,
		VB_TYPE_UINT32
	};

	enum IndexBindingType
	{
		IB_TYPE_UINT8,
		IB_TYPE_UINT16,
		IB_TYPE_UINT32
	};

	enum DrawBindingComponents
	{
		DB_COMPONENTS_1 = 1,
		DB_COMPONENTS_2 = 2,
		DB_COMPONENTS_3 = 3,
		DB_COMPONENTS_4 = 4
	};

	struct VertexBinding
	{
		int index;
		VertexBindingType type;
		DrawBindingComponents components;
		Buffer* buffer;
        unsigned offset;
        unsigned stride;
		// TODO: instancing
	};

	struct IndexBinding
	{
		IndexBindingType type;
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
