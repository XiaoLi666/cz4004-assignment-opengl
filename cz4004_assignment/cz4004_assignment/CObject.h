#ifndef __COBJECT_H__
#define __COBJECT_H__

namespace CZ4004
{
	class CObject
	{
	public:
		virtual void Render() = 0;

		// TO BE CONSIDERED
		// PRE RENDER:
		void PreRender();
		// POST RENDER:
		void PostRender();
	};
}

#endif // __COBJECT_H__